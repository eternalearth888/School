#ifndef IMAGE_H
#define IMAGE_H

#include <string>

class image
{
private:
	std::string input_filename;
	std::string output_filename;
	static const int BUFFER_SIZE  = 3000;
	std::string magic_number;
	int num_columns;
	int num_rows;
	int max_color_value;
	char edit_choice[11];
		
	void negate_red(int row[BUFFER_SIZE]);
	void negate_green(int row[BUFFER_SIZE]);
	void negate_blue(int row[BUFFER_SIZE]);
	void flip_horizontal(int row[BUFFER_SIZE]);
	void grey_scale(int row[BUFFER_SIZE]);
	void flatten_red(int row[BUFFER_SIZE]);
	void flatten_green(int row[BUFFER_SIZE]);
	void flatten_blue(int row[BUFFER_SIZE]);

	void horizontal_blur(int row[BUFFER_SIZE]);
	void extreme_contrast(int row[BUFFER_SIZE]);
	void random_noise(int row[BUFFER_SIZE]);

	void menu();

public:
	
	image(); 
	void run();	

};

#endif