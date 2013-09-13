#include "picture.h"

picture::picture(void){
	
}

picture::picture(const string &filename){
	ifstream in_file (filename.c_str());
	if (!in_file){
		cerr << "Invalid file!" << endl;
		exit(1);
	} 
	input_file = filename;
	in_file >> p_type >> columns >> rows >> max_color;
	in_file.close();

	// Create appropriate size buffer for pixels
	pixels = new int *[columns];
	if(columns >= 1000){
		columns = 1000;
		row_long = true;
	}
	for(int i = 0; i < columns; i++){
		pixels[i] = new int[3];
	}
}

picture::~picture(void){
	//for(int i = 0; i < columns; i++){
	//	delete[] pixels[i];
	//}
	//delete[] pixels;
}

void picture::applyFilters(const string &filename, const bool filters[FILTER_COUNT]){
	ifstream in_file (input_file.c_str());
	if (!in_file){
		cerr << "Invalid file!" << endl;
		exit(1);
	} 
	ofstream out_file (filename.c_str());
	if (!out_file){
		cerr << "Colud not create output file!" << endl;
		exit(1);
	}

	// Tranfers header info
	in_file >> p_type >> columns >> rows >> max_color;
	out_file << p_type << endl << columns << " " << rows << endl << max_color << endl;

	// Does specified image processing 
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			in_file >> pixels[j][1] >> pixels[j][2] >> pixels[j][3];
		}

		if (filters[0] == true){greyscale();}
		if (filters[1] == true){flip_h();}
		if (filters[2] == true){negate_R();}
		if (filters[3] == true){negate_R();}
		if (filters[4] == true){negate_R();}
		if (filters[5] == true){flat_R();}
		if (filters[6] == true){flat_R();}
		if (filters[7] == true){flat_R();}

		for(int j = 0; j < columns; j++){
			out_file << pixels[j][1] << " " << pixels[j][2] << " " << pixels[j][3] << " ";
		}
		out_file << endl;
	}
	in_file.close();
	out_file.close();
}

void picture::greyscale(){
	int average;
	for(int j = 0; j < columns; j++){
			average = (pixels[j][1] + pixels[j][2] + pixels[j][3]) / 3;
			for(int i = 0; i < 3; i++){
				pixels[j][i] = checkvalue(average);
			}
	}
}

void picture::flip_h(){
	int place_holder;
	for(int j = 0; j < columns/2; j++){
		for(int i = 0; i < 3; i++){
			place_holder = pixels[j][i];
			pixels[j][i] = checkvalue(pixels[columns - (j+1)][i]);
			pixels[columns - (j+1)][i] = checkvalue(place_holder);
		}
	}
}

void picture::negate_R(){
	for(int j = 0; j < columns; j++){
		pixels[j][1] = checkvalue(max_color - pixels[j][1]);
	}
}

void picture::negate_G(){
	for(int j = 0; j < columns; j++){
		pixels[j][2] = checkvalue(max_color - pixels[j][2]);
	}
}

void picture::negate_B(){
	for(int j = 0; j < columns; j++){
		pixels[j][3] = checkvalue(max_color - pixels[j][3]);
	}
}

void picture::flat_R(){
	for(int j = 0; j < columns; j++){
		pixels[j][1] = 0;
	}
}

void picture::flat_G(){
	for(int j = 0; j < columns; j++){
		pixels[j][2] = 0;
	}
}

void picture::flat_B(){
	for(int j = 0; j < columns; j++){
		pixels[j][3] = 0;
	}
}

int picture::checkvalue(const int i){
	if( i >= 0 && i <= max_color ){
		return i;
	} else if( i < 0) {
		return 0;
	} else if( i > max_color) {
		return max_color;
	}
}



