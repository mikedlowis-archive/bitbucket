; Convenience Macros
;------------------------------------------------------------------------------
(define-syntax defsyntax
  (syntax-rules ()
    [(_ name syms patts ...)
     (define-syntax name (syntax-rules syms patts ...))]))

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

(defsyntax :program ()
  [(_ frms ...) (if (lsof? (list frms ...) form?)
                    (list frms ...)
                    (repl-error (list frms ...) "Not a valid program"))])

(defsyntax :def ()
  [(_ name value) (definition 'name value)]
  [(_ args ...)   (repl-error (list _ args ...) "Not a valid definition")])

(defsyntax :begin ()
  [(_ exprs ...) (begin-block (list exprs ...))])

(defsyntax :quote ()
  [(_ datum)    '(quote datum)]
  [(_ args ...) (repl-error (list _ args ...) "Not a valid quotation")])

(defsyntax :if ()
  [(_ cnd br1 br2) (if-stmnt cnd br1 br2)]
  [(_ args ...)    (repl-error (list _ args ...) "Not a valid if statement")])

(defsyntax :func ()
  [(_ args expr ...) (func 'args (list expr ...))]
  [(_ args ...)     (repl-error (list _ args ...) "Not a valid function")])

(defsyntax :set ()
  [(_ name value) (assignment 'name value)]
  [(_ args ...)   (repl-error (list _ args ...) "Not a valid assignment")])

(defsyntax :apply ()
  [(_ fn args ...) (application fn (list args ...))]
  [(_ args ...)    (repl-error (list _ args ...) "Not a valid application")])

; Syntax Validators
(define (definition name value)
  (define form `(def ,name ,value))
  (if (and (symbol? name) (expression? value))
      form
      (repl-error form "Invalid definition")))

(define (begin-block exprs)
  (define form (cons 'begin exprs))
  (cond [(lsof? exprs definition?) form]
        [(lsof? exprs expression?) (application (func '() exprs) '())]
        [else                      (repl-error form "")]))

(define (if-stmnt cnd br1 br2)
  (define form `(if ,cnd ,br1 ,br2))
  (if (and (expression? cnd) (expression? br1) (expression? br2))
      form
      (repl-error from "")))

(define (func args body)
  (define form (cons 'func (cons args body)))
  (if (and (lsof? args symbol?) (lsof? body form?))
      form
      (repl-error form "")))

(define (assignment name value)
  (define form `(set ,name ,value))
  (if (and (symbol? name) (expression? value))
      form
      (repl-error form "")))

(define (application fn args)
  (define form (cons 'apply (cons fn args)))
  (if (and (expression? fn) (lsof? args expression?))
      form
      (repl-error "")))

; Predicates
(define (form? frm)
  (or (definition? frm) (expression? frm)))

(define (definition? def)
  (and (list? def)
       (or (equal? 'begin (car def))
           (equal? 'def (car def)))))

(define (expression? expr)
  (if (constant? expr) #t
      (and (list? expr)
           (case (car expr) [(quote if func set apply) #t]
                            [else                      #f]))))

(define (constant? cnst)
  (or (symbol? cnst) (char? cnst) (string? cnst) (number? cnst) (boolean? cnst)))

; Utility Predicate Procedures
;------------------------------------------------------------------------------
(define (lsof? lst prdfn)
  (if (not (list? lst)) #f
      (if (null? lst) #t
          (and (prdfn (car lst))
               (lsof? (cdr lst) prdfn)))))

(define (get-variables expr)
  (if (symbol? expr) expr
      (case (if (list? expr) (car expr) '())
            [(def)            (get-variables (caddr expr))]
            [(set)            (list (cadr expr) (get-variables (caddr expr)))]
            [(begin if apply) (map get-variables (cdr expr))]
            [(func)           (map get-variables (cddr expr))]
            [else             '()])))

(define (get-free-vars expr)
  (if (symbol? expr) expr
      (case (if (list? expr) (car expr) '())
            [(def)            (get-free-vars (caddr expr))]
            [(set)            (list (cadr expr) (get-free-vars (caddr expr)))]
            [(begin if apply) (map get-free-vars (cdr expr))]
            [(func)           (map get-free-vars (cddr expr))]
            [else             '()])))

; REPL Control Functions
;------------------------------------------------------------------------------
(define (lang-repl)
  (print (eval (read (current-input-port))
               (interaction-environment)))
  (lang-repl))

(define (repl-error frm msg)
  (pretty-print frm)
  (error msg))

; Start the REPL
;------------------------------------------------------------------------------
;(lang-repl)

(define test-form
  (:program
    (:def make_incrementor
      (:apply (:func ()
        (:def num 0)
        (:func () (:set num (:apply '+ 1 'num)) 'num))))))

(print (get-variables 'foo))
(print (get-variables (:def foo 'bar)))
(print (get-variables (:set foo 'baz)))
(print (get-variables (:begin (:def foo 'foo) (:def foo 'bar) (:def abc 'baz))))
(print (get-variables (:if 'foo 'bar 'baz)))
(print (get-variables (:apply 'foo 'bar 'baz)))
(print (get-variables (:func () 'foo 'bar 'baz)))
;(exit)

