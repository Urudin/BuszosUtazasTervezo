typedef struct num {
	int szam1;
	int szam2;
} num;

typedef struct Lista {
	int megallo;
	struct Lista * kov; //rekurzív módon megadott ptr
} Lista;


Lista *listaVegere(Lista *eleje, int megallo) {
	Lista *mozgo, *uj;
	uj = (Lista*)malloc(sizeof(Lista));
	uj->megallo = megallo;
	uj->kov = NULL;
	if (eleje == NULL)//üres lista?
		return uj;
	for (mozgo = eleje; mozgo->kov != NULL; mozgo = mozgo->kov)
		; //üres ciklus, megkeresi az utolsó elemet
	mozgo->kov = uj;
	return eleje;
}
int megallo_ellenorzo(char **adatb, char megallo[], int sorok)//kmegallo a kiindulási megállót kapja meg inputnak, cmegallo a célmegállót kapja inputnak
{
	int i, cmp;//kiindulási megálló visszatérési értéke összehasonlítás után
	for (i = 0; i < sorok; i++)
	{
		cmp = strcmp(megallo, adatb[i]);
		if (cmp == 0)
		{
			return i;
		}
	}
	return -1;
}
char** megallonevbeolvaso(char **sortomb, int *sorokszama)
{
	FILE *fp;
	int i = 0;
	char sor[SOR_MERET];
	//elég egyszer bekapcsolni a program során az ékezetes betuk miatt
	fp = fopen(MEGALLOK, "r");
	if (fp == NULL)
	{
		printf("Nem sikerült megnyitni a %s nevu fájlt\n", MEGALLOK);
		printf("A kilépéshez nyomja meg az entert\n");
		return NULL;
	}
	while (fgets(sor, SOR_MERET, fp) != NULL)
	{
		(*sorokszama)++;//megnézi hány soros a fájl
	}
	rewind(fp);//visszatér a fájl elejére
	sortomb = (char**)malloc(*sorokszama * sizeof(char*));
	while (fgets(sor, SOR_MERET, fp) != NULL)
	{
		if (sor[strlen(sor) - 1] == '\n')
		{
			sor[strlen(sor) - 1] = '\0';
		} //sortöréseket \0 ra cseréli
		sortomb[i] = (char*)malloc((strlen(sor) + 1) * sizeof(char));
		strcpy(sortomb[i], sor);
		i++;
	}
	fclose(fp);
	return (sortomb);
}// program végén a MEMÓRIÁT felszabadítani!!!


num *maxertek(Lista * head) {           //Függvény egy lista legnagyobb értékû elemének megtalálására
	int i = 0;
	int d = 0;
	num * n;                          //num struktúrája n ptr létregozása
	n = (num*)malloc(sizeof(num));    //helyfoglalás n ptr által mutatott struktúrának
	Lista * jelenlegi = head;               //mutató állítása a lista elsõ elemére
	while (jelenlegi != NULL)                 //Amíg a listára állított mutató nem NULL, addig fut a ciklus
	{
		if (i < jelenlegi->megallo) {             //Ha az i értéke kisebb mint a lista jelenlegi elemében tárolt,
			i = jelenlegi->megallo; n->szam2 = d; //akkor az i új értéke a lista elemében tárolt érték lesz, valamint 
		}                                  //d változóban elmentésre kerül, hogy a lista hányadik elemétõl kapta i az értékét
		jelenlegi = jelenlegi->kov;              //A listára mutatót mutató a lista következõ elemére állítása
		d++;                                //d változó növelése
	}
	n->szam1 = i;                                 //n i értéke i=vel lesz egyenlõ
	return n;                               //Visszatérési érték num stukúrában, amely tartalmazza hogy melyik volt a lista legnagyobb eleme, és annak mennyi az értéke


}
void print_utvonal(Lista *head, char **megallok) { //Kiírató függvény, amely az útvonalat írja ki, az utvonal lista és a megallok 2D tömb segítségével
	Lista *jelenlegi = head;                         //Mutató a lista léptetéséhez
	int i = 0;                                     //i változó létrehozása, és 0 érték adása
	while (jelenlegi != NULL) {                        //Addig fut a ciklus, amíg el nem éri a lista végét
		printf("%s", megallok[jelenlegi->megallo]); //A lista adott elemének megallo változójában tárolt számnak megfelelõ indexû elem kiíratása a megallo 2D tömbbõl
		if (jelenlegi->kov != NULL) { printf("-"); }      //Ha még nem az utolsó megálló került kiíratásra, akkor egy '-' megjelenítése, a kimeneten a tagolt megjelenítésért
		if (i == 2) {                                 //Ha már 2 megállónév kiírásra került, akkor
			printf("\n");                     //sortörést hajtunk végre, hogy mindenképp kiférjen a konzol ablakba az útvonal
			i = 0;                             //a sortörés után az i változót vissza kell állítani
		}
		jelenlegi = jelenlegi->kov;                     //A listára mutató mutató következõ elemre állítása
		i = i + 1;
	}
}
Lista * listaklonozas(Lista * head) { //függvény Lista* típusú láncolt lista másolásához
	Lista * klon;                   //Lista típusú klon mutató létrehozása
	klon = (Lista*)malloc(sizeof(Lista)); //Helyfoglalás a klon mutatónak
	Lista * megtart = klon;               //megtart mutató létrehozása, és a klónlista elsõ elemére állítása
	Lista * megadott = head;              //megadott mutató létrehozása, és az eredeti lista elsõ elemére állítása
	while (megadott != NULL) {              //Addig fut a ciklus, amíg a megadott listán végig nem ér
		klon->megallo = megadott->megallo;//a klónlista aktuális elemének értékét az eredeti lista megegyezõ sorszámú elemének értékével lesz egyenlõ
		megadott = megadott->kov;         //Az eredeti listára állított mutató léptetése a következõ elemre
		klon->kov = NULL;                 //A klónlista következõ eleme nullára állítódik
		if (megadott != NULL)               //Ha az eredeti listára mutató mutató nem NULL értékre mutat
		{
			klon->kov = (Lista*)malloc(sizeof(Lista));//Helyfoglalás a klónlista következõ elemének
			klon = klon->kov;                         //A klon mutatót a következõ elemre állítja a függvény,
			klon->kov = NULL;                         //az ezt követõ mutatót pedig NULL-ra
		}
	}
	return megtart;                     //A megtart mutatóval tér vissza a függvény, amely a klónlista elsõ elemére mutat
}
void listafelszabaditas(Lista* lista) //függvény Lista* típusú láncolt listák felszabadításához
{
	Lista * tmp;                      //lista típusú tmp mutató létrehozása
	while (lista != NULL)             //Addig fut a ciklus amíg a lista összes eleme fel nem szabadul(eléri a lista végén lévõ NULL pointert)
	{
		tmp = lista;                  //tmp mutató lista elejére állítása
		lista = lista->kov;           //a lista kezdõmutatója a következõ elem mutatója lesz
		free(tmp);                    //a tmp mutató által mutatott memóriaterület felszabadul
	}
}
Lista** megalloBeolvas(Lista **head, int *sorokszama) //Függvény számokat tartalmazó csv fájl láncolt listákba történõ beolvasására
{
	FILE *fp;           //Fájlmutató
	Lista *ptr = NULL;  //Lista mutató, NULL-ra állítva
	int i = 0, j = 0, k = 0, l, m, d=0;
	char sor[SORTOMB_MERET]; //SORTOMB_MERET méretû tömb
	char tmp[TMP_MERET];    //TMP_MÉRET méretû tömb

	fp = fopen(JARATOK, "r"); //A JARATOK-ként defineolt fájl megnyitása
	if (fp == NULL)          //Ha nem a fájlt nem sikerül megnyitni, a függvény NULL pointerrel tér vissza
	{
		printf("Nem sikerült megnyitni a %s nevu fájlt\n", JARATOK); //A hiba üzenet kiíratása
		printf("A kilépéshez nyomja meg az entert\n");
		return NULL;
	}

	while (fgets(sor, 100, fp) != NULL) { //Addig fut a ciklus, míg a fájl végére nem ér
		(*sorokszama)++;            //sorokszama változó növelése, eredményképp megkapjuk hány sor(hány járat) van a fájlban
	}

	head = (Lista**)malloc(*sorokszama * sizeof(Lista*)); //Head tömbnek dinamikus memóriafoglalás
	rewind(fp);                                            //mutató visszaállítása a fájl elejére

	ptr = head[0];                                          //Lista ptr head[0] lista elejére állítása

	while (fgets(sor, 100, fp) != NULL)                    //Addig fut a ciklus, míg a fájl végére nem ér, számok mentése sor tömbben
	{
		l = 0;
		m = 0;
		head[k] = malloc(sizeof(Lista)); //dinamikus helyfoglalás a head[k] elemének
		d = strlen(sor);
		for (i = 0; i <= d; i++) {              //addig fut a ciklus, amíg az i ciklusváltozó kisebb, mint a sor tömbben található karakterek száma
			if (sor[i] == ';' && isdigit(sor[i + 1])) { //ha ; kerül a sortömbbe, és az azutáni elem szám, akkor növeljük az l változót
				l++;
			}
		}
		ptr = head[k];                              //Lista ptr head[k] elemére állítása
		for (i = 0; m <= l; i++) {                       //Addig fut, amíg a listában szereplõ számok száma kevesebb, mint a sortömbben lévõ számok száma
			if (isdigit(sor[i])) {                   //Ha a sor[i] elem szám
				tmp[j] = sor[i];                    //akkor a tmp[j]==sor[i]
				j++;                                //j változó növelése
			}
			else {
				tmp[j] = '\0';                      //ha már nem szám következik, akor a tmp[j] elemét üresre állítjuk
				ptr->megallo = atoi(tmp);           //A ptr-el mutatott listaelem megálló értéke a tmp-ben található számsor lesz számmá alakítva
				ptr->kov = malloc(sizeof(Lista));   //helyfoglalás a következõ elemnek
				m++;                                //növeljük az m változót, jelezve, hogy egy elem kerül a listába
				if (m <= l) {                          //Ha az listában szereplõ számok száma kevesebb, mint a sortömb hossza,
					ptr = ptr->kov;                 // a ptr-t a következõ listaelemre állítjuk
				}
				else {
					ptr->kov = NULL;                  //Ha a listában szereplõ számok száma nem kevesebb mint a sortömb hossza, akkor a kov mutatót NULL-ra lesz állítvaa
				}
				j = 0;                                //j mutató visszaállítása 0-ra, hogy elõröl töltõdjön a temp tömb
			}
		}
		k++;                                        //k növelése
	}
	head[k] = NULL;                                   //Ha a függvény elérti a fájl végét, akkor az utolsó head-et NULL-ra állítja, hogy késõbb könnyû legyen megtalálni a tömb végét
	fclose(fp);                                     //fájl bezárása
	return head;                                    //visszatérés a láncolt listákat tartalmazó tömbbel
}

int matrixmeret(FILE* fp) {
	int M_XY = 0, i = 0, pv = 0, d;
	char cac[CAC_MERET];
	fp = fopen("mtx2.csv", "r");
	if (fp) {
		while (fgets(cac, CAC_MERET, fp) != NULL) {
			M_XY++; // megnézi hogy a csv fájl hány sorból áll, míg null értéket nem kap a mutató
		}
		rewind(fp); // visszaugrik a fájl elejére a mutató
		while (fgets(cac, CAC_MERET, fp) != NULL) {
			d = strlen(cac);
			for (i = 0; i < d; i++) {
				if (cac[i] == ';') {
					pv++; // a pontosvesszõk darabszámának segítségével magkapjuk hogy hány oszlopos a csv fájlunk (pv+1
					// oszlopos)
				}
			}
			if (pv + 1 != M_XY) {
				fclose(fp);
				return 0; //wprintf(L"Nem négyzetes mtx van a .csv fájlban!\n");
			}
			pv = 0;
		}
		fclose(fp);
	}
	else {
		printf("Hiba a %s nevû fájl megnyitásakor\n", MTX);
		return 0; //wprintf(L"Nem lehet megnyitni a fájlt!\n");
	}
	return M_XY;

}
int **dimmtxfgv(FILE* fp, int** dimmtx, int M_XY)
{

	int i, j = 0, x = 0, y = 0, d=0; // M_XY a dimmtx sorának és oszlopának száma, ha négyzetes a mtx,
	char cac[CAC_MERET], tmp[TMP_MERET];
	fp = fopen(MTX, "r");
	dimmtx = (int**)calloc(M_XY, sizeof(int*));
	for (i = 0; i < M_XY; i++) {
		dimmtx[i] = (int*)calloc(M_XY, sizeof(int));
	}
	while (fgets(cac, CAC_MERET, fp) != NULL) {
		d = strlen(cac);
		for (i = 0; i <= d; i++) {
			if (isdigit(cac[i])) {
				tmp[j] = cac[i];
				j++;
			}
			if (cac[i] == ';' || cac[i] == '\0') {
				tmp[j] = '\0';
				dimmtx[x][y] = atoi(tmp);
				y++;
				j = 0; //így mindig a tmp 0. elemébe tudja menten a percet
			}
		}
		x++;
		y = 0;
	}
	fclose(fp);

	return (dimmtx);
}
int szomszed(Lista ** head, int ertek1, int ertek2, int jaratokszama) { //Függvény annak tesztelésére, hogy a megadott kétmegálló szerepel-e egymás mellett
	int i;                                              //Bármelyik járatban
	for (i = 0; i < jaratokszama; i++) {
		Lista *elozo, *jelenlegi;

		if (head[i] == NULL) { //ha NULL pointer az i. elem, azaz az összes megállón végigért a függvény, és nem talált egyezést, akkor 0 értékkel tér vissza
			return 0;
		}

		elozo = jelenlegi = head[i]; //Kezdetben mindkét listamutatót head[i]-re állítjuk
		while (jelenlegi != NULL) { //Addig fut a ciklus, amíg el nem érjük a lista végét
			if (jelenlegi->megallo == ertek2 && elozo->megallo == ertek1) { //Ha a jelenlegi a kesobbi megallo es az elozo a korábbi megálló,
				return 1;                                           //függvény 1 értékkel tér vissza
			}

			elozo = jelenlegi;                                  //A ciklus következõ lefutásához az elozo a jelenlegi értékét kapja,
			jelenlegi = jelenlegi->kov;                        // a jelenlegi pedig ezt követõen az azt követõt
		}

	}
	return 0;                 //Ha nem szomszédosak a megállók, akkor a függvény 0 értékkel tér vissza
}


int holatszall(int elozo, int jelenlegi, Lista * head) {                  //1-et ad vissza ha a járatban szerepel az aktuálisan keresett megálló,
	if (head->megallo == elozo && head->kov->megallo == jelenlegi) { return 1; } //és késõbb mint az elõzõ megálló, 0-át ha nem szerepel, vagy elõbb
	Lista *mutat;
	mutat = head->kov;
	int j = 0;
	while (mutat->kov != NULL) { //Addig fut, amíg következõ elem nem NULL
		if (mutat->megallo == elozo) { j = 1; } //Ha a megálló, amin a mutató áll a korábbi, akkor j változót egyre állítjuk
		else { j = 0; } //Ha nem 0-ra kell állítanunk, ha esetleg korábban 1 lett volna
		if (mutat->kov->megallo == jelenlegi && j == 1) { //A függvény 1-et ad vissza értékül, ha a következõ megálló a késõbbi a keresettek közül, és a j==1
			return 1;
		}
		mutat = mutat->kov; // A mutató mozgatása a következõ megállóra
	}
	return 0; //Ha nem talál egyezést akkor 0-val tér vissza
}
//Függvény annak meghatározására, hogy melyik járatokkal meddig közlekedjünk
int melyikjarat(Lista * utvonal, Lista ** head, char **megallonevek) {
	int i, n = 0, d = 2, c = 2, vege = 0, maxido = 0;
	int elozo, mostani;
	int hol = 0;
	int elsofutas = 0;
	Lista * jelenlegi; //Mutato Lista * struktúrához
	jelenlegi = (Lista*)malloc(sizeof(Lista));
	Lista * lista; //Lista, melyben az egyes járatokkal megtehetõ megállók száma kerül rögzítésre
	Lista * utvonalklon; //az utvonal masolata
	utvonalklon = (Lista*)malloc(sizeof(Lista));
	printf("\n");
	while (vege != 1) { //Addig fut míg el nem érjük az útvonal utolsó elemét
		lista = malloc(sizeof(Lista)); //Lista beállítása
		lista->megallo = 0; //Lista elsõ elemének a megadása
		lista->kov = NULL;  //Lista következõ elemének NULL pointerre állítása
		while (head[n] != NULL) { //annyiszor fut le, ahány járat van
			if (elsofutas == 0) { //ha elõször fut le a függvéy akkor az útvonal listára állítjuk jelenlegi-et
				jelenlegi = utvonal;
			} //ha nem elõször fut le a függvény, akkor az útvonal másolatára állítjuk, ami minden lefutásnál változik
			if (elsofutas != 0) {
				jelenlegi = utvonalklon;
			}
			i = 0;          //Változó annak jelölésére, hogy hány megállót tudunk megtenni adott járattal
			while (c != 0) { //A ciklus vagy akkor ér véget, mikor kiderül, hogy az a megálló ahol jelenleg állunk nincs a járatban
				if (jelenlegi->kov != NULL) { //vagy akkor, ha végig érünk az útvonalon
					elozo = jelenlegi->megallo;
					mostani = jelenlegi->kov->megallo;
					d = holatszall(elozo, mostani, head[n]);
					if (d != 0) { i = i + 1; } //i változó növelése, ha holatszall fgv visszatérése nem 0, azaz ha meg tudunk tenni egy megállót átszállás nélkül
					jelenlegi = jelenlegi->kov;
				}
				if (d == 0) {
					c = 0;
				}
				if (jelenlegi->kov == NULL) {
					c = 0;
				}
			}
			listaVegere(lista, i); //a lista végére fûzzük a járat által megtehetõ megállók számát
			n++; //növeljük n változót, azaz a következõ járatra lépünk
			c = 1; //c-t el kell állítani 0-ról, hogy a legbelsõ while ciklus lefusson
		}
		n = 0; //n 0-ra állítása, hogy elõrõl vizsgáljuk a járatokat a megtenni kívánt útvonal fennmaradt részéhez
		num * num;
		num = malloc(sizeof(num));
		Lista * torol; //A lista elso elemet toroljuk, mert az nem hasznos adatot tartalmaz számunkra
		torol = lista;
		lista = lista->kov;
		free(torol); //A listából eltávolított elem által foglalt memóriaterületet felszabadítjuk
		printf("\n\n\n");
		if (elsofutas == 0)
		{
			utvonalklon = listaklonozas(utvonal); //Ha most fut le elõször a külsõ ciklus, akkor az utvonalat átmásoljuk egy utvonalklon nevú listába
		}
		else { maxido = maxido + 5; } //Ha nem elõször fut le a külsõ ciklus, akkor azt jelenti, átszállás volt az elõzõ lefutás eredménye, az atszallasi idot a maxido változóban mentjük
		num = maxertek(lista); //Annak meghatározása melyik járattal tudjuk a legtöbb megállót megtenni, és az mennyi
		listafelszabaditas(lista); //Mivel megvannak a szükséges adatok, ezért a lista által foglalt memóriaterület felszabadítható
		for (i = 0; i < num->szam1; i++) //A ciklus kitorli az utvonalklonból azokat a megállókat, amelyeket már megtettünk
		{
			torol = utvonalklon;
			utvonalklon = utvonalklon->kov;
			free(torol);
		}
		hol = utvonalklon->megallo; //A hol változóval adjuk meg, hogy melyik megállóig jutottunk az elõzõ járattal
		printf("\n%s megállóig a %d. járattal, majd ", megallonevek[hol], num->szam2 + 1); //Annak kiíratása, hogy melyik megállóig melyik járattal közlekedtünk
		free(num);
		if (utvonalklon->kov == NULL) {
			printf("VÉGÁLLOMÁS\n\n"); //Végállomás, ha az útvonalklón listának már csak egy eleme van(célmegálló)
			vege = 1;
		} // A vege változó 1-re állítása jelzi, hogy a keresés befejezõdött
		else {
			printf("ÁTSZÁLLÁS\n"); //Átszállás, ha nem csak a végállomás maradt fent
			elsofutas++;
		}
	}
	listafelszabaditas(utvonalklon);
	return maxido; //A függvény visszatérési értékként az átszállásra fordított idõt adja meg
}


int Legkozelebbi(int tavolsag[], bool beallitva[], int hossz)
{
	// Annak meghatározása, hogy a még nem rögzített értékû pontok közül, melyik van legközelebb a forráshoz
	int kozel = VEGTELEN, legkozelibb;
	int i = 0;
	for (i = 0; i < hossz; i++)
		if (beallitva[i] == false && tavolsag[i] <= kozel) //Ha a beállított[i] még nincs rögzítve, és távolsága kisebb, mint kozel változóé
			kozel = tavolsag[i], legkozelibb = i;     //akkor a kozel új értéke tavolsag[i] lesz, a legkozelibb változó pedig i;

	return legkozelibb;
}

// Függvény az útvonal megtaláláshoz, módosított dijkstra algortimussal
Lista *moddijkstra(int **graf, int forras, Lista **jaratok, int cel, int hossz, int *minido, int jaratokszama)
{
	int szamol = 0, u, n, i = 0;
	int *szulo = (int*)malloc(sizeof(int)*hossz); //Az output sor szulo[i] fogja tartalmazni hogy melyik pont a szüloje i-nek
	printf("\n");
	int *tavolsag = (int*)malloc(sizeof(int)*hossz);    // Az output sor.  tavolsag[i] fogja tartalmazni a legrövidebb távolságot forrás-bol i-be
	bool *beallitva = (bool*)malloc(sizeof(bool)*hossz);; // beallitva[i] igaz lesz, ha a pont benne van a legrövidebb utak
	// fában vagy ha a legrövidebb út a forrásból i-be véglegesített
	// Minden távolság végtelenre állítása és stpSet[] hamisra állítása
	for (i = 0; i < hossz; i++)
		tavolsag[i] = VEGTELEN, beallitva[i] = false;
	tavolsag[forras] = 0; // A forrás távolsága önmagától mindig 0!
	szulo[forras] = forras;  //A forrás szüloje mindig önmaga!
	for (szamol = 0; szamol < hossz - 1; szamol++) // A legrövidebb út megtalálása a gráf minden pontjához
	{
		u = Legkozelebbi(tavolsag, beallitva, hossz);// A legrövidebb távolságú pont kiválasztása azon pontok közül
		// melyek még nem lettek felhasználva, az elso lefutásnál az u mindig egyenlo a forrással
		beallitva[u] = true; // A kiválasztott pont megjelelölés, hogy tudjuk már rögzítettük a távolságát
		n = 0;
		for (n = 0; n < hossz; n++) { // A kiválasztott ponttal szomszédos pontok távolságértékének frissítése
			if (!beallitva[n] && graf[u][n] && tavolsag[u] != VEGTELEN && tavolsag[u] + graf[u][n] < tavolsag[n]) { //  tavolsag[v] frissítése akkor és csak akkor ha nincs beallitva tömbben,
				if (szomszed(jaratok, u, n, jaratokszama) == 1) {                                                      //   van egy él u-ból n-be  az út teljes súlya forrás-ból n-be
					tavolsag[n] = tavolsag[u] + graf[u][n];                                                         //   u-n keresztül kisebb, mint tavolsag[n] jelenlegi súlya, valamint ha
					szulo[n] = u;
				}
			}
		}                                                                            //  létezik olyan járat, melyben u és v szomszédos megállók
	}
	printf("\n");
	int *forditott = (int*)malloc(sizeof(int)*hossz);
	int a, c = szulo[cel]; // A függvény második részéhez néhány új változó
	forditott[0] = cel;
	szamol = 1;
	for (i = 1; i < hossz; i++) { //Fordított tömb feltöltése, az elemeket a céltól indulva, a kiinduló pontig töltjük bele, így megkapva az útvonal fordítottját
		forditott[i] = c;
		a = forditott[i];
		c = szulo[a];
		if (c == szulo[c]) { i = hossz; }
		szamol++;
	}
	Lista * utvonal;
	utvonal = malloc(sizeof(Lista));
	utvonal->megallo = forras;
	utvonal->kov = NULL;
	for (i = 1; i < szamol; i++) { //Utvonal listába már ez eredeti sorrendben mentjük az adatokat
		listaVegere(utvonal, forditott[szamol - i]);
	}
	listaVegere(utvonal, cel); //Az utvonal utolsó eleme mindig a célmegálló
	if (utvonal->megallo == utvonal->kov->megallo) { utvonal = utvonal->kov; }
	*minido = tavolsag[cel];
	printf("\nAz útvonal: ");
	free(szulo);
	free(tavolsag);
	free(beallitva);
	free(forditott);
	return utvonal; //visszatérési értékként megkapjuk az útvonalat egy láncolt listában
}