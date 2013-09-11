#include <iostream>
#include <fstream>
#include <string> 
#include <cmath>

using namespace std;

int *arr; 
int rows, cols, colordepth; 
char *choices; 

void negate_red()
{
	for(int x = 0; x < 3*cols; x += 3)
	{
		arr[x] = abs(arr[x] - 255);
	}
}

void negate_green()
{
	for(int x = 1; x < 3*cols; x += 3)
	{
		arr[x] = abs(arr[x] - 255);
	}
}

void negate_blue()
{
	for(int x = 2; x < 3*cols; x += 3)
	{
		arr[x] = abs(arr[x] - 255);
	}
}

void flip_horizontal()
{
	int *temp = new int[3*cols];
	int y = 0; 
	
	for(int x = 3*cols-3; x >=0; x-=3)
	{
		temp[y] = arr[x];
		temp[y+1] = arr[x+1];
		temp[y+2] = arr[x+2]; 

		y+=3; 
	} 

	delete [] arr; 
	arr = temp; 
}

void grey_scale()
{
	int y = 0; 
	int avg = 0; 
	
	for(int x = 0; x < 3*cols; x+=3)
	{
		avg = (arr[x] + arr[x+1] + arr[x+2])/3; 
		arr[x] = avg; 
		arr[x+1] = avg; 
		arr[x+2] = avg; 
	} 
}

void flatten_red()
{
	for(int x = 0; x < 3*cols; x += 3)
	{
		arr[x] = 0;
	}
}

void flatten_green()
{
	for(int x = 1; x < 3*cols; x += 3)
	{
		arr[x] = 0;
	}
}

void flatten_blue()
{
	for(int x = 2; x < 3*cols; x += 3)
	{
		arr[x] = 0;
	}
}

void extreme_contrast()
{
	int half = colordepth/2; 

	for(int x = 0; x < 3*cols; x++)
	{
		if(arr[x] > half)
			arr[x] = colordepth; 

		else
			arr[x] = 0; 
	}
}

void display_menu()
{
	choices = new char[9];

	cout << "Here are your choices:" << endl; 
	cout << "[1]  convert to greyscale [2]  flip horizontally" << endl;
	cout << "[3]  negative of red [4]  negative of green [5]  negative of blue" << endl;
	cout << "[6]  just the reds   [7]  just the greens   [8]  just the blues" << endl;
	cout << "[9]  extreme contrast" << endl;
	cout << endl;
	cout << "Do you want [1]? (y/n) ";
	cin >> choices[0]; 
	cout << "Do you want [2]? (y/n) ";
	cin >> choices[1]; 
	cout << "Do you want [3]? (y/n) ";
	cin >> choices[2]; 
	cout << "Do you want [4]? (y/n) ";
	cin >> choices[3]; 
	cout << "Do you want [5]? (y/n) ";
	cin >> choices[4]; 
	cout << "Do you want [6]? (y/n) ";
	cin >> choices[5]; 
	cout << "Do you want [7]? (y/n) ";
	cin >> choices[6]; 
	cout << "Do you want [8]? (y/n) ";
	cin >> choices[7]; 
	cout << "Do you want [9]? (y/n) "; 
	cin >> choices[8]; 
	cout << endl;
}

void selected_choices()
{

	if(choices[1] == 'y')
		flip_horizontal(); 

	if(choices[2] == 'y')
		negate_red();
	
	if(choices[3] == 'y')
		negate_green();

	if(choices[4] == 'y')
		negate_blue();

	if(choices[5] == 'y')
		flatten_red();

	if(choices[6] == 'y')
		flatten_green();

	if(choices[7] == 'y')
		flatten_blue();

	if(choices[8] == 'y')
		extreme_contrast();

	if(choices[0] == 'y')
		grey_scale();
}

int main()
{
	string inFile, outFile; 

	cout << "Portable Pixmap (PPM) Image Editor!" << endl; 
	cout << endl;
	cout << "Enter the name of image file: "; 
	cin >> inFile;
	cout << "Enter the name of output file: "; 
	cin >> outFile; 

	ifstream reader; 
	reader.open(inFile);

	if(!reader.is_open())
	{
		cout << "Could not open file." << endl;
		system("pause"); 
		return 0; 
	}

	int header[3];
	char type[2];
	int x = 0;
	
	ofstream writer; 
	writer.open(outFile); 

	//read and write header
	reader >> type[0]; 
	reader >> type[1]; 

	writer << type[0] << type[1] << "	" << endl; 

	reader >> header[0]; 
	reader >> header[1]; 
	reader >> header[2]; 

	writer << header[0] << "	" << header [1] << "	" << endl;
	writer << header[2] << endl;

	cols = header[0]; 
	rows = header[1]; 
	colordepth = header[2];

	display_menu();

	cout << "creating file..." << endl; 

	//get the rest of the file 
	arr = new int[3000];

	while(reader.good())
	{
		for(int r = 1; r <= rows; r++)
		{
			for(int c = 0; c < 3*cols; c++)
			{
				 reader >> arr[c];  
			}

			selected_choices(); 

			for(int x = 0; x < 3*cols; x++)
			{			 
				writer << arr[x] << " ";  
			}
		}		
	}
	reader.close();
	writer.close();

	cout << outFile << " created." << endl; 

	system("pause");
	return 0; 
}