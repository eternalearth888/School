Credits to those who helped:

James Dang
Tranh Tran
My older brother
From around the web (aka Googling):
cplusplus.com
stackoverflow.com
devshed.com
daniweb.com
yahoo! answers


Significant stuff that I learned:
My main problem was with the input output from file (well, mainly input). I eventually made
it work after getting help from the people and websites listed above. The following are what I learned
from other people and trial and error. Eventually I got everythings working, although I'm not too happy
with my I/O class since it ended up built almost specifically for this lab.

.seekg() and .tellg() are apparently for use when reading the file in binary mode
(although it worked well when I tried them while keeping the file as text).

cin in separate lines are still 'connected.' What's supposed to be two distinct inputs
could ended being read from one long input. Cin is also slightly problematic when assigned
to different types of variables.

getline() can't spit out integer array

Part 1 is the hardest part of this lab by far
(probably because I sucked at reading/writing files)

Use .eof() to find end of line.

Carriage return can screw up codes that otherwise work fine when there's only newline.

.ignore() and .clear() is your friend. It lets you ignore/clear junk (like carriage return above).

Cin won't accept spacing. Use get() or getline() instead.

Unlike Java, if you want to modify a variable that you send into a function's parameter,
you need to assign its reference (with &), not the variable's value itself. However, my
older brother remarked that this is not really a good idea, especially if I want to
do parallel code (but then, I don't think I'll get that far). This is apparently in the
basic c++ syntax page included in the lab manual, but I didn't understand it.

Finally understood what 'using namespace std' means (*facepalm*)

Error should be reported through cerr, not cout

Ofstream truncates file by default, but can be set to append things at the end

Use notepad++, because notepad ain't good enough

Unix doesn't have carriage return while DOS/Win does


What I like/dislike about this assignment:

Well, I learned a lot about c++ while doing it, mostly pertaining to iofstream,
but I still hate reading files. I was never good at it.

Also, why can't we just use a big enough, or dynamically allocated, 2D array from the start?
I ended up not doing the bonuses because I don't want to rewrite things with 2D array. I wasted
enough time trying to make my IO file working, so once it worked, I don't want to touch it.
And I don't see how any of part 2 can be hard to do when using 2D array.