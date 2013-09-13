#include <fstream>
#include <string>
#include <iostream>
#include "IOfile.h"
// this class does part 1
// NOTE: IFSTREAM MUST BE DECLARED AND CLOSED OUTSIDE OF CLASS
using namespace std;


IOFile::IOFile() //constructor, with boolean to keep track of end of file condition (from input file)
{
	eof = false;
}

void IOFile::input_file(std::ifstream &input, string file_name, int* iteration, int buffer[]) //read one line of file
{
	if (!input.is_open())
    {
        input.open(file_name.c_str());  //open if not opened yet
    }
	if (input.is_open())
	{
        if (*iteration == 0)  // first iteration, only take header
        {
            getline(input,header);
            *iteration = 1;
            for (int i = 0; i < HEADER; i++)
            {
                input >> buffer[i];
            }
            col = buffer[0];  //this is number of columns, used as the length of one line
            colr = buffer[2]; //this is maximum color bits
            if (col > 1000)
            {
                cerr << "error: image width greater than 1000 pixels" << endl; //due to array being set at 3000 length
                *iteration = -1;
                cin >> col;
                exit(0);
            }
        }
        else if (*iteration == 1) //any subsequent iterations
        {
            for (int i = 0; i < col*3; i++) //clear array
            {
                buffer[i] = 0;
            }
            for (int i = 0; i < col*3; i++)
            {
                if (!input.eof()) //check end of line
                {
                    input >> buffer[i];
                    input.get(carriage_check);
                    if (carriage_check == '\r')  //check and ignore carriage return from DOS/WIN files
                    {
                        input.ignore();
                    }
					eof = input.eof();
                }
                else //end of line
                {
					eof = input.eof();
                    *iteration = -1;
                    return;
                }
            }
        }
	}
	else //unable to open
	{
		cerr << "error: unable to open file. check name, location, and extension (.ppm)" << endl;
		*iteration = -1;
		cin >> col;
		exit(0);
	}
}

void IOFile::output_file(string file_name, bool* first_time, int buffer[]) //output line by line
{
	ofstream output;
	if (*first_time)
	{
        output.open(file_name.c_str(), std::fstream::trunc); //rewrite file on first iteration
    }
    else
    {
        output.open(file_name.c_str(), std::fstream::app);  //otherwise add to end of file
    }
	if (output.is_open())
	{
		if (eof)
		{
			return;  // do not write if end of file has been reached, or else it writes a bunch of zeroes (see input function above, where the array got cleared)
		}
		else if (*first_time) //first time, only write header
        {
            output.flush(); //make sure ofstream is cleared/flushed
            output << header << endl;
            for (int i = 0; i < HEADER; i++)
            {
                output << buffer[i] << " ";
            }
            output << endl;
        
            *first_time = false;
        }
        else //subsequent iterations
        {
            for (int i = 0; i < col*3; i++)
            {
                output << buffer[i] << " ";
            }
        }
	}
	else  //unable to write to file, or file can't be opened/created/modified
	{
		cerr << "error: unable to write file" << endl;
		cin >> col;
		exit(0);
	}
	output << endl;
	output.close();
}
