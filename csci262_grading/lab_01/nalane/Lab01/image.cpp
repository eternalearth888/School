#include <fstream>
#include <iostream>
#include "image.h"

using namespace std;

// Default constructor
image::image() {
	inFile = "input.ppm";
	outFile = "output.ppm";
}

// Constructor that uses filenames
image::image(const string &input, const string &output) {
	inFile = input;
	outFile = output;
}

// Set the input file if originally unknown
void image::setInput(const std::string &input) {
	inFile = input;
}

// Set the output file if originally unknown
void image::setOutput(const std::string &output) {
	outFile = output;
}

// Create the new file
bool image::copy(bool negate_red, bool negate_green, bool negate_blue, bool flip_horizontal, bool grey_scale, bool flatten_red, bool flatten_green, bool flatten_blue, bool extreme_contrast, bool horizontal_blur) {
	// Needed to check if this is the right kind of file.
	string header;

	// Creates a link to the input file.
	ifstream input(inFile.c_str());

	// Determines if the file can be accessed
	if (!input) {
		cerr << "Cannot read the input file!" << endl;
		return false;
	}

	// Ensure the header is correct (that this is a PPM file of the correct format).
	input >> header;

	if (header != "P3") {
		cerr << "Input file is not a PPM file!" << endl;
		return false;
	}

	// Determine the dimensions of the image.
	input >> width;
	input >> height;

	// Ensure the file's rows can fit into the buffer.
	if (3 * width > CAPACITY) {
		cerr << "Image too wide to be read!" << endl;
		return false;
	}

	// Get the maximum color value for the image.
	input >> maxVal;

	// Open a link to the output file
	ofstream output(outFile.c_str());

	// Determine if the output can be written to.
	if (!output) {
		cerr << "Cannot read the output file!" << endl;
		return false;
	}

	// Write the header information to the file.
	output << header << endl;
	output << width << " " << height << endl;
	output << maxVal << endl;

	// Go through the rows of the input file...
	for (int i = 0; i < height; i++) {
		// Store them to the buffer...
		for(int j = 0; j < 3 * width; j++) {
			input >> data[j];
		}

		// Perform any and all edits required of the program...
		if (negate_red) {
			this->negate_red();
		}

		if (negate_green) {
			this->negate_green();
		}

		if (negate_blue) {
			this->negate_blue();
		}

		if (flip_horizontal) {
			this->flip_horizontal();
		}

		if (grey_scale) {
			this->grey_scale();
		}

		if (flatten_red) {
			this->flatten_red();
		}

		if (flatten_green) {
			this->flatten_green();
		}

		if (flatten_blue) {
			this->flatten_blue();
		}

		if (extreme_contrast) {
			this->extreme_contrast();
		}

		if (horizontal_blur) {
			this->horizontal_blur();
		}

		// And write it all back to the output file.
		for(int j = 0; j < 3 * width; j++) {
			output << data[j];
			if (j % 3 == 2) {
				output << endl;
			}
			else {
				output << " ";
			}
		}
	}

	// Close the connections to the files.
	input.close();
	output.close();
}

void image::negate_red() {
	// Go through every red pixel in the row and negate it.
	for (int i = 0; i < width * 3; i += 3) {
		data[i] = 255 - data[i];
	}
}

void image::negate_green() {
	// Go through every green pixel in the row and negate it.
	for (int i = 1; i < width * 3; i += 3) {
		data[i] = 255 - data[i];
	}
}

void image::negate_blue() {
	// Go through every blue pixel in the row and negate it.
	for (int i = 2; i < width * 3; i += 3) {
		data[i] = 255 - data[i];
	}
}

void image::flip_horizontal() {
	// Create a copy of our data, since we will edit the original data.
	int copy[CAPACITY];

	for (int i = 0; i < width * 3; i++) {
		copy[i] = data[i];
	}

	// Make each pixel's color value equal to the one on the opposite side of the picture.
	for (int i = 2; i < width * 3; i += 3) {
		data[width * 3 - i - 1] = copy[i - 2];
		data[width * 3 - i] = copy[i - 1];
		data[width * 3 - i + 1] = copy[i];
	}
}

void image::grey_scale() {
	// Stores the average color value
	int avg;

	// Calculate the average for every pixel in the row.
	for (int i = 0; i < width * 3; i += 3) {
		avg = (data[i] + data[i + 1] + data[i + 2]) / 3;
		data[i] = avg;
		data[i + 1] = avg;
		data[i + 2] = avg;
	}
}

void image::flatten_red() {
	// Go through the red pixels, and make them all 0.
	for (int i = 0; i < width * 3; i += 3) {
		data[i] = 0;
	}
}

void image::flatten_green() {
	// Go through the green pixels, and make them all 0.
	for (int i = 1; i < width * 3; i += 3) {
		data[i] = 0;
	}
}

void image::flatten_blue() {
	// Go through the blue pixels, and make them all 0.
	for (int i = 2; i < width * 3; i += 3) {
		data[i] = 0;
	}
}

void image::extreme_contrast() {
	// Go through each pixel and determine if its color values should be maximized or minimized.
	for (int i = 0; i < width * 3; i++) {
		if (data[i] < maxVal / 2.0) {
			data[i] = 0;
		} else {
			data[i] = maxVal;
		}
	}
}

void image::horizontal_blur() {
	// Create a copy of the row, because we will edit the original data as we go through it.
	int copy[CAPACITY];

	for(int i = 0; i < width * 3; i++) {
		copy[i] = data[i];
	}

	// Go through each pixel and average its values with those that are adjacent to it.
	for (int i = 3; i < width * 3 - 3; i++) {
		data[i] = (copy[i - 3] + copy[i] + copy[i + 3]) / 3;
	}
}