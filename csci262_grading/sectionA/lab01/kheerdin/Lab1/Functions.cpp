//This file contains basic effects used
#include "string"
#include <iostream>
#include "Functions.h"

using namespace std;

//Reverses Color Value
int negate(int value, int maxcolor) {
		value = maxcolor - value;
	return value;
}
//Sets Color Value to 0
int flatten() {
	return 0;
}
//Averages Color Value
int greyscale(int red, int green, int blue){
	int avg = (red + blue + green)/3;
	return avg, avg, avg;
}
//For Effects Menu
bool ask(string question){
	char answer;
	cout << question << " " << endl;
	cin >> answer;
	if (answer == 'Y' || answer == 'y')
		return(1);
	else if (answer == 'N' || answer == 'n')
		return(0);
}
