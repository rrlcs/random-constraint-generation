(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (or (> y (- (f x x) (f x x))) (> y (- (f x x) (f x x)))))
(check-synth)