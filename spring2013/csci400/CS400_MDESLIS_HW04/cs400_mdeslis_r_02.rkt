; AUTHOR: MARIA DESLIS
; csci400 - Bahn - spring2013
; Racket - Homework FOUR
; done with Drew Koelling :-)

; for testing
(require racket/trace)
; for allowing make-list to work
(require racket/list)


; first thing to see in game
; player is allowed to choose which game of NIM they want to play
; if they do not choose a valid choice they will be prompted to choose again
(define (mainMenu)
  (display "WELCOME TO NIM!\n")
  (display "1. Human vs Human\n")
  (display "2. Human vs Random\n")
  (display "3. Human vs Smart\n")
  (display "Please choose what game to play by typing the number:\n")
  (define game (read))
  (if (or(negative? (- 3 game)) (zero? game) (negative? game))
      (begin (display "Game does not exist. Choose again!\n") (mainMenu))
       game
  )
)

; begin Nim
; call the menu
(define (startGame board)
  (define counter 1)
  (play board counter (mainMenu))
)

; play in our world, live in yours
; reads the choice from the menu to ensure it does the correct game
; display the current board
; call the counter and update it
; if the board is empty determine the winner and call game over
; otehrwise, continue the game
(define (play board counter choice)
  (cond
    ; if the player chooses human vs human, this will occur
    [(equals? choice 1)  
     (readRow board)
     (currentTurn counter)
     (if (win board counter choice)
        (display "\nGAME OVER\n")
        (play (chooseRow board) (+ counter 1) choice) 
     )
    ]
    ; if the player chooses human vs random, this will occur
    [(equals? choice 2)
     (readRow board)
     (currentTurn counter)
     (if (win board counter choice)
         (display "\nGAME OVER\n")
         (if (equals? (modulo counter 2) 0)
             (play (randomChoice board) (+ 1 counter) choice)
             (play (chooseRow board) (+ 1 counter) choice)
             )
         )
     
    ]
    ; if the player chooses human vs smart, this will occur
    [(equals? choice 3)
    ; (readRow board)
    ; (currentTurn counter)
    ; (if (win board counter choice)
    ;     (display "\nGAME OVER\n")
    ;     (if (equals? (modulo counter 2) 0)
    ;         (play (smartChoice board) (+ 1 counter) choice)
    ;         (play (chooseRow board) (+ 1 counter) choice)
    ;         )
    ;     )
     (display "Sorry, tried but decided life was worth living. See bottom of code for good faith effor :( .")
    ]
    ; THIS SHOULD NEVER OCCUR, but if it does, that means I have serious debugging to do
    [else
     (display "FALSE")
    ]
   )
)

; Calculates current
; if current is even, then the current player is player2
; if current is odd, then the current player is player1
(define (currentTurn current)
  (if (equals? (modulo current 2) 0)
      (display "Player 2 Turn\n ")
      (display "Player 1 Turn\n ")
   )
 )
    
; Check to see if the board is empty
; is the entire board already empty then it will be true in the play functon and the game over 
(define (emptyBoard board)
  (if (empty? board)
      #t
      (if (empty? (first board))
          (emptyBoard (rest board))
          #f
      )
     )
  )
           

; take the current value of counter
; if the board is empty
; check if the modulos of counter with 2 is 0 (even) then Player 1 wins
; otherwise Player 2 wins
; otherwise, win is not possible and you must continue the game
(define (win board counter choice)
  (if (emptyBoard board)    
      (if (equals? (modulo counter 2) 0)
          (display "\n\nPLAYER 1 WINS!!")
          (display "\n\nPLAYER 2 WINS!!")
      )
      #f
  )
)

; our board for NIM :-)
(define board1 
  '((X) (X X X) (X X X X X) (X X X X X X X))
  )

; print the board to the screen row by row
(define (readRow board)
  (display "\nRow 1: ")
  (display (first board))
  (display "\nRow 2: ")
  (display (second board))
  (display "\nRow 3: ")
  (display (third board))
  (display "\nRow 4: ")
  (display (fourth board))
  (display "\n")
  )

; prompt the current user for their row choice
; then call validRow to make sure that their row choice is valid
(define (chooseRow board)
  (display "Which row do you choose: ")
  (validRow (read) board)
  )

; if the row value - 4 is a negative number
; tell the user that their choice was invalid move and prompt for chooseRow to start over
; otherwise call numSticks and pass in the row choice with it
; basically, if that row is on the board, the user has made a valid row
(define (validRow rowChoice board)
  (if (negative? (- 4 rowChoice)) 
      (begin (invalidMove) (chooseRow board)) 
      (numSticks rowChoice board)
      )
  )

; prompt the user for the number of sticks they want to use from their current row
; take the row choice and the number of sticks and board and call validSticks
(define (numSticks rowChoice board)
  (display "How many sticks: ") 
  (validSticks (read) rowChoice board)
  )

; a function to tell the player that the current move they are doing is invalid
; it was easier to type the function name instead of repeating the same sentence over and over
(define (invalidMove)
  (display "\nINVALID MOVE - TRY AGAIN\n")
)

; Check to see that the number of sticks
; first, check to see if the choice is a 0 or negative number
; if it is, tell them it is invalid and prompt them to start over with choosing a row
; if the choice is neither 0 or negative
; take the current length of the row and subtract it from the choice value
; if that difference is negative, tell them it is an invalid choice and prompt them to start over with choosing a row
; otherwise call removeSticks
(define (validSticks stickChoice rowChoice board )
  (if (or (zero? stickChoice) (negative? stickChoice))
      (begin (invalidMove) (chooseRow board))
      (cond
        [(equal? 1 rowChoice) 
         (if (negative? (- (length (first board)) stickChoice))
             (begin (invalidMove) (chooseRow board))
             (removeSticks stickChoice rowChoice board)
             )
         ]
        [(equal? 2 rowChoice) 
         (if (negative? (- (length (second board)) stickChoice))
             (begin (invalidMove) (chooseRow board))
             (removeSticks stickChoice rowChoice board)
             )
         ]
        [(equal? 3 rowChoice) 
         (if (negative? (- (length (third board)) stickChoice))
             (begin (invalidMove) (chooseRow board))
             (removeSticks stickChoice rowChoice board)
             )
         ]
        [(equal? 4 rowChoice) 
         (if (negative? (- (length (fourth board)) stickChoice))
             (begin (invalidMove) (chooseRow board))
             (removeSticks stickChoice rowChoice board)
             )
         ]
        ; SHOULD NEVER GET HERE, if it does, we have serious debugging to do
        [else
         (begin (display "What you talkin' 'bout?") (chooseRow))
         ]
        )
      )
  )

; this function will be called under the assumption that the isValid function passed with a non-negative/non-zero value for number of sticks to be removed
; if the row choice is one
; make a new list of X where the number of X is equal to the difference of the length of the row and number of sticks to be removed
; then append the rest of the rows
; otherwise append the first row
; recurse removeSticks, decrement rowChoice until our rowChoice is equal to 1, append all previous rows
; then a new list of X where the number of X is equal to the difference of the length of the row and number of sticks to be removed
; append the rest of the rows, if there are any
(define (removeSticks stickChoice rowChoice board)
  (if (equal? 1 rowChoice)
      (cons 
       (make-list (- (length (first board)) stickChoice) 'X) 
       (rest board)
       )
      (cons 
        (first board) (removeSticks stickChoice (- rowChoice 1) (rest board)) 
       )
     )
 )
        
; RANDOM PLAYER BS

; All the random choices for the player that thinks randomly does
(define (randomChoice board)
  ; choose a row between 1 and 4
  (define randomRow (+ 1 (random 4)))
  
  ; choose number of sticks to be removed from the row you chose above
  ; since the biggest possible number of X's we can remove from a row is 7, the number of sticks to be removed will always be between 1 and 7
  ; call randomValid to make sure that the number of sticks to be removed from that row is possible
  ; if it is, call removeSticks
  ; otherwise, start randomChoice over
  (define randomSticks (+ 1 (random 7)))
  (if (randomValid randomRow randomSticks board)
      (removeSticks randomSticks randomRow board)
      (randomChoice board)
  )
)


; randomValid will take the row that was chosen in randomChoice and the number of sticks chosen in randomRow
; it will first make sure that value of sticks is neither zero or negative, if it is it will tell randomChoice it was a false value
; if the value of sticks is valid
; it will find the row that was chosen in randomChoice
; it will then find the difference between the current length of that row and value of sticks
; if it is negative, it will then be invalid and randomValid will tell randomChoice that the number of sticks to be removed is false, and thus invalid
; else it will be true
(define (randomValid randomRow randomSticks board)
  (if (or (zero? randomSticks) (negative? randomSticks))
      #f
      (cond
        [(equal? 1 randomRow) 
         (if (negative? (- (length (first board)) randomSticks))
             #f
             #t
             )
         ]
        [(equal? 2 randomRow) 
         (if (negative? (- (length (second board)) randomSticks))
             #f
             #t
             )
         ]
        [(equal? 3 randomRow) 
         (if (negative? (- (length (third board)) randomSticks))
             #f
             #t
             )
         ]
        [(equal? 4 randomRow) 
         (if (negative? (- (length (fourth board)) randomSticks))
             #f
             #t
             )
         ]
        ; SHOULD NEVER GET HERE, if it is, we have serious debugging to do
        [else
         (begin (display "What you talkin' 'bout?") #f)
         ]
        )
      )
 )


; SMART PLAYER BS

; HOW SMART PLAYER SHOULD WORK:
; Take all the rows contents and write them out in binary
; Then go through each column (add each column mod 2) and take the parity -- if there is an even number of 1's, the parity is 0, otherwise it is 1 (bitwise-xor)
; The winning state is all zeros, and the computer will have that as the default value
; The computer will then attempt to make it's winning state as close to all zeros as possible per move
; Thus the computer will almost always win


(define (smartParity board)
  (bitwise-xor (length (first board)) (length (second board)) (length (third board)) (length (fourth board)))
)

(define(smartChoice board)
  ; choose a row between 1 and 4
  (define smartRow (+ 1 (bitwise-xor 4)))
  
  (define smartSticks (+ 1 (bitewise-xor 7)))
  (if (smartValid smartRow smartSticks board)
      (smartSticks smartSticks smartRow board)
      (smartChoice board)
  )
)          


(define (smartValid smartRow smartSticks board)
  (if (or (zero? smartSticks) (negative? randomSticks))
      #f
      (cond
        [(equal? 1 smartRow) 
         (if (negative? (- (length (first board)) smartSticks))
             #f
             #t
             )
         ]
        [(equal? 2 smartRow) 
         (if (negative? (- (length (second board)) smartSticks))
             #f
             #t
             )
         ]
        [(equal? 3 smartRow) 
         (if (negative? (- (length (third board)) smartSticks))
             #f
             #t
             )
         ]
        [(equal? 4 smartRow) 
         (if (negative? (- (length (fourth board)) smartSticks))
             #f
             #t
             )
         ]
        ; SHOULD NEVER GET HERE, if it is, we have serious debugging to do
        [else
         (begin (display "NOOOOOOOOOOOOOOO") #f)
         ]
        )
      )
 )

; these traces were done while debugging to see what was happening in the specific function and where it was messing up
; very valuable!
;(trace chooseRow)
;(trace play)
;(trace randomChoice)

;start NIM!
(startGame board1)
      
      
      
     