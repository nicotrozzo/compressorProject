#include <iostream>
#include "image.h"
#include <iterator>
#include <vector>
#include <algorithm>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include "menu.h"

using namespace std;
using namespace boost::filesystem;

#define PATH "C:\Users\fliatondi\Documents\FACULTAD\EDA\imagenes"


int main(int argc, char *argv[])
{
	menu Menu;
	if (Menu.getInicialization() == true)
	{

		if (Menu.see_dirContent(argv[1]))	//le mando el path pasado por linea de comandos
		{
			Menu.showAndProcessContent();
		}

	}
	else
	{
		cout << "No se pudo crear el menu" << endl;
	}
	cout << "FIN PROGRAMA" << endl;;
	return 0;
}