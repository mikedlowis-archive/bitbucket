;------------------------------------------------------------------------------
; Associative Arrays (aka Tables)
;------------------------------------------------------------------------------
; entry? - determines whether the argument is a table entry
(define entry? pair?)

; entry - constructs a new table entry from the key and value passed in
(define entry cons)

; table? - determines whether the argument is a table
(define table? list?)

; table - constructs a new table from 0 or more entries
(define table list)

; table-get - retrieves a value from the table for the corresponding key
(define (table-get tbl key)
  (if (null? tbl)
	'()
    (let*
	  ((e (car tbl))
	   (k (car e))
	   (v (cdr e)))
	  (if (equal? k key) 
	    v 
		(table-get (cdr tbl) key) ))))

; table-put - associates a value with a specific key and stores it in the table
(define (table-put tbl key val)
  (if (null? tbl)
	(table (entry key val))
	(let*
	  ((e (car tbl))
	   (k (car e))
	   (v (cdr e)))
	  (if (equal? k key) 
	    (cons (entry key val) (cdr tbl)) 
	    (if (null? (cdr tbl))
		  (table e (entry key val))
		  (cons e (table-put (cdr tbl) key val)) )))))

;------------------------------------------------------------------------------
; Scope Chain (Symbol Table)
;------------------------------------------------------------------------------
(define (scope-start!) 
  (set! symbol-table (cons (table) symbol-table)))

(define (scope-end!) 
  (set! symbol-table (cdr symbol-table)))

(define (scope-register! sym val) 
  (set! symbol-table 
	(cons 
	  (table-put (car symbol-table) sym val)
	  (cdr symbol-table) )))

(define (scope-resolve tbl key) 
  (if (not (null? tbl))
	(let*
	  ((scp (car tbl))
	   (val (table-get scp key)))
	  (if (not (null? val))
		val
		(if (not (null? (cdr tbl)))
		  (scope-resolve (cdr tbl) key) )))))

;------------------------------------------------------------------------------
; Symbol Table
;------------------------------------------------------------------------------
(define symbol-table (list (table)))

; Global Scope
(scope-register! "foo1" "bar1")
(scope-register! "foo2" "bar2")
(scope-register! "foo3" "bar3")
(print "Symbol Table:")
(print symbol-table)
(print)

(print "Access bindings for Global Scope")
(print (scope-resolve symbol-table "foo1"))
(print (scope-resolve symbol-table "foo2"))
(print (scope-resolve symbol-table "foo3"))
(print (scope-resolve symbol-table "foo4"))
(print (scope-resolve symbol-table "foo5"))

(print "Local Scope")
(scope-start!)

(scope-register! "foo1" "bar1_1")
(scope-register! "foo4" "bar4")
(print "Symbol Table:")
(print symbol-table)
(print)

(print "Access bindings for Local Scope")
(print (scope-resolve symbol-table "foo1"))
(print (scope-resolve symbol-table "foo2"))
(print (scope-resolve symbol-table "foo3"))
(print (scope-resolve symbol-table "foo4"))
(print (scope-resolve symbol-table "foo5"))

(print "Nested Local Scope")
(scope-start!)

(scope-register! "foo1" "bar1_2")
(scope-register! "foo5" "bar5")
(print "Symbol Table:")
(print symbol-table)
(print)

(print "Access bindings for Nested Local Scope")
(print (scope-resolve symbol-table "foo1"))
(print (scope-resolve symbol-table "foo2"))
(print (scope-resolve symbol-table "foo3"))
(print (scope-resolve symbol-table "foo4"))
(print (scope-resolve symbol-table "foo5"))

(scope-end!)
(print "Access bindings for Local Scope")
(print (scope-resolve symbol-table "foo1"))
(print (scope-resolve symbol-table "foo2"))
(print (scope-resolve symbol-table "foo3"))
(print (scope-resolve symbol-table "foo4"))
(print (scope-resolve symbol-table "foo5"))

(scope-end!)
(print "Access bindings for Global Scope")
(print (scope-resolve symbol-table "foo1"))
(print (scope-resolve symbol-table "foo2"))
(print (scope-resolve symbol-table "foo3"))
(print (scope-resolve symbol-table "foo4"))
(print (scope-resolve symbol-table "foo5"))

(exit)
