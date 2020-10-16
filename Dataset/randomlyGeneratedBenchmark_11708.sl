(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (or (>= (f y y) (+ (f y y) y)) (< x y)))
(check-synth)