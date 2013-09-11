#ifndef MANIP_H
#define MANIP_H
#include <cstdlib>

class Manip
{
public:
    Manip();
    void negate_red(int data[], int max_color, int size);
    void negate_green(int data[], int max_color, int size);
    void negate_blue(int data[], int max_color, int size);
    void flip_horizontal(int data[], int size);
    void grey_scale(int data[], int size);
    void flatten_red(int data[], int size);
    void flatten_green(int data[], int size);
    void flatten_blue(int data[], int size); 
    void extreme_contrast(int data[], int max_color, int size);       
};
#endif
