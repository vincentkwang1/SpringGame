#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

#include "ppm.h"

//init with default values

void ppm::init() {
    width = 0;
    height = 0;
    max_col_val = 255;
}

//create a PPM object

ppm::ppm() {
    init();
}

//create a PPM object and fill it with data stored in fname 

ppm::ppm(const std::string &fname) {
    init();
}

//create an "epmty" PPM image with a given width and height;the R,G,B arrays are filled with zeros
//needed
ppm::ppm(const unsigned int _width, const unsigned int _height) {
    init();
    width = _width;
    height = _height;
    nr_lines = height;
    nr_columns = width;
    size = width*height;
}