(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int)
(declare-var x Int)
(declare-var y Int)
(constraint (or (<= (- x x) (f x y)) (<= (- x x) (f x y))))
(check-synth)