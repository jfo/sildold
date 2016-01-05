; (display
;    (car (cdr '(this that))))
; )

(define twice
 (lambda (x func)
  (func (func x))))

(define square
  (lambda (x) (* x x))
)

(display (square 2))
(display (twice 2 square))
