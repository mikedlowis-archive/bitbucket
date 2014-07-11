#lang scheme
; A macro that gives us a standard while loop
(define-syntax while
  (syntax-rules ()
    ((_ cnd body ...)
      (if cnd
        (let loop ()
          body ...
          (if cnd (loop)))))))

; the imperative version of our function
(define (get-stats-imp lst)
  (define val  (if (null? lst) '() (car lst)))
  (define minv val)
  (define maxv val)
  (define sum 0)
  (define count 0)
  (while (not (null? lst))
    ; Update our values
    (if (< val minv) (set! minv val))
    (if (> val maxv) (set! maxv val))
    (set! sum (+ sum val))
    (set! count (+ count 1))
    ; Set the next val
    (set! lst (cdr lst))
    (set! val (if (null? lst) '() (car lst))))
  (list minv maxv (/ sum count)))

; the functional version
(define (get-stats-func lst)
  (let ((sval (if (null? lst) '() (car lst))))
    (get-stats-func-helper lst sval sval 0 0)))

(define (get-stats-func-helper lst minv maxv sum count)
  (if (null? lst)
    (list minv maxv (if (> count 1) (/ sum count) '()))
    (let ((val (car lst)))
      (get-stats-func-helper
        (cdr lst)
        (if (< val minv) val minv)
        (if (> val maxv) val maxv)
        (+ sum val)
        (+ count 1)))))

