;; The background theory is linear integer arithmetic
(set-logic LIA)

;; Name and signature of the function to be synthesized
(synth-fun div1 ((x Int)) Int)

(declare-var x Int)

;; Define the semantic constraints on the function
(constraint (=> (= ( mod x 2) 1) ( = (div1 x) 0) ))
(constraint (=> (= ( mod x 2) 0) ( = ( + (div1 x) (div1 x)) x) ) )

(check-synth)
