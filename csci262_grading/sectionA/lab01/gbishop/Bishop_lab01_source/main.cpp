// CSCI 262 Lab 01
// Grant Bishop

// Std library includes
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Additional project files
#include "image.h"
#include "process.h"
#include "settings.h"

int main() {

	// Variables
	string filename_input_in;
	string filename_input;
	string filname_output_in;
	string filename_output;
	int row = 0;
	char user_input = 0;
	const int number_of_options = 11;
	bool do_process[number_of_options] = {false};


	// Welcome user
	cout << "CSCI261 Lab A: PPM image editor" << endl;

	// Input file
	cout << "Enter input filename: ";
	cin >> filename_input_in;
	filename_input = filename_default_directory + filename_input_in;
	
	// Instantiate the image input object and check for error in opening file
	// If file not opened. or too large, quit
	image_input img_in(filename_input);
	if (img_in.status == 1) {
		cerr << "File not found!" << endl;
		return 1;
	}
	else if (img_in.status == 2) {
		cerr << "Image to larger for buffer!" << endl;
		return 2;
	}

	// Output file
	cout << "Enter output filename: ";
	cin >> filname_output_in;
	filename_output = filename_default_directory + filname_output_in;
	
	// Instantiate the image input object with the information from the input file
	// And check for error in opening file - If file not opened, quit
	image_output img_out(filename_output,img_in.get_magic_number(),img_in.get_image_width(), img_in.get_image_height(),img_in.get_image_depth());
	if (img_in.status == 1) {
		cerr << "Unable to create output file!" << endl;
		return 1;
	}
	
	// Prompt user for action
	cout << "Here are your choices:" << endl;
	cout << "   [1] grayscale   [2] flip horizontally" << endl;
	cout << "   [3] negative red   [4] neg. green   [5] neg. blue" << endl;
	cout << "   [6] only red   [7] only green   [8] only blue" << endl;
	cout << "   [9] full contrast   [10]  horizontal blur" << endl;
	cout << "   [11] add random noise" << endl;
	cout << endl;
	cout << " Select y/n for each:" << endl;
	
	// Ask for each option
	for (int i = 0; i < number_of_options; i++) {
		cout << "[" << (i+1) << "]: ";
		cin >> user_input;
		if ( user_input == 'Y' || user_input == 'y' )
			do_process[i] = true;
		else
			do_process[i] = false;
	}
	cout << endl << "Working ... ";

	// Image buffer
	unsigned int image_buffer[BUFFER_SIZE];
	
	// Read a line from the input file (while there are lines remaining)
	while (img_in.read_line(image_buffer)) {
		row++;

		// Do the processes requested by the user

		// required functions:
		if (do_process[0])
			grey_scale(image_buffer,img_in.get_image_width());
		if (do_process[1])
			flip_horizontal(image_buffer,img_in.get_image_width());
		if (do_process[2])
			negate_red(image_buffer,img_in.get_image_width(),img_in.get_image_depth());
		if (do_process[3])
			negate_green(image_buffer,img_in.get_image_width(),img_in.get_image_depth());
		if (do_process[4])
			negate_blue(image_buffer,img_in.get_image_width(),img_in.get_image_depth());
		if (do_process[5]) {
			flatten_green(image_buffer,img_in.get_image_width());
			flatten_blue(image_buffer,img_in.get_image_width());
		}
		if (do_process[6]) {
			flatten_red(image_buffer,img_in.get_image_width());
			flatten_blue(image_buffer,img_in.get_image_width());
		}
		if (do_process[7]) {
			flatten_red(image_buffer,img_in.get_image_width());
			flatten_green(image_buffer,img_in.get_image_width());
		}
		// bonus functions
		if (do_process[8])
			extreme_contrast(image_buffer,img_in.get_image_width(),img_in.get_image_depth());
		if (do_process[9])
			horizontal_blur(image_buffer,img_in.get_image_width());
		if (do_process[10])
			random_noise(image_buffer,img_in.get_image_width(),img_in.get_image_depth(),RANDOM_AMOUNT,row);
	
		// Write the buffer to the output file
		img_out.write_line(image_buffer);
	}

	cout << " Done!" << endl;
	
	return 0;
}