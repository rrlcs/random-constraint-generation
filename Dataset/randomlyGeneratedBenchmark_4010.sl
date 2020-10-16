(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (or (>= y x) (<= (+ (f y y) y) (- (f y y) (f y y)))))
(check-synth)