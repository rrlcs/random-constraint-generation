(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (and (= (f x y) (+ x y)) (= (+ (f y x) (f x y)) (+ (f y x) (f x y)))))
(check-synth)