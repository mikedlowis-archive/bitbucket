(use '[clojure.java.io :only (reader)])

;------------------------------------------------------------------------------
; Commands
;------------------------------------------------------------------------------
(defn install-package [args]
	(println "# install-package")
	(println "ssh <user>@<host> apt-get install" (first args))
	(println))

(defn install-module [args] 
	(println "# install-module")
	(println (str "cd submodules/" (first args)))
	(println (str "<this-script> submodules/" (first args)))
	(println "cd ../../")
	(println))

(defn run-script [args] 
	(println "# run-script")
	(println "scp" (first args) "<user>@<host>")
	(println "ssh <user>@<host> chmod +x" (first args))
	(println "ssh <user>@<host>" (first args))
	(println))

(defn fetch-config [args] 
	(println "# fetch-config")
	(println "scp" (first args) "<user>@<host>:<destination>")
	(println))

;------------------------------------------------------------------------------
; Setup Functions and Input
;------------------------------------------------------------------------------
; Function to determine which lines we ignore
(defn ignored-line? [str]
	"Function to determine which lines we ignore"
	(or 
		(empty? (.replaceAll str "\\s+" ""))
		(.equals (.substring (.replaceAll str "^\\s+" "") 0 1) "#") ))

; Read in the lines from our file
(def input
	(filter #(not (ignored-line? %)) (line-seq (reader "foo.hl"))))

;------------------------------------------------------------------------------
; Main
;------------------------------------------------------------------------------
; Loop through all of our valid lines
(doseq [line input]
	; Tokenize the line
	(let [cmd (.split line "\\s+")]
		; Call the first element as a function and pass the rest as a param
		((eval (symbol (first cmd))) (rest cmd)) ))
