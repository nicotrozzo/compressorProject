#include "image.h"

image::image()
{
	//nada
}

bool image::imageInit(string filename)
{
	this->filename = filename;
	if ((bitmap = al_load_bitmap(filename.c_str())) == NULL) 
	{
		return false;
	}
	selected = false;
	return true;
}

bool image::toogleSelection()		//fijarse si conviene devolver el estado en el que dejo a selected o no
{
	selected = (selected == true ? false : true);
	return selected;
}

bool image::isSelected()
{
	return selected;
}

string image::getFilename()
{
	return filename;
}

image::~image()
{
	al_destroy_bitmap(bitmap);
}