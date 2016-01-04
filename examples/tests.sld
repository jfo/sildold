; (display (atom)) ; should throw an arity error
; (display (atom 1))
; (display (atom '1))
; (display (atom '()))
; (display (atom '(1)))
; (display (atom atom)) ; this is wrong
; (display (atom '1 '1)) ; this should throw an arity error

; (display (eq)) ; this crashes?
; (display (eq 1))
; (display (eq '1 '1))
; (display (eq '1 '1))
; (display (eq '1 '2))
; (display (eq '1 '()))
; (display (eq '() '()))
; (display (eq '(1) '(1)))
; (display (eq '(1) '(1 2)))
; (display (eq '(1) '(1) '1))
;

; (display (cond))
; (display (cond
;            ((eq '() '()))))
; (display (cond
;            ((eq '() '()) '1)))

; (display (cond
;            ((eq '(1) '()) '1)
;            ((eq '() '()) '2)))
;
; (display (cond
;            ((eq '(1) '()) )
;            ((eq '() '()) 2)))

; (display (cons )) ; breaks, should throw arity error
; (display (cons '1)) ; breaks, should throw arity error
; (display (cons '1 '1)) ; returns list with 1 in it? should throw error, scheme returns cell (1 . 1)
; (display (cons '1 '(2)))
; (display (cons '(1) '(2)))
; (display (cons '1 '()))
; (display (cons '1 '2 '())) ; should throw arity error
; (display (cons '1 '2 '(3))) ; should throw arity error

; (display (car)) ; returns NIL should throw error
; (display (car '1)) ; returns NIL should throw error
; (display (car '(1)))
; (display (car '())) ; returns NIL should throw error
; (display (car '(2 3)))

; (display (cdr )) ; returns NIL should throw error
; (display (cdr '2)) ; returns NIL should throw error
; (display (cdr '(2 3)))
(display (cdr '(2 3) '1)) ; returns NIL should throw error

; (display (quote '1))
; (display (quote 1))
; (display (quote)) ; fix error message
; (display (quote))
; (display (quote '1 '2))

(display ((lambda (x) (x)) 10))
; (display ((lambda (x) x) '1))

