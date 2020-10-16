(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (or (= y (+ y (f x y))) (< (f x y) x)))
(check-synth)