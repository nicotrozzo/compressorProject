#include "lodepng.h"
#include "lodepng.cpp"
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

#define MAXTHRESHOLD 3255
#define PIXELSIZE 4		//en bytes

void recursiveComp(unsigned char* rgb, unsigned maxSide, unsigned mySide, unsigned threshold, string& buffer);


/*Guarda en .var*/
bool compressor(const char* filename, unsigned threshold)
{
	bool ret = false;
	unsigned char *rgb;
	unsigned height, width, size;
	string compFilename = filename;
	compFilename.replace(compFilename.length()-strlen("png"),strlen("png"),"var");	//cambia la terminacion .png por .var elegida para el archivo comprimido
	ofstream compressedImage(compFilename);
	if (!lodepng_decode32_file(&rgb, &height, &width, filename))
	{
		if ((height == width) && ((log2(static_cast<double>(width*height))-floor(log2(static_cast<double>(width*height))) )== 0))	//si la imagen es cuadrada y w*h es potencia de 2
		{
			string buffer;	//crea buffer para ir guardando la informacion del archivo
			size = height * width * PIXELSIZE;
			buffer += to_string(width);	//escribo el ancho de la imagen
			buffer += '\n';					//enter para informar que empieza el arbol
			recursiveComp(rgb, size, size, floor(threshold*MAXTHRESHOLD / 100), buffer);
			//escribir buffer en archivo
		}
	}
	return ret;
}

/*recursiveComp: 
Recibe: -Puntero a la primera posicion del cuadrante a analizar (arriba a la izquierda)
		-Valor del ancho total de la imagen
		-Valor del ancho del cuadrante en el que esta
		-Valor del threshold solicitado (NO EL PORCENTAJE, EL VALOR ABSOLUTO)
		-Referencia al buffer en el que va escribiendo la informacion del archivo comprimido
*/
void recursiveComp(unsigned char* rgb, unsigned maxSide, unsigned mySide, unsigned threshold, string& buffer)
{
	unsigned Rmin = 255, Rmax = 0, Gmin = 255, Gmax = 0, Bmin = 255, Bmax = 0;
	unsigned weight = 0;
	for (int i = 0; i < mySide; i++)	//calcula los minimos y maximos del arreglo de pixeles
	{
		for (int j = 0; j < mySide; j++)
		{
			if (rgb[PIXELSIZE*i*j + i*(maxSide-mySide)] < Rmin)
				Rmin = rgb[PIXELSIZE * i*j + i * (maxSide - mySide)];
			else if (rgb[PIXELSIZE*i*j + i*(maxSide-mySide)] > Rmax)
				Rmax = rgb[PIXELSIZE * i*j + i * (maxSide - mySide)];
			if (rgb[PIXELSIZE * i*j + i * (maxSide - mySide) + 1] < Gmin)
				Gmin = rgb[PIXELSIZE * i*j + i * (maxSide - mySide) + 1];
			else if (rgb[PIXELSIZE * i*j + i * (maxSide - mySide) + 1] > Gmax)
				Gmax = rgb[PIXELSIZE * i*j + i * (maxSide - mySide) + 1];
			if (rgb[PIXELSIZE * i*j + i * (maxSide - mySide) + 2] < Bmin)
				Bmin = rgb[PIXELSIZE * i*j + i * (maxSide - mySide) + 2];
			else if (rgb[PIXELSIZE * i*j + i * (maxSide - mySide) + 2] > Bmax)
				Bmax = rgb[PIXELSIZE * i*j + i * (maxSide - mySide) + 2];
		}
	}
	weight = Rmax - Rmin + Gmax - Gmin + Bmax - Bmin;
	if ((weight < threshold) || (mySide/2 == 1))
	{
		unsigned long int totalRed = 0, totalGreen = 0, totalBlue = 0;
		for (int i = 0; i < mySide; i++)
		{
			for (int j = 0; j < mySide; j++)
			{
				totalRed += rgb[PIXELSIZE * i*j + i * (maxSide - mySide)];
				totalGreen += rgb[PIXELSIZE * i*j + i * (maxSide - mySide) + 1];
				totalBlue += rgb[PIXELSIZE * i*j + i * (maxSide - mySide) + 2];
			}
		}		
		buffer += 'H';
		buffer += static_cast<unsigned char>(totalRed/(mySide*mySide)); //guarda el promedio de cada color que ocupa un byte cada uno
		buffer += static_cast<unsigned char>(totalGreen/(mySide*mySide));
		buffer += static_cast<unsigned char>(totalBlue/(mySide*mySide));
	}
	else
	{
		buffer += 'N';	//marca como nodo la posicion actual
		recursiveComp(rgb,maxSide,mySide/2,threshold,buffer);	//llama para el cuadrante de arriba a la izquierda
		recursiveComp(rgb+PIXELSIZE*mySide/2,maxSide,mySide/2,threshold,buffer);	//llama para el cuadrante de arriba a la derecha
		recursiveComp(rgb+PIXELSIZE*mySide/2*maxSide,maxSide,mySide/2,threshold,buffer);	//llama para el cuadrante de abajo a la izquierda
		recursiveComp(rgb+PIXELSIZE*mySide/2*maxSide+PIXELSIZE*mySide/2,maxSide,mySide/2,threshold,buffer); //llama para el cuadrante de abajo a la derecha
	}
}
