#include <cstdlib>

#include "EncodingMock.h"

//TODO:

int BitConverter::ToInt32(unsigned char* bytes)
{
	// since the server is .NET, this is a little endian interpretation
	// assuming 32 bits
	unsigned int intVal = bytes[0];
	intVal = intVal | (bytes[1] << 8);
	intVal = intVal | (bytes[2] << 16);
	intVal = intVal | (bytes[3] << 24);
	return intVal;
}

unsigned char* BitConverter::GetBytes(int i)
{
	// generating 32 bits, little endian
	unsigned int uint = i;
	unsigned char* bytes = new unsigned char[4];
	bytes[0] = 0x000000FF & uint;
	bytes[1] = (0x0000FF00 & uint) >> 8;
	bytes[2] = (0x00FF0000 & uint) >> 16;
	bytes[3] = (0xFF000000 & uint) >> 24;
	return bytes;
}

char* UTF8Enc::GetString(unsigned char* bytes)
{
	//TODO: for now i'm cheating everything as ascii.
	return (char*)bytes;
}