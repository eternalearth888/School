#include <iostream>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

// Calculates the average of the R, G, and B values of each pixel and assigns each color that value
void grey_scale(int* data, int image_x) {
	for (int i = 0; i < image_x * 3; i += 3) {
		int average = (data[i] + data[i + 1] + data[i + 2]) / 3;
		data[i] = data[i + 1] = data[i + 2] = average;
	}
}

// Sets the red value of each pixel to max_color minus the current value
void negate_red(int* data, int image_x, int max_color) {
	for (int i = 0; i < image_x * 3; i += 3) {
		data[i] = max_color - data[i];
	}
}

// Sets the green value of each pixel to max_color minus the current value
void negate_green(int* data, int image_x, int max_color) {
	data++; // Offset pointer by 1 to work with greens
	for (int i = 0; i < image_x * 3; i += 3) {
		data[i] = max_color - data[i];
	}
}

// Sets the blue value of each pixel to max_color minus the current value
void negate_blue(int* data, int image_x, int max_color) {
	data += 2; // Offset pointer by 2 to work with blues
	for (int i = 0; i < image_x * 3; i += 3) {
		data[i] = max_color - data[i];
	}
}

// Sets the red value of each pixel to 0
void flatten_red(int* data, int image_x) {
	for (int i = 0; i < image_x * 3; i += 3) {
		data[i] = 0;
	}
}

// Sets the green value of each pixel to 0
void flatten_green(int* data, int image_x) {
	data++; // Offset pointer by 1 to work with greens
	for (int i = 0; i < image_x * 3; i += 3) {
		data[i] = 0;
	}
}

// Sets the blue value of each pixel to 0
void flatten_blue(int* data, int image_x) {
	data += 2; // Offset pointer by 2 to work with blues
	for (int i = 0; i < image_x * 3; i += 3) {
		data[i] = 0;
	}
}

// Flips the pixels horizontally
void flip_horizontal(int* data, int image_x) {
	// Last index = (image_x * 3) - 1
	// Last red index = (image_x * 3) - 3

	int temp;
	// Loop through the pixels in the first half of the row
	for (int i = 0; i < (image_x * 3) / 2; i += 3) {
		// For each pixel, loop through each color
		for (int j = 0; j < 3; j++) {
			// Store the value at this index in the temporary variable
			temp = data[i + j];

			// Assign the value at this index to the value on the other side of the array (index of last red - index of current red + color offset)
			data[i + j] = data[(image_x * 3) - 3 - i + j];
			
			// Assign the value on the other side of the array to the temporary value
			data[(image_x * 3) - 3 - i + j] = temp;
		}
	}
}

// Changes each color value to 0 or max_color, depending on which it is closer to.
void extreme_contrast(int* data, int image_x, int max_color) {
	for (int i = 0; i < (image_x * 3); i++) {
		if (data[i] > (max_color / 2)) {
			data[i] = max_color;
		} else {
			data[i] = 0;
		}
	}
}

int main() {
	
	const int BUFFER_SIZE = 4000;
	const string FILE_IDENTIFIER = "P3";

	cout << "Portable Pixmap (PPM) Image Editor\n\n";

	// Open the input file
	string input_filename;
	cout << "Enter name of image file: ";
	cin >> input_filename;
	ifstream input_file;
	input_file.open(input_filename.c_str(), ifstream::in);

	if (!input_file) {
		cout << "Error opening input file. Quitting.";
		exit(1);
	}

	// Open the output file
	string output_filename;
	cout << "Enter name of output file: ";
	cin >> output_filename;
	ofstream output_file;
	output_file.open(output_filename.c_str(), ifstream::out);

	if (!output_file) {
		cout << "Error opening output file. Quitting.";
		exit(1);
	}

	// Discard the first line containing the "magic number" file type identifier
	input_file.ignore(numeric_limits<streamsize>::max(), '\n');

	// Read x, y, and max color value from the file
	int image_x, image_y, max_color;
	input_file >> image_x >> image_y >> max_color;

	if (image_x * 3 > BUFFER_SIZE) {
		cout << "Image too large to process. Exiting.";
		exit(1);
	}
	
	output_file << FILE_IDENTIFIER << '\n' << image_x << ' ' << image_y << '\n' << max_color << '\n';

	cout << "Here are your choices: \n";
	cout << "[0]  no effect  [1]  convert to greyscale [2]  flip horizontally\n";
	cout << "[3]  negative of red [4]  negative of green [5]  negative of blue\n";
	cout << "[6]  flatten the reds   [7]  flatten the greens   [8]  flatten the blues\n";
	cout << "[9]  extreme contrast\n";

	string options;
	cout << "Enter the options you want without spaces. Options can be used multiple times and will be applied in the order in which they appear.\n";
	cin >> options;

	int data[BUFFER_SIZE];

	for (int i = 0; i < image_y; i++) {

		// Read a row into the buffer
		for (int j = 0; j < image_x * 3; j+= 3) {
			input_file >> data[j] >> data[j+1] >> data[j+2];
		}

		// Process the string of chosen options one at a time
		for (int k = 0; k < options.size(); k++) {
			if (options[k] == '1') {
				grey_scale(data, image_x);
			} else if (options[k] == '2') {
				flip_horizontal(data, image_x);
			} else if (options[k] == '3') {
				negate_red(data, image_x, max_color);
			} else if (options[k] == '4') {
				negate_green(data, image_x, max_color);
			} else if (options[k] == '5') {
				negate_blue(data, image_x, max_color);
			} else if (options[k] == '6') {
				flatten_red(data, image_x);
			} else if (options[k] == '7') {
				flatten_green(data, image_x);
			} else if (options[k] == '8') {
				flatten_blue(data, image_x);
			} else if (options[k] == '9') {
				extreme_contrast(data, image_x, max_color);
			}
		}

		// Output a modified row to the new file
		for (int j = 0; j < image_x * 3; j+= 3) {
			output_file << data[j] << ' ' << data[j+1] << ' ' << data[j+2] << ' ';
		}
		output_file << '\n';
	}

	input_file.close();
	output_file.close();

	system("pause");
	return 0;
}