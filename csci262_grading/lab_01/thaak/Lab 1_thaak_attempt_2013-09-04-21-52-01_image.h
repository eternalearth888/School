#include <iostream>
#include <string>

using namespace std;

//Author: TREVOR HAAK

const int BUFFER = 3000;

class image {
public:
	image();
	void read_image(ifstream &stream_in, ofstream &stream_out);
	void negate_red();
	void negate_green();
	void negate_blue();
	void flip_horizontal();
	void grey_scale();
	void flatten_red();
	void flatten_green();
	void flatten_blue();
	void select_effects(string fi_in, string fi_out);
	void image_setup(ifstream &st_in, ofstream &st_out, string fi_in, string fi_out);
	int get_max();

private:
	string ppm_type;
	int rows;
	int cols;
	int max;
	int data[BUFFER];
};