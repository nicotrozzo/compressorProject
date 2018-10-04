#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "lodepng.h"
#include <iostream>

using namespace std;

algo compressor(const char* filename, unsigned threshold)
{
	unsigned char *RGB;
	unsigned heigh, width, size;
	if (LodePNG_decode32_file(&RGB, &heigh, &width, filename))
	{
		cout << error << endl;
		return erro;            //algún error
	}
	size = heigh * width * 4;

}

int recursive(unsigned char* rgb, unsigned maxSide, unsigned mySide, unsigned threshold, string& buffer)
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
	if (weight < threshold)
	{



	}
	else
	{

	}
}