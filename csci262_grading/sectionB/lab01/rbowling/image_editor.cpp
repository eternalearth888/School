#include<iostream>
#include<fstream>
#include<string>

using namespace std;
const int MAX_DATA=3000;
int *negate_red(int*, int);
int *negate_green(int*,int);
int *negate_blue(int*, int);
int *flatten_red(int*, int);

int *flatten_green(int*, int);
int *flatten_blue(int*, int);
int *grey_scale(int*, int);
int *flip_horizontal(int*, int);
int *extreme_contrast(int*, int);
int main(){
	cout<<"Welcome!"<<endl<<"This is a Portable Pixmap (PPM) Image Editor"<<endl;
	int buffer[MAX_DATA]; //single buffer array

	//Opens file and creates and opens an output file
	string infilename;
	string outfilename;
	cout<<"Please enter the name of an image file"<<endl;
	cin>>infilename; 
	ifstream filein;
	filein.open(infilename);
	if(!filein){
		cout<<"Error: file cannot be opened";
		system("pause");
		exit(1);
	}
	ofstream fileout;
	cout<<"Please enter a file output name:"<<endl;
	cin>>outfilename;
	fileout.open(outfilename);

	//Reads and outputs alphanumeric number for file formating
	char P;
	int three;

	filein>>P;
	filein>> three;
	fileout<<P<<three<<endl;
	//cout<<P<<three<<endl;

	//Reads and outputs column and row values
	int column;
	int row;
	filein>>column>>row;
	if(column*3>MAX_DATA){
	cout<<"Error: Input file too large"<<endl;
	system("pause");
	exit(1);
	}
	fileout<<column<<" "<<row<<endl;
	//cout<<column<<" "<<row<<endl;

	//Reads and outputs maximum color value
	int maxclr;
	filein>>maxclr;
	fileout<<maxclr<<endl;
	//cout<<maxclr<<endl;

	
	//Reads the data one row at a time and writes it to the output file after applying specified effects
	cout<<"What do you want to do?"<<endl;
	cout<<"[1] Negate Red [y/n]"<<endl;
	cout<<"[2] Negate Green [y/n]"<<endl;
	cout<<"[3] Negate Blue [y/n]"<<endl;
	cout<<"[4] Flatten Red [y/n]"<<endl;
	cout<<"[5] Flatten Green [y/n]"<<endl;
	cout<<"[6] Flatten Blue [y/n]"<<endl;
	cout<<"[7] Gray Scale [y/n]"<<endl;
	cout<<"[8] Flip Horizontal [y/n]"<<endl;
	cout<<"[9] Extreme Contrast [y/n]"<<endl;

	string answer;
	char ans;
	for(int t=1; t<10; ++t){
	cout<<"Do you want ["<<t<<"]?"<<endl;
	cin>>ans;
	answer.append(1,ans);
	}

	int value;
	for(int k=0; k<row; ++k){
	for(int i=0; i<3*column; ++i){
		filein>>value;
		buffer[i]=value;
	}
	int*q;
	q=buffer;
	if(answer[0] == 'y'){
		q=negate_red(q,column);
	}
	if(answer[1] =='y'){
		q=negate_green(q,column);
	}
	if(answer[2] =='y'){
		q=negate_blue(q,column);
	}
	if(answer[3] =='y'){
		q=flatten_red(q,column);
	}
	if(answer[4] =='y'){
		q=flatten_green(q,column);
	}
	if(answer[5] =='y'){
		q=flatten_blue(q,column);
	}
	if(answer[6]=='y'){
		q=grey_scale(q,column);
	}
	if(answer[7]=='y'){
		q=flip_horizontal(q,column);
	}
	if(answer[8]=='y'){
		q=extreme_contrast(q,column);
	}
	for(int i=0; i<3*column; ++i){
       fileout<<q[i]<<" ";
	   //cout<<q[i]<<" ";
	}
	fileout<<endl;
	cout<<endl;
	}
	filein.close();
	fileout.close();
	
	cout<<outfilename<<" created"<<endl;

	system("pause");


	return 0;
}
	int *negate_red(int* buffer, int columns){
		
	static int newbuffer[MAX_DATA];
	for(int i=0; i<3*columns; i=i+3){
		newbuffer[i]=255-buffer[i];
		newbuffer[i+1]=buffer[i+1];
		newbuffer[i+2]=buffer[i+2];
		}
	return newbuffer;
	}

	int *negate_green(int* buffer, int columns){
	
		static int newbuffer[MAX_DATA];
	for(int i=0; i<3*columns; i=i+3){
		newbuffer[i]=buffer[i];
		newbuffer[i+1]=255-buffer[i+1];
		newbuffer[i+2]=buffer[i+2];
	}
	return newbuffer;
	}

	int *negate_blue(int* buffer, int columns){
	static int newbuffer[MAX_DATA];
	for(int i=0; i<3*columns; i=i+3){
		newbuffer[i]=buffer[i];
		newbuffer[i+1]=buffer[i+1];
		newbuffer[i+2]=255-buffer[i+2];
	}
	return newbuffer;
	}

	int *flatten_red(int* buffer, int columns){
		static int newbuffer[sizeof(buffer)];
	for(int i=0; i<3*columns; i=i+3){
		newbuffer[i]=0;
		newbuffer[i+1]=buffer[i+1];
		newbuffer[i+2]=buffer[i+2];
	}
	return newbuffer;
	}

	int *flatten_green(int* buffer, int columns){
	static int newbuffer[MAX_DATA];
	for(int i=0; i<3*columns; i=i+3){
		newbuffer[i]=buffer[i];
		newbuffer[i+1]=0;
		newbuffer[i+2]=buffer[i+2];
	}
	return newbuffer;
	}
	
	int *flatten_blue(int* buffer, int columns){
		static int newbuffer[MAX_DATA];
	for(int i=0; i<3*columns; i=i+3){
		newbuffer[i]=buffer[i];
		newbuffer[i+1]=buffer[i+1];
		newbuffer[i+2]=0;
	}
	return newbuffer;
	}
	int *grey_scale(int* buffer, int columns){
	static int newbuffer[MAX_DATA];
	int avg=0;
	for(int i=0; i<3*columns; i=i+3){
		avg+=buffer[i];
		avg+=buffer[i+1];
		avg+=buffer[i+2];
		avg=avg/3;
		newbuffer[i]=avg;
		newbuffer[i+1]=avg;
		newbuffer[i+2]=avg;\
		avg=0;
	}
	return newbuffer;
	}

	int *flip_horizontal(int*buffer, int columns){
		static int newbuffer[MAX_DATA];
		static int tempbuffer[MAX_DATA];
		for(int i=0; i<3*columns; ++i){
			tempbuffer[i]=buffer[((columns*3)-1)-i];
		}
		for(int j=0; j<columns*3; j=j+3){
		    newbuffer[j]=tempbuffer[j+2];
			newbuffer[j+1]=tempbuffer[j+1];
			newbuffer[j+2]=tempbuffer[j];
		}
	return newbuffer;
	}

	int *extreme_contrast(int*buffer, int columns){
	static int newbuffer[MAX_DATA];
	for(int i=0; i<3*columns; i=i+1){
		if(buffer[i]>=255){
			newbuffer[i]=255;
		}else{
		newbuffer[i]=0;
		}
		}
	return newbuffer;
	}
	

	
 

