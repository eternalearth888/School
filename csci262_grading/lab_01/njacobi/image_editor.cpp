// Author: Nathaniel Jacobi

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>


using namespace std;

// Global constants so they can be accessed if multiple functions need them.
const int BUFFER_LIMIT = 3000;
const string MAGIC_NUMBER_CONFIRM = "P3";
const string SPACE = " ";
const string NEWLINE = "\n";

// Global variables to allow multiple funtions to use them.
int buffer[BUFFER_LIMIT];
int flip_buffer[BUFFER_LIMIT];
string magic_number;
int max_color;
int columns;
int rows;

// Varaibles that store whether or not the user wants to use that funtion.
char use_negate_red, use_negate_green, use_negate_blue, use_flatten_red, use_flatten_green,
	use_flatten_blue, use_grey_scale, use_flip_horizontal;

// Prototypes for all functions
void create_output (string in_file, string out_file);

int negate_red (char use, int position, int position_value);

int negate_green (char use, int position, int position_value);

int negate_blue (char use, int position, int position_value);

int flatten_red (char use, int position, int position_value);

int flatten_green (char use, int position, int position_value);

int flatten_blue (char use, int position, int position_value);

int grey_scale  (int position, int position_value_one, int position_value_two, int position_value_three);

int flip_horizontal (int position);

int main (){
	// Variables to store the user's desired files
	string input_file;
	string output_file;

	// Titles the program and asks for the file names and stores them.
	cout << "Portable Pixmap (PPM) Image Editor!" << endl;
	cout << "Enter the name of the image file: ";
	cin >> input_file;
	cout << "Enter the name of the output file: ";
	cin >> output_file;

	// Lists the choices that the user can make to alter their file.
	cout << "Here are your choices:" << endl << "[1] negative of red [2] negative of green [3] negative of blue " << endl <<
		"[4] set reds to zero [5] set greens to zero [6] set blues to zero" << endl << "[7] convert to greyscale [8] flip hoizontally" << endl;

	// Prompts whether or not they want the corresponding function and stores the answer.
	cout << "Do you want [1]? (y/n) ";
	cin >> use_negate_red;
	cout << "Do you want [2]? (y/n) ";
	cin >> use_negate_green;
	cout << "Do you want [3]? (y/n) ";
	cin >> use_negate_blue;
	cout << "Do you want [4]? (y/n) ";
	cin >> use_flatten_red;
	cout << "Do you want [5]? (y/n) ";
	cin >> use_flatten_green;
	cout << "Do you want [6]? (y/n) ";
	cin >> use_flatten_blue;
	cout << "Do you want [7]? (y/n) ";
	cin >> use_grey_scale;
	cout << "Do you want [8]? (y/n) ";
	cin >> use_flip_horizontal;

	//Runs the main function that cycles through the others to make changes.
	create_output (input_file, output_file);

	// Confirmation that the file has been created and done being altered.
	cout << output_file << " created." << endl;

	return 0;
}

// Function that takes the file names, reads from one and writes to the other accoding to what the user wants.
void create_output (string in_file, string out_file) {
	// Array if the horizontal flip funciton is called.
	

	// Creates an input stream to raed the file.
	ifstream read_file(in_file.c_str());

	// Checks and displays if there is an error opening the file.
	if (!read_file) {
		cerr << "There was an error opening the image file." << endl;

		system("pause");
		exit(1);
	}

	// Reads the first three lines of the file and stores the items taken to be recopied later.
	read_file >> magic_number;
	read_file >> columns >> rows;
	read_file >> max_color;


	// Checks to see if the file will be too large for the buffer. Each column takes 3 spots, so there must be 1000 or less.
	if ((columns * 3) > 3000) {
		cout << "This file is too large to be read. The program will now exit." << endl;
		read_file.close();
	}

	// Creates an output stream using the filename given.
	ofstream create_file(out_file.c_str());

	// Checks if there is an error opening that file.
	if (!create_file) {
		cerr << "There was an error opening the new image file." << endl;

		system("pause");
		exit(1);
	}
	
	// Copies the first three lines into the new file.
	create_file << magic_number << NEWLINE;
	create_file << columns << SPACE << rows << NEWLINE;
	create_file <<max_color;
	
	// For loop that goes through each row.
	for (int i=1; i <= rows; i++) {
		// Makes a new line for every row.
		create_file << NEWLINE;
		
		// For loop that goes through all of the columns, stores and then alters the information if need be before writing it.
		for (int j=0; j < (columns * 3); j++) {
			// Stores the integer into the buffer
			read_file >> buffer[j];

			// Goes through each function and checks whether or not it needs to be altered, and stores the value returned.
			buffer[j] = negate_red (use_negate_red, j, buffer[j]);
			buffer[j] = negate_green (use_negate_green, j, buffer[j]);
			buffer[j] = negate_blue (use_negate_blue, j, buffer[j]);
			buffer[j] = flatten_red (use_flatten_red, j, buffer[j]);
			buffer[j] = flatten_green (use_flatten_green, j, buffer[j]);
			buffer[j] = flatten_blue (use_flatten_blue, j, buffer[j]);
			
			// Special (if) for the grey_scale function becuase it must effect past values before writing to the file.
			if (((use_grey_scale == 'y' || use_grey_scale == 'Y')) && ((j + 1) % 3 == 0)) {
				buffer[j-2] = buffer[j-1] = buffer[j] = grey_scale(j, buffer[j-2], buffer[j-1], buffer[j]);
			}
		}
		// For loop that will fill the flip_buffer if it is needed.
		for (int j=0; j < (columns * 3); j++) {
			if (use_flip_horizontal == 'y' || use_flip_horizontal == 'Y') {
				// Calls the flip_horizontal function that stores the values into the correct spots to be switched right after.
				flip_buffer[flip_horizontal(j)] = buffer[j];
			}
		}
		// For loop that will make the buffer array flipped if need be, and or then write that row to the file.
		for  (int j=0; j < (columns * 3); j++) {
			if (use_flip_horizontal == 'y' || use_flip_horizontal == 'Y'){
				buffer[j] = flip_buffer[j];
			}

			// If statement that will write the set of RGB colors together.
			if ((j + 1) % 3 == 0) {
				create_file << buffer[j-2] << SPACE << buffer[j-1] << SPACE << buffer[j] << SPACE;
				create_file << SPACE;
			}
		}
	}
	
	// Closes the files to avoid unintended changes.
	read_file.close();
	create_file.close();
}

// File that will change the value of red to its opposite. Ex 255 to 0 or 15 to 100.
int negate_red (char use, int position, int position_value) {
	int new_red;	// Integer to store teh new red value

	// Checks to see if the user wants this.
	if (use == 'y' || use == 'Y') {
		// Makes sure it alters the right position.
		if ((position % 3) == 0) {
				// Subtracts the max color value from the old color value, and gives its absolute value
				new_red = position_value;
				new_red = abs(new_red - max_color);
				position_value = new_red;
			}
		return position_value; // Returns new red
	}
	return position_value; // Returns original value if it is not needed.
}

// Same function as the red, just for green
int negate_green (char use, int position, int position_value) {
	int new_green;

	if (use == 'y' || use == 'Y') {
		if (((position - 1) % 3) == 0) {
				new_green = position_value;
				new_green = abs(new_green - max_color);
				position_value = new_green;
			}
		return position_value;
	}
	return position_value;
}

// Same function as the red and green, onl for blue.
int negate_blue (char use, int position, int position_value) {
	int new_blue;

	if (use == 'y' || use == 'Y') {
		if (((position + 1) % 3) == 0) {
				new_blue = position_value;
				new_blue = abs(new_blue - max_color);
				position_value = new_blue;
			}
		return position_value;
	}
	return position_value;
}

// Function that turns all red positions to the number 0.
int flatten_red (char use, int position, int position_value) {
	// Checks to see if it is wanted by the user
	if (use == 'y' || use == 'Y') {
		if ((position % 3) == 0) {
			position_value = 0; // Sets the new color value to 0.
		}
		return position_value; // Returns the new color value.
	}
	return position_value; // Returns the original value if the function is not wanted.
}

// Same function as the red, just for green.
int flatten_green (char use, int position, int position_value) {
	if (use == 'y' || use == 'Y') {
		if (((position - 1) % 3) == 0) {
			position_value = 0;
		}
		return position_value;
	}
	return position_value;
}

// Same function as for re and green, only for blue.
int flatten_blue (char use, int position, int position_value) {
	if (use == 'y' || use == 'Y') {
		if (((position + 1) % 3) == 0) {
			position_value = 0;
		}
		return position_value;
	}
	return position_value;
}

// Function that takes the set of RGB values and averages them.
int grey_scale (int position, int position_value_one, int position_value_two, int position_value_three) {
	int sum = 0;
	int average;

	// Checks to see the proper time of when to perform this function, so it only hits one set.
	if (((position + 1) % 3) == 0) {
		sum = (position_value_one + sum);
		sum = (position_value_two + sum);
		sum = (position_value_three + sum);
		average = sum/3;
		return average; // Returns the average.
	}
	 
}

// Funtion that flips the total pixles (so the RGB color values) to its opposite side.
int flip_horizontal (int position) {
	int total_num = columns * 3;
	int new_position;

	// Shifts the numbers into the correct position.
	if ((position % 3) == 0) {
		return total_num - position - 3;
	}
	else if (((position - 1) % 3) == 0) {
		return total_num - position - 1;
	}
	else if (((position + 1) % 3) == 0) {
		return total_num - position + 1;
	}
}