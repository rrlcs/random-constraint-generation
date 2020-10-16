(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (or (> (f x y) x) (< x (- x (f x y)))))
(check-synth)