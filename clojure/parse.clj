(use '[clojure.java.io :only (reader)])
(use 'clojure.pprint)

;------------------------------------------------------------------------------
; Lexer Functions
;------------------------------------------------------------------------------
(defn token? [re s]
	(not (nil? (re-matches re s))))	

(defn token [res s]
	(let [m (first (filter #(token? (first %) s) res))]
		(if (not (nil? m)) 
			(list (second m) (str s)) )))

(defn eval-token [tok]
	(if (symbol? (first tok))
		((eval (first tok)) (second tok))
		tok))

(defn char-seq [^java.io.BufferedReader rdr]
	(when-let [c (.read rdr)]
		(if (> c -1)
			(cons (char c) (lazy-seq (char-seq rdr))))))

(defn token-seq [types coll]
	(loop [s   ""
		   tok nil
		   c   coll]
		(if (not (empty? c))
			(let [news (str s (first c))
				  m    (token types news)]
				(if (nil? m)
					(cons (eval-token tok) (lazy-seq (token-seq types c)))
					(recur news m (rest c)) )))))

(defn lex [res ^java.io.BufferedReader rdr]
	(filter #(not (nil? (first %))) (token-seq res (char-seq rdr))))

;------------------------------------------------------------------------------
; Parser Functions
;------------------------------------------------------------------------------
(defn lr-shift [])
(defn lr-reduce [])
(defn lr-accept [])
(defn lr-action [])
(defn lr-goto [])

(defn rule [keyw & patterns]
	(for [pat patterns]
		(list keyw (first pat) (second pat)) ))

(defmacro defgrammar [sym start & rules] 
	`(def ~sym 
		(concat
			'((:start (~start)))
			~@rules) ))

(defn lr-parse [toks sytx input]
	(loop [stck  '()
		   inpt  input
		   outpt '() ]))

;------------------------------------------------------------------------------
; Main
;------------------------------------------------------------------------------
(defn lex-error [s]
	(println (str "Lex Error near: " s)))

(def tokens
	'((#"[A-Za-z-]+" :word)
	  (#";"          :terminator)
	  (#"#.+$")      ; Ignore comments
	  (#"\s+")       ; Ignore whitespace
	  (#"."          lex-error)))

; Sample Grammar DSL
(defgrammar syntax :exp
	(rule :exp
		'((:exp \+ :num) act1) 
		'((:exp \* :num) act2) 
		'((:num)         act3) )

	(rule :num
		'((0) act4)
		'((1) act5) ))

(pprint syntax)
;(println)
;(pprint (lex tokens (reader "foo.hl")))

