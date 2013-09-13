1. Collaborators: Nobody

2. Describe the challenges you encountered and how you surmounted them
	a. I didn't test each part of the program when I wrote it. I pretty much just wrote the entire program before testing it. This caused a few errors that could have been avoided otherwise. I had to figure out the bugs that were caused by programming like this which was much harder due to them stacking on each other and the fact that once you fix one bug, two more seem to appear.

	b. I had a problem where the program tried to allocate ~4 GB of ram. I couldn't figure out the cause of this for quite a while. I ended up realizing that my program was trying to edit the image using the input file twice. This for some reason was taking up too much memory. I solved this problem by closing the files and opening them in a different order. For example: The first input file was the original file. The first output file was the original output file. I closed both of these and then opened the original output file as the new input file and a temporary file as a new output file. At the end of this, I transferred all of the text from the new output file to the original output file and then deleted the temporary file. This may not be the best way to do this, but I decided it was better than taking up extra memory to create a temporary array.

	c. I had many stack errors. These were caused by incorrectly creating my dynamic array.

	d. I had a lot of difficulty with flipping the image horizontally. At first, I flipped all of the values. This meant that the entire line of values was flipped, not by pixel, but by r, g, b colors. Ex: 233 211 11  55 33 241 became 241 33 55  11 211 233. So, although it flipped the image, the colors were extremely messed up. After this, I messed up my values when moving the color values from the original array backwards to a temporary array.

3. What did you like/dislike about the assignment
	I really liked this project. I love programming and I really enjoy challenging myself. I also love learning new things. I don't love writing readme files, however. I do know the importance, though and am willing to learn how to write good documentation for my programs.