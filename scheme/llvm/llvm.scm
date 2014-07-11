; Convenience Macros
;------------------------------------------------------------------------------
(define-syntax defsyntax
  (syntax-rules ()
    [(_ name syms patts ...)
     (define-syntax name (syntax-rules syms patts ...))]))

; AST Syntax Definition
;------------------------------------------------------------------------------
(defsyntax :def (:)
  [(_ (name : args ...) body ...)
   (definition name (:func (list args ...) (list body ...)))]
  [(_ name value) (definition name value)]
  [(_ args ...)   (repl-error)])

(defsyntax :set! ()
 [(_ name value) (assignment name value)]
 [(_ args ...)   (repl-error)])

(defsyntax :apply ()
  [(_ name args ...) (application name (list args ...))]
  [(_ args ...)      (repl-error)])

(defsyntax :if (else)
  [(_ cnd br1)          (if-stmnt cnd br1 '())]
  [(_ cnd br1 br2)      (if-stmnt cnd br1 br2)]
  [(_ cnd br1 else br2) (if-stmnt cnd br1 br2)]
  [(_ args ...)         (repl-error)])

(defsyntax :infix ()
  [(_ left op right) (:apply op left right)]
  [(_ args ...)      (repl-error)])

; AST Data Structures
;------------------------------------------------------------------------------
; Datatypes
(define-record :num value)
(define (:num value)
  (if (number? value) (make-:num value) (repl-error)))

(define-record :sym value)
(define (:sym value)
  (if (symbol? value) (make-:sym value) (repl-error)))

(define-record :str value)
(define (:str value)
  (if (string? value) (make-:str value) (repl-error)))

(define-record :chr value)
(define (:chr value)
  (if (char? value) (make-:chr value) (repl-error)))

(define-record :func args body)
(define (:func args body)
  (if (and (lsof? args :sym?) (list? body))
      (make-:func args body)
      (repl-error)))

; Syntactic Constructs
(define-record definition name value)
(define (definition name value)
  (if (and (:sym? name) (aggregate? value))
    (make-definition name value)
    (repl-error)))

(define-record assignment name value)
(define (assignment name value)
  (if (and (:sym? name) (aggregate? value))
    (make-assignment name value)
    (repl-error)))

(define-record application fn args)
(define (application fn args)
  (if (and (aggregate? fn) (lsof? args aggregate?))
      (make-application fn args)
      (repl-error)))

(define-record if-stmnt cnd br1 br2)
(define (if-stmnt cnd br1 br2)
  (if (and (expression? cnd) (expression? br1)
           (or (null? br2) (expression? br2)))
      (make-if-stmnt cnd br1 br2)
      (repl-error)))

; Utility Predicate Procedures
;------------------------------------------------------------------------------
(define (primitive? value)
  (or (:num? value) (:sym? value) (:str? value) (:chr? value)))

(define (aggregate? value)
  (or (primitive? value) (:func? value) (application? value)))

(define (expression? value)
  (or (aggregate? value) (if-stmnt? value)))

(define (lsof? lst prdfn)
  (if (not (list? lst)) #f
      (if (null? lst) #t
          (and (prdfn (car lst))
               (lsof? (cdr lst) prdfn)))))

; AST Translation Procedures
;------------------------------------------------------------------------------
(define (sym->string sym)
  (symbol->string (:sym-value sym)))

(define (num->string num)
  (number->string (:num-value num)))

(define (str->string str)
  (:str-value str))

(define (chr->string chr)
  (string-append "'" (string (:chr-value chr)) "'"))

(define (func->string func)
  "&lambda")

(define (definition->string def)
  (string-append "var " (sym->string (definition-name def)) " = "
                 (expr->string (definition-value def)) ";"))

(define (assignment->string def)
  (string-append (sym->string (assignment-name def)) " = "
                 (expr->string (assignment-value def)) ";"))

(define (application->string app)
  (string-append
    (expr->string (application-fn app))
    "("
    (apply string-append
      (map (lambda (e) (string-append (expr->string e) ","))
           (application-args app)))
    ")"))

(define (if-stmnt->string cnd)
  (string-append
    "IF("
    (expr->string (if-stmnt-cnd cnd)) ","
    (expr->string (if-stmnt-br1 cnd)) ","
    (if (not (null? (if-stmnt-br2 cnd)))
        (expr->string (if-stmnt-br2 cnd))
        "Null")
    ")"))

(define (expr->string expr)
  (cond [(:sym? expr)        (sym->string expr)]
        [(:num? expr)        (num->string expr)]
        [(:str? expr)        (str->string expr)]
        [(:chr? expr)        (chr->string expr)]
        [(:func? expr)       (func->string expr)]
        [(definition? expr)  (definition->string expr)]
        [(assignment? expr)  (assignment->string expr)]
        [(application? expr) (application->string expr)]
        [(if-stmnt? expr)    (if-stmnt->string expr)]))

; Lambda lifting
;------------------------------------------------------------------------------
(define (lift-lambdas fnlst prnt expr)
  (cond [(:func? expr)       '()]
        [(definition? expr)  '()]
        [(assignment? expr)  '()]
        [(application? expr) '()]
        [(if-stmnt? expr)    '()]
        [else                '()]))

; Utility functions
;------------------------------------------------------------------------------
(define unique-id
  ((lambda ()
     (define id 0)
     (lambda () (set! id (+ id 1)) id))))

(define (lambda-id)
  (string-append "lambda_" (number->string (unique-id))))

; REPL Control Functions
;------------------------------------------------------------------------------
(define (lang-repl)
  (print (eval (read (current-input-port))
               (interaction-environment)))
  (lang-repl))

(define (repl-error)
  (print "ERROR"))

; Start the REPL
;------------------------------------------------------------------------------
(lang-repl)

