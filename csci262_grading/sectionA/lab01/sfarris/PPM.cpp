#include "PPM.h"

PPM::PPM() {
	cout << "Please input the PPM file name: ";
	cin >> input_name;
	input_file.open(input_name);
	while ( !input_file.is_open() ){
		cout << "Could not find file. Please enter another file name: ";
		cin >> input_name;
		input_file.open(input_name);
	}

	// open the output file and chack for errors
	cout << "Please input the ouput file name: ";
	cin >> out_name;
	out_file.open(out_name);
	while ( !out_file.is_open() ){
		cout << "Could not find file. Please enter another file name: ";
		cin >> out_name;
		out_file.open(out_name);
	}
}

void PPM:: get_initial_info() {
	input_file >> ppm_type;
	input_file >> columns;
	input_file >> rows;
	input_file >> max_color;
	buffer_array = new int[3 * columns];

}

int PPM::check_initial_info(){
	if ( ppm_type != "P3" || columns > MAX_COLUMNS ) {
		return 1;
	}
	else {
		return 0;
	}
}

void PPM::write_initial_info(){
	out_file << ppm_type << endl << columns << " " << rows << endl << max_color << endl;
}

void PPM::main_menu() {
	
	cout << "Here are your choices: \n" << "[1]  convert to greyscale [2]  flip horizontally \n" 
		<< "[3]  negative of red [4]  negative of green [5]  negative of blue \n"
		<< "[6]  just the reds   [7]  just the greens   [8]  just the blues \n" << endl;

	cout << "Do you want [1]? (y/n) ";
	cin >> effects[0];
	cout << "Do you want [2]? (y/n) ";
	cin >> effects[1];
	cout << "Do you want [3]? (y/n) ";
	cin >> effects[2];
	cout << "Do you want [4]? (y/n) ";
	cin >> effects[3];
	cout << "Do you want [5]? (y/n) ";
	cin >> effects[4];
	cout << "Do you want [6]? (y/n) ";
	cin >> effects[5];
	cout << "Do you want [7]? (y/n) ";
	cin >> effects[6];
	cout << "Do you want [8]? (y/n) ";
	cin >> effects[7];
}

void PPM::edit_line() {
	if ( effects[0] == 'y' ){
		grey_scale();
	}
	if ( effects[1] == 'y' ){
		flip_horizontal();
	}
	if ( effects[2] == 'y' ){
		negate_red();
	}
	if ( effects[3] == 'y' ){
		negate_green();
	}
	if ( effects[4] == 'y' ){
		negate_blue();
	}
	if ( effects[5] == 'y' ){
		flatten_green();
		flatten_blue();
	}
	if ( effects[6] == 'y' ){
		flatten_red();
		flatten_blue();
	}
	if ( effects[7] == 'y' ){
		flatten_red();
		flatten_green();
	}
}

void PPM::read_file(){
	for ( int i = 0; i < rows; i++ ){
		//read every pixel in on one line
		for ( int q = 0; q < 3*columns; q++ ){
			input_file >> buffer_array[q];
		}
		edit_line();
		for ( int q = 0; q < 3*columns; q++ ){
			out_file << buffer_array[q] << " ";
		}
	out_file << endl;
	}
	delete[] buffer_array;
}


void PPM::negate_red() {
	for ( int i = 0; i < columns * 3; i = i + 3){
		buffer_array[i] = max_color - buffer_array[i];
	}
}

void PPM::negate_green() {
	for ( int i = 1; i < columns * 3; i = i + 3){
		buffer_array[i] = max_color - buffer_array[i];
	}
}

void PPM::negate_blue() {
	for ( int i = 2; i < columns * 3; i = i + 3){
		buffer_array[i] = max_color - buffer_array[i];
	}
}

void PPM::flip_horizontal() {
	int *temp_array = new int[columns * 3];
	for ( int i = 0; i < 3 * columns; i++ ){
		temp_array[i] = buffer_array[i];
	}


	for ( int i = 0; i < columns * 3; i = i + 3){
		buffer_array[i] = temp_array[ columns * 3 - i - 3 ];
		buffer_array[i + 1] = temp_array[ columns * 3 - i - 2];
		buffer_array[i + 2] = temp_array[columns * 3 - i - 1];
	}
	delete[] temp_array;
}

void PPM::grey_scale() {
	for ( int i = 0; i < 3 * columns; i = i + 3 ){
		int ave = ( buffer_array[i] + buffer_array[i + 1] + buffer_array[i + 2] ) / 3;
		buffer_array[i] = buffer_array[i + 1] = buffer_array[i + 2] = ave;
	}
}

void PPM::flatten_red() {
	for ( int i = 0; i < columns * 3; i = i + 3 ){
		buffer_array[i] = 0;
	}
}

void PPM::flatten_green() {
	for ( int i = 1; i < columns * 3; i = i + 3 ){
		buffer_array[i] = 0;
	}
}

void PPM::flatten_blue() {
	for ( int i = 2; i < columns * 3; i = i + 3 ){
		buffer_array[i] = 0;
	}
}

