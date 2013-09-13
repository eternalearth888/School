#include "IOfile.h"
#include "Manip.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
int main()
{
	const int CHAR_LENGTH = 20;
	const int data_SIZE = 3000;
    char inputn[CHAR_LENGTH];
    char outputn[CHAR_LENGTH];
    string input_name;
    string output_name;
    IOFile input_output;
	ifstream input;
	int data[data_SIZE];
    int iteration;
	bool first_time;
	int size;
	int color;
	int ans;
	bool repeat = true;

    cout << ".ppm Image Manipulator v1.1" << endl; //version 1.0 has no repeat
    cout << "by: Michael Karman" << endl << endl;
    while(repeat)
    {
		for (int i = 0; i < CHAR_LENGTH; i++)
		{
			inputn[i] = NULL;
			outputn[i] = NULL;
		}
		for (int i = 0; i < data_SIZE; i++)
		{
			data[i] = 0;
		}
        iteration = 0;                             //bunches of reset
        first_time = true;
		input_output.col = 0;
		input_output.col = 0;
		input_output.header.clear();
		input_output.eof = false;
        cout << "Please enter file name to open\n(must be .ppm and less than 1000 pixels horizontally)" << endl;
        cout << "file: ";
        cin.getline(inputn, CHAR_LENGTH, '\n');
        input_name.assign(inputn);
        cin.clear();
        cout << endl << endl << "Please enter output file name (existing file will be overwritten)" << endl;
        cout << "file: ";
        cin.getline(outputn, CHAR_LENGTH, '\n');
        output_name.assign(outputn);
        cin.clear();
        Manip perform;
        cout << endl << "What would you like to do to the image? (enter number)\ntype any other number to quit" << endl;
        cout << "[1] Flatten Red\t" << "[2] Flatten Green\t" << "[3] Flatten Blue\n";
        cout << "[4] Negate Red\t" << "[5] Negate Green\t" << "[6] Negate Blue\n";
        cout << "[7] Greyscale\t" << "[8] Flip Horizontally\t" << "[9] Extreme Contrast\n";
        cout << "[10] Copy File" << endl;
        cin >> ans;
        cin.ignore(5, '\n');   
        switch(ans) //menu
        {
            case 1:
                cout << "please wait" << endl;
                input.clear();
                input_output.input_file(input, input_name, &iteration, data);
                input_output.output_file(output_name, &first_time, data);         //this initial call for I/O from file is to pick header and column/color info
                size = input_output.col*3;
                color = input_output.colr;
                while(iteration > 0)
            	{
                    input_output.input_file(input, input_name, &iteration, data);
                    perform.flatten_red(data,size);
                    input_output.output_file(output_name, &first_time, data);
                }
                input.close();
                cout << "done" << endl << endl;
                break;
            case 2:
                cout << "please wait" << endl;
                input.clear();
                input_output.input_file(input, input_name, &iteration, data);
                input_output.output_file(output_name, &first_time, data);
                size = input_output.col*3;
                color = input_output.colr;
                while(iteration > 0)
                {
                   input_output.input_file(input, input_name, &iteration, data);
                   perform.flatten_green(data,size);
                   input_output.output_file(output_name, &first_time, data);
                }
                input.close();
                cout << "done" << endl << endl;
                break;
            case 3:
                cout << "please wait" << endl;
                input.clear();
                input_output.input_file(input, input_name, &iteration, data);
                input_output.output_file(output_name, &first_time, data);
                size = input_output.col*3;
                color = input_output.colr;
                while(iteration > 0)
            	{
                    input_output.input_file(input, input_name, &iteration, data);
                    perform.flatten_blue(data,size);
                    input_output.output_file(output_name, &first_time, data);
                }
                input.close();
                cout << "done" << endl << endl;
                break;
            case 4:
                cout << "please wait" << endl;
                input.clear();
                input_output.input_file(input, input_name, &iteration, data);
                input_output.output_file(output_name, &first_time, data);
                size = input_output.col*3;
                color = input_output.colr;
                while(iteration > 0)
            	{
                    input_output.input_file(input, input_name, &iteration, data);
                    perform.negate_red(data,color,size);
                    input_output.output_file(output_name, &first_time, data);
                }
                input.close();
                cout << "done" << endl << endl;
                break;
            case 5:
                cout << "please wait" << endl;
                input.clear();
                input_output.input_file(input, input_name, &iteration, data);
                input_output.output_file(output_name, &first_time, data);
                size = input_output.col*3;
                color = input_output.colr;
                while(iteration > 0)
            	{
                    input_output.input_file(input, input_name, &iteration, data);
                    perform.negate_green(data,color,size);
                    input_output.output_file(output_name, &first_time, data);
                }
                input.close();
                cout << "done" << endl << endl;
                break;
            case 6:
                cout << "please wait" << endl;
                input.clear();
                input_output.input_file(input, input_name, &iteration, data);
                input_output.output_file(output_name, &first_time, data);
                size = input_output.col*3;
                color = input_output.colr;
                while(iteration > 0)
            	{
                    input_output.input_file(input, input_name, &iteration, data);
                    perform.negate_blue(data,color,size);
                    input_output.output_file(output_name, &first_time, data);
                }
                input.close();
                cout << "done" << endl << endl;
                break;
            case 7:
                cout << "please wait" << endl;
                input.clear();
                input_output.input_file(input, input_name, &iteration, data);
                input_output.output_file(output_name, &first_time, data);
                size = input_output.col*3;
                color = input_output.colr;
                while(iteration > 0)
            	{
                    input_output.input_file(input, input_name, &iteration, data);
                    perform.grey_scale(data,size);
                    input_output.output_file(output_name, &first_time, data);
                }
                input.close();
                cout << "done" << endl << endl;
                break;
            case 8:
                cout << "please wait" << endl;
                input.clear();
                input_output.input_file(input, input_name, &iteration, data);
                input_output.output_file(output_name, &first_time, data);
                size = input_output.col*3;
                color = input_output.colr;
                while(iteration > 0)
            	{
                    input_output.input_file(input, input_name, &iteration, data);
                    perform.flip_horizontal(data,size);
                    input_output.output_file(output_name, &first_time, data);
                }
                input.close();
                cout << "done" << endl << endl;
                break;
            case 9:
                cout << "please wait" << endl;
                input.clear();
                input_output.input_file(input, input_name, &iteration, data);
                input_output.output_file(output_name, &first_time, data);
                size = input_output.col*3;
                color = input_output.colr;
                while(iteration > 0)
            	{
                    input_output.input_file(input, input_name, &iteration, data);
                    perform.extreme_contrast(data,color,size);
                    input_output.output_file(output_name, &first_time, data);
                }
                input.close();
                cout << "done" << endl << endl;
                break;
            case 10:
                cout << "please wait" << endl;
                input.clear();
                while(iteration >= 0)
            	{
                    input_output.input_file(input, input_name, &iteration, data);
                    input_output.output_file(output_name, &first_time, data);
                }
                input.close();
                cout << "done" << endl << endl;
                break;
            default:
                cout  << "Quit" << endl;
                repeat = false;
                break;
        }
    }
    cin >> ans; //for pausing before quitting
	return 0;
}
