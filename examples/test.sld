(define null? (lambda (x) (eq x '())))
(define cadr (lambda (x) (car (cdr x))))

(define thing (lambda (x l)
                (cond ((eq x (car l)) (cadr l))
                      ((eq '() '()) (thing x (cdr l))))))

(define else (eq '()'()))
; (debug else)
; (debug else)
; (debug else)
; (debug else)
; (debug else)

; (display
;  (cond
;   (else 1)
;   ((eq '() '()) 2)
;  )
; )

(define member?
  (lambda (a lat)
    (cond
      ((null? lat) '())
      ((eq a (car lat)) (atom '()))
      ((atom '()) (member? a (cdr lat))))))

(define reverser
  (lambda (l acc)
    (cond
      ((null? l) acc)
      ((eq '() '()) (reverser (cdr l) (cons (car l) acc))))))

(display
  (eq '() '())
)

(display
  (eq '(1 2 3 4) (reverser (reverser '(1 2 3 4) '()) '()))
)

(define assoc
  (lambda (k dict)
    (cond
      ((null? dict) '())
      ((eq k (car (car dict))) (cadr (car dict)))
      ((eq '() '()) (assoc k (cdr dict))))))

; (display
;   (assoc 'c '((a 1) (b 2) (c 3)) )
; )
(define mydict '((a 1) (b 2) (c 3)) )

; (display
;   (assoc 'c mydict)
; )

(define thread
 (lambda (input functions)
  (cond
   ((eq (cdr functions) '())
    ((car functions) input))
   ((eq '() '())
    (thread ((car functions) input) (cdr functions))))))

; (display
;   (thread '(1 2 3 4 5 6) '(cdr cdr cdr car))
; )
