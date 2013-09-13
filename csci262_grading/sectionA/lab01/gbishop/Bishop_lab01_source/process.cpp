#include "process.h"

void negate_red(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width, unsigned int image_depth) {
	// Call negate_color( ... 0) for red
	negate_color(buffer_array,image_width,image_depth,0);
}

void negate_green(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width, unsigned int image_depth) {
	// Call negate_color( ... 1) for green
	negate_color(buffer_array,image_width,image_depth,1);
}

void negate_blue(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width, unsigned int image_depth) {
	// Call negate_color( ... 2) for blue
	negate_color(buffer_array,image_width,image_depth,2);
}

void negate_color(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width, unsigned int image_depth, unsigned int color) {

	// 'Flip' the color
	// called by function for each color, 0 = red, 1 = green, 2 = blue

	// local variables
	int lower = 0;
	int upper = image_depth;

	// Loop through each red pixel in the buffer and 'flip' it
	for (unsigned int i = color; i < (image_width*3); i+=3) {
		buffer_array[i] = (lower + upper - buffer_array[i]);
	}


}

void grey_scale(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width) {

	// local variables
	unsigned int average;

	// Loop through each set of three pixels, taking the average of them
	// and assigining that same value to each
	for (unsigned int i = 0; i < (image_width*3); i+=3) {
		average = (buffer_array[i]+buffer_array[i+1]+buffer_array[i+2])/3;
		buffer_array[i] = average; buffer_array[i+1] = average; buffer_array[i+2] = average;
	}
}

void flatten_red(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width) {
	// Call flatten color with 0 for red
	flatten_color(buffer_array,image_width,0);
}

void flatten_green(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width) {
	// Call flatten color with 1 for green
	flatten_color(buffer_array,image_width,1);
}

void flatten_blue(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width) {
	// Call flatten color with 2 for blue
	flatten_color(buffer_array,image_width,2);
}

void flatten_color(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width, unsigned int color) {
	// set the specified color to zero
	// Loop through the buffer and set each value of the chosen color to zero
	for (unsigned int i = color; i < (image_width*3); i+=3) {
		buffer_array[i] = 0;
	}
}

void flip_horizontal(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width) {

	// Temporary buffer
	unsigned int temp_buffer_array[BUFFER_SIZE];

	// Copy values to temporary buffer
	for (unsigned int i = 0; i < (image_width*3); i++) {
		temp_buffer_array[i] = buffer_array[i];
	}

	// Apply the values from the temporary buffer to the real one in reverse order
	// Acounting for r,g,b values, offset at i, i+1, i+2
	// Perhaps not the most efficent way to do this, as there are two buffers in memory
	for (unsigned int i = 0; i < (image_width*3); i+=3) {
		buffer_array[i] = temp_buffer_array[((image_width*3)-3-i)]; // Red
		buffer_array[i+1] = temp_buffer_array[((image_width*3)-2-i)]; // Green
		buffer_array[i+2] = temp_buffer_array[((image_width*3)-1-i)]; // Blue

	}

}

void extreme_contrast(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width, unsigned int image_depth) {

	// local variables
	unsigned int half_point = image_depth/2;
	unsigned int min_color = 0;
	unsigned int max_color = image_depth;

	for (unsigned int i = 0; i < (image_width*3); i++) {
		
		// Is the color below or above the midpoint?
		if (buffer_array[i] > half_point) {
			// set to max
			buffer_array[i] = max_color;
		}
		else {
			// set to min
			buffer_array[i] = min_color;
		}
	}
}

void random_noise(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width, unsigned int image_depth, unsigned int range, int random_offset) {

	// set up random seed
	unsigned int seed_value = (unsigned int)time(NULL);
	srand(seed_value);

	// local vairables
	int temp_color;
	int lower_bound = -1*range;
	int upper_bound = range;

	for (unsigned int i = 0; i < (image_width*3); i++) {
		
		// add the color value and the random value
		temp_color = buffer_array[i] + ((rand() % (upper_bound - lower_bound + 1)) + lower_bound);

		// is the resulting value valid, or does it need to be set to min/max?
		if (temp_color > (int)image_depth) {
			buffer_array[i] = image_depth;
		}
		else if (temp_color < 0) {
			buffer_array[i] = 0;
		}
		else {
			buffer_array[i] = temp_color;
		}

		// change the seed each time, other wise it there are noticable bands where the same psudo random values are used
		seed_value += ((i+1)*random_offset+(temp_color/2)); // that should be sufficently unpredictable? - using row for random_offset works well
		srand(seed_value); // still some banding for some images ... probably need one of the 'more random' functions ..

	}

}

void horizontal_blur(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width) {

	// Check for sufficent width (otherwise edges will cause issues)
	if (image_width > 9) {

		// left edge
		for (unsigned int i = 0; i < 3; i++) {
			// average of self and pixel to the right
			buffer_array[i] = (buffer_array[i] + buffer_array[i+3])/2; 
		}

		// 'normal' middle pixels
		for (unsigned int i = 3; i < (image_width*3)-3; i++) {
			// average of self, and pixel on each side
			buffer_array[i] = (buffer_array[i-3] + buffer_array[i] + buffer_array[i+3])/3; i++; // Red
			buffer_array[i] = (buffer_array[i-3] + buffer_array[i] + buffer_array[i+3])/3; i++; // Green
			buffer_array[i] = (buffer_array[i-3] + buffer_array[i] + buffer_array[i+3])/3; // Blue
		}

		// right edge
		for (unsigned int i = image_width-3; i < image_width; i++) {
			// average of self andf pixel to left
			buffer_array[i] = (buffer_array[i] + buffer_array[i-3])/2;
		}

	}

}