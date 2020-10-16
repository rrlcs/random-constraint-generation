(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (and (< (f y x) (- (f y x) y)) (< (f y x) (- (f y x) y))))
(check-synth)