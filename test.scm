; (define null? (lambda (x) (eq? x '())))
; (define cadr (lambda (x) (car (cdr x))))
; (define thing (lambda (x l)
;                 (cond ((eq? x (car l)) (cadr l))
;                       ((eq? '() '()) (thing x (cdr l))))))

; (define else (eq? '()'()))
; (define atom atom?)

; (define member?
;   (lambda (a lat)
;     (cond
;       ((null? lat) '())
;       ((eq? a (car lat)) (atom? '()))
;       ((atom? '()) (member? a (cdr lat))))))

; (define reverser
;   (lambda (l acc)
;     (cond
;       ((null? l) acc)
;       ((eq? '() '()) (reverser (cdr l) (cons (car l) acc))))))

; (define assoc
;   (lambda (k dict)
;     (cond
;       ((null? dict) '())
;       ((eq? k (car (car dict))) (cadr (car dict)))
;       ((eq? '() '()) (assoc k (cdr dict))))))

(display
  (- 1 1)
)

; (define mydict '((a 1) (b 2) (c 3)) )
; (display
;   (assoc 'c mydict)
; )
; (display
;   (assoc 'c '((a 1) (b 2) (c 3)) )
; )

