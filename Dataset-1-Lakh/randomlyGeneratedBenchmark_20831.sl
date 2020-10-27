(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (and (>= (+ y x) (+ y x)) (> (- (+ y x) y) (- (+ y x) y))))
(check-synth)