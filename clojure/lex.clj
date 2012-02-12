(use '[clojure.java.io :only (reader)])

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
; Main
;------------------------------------------------------------------------------
(defn handle-error [s]
	(println (str "Lex Error near: " s)))

(def tokens
	'((#"[A-Za-z-]+" :word)
	  (#";"          :terminator)
	  (#"#.+$")      ; Ignore comments
	  (#"\s+")       ; Ignore whitespace
	  (#"."          handle-error)))

(print (lex tokens (reader "foo.hl")))

