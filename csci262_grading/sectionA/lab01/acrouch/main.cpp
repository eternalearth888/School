#include <iostream>
#include <fstream>
#include <string>

#define BUFFER_SIZE 3000

using namespace std;

void negate_red(int** _array, int columns, int depth) {
	for (int i = 0; i < columns; i++) {
		_array[i][0] = depth - _array[i][0];
	}
}
void negate_green(int** _array, int columns, int depth) {
	for (int i = 0; i < columns; i++) {
		_array[i][1] = depth - _array[i][1];
	}
}
void negate_blue(int** _array, int columns, int depth) {
	for (int i = 0; i < columns; i++) {
		_array[i][2] = depth - _array[i][2];
	}
}
void grey_scale(int** _array, int columns) {
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < 3; j++) {
			if (j % 3 == 0) {
				_array[i][j] = (_array[i][j] + _array[i][j + 1] + _array[i][j + 2]) / 3;
				_array[i][j + 1] = _array[i][j];
				_array[i][j + 2] = _array[i][j];
			}
		}
	}
}
void horizontal_flip(int** _array, int columns) {
	int** new_array = new int*[1000];
	for(int i = 0; i < 1000; i++){
		new_array[i] = new int[3];
	}
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < 3; j++) {
			new_array[i][j] = _array[columns - i - 1][j];
		}
	}
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < 3; j++) {
			_array[i][j] = new_array[i][j];
		}
	}
}
void flatten_red(int** _array, int columns) {
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < 3; j++) {
			if (j % 3 == 0) {
				_array[i][j] = 0;
			}
		}
	}
}
void flatten_green(int** _array, int columns) {
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < 3; j++) {
			if (j % 3 == 1) {
				_array[i][j] = 0;
			}
		}
	}
}
void flatten_blue(int** _array, int columns) {
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < 3; j++) {
			if (j % 3 == 2) {
				_array[i][j] = 0;
			}
		}
	}
}
void extreme_contrast(int** _array, int columns, int depth) {
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < 3; j++) {
			if (_array[i][j] < depth / 2) {
				_array[i][j] = 0;
			}
			else {
				_array[i][j] = depth;
			}
		}
	}
}
int main() {

	char gsdecide, hfdecide, nrdecide, ngdecide, nbdecide, jrdecide, jgdecide, jbdecide, ecdecide;
	string file_contents;
	string filename;
	string magic;
	int col, row, depth;

	cout << "Enter file name: ";
	cin >> filename;
	ifstream myfile (filename.c_str());
	if (!myfile) {
		cerr << "Error! Does not open!";
		exit(1);
	}

	cout << "Enter name of new file: ";
	cin >> filename;
	ofstream outfile (filename.c_str());

	myfile >> magic >> col >> row >> depth;
	outfile << magic << endl;
	outfile << col << " " << row <<endl;
	outfile << depth << endl;
	if (col > 1000) {
		cerr << "Error! File is too large!" << endl;
		system("pause");
		exit(1);
	}
	int** _array = new int*[1000];
	for(int i = 0; i < 1000; i++){
		_array[i] = new int[3];
	}
	cout << "Here are you choices: " << endl;
	cout << "[1] convert to greyscale [2] flip horizontally" << endl;
	cout << "[3] negative of red [4] negative of green [5] negative of blue" << endl;
	cout << "[6] just the reds [7] just the greens [8] just the blues" << endl;
	cout << "[9] extreme contrast" << endl;
	cout << "Do you want [1]? (y/n) ";
	cin >> gsdecide;
	cout << "Do you want [2]? (y/n) ";
	cin >> hfdecide;
	cout << "Do you want [3]? (y/n) ";
	cin >> nrdecide;
	cout << "Do you want [4]? (y/n) ";
	cin >> ngdecide;
	cout << "Do you want [5]? (y/n) ";
	cin >> nbdecide;
	cout << "Do you want [6]? (y/n) ";
	cin >> jrdecide;
	cout << "Do you want [7]? (y/n) ";
	cin >> jgdecide;
	cout << "Do you want [8]? (y/n) ";
	cin >> jbdecide;
	cout << "Do you want [9]? (y/n) ";
	cin >> ecdecide;
	for(int k = 0; k < row; k++){
		for (int i = 0; i < col; i++) {
			for (int j = 0; j < 3; j++) {
				myfile >> _array[i][j];
			}
		}
		if (gsdecide == 'y') {
			grey_scale(_array, col);
		}
		if (hfdecide == 'y') {
			horizontal_flip(_array, col);
		}
		if (nrdecide == 'y') {
			negate_red(_array, col, depth);
		}
		if (ngdecide == 'y') {
			negate_green(_array, col, depth);
		}
		if (nbdecide == 'y') {
			negate_blue(_array, col, depth);
		}
		if (jrdecide == 'y') {
			flatten_red(_array, col);
		}
		if (jgdecide == 'y') {
			flatten_green(_array, col);
		}
		if (jbdecide == 'y') {
			flatten_blue(_array, col);
		}
		if (ecdecide == 'y') {
			extreme_contrast(_array, col, depth);
		}
		for (int i = 0; i < col; i++) {
			for (int j = 0; j < 3; j++) {
				outfile << _array[i][j] << " ";
			}
		}
	}
	outfile << endl;
	cout << filename << " created." << endl;

	myfile.close();
	outfile.close();

	system("pause");

	return 0;
}