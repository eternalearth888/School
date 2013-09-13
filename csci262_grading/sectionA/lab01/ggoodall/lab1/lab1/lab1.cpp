#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

const int max_pixels = 3000;
void negate_red(int i, int jim[]){
	if(i%3 == 0){jim[i] = 255-jim[i];}
}
void negate_green(int i, int jim[]){
	if(i%3 == 1){jim[i] = 255-jim[i];}
}
void negate_blue(int i, int jim[]){
	if(i%3 == 2){jim[i] = 255-jim[i];}
}

void flatten_red(int i, int farray[]){
	if(i%3 == 0){
		farray[i] = 0; 
	}
}

void flatten_green(int i, int farray[]){
	if(i%3 == 1){
		farray[i] = 0; 
	}
}

void flatten_blue(int i, int farray[]){
	if(i%3 == 2){
		farray[i] = 0; 
	}
}


void flip_horizontal (int i, int col, int fhf1array[],int fhlarray[]){
	
			for(int i = 0; i < col; i++){
				fhf1array[i*3] = fhlarray[3*(col-i -1)];
				fhf1array[i*3+1] = fhlarray[3*(col-i-1) + 1];
				fhf1array[i*3+2] = fhlarray[3*(col-i-1)+2];
				
				}
			for (int i =0; i<3*col;i++)
				fhlarray[i] = fhf1array[i];
			}
void grey_scale(int i, int garray[]){
if((i+1)%3==0){
		int avg=(garray[i]+garray[i-1]+garray[i-2])/3;
		garray[i-2]=avg;
		garray[i-1]=avg;
		garray[i]=avg;
		}
}
//worked with Michael Scioletti, and received help from Ben Johnson and Mojtaba Rezbekha
 int main(){
	 char output[max_pixels];
	 char input[max_pixels];
	 int larray[max_pixels]; //large array
	 int counter[3];

	 

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

			cout << "Here are your choices: "<< endl; 
	 cout << "[1]  convert to greyscale [2]  flip horizontally" << endl;
	 cout << "[3]  negative of red [4]  negative of green [5]  negative of blue" << endl;
	 cout << "[6]  just the reds   [7]  just the greens   [8]  just the blues" << endl; 


	 char grey_input;
	 char fh_input;
	 char fred_input;
	 char negred_input;
	 char neggreen_input;
	 char negblue_input;
	 char fgreen_input;
	 char fblue_input;


	    cout << " Do you want [1]? (y/n)" << endl;
		cin >> grey_input;  
	    cout<<  " Do you want [2]? (y/n)" << endl; 
		cin >> fh_input;
	    cout << " Do you want [3]? (y/n)" << endl; 
		cin >> negred_input;
		cout << " Do you want [4]? (y/n)" << endl;
		cin >> neggreen_input;
	    cout << " Do you want [5]? (y/n)" << endl;
		cin >> negblue_input;
		cout << " Do you want [6]? (y/n)" << endl;
		cin >> fred_input;
		cout << " Do you want [7]? (y/n)" << endl;
		cin >> fgreen_input; 
		cout << " Do you want [8]? (y/n)" << endl;
		cin >> fblue_input;
	     cout << output << "created." << endl;
			
				 string p; //p3
				 int row,col,val,num;
				 int f1array[3000];
				
				ppmfile>>p;
				ppmfile>>col;
				ppmfile>>row;
				ppmfile>>val;
				out<<p<<endl;
				out<<col<<" ";
				out<<row<<endl;
				out<<val<<endl;

				for(int i = 0; i < row; i++)
				{
					if(3*col>=3000)
					{
						cout<<"File is too big";
					}
					else
					{
						for (int i =0; i < 3*col ;i++)
						{
							ppmfile >> num;
							larray[i]= num;
	
		                 /*  if (negred_input == 'y' || negred_input == 'Y'){
							negate_red (i, larray);
							//negred_input = '\0';
							}
							
							if(neggreen_input == 'y' || neggreen_input == 'Y'){
							negate_green (i, larray);
							}
							
							//negate_green(i, larray);
							if (negblue_input == 'y' || negblue_input =='Y'){
							negate_blue (i, larray);
							}
							
							//negate_blue(i, larray);
							if (grey_input == 'y' || grey_input == 'Y'){
							grey_scale(i, larray);
							}
							
							if (fred_input == 'y' || fred_input == 'Y'){
							flatten_red(i, larray);
							}
							
							//flatten_red(i, larray); 
							if (fgreen_input == 'y' || fgreen_input == 'Y'){
							flatten_green(i, larray);
							}
							
							//flatten_green(i, larray);
							if (fblue_input == 'y' || fblue_input == 'Y'){
							flatten_blue(i, larray);
							} */
							
							//flatten_blue(i, larray); 

						}				
	//} we closed the for loop abovethis function, we are now opening to include output.	
	//flip_horizontal(i, col, larray);//flip would go down move the declaration to the top
		/*	int f1array[3000];
			for(int i = 0; i < col; i++){
				f1array[i*3] = larray[3*(col-i -1)];
				f1array[i*3+1] = larray[3*(col-i-1) + 1];
				f1array[i*3+2] = larray[3*(col-i-1)+2];
			} */
						if (fh_input == 'y' || fh_input =='Y'){
							flip_horizontal (i, col, f1array, larray);
							}
							


			for (int i =0; i<3*col;i++){
				out << larray[i]<<" ";
				//out <<f1array[i]<<" ";
			}							

			out<<endl;
				}
				}
			 ppmfile.close();
			 out.close();
		 }
		 
	
	//}
	 


	 system("PAUSE");

	 return 0;
 }

 }