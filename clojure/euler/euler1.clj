(defn we-care? [a]
	(or
		(== 0 (rem a 3))
		(== 0 (rem a 5)) ))

(defn add-nums [accum min max]
	(if (< min max)
		(if (we-care? min)
			(add-nums (+ accum min) (+ min 1) max)
			(add-nums accum (+ min 1) max))
		accum))

(println (add-nums 0 0 1000000))
(println 
	(reduce 
		+ 
		(filter 
			we-care? 
			(range 
				0 
				1000000 ))))
