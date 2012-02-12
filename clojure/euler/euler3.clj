(use '[clojure.main :only [repl]])

(defn factors [n]
	(filter #(zero? (mod % n)) (range 2 n)))

(defn isprime [n]
	(empty? (filter #(zero? (rem n %)) (range 2 n))))

(defn next-primes [p]
	(let [z (if (zero? (mod p 2)) 1 2) ]
		(loop [n (+ p z)]
			(if (isprime n) 
				(cons n (lazy-seq (next-primes n)))
				(recur (+ n z))))))

(defn primes []
"Return a lazy-seq of all prime numbers"
	(lazy-cat [2 3]
		(next-primes 3)))
	
(defn e3 [n]
"What is the largest prime factor of the number 600851475143"
	(max
		(filter
			#(zero? (mod % n))
			(filter isprime (range 1 (- n 1)))
		)
	)
)

(println 600851475143)

(repl)
