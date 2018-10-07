#include <iostream>
#include <fstream>
#include <cmath>
#include "lodepng.h"

#define A 255
#define PIXELSIZE 4		//en bytes

using namespace std;

void recursiveDesc(ifstream& src, unsigned char* image, unsigned int depth, unsigned int totalWidth);

/*Recibe un path a un archivo comprimido en formato .var y lo descomprime en un archivo
del mismo nombre en formato png*/
bool decompress(const char* filename)
{
	bool ret = false;
	string strFilename(filename), dotVar(".var");
	if (strFilename.substr(strFilename.length()-strlen(".var")) == dotVar)	//si la terminacion del archivo es .var, continua
	{
		ifstream src(filename, ios::binary);
		string line;								//para obtener la primera linea del archivo
		getline(src, line);							//saco el ancho de la imagen original 
		unsigned int width = atoi(line.c_str());
		unsigned char* image = new unsigned char[width*width*PIXELSIZE];
		recursiveDesc(src, image, 0, width);	//descomprime el archivo, carga en image la informacion de los pixeles
		string descFilename = filename;		//nombre del archivo a crear
		descFilename.replace(descFilename.length() - strlen("var"), strlen("var"), "png");	//cambia la terminacion .var por .png elegida para el archivo comprimido
		if (lodepng_encode32_file(descFilename.c_str(), image, width, width))
		{
			ret = true;
		}
		delete[] image;
	}
	return ret;
}

/*recursiveDesc:
Recibe: -referencia al archivo comprimido
		-puntero image con la informacion de cada pixel que sera llenada(apuntando al primer byte del cuadrante que esta analizando)
		-profundidad del arbol en la que esta
		-ancho total de la imagen
*/
void recursiveDesc(ifstream& src, unsigned char* image, unsigned int depth, unsigned int totalWidth )
{
	char c = src.get();
	if (c == 'N')	//si encuentra un nodo
	{
		recursiveDesc(src, image, depth + 1, totalWidth);	//llama a la recursiva para cada cuadrante
		recursiveDesc(src,image + floor(PIXELSIZE *totalWidth/pow(2,depth)),depth+1,totalWidth); //arriba a la derecha
		recursiveDesc(src,image + floor(PIXELSIZE *totalWidth*(totalWidth/pow(2,depth))),depth+1,totalWidth);	//abajo a la izquierda
		recursiveDesc(src,image + floor(PIXELSIZE * totalWidth / pow(2, depth) + PIXELSIZE * totalWidth*(totalWidth / pow(2, depth))),depth+1,totalWidth); //abajo a la derecha
	}
	else if(c == 'H')	//si encuentra una hoja, caso base
	{
		for (int i = 0; i < totalWidth / pow(2, depth); i++)	//llena todo el cuadrante del color de la hoja
		{
			for (int j = 0; j < totalWidth / pow(2, depth); j++)
			{
				image[PIXELSIZE*i + j*totalWidth*PIXELSIZE] = src.get();
				image[PIXELSIZE*i + j * totalWidth*PIXELSIZE + 1] = src.get();
				image[PIXELSIZE*i + j * totalWidth*PIXELSIZE + 2] = src.get();
				image[PIXELSIZE*i + j * totalWidth*PIXELSIZE + 3] = A;	//transparencia 100%
			}
		}
	}
}

/*GONZA VERSION
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

}*/