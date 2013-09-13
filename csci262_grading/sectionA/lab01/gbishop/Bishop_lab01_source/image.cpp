#include "image.h"

// Paramaterized constructor
image_input::image_input(string filename) {

	// Open the file
	file_input.open(filename.c_str());

	// Check for failure is so, set status to false, else continue constructor
	if (!file_input) {
		status = 1; 
	}
	else {
		status = 0;
		// Get the image paramters

		// Get the magic number
		file_input >> magic_number;
		
		// Get the image size
		file_input >> image_width;
		file_input >> image_height;

		// Does the image size work with the given buffer?
		if (image_width > BUFFER_SIZE) {
			status = 2;
		}
		
		// Get the max color value
		file_input >> image_depth;

		// Set to first line
		current_read_line = 0;
	}		
}

// Destructor (is this a valid way to make sure the file is closed? - seems to work, but is it good practice?)
image_input::~image_input() {
	// Close the file
	file_input.close();
	//cerr << "file closed!" << endl; // <- this gets called, so the file must have been closed?
}

// Read one line to the buffer
bool image_input::read_line(unsigned int buffer_array[BUFFER_SIZE]) {
	
	// Temporary variables to store in buffer
	int pixel_r = 0;
	int pixel_g = 0;
	int pixel_b = 0;

	// Are there still lines to be read?
	if (current_read_line < image_height) {
		
		// Read the values from one line into the buffer
		for (unsigned int i = 0; i < (image_width*3); i++) {
			
			// Copy one value from the file to the buffer
			file_input >> buffer_array[i];

		}
		
		// Increment line counter
		current_read_line++;
		return true;
	}
	else {
		return false;
	}
}

// Parameterized constructor
image_output::image_output(string filename, string magic, unsigned int width, unsigned int height, unsigned int depth) {

	// Open the file
	file_output.open(filename.c_str());

	// Check for failure is so, set status to false, else continue constructor
	if (!file_output) {
		status = 1; 
	}
	else {
		status = 0;

		// Set image paramters
		magic_number = magic;
		image_width = width;
		image_height = height;
		image_depth = depth;

		// Write image paramters to file
		file_output << magic_number << endl;
		file_output << image_width << DELIM_CHAR << image_height << endl;
		file_output << image_depth << endl;
	}

}

// Destructor
image_output::~image_output() {
	// Close the file
	file_output.close();
}

// Write one life from a buffer
void image_output::write_line(unsigned int buffer_array[BUFFER_SIZE]) {

	for (unsigned int i = 0; i < (image_width*3); i++)
		file_output << buffer_array[i] << DELIM_CHAR;

	file_output << endl;

}