(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (and (< x (+ (f x x) (f x x))) (> (+ (f x x) (f x x)) (f x x))))
(check-synth)