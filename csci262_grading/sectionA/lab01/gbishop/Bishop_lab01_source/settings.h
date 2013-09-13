// Settings (buffer size, default directory, etc)

#pragma once // is this redundeant with the define IMAGE_H ? Ask on wed

// "header gaurds" as per class on monday 8/26
#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

const string filename_default_directory = ""; // eg: "I:\\CSCI262\\lab_01_sampleinputs\\"
const unsigned int BUFFER_SIZE = 3000;


const int RANDOM_AMOUNT = 100;
const char DELIM_CHAR = 32; // (Space) - for output only!

#endif