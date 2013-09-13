/* Philip Eittreim
 * CSCI262B
 * Colorado School of Mines
 * Fall 2013
 *
 * LAB 1: image editor
 *
 */

#include <iostream>
#include <string>
#include <cctype>
#include "ppm_image.h"

using namespace std;

int main(int argc, char **argv) {
	string input_filename;
	string output_filename;
	ppm_image image;
	int current_option;
	char choice;

	if (argc == 3) {
		input_filename = argv[1];
		output_filename = argv[2];
		cout << "Input file:  " << input_filename << endl;
		cout << "Output file: " << output_filename << endl;
	} else {
		cout << "Enter input filename: ";
		cin >> input_filename;
		cout << "Enter output filename: ";
		cin >> output_filename;
	}
	
	image.set_input_filename(input_filename);
	image.set_output_filename(output_filename);

	cout << "Here are your choices:" << endl <<
	     "[1]  convert to greyscale [2]  flip horizontally" << endl <<
	     "[3]  negative of red [4]  negative of green [5]  negative of blue" << endl <<
	     "[6]  remove just the reds   [7]  remove just the greens " << endl << 
		  "[8]  remove just the blues  [9]  horizontal blur" << endl <<
		  "[10] extreme contrast       [11] random noise" << endl <<
		  "[12] flip veritcal" << endl;


	for (current_option = 1; current_option <= 12; current_option++) {
		cout << "Do you want [" << current_option << "] (y/n)? ";
		cin >> choice;
		if ((char)toupper(choice) == 'Y') {
			switch (current_option) {
				case 1:
					image.options.use_gray_scale = true;
					break;
				case 2:
					image.options.use_flip_horizontal = true;
					break;
				case 3:
					image.options.use_negate_red = true;
					break;
				case 4:
					image.options.use_negate_green = true;
					break;
				case 5:
					image.options.use_negate_blue = true;
					break;
				case 6:
					image.options.use_flatten_red = true;
					break;
				case 7:
					image.options.use_flatten_green = true;
					break;
				case 8:
					image.options.use_flatten_blue = true;
					break;
				case 9:
					image.options.use_horizontal_blur = true;
					break;
				case 10:
					image.options.use_extreme_contrast = true;
					break;
				case 11:
					image.options.use_random_noise = true;
					cout << "\"Random\" number range: (0 to " << 
						image.get_max_color_value() << ") ";
					cin >> image.options.random_noise_amount;
					break;
				case 12:
					image.options.use_flip_vertical = true;
					break;
			}
		}
	}

	if (image.options.use_flip_vertical == true) {
		image.options.use_flip_vertical = false;
		image.process();
		image.clear_all_options();
		image.options.use_flip_vertical = true;
		image.process();	
	} else {
		image.process();
	}

	return 0;
}



