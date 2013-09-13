// process.h - contains functions to manipulate the contents of buffer arrays

#pragma once // is this redundeant with the define

// "header gaurds" as per class on monday 8/26
#ifndef PROCESS_H
#define PROCESS_H

// Std library includes ------where is the 'proper' place to put these - before or after ifndef ? --
#include <cstdlib>
#include <ctime>
using namespace std;

#include "settings.h"

// Required functions

void negate_red(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width, unsigned int image_depth);
void negate_green(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width, unsigned int image_depth);
void negate_blue(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width, unsigned int image_depth);
void negate_color(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width, unsigned int image_depth, unsigned int color);

void grey_scale(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width);

void flatten_red(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width);
void flatten_green(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width);
void flatten_blue(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width);
void flatten_color(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width, unsigned int color);

void flip_horizontal(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width);


// "Bonus" functions

void extreme_contrast(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width, unsigned int image_depth);
void random_noise(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width, unsigned int image_depth, unsigned int range, int random_offset);
void horizontal_blur(unsigned int buffer_array[BUFFER_SIZE], unsigned int image_width);

#endif