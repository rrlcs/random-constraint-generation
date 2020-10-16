(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (or (= (f x y) (f x y)) (>= (+ (+ y x) x) y)))
(check-synth)