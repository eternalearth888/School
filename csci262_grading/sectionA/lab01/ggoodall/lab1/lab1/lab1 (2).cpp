#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

const int max_pixels = 3000;

 int main(){
	 char output[max_pixels];
	 char input[3000];
	 //string input;
	 //string output;
	 int colors[max_pixels];

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
			
			while(!ppmfile.eof())
			 {
				ppmfile >> input;
				cout << input;
				out<<input;
			 }
			 ppmfile.close();
			 out.close();
		 }
	 }

	 system("PAUSE");

	 return 0;
 }