#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

class picture{
public:
	picture(void);
	picture(const string &filename);
	~picture(void);

	static const int FILTER_COUNT = 8;

	void applyFilters(const string &filename, const bool filters[FILTER_COUNT]);

private:
	string p_type;
	string input_file;
	bool row_long;
	int max_color;
	int **pixels;
	int columns, rows;
	ifstream in_file;
	ofstream out_file;

	void greyscale();
	void flip_h();
	void negate_R();
	void negate_G();
	void negate_B();
	void flat_R();
	void flat_G();
	void flat_B();
	int checkvalue(const int i);

	
};

