#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "lodepng.h"
#include "lodepng.cpp"
#include <iostream>
#include <string>

using namespace std;

bool compressor(const char* filename, unsigned threshold)
{
	bool ret = true;
	unsigned char *rgb;
	unsigned height, width, size;
	string buffer;
	if (lodepng_decode32_file(&rgb, &height, &width, filename))
	{
		ret = false;        
	}
	size = height * width * 4;
	buffer += to_string(height*width);			//cargo la cantidad de pixeles de la imagen	hay que ver como mierda lo hacemos
	buffer += '-';					//mando un guion para informar que empieza el arbol
	recursive(rgb,size,size,threshold,buffer);
	//escribir buffer en archivo
	return ret;
}

void recursive(unsigned char* rgb, unsigned maxSide, unsigned mySide, unsigned threshold, string& buffer)
{
	unsigned Rmin = 255, Rmax = 0, Gmin = 255, Gmax = 0, Bmin = 255, Bmax = 0;
	unsigned weight = 0;
	for (int i = 0; i < mySide; i++)	//calcula los minimos y maximos del arreglo de pixeles
	{
		for (int j = 0; j < mySide; j++)
		{
			if (rgb[4*i*j + i*(maxSide-mySide)] < Rmin)
				Rmin = rgb[4 * i*j + i * (maxSide - mySide)];
			else if (rgb[4*i*j + i*(maxSide-mySide)] > Rmax)
				Rmax = rgb[4 * i*j + i * (maxSide - mySide)];
			if (rgb[4 * i*j + i * (maxSide - mySide) + 1] < Gmin)
				Gmin = rgb[4 * i*j + i * (maxSide - mySide) + 1];
			else if (rgb[4 * i*j + i * (maxSide - mySide) + 1] > Gmax)
				Gmax = rgb[4 * i*j + i * (maxSide - mySide) + 1];
			if (rgb[4 * i*j + i * (maxSide - mySide) + 2] < Bmin)
				Bmin = rgb[4 * i*j + i * (maxSide - mySide) + 2];
			else if (rgb[4 * i*j + i * (maxSide - mySide) + 2] > Bmax)
				Bmax = rgb[4 * i*j + i * (maxSide - mySide) + 2];
		}
	}
	weight = Rmax - Rmin + Gmax - Gmin + Bmax - Bmin;
	if ((weight < threshold) || (mySide/2 == 1))
	{
		long int totalRed = 0, totalGreen = 0, totalBlue = 0;
		for (int i = 0; i < mySide; i++)
		{
			for (int j = 0; j < mySide; j++)
			{
				totalRed += rgb[4 * i*j + i * (maxSide - mySide)];
				totalGreen = rgb[4 * i*j + i * (maxSide - mySide) + 1];
				totalBlue = rgb[4 * i*j + i * (maxSide - mySide) + 2];
			}
		}		
		buffer += 'H';
		buffer += totalRed/(mySide*mySide); 
		buffer += totalGreen/(mySide*mySide); 
		buffer += totalBlue/(mySide*mySide); 
	}
	else
	{
		buffer += 'N';	//marca como nodo la posicion actual
		recursive(rgb,maxSide,mySide/2,threshold,buffer);	//llama para el cuadrante de arriba a la izquierda
		recursive(rgb+4*mySide/2,maxSide,mySide/2,threshold,buffer);	//llama para el cuadrante de arriba a la derecha
		recursive(rgb+4*mySide/2*maxSide,maxSide,mySide/2,threshold,buffer);	//llama para el cuadrante de abajo a la izquierda
		recursive(rgb+4*mySide/2*maxSide+4*mySide/2,maxSide,mySide/2,threshold,buffer); //llama para el cuadrante de abajo a la derecha
	}
}
