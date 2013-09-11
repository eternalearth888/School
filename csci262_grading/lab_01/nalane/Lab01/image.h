#pragma once

#include <string>

class image {
public:
	// The capacity of out buffer.
	const static int CAPACITY = 3000;

	// Constructors
	image();
	image(const std::string &input, const std::string &output);

	// Set the filenames
	void setInput(const std::string &input);
	void setOutput(const std::string &output);

	// Create the new file
	bool copy(bool negate_red, bool negate_green, bool negate_blue, bool flip_horizontal, bool grey_scale, bool flatten_red, bool flatten_green, bool flatten_blue, bool extreme_contrast, bool horizontal_blur);

	// Changes made in the file
	void negate_red();
	void negate_green();
	void negate_blue();
	void flip_horizontal();
	void grey_scale();
	void flatten_red();
	void flatten_green();
	void flatten_blue();
	void extreme_contrast();
	void horizontal_blur();

private:
	// Parameters of the image
	int width;
	int height;
	int maxVal;

	// Filepaths
	std::string inFile;
	std::string outFile;

	// Buffer
	int data[CAPACITY];
};