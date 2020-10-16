(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (or (< (- x y) (f x y)) (>= y (f x y))))
(check-synth)