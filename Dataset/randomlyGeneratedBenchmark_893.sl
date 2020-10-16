(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (or (> x y) (<= (- (f y x) (- (f y x) x)) (- (f y x) x))))
(check-synth)