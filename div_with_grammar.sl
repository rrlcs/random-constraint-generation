;; The background theory is linear integer arithmetic
(set-logic LIA)

;; Name and signature of the function to be synthesized
(synth-fun div1 ((x Int) (y Int)) Int
    ;; Define the grammar for allowed implementations of max2
    ((I Int) (C Int) (B Bool))

    ;((I Int) (B Bool))
    
    ((I Int (x y
            (+ I I)
            (- I I)
            (* I C)
            (* C I)
            (div I C)
            (mod I C)
            (ite B I I)))
     (C Int (0 1))
     (B Bool (true false
             (and B B)
             (or B B)
             (=> B B)
             (xor B B)
             ;(xnor B B)
             ;(nand B B)
             ;(nor B B)
             ;(iff B B)
             (not B)
             (= B B)
             (<= I I)
             (>= I I)
             (< I I)
             (> I I)
             (= I I))))

    ;((I Int (x 2 1 0
    ;        (div I 2)
    ;        (mod I I)
    ;        (ite B I I)))
    ; (B Bool ((= I I))))
    ;(
    ;    (I Int (x 2 1 0 (div I 2) (mod I I) (ite B I I)) )
    ;    (B Bool ((= I I)))    
    ;)
)

(declare-var x Int)
(declare-var y Int)

;; Define the semantic constraints on the function
(constraint (=> (= ( mod x 2) 1) ( = (div1 x) 0) ))
(constraint (=> (= ( mod x 2) 0) ( = ( + (div1 x) (div1 x)) x) ) )

(check-synth)
