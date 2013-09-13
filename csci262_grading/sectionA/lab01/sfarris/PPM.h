#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class PPM {

public:
	PPM();

	void get_initial_info();
	int check_initial_info();
	void write_initial_info();
	void main_menu();

	void read_file();
	void edit_line();

	void negate_red();
	void negate_green();
	void negate_blue();
	void flip_horizontal();
	void grey_scale();
	void flatten_red();
	void flatten_green();
	void flatten_blue();

	ifstream input_file;
	ofstream out_file;
	string input_name;
	string out_name;
	string ppm_type;
	int columns, rows, max_color;
	static const int MAX_COLUMNS = 1000;
	int *buffer_array;
	char effects[8];
	
};