#pragma once
#include <iostream>
#include <string>
#include <allegro5\allegro.h>

using namespace std;

class image
{
public:
	~image();
	bool imageInit(string filename, string path, string extension);
	void toogleSelection();
	void setSelected(bool valor);
	string getFilename();
	string getExtension();
	string getPath();
	ALLEGRO_BITMAP* getBitmap();
	float getBitmapWidth();
	float getBitmapHeight();
	bool isSelected();
private:
	string filename;
	string extension;
	string path;
	ALLEGRO_BITMAP *bitmap;
	bool selected;
	float width;
	float height;
};