(define name "William L. Bahn")
(define user "wbahn")

; Lexical Environments and Closures

; THIS IS TO BE AN INDIVIDUAL EFFORT!

; You may discuss the concepts with your classmates (or come see me).
; You may post questions on Piazza.
; But the answers you submit should be ones that you write without
; referencing ANY material resulting from discussions with your classmates.
; In other words, it's the 'open hands' policy.

; Please don't push this and try to play games. Whatever you turn in will
; be taken as a reflection of YOUR level of understanding of this material.
; If subsequent work shows that your actual level of understanding falls
; considerably short of what you turn in here, things will not be pleasant.

; BASIC INSTRUCTIONS

; 1) Replace my name and username with your own.
; 2) Save the file using the format "CS400_UserID_HW_06_Part_1.rkt".
; 3) Run the file.
; 4) Read the contents and do what is asked for each problem.

(display "=============================\n")
(display (string-append "NAME: " name "\n"))
(display (string-append "FILE: CS400_" user "_HW_06_Part_1.rkt\n"))
(display "=============================\n")

;==========================================================================
(display "\nLEXICAL SCOPE\n")
;==========================================================================

;--------------------------------------------------------------------------
; let vs let*
;--------------------------------------------------------------------------

; I's important to understand the difference between 'let' and 'let*'. 
; Both are of the form:

; ( let|let* list-of-locals body)

; where 'list-of-locals' is of the form:

; ( (id_1 val_1) (id_2 val_2) ... )

; Keep in mind that 'val_1' can be any expression, including an expression
; the returns a function, in which case id_1 is a function.

; With the 'let' statement, all of the val_* expressions are evaluated in
; the lexical environment containing the 'let' statement. The new 
; identifiers are not visible except in the body. 

; With the 'let*' statement, the only thing that changes is that the 
; lexical environment for each expression includes the new identifiers that
; precede it in the list. 

; In actuality, the 'let*' statement is merely a shorthand for a sequence
; of nested 'let' statements, as illustrated below:

(define (let_ex x)
   (let* ((z 5) (y 20) (fn (lambda (x) (* x y z))) )
         (let ((y 10))
              (fn y)
         )
   )
) 

(define (let*_ex x)
   (let ((z 5))
      (let ((y 20))
         (let ((fn (lambda (x) (* x y z))) )
           (let ((y 10))
              (fn y)
           )
         )
      )
   )
)

(define (ut_let/let*)
  (and (let [(a 10)] (eq? (let_ex a) (let*_ex a)))
       (let [(a  0)] (eq? (let_ex a) (let*_ex a)))
       (let [(a 99)] (eq? (let_ex a) (let*_ex a)))
       (let [(a -1)] (eq? (let_ex a) (let*_ex a)))
       (let [(a 15)] (eq? (let_ex a) (let*_ex a)))
       (let [(a  1)] (eq? (let_ex a) (let*_ex a)))
  )
)

(display "Unit test on let/let*:....... ")
(display (ut_let/let*))
(display "\n")

; To see this from a different perspective, consider the following:

(define apple 3)
(define (let/let*)
  (display "Using 'let':................. ")
  (display (let [(pear 5) (apple 7) (grape (* 11 apple))] 
                (* apple pear grape)
           )
  )
  (display "\n")
  (display "Using 'let*':................ ")
  (display (let* [(pear 5) (apple 7) (grape (* 11 apple))] 
                 (* apple pear grape)
           )
  )
  (display "\n")
)

(let/let*)

;--------------------------------------------------------------------------
; LEXICAL SCOPE
;--------------------------------------------------------------------------

; It is important to keep in mind that, at least for the parts of the 
; language we have studied, identifiers only get created in one of three
; ways: With a 'define' statement, as a parameter in a function definition,
; or as a definition in a let/let* statement.

; Each time a new set of parameters is defined, it creates a nested level
; of the 'lexical environment' in which it sits. If the new environment
; creates any identifiers with the same name as a higher level, then the
; code at the new level (and any subsequent lower levels) can no longer 
; see the higher-level identifiers, only the new ones.

; The lexical environment for any given peice of code consists of any
; identifiers in the nested environemtns in which it sits, all the way to
; the top (global) level, with the caveat that if a given identifier is
; defined at multiple levels, it can only see the one that is at the lowest
; level above it.

; With this in mind, let's look at one of the problems from Quiz #1

(define (cl x)
   (let* ((z 5) (y 20) (fn (lambda (x) (* x y z))) )
         (let ((y 10))
              (fn y)
         )
   )
)

(display "Running (cl 4):.............. ")
(display (cl 4))
(display "\n")

; As you can see when you run this, the output is 1000. Why?

; Let's identify the nested levels of the lexical environment:

; LE0 - Global Level

(define (cl_2 x) ; LE1 - The x masks any x from any higher level.
   ; Note that the cl_2 (the item being defined) is part of the next higher 
   ; lexical environment (LE0, in this case), meaning that code at LE0 can
   ; see it.
   (let* ( ; A let* is shorthand for a nested series of let statements, each
           ; one adding one more level of depth to the lexical environment.
           (z 5)  ; LE2 - The z masks any z from a higher level.
           (y 20) ; LE3 - The y masks any y from a higher level.
           (fn ; LE4 - The fn masks any fn from a higher level. 
             (lambda (x) ; LE5 - The x masks any x from a higher level,
                         ; including the one at LE1.
               (* x y z))) 
         )
         ; This is the body for the let* and is at LE5
         (let (
                (y 10) ; LE6 - The y masks any y from a higher level.
               )
              ; This is the body for the let and is at LE6
              (fn y) 
         )
   )
)

(display "Running (cl_2 4):............ ")
(display (cl_2 4))
(display "\n")

; So notice that we have the following identifier name collisions:

; x {LE1, LE5}
; y {LE3, LE6}

; While the rules for lexical scoping resolve these collisions as described
; above, it is helpful for humans to resolve them in a more direct and 
; visible way. So let's simply append them with the level of their 
; lexical environment. This results in the following modified code:

(define (cl_3 x1)
   (let* ((z 5) (y3 20) (fn (lambda (x5) (* x5 y3 z))) )
         (let ((y6 10))
              (fn y6)
         )
   )
)

(display "Running (cl_3 4):............ ")
(display (cl_3 4))
(display "\n")

; Notice how, with things renamed this way, the code is much more easily
; understood by us humans. It is obvious that the input argument is never
; used and that the lambda function is working with whatever value is 
; eventually passed into it (x5) and with the values 5 and 20 for z and y.
; It is also clear that y6 has no effect on the internals of the lambda
; function and that it is the value that is passed into the lambda function
; (which is known by the identifier 'fn' at LE4 and below).

(define (ut_cl_3)
  (and (let [(a 10)] (eq? (cl a) (cl_3 a)))
       (let [(a  0)] (eq? (cl a) (cl_3 a)))
       (let [(a 99)] (eq? (cl a) (cl_3 a)))
       (let [(a -1)] (eq? (cl a) (cl_3 a)))
       (let [(a 15)] (eq? (cl a) (cl_3 a)))
       (let [(a  1)] (eq? (cl a) (cl_3 a)))
  )
)

(display "Unit test on cl_3:........... ")
(display (ut_cl_3))
(display "\n")

; It is important to realize that, while 'cl_1' and 'cl_3' look very 
; different to us, they are identical pieces of code as far as the actual 
; executable code that a compiler would produce.

;==========================================================================
(display "\n\nPROBLEM #1\n")
;==========================================================================

; The next thing that is important to realize is that when we say that a
; closure captures the variables in its lexical scope, we really mean it;
; the variables, and not their values at a partcular moment in time, are
; captured. If we change the values of those variables in the future, we
; also change the values used by the function in the closure.

; In the following code, set! is being used to force changes in variables.
; This is being done because it is about the only way to demonstrate that
; it is the variables, and not their values, that are captured. 

(define (cl_4 x y z)
  (let* [(y 7) (fn (lambda (x) (+ x y z)))] 
    (let [(z 1)]
      (set! y 5)
      (set! z 3)
      (fn z)
    )
  )
)

(display "Running (cl_4 10 20 30):..... ")
(display (cl_4 10 20 30))
(display "\n")

; Identify the lexical environments within the code for 'cl_4' and rewrite
; the code, as 'cl_5' below (a placeholder return value is there so that 
; the test code will run - replace the placeholder code with yours). Your
; code should contain NO identifier name collisions.

;**************************************************************************
;**************************************************************************
(define (cl_5 x y z) 
  ; PUT YOUR CODE HERE (and delete the 42)
  42
)
;**************************************************************************
;**************************************************************************

(define (ut_cl_5)
  (and (let [(a 10) (b 20) (c 30)] (eq? (cl_4 a b c) (cl_5 a b c)))
       (let [(a  0) (b  0) (c  0)] (eq? (cl_4 a b c) (cl_5 a b c)))
       (let [(a  1) (b  2) (c  3)] (eq? (cl_4 a b c) (cl_5 a b c)))
       (let [(a -1) (b -1) (c -1)] (eq? (cl_4 a b c) (cl_5 a b c)))
       (let [(a 99) (b 99) (c 99)] (eq? (cl_4 a b c) (cl_5 a b c)))
       (let [(a -9) (b 50) (c  0)] (eq? (cl_4 a b c) (cl_5 a b c)))
  )
)

(display "Running (cl_5 10 20 30):..... ")
(display (cl_5 10 20 30))
(display "\n")
(display "Unit test on cl_5:........... ")
(display (ut_cl_5))
(display "\n")

;==========================================================================
(display "\n\nPROBLEM #2\n")
;==========================================================================

; The function below is nearly identical to the one presented in class. It
; has only been tweaked to keep the values produced more manageable for
; hand computations.

; The 'jj' function creates a pair of functions, 'jack' and 'jill', that
; then each called twice. This process is performed twice, with a new call
; to 'fnlst' each time to get fresh functions. The ONLY difference between
; the two sequences is that the final pair of statements in each sequence
; are swapped.

; PART (a)
; Show that you understand the lexical scope of each of the identifies in
; the code by rewriting jack and jill using only global variables. Note
; that this is the same as ensuring that there are no identifier name 
; collisions, except that you are having to deconflict names between more
; than one function. Do this in the space provided below. Some placeholder
; code is already present. Note that the parameters passed to jack and jill
; are not global (though you could do it that way if you want).

; PART (b)
; Then, show the operations performed in the call to 'jj' in the example
; execution below. You can use a table such as the one below, if you would
; like: (a, b, c, d) -- perhaps more -- represent your global variables.
; The 'returns' column is the value returned by that call and this column
; should contain values that match the example you see when you run 'jj'.

; CALL   a    b    c    d    returns
; jack
; jill
; jack
; jill

; CALL   a    b    c    d    returns
; jack
; jill
; jill
; jack

; Note that you do not need to show the actual computations. It is 
; sufficient to show the final value of all of the global variables
; after each call to either jack or jill.

(define (fnlst c) 
  (let ((a 3) (b 5))
      (list (lambda (x) (set! a (+ a b c)) (+ a b c x)) 
            (lambda (x) (set! b (- a b c)) (+ a b c x))
      )
  )
)

(define (jj x y)
  (let [(fns (fnlst x))]
       (let [(jack (car fns)) (jill (cadr fns))]
          (display "jack-jill-jack-jill\n")
          (display "jack: ") (display (jack y)) (display "\n")
          (display "jill: ") (display (jill y)) (display "\n")
          (display "jack: ") (display (jack y)) (display "\n")
          (display "jill: ") (display (jill y)) (display "\n")
       )
  )
  (let [(fns (fnlst x))]
       (let [(jack (car fns)) (jill (cadr fns))]
          (display "jack-jill-jill-jack\n")
          (display "jack: ") (display (jack 2)) (display "\n")
          (display "jill: ") (display (jill 2)) (display "\n")
          (display "jill: ") (display (jill 2)) (display "\n")
          (display "jack: ") (display (jack 2)) (display "\n")
       )
  )
)

(jj 3 2)

;**************************************************************************
;**************************************************************************

; PART (a)
; Define your global variables and your jack and jill functions below.
; then write a function called 'jj1' that calls these functions to produce
; the same set of results as 'jj'. Note that the 'a' and 'b' below are not
; necessariy the same 'a' and 'b' in the 'fnlst'. They are just example
; identifiers. You can use them (or not).

(define a 1)
(define b 1)
(define (jack x) 42)
(define (jill x) 39)

         
; PART (b)
; Put your computations here. Be sure to make them comments so that the
; file you submit will run.

; CALL   a    b    c    d    returns
; jack
; jill
; jack
; jill

; CALL   a    b    c    d    returns
; jack
; jill
; jill
; jack

;**************************************************************************
;**************************************************************************


;==========================================================================
(display "\n\nPROBLEM #3\n")
;==========================================================================

; This is the basically same code as discussed in class. Do the same things
; as in Problem #2 above, namely write the four functions (jack, jill, adam 
; and abby) using all global variables and then make a table that walks
; through the changes in these variables resulting from each call to any of
; them. 

(define (jjaa x y)
  (let ((fns (list (fnlst x) (fnlst x))))
    (let ((jack (car  (car fns))) 
          (jill (cadr (car fns)))
          (adam (car  (cadr fns))) 
          (abby (cadr (cadr fns)))                       
         )
      (begin
        (display "adam: ") (display (adam y)) (display "\n")
        (display "abby: ") (display (abby y)) (display "\n")
        (display "adam: ") (display (adam y)) (display "\n")
        (display "abby: ") (display (abby y)) (display "\n")
        (display "jack: ") (display (jack y)) (display "\n")
        (display "jill: ") (display (jill y)) (display "\n")
        (display "adam: ") (display (adam y)) (display "\n")
        (display "abby: ") (display (abby y)) (display "\n")
        (display "jack: ") (display (jack y)) (display "\n")
        (display "jill: ") (display (jill y)) (display "\n")
        (display "adam: ") (display (adam y)) (display "\n")
        (display "abby: ") (display (abby y)) (display "\n")
        (display "jack: ") (display (jack y)) (display "\n")
        (display "jill: ") (display (jill y)) (display "\n")
      )
    )
  )
)

(jjaa 7 2)

;**************************************************************************
;**************************************************************************

; PART (a)
; Define your global variables and your jack and jill functions below.
; then write a function called 'aajj1' that calls these functions to produce
; the same set of results as 'aajj'. Note that the 'a' and 'b' below are not
; necessariy the same 'a' and 'b' in the 'fnlst'. They are just example
; identifiers. You can use them (or not).

(define a 1)
(define b 1)
(define (jack w) 17)
(define (jill x) 13)
(define (adam y) 42)
(define (abby z) 39)

         
; PART (b)
; Put your computations here. Be sure to make them comments so that the
; file you submit will run.

; CALL   a    b    c    d    returns
; adam
; abby
; adam
; abby
; jack
; jill
; adam
; abby
; jack
; jill
; adam
; abby
; jack
; jill

;**************************************************************************
;**************************************************************************

;==========================================================================
