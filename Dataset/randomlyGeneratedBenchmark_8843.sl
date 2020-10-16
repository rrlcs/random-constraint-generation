(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (or (>= x (f y y)) (> (+ y (+ (f y y) y)) y)))
(check-synth)