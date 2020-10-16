(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (or (>= (f y x) (f y x)) (<= (- (f y x) x) x)))
(check-synth)