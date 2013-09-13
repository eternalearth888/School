Lab assignment #1
Grant Bishop

Files:
	main.cpp
	image.cpp, image.h
	process.cpp, process.cpp
	settings.h

Notes:
	settings.h contains global variables than can be set to control the buffer size, default file location, random_noise amount, and output delimitation character
	
2.

The hardest single part was flip_horizontal, as I was originally trying to do it just in the buffer array without a temporary place to store variables.
I used a second array to do this, but perhaps it could be more efficient to just use one or two ints to store only the values that are needed at one time in the opperation.

In general the most frustrating part was a bunch of off-by-one errors in doing all the array operations.

I still haven't got random_noise quite right.  For some images, particularly grayscale and high contrast ones there is visable 'banding' where the not truly random nature of rand() is apparent.
To do this better I would probably have to either find a better way to seed, or to use a different "more random" random number function.

3.

I actually quite enjoyed this assignment - it felt a lot more representative of a 'real world' problem than most of the HW from csci 261.