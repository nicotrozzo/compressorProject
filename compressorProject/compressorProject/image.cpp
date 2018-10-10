#include "image.h"

//#define PATH "C:\\Users\\fliatondi\\Documents\\FACULTAD\\EDA\\imagenes\\imagenes-png-8.png"

image::image()
{
	//nada
}

bool image::imageInit(string filename, string path, string extension)
{
	this->filename = filename;
	if (extension == ".var")
	{
		if ((bitmap = al_load_bitmap("pregunta.png")) == NULL)
		{
			return false;
		}
	}
	else if ((bitmap = al_load_bitmap(path.c_str())) == NULL) //falta ver que hago cuando estpy en la etapa de descompresion
	{
		return false;
	}
	width = al_get_bitmap_width(bitmap);
	height = al_get_bitmap_height(bitmap);
	selected = false;
	return true;
}

void image::toogleSelection()		//fijarse si conviene devolver el estado en el que dejo a selected o no
{
	selected = (selected == true ? false : true);
}

void image::setSelected(bool valor)
{
	selected = valor;
}

bool image::isSelected()
{
	return selected;
}

string image::getFilename()
{
	return filename;
}

ALLEGRO_BITMAP* image::getBitmap()
{
	return bitmap;
}

float image::getBitmapWidth()
{
	return width;
}

float image::getBitmapHeight()
{
	return height;
}

image::~image()
{
	if (bitmap != NULL)
	{
		al_destroy_bitmap(bitmap);
	}
}