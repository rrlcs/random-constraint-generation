(set-logic LIA)
(synth-fun f ((x Int) (y Int)) Int
    ;((I Int) (B Bool))

;    ((I Int (x y 0 1 2
 ;           (- 1)
  ;          (- I I)
   ;         (ite B I I)))
    ; (B Bool ((>= I I))))
)
(declare-var x Int)
(declare-var y Int)
(constraint (>= (+ y (f x y)) x))
(check-synth)