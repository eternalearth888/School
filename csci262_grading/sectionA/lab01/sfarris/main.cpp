#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "PPM.h"


using namespace std;



int main() {

	cout << "Portable Pixmap (PPM) Image Editor" << endl << endl;

	PPM ppm;
	ppm.get_initial_info();

	if ( ppm.check_initial_info() == 1 ){
		return -1;
	}
	else {
		ppm.write_initial_info();
	}

	ppm.main_menu();
	ppm.read_file();


	// close input and output files
	ppm.input_file.close();
	ppm.out_file.close();

	return 0;
}

