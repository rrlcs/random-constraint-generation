(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (and (< (- (f x x) x) x) (< (- (f x x) x) x)))
(check-synth)