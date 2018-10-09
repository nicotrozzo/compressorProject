#include "decompressor.h"
#include "compressor.h"
#include <fstream>

void copyFile(const char* srcFilename, const char * destFilename);

using namespace std;

int main(void)
{
	compressor("pruebafacil.png", 3);
	copyFile("pruebafacil.var","pruebafacil2.var");
	decompress("pruebafacil2.var");
	compressor("riverplate.png",0);
	copyFile("riverplate.var","inventaronel.var");
	decompress("inventaronel.var");
}

/*Copia el contenido de un archivo a otro*/
void copyFile(const char* srcFilename, const char * destFilename)
{
	ifstream src(srcFilename, ios::binary);
	src.seekg(0,ios::end);
	streampos size = src.tellg();

	char *data = new char[size];
	src.seekg(0, ios::beg);
	src.read(data, size);
	src.close();

	ofstream out(destFilename, ios::binary);
	out.write(data, size);
	out.close();
	delete[] data;
}