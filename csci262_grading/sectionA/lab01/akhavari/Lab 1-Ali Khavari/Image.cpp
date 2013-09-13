#include "Image.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

image::image()
{
	for (int i=0; i<8; i++)
	{
		edit_choice[i] = false;
	}

	input_filename = "";
	output_filename = "";
	magic_number = "";
	num_columns = 0;
	num_rows = 0;
	max_color_value = 0;
}

void image::run()
{

	// User Inputs
	cout << "Portable Pi xmap Image Editor \n";
	cout << "Enter the name of the image file (.ppm): ";
	cin >> input_filename;
	cout << "Enter the name of the output file (.ppm): ";
	cin >> output_filename;

	menu();

	// Open input and output file stream
	ifstream input_file(input_filename);
	ofstream output_file(output_filename);

	// check for errors in input/output file
	if (!input_file) 
	{
		cerr << "Error: Input file could not be opened properly \n";
		exit(1);
	}
	if (!output_file)
	{
		cerr << "Error: Output file could not be opened properly \n";
		exit(1);
	}
	
	int header_count = 0;
	int buffer_count = 0;
	int buffer[BUFFER_SIZE];

	while ( !input_file.eof() ) {
		// Reads in the header data and stores information
		// Also writes header info to output_file
		if (header_count == 0) 
		{
			input_file >> magic_number;
			output_file << magic_number << endl;
		}

		else if (header_count == 1) 
		{
			input_file >> num_columns >> num_rows; 
			output_file << num_columns << " " << num_rows << endl;
		}

		else if (header_count == 2)
		{
			input_file >> max_color_value;
			output_file << max_color_value << endl;
		}
	
	// Reads in and stores the body data using a buffer
	// Reads in one row of pixels and stores it into buffer[]
		else
		{
			// stops input when one row is complete
			if (buffer_count < (num_columns * 3))
			{
				// inputs into a buffer 
				input_file >> buffer[buffer_count];
				buffer_count ++;
			}

			else 
			{
				// Buffer (Image) Modifiers
				

				if (edit_choice[0] == 'y')
				{
					grey_scale(buffer);
				}

				if (edit_choice[1] == 'y')
				{
					flip_horizontal(buffer);
				}

				if (edit_choice[2] == 'y')
				{
					negate_red(buffer);
				}

				if (edit_choice[3] == 'y')
				{
					negate_green(buffer);
				}

				if (edit_choice[4] == 'y')
				{
					negate_blue(buffer);
				}

				if (edit_choice[5] == 'y')
				{
					flatten_red(buffer);
				}

				if (edit_choice[6] == 'y')
				{
					flatten_green(buffer);
				}

				if (edit_choice[7] == 'y')
				{
					flatten_blue(buffer);
				}

				if (edit_choice[8] == 'y')
				{
					horizontal_blur(buffer);
				}

				if (edit_choice[9] == 'y')
				{
					extreme_contrast(buffer);
				}

				if (edit_choice[10] == 'y')
				{
					random_noise(buffer);
				}

				

				// Outputs buffer into output file

				for (int i=0; i<buffer_count; i++)
				{
					output_file << buffer[i] << " ";
				}
				output_file << "\n"; 
				buffer_count = 0;
			}
		}
		header_count++;
	}

	cout << output_filename << " successfully created! \n";
	// close input and output file streams
	input_file.close();
	output_file.close();
		
	// Checks to see if the input file has the correct dimensions.
	// If the file is too big, then the program terminates after an error message.
	if (num_columns > (BUFFER_SIZE/3))
	{
		cout << "Sorry the maximum pixel width is " << BUFFER_SIZE/3 << endl;
		cout << "Either use a skinnier image or change the buffer capacity. \n";
		exit(1);
	}
	


}

void image::menu()
{
	char filter; 
	cout << "Would you like to apply a filter to your image? (y/n): ";
	cin >> filter;
	
	if (filter == 'y')
	{
		cout << "\n";
		cout << "Which filter(s) would you like to apply (y/n)? \n";
		cout << "1) Greyscale \n2) Mirror \n3) Negate Reds \n"
			"4) Negate Greens \n5) Negate Blues \n6) Flatten Reds \n"
			"7) Flatten Greens \n8) Flatten Blues \n9) Horizontal Blur \n"
			"10) Extreme Contrast \n 11) Random Noise \n";

		for (int i=0; i<11; i++)
		{
			cout << i+1 << ") ";
			cin >> edit_choice[i];
		}
		cout << "\n";
	}
}

void image::negate_red(int row[BUFFER_SIZE])
{
	// checks even/odd and creates appropriate value of
	// mid_val (median)
	if (max_color_value % 2 == 0)
	{
		int mid_val = max_color_value/2; 
	}
	else
	{
		int mid_val = (max_color_value/2) +1; 
	} 

	// negates the red values
	for (int i=0; i<num_columns *3; i+=3)
	{
		row[i] = max_color_value - row[i];
	}
}

void image::negate_green(int row[BUFFER_SIZE])
{
	// checks even/odd and creates appropriate value of
	// mid_val (median)
	if (max_color_value % 2 == 0)
	{
		int mid_val = max_color_value/2; 
	}
	else
	{
		int mid_val = (max_color_value/2) +1; 
	} 

	// Negates the Green values
	for (int i=1; i<num_columns *3; i+=3)
	{
		row[i] = max_color_value - row[i];
	}
}

void image::negate_blue(int row[BUFFER_SIZE])
{
	// checks even/odd and creates appropriate value of
	// mid_val (median)
	if (max_color_value % 2 == 0)
	{
		int mid_val = max_color_value/2; 
	}
	else
	{
		int mid_val = (max_color_value/2) +1; 
	} 
	// Negates the Blue values
	for (int i=2; i<num_columns *3; i+=3)
	{
		row[i] = max_color_value - row[i];
	}
}

void image::flip_horizontal(int row[BUFFER_SIZE])
{
	int mid_val;
	int temp;
	// checks even/odd and creates appropriate value of
	// mid_val (median) = median of one row  
	if (num_columns % 2 == 0)
	{
		mid_val = (num_columns*3)/2; 
	}
	else
	{
		mid_val = (num_columns*3/2) +1; 
	} 
	// First reverses order of row[]
	for (int i = 0; i< mid_val; i++)
	{
		temp = row[i];
		row[i] = row[(num_columns*3)-i];
		row[(num_columns*3)-i] = temp;
	}

	// Flips blue and red values to return correct
	// formatting to the row
	for (int i=0; i< num_columns*3; i+=3)
	{
		temp = row[i];
		row[i] = row[i+2];
		row[i+2] = temp;
	}
}

void image::grey_scale(int row[BUFFER_SIZE])
{
	int avg = 0;
	// finds the average RGB value for each pixel and 
	// assigns each value to the average
	for (int i=0; i<num_columns*3; i+=3)
	{
		avg = (row[i] + row[i+1] + row[i+2])/3;
		row[i] = row[i+1] = row[i+2] = avg;
	}
}

void image::flatten_red(int row[BUFFER_SIZE])
{
	// changes all red values to 0
	for (int i=0; i < num_columns*3; i+=3)
	{
		row[i] = 0; 
	}
}

void image::flatten_green(int row[BUFFER_SIZE])
{
	// changes all green values to 0
	for (int i=0; i < num_columns*3; i+=3)
	{
		row[i+1] = 0; 
	}
}

void image::flatten_blue(int row[BUFFER_SIZE])
{
	// changes all blue  values to 0
	for (int i=0; i < num_columns*3; i+=3)
	{
		row[i+2] = 0; 
	}
}

void image::horizontal_blur(int row[BUFFER_SIZE])
{
	int avg_red = 0;
	int avg_green = 0;
	int avg_blue = 0;
	int row_size = num_columns*3;

	if (num_columns % 3 == 0)
	{
		for (int i=0; i < row_size; i+=9)
		{
			avg_red = (row[i] + row[i+3] + row[i+6]) / 3;
			avg_green = (row[i+1] + row[i+4] + row[i+7]) / 3;
			avg_blue = (row[i+2] + row[i+5] + row[i+8]) / 3;

			row[i] = row[i+3] = row[i+6] = avg_red;
			row[i+1] = row[i+4] = row[i+7] = avg_green;
			row[i+2] = row[i+5] = row[i+8] = avg_blue;
		}

	}
	
	if (num_columns % 3 == 1)
	{
		for (int i=0; i < (row_size) - 12; i+=9)
		{
			avg_red = (row[i] + row[i+3] + row[i+6]) / 3;
			avg_green = (row[i+1] + row[i+4] + row[i+7]) / 3;
			avg_blue = (row[i+2] + row[i+5] + row[i+8]) / 3;

			row[i] = row[i+3] = row[i+6] = avg_red;
			row[i+1] = row[i+4] = row[i+7] = avg_green;
			row[i+2] = row[i+5] = row[i+8] = avg_blue;
		}

		
			avg_red = (row[row_size-12] + row[row_size-9] + row[row_size-6] + row[row_size-3])/4;
			avg_green = (row[row_size-11] + row[row_size-8] + row[row_size-5] + row[row_size-2])/4;
			avg_blue = (row[row_size-10] + row[row_size-7] + row[row_size-4] + row[row_size-1])/4;

			
			row[row_size-12] = row[row_size-9] = row[row_size-6] = row[row_size-3] = avg_red;
			row[row_size-11] = row[row_size-8] = row[row_size-5] = row[row_size-2] = avg_green;
			row[row_size-10] = row[row_size-7] = row[row_size-4] = row[row_size-1] = avg_blue;

	}

	if (num_columns % 3 == 2)
	{
		for (int i=0; i < (row_size) - 15; i+=9)
		{
			avg_red = (row[i] + row[i+3] + row[i+6]) / 3;
			avg_green = (row[i+1] + row[i+4] + row[i+7]) / 3;
			avg_blue = (row[i+2] + row[i+5] + row[i+8]) / 3;

			row[i] = row[i+3] = row[i+6] = avg_red;
			row[i+1] = row[i+4] = row[i+7] = avg_green;
			row[i+2] = row[i+5] = row[i+8] = avg_blue;
		}

		
			avg_red = (row[row_size-15] + row[row_size-12] + row[row_size-9] + row[row_size-6] + row[row_size-3])/4;
			avg_green = (row[row_size-14] + row[row_size-11] + row[row_size-8] + row[row_size-5] + row[row_size-2])/4;
			avg_blue = (row[row_size-13] + row[row_size-10] + row[row_size-7] + row[row_size-4] + row[row_size-1])/4;

			
			row[row_size-15] = row[row_size-12] = row[row_size-9] = row[row_size-6] = row[row_size-3] = avg_red;
			row[row_size-14] = row[row_size-11] = row[row_size-8] = row[row_size-5] = row[row_size-2] = avg_green;
			row[row_size-13] = row[row_size-10] = row[row_size-7] = row[row_size-4] = row[row_size-1] = avg_blue;

	}


}

void image::extreme_contrast(int row[BUFFER_SIZE])
{
	int mid_val;
	// checks even/odd and creates appropriate value of
	// mid_val (median) = median of one row  
	if (num_columns % 2 == 0)
	{
		mid_val = (num_columns*3)/2; 
	}
	else
	{
		mid_val = (num_columns*3/2) +1; 
	} 

	for (int i=0; i < num_columns*3; i++)
	{
		if (row[i] < mid_val)
		{
			row[i] = 0;
		}
		else
		{
			row[i] = max_color_value;
		}
	}


}

void image::random_noise(int row[BUFFER_SIZE])
{
	const int randomness = 10;		// domain of values to be added/subtracted
	int int_type = rand() % 100;	// chooses addition or subtraction based on random value

	// 50% chance of subtractoin
	if (int_type <50)
	{
		for (int i=0; i<num_columns*3; i++)
		{
			row[i] -= rand() % randomness;
		}
	}
	// 50% chance of addition
	else
	{
		for (int i=0; i<num_columns*3; i++)
		{
			row[i] += rand() % randomness;
		}
	}
	

}