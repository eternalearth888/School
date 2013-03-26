; Aakash showed me that this was much more efficient and easier than using Swindle
#lang racket

; Maria Deslis
; Bahn - csci400 - spring2013
; hw06_part2

; verbally collaborated with Aakash Shah, Drew Koelling, and Anastasia Shpurik

(define articles '(
     ((Test-Driven Learning: Intrinsic Integration of Testing into the CS/SE Curriculum)
      ((David Jansen)(Hossein Saiedian))
      ("Test-driven learning" "test-driven development" "extreme programming" "pedagogy" "CS1"))
     ((Process Improvement of Peer Code Review and Behavior Analysis of its Participants)
      ((WANG Yan-qing) (LI Yi-jun) (Michael Collins) (LIU Pei-jie))
      ("peer code review" "behavior analysis" "software quality assurance" 
        "computer science education" "software engineering"))
     ((Computer Games as Motivation for Design Patterns)
      ((Paul V. Gestwicki))
      ("Design Patterns" "Games" "Pedagogy" "Java"))
     ((Killer "Killer Examples" for Design Patterns)
      ((Carl Alphonce) (Michael Caspersen) (Adrienne Decker))
      ("Object-orientation" "Design Patterns"))
     ((Test-First Java Concurrency for the Classroom)
      ((Mathias Ricken)(Robert Cartwright))
      ("CS education" "Java" "JUnit" "unit testing" "concurrent programming"
       "tools" "software engineering"))
     ((Teaching Design Patterns in CS1: a Closed Laboratory Sequence
                based on the Game of Life)
      ((Michael Wick))
      ("Design Patterns" "Game of Life" "CS1" "Laboratory"))
   ))

; STEP 1

(define (getTitle title)
  (first title)
)

(define (getAuthors author)
  (second author)
)

(define (getKeywords keyword)
 (third keyword)
)

(display "STEP 1\n")
(display "(getTitle (car articles))\n")
(getTitle (car articles))
(display "(getAuthors (car articles))\n")
(getAuthors (car articles))
(display "(getKeywords (car articles))\n")
(getKeywords (car articles))


; STEP 2
; main function
; takes in the keyword and the articles
; map takes in a procedure(getTitle) and a list(articles)
; getTitle gives you the title associated with each article associated with the result set
; which comes from the reduction function
(define (keywordSearch kword articles)
  (map getTitle (reduction (applySearch kword) articles))
  )

; Here we are adding an initial value in a list to the next value
; in the list until we have reached the end
; It will then return the final product
; ex: (foldl 0 + '(1 2 3)) returns 6
(define (reduction applySearch articles)
  (foldl applySearch '() articles)
 )

; applySearch creates a curried procedure
; captures the argument keyword with the function call as well
; so we can apply the argument to the function later
; so for everyother call, we use the keyword that has been saved
(define (applySearch kword)
  (curry search kword)
  )

; we are checking to see that the keyword that is passed in
; is a member ANYWHERE in getKeywords of the current article
; if there is a match anywhere, we add the current article to matchResult
; otherwise, we simply return matchResult
(define (search kword current matchResult)
  (if
   (member kword (getKeywords current))
      (list* current matchResult)
      matchResult
      )
  )

(display "STEP 2\n")
(display "(keywordSearch \"Java\" articles)\n")
(keywordSearch "Java" articles)
