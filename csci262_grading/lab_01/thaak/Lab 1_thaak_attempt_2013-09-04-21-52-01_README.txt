//////////////////////////////////////////////////////////////////////////////////////////
//README (Haak Lab 01)
//Author: Trevor Haak
////////////////////////////////////////////////////////////////////////////////
1. Those who worked on this project: Trevor Haak

////////////////////////////////////////////////////////////////////////////////
2. Challenges encountered:
A major challenge encountered was writing the flip_horizontal function. It was discovered that for awhile, the function was flipping the image twice.
Other times, the function would only flip half of the image and created a mirror effect. Ultimately, it was discovered that the for loop always needed
to be half the duration of the other effect function for loops.
Another major challenge was implementing the effect functions so that they would occur one at a time. At first, it was tried to first prompt the user
then store booleans as to whether the function was to be implemented or not. Then, as the program read in the rgb values from the image, it would apply
the group of effects sequentially to each row. It was discovered that this method took too long to be practical (More than 5 mins!!!). Instead, only
applying effects to the entire image one by one if the user requested them seemed to proceed much faster.

////////////////////////////////////////////////////////////////////////////////
3. Likes/Dislikes:
I liked exploring the idea of coding photo effects. I've used photoshop before and have always wondered how it actually carries out some of the
effects. I also liked how sample PPM files were supplied, as I wasn't readily sure how to acquire one in that format.
I disliked the time it takes to test each function, but I guess that's part of my limited coding knowledge of faster methods.