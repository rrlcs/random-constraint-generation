(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (and (<= x (- (- x x) y)) (<= x (- (- x x) y))))
(check-synth)