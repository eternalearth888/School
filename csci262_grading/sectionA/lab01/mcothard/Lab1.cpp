#include <iostream>
#include <fstream>
#include <string>

using namespace std;
void negate_red(int,int[],int);
void negate_green(int,int[],int);
void negate_blue(int,int[],int);
void flip_horizontal();
void grey_scale(int[],int);
void flatten_red(int[],int);
void flatten_green(int[],int);
void flatten_blue(int[],int);
void extreme_contrast(int,int[],int);

void negate_red(int color,int row[],int columns){
	for(int i=0;i<columns*3;i+=3)
		row[i]=color-row[i];
	return;
}

void negate_green(int color,int row[],int columns){
	for(int i=1;i<columns*3;i+=3)
		row[i]=color-row[i];
	return;
}

void negate_blue(int color,int row[],int columns){
	for(int i=2;i<columns*3;i+=3)
		row[i]=color-row[i];
	return;
}

void flip_horizontal(int row[],int columns){
	int temp1=0;
	int temp2=0;
	for(int i=0;i<columns*3/2;i+=3){
		temp1=row[i];
		temp2=row[columns*3-i-3];
		row[i]=temp2;
		row[columns*3-i-3]=temp1;

		temp1=row[i+1];
		temp2=row[columns*3-i-2];
		row[columns*3-i-2]=temp1;
		row[i+1]=temp2;

		temp1=row[i+2];
		temp2=row[columns*3-i-1];
		row[columns*3-i-1]=temp1;
		row[i+2]=temp2;
	}
	if(columns%2!=0){
		int temp=0;
		temp=row[columns*3/2];
		row[columns*3/2]=row[(columns*3/2)+2];
		row[(columns*3/2)+2]=temp;
	}
}

void grey_scale(int row[],int columns){
	for(int i=0;i<columns*3;i+=3){
		int a=row[i];
		int b=row[i+1];
		int c=row[i+2];
		int avg=(a+b+c)/3;
		row[i]=avg;
		row[i+1]=avg;
		row[i+2]=avg;
	}
	return;
}

void flatten_red(int row[],int columns){
	for(int i=0;i<columns*3;i+=3)
		row[i]=0;
	return;
}

void flatten_green(int row[],int columns){
	for(int i=0;i<columns*3;i+=3)
		row[i+1]=0;
	return;
}

void flatten_blue(int row[],int columns){
	for(int i=0;i<columns*3;i+=3)
		row[i+2]=0;
	return;
}

void extreme_contrast(int color,int row[],int columns){
	for(int i=0;i<columns*3;i++){
		if(row[i]>color/2)
			row[i]=color;
		else
			row[i]=0;
	}
}

int main()
{
	string file_name;
	ifstream pic;
	string file_out_name;
	ofstream new_pic;
	const int MAX_INTS=3000;
	int row[MAX_INTS];
	int count=0;
	const int MAX_COLOR=255;
	string file_type;
	int columns=0;
	int rows=0;
	int color_max=0;
	string choice1;
	string choice2;
	string choice3;
	string choice4;
	string choice5;
	string choice6;
	string choice7;
	string choice8;

	cout << "Input the name of the file: ";
	getline(cin,file_name);

	pic.open(file_name);
	if(pic.fail()){
		cout<<"error in opening file";
		return 1;
	}

	cout<<"Input the name of the new file: ";
	getline(cin,file_out_name);
	
	new_pic.open(file_out_name, ios::app);
	pic>>file_type>>columns>>rows>>color_max;
	
	if(color_max>MAX_COLOR){
		cout<<"Color out of range";
		return 1;
	}

	if(columns>(MAX_INTS)){
		cout<<"Image too wide.";
		return 1;
	}

	cout<<"Here are our your choices: \n [1] Convert to gray scale [2] flip horizontally \n"
		<<"[3] negative of red [4] negative of green [5] negative of blue [6] \n just the reds"
		<<" [7] just the greens [8] just the blues";
	cout<<"Do you want [1]?";
	cin>>choice1;
	cout<<"Do you want [2]?";
	cin>>choice2;
	cout<<"Do you want [3]?";
	cin>>choice3;
	cout<<"Do you want [4]?";
	cin>>choice4;
	cout<<"Do you want [5]?";
	cin>>choice5;
	cout<<"Do you want [6]?";
	cin>>choice6;
	cout<<"Do you want [7]?";
	cin>>choice7;
	cout<<"Do you want [8]?";
	cin>>choice8;

	new_pic<<file_type<<endl<<columns<<' '<<rows<<endl<<color_max<<endl;
	do{
	for(int i=0;i<(columns*3);i++){
			pic>>row[i];
	}

	
	if(choice1[0]=='y' || choice1[0]=='Y')
		grey_scale(row,columns);
	if(choice2[0]=='y' || choice2[0]=='Y')
		flip_horizontal(row,columns);
	if(choice3[0]=='y' || choice3[0]=='Y')
		negate_red(color_max,row,columns);
	if(choice4[0]=='y' || choice4[0]=='Y')
		negate_green(color_max,row,columns);
	if(choice5[0]=='y' || choice5[0]=='Y')
		negate_blue(color_max,row,columns);
	if(choice6[0]=='y' || choice6[0]=='Y'){
		flatten_blue(row,columns);
		flatten_green(row,columns);
	}
	if(choice7[0]=='y' || choice7[0]=='Y'){
		flatten_blue(row,columns);
		flatten_red(row,columns);
	}
	if(choice8[0]=='y' || choice8[0]=='Y'){
		flatten_red(row,columns);
		flatten_green(row,columns);
	}

	for(int i=0;i<(columns*3);i++){
			if(i==(columns*3)-1)
				new_pic<<row[i]<<endl;
			else 
				new_pic<<row[i]<<' ';
	}

	count++;
	}while(count<rows);
	

	cout<<file_out_name<<" created";
	pic.close();
	new_pic.close();
}