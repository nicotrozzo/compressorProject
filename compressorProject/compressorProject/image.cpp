#include "image.h"


bool image::imageInit(string filename, string path, string extension)
{
	this->filename = filename;
	this->extension = extension;
	this->path = path;
	if (extension == ".var")
	{
		if ((bitmap = al_load_bitmap("pregunta.png")) == NULL)
		{
			return false;
		}
	}
	else if ((bitmap = al_load_bitmap(path.c_str())) == NULL) 
	{
		return false;
	}
	width = al_get_bitmap_width(bitmap);
	height = al_get_bitmap_height(bitmap);
	selected = false;
	return true;
}

void image::toogleSelection()
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

string image::getExtension()
{
	return extension;
}

string image::getPath()
{
	return path;
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