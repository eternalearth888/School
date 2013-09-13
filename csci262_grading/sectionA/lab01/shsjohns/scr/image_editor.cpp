//This program was created by Shawn Johnson

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void negate_red(int colors[3000], int column){
	for( int i = 0; i < (column*3); i = i + 3){
		colors[i]= 255-colors[i];
	}
}

void negate_green(int colors[3000], int column){
	for( int i = 1; i < (column*3); i = i + 3){
		colors[i]= 255-colors[i];
	}
}

void negate_blue(int colors[3000], int column){
	for( int i = 2; i < (column*3); i = i + 3){
		colors[i]= 255-colors[i];
	}
}

void flip_horizontally(int colors[3000], int column){
	int *temp = new int[(column*3)];
	for( int i = 0, j = 1; i < (column * 3); i = i + 3 , j++){		
		temp[i]=colors[3*(column-j)];
		temp[i + 1]=colors[3*(column-j) + 1];
		temp[i + 2]=colors[3*(column-j) + 2];	
	}
	for (int i = 0; i < (column * 3); i++){
		colors[i] = temp[i];
	}
	delete[] temp;
}

void grey_scale(int colors[3000], int column){
	int average;
	for( int i = 0; i < (column*3); i = i + 3){
		average = (colors[i] + colors[i + 1] + colors[i + 2])/3;
		colors[i] = colors[i + 1] = colors[i + 2] = average;
	}
}

void flatten_red(int colors[3000], int column){
	for( int i = 0; i < (column*3); i = i + 3){
		colors[i]= 0;
	}
}

void flatten_green(int colors[3000], int column){
	for( int i = 1; i < (column*3); i = i + 3){
		colors[i]= 0;
	}
}

void flatten_blue(int colors[3000], int column){
	for( int i = 2; i < (column*3); i = i + 3){
		colors[i]= 0;
	}
}

int main(){
	string image_file, output_file;
	char c,o1,o2,o3,o4,o5,o6,o7,o8;
	int row, column, max_color, colors[3000], temp, i=0;

	cout << "Enter the name of the image file (.ppm at the end): ";
	cin >> image_file;
	cout << "Enter the name of the output file (.ppm at the end): ";
	cin >> output_file;
	cout << "You can change the original picture by the following options \n";
	cout << "1. negatives of red? (y/n): ";
	cin >> o1;
	cout << "2. negatives of green? (y/n): ";
	cin >> o2;
	cout << "3. negatives of blue? (y/n): ";
	cin >> o3;
	cout << "4. grey scale it? (y/n): ";
	cin >> o4;
	cout << "5. just red? (y/n): ";
	cin >> o5;
	cout << "6. just green? (y/n): ";
	cin >> o6;
	cout << "7. just blues? (y/n): ";
	cin >> o7;
	cout << "8. flip horizontally? (y/n): ";
	cin >> o8;

	ifstream myfile(image_file.c_str());
	ofstream output(output_file.c_str());
	if (!myfile){
		cout << "Error in opening input file. \n";
		system("PAUSE");
		return 0;
	}
	if(!output){
		cout << "Error in opening output file. \n";
		return 0;
	}
	
	// gets first line
	while (myfile.get(c)){
		if(c == '\n'){
			output << "\n";
			break;
		}else{
			output << c;
		}
	}
	// puts next to lines
	while(myfile >> temp){
		if (i == 0){
			column = temp;
			output << temp << " ";
		}else if (i == 1){
			row = temp;
			output << temp << "\n";
		}else if(i == 2){
			max_color = temp;
			output << temp << "\n";
			break;
		}
		i++;
	}
	
	i=0;

	if ((row*3) > 3000){
		cout <<  "Picture size is too large. \n";
	}else{
		while (myfile >> temp){
			colors[i]=temp;
			i++;
			if(i % (row * 3) == 0){
				if( o1 == 'y' || o1 == 'Y'){
					negate_red(colors, column);
				}
				if( o2 == 'y' || o2 == 'Y'){
					negate_green(colors, column);
				}
				if( o3 == 'y' || o3 == 'Y'){
					negate_blue(colors, column);
				}
				if( o4 == 'y' || o4 == 'Y'){
					grey_scale(colors,column);
				}
				if( o5 == 'y' || o5 == 'Y'){
					flatten_blue(colors,column);
					flatten_green(colors,column);
				}
				if( o6 == 'y' || o6 == 'Y'){
					flatten_blue(colors,column);
					flatten_red(colors,column);
				}
				if( o7 == 'y' || o7 == 'Y'){
					flatten_red(colors,column);
					flatten_green(colors,column);
				}
				if( o8 == 'y' || o8 == 'Y'){
					flip_horizontally(colors,column);
				}
				//functions
				for( int j = 0; j < (row * 3); j++){
					output << colors[j] << " ";
				}
				i = 0;
				output << "\n";
			}
		}
	}
	myfile.close();
	output.close();


	system("PAUSE");
	return 0;
}