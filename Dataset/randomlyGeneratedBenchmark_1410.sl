(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (and (< (+ x x) y) (< (f y x) (+ x x))))
(check-synth)