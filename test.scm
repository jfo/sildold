(define null? (lambda (x) (eq? x '())))

(display
  (cond
         ((null? '(x)) '4)
         ((null? '(s)) '3)
))

