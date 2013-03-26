#ifndef ENCODING_MOCK_H
#define ENCODING_MOCK_H

class BitConverter
{
public:
	static int ToInt32(unsigned char* bytes);
	static unsigned char* GetBytes(int i);
};


class UTF8Enc
{
public:
	static char* GetString(unsigned char* bytes);
};

#endif