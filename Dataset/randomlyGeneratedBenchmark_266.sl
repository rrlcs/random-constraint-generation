(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (and (> y (- (f x x) x)) (> y (- (f x x) x))))
(check-synth)