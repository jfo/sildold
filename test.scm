(define null? (lambda (x) (eq? x '())))
(define cadr (lambda (x) (car (cdr x))))
(define thing (lambda (x l)
                (cond ((eq? x (car l)) (cadr l))
                      ((eq? '() '()) (thing x (cdr l))))))

(define else (eq? '()'()))
; (define atom atom?)

; (define member?
;   (lambda (a lat)
;     (cond
;       ((null? lat) '())
;       ((eq? a (car lat)) (atom? '()))
;       ((atom? '()) (member? a (cdr lat))))))

(define reverser
  (lambda (l acc)
    (cond
      ((null? l) acc)
      ( (eq? '() '()) (reverser (cdr l) (cons (car l) acc))))))

; (display
;   (reverser '(1 2 3 4 5 6) '())
; )

(display
  ((lambda (a)
     ((lambda (b) b) 'c)) 'd)
)

(display
  ((lambda (a)
     ((lambda (b) a) 'c)) 'd)
)
