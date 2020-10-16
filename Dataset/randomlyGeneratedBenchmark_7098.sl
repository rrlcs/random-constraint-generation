(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (and (= x (+ x (f x y))) (>= (+ x y) y)))
(check-synth)