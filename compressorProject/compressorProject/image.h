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
	bool imageInit(string filename);
	bool toogleSelection();
	//bool loadBitmap();
	string getFilename();
	bool isSelected();
private:
	string filename;
	ALLEGRO_BITMAP *bitmap;
	bool selected;
};