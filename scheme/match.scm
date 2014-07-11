(define (patt-matches? seq idxfn predfn patt)
  (if (equal? 'or (car patt))
      (seq-matches-one-of? seq idxfn predfn (cdr patt))
      (seq-matches-patt? seq idxfn predfn patt 0)))

(define (seq-matches-one-of? seq idxfn predfn pattlst)
  (cond ((null? pattlst) #f)
        ((seq-matches-patt? seq idxfn predfn (car pattlst) 0) #t)
        (else (seq-matches-one-of? seq idxfn predfn (cdr pattlst)))))

(define (seq-matches-patt? seq idxfn predfn patt idx)
  (cond ((null? patt) #t)
        ((predfn (idxfn seq idx) (car patt))
         (seq-matches-patt? seq idxfn predfn (cdr patt) (+ idx 1)))
        (else #f)))

(define-syntax match
  (syntax-rules (else)
    ((_ seq idxfn predfn (else expr1 expr2 ...))
     (begin expr1 expr2 ...))

    ((_ seq idxfn predfn (patt expr1 expr2 ...))
     (if (patt-matches? seq idxfn predfn (quote patt))
         (begin expr1 expr2 ...)))

    ((_ seq idxfn predfn (patt expr1 expr2 ...) cls1 cls2 ...)
     (if (patt-matches? seq idxfn predfn (quote patt))
         (begin expr1 expr2 ...)
         (match seq idxfn predfn cls1 cls2 ...)))))

;(print (match '(1 2 3) list-ref equal?
;              ((or (1 3)
;                   (1 2)) 1)
;              ((1 1 2)    2)
;              (else       3)))

;(print (seq-matches-patt? '(1 2 3) list-ref equal? '(1 2) 0))
;(print (seq-matches-patt? '(1 2 3) list-ref equal? '(1 3) 0))
;(print (seq-matches-one-of? '(1 2 3) list-ref equal? '((1 3) (1 2))))
;(print (seq-matches-one-of? '(1 2 3) list-ref equal? '((1 3) (1 4))))

(define (match-test coll seqfn predfn)
  (match coll seqfn predfn
         ((1)           1)
         ((2 1)         2)
         ((or (1 2)
              (1 1 2))  3)
         ((1 symbol? 2) 4)
         (else          5)))

(print (equal? 1 (match-test '(1) list-ref equal?)))
(print (equal? 2 (match-test '(2 1) list-ref equal?)))
(print (equal? 3 (match-test '(1 2) list-ref equal?)))
(print (equal? 3 (match-test '(1 1 2) list-ref equal?)))
;(print (equal? 4 (match-test '(1 foo 2) list-ref equal?)))
(print (equal? 5 (match-test '(3) list-ref equal?)))

(exit)

