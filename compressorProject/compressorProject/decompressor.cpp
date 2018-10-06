#include <iostream>
#include <fstream>
#include "lodepng.h"

#define A 255
 
using namespace std;

/*Recibe un path a un archivo comprimido en formato .var y lo descomprime en un archivo
del mismo nombre en formato png*/
bool decompress(const char* filename)
{
	int hojas = 0, nodos = 0;
	ifstream src;
	unsigned size;
	string line;
	src.open(filename, std::ifstream::in);
	getline(src,line);							//saco el tamaño de la imagen original 
	size = atoi(line.c_str());

}


void recursiveDesc(ifstream src, unsigned char* buffer, int hojas, int nodos, unsigned size)		//debe estar todo como el culo porque me volvi loco y entre a cambiar cosas
{
	if (src.get() == 'N')
	{
		nodos++;
	}
	else if (src.get() == 'H')
	{
		if (hojas == 4)
		{
			hojas = 0;
		}
		hojas++;
		unsigned char r, g, b;
		r = ifs.get();		//cargo rojo
		g = ifs.get();		//cargo verde
		b = ifs.get();		//cargo azul
		if (hojas == 1)				//me fijo de estar en un primer cuadrante
		{
			for (int i = 0; i < (size*4/(2*nodos)); i++)
			{
				buffer[i+4] = r;
			}
		}
		else if (hojas == 2)		//me fijo de estar en un segundo cuadrante
		{

		}
		else if (hojas == 3)		//me fijo de estar en un tercer cuadrante
		{

		}
		else if (hojas == 4)		//me fijo de estar en un cuarto cuadrante
		{

		}
	}
}