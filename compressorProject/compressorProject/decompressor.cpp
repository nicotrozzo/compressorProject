#include <iostream>
#include <fstream>
#include "lodepng.h"
 
using namespace std;


bool decompress(const char* filename)
{
  
}


void recursive(const char* filename)
{
	ifstream ifs;
	ifs.open(filename, std::ifstream::in);
	if (ifs.get() == 'N')
	{

	}
	else
	{

	}
}