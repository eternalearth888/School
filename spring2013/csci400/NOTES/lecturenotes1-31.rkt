;;;<class notes>

;review from last racket lecture: if statements
;if statement syntax:
;   (if (predicate) ifTrue ifFalse)
; predicate: what to evaluate
; ifTrue: what to return if it is true
; ifFalse: what to return if it is false

;new notes
;a cond is a more flexible switch statement and has the syntax of
; (cond (c1) ... (cn) [else (what to return if all conditions fail)])
; c1 throuch cn are conditions which have 2 parts.  The syntax for a condition is:
; ((condition to evaluate) (what to return if the condition is true))


;;;</class notes>

;an example of a simple condition statement
;(define a 5)
;(cond ((< a 20) (display "Less than 20")) ((= a 5) (display "equal to 5")) [else (display "Something else")])
;this will print to screen "less than 20" because conditions are evaluated in the order they are given

;an example of creating a function for a condition statement
(define a 5);creates an int a=5

;creates the function bob which takes a parameter used in a lambda function
(define bob 
             (lambda (a) 
               (cond ((< a 20) (display "Less than 20\n")) ((= a 5) (display "equal to 5\n")) [else (display "Something else\n")])
               )
  )
(bob 27);example case of using function bob, it prints "something else"  

;creates the function sue which takes parameter a and will not use a lambda function because a is one of the arguments for the function
(define (sue a) 
  (cond ((= a 5) (display "equal to 5\n")) ((< a 20) (display "Less than 20\n")) [else (display "Something else\n")])
  )
(sue 5);example case of using the function sue, it prints "equal to 5"

;If you dont know what the towers of hanoi problem is, just google it super quick
;defines a function that will tell us how many moves it will take to complete the towers of hanoi problem
;the number of moves for n disks can be thought of as
;    f(n) = 1 + 2*f(n-2)
;note that there is no need for a lambda function because n(the number of disks) is an argument for the function
(define (hanoi-moves n) 
  (if 
   (= n 0) ;condiditon to evaluate i.e if there are no more disks to move
   0 ;if n == 0 return 0
   ;else if n != 0 
   (+ 1 (* 2 (hanoi-moves(- n 1))));evaluate f(n-1) then multiply by 2 then add 1
   )
  )

;;;test cases we used were n=8 and n=9
(hanoi-moves 8);should return 255
(hanoi-moves 9);should return 511

;;;Final remarks and observations
;although 'a' is defined prior to bob and sue, bob and sue will use the 'a' passed to its function becuase of scope