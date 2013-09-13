/*
 * ppmedit.cpp
 *
 *  Created on: Aug 28, 2013
 *      Author: Samuel
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

int main() {

	string ifname,ofname,type;
	int header[3];
	int colorarr[3000];
	int _numrows, _numcols, _maxcolor, _randnum;

	void negate_red(int changearr[], int maxrgb, int cols);
	void negate_green(int changearr[], int maxrgb, int cols);
	void negate_blue(int changearr[], int maxrgb, int cols);
	void flip_horizontal(int changearr[], int cols);
	void flatten_red(int changearr[], int cols);
	void flatten_green(int changearr[], int cols);
	void flatten_blue(int changearr[], int cols);
	void grey_scale(int changearr[], int cols);
	void extreme_contrast(int changearr[], int maxrgb, int cols);
	void horizontal_blur(int changearr[], int cols);
	void random_noise(int changearr[], int maxrgb, int cols, int randnum);
	void flip_vertical(int** changearr, int cols, int rows);
	bool response_tf();

	bool is_nr,is_ng,is_nb,is_fh,is_gs,is_fr,is_fg,is_fb,is_ec,is_hb,is_rn,is_fv;

	cout << "Enter the name of a ppm file: ";
	cin >> ifname;
	ifstream infile (ifname.c_str());
	if (!infile){
		cout << "File does not exist. Aborting program." << endl;
		exit(1);
	}
 	cout << "Enter the name of the output file: ";
	cin >> ofname;
	if (ifname == ofname) {
		cout << "Input file and output file cannot have the same name. Aborting program" << endl;
		exit(1);
	}

	cout << "\n1. Negate red? (y/n): ";
	is_nr = response_tf();
	cout << "2. Negate green? (y/n): ";
	is_ng = response_tf();
	cout << "3. Negate blue? (y/n): ";
	is_nb = response_tf();
	cout << "4. Greyscale? (y/n): ";
	is_gs = response_tf();
	cout << "5. Flatten red? (y/n): ";
	is_fr = response_tf();
	cout << "6. Flatten green? (y/n): ";
	is_fg = response_tf();
	cout << "7. Flatten blue? (y/n): ";
	is_fb = response_tf();
	cout << "8. Flip horizontally? (y/n): ";
	is_fh = response_tf();
	cout << "9. Extreme contrast? (y/n): ";
	is_ec = response_tf();
	cout << "10. Horizontal blur? (y/n): ";
	is_hb = response_tf();
	cout << "11. Random noise? (y/n): ";
	is_rn = response_tf();
	if (is_rn == true) {
		cout << "   Enter a number to represent the range of values that will be randomly selected: ";
		cin >> _randnum;
		if (_randnum == NULL){
			cout << "   Did not enter a valid integer. Aborting program." << endl;
			exit(1);
		}
	}
	cout << "12. Flip vertically? (y/n): ";
	is_fv = response_tf();

	infile >> type;

	if (type!="P3") {
		cout << "File type not supported; must be in P3 format. Aborting program." << endl;
			exit(1);
	}

	for (int x = 0; x<3; x++) {
		infile >> header[x];
	}

	_numcols=header[0]*3;
	_numrows=header[1];
	_maxcolor = header[2];
	int** verarr = new int* [_numrows];
	for( int i = 0 ; i < _numrows ; i++ ) {
	    verarr[i] = new int[_numcols];
	}

	if (_numcols > 3000) {
		cout << "Image size too large; bounds are 1000 pixels. Aborting program." << endl;
		exit(1);
	}

	ofstream outfile (ofname.c_str());
	char typel=type[0];
	char typen = type[1];
	outfile << typel<< typen << endl << header[0] << " " << header[1] << endl << header[2] << endl;

	for (int x=0; x<_numrows;x=x+1) {

		for (int i=0; i<_numcols; i++) {
			infile >> colorarr[i];
		}


		if (is_nr)
			negate_red(colorarr,_maxcolor, _numcols);
		if (is_ng)
			negate_green(colorarr,_maxcolor, _numcols);
		if (is_nb)
			negate_blue(colorarr,_maxcolor, _numcols);
		if (is_gs)
			grey_scale(colorarr,_numcols);
		if (is_fr)
			flatten_red(colorarr, _numcols);
		if (is_fg)
			flatten_green(colorarr, _numcols);
		if (is_fb)
			flatten_blue(colorarr, _numcols);
		if (is_fh)
			flip_horizontal(colorarr,_numcols);
		if (is_ec)
			extreme_contrast(colorarr,_maxcolor,_numcols);
		if (is_hb)
			horizontal_blur(colorarr, _numcols);
		if (is_rn)
			random_noise(colorarr, _maxcolor, _numcols, _randnum);

		if (!is_fv) {
			for (int i=0; i<_numcols; i++) {
				outfile << colorarr[i] << " " << flush;
			}

			outfile << endl;

		}
		else {
			for (int i=0; i < _numcols;i++) {
				verarr[x][i] = colorarr[i];
			}
		}

	}

	if (is_fv) {
		flip_vertical(verarr, _numcols, _numrows);
		for (int i=0; i < _numrows;i++) {
			for (int j=0; j < _numcols; j++) {
				outfile << verarr[i][j] << " " << flush;
			}
			outfile << endl;
		}
	}

	cout << ofname << " created." << endl;

	infile.close();
	outfile.close();
	for( int i = 0 ; i < _numrows ; i++ ) {
	    delete [] verarr[i];
	}
	delete [] verarr;

	system("pause");
	return 0;
}

bool response_tf() {
	string response;
	cin >> response;
	if (response == "y") {
		return true;
	} else if (response == "n") {
		return false;
	} else {
		cout << "Did not respond with a 'y' or an 'n'. Aborting program." << endl;
		exit(1);
	}
}

void negate_red(int changearr[], int maxrgb, int cols) {
	for (int x=0; x<cols;x=x+3) {
			changearr[x] = maxrgb-changearr[x];
		}
	return;
	}

void negate_green(int changearr[], int maxrgb, int cols) {
	for (int x=1; x<cols;x=x+3) {
			changearr[x] = maxrgb-changearr[x];
		}
	return;
	}

void negate_blue(int changearr[], int maxrgb, int cols) {
	for (int x=2; x<cols;x=x+3) {
			changearr[x] = maxrgb-changearr[x];
		}
	return;
	}

void flip_horizontal (int changearr[], int cols) {
	for (int i=0; i<cols/2; i=i+3) {
		swap(changearr[i],changearr[cols-3-i]);
		swap(changearr[i+1],changearr[cols-2-i]);
		swap(changearr[i+2],changearr[cols-1-i]);
	}

	return;
}

void flatten_red(int changearr[], int cols) {
	for (int x=0; x<cols;x=x+3) {
			changearr[x] = 0;
		}
	return;
	}

void flatten_green(int changearr[], int cols) {
	for (int x=1; x<cols;x=x+3) {
			changearr[x] = 0;
		}
	return;
	}

void flatten_blue(int changearr[], int cols) {
	for (int x=2; x<cols;x=x+3) {
			changearr[x] = 0;
		}
	return;
	}

void grey_scale(int changearr[], int cols) {
	int avg;
	for (int x=0; x < cols; x=x+3) {
		avg = (changearr[x] + changearr[x+1] + changearr[x+2])/3;
		for (int i=0; i<3;i++)
			changearr[i+x]=avg;
	}
	return;
}


void extreme_contrast(int changearr[], int maxrgb, int cols){
	for (int x=0; x<cols;x++) {
		if (changearr[x] < maxrgb/2)
			changearr[x] = 0;
		else
			changearr[x] = maxrgb;
	}
	return;
}

void horizontal_blur(int changearr[], int cols) {
	int avg_red;
	int avg_green;
	int avg_blue;
	for (int i=9;i<cols;i=i+3) {
		avg_red = (changearr[i-9]+changearr[i-6]+changearr[i-3])/3;
		avg_green = (changearr[i-8]+changearr[i-5]+changearr[i-2])/3;
		avg_blue = (changearr[i-7]+changearr[i-4]+changearr[i-1])/3;
		changearr[i-9]= avg_red,changearr[i-6]=avg_red,changearr[i-3] = avg_red;
		changearr[i-8]= avg_green,changearr[i-5]=avg_green,changearr[i-2] = avg_green;
		changearr[i-7]= avg_blue,changearr[i-4]=avg_blue,changearr[i-1] = avg_blue;
	}
	return;
}

void random_noise (int changearr[], int maxrgb, int cols, int randnum){
	int addorsubtract;
	for (int i=0;i<cols;i++) {
		addorsubtract = rand()%2;
		if (addorsubtract == 0)
			changearr[i] = changearr[i] + rand()%randnum;
		else
			changearr[i] = changearr[i] - rand()%randnum;
		if (changearr[i]<0)
			changearr[i]=0;
		else if (changearr[i]>maxrgb)
			changearr[i]=maxrgb;
	}
	return;
}

void flip_vertical(int** changearr, int cols, int rows){
	for (int i=0; i<rows/2; i++) {
		for (int j=0; j<cols; j++) {
			swap (changearr[i][j],changearr[rows-1-i][j]);
		}
	}
	return;
}
