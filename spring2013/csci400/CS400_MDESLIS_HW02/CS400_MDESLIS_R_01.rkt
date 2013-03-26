; AUTHOR: MARIA DESLIS
; csci400 - Bahn - spring2013
; Racket - Homework One
;
; (with help from Brianna Fidder cause I started to get SUPER confused)


; PART I
(define (containsAnywhere el lis) ; the function containsAnywhere takes two parameters, el (referring to an element) and lis (referring to a list)
  (cond ((null? lis) false) ; if there is no  list, return false on default otherwise continue
        (
         (list? (car lis)) ; is the first element in a list a list itself?
         (or (containsAnywhere el (car lis)) (containsAnywhere el (cdr lis))) ; if it is, compare the values inside of that to the original element given, if the first one is false move on the next
        )
        (else (if(eq? el (car lis)) true (containsAnywhere el (cdr lis)))) ; else if the element in the list is not a list itself, compare the elements
        )
  )

(define (unitTest)
  (and 
   (containsAnywhere 'a '(a))
   (containsAnywhere 'a '(b a))
   (not (containsAnywhere 'a '(c d)))
   (containsAnywhere 'a '((a) b))
   (containsAnywhere 'b '((c d e) (g b e)))
   (containsAnywhere 'b '((c d e) (g (b) e)))
   (not (containsAnywhere 'x '((c d e) (g (b) e))))
   (containsAnywhere 'f '((c d e) (g (b) e) f))
   (not (containsAnywhere 'h '((c d e) (g (b) e) f)))
  ))

; PART II
(define (removeAll el lis)
  (cond ((null? lis) '()) ; if there are no lists to begin with, return an empty list
    (
     (list? (car lis)) ; is the first element in a list a list itself?
     (cons (removeAll el (car lis)) (removeAll el (cdr lis))) ; if it is, evaluate the first list and then concatonate it to the rest while ignoring the original element
     )
    (
     (eq? el (car lis)
    ) 
     (removeAll el (cdr lis)); if the element in the list matches the original element, evaluate everything else and concatonate them together
    )
    (else (cons (car lis) (removeAll el (cdr lis)))) ; if it's not the first element and it is not a list, concatonate with the rest of the evaluations
    )
  )

(define (unitTest2)
  (and 
   (equal? (removeAll 'a '(b a c)) '(b c))
   (equal? (removeAll 'a '((b a c d))) '((b c d)))
   (equal? (removeAll 'b '((b a c d (f)))) '((a c d (f))))
   (equal? (removeAll 'b '((b a c d (f b)))) '((a c d (f))))
   (equal? (removeAll 'b '((b a c d (f (b))))) '((a c d (f ()))))
   (equal? (removeAll 'b '((b a c d (f (b g))))) '((a c d (f (g)))))
   ))


; PART III
(define (calculator)
  (display "CALCULATE: Inches/Centimeters? Pounds/Kilograms?\n") ; letting the user know what conversions are available
  (display "Remember that spelling is important \n")
  (let ((a (getUnit1)) ; grabbing the unit to be converted
        (b (getUnit2)) ; grabbing the unit to be converted TO
        (value (getConvert)); grabbing the value 
       ) 
   (
    (eval (string->symbol(string-append a "To" b))) value)
   )
) ;string-> returns the string whose name is the a appended to To appended to b and feeds in the value to the functions

(define (getUnit1)
  (display "Original unit: ")(read-line))

(define (getUnit2)
  (display "New unit: ")(read-line))

(define (getConvert)
  (display "Value to convert: ")(read))

; inches & centimeters conversions
(define (inchesTocentimeters el)
  (display (* el 2.5))(display " centimeters"))

(define (centimetersToinches el)
  (display (/ el 2.5))(display " inches"))

; pounds & kilgorams conversions
(define (poundsTokilograms el)
  (display (/ el 2.20462))(display " kilograms"))

(define (kilogramsTopounds el)
  (display (* el 2.20462))(display " pounds"))

; Making it easier to read/deal with
(display "Results for containsAnywhere: ")
(unitTest)
(display "\nResults for removeAll: ")
(unitTest2)
(display "\n")
(display "Please type (calculator) to start the calulator")