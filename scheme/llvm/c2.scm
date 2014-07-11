(use srfi-1)

; Formal Syntax
;------------------------------------------------------------------------------
;
; Program ::= Form*
;
; Form ::= Definition | Expression
;
; Definition ::= '(:def' Variable Expression ')'
;              | '(:begin' Definition* ')'
;
; Expression ::= Constant
;              | Variable
;              | '(:quote' Datum ')'
;              | '(:func' ArgList Expression Expression* ')'
;              | '(:if' Expression Expression Expression ')'
;              | '(:set' Variable Expression ')'
;              | '(:apply' Expression Expression* ')'
;
; Constant ::= Boolean
;            | Number
;            | Character
;            | String
;
; ArgList ::= '(' Variable ')'
;           | '(' Variable Variable '.' Variable ')'
;

(define (validate-form frm)
  (if (and (list? frm) (not (null? frm)))
      (case (car frm)
            [(quote) (validate-quotation frm)]
            [(func)  (validate-func frm)]
            [(if)    (validate-if frm)]
            [(set)   (validate-set frm)]
            [else    (validate-apply frm)])
      (validate-constant frm)))

(define (validate-quotation frm)
  (if (not (quote? frm))
      (repl-error frm "Invalid quotation")))

(define (validate-func frm)
  (if (not (func? frm))
      (repl-error frm "Invalid function definition")))

(define (validate-if frm)
  (if (not (if? frm))
      (repl-error frm "Invalid if statement")))

(define (validate-set frm)
  (if (not (set? frm))
      (repl-error frm "Invalid assignment expression")))

(define (validate-apply frm)
  (if (not (apply? frm))
      (repl-error frm "Invalid application expression")))

(define (validate-constant frm)
  (if (not (constant? frm))
      (repl-error frm "Not a valid constant")))

;------------------------------------------------------------------------------

(define (form? frm)
  (or (definition? frm) (expression? frm)))

(define (definition? frm)
  (or (def? frm) (begin? frm)))

(define (def? frm)
  (and (list-of-length? frm 3)
       (equal? 'def (car frm))
       (symbol? (cadr frm))
       (expression? (caddr frm))))

(define (begin? frm)
  (and (list-of->=-length? frm 2)
       (equal? 'begin (car frm))
       (list-of? (cdr frm) definition?)))

(define (expression? expr)
  (if (constant? expr) #t
      (and (list? expr)
           (not (null? expr))
           (case (car expr) [(begin def) #f]
                            [else        #t]))))

(define (quote? frm)
  (and (list-of-length? frm 2)
       (equal? 'quote (car frm))))

(define (func? frm)
  (and (list-of->=-length? frm 3)
       (equal? 'func (car frm))
       (list-of? (cadr frm) symbol?)
       (list-of? (cddr frm) expression?)))

(define (if? frm)
  (and (list-of-length? frm 4)
       (equal? 'if (car frm))
       (list-of? (cdr frm) expression?)))

(define (set? frm)
  (and (list-of-length? frm 3)
       (equal? 'set (car frm))
       (symbol? (cadr frm))
       (expression? (caddr frm))))

(define (apply? frm)
  (and (not (null? frm))
       (list-of? frm expression?)))

(define (constant? frm)
  (or (number? frm) (string? frm) (symbol? frm) (char? frm) (boolean? frm)))

; Utility Predicate Procedures
;------------------------------------------------------------------------------
(define (list-of? lst prdfn)
  (if (not (list? lst)) #f
      (if (null? lst) #t
          (and (prdfn (car lst))
               (list-of? (cdr lst) prdfn)))))

(define (list-of->=-length? lst len)
  (and (list? lst) (>= (length lst) len)))

(define (list-of-length? lst len)
  (and (list? lst) (= (length lst) len)))

(define (get-free-vars expr)
  (if (symbol? expr) expr
      (case (if (list? expr) (car expr) '())
            [(def set)  (list (cadr expr) (get-free-vars (caddr expr)))]
            [(begin if) (map get-free-vars (cdr expr))]
            [(func)     (filter-vars (cadr expr) (map get-free-vars (cddr expr)))]
            [else       (map get-free-vars expr)])))

(define (filter-vars defd lst)
  (filter (lambda (item) (not (member item defd))) lst))

; Closure Conversion
;------------------------------------------------------------------------------
(define closure-list '())

(define (closure-conversion expr)

(define (register-func name fn) '())

(define (func->closure fn)
  ;(define env    (make-env (get-free-vars fn)))
  ;(define fn-ptr (register-func fn env))
  `(closure ,fn-ptr ,env))

; REPL Control Functions
;------------------------------------------------------------------------------
(define (lang-repl)
  (define form (read (current-input-port)))
  (validate-form form)
  (print form)
  (lang-repl))

(define (repl-error frm msg)
  (pretty-print frm)
  (error msg))

; Start the REPL
;------------------------------------------------------------------------------
;(lang-repl)

; Unit tests
;------------------------------------------------------------------------------
(assert (not (form? '())))
(assert (form? '(def foo bar)))
(assert (form? '(foo bar)))
(assert (form? 'foo))

; Definition tests
(assert (not (definition? '())))
(assert (not (definition? '(def))))
(assert (not (definition? '(def foo))))
(assert (not (definition? '(def "foo" bar))))
(assert (definition? '(def foo bar)))
(assert (not (definition? '())))
(assert (not (definition? '(begin))))
(assert (not (definition? '(begin foo))))
(assert (definition? '(begin (def foo bar))))
(assert (definition? '(begin (begin (def foo bar)))))

(assert (not (def? '())))
(assert (not (def? '(def))))
(assert (not (def? '(def foo))))
(assert (not (def? '(def "foo" bar))))
(assert (def? '(def foo bar)))

(assert (not (begin? '())))
(assert (not (begin? '(begin))))
(assert (not (begin? '(begin foo))))
(assert (begin? '(begin (def foo bar))))
(assert (begin? '(begin (begin (def foo bar)))))

; Expression tests
(assert (not (expression? '())))
(assert (not (expression? '(def foo bar))))
(assert (expression? '(quote foo)))
(assert (expression? '(func (foo) bar)))
(assert (expression? '(if foo bar baz)))
(assert (expression? '(set foo bar)))
(assert (expression? '(foo)))
(assert (expression? '"foo"))
(assert (expression? 'foo))
(assert (expression? '123))
(assert (expression? '#\x))
(assert (expression? '#t))

; Quotation tests
(assert (not (quote? '())))
(assert (not (quote? '(quote))))
(assert (quote? '(quote "")))
(assert (quote? '(quote foo)))
(assert (quote? '(quote #\x)))
(assert (quote? '(quote #t)))
(assert (quote? '(quote 123)))
(assert (quote? '(quote ())))

; Function tests
(assert (not (func? '())))
(assert (not (func? '(func))))
(assert (not (func? '(func bar))))
(assert (not (func? '(func bar baz))))
(assert (not (func? '(func ()))))
(assert (not (func? '(func (a 1) baz))))
(assert (func? '(func () baz)))
(assert (func? '(func (a) baz)))
(assert (func? '(func (a b) bar baz)))

; If Statement tests
(assert (not (if? '())))
(assert (not (if? '(if))))
(assert (not (if? '(if foo))))
(assert (not (if? '(if foo bar))))
(assert (if? '(if foo bar baz)))

; Set tests
(assert (not (set? '())))
(assert (not (set? '(set))))
(assert (not (set? '(set foo))))
(assert (not (set? '(set "foo" bar))))
(assert (set? '(set foo bar)))

; Application tests
(assert (not (apply? '())))
(assert (apply? '(foo)))
(assert (apply? '(foo bar)))
(assert (apply? '(foo bar baz)))

; Constant tests
(assert (not (constant? '())))
(assert (constant? '"foo"))
(assert (constant? 'foo))
(assert (constant? '123))
(assert (constant? '#\x))
(assert (constant? '#t))

;(exit)

