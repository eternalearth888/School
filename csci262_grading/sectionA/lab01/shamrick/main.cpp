#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void negate_red(int* arr, int i){
	arr[i] = (255 - arr[i]);
}

void negate_green(int* arr, int i){
	arr[i] = (255 - arr[i]);
}

void negate_blue(int* arr, int i){
	arr[i] = (255 - arr[i]);
}

void flatten_red(int* arr, int i){
	arr[i] = 0;
}

void flatten_green(int* arr, int i){
	arr[i] = 0;
}

void flatten_blue(int* arr, int i){
	arr[i] = 0;
}

int main(){
	
	//variables
	string filename;
	string file_contents = " ";
	int picture[3000] = {};
	string imagetype = " ";
	int filelocationf = 0;
	int filelocations = 0;
	int rows = 0;
	int columns = 0;
	int runs = 0;
	char answer[8];
	int temparr[3] = {-1, -1, -1};

	//setting up ui
	cout << "PPM Image Editor" << endl;

	//getting input file
	cout << "Please enter a file to be opened: ";
	cin >> filename;
	ifstream myfile;
	myfile.open(filename);

	if(!myfile){
		cout << "File cannont be opened! Press any key to continue.\n" << endl;
		system("pause");
		exit(0);
	}
	
	//getting output file
	cout << "Please enter an output file name: ";
	cin >> filename;
	ofstream yourfile (filename);

	if(!yourfile){
		cerr << "File cannot be created! Press any key to contiune.\n" << endl;
		system("pause");
		exit(0);
	}

	//setting up the ui
	cout << "What conversions would you like to make?" << endl;
	cout << "[1] Convert to greyscale  \n[2] Flip horizontally" << endl;
	cout << "[3] Negative of red  \n[4] Negatieve of green  \n[5] Negative of blue" << endl;
	cout << "[6] Just the reds  \n[7] Just the greens  \n[8] Just the blues" << endl;

	//using for loop to get input
	for(int i = 0; i < 8; i++){
		cout << "Do you want [" << i + 1 << "]? (y/n) ";
		cin >> answer[i];
		//making sure either yes or no is specificed
		//if not then the answer is no
		if(answer[i] != 'y' && answer[i] != 'n'){
			answer[i] = 'n';
		}
	}

	//getting the header and putting it in the output file
	myfile >> imagetype;
	myfile >> temparr[0] >> temparr[1] >> temparr[2];
	
	//storing the size of the picture to output the proper size
	rows = temparr[0];
	columns = temparr[1];
	int temp = 1;
	const int columnz = temparr[1];
	const int rowsmax = temparr[0];
	yourfile << imagetype << "\n";
	yourfile << temparr[0] << " ";
	yourfile << temparr[1] << "\n";
	yourfile << temparr[2] << "\n";
	
	//this entire setion of code is just a copy of what is below to get
	//the flipe horizontally command to work, after I completed this I
	//came to the startling realization that this could have been done
	//all in my first loop.
	if(answer[1] == 'y'){
		while(columns > 0){
			if(columns == columnz){
				if(rowsmax - 1000 > 0){
					filelocations = rowsmax;
					filelocationf = rowsmax - 1000;
					columns++;
					rows -= 1000;
				}else{
					filelocations = rowsmax;
					filelocationf = 0;
				}
			}else{
				if(rows > 1000){
					filelocations = rowsmax - runs * 1000;
					filelocationf = rowsmax - runs * 1000 - 1000;
					columns++;
					rows -= 1000;
				}else if(rows < 1000){
					filelocations = rowsmax;
					filelocationf = 0;
				}
		}
		for(int i = filelocations * 3; i > filelocationf; i -= 3){
			for(int k = 2; k >= 0; k--){
				myfile >> picture[i - k];
			if(temp == 1 && answer[2] == 'y'){
				negate_red(picture, (i - k));
			}else if(temp == 2 && answer[5] == 'y'){
				flatten_green(picture, (i - k));
			}else if(temp == 3 && answer[5] == 'y'){
				flatten_blue(picture, (i - k));
			}else if(temp == 2 && answer[3] == 'y'){
				negate_green(picture, (i - k));
			}else if (temp == 1 && answer[6] == 'y'){
				flatten_red(picture, (i - k));
			}else if(temp == 3 && answer[6] == 'y'){
				flatten_blue(picture, (i - k));
			}else if(temp == 3 && answer[4] == 'y'){
				negate_blue(picture, (i - k));
			}else if(temp == 1 && answer[7] == 'y'){
				flatten_red(picture, (i - k));
			}else if(temp ==2  && answer[7] == 'y'){
				flatten_green(picture, (i - k));
			}
				temp++;
				if(temp > 3){
					temp = 1;
				}
			}
		}
			for(int j = filelocationf + 1; j < filelocations * 3 + 1; j++){
					if(j % 3 == 0){
							yourfile << "\t";
						}
					if(answer[0] == 'n'){
						yourfile << picture[j];
						yourfile << " ";
					}else if(answer[0] == 'y'){
						temparr[temp - 1] = picture[j];
						if(temp == 3){
							picture[j - 2] = (temparr[0] + temparr[1] + temparr[2]) / 3;
							picture[j - 1] = picture[j - 2];
							picture[j] = picture[j - 2];
							yourfile << picture[j - 2] << " " << picture[j - 1] << " " << picture[j] << " ";
						}
			
					}
					temp++;
					if(temp > 3){
						temp = 1;
					}
				
			}
		
			yourfile << "\n";
			columns--;
			runs++;
		
			}
	}else{
	//putting the contents of the original into the new file
	while(columns > 0){
		//if on the first column
		if(columns == columnz){

			if(rows > 1000){
				filelocations = 0;
				filelocationf = 1000;
				//adds one to columns because the line isn't
				//completed
				columns++;
				//removing 1000 from the rows count because 1000
				//has been read from the input file
				rows -= 1000;
			//if the original amount of rows total
			//is less than 1000 then the starting value is zero
			//and the end row is the current rows
			}else if(rows < 1000){
				filelocations = 0;
				filelocationf = rows;
			}
		//if on any column but the first
		}else{
			//if there is more than 1000 pieces of data to be read
			if(rows > 1000){
				//starting point is the number of run throughs
				//multiplied by 1000
				filelocations = (runs * 1000);
				//end point is 1000 past the start point
				//because there is more than 1000 remaining
				filelocationf = (runs * 1000 + 1000);
				//removing 1000 from the rows count because 1000
				//has been read from the input file
				rows -= 1000;
				//adding one column because the entire line
				//hasn't been read yet
				columns++;
			//if there are less than a thousand rows,
			//and there was more than a thousand to
			//start with
			}else if(rows < 1000 && rowsmax >= 1000){
				//starts at the number of run throughs
				//multiplied by 1000
				filelocations = (runs * 1000);
				//ends at run thoughs multiplied a 1000
				//plus the remaining rows (should be less 1000)
				filelocationf = (runs * 1000 + rows);
			//if the number of rows is less than 1000
			//if the number of maxrows is less than 1000
			}else if(rows < 1000 && rowsmax < 1000){
				//beginning is zero
				filelocations = 0;
				//end is the total number of rows (less than 1000)
				filelocationf = rowsmax;
			}
		}
		//from the beginning to three times the max because there are three
		//clor values for one pixel
		for(int i = filelocations; i < filelocationf * 3; i++){
			//every three numbers put a tab to make it look neater
			if(i % 3 == 0){
				yourfile << "\t";
			}

			//getting the input and store it into the array
			myfile >> picture[i];
			//either flattening or negating the respective color
			if(temp == 1 && answer[2] == 'y'){
				negate_red(picture, i);
			}else if(temp == 2 && answer[5] == 'y'){
				flatten_green(picture, i);
			}else if(temp == 3 && answer[5] == 'y'){
				flatten_blue(picture, i);
			}else if(temp == 2 && answer[3] == 'y'){
				negate_green(picture, i);
			}else if (temp == 1 && answer[6] == 'y'){
				flatten_red(picture, i);
			}else if(temp == 3 && answer[6] == 'y'){
				flatten_blue(picture, i);
			}else if(temp == 3 && answer[4] == 'y'){
				negate_blue(picture, i);
			}else if(temp == 1 && answer[7] == 'y'){
				flatten_red(picture, i);
			}else if(temp ==2  && answer[7] == 'y'){
				flatten_green(picture, i);
			}

			//account for the grayscale				
			if(answer[0] == 'n'){
				//put the array value into the output
				yourfile << picture[i];
				//adding whitespace to make it look perty
				yourfile << " "; 
	
			}else if(answer[0] == 'y'){
				temparr[temp - 1] = picture[i];
				//if on the third color value, then output the average to the file
				if(temp == 3){
					picture[i - 2] = (temparr[0] + temparr[1] + temparr[2]) / 3;
					picture[i - 1] = picture[i - 2];
					picture[i] = picture[i -1];
					yourfile << picture[i - 2] << " " << picture[i - 1] << " " << picture[i] << " ";					
				
				}
			}
		
			
			//used to identify if it's on the first second or third
			//color for the pixel
			temp++;
			if(temp > 3){
				temp = 1;
			}
		}
		
		
		yourfile << "\n";

		//subtract one column as we have gone through one
		columns--;
		//add a run through
		runs++;
		}
	}

	
	myfile.close();
	yourfile.close();
	system("pause");
	

	return 0;
}