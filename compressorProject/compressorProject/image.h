#pragma once
#include <iostream>
#include <string>
#include <allegro5\allegro.h>

using namespace std;

class image
{
public:
	image();
	~image();
	bool imageInit(string filename, string path, string extension);
	void toogleSelection();
	void setSelected(bool valor);
	//bool loadBitmap();
	string getFilename();
	ALLEGRO_BITMAP* getBitmap();
	float getBitmapWidth();
	float getBitmapHeight();
	bool isSelected();
private:
	string filename;
	ALLEGRO_BITMAP *bitmap;
	bool selected;
	float width;
	float height;
};