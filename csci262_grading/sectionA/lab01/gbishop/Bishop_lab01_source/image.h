// image.h - contains image_input and image_output classes

#pragma once // is this redundeant with the define IMAGE_H ?


// "header gaurds" as per class on monday 8/26
#ifndef IMAGE_H
#define IMAGE_H

// Std library includes ------where is the 'proper' place to put these - before or after ifndef ? --
#include <fstream>
#include <string>
using namespace std;

#include "settings.h"

// image_input class - the image to read from
class image_input {
public:
	
	// Paramaterized constructor
	image_input(string filename);
	// Destructor (is this a valid way to make sure the file is closed? -  seems to work, but is it good practice?)
	~image_input();

	// Good image? Set by constructor
	int status;
	// status = 0 > all good
	// status = 1 > no file
	// status = 2 > image to wide (buffer to small)

private:

	// file
	ifstream file_input;

	// Magic number
	string magic_number;

	// Image size
	unsigned int image_width;
	unsigned int image_height;

	// Image color depth
	unsigned int image_depth;

	// Current line
	unsigned int current_read_line;

public:

	// Acsessor functions for image paramaters
	string get_magic_number() const {return magic_number;}
	unsigned int get_image_width() const {return image_width;}
	unsigned int get_image_height() const {return image_height;}
	unsigned int get_image_depth() const {return image_depth;}

	// read one line to the buffer
	bool read_line(unsigned int buffer_array[BUFFER_SIZE]);

};

// image_output class - the image to write to
class image_output {
public:
	// Paramaterized constructor
	image_output(string filename, string magic_number, unsigned int width, unsigned int height, unsigned int depth);
	// Destructor (is this a valid way to make sure the file is closed? -  seems to work, but is it good practice?)
	~image_output();

	// Good image? Set by constructor
	int status;
	// status = 0 > all good
	// status = 1 > no file

private:
	
	// file
	ofstream file_output;

	// Magic number
	string magic_number;

	// Image size
	unsigned int image_width;
	unsigned int image_height;

	// Image color depth
	unsigned int image_depth;

public:

	// Write a buffer to a line
	void write_line(unsigned int buffer_array[BUFFER_SIZE]);

};

#endif