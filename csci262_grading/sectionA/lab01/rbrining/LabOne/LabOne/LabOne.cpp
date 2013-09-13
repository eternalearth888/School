
// project for reading PPM files
// Author: Richmond Brininger

#include <iostream>
#include <fstream>
#include <string>


using namespace std;



int negate_red(int red, int debth)
{
	red = debth - red;
	return red;
}

int negate_green(int green, int debth)
{
	green = debth - green;
	return green;
}

int negate_blue(int blue, int debth)
{
	blue = debth - blue;

	return blue;
}

void flip_horizontal(int** switched, int columbs){
	int **list = new int*[1000];
	for(int i=0; i<1000; i++){
		list[i] = new int[3];
	}
	for(int i = 0; i < columbs; i++){
		for(int j = 0; j < 3; j++){
			list[i][j] = switched[columbs-i][j];
		}
	}
	for(int i = 0; i < columbs; i++){
		for(int j = 0; j < 3; j++){
			switched[i][j] = list[i][j];
		}
	}
	delete list;
}


int grey_scale(int red, int green, int blue){
	int grey = 0;
	grey = (red+green+blue)/3;
	return grey;
}

int flatten_red(){
	int red = 0;
	return red;
}

int flatten_green(){
	int green = 0;
	return green;
}

int flatten_blue(){
	int blue = 0;
	return blue;
}

void horizontal_blur(int** switched, int columbs){

	for (int i = 0; i < columbs-3; i++){
		switched[i][0] = (switched[i][0]+switched[i+1][0]+switched[i+2][0])/3;
	}
	for(int i = columbs; i > 4; i--){
		switched[i][0] = (switched[i][0] + switched[i-1][0] + switched[i-2][0])/3;
	}
	for (int i = 0; i < columbs-3; i++){
		switched[i][1] = (switched[i][1]+switched[i+1][1]+switched[i+2][1])/3;
	}
	for(int i = columbs; i > 4; i--){
		switched[i][1] = (switched[i][1] + switched[i-1][1] + switched[i-2][1])/3;
	}
	for (int i = 0; i < columbs-3; i++){
		switched[i][2] = (switched[i][2]+switched[i+1][2]+switched[i+2][2])/3;
	}
	for(int i = columbs; i > 4; i--){
		switched[i][2] = (switched[i][2] + switched[i-1][2] + switched[i-2][2])/3;
	}
}

void extreme_contrast(int** switched, int columbs, int debth){
	for(int i = 0; i < columbs; i++){
		if (switched[i][0] < debth/2){
			switched[i][0] = 0;
		}else{
			switched[i][0] = debth;
		}
		if (switched[i][1] < debth/2){
			switched[i][1]= 0;
		}else{
			switched[i][1] = debth;
		}
		if (switched[i][2] < debth/2){
			switched[i][2] = 0;
		}else{
			switched[i][2] = debth;
		}
	}
}


int main(){
	
	string output;
	string input;
	string type;



	cout << "Portable Pixmap (PPM) Image Editor!\n\nEnter name of image file: ";
	cin >> input;
	cout << "\n\nEnter name of output file: ";
	cin >> output;
	int columbs;
	int rows;
	int main[1000][3];
	int debth;
	char one = 'n';
	char two = 'n';
	char three = 'n';
	char four = 'n';
	char five = 'n';
	char six = 'n';
	char seven = 'n';
	char eight = 'n';
	char nine = 'n';
	char ten = 'n';

	cout << "Here are your choices:\n";
	cout << "[1] convert to greyscale  [2] flip horizontally\n[3] negative of red  [4] negative of green  [5] negative of blue\n[6] just the reds  [7] just the greens  [8] just the blues  [9] horizontal blur\n[10] extreme_contrast\n\n";

	cout << "Do you want [1]? (y/n) ";
	cin >> one;
	cout << "\nDo you want [2]? (y/n) ";
	cin >> two;
	cout << "\nDo you want [3]? (y/n) ";
	cin >> three;
	cout << "\nDo you want [4]? (y/n) ";
	cin >> four;
	cout << "\nDo you want [5]? (y/n) ";
	cin >> five;
	cout << "\nDo you want [6]? (y/n) ";
	cin >> six;
	cout << "\nDo you want [7]? (y/n) ";
	cin >> seven;
	cout << "\nDo you want [8]? (y/n) ";
	cin >> eight;
	cout << "\nDo you want [9]? (y/n) ";
	cin >> nine;
	cout << "\nDo you want [10]? (y/n) ";
	cin >> ten;

	
	ifstream inFile(input.c_str());

	if (!inFile){
		cout <<"Error opening file"<<endl;
		system("pause");
		return 0;
	}


	ofstream outFile(output.c_str());

	inFile >> type;
	inFile >> columbs;
	inFile >> rows;
	inFile >> debth;
	outFile << type <<'\n'<<columbs << " " << rows << '\n' << debth << '\n';

	for(int i = 0; i < rows; i++){ 

		for(int i = 0; i < columbs; i++){
			for(int j = 0; j < 3; j++){
				inFile >> main[i][j];
			}
		}

		if(one == 'y'){
			for(int i = 0; i < columbs; i++){
				int grey = 0;
				grey = grey_scale(main[i][0],main[i][1],main[i][2]);
				main[i][0]=grey;
				main[i][1]=grey;
				main[i][2]=grey;
			}
		}
		if(two == 'y'){
			int **switched = new int*[1000];
				for(int i=0; i<1000; i++){
					switched[i] = new int[3];
				}
			for(int i = 0; i < columbs; i++){
				for (int j = 0; j < 3; j++){
					switched[i][j] = main[i][j];
				}
			}
			flip_horizontal(switched, columbs);

			for(int i = 0; i < columbs; i++){
				for (int j = 0; j < 3; j++){
					main[i][j] = switched[i][j];
				}
			}
			delete switched;
		}

		if(three == 'y'){
			for(int i = 0; i < columbs; i++){
			main[i][0] = negate_red(main[i][0], debth);
			}
		}

		if(four == 'y'){
			for(int i = 0; i < columbs; i++){
			main[i][1] = negate_green(main[i][1], debth);
			}
		}

		if(five == 'y'){
			for(int i = 0; i < columbs; i++){
			main[i][2] = negate_blue(main[i][2], debth);
			}
		}

		if(six == 'y'){
			for(int i = 0; i < columbs; i ++){
				main[i][1] = flatten_green();
				main[i][2] = flatten_blue();
			}
		}
		if(seven == 'y'){
			for(int i = 0; i < columbs; i ++){
				main[i][0] = flatten_red();
				main[i][2] = flatten_blue();
			}
		}
		if(eight == 'y'){
			for(int i = 0; i < columbs; i ++){
				main[i][0] = flatten_red();
				main[i][1] = flatten_green();
			}
		}

		if(nine == 'y'){
			int **switched = new int*[1000];
				for(int i=0; i<1000; i++){
					switched[i] = new int[3];
				}
			for(int i = 0; i < columbs; i++){
				for (int j = 0; j < 3; j++){
					switched[i][j] = main[i][j];
				}
			}
			horizontal_blur(switched, columbs);

			for(int i = 0; i < columbs; i++){
				for (int j = 0; j < 3; j++){
					main[i][j] = switched[i][j];
				}
			}
			delete switched;
		}

		if (ten == 'y'){ 
			int **switched = new int*[1000];
				for(int i=0; i<1000; i++){
					switched[i] = new int[3];
				}
			for(int i = 0; i < columbs; i++){
				for (int j = 0; j < 3; j++){
					switched[i][j] = main[i][j];
				}
			}
			extreme_contrast(switched, columbs, debth);

			for(int i = 0; i < columbs; i++){
				for (int j = 0; j < 3; j++){
					main[i][j] = switched[i][j];
				}
			}
			delete switched;
		}




		
		for(int i = 0; i < columbs; i++){
			for(int j = 0; j < 3; j++){
				outFile << main[i][j] << " ";
			}
			outFile << '\n';
		}
	}

	inFile.close();
	outFile.close();

	
	system ("pause");
	return 0;
}

