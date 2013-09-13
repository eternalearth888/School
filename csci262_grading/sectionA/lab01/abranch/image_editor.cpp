#include <iostream>
#include <fstream>
#include <string>


using namespace std;

//User defined functions
void negate_red();
void negate_green();
void negate_blue();
void flip_horizontal();
void grey_scale();
void flatten_red();
void flatten_green();
void flatten_blue();
void extreme_contrast();
void random_noise(int randomNumber);

//Declare and initiate variables
const int bufferSize = 3000;
string inputFile, outputFile, type;
ifstream  image, practice;
ofstream newImage;
int rows(0), cols(0), maxColor(0), entries(0), randomNum(50);
int buffer[bufferSize];
char yes_no[10];



int main()
{

	cout<<"Portable Pixmap (PPM) Image Editor!"<<endl;
	cout<<'\n';

	//Prompt user for name of input file
	cout <<"Enter the name of the input file:  ";
	cin>> inputFile;
	cout<< '\n';

	//Check if input file can open and inform user
	practice.open(inputFile);
	if (!practice)
	{
		cout<<"File "<< inputFile <<" could not be opened."<<endl;
		cout<<"The program has been aborted."<<endl;
		system("pause");
		exit(1);
	}
	else cout<<"Input file " <<inputFile<< " opened correctly!"<<endl;

	//Read in header info of practice file
	practice>>type>> cols>> rows>>maxColor;
	int counter(0), temp(0);

	//calculate total number of values in one row
	entries = cols*3;

	//Check if the buffer size is large enough for the number of columns
	if(entries>bufferSize)
	{
		cout<<'\n';
		cout<<"The number of columns in the image file is too large for a buffer size of 3000. "<<endl;
		cout<< "Abort program."<<endl;
		system("pause");
		exit(1);
	}

	//Check number of pixels
	while(practice)
	{
		counter++;
		practice >> temp;
	}

	if ((counter-1) != entries*rows)
	{
		cout<<'\n';
		cout<<"The specified row and column data for the file did not "<<endl;
		cout<<"match up with the number of entries. Abort program!"<<endl;
		system("pause");
		exit(1);
	}

	//close practice stream
	practice.close();

	//Prompt user for name of output file
	cout<<'\n';
	cout<<"Enter the name of the output file: ";
	cin >> outputFile;

	newImage.open(outputFile);

	//Read in image header information and write to output file
	image.open(inputFile);
	image>>type>>cols>>rows>>maxColor;
	newImage << type <<endl<<cols<<" "<<rows<<endl<<maxColor<<endl;
	
	//Print options to user
	cout<<'\n';
	cout<<"Here are your choices: "<<endl;
	cout<<"[1]  negative of red    [2]  negative of green      [3]  negative of blue"<<endl;
	cout<<"[4]  flip horizontally  [5]  convert to greyscale"<<endl;
	cout<<"[6]  just the reds      [7]  just the greens        [8]  just the blues"<<endl;
	cout<<"[9]  extreme contrast   [10] add or subtract random number "<<endl;
	cout<<endl;
	cout<<"Please enter your choices with no spaces."<<endl;
	cout<<"Do you want [1]? (y/n) :";
	cin>>yes_no[0];
	cout<<"Do you want [2]? (y/n) :";
	cin>>yes_no[1];
	cout<<"Do you want [3]? (y/n) :";
	cin>>yes_no[2];
	cout<<"Do you want [4]? (y/n) :";
	cin>>yes_no[3];
	cout<<"Do you want [5]? (y/n) :";
	cin>>yes_no[4];
	cout<<"Do you want [6]? (y/n) :";
	cin>>yes_no[5];
	cout<<"Do you want [7]? (y/n) :";
	cin>>yes_no[6];
	cout<<"Do you want [8]? (y/n) :";
	cin>>yes_no[7];
	cout<<"Do you want [9]? (y/n) :";
	cin>>yes_no[8];
	cout<<"Do you want [10]?(y/n) :";
	cin>>yes_no[9];

	//Read data from image file and write data to newImage file
	for(int i=1; i<=rows; i++)
	{
		for(int j=0; j< entries; j++)
		{
			image>>buffer[j];

			if(buffer[j] > maxColor) buffer[j] = maxColor;
			if(buffer[j] <0) buffer [j] = 0;
		}

		int breakOut(0);
		//Call functions if user wants them
		if(yes_no[0] == 'y') negate_red();
		if(yes_no[1] == 'y') negate_green();
		if(yes_no[2] == 'y') negate_blue();
		if(yes_no[3] == 'y') flip_horizontal();
		if(yes_no[4] == 'y') grey_scale();
		if(yes_no[5] == 'y') flatten_red();
		if(yes_no[6] == 'y') flatten_green();
		if(yes_no[7] == 'y') flatten_blue();
		if(yes_no[8] == 'y') extreme_contrast();
		if(yes_no[9] == 'y') random_noise(randomNum);
			

		//Check that every value of the current row is between 0 and maxColor.
		//If not, change values greater than maxColor to maxColor, and negative values to 0.
		for (int i=0; i< entries; i++)
		{
			newImage << buffer[i];
			newImage << " ";
		}

		newImage<<'\n';
	}

	//close input and output files
	image.close();
	newImage.close();

	cout<<'\n';

	cout<<outputFile<< " was created! Go check it out!"<<endl;
	system("pause");
}

//function negates red number of each pixel
void negate_red()
{
	for(int i=0; i<entries; i+=3)
	{
		buffer[i] = maxColor-buffer[i];
	}
}

//function negates green number of each pixel
void negate_green()
{
	for(int i=1; i<entries; i+=3)
	{
		buffer[i] = maxColor-buffer[i];
	}
}

//function negates red number of each pixel
void negate_blue()
{
	for(int i=2; i<entries; i+=3)
	{
		buffer[i] = maxColor-buffer[i];
	}

}

//function flips each row horizontally
void  flip_horizontal()
{

	int newArray[bufferSize];
	int swap(entries-1);

	for(int m=0; m<entries; m+=3)
	{
		newArray[swap]=buffer[m+2];
		newArray[swap-1]=buffer[m+1];
		newArray[swap-2] = buffer[m];
		swap = swap -3;
	}

	for(int i = 0;  i<entries; i++)
	{
		buffer[i] = newArray[i];
	}

}

//function sets each pixel value to the average of the three
void grey_scale( )
{
	for(int i=0; i<entries; i+=3)
	{
		buffer[i] = buffer[i+1] = buffer[i+2] = ((buffer[i] + buffer[i+1] + buffer[i+2])/3);
	}

}

//function sets the red value to zero
void flatten_red()
{
	for(int i=0; i<entries; i+=3)
	{
		buffer[i] = 0;
	}

}

//function sets the green value to zero
void flatten_green()
{
	for(int i=1; i<entries; i+=3)
	{
		buffer[i] = 0;
	}

}

//function sets the blue value to zero
void flatten_blue()
{
	for(int i=2; i<entries; i+=3)
	{
		buffer[i] = 0;
	}
}

//function sets each value to either extreme
void extreme_contrast()
{
	for(int i = 0; i<entries; i++)
	{
		if (buffer[i] > (maxColor/2))
		{
			buffer[i] = maxColor;
		}
		else buffer[i] = 0;
	}
}

//function adds or subtracts a random number
void random_noise(int randomNumber)
{
	int range(0);
	int sign(0);

	for (int i = 0; i<entries; i++)
	{
		range = rand()%randomNumber;
		
		if (sign == 0)
		{
			sign = -1;
		}

		buffer[i] = buffer[i] + range*sign;

		if (buffer[i] > maxColor)
		{
			buffer[i] = maxColor;
		}

		if(buffer[i] <0)
		{
			buffer[i] = 0;
		}
	}
}



