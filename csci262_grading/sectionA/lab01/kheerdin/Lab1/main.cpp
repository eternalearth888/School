#include "string"
#include <iostream>
#include <fstream>
#include "Functions.h"
using namespace std;

const int BUFFER_SIZE = 4000;


int main() {
	int buffer[BUFFER_SIZE];
	int columns, rows, maxcolor;
	string filename, type;
	string newfile;

	//Menu
	cout << "Enter input filename: " << endl;
	cin >> filename;

	cout << "Enter new filename: " << endl;
	cin >> newfile;

	//File Check
	ifstream input(filename.c_str());

	ofstream output(newfile);

	if (!input) {
		cout << "Could not read file.\n";
		return(1);
	}
		
	//Stores header
	input >> type >> columns >> rows >> maxcolor; 

	if(columns * 3 > BUFFER_SIZE){
		cout << "File is too big!" << endl;
		return(2);
	}

	//Writes Header to File
	output << type << endl << columns << " " << rows << endl << maxcolor << endl ;
	//Effects Menu

	bool negate_red = ask("Negate Red? (Y/N)");
	bool negate_green = ask("Negate Green? (Y/N)");
	bool negate_blue = ask("Negate Blue? (Y/N)");
	bool flatten_red = ask("Flatten Red? (Y/N)");
	bool flatten_green = ask("Flatten Green? (Y/N)");
	bool flatten_blue = ask("Flatten Blue? (Y/N)");
	bool grey_scale = ask("Greyscale? (Y/N)");
	bool flip_horizontal = ask("Flip Horizontal? (Y/N)");
	
	//Da Magicks
	for(int j = 0; j < rows; j++){
		 //Reads in File for one row of ints
		  for(int i = 0; i < columns * 3; i++){
			  input >> buffer[i];
		  }
		 //Modifies File
		  if(negate_red) {
			  int i;
			  for(i = 0; i < columns * 3; i += 3) {
				 buffer[i] = negate(buffer[i], maxcolor);
			  }
		  }
		  if(negate_green) {
			  for(int i = 1; i < columns * 3; i += 3) 
				 buffer[i] = negate(buffer[i], maxcolor);
		  }
		  if(negate_blue) {
			  for(int i = 2; i < columns * 3; i += 3) 
				 buffer[i] = negate(buffer[i], maxcolor);
		  }
		  if(flatten_red) {
			  for(int i = 0; i < columns * 3; i += 3) 
				 buffer[i] = 0;
		  }
		  if(flatten_green) {
			  for(int i = 1; i < columns * 3; i += 3) 
				 buffer[i] = flatten();
		  }
		  if(flatten_blue) {
			  for(int i = 2; i < columns * 3; i += 3) 
				 buffer[i] = flatten();
		  }
		  if(grey_scale) {
			  for(int i = 0; i < columns * 3; i += 3){
				  int g = greyscale(buffer[i], buffer[i+1], buffer[i+2]);  
				  buffer[i] = g;
				  buffer[i+1] = g;
				  buffer[i+2] = g;
			  }
		  }
		  if(flip_horizontal) {
			  int temp[BUFFER_SIZE];
			  int j = 0;
			  for (int i = (columns * 3) - 1; i >= 0; i -= 3) { 
				  temp[j] = buffer[i - 2];
				  temp[j + 1] = buffer[i - 1];
				  temp[j + 2] =  buffer[i];
				  j = j + 3;
			  }
			  for (int i = 0; i < columns * 3; i++){
				  buffer[i] = temp[i];
			  }
		  }

		 //Outputs File
		  for(int k = 0; k < columns * 3; k++){
			  if (k % 15 == 0)
				output << buffer[k] << endl;
			  else
				   output << buffer[k] << " ";
		  }
	 }
	//Closes Streams
	input.close();
	output.close();

	return(0);
}
