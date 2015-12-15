(define null? (lambda (x) (eq? x '())))
(define cadr (lambda (x) (car (cdr x))))

(define thing (lambda (x l)
                (cond ((eq? x (car l)) (cadr l))
                      ((eq? '() '()) (thing x (cdr l))))))
(display
  (thing '2 '(1 2 3))
)

