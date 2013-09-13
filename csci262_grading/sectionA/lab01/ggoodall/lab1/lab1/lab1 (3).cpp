#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

const int max_pixels = 3000;

 int main(){
	 char output[max_pixels];
	 char input[3000];
	 int aray[3000];
	 //string input;
	 //string output;
//	 int colors[max_pixels];

	 ifstream ppmfile(input);
	 {
		 cout << "Please enter an input file name." << endl;
		 cin >> input;
		 ppmfile.open(input);
	 
		 if (!input)
		 {
			 cout << "The file cannot be opened" << endl;
			 ppmfile.close();
		 }
		 else
		 {

			ofstream out;
			cout <<"Please enter an output file name." << endl;
			cin >> output;
			out.open (output);
			
				 string p; //p3
				 int rows, cols,num;
				//ppmfile>>p;
				ppmfile>>p;
				ppmfile>>cols;
				ppmfile>>rows;
				ppmfile>>num;
				out<<p<<endl;
				out<<cols<<" ";
				out<<rows<<endl;
				out<<num<<endl;

				for(int i = 0; i<rows; i++)
				{
					if(3*cols>=3000)
					{
						cout<<"File is too big";
					}
					else
					{
						for (int i =0; i<3*cols;i++)
						{
							ppmfile >> num;
							aray[i]= num;
						}

						for (int i =0; i<3*cols;i++)
						{
							out << aray[i]<<" ";
							
						}
						out<<endl;
					}
				}
			 ppmfile.close();
			 out.close();
		 }
		 }
	

	 system("PAUSE");

	 return 0;
 }