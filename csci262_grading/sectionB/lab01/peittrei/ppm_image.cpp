/* Philip Eittreim
 * CSCI262B
 * Colorado School of Mines
 * Fall 2013
 *
 * ppm_image class implementation
 *
 *
 * NOTE: broken ppm image files (wrong amount of data when compared to dimensions
 * according to the size header info) will result in broken output as well.
 * If the damage is minimal on the input file, the output file will have the same 
 * amount of broken-ness as the input file. As long as the input/output files can
 * be opened, the class will try to drive on in the face of errors.
 *
 */

#include "ppm_image.h"
#include <cassert>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <iostream>

ppm_image::ppm_image() {
	_rows = 0;
	_cols = 0;

	srand(_rows * _cols);
	
	// by default do no operations on the image
	clear_all_options();
}

void ppm_image::clear_all_options() {
	options.use_negate_red = false;
	options.use_negate_green = false;
	options.use_negate_blue = false;
	options.use_flip_horizontal = false;
	options.use_gray_scale = false;
	options.use_flatten_red = false;
	options.use_flatten_green = false;
	options.use_flatten_blue = false;
	options.use_horizontal_blur = false;
	options.use_extreme_contrast = false;
	options.use_random_noise = false;
	options.use_flip_vertical = false;
	
	options.random_noise_amount = 0;
}

int ppm_image::get_max_color_value() {
	return _max_color_value;
}

void ppm_image::set_input_filename(string filename) {

	_input_filename = filename;
	_input_file.open(_input_filename.c_str());

	assert(_input_file);
	
	_input_file >> _image_type;
	_input_file >> _cols;
	_input_file >> _rows;
	_input_file >> _max_color_value;

	if (_cols >= BUFFER_SIZE / 3) { // image is too wide
		cerr << "Image is too wide. Maximum width is " << BUFFER_SIZE / 3 <<
			" columns and this image is " << _cols << " columns wide." << endl;
		assert(_cols < BUFFER_SIZE / 3);
	}
}

void ppm_image::set_output_filename(string filename) {
	
	_output_filename = filename;
	_output_file.open(_output_filename.c_str());

	assert(_output_file);

	_output_file << _image_type << endl;
	_output_file << _cols << " " << _rows << endl;
	_output_file << _max_color_value << endl;

}

void ppm_image::process() {
	int rows_read;

	if (_rows > 0) { // only look at the image if there is at least 1 row in it
		if (options.use_flip_vertical == true) {
			_flip_vertical();
		} else {
			for (rows_read = 0; rows_read < _rows; rows_read++) {
				_read_one_row();
				_process_row();
				_write_one_row();
			}
		}
	}	

}
		

ppm_image::~ppm_image() {
	_input_file.close();
	_output_file.close();
}

// private methods
//
void ppm_image::_read_one_row() {
	int subpixels_read;

	for (subpixels_read = 0; subpixels_read < _cols * 3; subpixels_read++) {
		_input_file >> _image_buffer[subpixels_read];
	}
}

void ppm_image::_process_row() {
	
	if (options.use_negate_red == true) {
		_negate_red();
	}
	if (options.use_negate_green == true) {
		_negate_green();
	}
	if (options.use_negate_blue == true) {
		_negate_blue();
	}
	if (options.use_flip_horizontal == true) {
		_flip_horizontal();
	}
	if (options.use_gray_scale == true) {
		_gray_scale();
	}
	if (options.use_flatten_red == true) {
		_flatten_red();
	}
	if (options.use_flatten_green == true) {
		_flatten_green();
	}
	if (options.use_flatten_blue == true) {
		_flatten_blue();
	}
	if (options.use_horizontal_blur == true) {
		_horizontal_blur();
	}
	if (options.use_extreme_contrast == true) {
		_extreme_contrast();
	}	
	if (options.use_random_noise == true) {
		_random_noise();
	}
	// _flip_vertical is not here as it is not a one row at a time operation
	// it must be called from process() to bypass these row wise operations
}

void ppm_image::_write_one_row() {
	int subcols_written;

	for (subcols_written = 0; subcols_written < _cols * 3; subcols_written++) {
		if (subcols_written != 0) {
			if (subcols_written % 3 == 0) {
				_output_file << "  ";
			}
			if (subcols_written % 12 == 0) {
				_output_file << endl;
			}
		}
		_output_file << setw(3) << _image_buffer[subcols_written] << " ";
	}
	_output_file << endl << endl;

}

void ppm_image::_negate_red() {
	int subpixel;

	for (subpixel = 0; subpixel < _cols * 3; subpixel+=3) {
		_image_buffer[subpixel] = abs(_max_color_value - _image_buffer[subpixel]);
	}

}

void ppm_image::_negate_green() {
	int subpixel;

	for (subpixel = 1; subpixel < _cols * 3; subpixel+=3) {
		_image_buffer[subpixel] = abs(_max_color_value - _image_buffer[subpixel]);
	}

}

void ppm_image::_negate_blue() {
	int subpixel;

	for (subpixel = 2; subpixel < _cols * 3; subpixel+=3) {
		_image_buffer[subpixel] = abs(_max_color_value - _image_buffer[subpixel]);
	}

}

void ppm_image::_flip_horizontal() {
	int tmp_subpixel;
	int i, j;
	
	for (i = 0; i < _cols * 1.5; i+=3) {
		for (j = 0; j < 3; j++) {
			tmp_subpixel = _image_buffer[i+j];
			_image_buffer[i+j] = _image_buffer[_cols*3-i+j];
			_image_buffer[_cols*3-i+j] = tmp_subpixel;
		}
	}
}

void ppm_image::_gray_scale() {
	float average_value_working;
	int average_value;
	int i, j;

	for (i = 0; i < _cols * 3; i+=3) {
		for (j = 0, average_value_working = 0; j < 3; j++) {
			average_value_working +=  _image_buffer[i+j];
		}
		average_value = (int)round(average_value_working / 3.0);
		for (j = 0; j < 3; j++) {
			_image_buffer[i+j] = average_value;
		}
	}

}

void ppm_image::_flatten_red() {
	int i;

	for (i = 0; i < _cols * 3; i+=3) {
		_image_buffer[i] = 0;
	}

}

void ppm_image::_flatten_green() {
	int i;

	for (i = 0; i < _cols * 3; i+=3) {
		_image_buffer[i+1] = 0;
	}

}

void ppm_image::_flatten_blue() {
	int i;

	for (i = 0; i < _cols * 3; i+=3) {
		_image_buffer[i+2] = 0;
	}

}

void ppm_image::_horizontal_blur() {
	int i, col, subpixel, color, average_color;
	int subpixels[3];


	for (color = 0; color < 3; color++) {
		for (col = color; col < _cols * 3; col+=3) {

			if (col < 3) { // on the left edge
				average_color =
					(_image_buffer[col] + _image_buffer[col] +
					 _image_buffer[col+3]) / 3;
				_image_buffer[col] = average_color;
				_image_buffer[col+3] = average_color;
			} else if (col > _cols * 3 -1) { // right edge
				average_color =
					(_image_buffer[col-3] + _image_buffer[col] +
					 _image_buffer[col]) / 3;
				_image_buffer[col-3] = average_color;
				_image_buffer[col] = average_color;
			} else { // non edge part of the image
				average_color =
					(_image_buffer[col-3] + _image_buffer[col] +
					 _image_buffer[col+3]) / 3;
				_image_buffer[col-3] = average_color;
				_image_buffer[col] = average_color;
				_image_buffer[col+3] = average_color;

			}
		}
	}
}

void ppm_image::_extreme_contrast() {
	int i;

	for (i = 0; i < _cols * 3; i+=3) {
		_image_buffer[i] = 
			_image_buffer[i] > _max_color_value / 2 ? _max_color_value : 0;
	}

}

void ppm_image::_random_noise() {
	int i;

	int adjustment_amount; // how much to vary the subpixel
	int adjustment_direction; // -1 or 1 depending on addition or subtraction

	assert(RAND_MAX >= options.random_noise_amount);

	for (i = 0, adjustment_amount = 0; i < _cols * 3; i++) {
		adjustment_direction = (rand() < RAND_MAX / 2) ? -1 : 1;
		adjustment_amount = 
			rand() % options.random_noise_amount * adjustment_direction;

		if (adjustment_amount < 0) {
			adjustment_amount = 0;
		} else if (adjustment_amount > _max_color_value) {
			adjustment_amount = _max_color_value;
		} 

		_image_buffer[i] += adjustment_amount;

	}
}

void ppm_image::_flip_vertical() {
	int **_tmp_image;
	int row, col;

	_tmp_image = new int*[_rows];
	for (row = 0; row < _rows; row++) {
		_tmp_image[row] = new int[_cols * 3];
	}

	// close the output file, reopen it as input and read the entire image
	_input_file.close();
	_output_file.close();
	set_input_filename(_output_filename);

	for (row = 0; row < _rows; row++) {
		_read_one_row();
		for (col = 0; col < _cols * 3; col++) {
			_tmp_image[row][col] = _image_buffer[col];
		}
	}
	
	// reopen this same file, now as an output file
	_input_file.close();
	set_output_filename(_output_filename);

	for (row = _rows - 1; row >= 0; row--) {
		for (col = 0; col < _cols * 3; col++) {
			_image_buffer[col] = _tmp_image[row][col];
		}
		_write_one_row();
	}
		
	for (row = 0; row < _rows; row++) {
		delete[] _tmp_image[row];
	}
	
}
