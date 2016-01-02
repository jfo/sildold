(define ->
  (lambda (input functions)
  (cond
    ((eq (cdr functions) '()) ((car functions) input))
    ((eq '() '()) ((car (cdr functions)) ((car functions) input))))))

(display
  (-> '(1 2 3) '(
                     car
                     quote
                     quote
                     )))
