(define thread
  (lambda (input functions)
  (cond
    ((eq (cdr functions) '()) ((car functions) input))
    ((eq '() '()) ((car (cdr functions)) ((car functions) input))))))

(display
  (thread '1 '(atom quote))
  )
