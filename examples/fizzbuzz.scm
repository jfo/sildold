(define fizzbuzz (lambda (x acc)
                (cond
                  ((eq x 100)
                   acc)
                  ((eq (% x 3) 0)
                   (cond
                      ((eq (% x 5) 0)
                      (thing (+ x 1) (cons 'fizzbuzz acc)))
                     ((eq 1 1)
                      (thing (+ x 1) (cons 'fizz acc)))))
                  ((eq (% x 5) 0)
                   (thing (+ x 1) (cons 'buzz acc)))
                  ((eq 1 1)
                   (thing (+ x 1) (cons x acc))))))


(display (fizzbuzz 1 '()))
