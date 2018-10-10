#include "menu.h"

menu::menu()
{
	menuInit();
	pages = 0;
	pageIndex = 0;
	imageIndex = 0;
}

void menu::menuInit()
{
	if (al_init() == true)
	{
		if ((display = al_create_display(DISPLAY_WIDHT, DISPLAY_HEIGHT)) != NULL)
		{
			if (al_install_keyboard() == true)
			{
				if (al_init_image_addon())
				{
					if (al_init_primitives_addon())
					{
						if (al_init_font_addon())
						{
							if (al_init_ttf_addon())
							{
								if ((font = al_load_ttf_font("AARDV.ttf", 11, 0)) != NULL)
								{
									if ((queue = al_create_event_queue()) != NULL)
									{
										al_register_event_source(queue, al_get_keyboard_event_source());
										inicialization = true;
										return;
									}
									else
									{
										cout << "No se pudo crear la cola de eventos" << endl;
									}
									al_destroy_font(font);
								}
								else
								{
									cout << "No se pudo crear font" << endl;
								}
								al_shutdown_ttf_addon();
							}
							else
							{
								cout << "No se pudo inicializar ttf addon" << endl;
							}
							al_shutdown_font_addon();
						}
						else
						{
							cout << "No se pudo inicializar font addon" << endl;
						}
						al_shutdown_primitives_addon();
					}
					else
					{
						cout << "No se pudi inicializar primitives addon" << endl;
					}
					al_shutdown_image_addon();
				}
				else
				{
					cout << "No se pudo inicializar image addon" << endl;
				}
			}
			else
			{
				cout << "No se pudo instalar el driver del teclado" << endl;
			}
			al_destroy_display(display);
		}
		else
		{
			cout << "No se pudo crear display" << endl;
		}
	}
	else
	{
		cout << "Fallo iniciando allegro" << endl;
	}
	inicialization = false;
	return;
}

bool menu::getInicialization()
{
	return inicialization;
}

bool menu::see_dirContent(const char* dir)
{
	img = new image;
	path p(dir);
	if (exists(p))
	{
		if (is_regular_file(p))
		{
			if (p.has_extension() && ((p.extension().string() == ".png") || (p.extension().string() == ".var")))
			{
				if (img->imageInit(p.filename().string(), p.filename().string(), p.extension().string()))
				{
					images.push_back(*img);
					return true;
				}
			}
		}
		else if (is_directory(p))
		{
			string Path = dir;
			for (directory_iterator itr(p); itr != directory_iterator(); itr++)
			{
				if ((is_regular_file(itr->path())) && (itr->path().has_extension()) && ((itr->path().extension().string() == ".png") || (itr->path().extension().string() == ".var")))
				{
					if (img->imageInit(itr->path().filename().string(), Path + "\\" + itr->path().filename().string(), itr->path().extension().string())) //falta ver como hago en la etapa de descompresion
					{
						images.push_back(*img);
					}
				}
			}
			pages = (int)(((images.size() % 9) != 0) ? ((images.size() / 9) + 1) : (images.size() / 9));
			return true;
		}

	}
	delete img;
	return false;
}

void menu::showAndProcessContent()
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	while (event.keyboard.keycode != ALLEGRO_KEY_ENTER)
	//while (key != ENTER)
	{
		if ((inminentEvent() == true) && (key != INVALID))
		{
			process();
			//ver el tema de paginas e imagen
		}
		show();
	}
	//llamar al compresor y descompresor... acordarse del treshold
}

void menu::process()
{
	switch (key) //falta ver que pasa cuando cambio selected con la imagen
	{
	case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		if (key - 1 + 9 * pageIndex < images.size())
		{
			itrImage = images.begin();
			advance(itrImage, key - 1 + 9 * pageIndex);
			itrImage->toogleSelection();
		}
		key = INVALID;
		break;
	case RIGHT:
		if (pageIndex < pages)
		{
			pageIndex++;
		}
		key = INVALID;
		break;
	case LEFT:
		if (pageIndex >= 1)
		{
			pageIndex--;
		}
		key = INVALID;
		break;
	case A:
		for (itrImage = images.begin(); itrImage != images.end(); itrImage++)
		{
			itrImage->setSelected(true);
		}
		key = INVALID;
		break;
	case N:
		for (itrImage = images.begin(); itrImage != images.end(); itrImage++)
		{
			itrImage->setSelected(false);
		}
		key = INVALID;
		break;
	case ENTER:
		break;
	default:
		key = INVALID;
		break;
	}
}

void menu::show()
{
	ALLEGRO_BITMAP * temp;
	float tWidth;
	float tHeihght;
	float mosaicWidth = DISPLAY_WIDHT / 4;
	float mosaicHeight = DISPLAY_HEIGHT / 4;
	float margenX = DISPLAY_WIDHT / 16;
	float margenY = DISPLAY_HEIGHT / 16;
	float dx;
	float dy = margenY;

	al_clear_to_color(al_map_rgb(0, 0, 0));

	for (imageIndex = 0; (imageIndex < 9) && (imageIndex < (images.size() - 9 * pageIndex)); imageIndex++)
	{
		itrImage = images.begin();
		advance(itrImage, imageIndex + 9 * pageIndex);
		temp = itrImage->getBitmap();
		tWidth = itrImage->getBitmapWidth();//al_get_bitmap_width(temp);
		tHeihght = itrImage->getBitmapHeight();//al_get_bitmap_height(temp);
		dx = ((imageIndex % 3) + 1) * margenX + (imageIndex % 3) * mosaicWidth;
		if( (imageIndex == 3) || (imageIndex == 6))
		{
			dy += margenY + mosaicHeight;
		}
		if (itrImage->isSelected())
		{
			al_draw_filled_rectangle(dx - (margenX / 2), dy - (margenY / 2), dx + (margenX / 2) + mosaicWidth, dy + (margenY / 2) + mosaicHeight, al_map_rgb(0, 255, 0));
		}
		al_draw_scaled_bitmap(temp, 0, 0, tWidth, tHeihght, dx , dy, mosaicWidth, mosaicHeight, 0);
		al_draw_text(font, al_map_rgb(255, 255, 255), dx, dy + mosaicHeight + margenY / 6, 0, itrImage->getFilename().c_str());
	}
	al_flip_display();
}



bool menu::inminentEvent()
{
	if (al_get_next_event(queue, &event))
	{
		return checkValidEvent();
	}
	return false;
}

bool menu::checkValidEvent()
{
	if (event.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		switch (event.keyboard.keycode)
		{
		case ALLEGRO_KEY_1:
			key = ONE;
			break;
		case ALLEGRO_KEY_2:
			key = TWO;
			break;
		case ALLEGRO_KEY_3:
			key = THREE;
			break;
		case ALLEGRO_KEY_4:
			key = FOUR;
			break;
		case ALLEGRO_KEY_5:
			key = FIVE;
			break;
		case ALLEGRO_KEY_6:
			key = SIX;
			break;
		case ALLEGRO_KEY_7:
			key = SEVEN;
			break;
		case ALLEGRO_KEY_8:
			key = EIGHT;
			break;
		case ALLEGRO_KEY_9:
			key = NINE;
			break;
		case ALLEGRO_KEY_ENTER:
			key = ENTER;
			break;
		case ALLEGRO_KEY_RIGHT:
			key = RIGHT;
			break;
		case ALLEGRO_KEY_LEFT:
			key = LEFT;
			break;
		case ALLEGRO_KEY_A:
			key = A;
			break;
		case ALLEGRO_KEY_N:
			key = N;
			break;
		default:
			key = INVALID;
			break;
		}
		return true;
	}
	else
	{
		return false;
	}
}

menu::~menu()
{
	if (display != NULL)
	{
		al_destroy_display(display);
	}
	if (queue != NULL)
	{
		al_destroy_event_queue(queue);
	}
	//delete img;
}