(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (and (= (- y x) (f y x)) (= (- y x) (f y x))))
(check-synth)