(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (and (< y (- (- (f x y) x) x)) (< y (- (- (f x y) x) x))))
(check-synth)