typedef struct num {
	int szam1;
	int szam2;
} num;

typedef struct Lista {
	int megallo;
	struct Lista * kov; //rekurz�v m�don megadott ptr
} Lista;


Lista *listaVegere(Lista *eleje, int megallo) {
	Lista *mozgo, *uj;
	uj = (Lista*)malloc(sizeof(Lista));
	uj->megallo = megallo;
	uj->kov = NULL;
	if (eleje == NULL)//�res lista?
		return uj;
	for (mozgo = eleje; mozgo->kov != NULL; mozgo = mozgo->kov)
		; //�res ciklus, megkeresi az utols� elemet
	mozgo->kov = uj;
	return eleje;
}
int megallo_ellenorzo(char **adatb, char megallo[], int sorok)//kmegallo a kiindul�si meg�ll�t kapja meg inputnak, cmegallo a c�lmeg�ll�t kapja inputnak
{
	int i, cmp;//kiindul�si meg�ll� visszat�r�si �rt�ke �sszehasonl�t�s ut�n
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
	//el�g egyszer bekapcsolni a program sor�n az �kezetes betuk miatt
	fp = fopen(MEGALLOK, "r");
	if (fp == NULL)
	{
		printf("Nem siker�lt megnyitni a %s nevu f�jlt\n", MEGALLOK);
		printf("A kil�p�shez nyomja meg az entert\n");
		return NULL;
	}
	while (fgets(sor, SOR_MERET, fp) != NULL)
	{
		(*sorokszama)++;//megn�zi h�ny soros a f�jl
	}
	rewind(fp);//visszat�r a f�jl elej�re
	sortomb = (char**)malloc(*sorokszama * sizeof(char*));
	while (fgets(sor, SOR_MERET, fp) != NULL)
	{
		if (sor[strlen(sor) - 1] == '\n')
		{
			sor[strlen(sor) - 1] = '\0';
		} //sort�r�seket \0 ra cser�li
		sortomb[i] = (char*)malloc((strlen(sor) + 1) * sizeof(char));
		strcpy(sortomb[i], sor);
		i++;
	}
	fclose(fp);
	return (sortomb);
}// program v�g�n a MEM�RI�T felszabad�tani!!!


num *maxertek(Lista * head) {           //F�ggv�ny egy lista legnagyobb �rt�k� elem�nek megtal�l�s�ra
	int i = 0;
	int d = 0;
	num * n;                          //num strukt�r�ja n ptr l�tregoz�sa
	n = (num*)malloc(sizeof(num));    //helyfoglal�s n ptr �ltal mutatott strukt�r�nak
	Lista * jelenlegi = head;               //mutat� �ll�t�sa a lista els� elem�re
	while (jelenlegi != NULL)                 //Am�g a list�ra �ll�tott mutat� nem NULL, addig fut a ciklus
	{
		if (i < jelenlegi->megallo) {             //Ha az i �rt�ke kisebb mint a lista jelenlegi elem�ben t�rolt,
			i = jelenlegi->megallo; n->szam2 = d; //akkor az i �j �rt�ke a lista elem�ben t�rolt �rt�k lesz, valamint 
		}                                  //d v�ltoz�ban elment�sre ker�l, hogy a lista h�nyadik elem�t�l kapta i az �rt�k�t
		jelenlegi = jelenlegi->kov;              //A list�ra mutat�t mutat� a lista k�vetkez� elem�re �ll�t�sa
		d++;                                //d v�ltoz� n�vel�se
	}
	n->szam1 = i;                                 //n i �rt�ke i=vel lesz egyenl�
	return n;                               //Visszat�r�si �rt�k num stuk�r�ban, amely tartalmazza hogy melyik volt a lista legnagyobb eleme, �s annak mennyi az �rt�ke


}
void print_utvonal(Lista *head, char **megallok) { //Ki�rat� f�ggv�ny, amely az �tvonalat �rja ki, az utvonal lista �s a megallok 2D t�mb seg�ts�g�vel
	Lista *jelenlegi = head;                         //Mutat� a lista l�ptet�s�hez
	int i = 0;                                     //i v�ltoz� l�trehoz�sa, �s 0 �rt�k ad�sa
	while (jelenlegi != NULL) {                        //Addig fut a ciklus, am�g el nem �ri a lista v�g�t
		printf("%s", megallok[jelenlegi->megallo]); //A lista adott elem�nek megallo v�ltoz�j�ban t�rolt sz�mnak megfelel� index� elem ki�rat�sa a megallo 2D t�mbb�l
		if (jelenlegi->kov != NULL) { printf("-"); }      //Ha m�g nem az utols� meg�ll� ker�lt ki�rat�sra, akkor egy '-' megjelen�t�se, a kimeneten a tagolt megjelen�t�s�rt
		if (i == 2) {                                 //Ha m�r 2 meg�ll�n�v ki�r�sra ker�lt, akkor
			printf("\n");                     //sort�r�st hajtunk v�gre, hogy mindenk�pp kif�rjen a konzol ablakba az �tvonal
			i = 0;                             //a sort�r�s ut�n az i v�ltoz�t vissza kell �ll�tani
		}
		jelenlegi = jelenlegi->kov;                     //A list�ra mutat� mutat� k�vetkez� elemre �ll�t�sa
		i = i + 1;
	}
}
Lista * listaklonozas(Lista * head) { //f�ggv�ny Lista* t�pus� l�ncolt lista m�sol�s�hoz
	Lista * klon;                   //Lista t�pus� klon mutat� l�trehoz�sa
	klon = (Lista*)malloc(sizeof(Lista)); //Helyfoglal�s a klon mutat�nak
	Lista * megtart = klon;               //megtart mutat� l�trehoz�sa, �s a kl�nlista els� elem�re �ll�t�sa
	Lista * megadott = head;              //megadott mutat� l�trehoz�sa, �s az eredeti lista els� elem�re �ll�t�sa
	while (megadott != NULL) {              //Addig fut a ciklus, am�g a megadott list�n v�gig nem �r
		klon->megallo = megadott->megallo;//a kl�nlista aktu�lis elem�nek �rt�k�t az eredeti lista megegyez� sorsz�m� elem�nek �rt�k�vel lesz egyenl�
		megadott = megadott->kov;         //Az eredeti list�ra �ll�tott mutat� l�ptet�se a k�vetkez� elemre
		klon->kov = NULL;                 //A kl�nlista k�vetkez� eleme null�ra �ll�t�dik
		if (megadott != NULL)               //Ha az eredeti list�ra mutat� mutat� nem NULL �rt�kre mutat
		{
			klon->kov = (Lista*)malloc(sizeof(Lista));//Helyfoglal�s a kl�nlista k�vetkez� elem�nek
			klon = klon->kov;                         //A klon mutat�t a k�vetkez� elemre �ll�tja a f�ggv�ny,
			klon->kov = NULL;                         //az ezt k�vet� mutat�t pedig NULL-ra
		}
	}
	return megtart;                     //A megtart mutat�val t�r vissza a f�ggv�ny, amely a kl�nlista els� elem�re mutat
}
void listafelszabaditas(Lista* lista) //f�ggv�ny Lista* t�pus� l�ncolt list�k felszabad�t�s�hoz
{
	Lista * tmp;                      //lista t�pus� tmp mutat� l�trehoz�sa
	while (lista != NULL)             //Addig fut a ciklus am�g a lista �sszes eleme fel nem szabadul(el�ri a lista v�g�n l�v� NULL pointert)
	{
		tmp = lista;                  //tmp mutat� lista elej�re �ll�t�sa
		lista = lista->kov;           //a lista kezd�mutat�ja a k�vetkez� elem mutat�ja lesz
		free(tmp);                    //a tmp mutat� �ltal mutatott mem�riater�let felszabadul
	}
}
Lista** megalloBeolvas(Lista **head, int *sorokszama) //F�ggv�ny sz�mokat tartalmaz� csv f�jl l�ncolt list�kba t�rt�n� beolvas�s�ra
{
	FILE *fp;           //F�jlmutat�
	Lista *ptr = NULL;  //Lista mutat�, NULL-ra �ll�tva
	int i = 0, j = 0, k = 0, l, m, d=0;
	char sor[SORTOMB_MERET]; //SORTOMB_MERET m�ret� t�mb
	char tmp[TMP_MERET];    //TMP_M�RET m�ret� t�mb

	fp = fopen(JARATOK, "r"); //A JARATOK-k�nt defineolt f�jl megnyit�sa
	if (fp == NULL)          //Ha nem a f�jlt nem siker�l megnyitni, a f�ggv�ny NULL pointerrel t�r vissza
	{
		printf("Nem siker�lt megnyitni a %s nevu f�jlt\n", JARATOK); //A hiba �zenet ki�rat�sa
		printf("A kil�p�shez nyomja meg az entert\n");
		return NULL;
	}

	while (fgets(sor, 100, fp) != NULL) { //Addig fut a ciklus, m�g a f�jl v�g�re nem �r
		(*sorokszama)++;            //sorokszama v�ltoz� n�vel�se, eredm�nyk�pp megkapjuk h�ny sor(h�ny j�rat) van a f�jlban
	}

	head = (Lista**)malloc(*sorokszama * sizeof(Lista*)); //Head t�mbnek dinamikus mem�riafoglal�s
	rewind(fp);                                            //mutat� vissza�ll�t�sa a f�jl elej�re

	ptr = head[0];                                          //Lista ptr head[0] lista elej�re �ll�t�sa

	while (fgets(sor, 100, fp) != NULL)                    //Addig fut a ciklus, m�g a f�jl v�g�re nem �r, sz�mok ment�se sor t�mbben
	{
		l = 0;
		m = 0;
		head[k] = malloc(sizeof(Lista)); //dinamikus helyfoglal�s a head[k] elem�nek
		d = strlen(sor);
		for (i = 0; i <= d; i++) {              //addig fut a ciklus, am�g az i ciklusv�ltoz� kisebb, mint a sor t�mbben tal�lhat� karakterek sz�ma
			if (sor[i] == ';' && isdigit(sor[i + 1])) { //ha ; ker�l a sort�mbbe, �s az azut�ni elem sz�m, akkor n�velj�k az l v�ltoz�t
				l++;
			}
		}
		ptr = head[k];                              //Lista ptr head[k] elem�re �ll�t�sa
		for (i = 0; m <= l; i++) {                       //Addig fut, am�g a list�ban szerepl� sz�mok sz�ma kevesebb, mint a sort�mbben l�v� sz�mok sz�ma
			if (isdigit(sor[i])) {                   //Ha a sor[i] elem sz�m
				tmp[j] = sor[i];                    //akkor a tmp[j]==sor[i]
				j++;                                //j v�ltoz� n�vel�se
			}
			else {
				tmp[j] = '\0';                      //ha m�r nem sz�m k�vetkezik, akor a tmp[j] elem�t �resre �ll�tjuk
				ptr->megallo = atoi(tmp);           //A ptr-el mutatott listaelem meg�ll� �rt�ke a tmp-ben tal�lhat� sz�msor lesz sz�mm� alak�tva
				ptr->kov = malloc(sizeof(Lista));   //helyfoglal�s a k�vetkez� elemnek
				m++;                                //n�velj�k az m v�ltoz�t, jelezve, hogy egy elem ker�l a list�ba
				if (m <= l) {                          //Ha az list�ban szerepl� sz�mok sz�ma kevesebb, mint a sort�mb hossza,
					ptr = ptr->kov;                 // a ptr-t a k�vetkez� listaelemre �ll�tjuk
				}
				else {
					ptr->kov = NULL;                  //Ha a list�ban szerepl� sz�mok sz�ma nem kevesebb mint a sort�mb hossza, akkor a kov mutat�t NULL-ra lesz �ll�tvaa
				}
				j = 0;                                //j mutat� vissza�ll�t�sa 0-ra, hogy el�r�l t�lt�dj�n a temp t�mb
			}
		}
		k++;                                        //k n�vel�se
	}
	head[k] = NULL;                                   //Ha a f�ggv�ny el�rti a f�jl v�g�t, akkor az utols� head-et NULL-ra �ll�tja, hogy k�s�bb k�nny� legyen megtal�lni a t�mb v�g�t
	fclose(fp);                                     //f�jl bez�r�sa
	return head;                                    //visszat�r�s a l�ncolt list�kat tartalmaz� t�mbbel
}

int matrixmeret(FILE* fp) {
	int M_XY = 0, i = 0, pv = 0, d;
	char cac[CAC_MERET];
	fp = fopen("mtx2.csv", "r");
	if (fp) {
		while (fgets(cac, CAC_MERET, fp) != NULL) {
			M_XY++; // megn�zi hogy a csv f�jl h�ny sorb�l �ll, m�g null �rt�ket nem kap a mutat�
		}
		rewind(fp); // visszaugrik a f�jl elej�re a mutat�
		while (fgets(cac, CAC_MERET, fp) != NULL) {
			d = strlen(cac);
			for (i = 0; i < d; i++) {
				if (cac[i] == ';') {
					pv++; // a pontosvessz�k darabsz�m�nak seg�ts�g�vel magkapjuk hogy h�ny oszlopos a csv f�jlunk (pv+1
					// oszlopos)
				}
			}
			if (pv + 1 != M_XY) {
				fclose(fp);
				return 0; //wprintf(L"Nem n�gyzetes mtx van a .csv f�jlban!\n");
			}
			pv = 0;
		}
		fclose(fp);
	}
	else {
		printf("Hiba a %s nev� f�jl megnyit�sakor\n", MTX);
		return 0; //wprintf(L"Nem lehet megnyitni a f�jlt!\n");
	}
	return M_XY;

}
int **dimmtxfgv(FILE* fp, int** dimmtx, int M_XY)
{

	int i, j = 0, x = 0, y = 0, d=0; // M_XY a dimmtx sor�nak �s oszlop�nak sz�ma, ha n�gyzetes a mtx,
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
				j = 0; //�gy mindig a tmp 0. elem�be tudja menten a percet
			}
		}
		x++;
		y = 0;
	}
	fclose(fp);

	return (dimmtx);
}
int szomszed(Lista ** head, int ertek1, int ertek2, int jaratokszama) { //F�ggv�ny annak tesztel�s�re, hogy a megadott k�tmeg�ll� szerepel-e egym�s mellett
	int i;                                              //B�rmelyik j�ratban
	for (i = 0; i < jaratokszama; i++) {
		Lista *elozo, *jelenlegi;

		if (head[i] == NULL) { //ha NULL pointer az i. elem, azaz az �sszes meg�ll�n v�gig�rt a f�ggv�ny, �s nem tal�lt egyez�st, akkor 0 �rt�kkel t�r vissza
			return 0;
		}

		elozo = jelenlegi = head[i]; //Kezdetben mindk�t listamutat�t head[i]-re �ll�tjuk
		while (jelenlegi != NULL) { //Addig fut a ciklus, am�g el nem �rj�k a lista v�g�t
			if (jelenlegi->megallo == ertek2 && elozo->megallo == ertek1) { //Ha a jelenlegi a kesobbi megallo es az elozo a kor�bbi meg�ll�,
				return 1;                                           //f�ggv�ny 1 �rt�kkel t�r vissza
			}

			elozo = jelenlegi;                                  //A ciklus k�vetkez� lefut�s�hoz az elozo a jelenlegi �rt�k�t kapja,
			jelenlegi = jelenlegi->kov;                        // a jelenlegi pedig ezt k�vet�en az azt k�vet�t
		}

	}
	return 0;                 //Ha nem szomsz�dosak a meg�ll�k, akkor a f�ggv�ny 0 �rt�kkel t�r vissza
}


int holatszall(int elozo, int jelenlegi, Lista * head) {                  //1-et ad vissza ha a j�ratban szerepel az aktu�lisan keresett meg�ll�,
	if (head->megallo == elozo && head->kov->megallo == jelenlegi) { return 1; } //�s k�s�bb mint az el�z� meg�ll�, 0-�t ha nem szerepel, vagy el�bb
	Lista *mutat;
	mutat = head->kov;
	int j = 0;
	while (mutat->kov != NULL) { //Addig fut, am�g k�vetkez� elem nem NULL
		if (mutat->megallo == elozo) { j = 1; } //Ha a meg�ll�, amin a mutat� �ll a kor�bbi, akkor j v�ltoz�t egyre �ll�tjuk
		else { j = 0; } //Ha nem 0-ra kell �ll�tanunk, ha esetleg kor�bban 1 lett volna
		if (mutat->kov->megallo == jelenlegi && j == 1) { //A f�ggv�ny 1-et ad vissza �rt�k�l, ha a k�vetkez� meg�ll� a k�s�bbi a keresettek k�z�l, �s a j==1
			return 1;
		}
		mutat = mutat->kov; // A mutat� mozgat�sa a k�vetkez� meg�ll�ra
	}
	return 0; //Ha nem tal�l egyez�st akkor 0-val t�r vissza
}
//F�ggv�ny annak meghat�roz�s�ra, hogy melyik j�ratokkal meddig k�zlekedj�nk
int melyikjarat(Lista * utvonal, Lista ** head, char **megallonevek) {
	int i, n = 0, d = 2, c = 2, vege = 0, maxido = 0;
	int elozo, mostani;
	int hol = 0;
	int elsofutas = 0;
	Lista * jelenlegi; //Mutato Lista * strukt�r�hoz
	jelenlegi = (Lista*)malloc(sizeof(Lista));
	Lista * lista; //Lista, melyben az egyes j�ratokkal megtehet� meg�ll�k sz�ma ker�l r�gz�t�sre
	Lista * utvonalklon; //az utvonal masolata
	utvonalklon = (Lista*)malloc(sizeof(Lista));
	printf("\n");
	while (vege != 1) { //Addig fut m�g el nem �rj�k az �tvonal utols� elem�t
		lista = malloc(sizeof(Lista)); //Lista be�ll�t�sa
		lista->megallo = 0; //Lista els� elem�nek a megad�sa
		lista->kov = NULL;  //Lista k�vetkez� elem�nek NULL pointerre �ll�t�sa
		while (head[n] != NULL) { //annyiszor fut le, ah�ny j�rat van
			if (elsofutas == 0) { //ha el�sz�r fut le a f�ggv�y akkor az �tvonal list�ra �ll�tjuk jelenlegi-et
				jelenlegi = utvonal;
			} //ha nem el�sz�r fut le a f�ggv�ny, akkor az �tvonal m�solat�ra �ll�tjuk, ami minden lefut�sn�l v�ltozik
			if (elsofutas != 0) {
				jelenlegi = utvonalklon;
			}
			i = 0;          //V�ltoz� annak jel�l�s�re, hogy h�ny meg�ll�t tudunk megtenni adott j�rattal
			while (c != 0) { //A ciklus vagy akkor �r v�get, mikor kider�l, hogy az a meg�ll� ahol jelenleg �llunk nincs a j�ratban
				if (jelenlegi->kov != NULL) { //vagy akkor, ha v�gig �r�nk az �tvonalon
					elozo = jelenlegi->megallo;
					mostani = jelenlegi->kov->megallo;
					d = holatszall(elozo, mostani, head[n]);
					if (d != 0) { i = i + 1; } //i v�ltoz� n�vel�se, ha holatszall fgv visszat�r�se nem 0, azaz ha meg tudunk tenni egy meg�ll�t �tsz�ll�s n�lk�l
					jelenlegi = jelenlegi->kov;
				}
				if (d == 0) {
					c = 0;
				}
				if (jelenlegi->kov == NULL) {
					c = 0;
				}
			}
			listaVegere(lista, i); //a lista v�g�re f�zz�k a j�rat �ltal megtehet� meg�ll�k sz�m�t
			n++; //n�velj�k n v�ltoz�t, azaz a k�vetkez� j�ratra l�p�nk
			c = 1; //c-t el kell �ll�tani 0-r�l, hogy a legbels� while ciklus lefusson
		}
		n = 0; //n 0-ra �ll�t�sa, hogy el�r�l vizsg�ljuk a j�ratokat a megtenni k�v�nt �tvonal fennmaradt r�sz�hez
		num * num;
		num = malloc(sizeof(num));
		Lista * torol; //A lista elso elemet toroljuk, mert az nem hasznos adatot tartalmaz sz�munkra
		torol = lista;
		lista = lista->kov;
		free(torol); //A list�b�l elt�vol�tott elem �ltal foglalt mem�riater�letet felszabad�tjuk
		printf("\n\n\n");
		if (elsofutas == 0)
		{
			utvonalklon = listaklonozas(utvonal); //Ha most fut le el�sz�r a k�ls� ciklus, akkor az utvonalat �tm�soljuk egy utvonalklon nev� list�ba
		}
		else { maxido = maxido + 5; } //Ha nem el�sz�r fut le a k�ls� ciklus, akkor azt jelenti, �tsz�ll�s volt az el�z� lefut�s eredm�nye, az atszallasi idot a maxido v�ltoz�ban mentj�k
		num = maxertek(lista); //Annak meghat�roz�sa melyik j�rattal tudjuk a legt�bb meg�ll�t megtenni, �s az mennyi
		listafelszabaditas(lista); //Mivel megvannak a sz�ks�ges adatok, ez�rt a lista �ltal foglalt mem�riater�let felszabad�that�
		for (i = 0; i < num->szam1; i++) //A ciklus kitorli az utvonalklonb�l azokat a meg�ll�kat, amelyeket m�r megtett�nk
		{
			torol = utvonalklon;
			utvonalklon = utvonalklon->kov;
			free(torol);
		}
		hol = utvonalklon->megallo; //A hol v�ltoz�val adjuk meg, hogy melyik meg�ll�ig jutottunk az el�z� j�rattal
		printf("\n%s meg�ll�ig a %d. j�rattal, majd ", megallonevek[hol], num->szam2 + 1); //Annak ki�rat�sa, hogy melyik meg�ll�ig melyik j�rattal k�zlekedt�nk
		free(num);
		if (utvonalklon->kov == NULL) {
			printf("V�G�LLOM�S\n\n"); //V�g�llom�s, ha az �tvonalkl�n list�nak m�r csak egy eleme van(c�lmeg�ll�)
			vege = 1;
		} // A vege v�ltoz� 1-re �ll�t�sa jelzi, hogy a keres�s befejez�d�tt
		else {
			printf("�TSZ�LL�S\n"); //�tsz�ll�s, ha nem csak a v�g�llom�s maradt fent
			elsofutas++;
		}
	}
	listafelszabaditas(utvonalklon);
	return maxido; //A f�ggv�ny visszat�r�si �rt�kk�nt az �tsz�ll�sra ford�tott id�t adja meg
}


int Legkozelebbi(int tavolsag[], bool beallitva[], int hossz)
{
	// Annak meghat�roz�sa, hogy a m�g nem r�gz�tett �rt�k� pontok k�z�l, melyik van legk�zelebb a forr�shoz
	int kozel = VEGTELEN, legkozelibb;
	int i = 0;
	for (i = 0; i < hossz; i++)
		if (beallitva[i] == false && tavolsag[i] <= kozel) //Ha a be�ll�tott[i] m�g nincs r�gz�tve, �s t�vols�ga kisebb, mint kozel v�ltoz��
			kozel = tavolsag[i], legkozelibb = i;     //akkor a kozel �j �rt�ke tavolsag[i] lesz, a legkozelibb v�ltoz� pedig i;

	return legkozelibb;
}

// F�ggv�ny az �tvonal megtal�l�shoz, m�dos�tott dijkstra algortimussal
Lista *moddijkstra(int **graf, int forras, Lista **jaratok, int cel, int hossz, int *minido, int jaratokszama)
{
	int szamol = 0, u, n, i = 0;
	int *szulo = (int*)malloc(sizeof(int)*hossz); //Az output sor szulo[i] fogja tartalmazni hogy melyik pont a sz�loje i-nek
	printf("\n");
	int *tavolsag = (int*)malloc(sizeof(int)*hossz);    // Az output sor.  tavolsag[i] fogja tartalmazni a legr�videbb t�vols�got forr�s-bol i-be
	bool *beallitva = (bool*)malloc(sizeof(bool)*hossz);; // beallitva[i] igaz lesz, ha a pont benne van a legr�videbb utak
	// f�ban vagy ha a legr�videbb �t a forr�sb�l i-be v�gleges�tett
	// Minden t�vols�g v�gtelenre �ll�t�sa �s stpSet[] hamisra �ll�t�sa
	for (i = 0; i < hossz; i++)
		tavolsag[i] = VEGTELEN, beallitva[i] = false;
	tavolsag[forras] = 0; // A forr�s t�vols�ga �nmag�t�l mindig 0!
	szulo[forras] = forras;  //A forr�s sz�loje mindig �nmaga!
	for (szamol = 0; szamol < hossz - 1; szamol++) // A legr�videbb �t megtal�l�sa a gr�f minden pontj�hoz
	{
		u = Legkozelebbi(tavolsag, beallitva, hossz);// A legr�videbb t�vols�g� pont kiv�laszt�sa azon pontok k�z�l
		// melyek m�g nem lettek felhaszn�lva, az elso lefut�sn�l az u mindig egyenlo a forr�ssal
		beallitva[u] = true; // A kiv�lasztott pont megjelel�l�s, hogy tudjuk m�r r�gz�tett�k a t�vols�g�t
		n = 0;
		for (n = 0; n < hossz; n++) { // A kiv�lasztott ponttal szomsz�dos pontok t�vols�g�rt�k�nek friss�t�se
			if (!beallitva[n] && graf[u][n] && tavolsag[u] != VEGTELEN && tavolsag[u] + graf[u][n] < tavolsag[n]) { //  tavolsag[v] friss�t�se akkor �s csak akkor ha nincs beallitva t�mbben,
				if (szomszed(jaratok, u, n, jaratokszama) == 1) {                                                      //   van egy �l u-b�l n-be  az �t teljes s�lya forr�s-b�l n-be
					tavolsag[n] = tavolsag[u] + graf[u][n];                                                         //   u-n kereszt�l kisebb, mint tavolsag[n] jelenlegi s�lya, valamint ha
					szulo[n] = u;
				}
			}
		}                                                                            //  l�tezik olyan j�rat, melyben u �s v szomsz�dos meg�ll�k
	}
	printf("\n");
	int *forditott = (int*)malloc(sizeof(int)*hossz);
	int a, c = szulo[cel]; // A f�ggv�ny m�sodik r�sz�hez n�h�ny �j v�ltoz�
	forditott[0] = cel;
	szamol = 1;
	for (i = 1; i < hossz; i++) { //Ford�tott t�mb felt�lt�se, az elemeket a c�lt�l indulva, a kiindul� pontig t�ltj�k bele, �gy megkapva az �tvonal ford�tottj�t
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
	for (i = 1; i < szamol; i++) { //Utvonal list�ba m�r ez eredeti sorrendben mentj�k az adatokat
		listaVegere(utvonal, forditott[szamol - i]);
	}
	listaVegere(utvonal, cel); //Az utvonal utols� eleme mindig a c�lmeg�ll�
	if (utvonal->megallo == utvonal->kov->megallo) { utvonal = utvonal->kov; }
	*minido = tavolsag[cel];
	printf("\nAz �tvonal: ");
	free(szulo);
	free(tavolsag);
	free(beallitva);
	free(forditott);
	return utvonal; //visszat�r�si �rt�kk�nt megkapjuk az �tvonalat egy l�ncolt list�ban
}