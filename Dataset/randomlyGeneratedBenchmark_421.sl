(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (and (< (+ (f y y) (f y y)) y) (= (+ (f y y) (f y y)) x)))
(check-synth)