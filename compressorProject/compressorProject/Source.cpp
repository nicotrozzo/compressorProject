#include <iostream>
#include <cstdlib>
#include "menu.h"

using namespace std;

int main(int argc, char *argv[])
{
	if ((argc == 2) || (argc == 3))
	{
		bool compress;
		argc == 2 ? compress = false : compress = true;
		menu Menu(compress);
		if (Menu.getInicialization() == true)
		{
			if (Menu.see_dirContent(argv[1]))	//le mando el path pasado por linea de comandos
			{
				Menu.showAndProcessContent();
				if (argc == 3)	//si mandaron tres parametros, interpreta que piden comprimir
				{
					if ((strtol(argv[2], NULL, 10) != 0) || !strcmp("0", argv[2]))	//si argv[2] es un numero, se envia como threshold
					{
						Menu.actionCompress(atoi(argv[2]));
					}
					else
					{
						cout << "Threshold invalido" << endl;
					}
				}
				else if (argc == 2)	//si mandaron dos parametros se interpreta que quieren descomprimir
				{
					Menu.actionDecompress();
				}
			}
		}
		else
		{
			cout << "No se pudo crear el menu" << endl;
		}
	}
	else
	{
		cout << "Ingrese los parametros path y threshold (solo en caso de querer comprimir)" << endl;
	}
	cout << "Programa terminado, presione Enter para salir" << endl;
	getchar();
	return 0;
}