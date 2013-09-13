#include "Manip.h"
//this class does everything on part 2, as well as high contrast as a bonus

using namespace std;

Manip::Manip() //empty constructor
{
}

void Manip::negate_red(int data[], int max_color, int size) //change red from high to low or vice versa
{
    for (int i = 0; i < size - 2; i += 3)
    {
        data[i] = abs(max_color-data[i]);
    }
}

void Manip::negate_green(int data[], int max_color, int size) //change green from high to low or vice versa
{
    for (int i = 1; i < size - 1; i += 3)
    {
        data[i] = abs(max_color-data[i]);
    }
}

void Manip::negate_blue(int data[], int max_color, int size) //change blue from high to low or vice versa
{
    for (int i = 2; i < size; i += 3)
    {
        data[i] = abs(max_color-data[i]);
    }
}

void Manip::flip_horizontal(int data[], int size) //flip image horizontally
{
    int tempr;
    int tempg;
    int tempb;
    for (int i = size - 1; i >= size/2; i -= 3)
    {
        tempb = data[i];
        tempg = data[i-1];
        tempr = data[i-2];
        data[i] = data[size + 1 - i];
        data[i-1] = data[size - i];
        data[i-2] = data[size - 1 - i];
        data[size + 1 - i] = tempb;
        data[size - i] = tempg;
        data[size - 1 - i] = tempr;
    }
}
        
void Manip::grey_scale(int data[], int size) //averaged rgb value
{
    for (int i = 1; i < size - 1; i += 3)
    {
        data[i] = (data[i-1] + data[i] + data[i+1])/3;
        data[i-1] = data[i+1] = data[i];
    }
}
void Manip::flatten_red(int data[], int size)  //red = 0
{
    for (int i = 0; i < size - 2; i += 3)
    {
        data[i] = 0;
    }
}
void Manip::flatten_green(int data[], int size)  //green = 0
{
    for (int i = 1; i < size - 1; i += 3)
    {
        data[i] = 0;
    }
}
void Manip::flatten_blue(int data[], int size)  //blue = 0
{
    for (int i = 2; i < size; i += 3)
    {
        data[i] = 0;
    }
}
void Manip::extreme_contrast(int data[], int max_color, int size) //either min or max color depends on whether color is below or above half of the maximum color bits
{
    for (int i = 0; i < size; i++)
    {
        if (data[i] <= max_color/2)
        {
            data[i] = 0;
        }
        else
        {
            data[i] = max_color;
        }
    }
}
