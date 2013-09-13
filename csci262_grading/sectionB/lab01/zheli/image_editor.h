#include <cmath>
#include "image_pix.h"

//the function of negate_red
pix negate_red(int max, pix p){
	p.red = max - p.red;
	return p;
}

//the function of negate_green
pix negate_green(int max, pix p){
	p.green = max - p.green;
	return p;
}

//the function of negate_blue
pix negate_blue(int max, pix p){
	p.blue = max - p.blue;
	return p;
}

//the function of flip_horizontal
pix *flip_horizontal(pix *pointpix, int col){
	pix *currentpoint = new pix[col];
	for (int i = col -1; i >= 0; i--) {
         currentpoint[col - i -1] = pointpix[i];
	}
	return currentpoint;
}

//grey_scale function
pix grey_scale(pix p){
	int ave;
	ave = (p.blue + p.green + p.red) / 3;
	p.blue = ave;
	p.green = ave;
	p.red = ave;
	return p;
}

//flatten_red function
pix flatten_red(pix p){
	p.red = 0;
	return p;
}

//flatten_green function
pix flatten_green(pix p){
	p.green = 0;
	return p;
}

//flatte_blue fucntion
pix flatten_blue(pix p){
	p.blue = 0;
	return p;
}
	