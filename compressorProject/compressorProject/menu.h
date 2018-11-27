#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "image.h"
#include <iterator>
#include <list>
#include <algorithm>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost::filesystem;

#define DISPLAY_WIDHT	1000
#define DISPLAY_HEIGHT	600

typedef enum { INVALID, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ENTER, RIGHT, LEFT, A, N }keyPressed;

class menu
{
public:
	menu(bool compress_);
	~menu();
	void menuInit();
	bool getInicialization();
	bool see_dirContent(const char* dir);
	void showAndProcessContent();
	void show();
	void process();
	bool inminentEvent();
	bool checkValidEvent();
	void actionDecompress();
	void actionCompress(int threshold);
private:
	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE * queue;
	ALLEGRO_EVENT event;
	ALLEGRO_FONT * font;
	list<image> images;
	image* img;
	list<image>::iterator itrImage;
	bool inicialization;
	unsigned int pages;
	unsigned int pageIndex;
	keyPressed key;
	unsigned int imageIndex;
	bool compress;
};