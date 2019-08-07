#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#if defined(WIN32) || defined(_WIN32)
#include <windows.h>
#endif
#define VEGTELEN 9999

#define SOR_MERET 50//txt sorai max ilyen hosszúak lehetnek
#define MEGALLO_MERET 5
#define MEGALLOK "megallonevek.txt"
#define MTX "mtx2.csv"
#define CAC_MERET 33
#define GYAKORISAG "gyakorisag1.txt"
#define JARATOK "jaratok1.csv"
#define SORTOMB_MERET 50
#define TMP_MERET 10

#include "fuggvenyek.h"
#include "iskola.h"


int main()
{
	setlocale(LC_ALL, "");
#if defined(WIN32) || defined(_WIN32)
	SetConsoleCP(1250); SetConsoleOutputCP(1250);
#endif
	int sorokszama = 0, induloszama, celszama, minido = 0, atszall = 0, hossz = 0, **graf, i,  jaratokszama = 0, jo=0;
	char **megallonevek, indulo[SOR_MERET], cel[SOR_MERET];
	FILE* f;
	f = (FILE*)malloc(sizeof(FILE));
	megallonevek = (char**)malloc(sizeof(char));
	megallonevek = megallonevbeolvaso(megallonevek, &sorokszama);
	if (megallonevek == NULL) {
		getchar();
		return 0;
	}
	while (jo == 0) {
		jo = 1;
		hossz = 0;
		printf("Adja meg az induló megallót!\n");
		while (hossz == 0 || induloszama == -1) {
			hossz = getline(indulo, SOR_MERET);
			induloszama = megallo_ellenorzo(megallonevek, indulo, sorokszama);
			if (hossz == 0) { printf("Kérem adjon meg egy induló megállót!\n"); }
			if (induloszama == -1 && hossz!=0) { printf("A városban nincs ilyen megálló! Kérem adjon meg egy létezõ megállót!\n"); }
		}
		hossz = 0;
		printf("Adja meg a cél megállót!\n");
		while (hossz == 0 || celszama == -1) {
			hossz = getline(cel, SOR_MERET);
			celszama = megallo_ellenorzo(megallonevek, cel, sorokszama);
			if (hossz == 0) { printf("Kérem adjon meg egy cél megállót!\n"); }
			if (celszama == -1 && hossz != 0) { printf("A városban nincs ilyen megálló! Kérem adjon meg egy létezõ megállót!\n"); }
		}
		if (induloszama == celszama)
		{
			printf("Ugyanazt a megállót adta meg kétszer!\nKérem adjon meg két különbözõ megállót!\n");
			jo = 0;
		}
	}
	hossz = matrixmeret(f);
	if (hossz == 0) {
		printf("A befejezéshez nyomja meg az enter-t\n");
		indulo[0]=getchar();
		return 1;
	}
	graf = (int**)malloc(sizeof(int*));
	graf = dimmtxfgv(f, graf, hossz);
	free(f);
	Lista **jaratok = NULL;
	jaratok = megalloBeolvas(jaratok, &jaratokszama);
	if (jaratok == NULL) {
		indulo[0] = getchar();
		return 0;

	}
	Lista *utvonal;
	utvonal = moddijkstra(graf, induloszama, jaratok, celszama, hossz, &minido, jaratokszama);
	for (i = 0; i < sorokszama; i++) {
		free(graf[i]);
	}
	free(graf);
	printf("\n\n\n");
	print_utvonal(utvonal, megallonevek);
	atszall = melyikjarat(utvonal, jaratok, megallonevek);
	for (i = 0; i < sorokszama; i++)//megallonevbeolvaso-nál használt soroknak lefoglalt memória felszabadítása
	{
		free(megallonevek[i]);
	}
	free(megallonevek);
	listafelszabaditas(utvonal);
	printf("A minimális utazási idõ: %d perc\naz átszállásra fordított maximális idõ: %d perc\nösszesen maximum: %d perc\n", minido, atszall, minido + atszall);
	for (i = 0; i < jaratokszama; i++) {
		listafelszabaditas(jaratok[i]);
	}
	printf("A befejezéshez nyomja meg az enter-t\n");
	indulo[0]=getchar();
	return 0;
}