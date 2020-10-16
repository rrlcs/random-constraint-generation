(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (or (> (- x (f x y)) (+ (f x y) y)) (> (- x (f x y)) (+ (f x y) y))))
(check-synth)