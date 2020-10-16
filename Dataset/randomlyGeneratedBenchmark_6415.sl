(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (or (< x (+ (- y y) y)) (> (- y y) x)))
(check-synth)