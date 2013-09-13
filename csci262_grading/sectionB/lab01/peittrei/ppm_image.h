/* Philip Eittreim
 * CSCI262B
 * Colorado School of Mines
 * Fall 2013
 *
 * ppm_image class header
 *
 */


#ifndef PPM_IMAGE_H
#define PPM_IMAGE_H

#include <string>
#include <fstream>

#define BUFFER_SIZE 3000

using namespace std;

class ppm_image {
public:
	struct {
		bool use_negate_red;
		bool use_negate_green;
		bool use_negate_blue;
		bool use_flip_horizontal;
		bool use_gray_scale;
		bool use_flatten_red;
		bool use_flatten_green;
		bool use_flatten_blue;
		bool use_horizontal_blur;
		bool use_extreme_contrast;
		bool use_random_noise;
		bool use_flip_vertical; // flip vertical CANNOT be used with any
										// other options

		int random_noise_amount;
	} options;


	ppm_image();

	int get_max_color_value(); // get the highest allowable color value

	void set_input_filename(string filename);
	void set_output_filename(string filename);

	void clear_all_options(); // reset all options to false

						 // image is read one row at a time
	void process(); // read input file, process it, and write it to output

	~ppm_image();

private:
	string _image_type; // default to P3
	int _rows;
	int _cols;
	int _max_color_value;
	int _image_buffer[BUFFER_SIZE];
	string _input_filename;
	string _output_filename;
	ifstream _input_file;
	ofstream _output_file;

	void _read_one_row();
	void _process_row(); 	// this is where any operations on the row 
									// will happen as the current
									//	row will be discarded upon reading the next row.
									//	during process_row(), the image must be written 
									//	to another file for any changes to persist
	void _write_one_row();

	// image manipulation methods.  these are all private because they only
	// operate on one row at a time. they rely on being in a loop with
	// _read_one_row() and _write_one_row()
	void _negate_red();			// negate all red values
	void _negate_green();		// negate all green values
	void _negate_blue();			// negate all blue values
	void _flip_horizontal();	// flip image horizontally
	void _gray_scale();			// make image gray scale
	void _flatten_red();			// remove all red
	void _flatten_green();		// remove all green
	void _flatten_blue();		// remove all blue
	void _horizontal_blur(); // take average of 3 nearest same color subpixels
	void _extreme_contrast();	// round all colors to either 0 or maximum
	void _random_noise();		// add random noise to each subpixel

	// _flip_vertical() needs to be called directly by process() at it is not a
	// row wise operation. It is required that the output file be opened again as
	// input part way through this operation.
	void _flip_vertical();		// flip image vertically. will ONLY work with files
};

#endif
