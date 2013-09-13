#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
void negate_red( int** arr, int cols)
{
	for(int i = 0; i<cols; i++)
	{
		arr[i][0] = 255 - arr[i][0];
	}
}
void negate_green( int** arr, int cols)
{
	for(int i = 0; i<cols; i++)
	{
			arr[i][1] = 255 - arr[i][1];
				
			
	}
}
void negate_blue( int** arr, int cols)
{
	for(int i = 0; i<cols; i++)
	{
			arr[i][2] = 255 - arr[i][2];
	}
}
void flip_horizontal( int** arr, int cols)
{
	int** out_arr=0;
	out_arr = new int*[1000];
	for(int i=0; i<1000; i++){
		out_arr[i] = new int[3];
	}
	for(int i=0; i<cols; i++)
	{
		for(int j=0; j<3; j++)
		{
				out_arr[cols-i-1][j] = arr[i][j];
		}
	}
	for(int i = 0; i < cols; i++)
	{
		for(int j = 0; j < 3; j++)
		arr[i][j] = out_arr[i][j];
	}
}
void grey_scale( int** arr, int cols)
{


	for(int i=0; i<cols; i++)
	{
		double avg = double( arr[i][0] + arr[i][1] + arr[i][2] )/3;
	
			arr[i][0] = avg;
			arr[i][1] = avg;
			arr[i][2] = avg;
	}

}
void flatten_red( int** arr, int cols)
{
	for(int i = 0; i<cols; i++)
	{
			arr[i][0] = 0;
	}
}
void flatten_green( int** arr, int cols)
{
	for(int i = 0; i<cols; i++)
	{
			arr[i][1] = 0;
	}
}
void flatten_blue( int** arr, int cols)
{
	for(int i = 0; i<cols; i++)
	{
			arr[i][2] = 0;
	}
}
int main(){
	
	string input;
	string output;
	int x;
	cout << "please enter input file name: \n";
	cin >> input;	
	ifstream infile( input.c_str() );
	cout << "please enter output file name: \n";
	cin >> output;
    ofstream outfile( output.c_str() );
	if(!infile)
	{
		cerr << "Error\n";
		exit(1);
	}
	string f_name;
	int cols;
	int rows;
	int color;
	infile >> f_name;
	infile >> cols;
	infile >> rows;
	infile >> color;
	outfile << f_name<< endl;
	outfile << cols << " ";
	outfile << rows << endl;
	outfile << color <<endl;
	int** arr=0;
	arr = new int*[1000];
	for(int i=0; i<1000; i++){
		arr[i] = new int[3];
	}
	char c[8];
	cout << "Here are your choices:"<<endl<<
			"[1]  convert to greyscale [2]  flip horizontally" << endl <<
			"[3]  negative of red [4]  negative of green [5]  negative of blue" << endl <<
			"[6]  just the reds   [7]  just the greens   [8]  just the blues"<< endl;
	for (int i=0; i<8; i++)
	{
	cout <<"Do you want "<<"["<<i+1<<"]"<<"? (y/n)";
	cin >> c[i];
	}
		for(int i = 0; i < rows; i++)
		{
			if ( 3 * cols >= 3000)
				cout << "Size of file is too big";
			else
			{
				for(int k = 0; k < cols; k++){
					for( int j = 0; j < 3; j++ )
					{
						infile >> arr[k][j];
					}
				}
			}

				
				
				if (c[0]=='y')
					grey_scale( arr, cols);
				else if(c[1]=='y')
					flip_horizontal(arr, cols);
				else if(c[2]=='y')
					 negate_red(  arr, cols);
				else if(c[3]=='y')
					 negate_green(  arr, cols);
				else if(c[4]=='y')
					 negate_blue(  arr, cols);
				else if(c[5]=='y')
					 flatten_red(  arr, cols);
				else if(c[6]=='y')
					 flatten_green(  arr, cols);
				else if(c[7]=='y')
					 flatten_blue(  arr, cols);

				for(int i = 0; i < cols; i++)
				{
					for( int j = 0; j < 3; j++ )
						outfile << arr[i][j] <<" ";
					outfile << endl;
				}
		}
		
	infile.close();
	outfile.close();
	

	system( "pause" );
	return 0;
}