(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (or (< y (+ (f y x) x)) (< y (+ (f y x) x))))
(check-synth)