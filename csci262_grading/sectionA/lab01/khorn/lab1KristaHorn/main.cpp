#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
const int MAX = 3000;

int* negate_red (int, int[], int);
int* negate_green (int, int[], int);
int* negate_blue (int, int[], int);
int* flatten_red (int, int[]);
int* flatten_green (int, int[]);
int* flatten_blue (int, int[]);
int* grey_scale (int[], int);
int* flip_horizontal (int, int[]);

int main() {
	string input_file_name;
	string output_file_name;
	string header;
	int rows, columns, max_color;
	int temp_color;
	int yes_count = 0;
	char one_answer, two_answer, three_answer, four_answer, five_answer, six_answer, seven_answer, eight_answer;
	
	cout << "Enter input file name: ";
	cin >> input_file_name;

	ifstream file(input_file_name);
	if (!file) {
		cerr << "Trouble finding file." << endl;
		exit(1);
	}

	cout << "Enter output file name: ";
	cin >> output_file_name;

	ofstream output_file(output_file_name);
	if(!output_file)
		cout << "Trouble creating file.";

	cout << "Here are your choices: " << endl;
	cout << "[1]  convert to greyscale [2]  flip horizontally" << endl;
	cout << "[3]  negative of red [4]  negative of green [5]  negative of blue" << endl;
	cout << "[6]  just the reds   [7]  just the greens   [8]  just the blues" << endl;
	cout << "Do you want [1]? (y/n) ";
	cin >> one_answer;
	cout << "Do you want [2]? (y/n) ";
	cin >> two_answer;
	cout << "Do you want [3]? (y/n) ";
	cin >> three_answer;
	cout << "Do you want [4]? (y/n) ";
	cin >> four_answer;
	cout << "Do you want [5]? (y/n) ";
	cin >> five_answer;
	cout << "Do you want [6]? (y/n) ";
	cin >> six_answer;
	cout << "Do you want [7]? (y/n) ";
	cin >> seven_answer;
	cout << "Do you want [8]? (y/n) ";
	cin >> eight_answer;


	file >> header;
	file >> columns;

	if (columns > MAX) {
		cerr << "Too big." << endl;
		exit(2);
	}

	file >> rows;
	file >> max_color;

	int temp_array[MAX];
	int temp2_array[MAX];
	int input_array[MAX];

	output_file << header << endl;
	output_file << columns << endl;
	output_file << rows << endl;
	output_file << max_color << endl;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < (3 * columns); j++) {
			file >> temp_color;
			input_array[j] = temp_color;
		}
	
		for (int j = 0; j < (3 * columns); j++) {
			if (one_answer == 'y') {
				yes_count++;
				int *temp_array = grey_scale(input_array, columns);
				output_file << temp_array[j] << " ";
			}
			if (two_answer == 'y') {
				yes_count++;
				int *temp_array = flip_horizontal (columns, input_array);
				output_file << temp_array[j] << " ";
			}
			if (three_answer == 'y') {
				yes_count++;
				int *temp_array = negate_red (max_color, input_array, columns);
				output_file << temp_array[j] << " ";
			}
			if (four_answer == 'y') {
				yes_count++;
				int *temp_array = negate_green (max_color, input_array, columns);
				output_file << temp_array[j] << " ";
			}
			if (five_answer == 'y') {
				yes_count++;
				int *temp_array = negate_blue (max_color, input_array, columns);
				output_file << temp_array[j] << " ";
			}
			if (six_answer == 'y') {
				yes_count++;
				int *temp_array = flatten_green (columns, input_array);
				int *temp2_array = flatten_blue (columns, input_array);
				output_file << (temp_array[j] + temp2_array[j]) << " ";
			}
			if (seven_answer == 'y') {
				yes_count++;
				int *temp_array = flatten_red (columns, input_array);
				int *temp2_array = flatten_blue (columns, input_array);
				output_file << (temp_array[j] + temp2_array[j]) << " ";
			}
			if (eight_answer == 'y') {
				yes_count++;
				int *temp_array = flatten_green (columns, input_array);
				int *temp2_array = flatten_red (columns, input_array);
				output_file << (temp_array[j] + temp2_array[j]) << " ";
			}
			if (yes_count == 0)
				output_file << input_array[j] << " ";
		}
		output_file << endl;
	}

	cout << output_file_name << " created." << endl;

	output_file.close();
	file.close();

	system("pause");
	return 0;
}

int* negate_red (int max, int arr[], int columns) {
	int new_red;
	int temp_array[MAX];
	for (int i = 0; i < (3 * columns); i++) {
		if (i % 3 == 0) {
			if ((arr[i] - max) != 0)
				new_red = (arr[i] - max) * -1;
			else 
				new_red = arr[i] - max;
			temp_array[i] = new_red;
		}
		else
			temp_array[i] = arr[i];
	}
	return temp_array;
}

int* negate_green (int max, int arr[], int columns) {
	int new_green;
	int temp_array[MAX];
	for (int i = 0; i < (3 * columns); i++) {
		if (i % 3 == 1) {
			if ((arr[i] - max) != 0)
				new_green = (arr[i] - max) * -1;
			else 
				new_green = arr[i] - max;
			temp_array[i] = new_green;
		}
		else
			temp_array[i] = arr[i];
	}
	return temp_array;
}

int* negate_blue (int max, int arr[], int columns) {
	int new_blue;
	int temp_array[MAX];
	for (int i = 0; i < (3 * columns); i++) {
		if (i % 3 == 2) {
			if ((arr[i] - max) != 0)
				new_blue = (arr[i] - max) * -1;
			else 
				new_blue = arr[i] - max;
			temp_array[i] = new_blue;
		}
		else
			temp_array[i] = arr[i];
	}
	return temp_array;
}

int* flatten_red (int columns, int arr[]) {
	int temp_array[MAX];
	for (int i = 0; i < (3 * columns); i++) {
		if (i % 3 == 0) {
			temp_array[i] = 0;
		}
		else
			temp_array[i] = arr[i];
	}
	return temp_array;
}

int* flatten_green (int columns, int arr[]) {
	int temp_array[MAX];
	for (int i = 0; i < (3 * columns); i++) {
		if (i % 3 == 1) {
			temp_array[i] = 0;
		}
		else
			temp_array[i] = arr[i];
	}
	return temp_array;
}

int* flatten_blue (int columns, int arr[]) {
	int temp_array[MAX];
	for (int i = 0; i < (3 * columns); i++) {
		if (i % 3 == 2) {
			temp_array[i] = 0;
		}
		else
			temp_array[i] = arr[i];
	}
	return temp_array;
}

int* grey_scale (int new_array[], int columns) {
	int grey;
	int temp_array[MAX];
	for (int i = 0; i < ((3 * columns) - 2); i+=3) {
		grey = (new_array[i] + new_array[i + 1] + new_array[i + 2]) / 3;
		temp_array[i] = grey;
		temp_array[i + 1] = grey;
		temp_array[i + 2] = grey;
	}
	return temp_array;
}

int* flip_horizontal (int columns, int new_array[]) {
	int temp_array[MAX];
	int length_count = (columns * 3);
	for (int i = 0; i < ((3 * columns) - 2); i+=3) {
			temp_array[length_count - 2] = new_array[i + 1];
			temp_array[length_count - 1] = new_array[i + 2];
			temp_array[length_count] = new_array[i];
			length_count-=3;
	}
	return temp_array;
}