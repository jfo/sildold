(define thing (lambda (x acc)
                (cond
                  ((eq x 10) acc)
                  ((eq 1 1) (thing (+ x 1)  (cons x acc))))))


(display (thing 0 '()))
