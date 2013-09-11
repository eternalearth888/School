#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int negate_red(int r) {
	int n_r = (255 - r);
	return n_r;
}

int main() {
	string entry, copy, first;
	const int k = 3000;
	int length, depth, maxp, space;
	char grey, flip, neg_red, neg_green, neg_blue, just_red, just_green, just_blue;
	int arr[k];
	
	cout << "Enter name of image file: ";
	cin >> entry;
	cout << "Enter name of output file: ";
	cin >> copy;

	ifstream photo(entry);
	if (!photo) {
		cerr << "Error opening input file.\n";
		exit(1);
	}

	ofstream photo2(copy);
	if (!photo2) {
		cerr << "Error opening output file.\n";
		exit(1);
	}

	cout << "Here are your choices: \n" << "[1]  convert to greyscale [2]  flip horizontally \n" << "[3]  negative of red [4]  negative of green [5]  negative of blue \n" << "[6]  just the reds   [7]  just the greens   [8]  just the blues \n";
	cout << "Do you want [1]? (y/n)  ";
	cin >> grey;
	cout << "Do you want [2]? (y/n)  ";
	cin >> flip;
	cout << "Do you want [3]? (y/n)  ";
	cin >> neg_red;
	cout << "Do you want [4]? (y/n)  ";
	cin >> neg_green;
	cout << "Do you want [5]? (y/n)  ";
	cin >> neg_blue;
	cout << "Do you want [6]? (y/n)  ";
	cin >> just_red;
	cout << "Do you want [7]? (y/n)  ";
	cin >> just_green;
	cout << "Do you want [8]? (y/n)  ";
	cin >> just_blue;

	photo >> first >> length >> depth >> maxp;
	photo2 << first << " " << length << " " << depth << " " << maxp;

	if ((length * 3) < k) {
		while (!photo.eof()) {
			for (int i = 0; i < depth; i++) {
				for (int j = 0; j < length; j++) {
					photo >> arr[i];
					if (neg_red == 'y' || neg_green == 'y' || neg_blue == 'y') {   // invert a color
						if (neg_red == 'y') {
							space = 0;
							if (j % 3 == space) {
							arr[i] = negate_red(arr[i]);
							}
						}else if (neg_green == 'y') {
							space = 1;
							if (j % 3 == space) {
							arr[i] = negate_red(arr[i]);
							}
						}else if (neg_blue == 'y') {
							space = 2;
							if (j % 3 == space) {
							arr[i] = negate_red(arr[i]);
							}
						}
					} 
					if (just_red == 'y' || just_green == 'y' || just_blue == 'y') {   // zero a color
						if (just_red == 'y') {
							space = 0;
							if (j % 3 == space) {
							arr[i] = 0;
							}
						}else if (just_green == 'y') {
							space = 1;
							if (j % 3 == space) {
							arr[i] = 0;
							}
						}else if (just_blue == 'y') {
							space = 2;
							if (j % 3 == space) {
							arr[i] = 0;
							}
						}
					}
					photo2 << " " << arr[i];

				
				}

				//supposed to be for the greyscale and horizontal flip
				/*
				for (int m = 0; m < length; m += 3) {
					int ave = ((arr[m] + arr[m + 1] + arr[m + 2])/3);
					photo2 << " " << ave << " " << ave << " " << ave;
				}
				for (int m = length - 1; m >= 0; m -= 3) {
					photo2 << " " << arr[m - 2] << " " << arr[m - 1] << " " << arr[m];
				}*/
			}
		}
	}

	cout << copy << " was created." << endl;

	photo.close();
	photo2.close();

    // Exit program.
    return 0;

}