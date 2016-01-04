syn match sildMath "[\*|\-|\/|\%|\+]"
syn keyword sildBuiltin eq quote  cond atom car cdr cons
syn keyword sildSpecial display define debug
syn keyword sildLambda lambda
syn match sildComment ";.*$"
syn match sildQuote "\'"
syn match sildInt "[0-9]"

hi def link sildQuote Special
hi def link sildSpecial Special
hi def link sildMath Function
hi def link sildBuiltin Function
hi def link sildComment Comment
hi def link sildInt Number
hi def link sildLambda Operator
