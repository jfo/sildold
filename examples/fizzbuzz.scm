(define fizzbuzz (lambda (x acc)
                (cond
                  ((eq x 101)
                   acc)
                  ((eq (% x 3) 0)
                   (cond
                      ((eq (% x 5) 0)
                      (fizzbuzz (+ x 1) (cons 'fizzbuzz acc)))
                     ((eq 1 1)
                      (fizzbuzz (+ x 1) (cons 'fizz acc)))))
                  ((eq (% x 5) 0)
                   (fizzbuzz (+ x 1) (cons 'buzz acc)))
                  ((eq 1 1)
                   (fizzbuzz (+ x 1) (cons x acc))))))

(display (fizzbuzz 1 '()))
