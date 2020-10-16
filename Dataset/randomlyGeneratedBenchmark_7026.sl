(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (and (>= (+ (+ x (f x y)) (f x y)) (+ (+ x (f x y)) (f x y))) (>= (+ (+ x (f x y)) (f x y)) (+ (+ x (f x y)) (f x y)))))
(check-synth)