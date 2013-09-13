#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){

	//Welcome
	cout << "Portable Pixmap (PPM) Image Editor!\n";

	// Buffer Array
	int buffer[3000];
	
	//File I/O
	string magic = "";
	int x=0;
	int col, row, max;
	string choice = "";
	bool n_r =false;
	bool n_g =false;
	bool n_b =false;
	bool f_r=false;
	bool f_g=false;
	bool f_b=false;
	bool grey=false;
	bool flip=false;
	bool e_c=false;
	string feed_name = "";
	string out_name = "";
	cout << "Enter name of image file: ";
	cin >> feed_name;
	ifstream feed (feed_name.c_str());
	if (feed.is_open()){
		cout << "Enter name of output file: ";
		cin >> out_name;
		ofstream out (out_name.c_str());
		if (out.is_open()){
			cout << "Here are your choices:\n";
			cout << "[1] convert to greyscale\n[2] flip horizontally\n[3] negative of red\n[4] negative of green\n[5]  negative of blue\n[6]  flatten red\n[7]  flatten green\n[8]  flatten blue\n[9] extreme contrast\n\n";
			cout << "Do you want [1]? (y/n)\n";
			cin >> choice;
			if(choice=="y")
				grey=true;
			cout << "Do you want [2]? (y/n)\n";
			cin >> choice;
			if(choice=="y")
				flip=true;
			cout << "Do you want [3]? (y/n)\n";
			cin >> choice;
			if(choice=="y")
				n_r=true;
			cout << "Do you want [4]? (y/n)\n";
			cin >> choice;
			if(choice=="y")
				n_g=true;
			cout << "Do you want [5]? (y/n)\n";
			cin >> choice;
			if(choice=="y")
				n_b=true;
			cout << "Do you want [6]? (y/n)\n";
			cin >> choice;
			if(choice=="y")
				f_r=true;
			cout << "Do you want [7]? (y/n)\n";
			cin >> choice;
			if(choice=="y")
				f_g=true;
			cout << "Do you want [8]? (y/n)\n";
			cin >> choice;
			if(choice=="y")
				f_b=true;
			cout << "Do you want [9]? (y/n)\n";
			cin >> choice;
			if(choice=="y")
				e_c=true;
			feed >> magic >> col >> row >> max;
			if(col>1000){
				cout << "Pixel count too high for buffer, program aborted!\n";
				system("pause");
				return 0;
			}
			out << magic << endl << col << " " << row << endl << max << endl;
	    	while (feed.good()){
				for(int i=0; i<col*3; i++){
					feed >> buffer[i];
				}
				//flip horizontally
				if(flip){
					for (int i=0; i<=col*3/2; i+=3) {
						int r = buffer[i]; 
						int g = buffer[i+1]; 
						int b = buffer[i+2]; 
						buffer[i] = buffer[col*3-i-3]; 
						buffer[i+1] = buffer[col*3-i-2]; 
						buffer[i+2] = buffer[col*3-i-1]; 
						buffer[col*3-i-3] = r; 
						buffer[col*3-i-2] = g; 
						buffer[col*3-i-1] = b; 
					}
				}
				//grey
				if(grey){
					for (int i=0; i<=col*3; i+=3) {
						int r = buffer[i]; 
						int g = buffer[i+1]; 
						int b = buffer[i+2]; 
						int grey=((r+g+b)/3);
						buffer[i] = grey; 
						buffer[i+1] = grey; 
						buffer[i+2] = grey; 
					}
				}
				for(int i=0; i<col*3; i++){
					//negate_red
					if(n_r&&((i%3)==0))
						buffer[i]=abs(buffer[i]-max);
					//negate_green
					if(n_g&&(((i-1)%3)==0))
						buffer[i]=abs(buffer[i]-max);
					//negate_blue
					if(n_b&&(((i-2)%3)==0))
						buffer[i]=abs(buffer[i]-max);
					//flatten_red
					if(f_r&&((i%3)==0))
						buffer[i]=0;
					//flatten_green
					if(f_g&&(((i-1)%3)==0))
						buffer[i]=0;
					//flatten_blue
					if(f_b&&(((i-2)%3)==0))
						buffer[i]=0;
					//extreme_contrast
					if(e_c){
						if(buffer[i]>=max/2){
							buffer[i]=max;
						}
						else{
							buffer[i]=0;
						}
					}
					out << buffer[i] << " ";
				}

				out << endl;
			}
		out.close();
		}
		else {
			cout << "Unable to open output file, program aborted!\n";
			system("pause");
			return 0;
		}
	feed.close();
	}
	else {
		cout << "Unable to open input file, program aborted!\n";
		system("pause");
		return 0;
	}
	cout << out_name << " created!\n";
	system("pause");
	return 0;
}


	