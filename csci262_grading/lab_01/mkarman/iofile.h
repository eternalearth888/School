#ifndef IOFILE_H
#define IOFILE_H
#include <string>
#include <fstream>


class IOFile
{
public:
	IOFile();
	void input_file(std::ifstream &input, std::string file_name, int* read_position, int buffer[]);
	void output_file(std::string file_name, bool* first_time, int buffer[]);
	int col;
    int colr;
	std::string header;
	bool eof;
private:
    static const int HEADER = 3;
    char carriage_check;
};
#endif
