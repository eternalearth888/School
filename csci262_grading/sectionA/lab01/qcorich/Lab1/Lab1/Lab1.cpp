// Lab1.cpp : Defines the entry point for the console application.
//
// Quentin Corich

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int ROWSIZE = 16;

int negate_red(int arr[]){
	for(int i = 0; i < ROWSIZE; i++){
		if((arr[i] % 3) == 0){
			arr[i] = 255 - arr[i];
		}
}
	return arr[ROWSIZE];
}
int negate_green(int arr[]){
	for(int i = 0; i < ROWSIZE; i++){
		if(((arr[i] - 1) % 3) == 0){
			arr[i] = 255 - arr[i];
		}
}
	return arr[ROWSIZE];
}
int negate_blue(int arr[]){
	for(int i = 0; i < ROWSIZE; i++){
		if(((arr[i] - 2) % 3) == 0){
			arr[i] = 255 - arr[i];	
		}
}
	return arr[ROWSIZE];
}
int flip_horizontal(int arr[]){
	for(int i = 0; i < (ROWSIZE / 2); i++){
			int a;
			int b;
			a = arr[i];
			b = arr[ROWSIZE - i];
			arr[i] = b;
			arr[ROWSIZE - i] = a;
	}
	return arr[ROWSIZE];
}
int greyscale(int arr[]){
	for(int i = 0; i < ROWSIZE; i ++){
		arr[i] = arr[i] /127;
	}
	return arr[ROWSIZE];
}
int flatten_red(int arr[]){
	for(int i = 0; i < ROWSIZE; i++){
		if((arr[i] % 3) == 0){
			arr[i] = 0;
		}
}
	return arr[ROWSIZE];
}
int flatten_green(int arr[]){
	for(int i = 0; i < ROWSIZE; i++){
		if(((arr[i] - 1) % 3) == 0){
			arr[i] = 0;
		}
}
	return arr[ROWSIZE];
}
int flatten_blue(int arr[]){
	for(int i = 0; i < ROWSIZE; i++){
		if(((arr[i] - 2) % 3) == 0){
			arr[i] = 0;
		}
}
	return arr[ROWSIZE];
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	string filename;
	string copy;
	int info = 0;
	bool ired, igreen, iblue = false;
	char a, b, c, d, e, f, g, h = 'a';
	bool horizontal = false;
	bool grey = false;
	bool fred, fgreen, fblue = false;

	cout << "Hello, type the name of the picture you want coppied: ";
	cin >> filename;
	cout << "Create a name for the copy: ";
	cin >> copy;
	copy = filename + "_clone";
	cout <<"Would you like to inverse red?(y/n) ";
	cin >> a;
	while(a != 'y' || a != 'n'){
		cout << "Could not recognize, please re-enter choice (y/n): ";
		cin >> a;
	}
	if(a == 'y'){
		ired = true;
	}
	cout <<"Would you like to inverse green?(y/n) ";
	cin >> b;
	while(b != 'y' || b != 'n'){
		cout << "Could not recognize, please re-enter choice (y/n): ";
		cin >> b;
	}
	if(b == 'y'){
		igreen = true;
	}
	cout <<"Would you like to inverse blue?(y/n) ";
	cin >> c;
	while(c != 'y' || c != 'n'){
		cout << "Could not recognize, please re-enter choice (y/n): ";
		cin >> c;
	}
	if(c == 'y'){
		iblue = true;
	}
	cout <<"Would you like to flip the picture horizontally?(y/n) ";
	cin >> d;
	while(d != 'y' || d != 'n'){
		cout << "Could not recognize, please re-enter choice (y/n): ";
		cin >> d;
	}
	if(d == 'y'){
		horizontal = true;
	}
	cout <<"Would you like to use grey scale?(y/n) ";
	cin >> e;
	while(e != 'y' || e != 'n'){
		cout << "Could not recognize, please re-enter choice (y/n): ";
		cin >> e;
	}
	if(e == 'y'){
		grey = true;
	}
	cout <<"Would you like to remove all red?(y/n) ";
	cin >> f;
	while(f != 'y' || f != 'n'){
		cout << "Could not recognize, please re-enter choice (y/n): ";
		cin >> f;
	}
	if(f == 'y'){
		fred = true;
	}
	cout <<"Would you like to remove all green?(y/n) ";
	cin >> g;
	while(g != 'y' || g != 'n'){
		cout << "Could not recognize, please re-enter choice (y/n): ";
		cin >> g;
	}
	if(g == 'y'){
		fgreen = true;
	}
	cout <<"Would you like to remove all blue?(y/n) ";
	cin >> h;
	while(h != 'y' || h != 'n'){
		cout << "Could not recognize, please re-enter choice (y/n): ";
		cin >> h;
	}
	if(h == 'y'){
		fblue = true;
	}

	ifstream picture(filename.c_str());
	ofstream clone(copy.c_str());

	if(!picture){
		cerr << "Error opening file.\n";
		exit(1);
	}
	if(!clone){
		cerr << "Error creating file.\n";
		exit(1);
	}

	int data[ROWSIZE];

	while(!picture.eof()){
		for(int i = 0; i < ROWSIZE; i++){
		data[i] = info;
		}

		if(ired){
			data[ROWSIZE] = negate_red(data);
		}else if(igreen){
			data[ROWSIZE] = negate_green(data);
		}else if(iblue){
			data[ROWSIZE] = negate_blue(data);
		}else if(horizontal){
			data[ROWSIZE] = flip_horizontal(data);
		}else if(grey){
			data[ROWSIZE] = greyscale(data);
		}else if(fred){
			data[ROWSIZE] = flatten_red(data);
		}else if(fgreen){
			data[ROWSIZE] = flatten_green(data);
		}else if(fblue){
			data[ROWSIZE] = flatten_blue(data);
		}

		for(int j = 0; j < ROWSIZE; j++){
			cout << data[j] << " ";
		}
		cout << endl;
	}
	picture.close();
	clone.close();
	return 0;
}

