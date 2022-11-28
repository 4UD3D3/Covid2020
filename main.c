/* GAINCHE Andr�a projet Covid2020 05/12/20 19h37*/

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

typedef struct date {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct citoyen {
    char nom[40];
    char prenom[40];
    struct citoyen *pnext;
    struct citoyen *pprevious;
} Tcitoyen;

typedef struct participant {
    Date *date;
    Tcitoyen *ppersonne;
    struct participant *psuivant;
} Tparticipant;

typedef struct lieu {
    char nomLieu[40];
    Tparticipant *pliste;
    struct lieu *pavant;
    struct lieu *pprecedent;
} Tlieu;

typedef struct citrencontre {
    Tcitoyen *citoyen;
    Tparticipant *part;
    struct citrencontre *pdespues;
} Tcitrencontre;

typedef struct poubelle{
	Tparticipant *part;
	struct poubelle *seguente;
}Tpoubelle;

/////////////////////////////////////////////////////////////////////
///////////////////////////fonction affichage////////////////////////
/////////////////////////////////////////////////////////////////////

int lireCaract() { //comment�

    char c = 10;
    int fnt = 0;

    c = getch(); // on lit le caractere entr� au clavier
    fnt = c;
    if (c == -32) { 
        c = getch();
        fnt = 400 + c;
    }
    if (c == 0) {
        c = getch();
        fnt = 500 + c;
    }
    return fnt;
}

////////////////////////////////////////////////////////////////////

void gotoligcol(int lig, int col) {// comment�
    COORD mycoord;

    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord); // place le curseur a la ligne et la colone indiqu�
}

////////////////////////////////////////////////////////////////////

void affichelogomenu() {// comment�
    gotoligcol(1, 2); //fonction qui affiche juste des caracteres
    printf(" .----------------.  .----------------.  .-----------------. .----------------. ");
    gotoligcol(2, 2);
    printf("| .--------------. || .--------------. || .--------------. || .--------------. |");
    gotoligcol(3, 2);
    printf("| | ____    ____ | || |  _________   | || | ____  _____  | || | _____  _____ | |");
    gotoligcol(4, 2);
    printf("| ||_   \\  /   _|| || | |_   ___  |  | || ||_   \\|_   _| | || ||_   _||_   _|| |");
    gotoligcol(5, 2);
    printf("| |  |   \\/   |  | || |   | |_  \\_|  | || |  |   \\ | |   | || |  | |    | |  | |");
    gotoligcol(6, 2);
    printf("| |  | |\\  /| |  | || |   |  _|  _   | || |  | |\\ \\| |   | || |  | '    ' |  | |");
    gotoligcol(7, 2);
    printf("| | _| |_\\/_| |_ | || |  _| |___/ |  | || | _| |_\\   |_  | || |   \\ `--' /   | |");
    gotoligcol(8, 2);
    printf("| ||_____||_____|| || | |_________|  | || ||_____|\\____| | || |    `.__.'    | |");
    gotoligcol(9, 2);
    printf("| |              | || |              | || |              | || |              | |");
    gotoligcol(10, 2);
    printf("| '--------------' || '--------------' || '--------------' || '--------------' |");
    gotoligcol(11, 2);
    printf(" '----------------'  '----------------'  '----------------'  '----------------' ");
}

////////////////////////////////////////////////////////////////////

void affichelogocitoyen() {// comment�
    gotoligcol(1, 10);//fonction qui affiche juste des caracteres
    printf("   _____   _   _                                  ");
    gotoligcol(2, 10);
    printf("  / ____| (_) | |                                 ");
    gotoligcol(3, 10);
    printf(" | |       _  | |_    ___    _   _    ___   _ __  ");
    gotoligcol(4, 10);
    printf(" | |      | | | __|  / _ \\  | | | |  / _ \\ | '_ \\ ");
    gotoligcol(5, 10);
    printf(" | |____  | | | |_  | (_) | | |_| | |  __/ | | | |");
    gotoligcol(6, 10);
    printf("  \\_____| |_|  \\__|  \\___/   \\__, |  \\___| |_| |_|");
    gotoligcol(7, 10);
    printf("                              __/ |               ");
    gotoligcol(8, 10);
    printf("                             |___/                ");
}

////////////////////////////////////////////////////////////////////

void affichelogolieu1() {// comment�
    gotoligcol(1, 20);//fonction qui affiche juste des caracteres
    printf("  _        _                ");
    gotoligcol(2, 20);
    printf(" | |      (_)               ");
    gotoligcol(3, 20);
    printf(" | |       _    ___   _   _ ");
    gotoligcol(4, 20);
    printf(" | |      | |  / _ \\ | | | |");
    gotoligcol(5, 20);
    printf(" | |____  | | |  __/ | |_| |");
    gotoligcol(6, 20);
    printf(" |______| |_|  \\___|  \\__,_|");
}

////////////////////////////////////////////////////////////////////

void affichesucces(){// comment�
	gotoligcol(1,20);//fonction qui affiche juste des caracteres
	printf("   _____                                    ");
	gotoligcol(2,20);
	printf("  / ____|                                   ");
	gotoligcol(3,20);
	printf(" | (___    _   _    ___    ___    ___   ___ ");
	gotoligcol(4,20);
	printf("  \\___ \\  | | | |  / __|  / __|  / _ \\ / __|");
	gotoligcol(5,20);
	printf("  ____) | | |_| | | (__  | (__  |  __/ \\ _ \\ ");
	gotoligcol(6,20);
	printf(" |_____/   \\__,_|  \\___|  \\___|  \\___| |___/");
}

////////////////////////////////////////////////////////////////////

void affichefichiers(){// comment�
	gotoligcol(1,20);//fonction qui affiche juste des caracteres
	printf("  ______   _          _       _                     ");
	gotoligcol(2,20);
	printf(" |  ____| (_)        | |     (_)                    ");
	gotoligcol(3,20);
	printf(" | |__     _    ___  | |__    _    ___   _ __   ___ ");
	gotoligcol(4,20);
	printf(" |  __|   | |  / __| | '_ \\  | |  / _ \\ | '__| / __|");
	gotoligcol(5,20);
	printf(" | |      | | | (__  | | | | | | |  __/ | |    \\__ \\");
	gotoligcol(6,20);
	printf(" |_|      |_|  \\___| |_| |_| |_|  \\___| |_|    |___/");
}

////////////////////////////////////////////////////////////////////

void affichedate(){// comment�
	gotoligcol(1,20);//fonction qui affiche juste des caracteres
	printf(" _____            _          ");
	gotoligcol(2,20);
	printf("|  __ \\          | |         ");
	gotoligcol(3,20);
	printf("| |  | |   __ _  | |_    ___ ");
	gotoligcol(4,20);
	printf("| |  | |  / _` | | __|  / _ \\");
	gotoligcol(5,20);
	printf("| |__| | | (_| | | |_  |  __/");
	gotoligcol(6,20);
	printf("|_____/   \\__,_|  \\__|  \\___|");
}

////////////////////////////////////////////////////////////////////

void affichesupprimer(){// comment�
	gotoligcol(1,10);//fonction qui affiche juste des caracteres
	printf("   _____                                  _                               _ ");
	gotoligcol(2,10);
	printf("  / ____|                                (_)                             | |");
	gotoligcol(3,10);
	printf(" | (___    _   _   _ __    _ __    _ __   _   _ __ ___     ___   _ __    | |");
	gotoligcol(4,10);
	printf("  \\___ \\  | | | | | '_ \\  | '_ \\  | '__| | | | '_ ` _ \\   / _ \\ | '__|   | |");
	gotoligcol(5,10);
	printf("  ____) | | |_| | | |_) | | |_) | | |    | | | | | | | | |  __/ | |      |_|");
	gotoligcol(6,10);
	printf(" |_____/   \\__,_| | .__/  | .__/  |_|    |_| |_| |_| |_|  \\___| |_|      (_)");
	gotoligcol(7,10);
	printf("                  | |     | |                                               ");
	gotoligcol(8,10);
	printf("                  |_|     |_|                                               ");
}

////////////////////////////////////////////////////////////////////

void affichelogorencontre(){// comment�
	gotoligcol(1,20);//fonction qui affiche juste des caracteres
	printf("  _____                                          _                 ");
	gotoligcol(2,20);
	printf(" |  __ \\                                        | |                ");
	gotoligcol(3,20);
	printf(" | |__) |   ___   _ __     ___    ___    _ __   | |_   _ __    ___ ");
	gotoligcol(4,20);
	printf(" |  _  /   / _ \\ | '_ \\   / __|  / _ \\  | '_ \\  | __| | '__|  / _ \\");
	gotoligcol(5,20);
	printf(" | | \\ \\  |  __/ | | | | | (__  | (_) | | | | | | |_  | |    |  __/");
	gotoligcol(6,20);
	printf(" |_|  \\_\\  \\___| |_| |_|  \\___|  \\___/  |_| |_|  \\__| |_|     \\___|");
}

////////////////////////////////////////////////////////////////////

void affichefleche(int a, HANDLE hConsole) {// comment�
    SetConsoleTextAttribute(hConsole, 16 * 0 + 15);
    gotoligcol(a, 3); // on va a la ligne indique 
    printf(">>-->");// on affiicher la fl�che
}

////////////////////////////////////////////////////////////////////

void cadre(int x, int y, int haut, int larg) {// comment�
    int i, j;
	char c, cvertical = 186, chorizontal = 205, cangleGH = 201, cangleGB = 200, cangleDH = 187, cangleDB = 188;
    //ligne haut
    gotoligcol(x, y);
    printf("%c", cangleGH);
    i = larg;
    while (i > 0) {
        printf("%c", chorizontal);
        i = i - 1;
    };
    printf("%c", cangleDH);

    // ligne intermediaires
    j = haut;

    while (j > 0) {
        gotoligcol(x + j, y);
        printf("%c", cvertical);
        i = larg;
        while (i > 0) {
            printf("%c", ' ');
            i = i - 1;
        };
        j = j - 1;
        printf("%c", cvertical);
    }
    //ligne bas
    gotoligcol(x + haut, y);
    printf("%c", cangleGB);
    i = larg;
    while (i > 0) {
        printf("%c", chorizontal);
        i = i - 1;
    };
    printf("%c", cangleDB);
}

////////////////////////////////////////////////////////////////////

void afficheMenu(HANDLE hConsole) {// comment�

    system("cls");

    affichelogomenu();

    SetConsoleTextAttribute(hConsole, 15);
    gotoligcol(13, 9);
    printf("1 - Afficher la liste des citoyens");
    gotoligcol(14, 9);
    printf("2 - Afficher la liste des lieux de f�tes");
    gotoligcol(15, 9);
    printf("3 - Ajouter un citoyen");
    gotoligcol(16, 9);
    printf("4 - Ajouter un lieu de f�tes");
    gotoligcol(17, 9);
    printf("5 - Remplir les participants � une f�te");
    gotoligcol(18, 9);
    printf("6 - Afficher tous ceux qui ont rencontre un citoyen");
    gotoligcol(19, 9);
    printf("7 - Enregistrer un fichier situation");
    gotoligcol(20, 9);
    printf("8 - Ouvrir un ficher situation");
    gotoligcol(21, 9);
    printf("9 - Supprimer tous les �v�nements anterieur � une date");
    gotoligcol(22, 9);
    printf("0 - Quit");
}

/////////////////////////////////////////////////////////////////////
////////////////////////fonction autre///////////////////////////////
/////////////////////////////////////////////////////////////////////

Tparticipant *creationliste() {// comment�
    Tparticipant *pdebut = NULL;

    pdebut = (Tparticipant *) malloc(sizeof(Tparticipant)); // on alloue une case de m�moire � pdebut
    pdebut->psuivant = NULL; // le prochaine participant est nul

    return pdebut; 
}

////////////////////////////////////////////////////////////////////

Tcitrencontre *creationrencontre(Tcitoyen *cit) {// comment�
    Tcitrencontre *pdebut = NULL;

    pdebut = (Tcitrencontre *) malloc(sizeof(Tcitrencontre));// on alloue une case de m�moire � pdebut
    pdebut->pdespues = NULL; // le prochaine participant est nul
    pdebut->citoyen = cit; //on met le citoyen recherch� dans le citrencontre
    pdebut->part = NULL; // on met null dans partcicipant car on le remplie apres

    return pdebut;
}

////////////////////////////////////////////////////////////////////

int longueurcitoyen(Tcitoyen *p) {// comment�
    Tcitoyen *px = NULL; // cette fonction sert � calculer combien de citoyen il a dans la liste
    int i = 0;
    px = p->pnext;
    while (px->pnext->pnext != NULL) { // on parcourt toute la liste des citoyens
        i++; // on incr�mente i � chaque citoyen
        px = px->pnext;
    }
    return i; // on retourne le nom total de citoyen
}

////////////////////////////////////////////////////////////////////

int longueurlieu(Tlieu *p) {// comment�
    Tlieu *px = NULL;// cette fonction sert � calculer combien de lieu il a dans la liste
    int i = 0;
    px = p->pavant;
    while (px->pavant->pavant != NULL) {// on parcourt toute la liste des lieu
        i++;// on incr�mente i � chaque lieu
        px = px->pavant;
    }
    return i;// on retourne le nom total de lieu
}

////////////////////////////////////////////////////////////////////

Tlieu *positionelementlieu(Tlieu *pdeb, int h) { // comment�
    Tlieu *px = NULL;  //h est le n eme �l�ment de la liste que l'on cherche
    int i = 1;
    
    px = pdeb->pavant;
    

    while (px->pavant->pavant != NULL) { // on parcourt toute la liste des lieux
        if (i == h) { // si on arrive au nombre de l'�l�ment cherch� on casse la chaine
            break;
        }
        i++; // on incr�mente i a chaque lieu
        px = px->pavant;
    }
    return px; // on revoie le lieu cherch�
}

////////////////////////////////////////////////////////////////////

Tcitoyen *positionementcit(Tcitoyen *pdeb, int h) {// comment�
    Tcitoyen *px = NULL; //h est le n eme �l�ment de la liste que l'on cherche
    px = pdeb->pnext;
    int i = 1;

    while (px->pnext->pnext != NULL) { // on parcourt toute la liste des citoyens
        if (i == h) { // si on arrive au nombre de l'�l�ment cherch� on casse la chaine
            break;
        }
        i++; // on incr�mente i a chaque citoyen
        px = px->pnext;
    }
    return px; // on revoie le citoyen cherch�
}

////////////////////////////////////////////////////////////////////

void insertioncitoyen(Tcitoyen *p) {// comment�
    Tcitoyen *py = NULL; // fonction qui cr�� et chaine chaque citoyen que l'on veut ajout�
    py = (Tcitoyen *) malloc(sizeof(Tcitoyen));
    py->pnext = p->pnext;
    py->pprevious = p;
    p->pnext->pprevious = py;
    p->pnext = py;
}

////////////////////////////////////////////////////////////////////

void insertionlieu(Tlieu *p) {// comment�
    Tlieu *py = NULL;// fonction qui cr�� et chaine chaque lieu que l'on veut ajout�
    py = (Tlieu *) malloc(sizeof(Tlieu));
    py->pavant = p->pavant;
    py->pprecedent = p;
    p->pavant->pprecedent = py;
    p->pavant = py;
}

////////////////////////////////////////////////////////////////////

void affichepoubelle(Tpoubelle *ppoubelledeb){ //comment�
	//le but de cette fonction est d'affich� le contenu de la liste de la poubelle -> elle n'apparait pas dans le programme normalement que dans les tests
	Tpoubelle *ppoubellex = NULL;
	int a=0;
	system("cls");
	ppoubellex=ppoubelledeb->seguente;
	while (ppoubellex != NULL){ //on parcourt la liste poubelle
		printf("cit :%s %s\n date: %d/%d/%d\n",ppoubellex->part->ppersonne->nom,ppoubellex->part->ppersonne->prenom,ppoubellex->part->date->jour,ppoubellex->part->date->mois,ppoubellex->part->date->annee);
		ppoubellex = ppoubellex->seguente;
	}
	a=lireCaract();
}

////////////////////////////////////////////////////////////////////

void affichagecitoyen(Tcitoyen *pdebut) { // comment�
    Tcitoyen *p = NULL; // fonction qui affcihe la liste des citoyens
    int poubelle = 0;
    p = pdebut->pnext;
    int i = 1;

    system("cls");
    affichelogocitoyen(); // on affiche le logo 

    while (p->pnext != NULL) { // on parcourt la liste des citoyen
        gotoligcol(i + 9, 20); // on place le curseur au bon endroit
        printf("Citoyen ""%d"" : ""%s"" ""%s", i, p->nom, p->prenom); // on �rit le nom et le pr�nom du citoyen
        p = p->pnext; // on va sur le prochain citoyen
        i++; // on incr�mente i ppour l'affichage
    }
    gotoligcol(i + 18, 5); 
}

////////////////////////////////////////////////////////////////////

void affichagenomlieu(Tlieu *pdebut) { //comment�
    Tlieu *px = NULL; // fonction affiche la liste des lieux
    int i = 1, colonne = 10, ligne = 9,poubelle = 0;
    
    system("cls");
    affichelogolieu1();
    
    px = pdebut->pavant;
    while (px->pavant != NULL) { // on parcourt la liste des lieux
        gotoligcol(i + colonne, ligne); // on met le curseur au bon endroit
        printf("Lieu ""%d"" de fete : ""%s", i, px->nomLieu); // on affcihe le nom du lieu
        px = px->pavant;
        i++;
    }
    gotoligcol(i + 18, 5);
}

////////////////////////////////////////////////////////////////////

void affichagelistpart(Tparticipant *pdeb) { //comment�
    Tparticipant *ppartx = NULL; //fonction qui affiche la liste de participant juste pour les test -> ne sert pas dans le vrai programme
    ppartx = pdeb;
    int i = 1, colonne = 10, ligne = 9, poubelle = 0;

    system("cls");

    while (ppartx != NULL) { // on parcourt la liste des participants
        gotoligcol(i + colonne, ligne);
        printf("%s %s �tait l� le %d/%d/%d", ppartx->ppersonne->nom, ppartx->ppersonne->prenom, ppartx->date->jour, ppartx->date->mois, ppartx->date->annee);
        // on affiche le nom prenom et la date du citoyen 
        ppartx = ppartx->psuivant;
        i++; // on incr�mente i pour l'affichage 
    }

    poubelle = lireCaract(); // on met un lireCaract pour voir le r�sultat affich�
    gotoligcol(i + 30, 0);
}

////////////////////////////////////////////////////////////////////

void afficheparticipant(Tlieu *plieudeb) { //comment�
	//fonction s�lectionne un lieu pour affich� les participant qui corresponde, juste pour les test -> ne sert pas dans le vrai programme
    int c = 32, fleche = 11, vide = 0, longueurlistlieu = 0; 
    Tparticipant *pdebutlist = NULL, *ppart = NULL;
    Tlieu *px = NULL;

    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (TRUE) {
        longueurlistlieu = longueurlieu(plieudeb); // on calcule la longueur de la liste des lieux

        affichagenomlieu(plieudeb); // on affiche le logo
        affichefleche(fleche, hConsole); // on affcihe la fleche
        gotoligcol(25, 7);
        printf("Appuyer sur echap pour quitter.");
        c = lireCaract(); // on lit le caractere du plavier

        if (c == 472) {
            if (fleche == 11) {} //fleche du haut
            else {
                fleche = fleche - 1;  // on fait mont� la fleche d une ligne
            }
        }
        if (c == 480) {
            if (fleche == longueurlistlieu + 11) {} //fleche du bas
            else {
                fleche = fleche + 1;  // on fait descendre la fleche
            }
        }
        if (c == 27) { //touche echap
            break;
        }
        if (c == 13) {
            px = positionelementlieu(plieudeb, fleche - 10); //on se positionne sur le px eme element selectionn� avec la fleche
            if (px->pliste != NULL) { // si il y a une liste de participant on l'affiche
                affichagelistpart(px->pliste);
            } else { // si il n'y en a pas on affcihe qu il n'y en a pas
                system("cls");
                gotoligcol(9, 20);
                printf("Pas de citoyen dans ce lieu");
                vide = lireCaract();
            }
        }
    }
}

////////////////////////////////////////////////////////////////////

void affichagecitoyenvalidation(Tcitoyen *pdebut, Tparticipant *pstart, Date *datedonnee) { //comment�
    Tcitoyen *pc = NULL; // cette fonction sert � affich� la liste des citoyens ainsi que de colorer les citoyen si ils appartiennent � la liste des participants
    Tparticipant *ppart = NULL;
    int i = 1;

    pc = pdebut->pnext;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls");
    affichelogocitoyen(); // on affiche le logo des citoyens

    while (pc->pnext != NULL) { // on parcout la liste des citoyens
        ppart = pstart;

        gotoligcol(i + 9, 20);
        SetConsoleTextAttribute(hConsole, 15); // de base l'�criture est en noire et blanc de base

        while (ppart != NULL) {
            if (pc == ppart->ppersonne && ppart->date->annee == datedonnee->annee &&
                ppart->date->mois == datedonnee->mois && ppart->date->jour == datedonnee->jour) { //on cherche le meme si le citoyen est deja dans la liste � la meme date
                //on change la couleur d'�criture des citoyens qui sont dans la liste des citoyens et participants et qui sont dans le lieu a la bonne meme date
                SetConsoleTextAttribute(hConsole, 227); //ecriture en couleur
            }
            ppart = ppart->psuivant;
        }

        printf("Citoyen %d : %s %s", i, pc->nom, pc->prenom); // on affiche le citoyen avec la couleur d�fini auparavent

        pc = pc->pnext;
        i++;
    }
}

////////////////////////////////////////////////////////////////////

void ajoutecitoyen(Tcitoyen *pdeb, Tcitoyen *pfin) { //comment�
    Tcitoyen *px = NULL; // fonction pour ajout� des citoyens � la liste
    char *phrase1 = "Citoyen pr�c�dent : ", *phrase2 = "Nom (0 pour arr�ter): ",le_nom[40];

    system("cls");
    setlocale(LC_ALL, "");

    px = pdeb;
    px->nom[0] = '\0'; // on remplie le nom et prenom du premier par des champs vide pour ne pas que �a affiche n'importe quoi 
    px->prenom[0] = '\0';

    while (px->pnext->pnext != 0) { // on se place juste avant le bidon de fin
        px = px->pnext;
    }


    while (TRUE) {
        system("cls");
        affichelogocitoyen();
        gotoligcol(10, 20);
        printf("%s %s %s", phrase1, px->nom, px->prenom); //affiche le precedent
        
		gotoligcol(12, 20);
		printf("%s", phrase2);
		scanf("%s",le_nom); //l'utilisateur entre le nom du citoyen
		
		if(strcmp(le_nom, "0") == 0){ // si le nom entr� est un 0 on casse la boucle
			break;
		}

        insertioncitoyen(px); // on insert un citoyen 
        px = px->pnext; // puis on se place dessus
        strcpy(px->nom,le_nom); // on copie le nom dedans

        gotoligcol(13, 19);
        printf(" Premnom : ");
        scanf("%s", &px->prenom); //remplie le prenom du citoyen
    }
}

////////////////////////////////////////////////////////////////////

void ajoutelieunom(Tlieu *pdeb, Tlieu *pfin) { //comment�
    Tlieu *px = NULL;
    char *debut = "Pas de lieu savegard�", *phrase1 = "Lieux pr�c�dent : ", *phrase2 = "Nom du lieu nouveau (0 pour arr�ter) : ",le_lieu[40];
    int xprecedent = 11, yprecedent = 20, xactuel = 17, yactuel = 20;

    px = pdeb;

    system("cls");

    if (pdeb->pavant == pfin) {
        strcpy(pdeb->nomLieu, debut); //rentre le caractere de base pour bien affich� une phrase d�finit et pas quelque chose au hasard de la m�moire
    }

    while (px->pavant != pfin) { //on se place juste avant le bidon de fin
        px = px->pavant;
    }

    while (TRUE) {
        system("cls");
        affichelogolieu1();

        cadre(xprecedent - 2, yprecedent - 3, 4, strlen(px->nomLieu) + strlen(phrase1) + 4); // on affiche un cadre en fonction de la longueur du lieu
        gotoligcol(xprecedent, yprecedent);
        printf("%s%s", phrase1, px->nomLieu); //on affiche le lieu precedent

        cadre(xactuel - 2, yactuel - 3, 4, strlen(phrase2) + 40);
        gotoligcol(xactuel, yactuel);
        printf("%s", phrase2);
		
		scanf("%s", &le_lieu);
		if(strcmp(le_lieu, "0") == 0){ // si le lieu entr� est un 0 on casse la boucle
			break;
		}
		
        insertionlieu(px); // on insert un lieu

        px = px->pavant;
        px->pliste = NULL; //on met la liste des participants � null
		strcpy(px->nomLieu,le_lieu); //on rentre le nom du lieu dans le nomLieu
    }
}

////////////////////////////////////////////////////////////////////

Date *ajoutdate() { //comment�
	//fonction qui permet de rentr� une date
    Date *ladate = (Date *) malloc(sizeof(Date)); //on alloue une case de memoire 

    //system("cls");
	
	affichedate();
	
    gotoligcol(15, 18);
    printf("Jour : ");
    scanf("%d", &ladate->jour); //on rentre le jour

    gotoligcol(16, 18);
    printf("Mois : ");
    scanf("%d", &ladate->mois); //puis le mois

    gotoligcol(17, 18);
    printf("Annee : ");
    scanf("%d", &ladate->annee); // et enfin la date

    return ladate;
}

////////////////////////////////////////////////////////////////////

void ajouteparticipantfete(Tcitoyen *pdebcit, Tparticipant *ppartdeb, Tlieu *pdeblieu,Tpoubelle *ppoubelledeb) { //comment�
	//cette foncion � pour but d'ajout� des participants � un lieux d�j� selectionner � partir de la liste des citoyens.
    int c = 32, fleche = 10, longueurcit = 0, memedate = 0;
    Tparticipant *ppartx = NULL, *pparty = NULL;
    Tcitoyen *pcit = NULL;
    Tpoubelle *ppoubellex = NULL, *ppoubelley = NULL;
    Date *ladate;

    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ppartx = ppartdeb; //on se place sur le d�vut de la liste des partcipants.

    while (ppartx->psuivant != NULL) { //si on est pas sur le dernier �l�ment de la liste des participants on y va
        ppartx = ppartx->psuivant;
    }
	
	
    longueurcit = longueurcitoyen(pdebcit); // on calcule la longueure de la liste des participants
    
    system("cls");
    gotoligcol(12,15);
    printf("Entrez la date de la fete :");
    ladate = ajoutdate(); //on ex�cute la fonction ajoutdate qui permet a l'utilisateur d'entr� une date au clavier
    
    
    while (TRUE) {
        affichagecitoyenvalidation(pdebcit, ppartdeb, ladate);
        affichefleche(fleche, hConsole);
        gotoligcol(9,20);
        printf("S�lectionnez les citoyens pr�sent � la fete :");
        gotoligcol(25, 7);
        printf("Appuyer sur echap pour quitter.");

        c = lireCaract();

        if (c == 472) { //fleche du haut
            if (fleche == 10) {} //si la fleche est sur le dernier �l�ment de liste on ne fait rien
            else {
                fleche = fleche - 1;  //la fleche monte
            }
        }

        if (c == 480) { //fleche du bas
            if (fleche == longueurcit + 10) {}  //si la fleche est sur le dernier �l�ment de liste on ne fait rien
            else {
                fleche = fleche + 1;  //la fleche descend
            }
        }
        if (c == 27) { //touche echap
            break;
        }
        if (c == 13) {  //touche entr�e
        
        	ppoubellex = ppoubelledeb; //on sauvgarde le d�but de la poubelle
        	ppoubelley = ppoubelledeb;
        	if (ppoubellex->seguente != NULL){ // si la poubelle n'est pas vide
        		while (ppoubellex->seguente != NULL){ // on se place sur le dernier �l�ment de la poubelle 
        			ppoubellex = ppoubellex->seguente;
				}
				ppartx->psuivant = ppoubellex->part; // on met le participant de la poubelle dans la liste des participants
				while (ppoubelley->seguente->seguente != NULL){ //on se place sur l'avant dernier �l�ment de la liste des poubelles
					ppoubelley= ppoubelley->seguente; 
				}
				ppoubelley->seguente = NULL; // on supprime le dernier �l�ment
			}
			else{
				ppartx->psuivant = (Tparticipant *) malloc(sizeof(Tparticipant)); //on alloue de la m�moir pour un nouveau participant si il y a rien dans la poubelle.
			}
            
			pcit = positionementcit(pdebcit, fleche - 9);  //on se place dans la liste sur l'element sur lequel est la fleche
            ppartx->ppersonne = pcit; //on met le citoyen dans le participant
            ppartx->date = ladate; //on met la date dans le participant
            ppartx = ppartx->psuivant; //on va sur le participant suivant
            ppartx->psuivant = NULL; //on dis que ce participant pointe sur un NULL
        }
    }
}

////////////////////////////////////////////////////////////////////

void afficheparticipantfete(Tcitoyen *pdebcit, Tcitoyen *pfincit, Tlieu *pdeblieu, Tlieu *pfinlieu,Tpoubelle *ppoubelledeb) { //comment�
	//cette fonction a pour but de s�lectionner le lieu dans lequel on veut ajouter des participants
    int c = 32, fleche = 11, longueurlistcit = 0, longueurlistlieu = 0;
    Tparticipant *pdebutlist = NULL, *ppart = NULL;
    Tlieu *px = NULL;

    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (TRUE) {
        longueurlistlieu = longueurlieu(pdeblieu); //on calcule la longueure de la liste des lieux pour g�r� la fl�che

        affichagenomlieu(pdeblieu); //on affiche la liste des lieux
        affichefleche(fleche, hConsole); //on affiche la fleche
        gotoligcol(9,9);
        printf("S�lectionnez le lieu de la fete :");
        gotoligcol(25, 7);
        printf("Appuyer sur echap pour quitter.");
        c = lireCaract(); //on lit le caractere entr� par l'utilisateur au clavier

        if (c == 472) { //fleche du haut
            if (fleche == 11) {} //si la fleche est sur le premier �l�ment de liste on ne fait rien
            else { //sinon on monte
                fleche = fleche - 1;  
            }
        }
        if (c == 480) { //fleche du bas
            if (fleche == longueurlistlieu + 11) {} //si la fleche est sur le dernier �l�ment de liste on ne fait rien
            else { //sinon on descend
                fleche = fleche + 1;  
            }
        }
        if (c == 27) { //touche echap
            break; //on casse la boucle
        }
        if (c == 13) { //touche entr�e
 
            px = positionelementlieu(pdeblieu, fleche - 10); //on se positionne sur le px eme element selectionn� avec la fleche
            if (px->pliste == NULL) { //on v�rifie qu'il n'y a pas d�j� une liste de participant li� � ce lieu
                pdebutlist = creationliste();  //on cr�e la liste des participants
                px->pliste = pdebutlist; //on lit la liste des participants avec le lieu
                px->pliste->psuivant = NULL; //on dis que le prochain participant est null
                ajouteparticipantfete(pdebcit, pdebutlist, pdeblieu,ppoubelledeb); //on lance la fonction ajouteparticipantfete
            } else {
                pdebutlist = px->pliste; //on dit que le d�but de la liste des participants est l'�lement sur lequel pointe le pliste du lieu
                ajouteparticipantfete(pdebcit, pdebutlist, pdeblieu,ppoubelledeb); //on lance la fonction ajouteparticipantfete
            }
        }
    }
}

////////////////////////////////////////////////////////////////////

int mois30_31(Date *d) { //comment�
	//cette fonction d�termine si le mois est un mois � 28 29 30 ou 31 jour
    int reponse = 0;
    if (d->mois == 1 || d->mois == 3 || d->mois == 5 || d->mois == 7 || d->mois == 8 || d->mois == 10 || d->mois == 12) { //on regarde si c est un mois a 31 jours
        reponse = 31;
    } else if (d->mois == 4 || d->mois == 6 || d->mois == 9 || d->mois == 11) { //on regarde si c est un mois a 30 jours
        reponse = 30;
    } else {
        if (d->annee % 4 == 0) { //on regarde si c est une ann�e bisextile pour le mois de f�vrier
            reponse = 29;
        } else {
            reponse = 28;
        }
    }
    return reponse;
}

////////////////////////////////////////////////////////////////////

int comparedatesemaine(Date *a, Date *b) { //comment�
	//cette fonction compart 2 dates
    int reponse = 0;

    if (a->annee == b->annee) { // si les 2 dates on la m�me ann�e
        if (a->mois == b->mois) {  // si les 2 dates on le m�me mois
            if (a->jour - 7 <= b->jour && a->jour >= b->jour) { //si les 2 dates on 7 jours d'�cart au maximum on met la r�ponse � 1
                reponse = 1;
            } else if (b->jour - 7 <= a->jour && b->jour >= a->jour) {
                reponse = 1;
            }
        } else if (a->mois - 1 == b->mois && a->jour + mois30_31(a) - 7 <= b->jour) { //si les 2 dates n'on pas le m�me mois quand m�me 7 jours d'ecart on met la r�ponse � 1
            reponse = 1;

        } else if (b->mois - 1 == a->mois && b->jour + mois30_31(b) - 7 <= a->jour) {
            reponse = 1;
        }
    } else if (a->annee - 1 == b->annee && a->jour + 31 <= b->jour) { //si les 2 dates n'on pas la m�me ann�e mais quand m�me 7 jours d'�art opn met la r�ponse � 1
        reponse = 1;
    } else if (b->annee - 1 == a->annee && b->jour + 31 <= a->jour) {
        reponse = 1;
    }
	//si la r�ponse est 1 c est que les 2 dates on 7 jours ou moins d'�cart
    return reponse;
}

////////////////////////////////////////////////////////////////////

int memedate(Date *a, Date *b){ //comment�
//cette fonction permet de v�rifier que 2 dates sont les m�me
	int reponse = 0;
	if (a->jour == b->jour && a->mois == b->mois && a->annee == b->annee){
		reponse = 1;
	}
	return reponse;
}

////////////////////////////////////////////////////////////////////

void affichecitrencontre(Tcitrencontre *pdebut) { //comment�
	//fonction qui affiche la liste des citrencontre
    Tcitrencontre *px;
    int poubelle = 0, i = 1, colonne = 10, ligne = 12;

    px = pdebut->pdespues;

    while (px != NULL) { // on parcourt la liste
    	affichelogorencontre();
        gotoligcol(i + colonne, ligne);
        printf("%s %s a �t� en contact avec %s %s le %d/%d/%d\n", pdebut->citoyen->nom,
               pdebut->citoyen->prenom, px->part->ppersonne->nom, px->part->ppersonne->prenom, px->part->date->jour,
               px->part->date->mois, px->part->date->annee); // on affiche tout
        i++;
        px = px->pdespues;
    }
    poubelle = lireCaract();
}

////////////////////////////////////////////////////////////////////

void afficherencontrecitecran2(Tcitoyen *pcit, Tlieu *plieudeb) { //comment�
	//cette fonction � pour but de cr�� une liste simplement chain�e contenant tous les citoyens qui on rencontr� le citoyen cherch�
    Tparticipant *ppartx = NULL, *ppartdeb = NULL, *pparty = NULL;
    Tlieu *plieux = NULL;
    Tcitrencontre *pcitrencontredeb = NULL, *pcitrencontrex = NULL;
    int creation = 0, c = 0;
    Date *ladate = NULL, *day = NULL;

    system("cls");
	gotoligcol(12,15);
    printf("Entrez la date � laquelle vous voulez chercher des citoyens en contact avec %s %s :",pcit->nom, pcit->prenom);
    ladate = ajoutdate(); // on demande � l'utilisateur de rentrer la date du jour

    system("cls");

    plieux = plieudeb;
    while (plieux->pavant != NULL) { // on parcoure la liste des lieux
        ppartx = plieux->pliste; // on sauvgarde le d�but de la liste des participants
        pparty = plieux->pliste;

        if (ppartx == NULL) { //si la liste des participants est vide on break et on passe au lieux suivant
            plieux = plieux->pavant;
        }
		else { //si il y a bien une liste de participant on entre
            while (ppartx->psuivant != NULL) { // on parcourt uen premiere fois la liste des participants
                if (pcit == ppartx->ppersonne) {
                    if (creation == 0) { // on cr�e une seul liste
                        pcitrencontredeb = creationrencontre(pcit); //on cr�� la liste des participants qui on rencontr� le citoyen cherch�
                        pcitrencontrex = pcitrencontredeb; // on sauvgarde le d�but de la liste pour l'affich� apr�s
                        creation++;  // on incr�mente pour ne cr�� qu'une fois la liste
                    }

                    day = ppartx->date;
					
                    while (pparty->psuivant != NULL) { //on parcoure une nouvelle fois la liste de participants pour trouver ceux qui �tait � la meme date que le citoyen et � 7 jours d'�cart
						if (memedate(day,pparty->date) == 1 && comparedatesemaine(ladate, pparty->date) == 1 && pcit != pparty->ppersonne) {
                            pcitrencontrex->pdespues = (Tcitrencontre *) malloc(sizeof(Tcitrencontre)); // on alloue une case de m�moire a un nouveau citrencontre
                            pcitrencontrex = pcitrencontrex->pdespues; // on va sur ce nouveau citrencontre
                            pcitrencontrex->citoyen = pcit; // on rentre le citoyen recherch�
                            pcitrencontrex->part = pparty; // on entre le participant
                            pcitrencontrex->pdespues = NULL; // on dis que le prochaine est NULL
                        }
                        pparty = pparty->psuivant;
                    }
                }
                ppartx = ppartx->psuivant;
            }
            plieux = plieux->pavant;
        }
    }
    if (creation > 0 && pcitrencontredeb->pdespues != NULL) {
        affichecitrencontre(pcitrencontredeb); // si on a cr�� la liste on l'affiche
    } else {
    	gotoligcol(15,15);
        printf("Ce citoyen n'a ete en contact avec personne"); //si on a pas cr�� la liste en ne l affiche pas
        c = lireCaract();
    }
}

////////////////////////////////////////////////////////////////////

void afficherencontrecitecran1(Tcitoyen *pdebcit, Tlieu *pdeblieu) { //comment&�
	//cette fonction permet de selectionner le citoyen que l'on va ensuite cherch� dans les participants (dans une autre fonction)
    int c = 32, fleche = 10, longueurlistcit = 0;
    Tcitoyen *pcit;

    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (TRUE) {
        longueurlistcit = longueurcitoyen(pdebcit); //on calcule la longeure total de la liste pour la gestion de la fleche

        affichagecitoyen(pdebcit); // on affiche la liste des participants
        affichefleche(fleche, hConsole); // on affiche la fleche
        gotoligcol(9,15);
        printf("S�lectionnez le citoyen que vous voulez chercher :");
		gotoligcol(25, 7);
        printf("Appuyer sur echap pour quitter.");
        
        c = lireCaract(); // on lit un caractere donn� par l'utilisateur au clavier

        if (c == 472) { // gestion de la fleche
            if (fleche == 10) {}
            else {
                fleche = fleche - 1;  //fleche du haut
            }
        }

        if (c == 480) {
            if (fleche == longueurlistcit + 10) {}
            else {
                fleche = fleche + 1;  //fleche du bas
            }
        }
        if (c == 27) { //touche echap
            break;
        }
        if (c == 13) { //touche entr�e
            pcit = positionementcit(pdebcit, fleche - 9); // on selectionne le x eme citoyen selectionner gr�ce � la position de la fleche 
            afficherencontrecitecran2(pcit, pdeblieu); // on lance la fonction suivante
        }
    }
}

////////////////////////////////////////////////////////////////////

void sauvegardelieu(Tlieu *pdeblieu) {// comment�
    FILE *fichier = NULL;
    Tlieu *plieux;
    char *buffer;
    int c;

    fichier = fopen("fichier_lieu.txt", "wt");

    plieux = pdeblieu->pavant;
    buffer = (char *) malloc(sizeof(char *));


    if (fichier != NULL) { // on v�rifie que le fichier est bien ouvert
        while (plieux->pavant != NULL) { // on parcour la liste des lieux
            strcpy(buffer, plieux->nomLieu);  // on copie le nom du lieux dans un buffer 
            fprintf(fichier, buffer); // on �crit le nom du lieu contenu dans le buffer dans le fichier
            fprintf(fichier, "\n"); // on revien a la ligne
            plieux = plieux->pavant;
        }
        fprintf(fichier, "$"); // on fini le fichier par un "$"
        fclose(fichier);

        system("cls");
        gotoligcol(9,9),
        printf("Fichier lieu bien sauvgard�.");
        affichesucces();
        c = lireCaract();
    } else { // si le fichier n'est pas bien ouvert on l'�crit
        printf("Impossible d'ouvrir le fichier test.txt");
    }
}

////////////////////////////////////////////////////////////////////

void sauvgardecitoyen(Tcitoyen *pdebcit) { //comment�
    FILE *fichier = NULL;
    Tcitoyen *pcitx;
    char *buffer1, *buffer2;
    int c;

    fichier = fopen("fichier_citoyen.txt", "wt");

    pcitx = pdebcit->pnext;
    buffer1 = (char *) malloc(sizeof(char *));
    buffer2 = (char *) malloc(sizeof(char *));


    if (fichier != NULL) { // on v�rifie que le fichier est bien ouvert
        while (pcitx->pnext != NULL) { // on parcour la liste des citoyens
            strcpy(buffer1, pcitx->nom); // on copie le nom et le prenom dans des buffer pour pourvoir les �crires dans le fichier
            strcpy(buffer2, pcitx->prenom);
            fprintf(fichier, buffer1); // on �crit le nom du citoyen dans le fichier
            fprintf(fichier, "\n");
            fprintf(fichier, buffer2);// on �crit le prenom du citoyen dans le fichier
            fprintf(fichier, "\n");
            pcitx = pcitx->pnext;
        }
        fprintf(fichier, "$");// on �crit "$" pour finaliser le fichier.
        
        system("cls");
        gotoligcol(9,9);
        printf("Fichier citoyen bien sauvgard�.");
        affichesucces();
        c = lireCaract(); // on met un lireCaract juste pour que la reponse reste afficher.
    } else { // si le fichier n'est pas bien ouvert on l'�crit
        printf("Impossible d'ouvrir le fichier test.txt");
    }
}

////////////////////////////////////////////////////////////////////

void sauvgardeparticipant(Tlieu *plieudeb, Tcitoyen *pcitdeb){ // comment�
	FILE *fichier = NULL;
	Tlieu *plieux = NULL;
	Tparticipant *ppartx =NULL;
	int c;
	char le_jour[10], le_mois[10], l_annee[10];
	
    fichier = fopen("fichier_participant.txt", "wt");
	
	plieux = plieudeb->pavant;
	
	if (fichier != NULL){  // on v�rifie que le fichier est bien ouvert
		while (plieux->pavant != NULL){
			fprintf(fichier, plieux->nomLieu);  // on �crit le nom de chaque lieu
			fprintf(fichier, "\n");
			
			if (plieux->pliste == NULL){  // si il n'y a pas de participant on met directement ":" et on passe au prochain lieu
				fprintf(fichier, ":");
				fprintf(fichier, "\n");
			}
			else {
				ppartx = plieux->pliste;
				while (ppartx->psuivant != NULL){ // si il y a des participant on �crit le nom
					fprintf(fichier, ppartx->ppersonne->nom);
					fprintf(fichier, "\n");
					fprintf(fichier, ppartx->ppersonne->prenom); //puis on �crit le prenom
					fprintf(fichier, "\n");

  					sprintf(le_jour, "%d", ppartx->date->jour); // conversion des int de la date en char pour pouvoir les �crit avec fprintf dans le fichier
  					sprintf(le_mois, "%d", ppartx->date->mois);
  					sprintf(l_annee, "%d", ppartx->date->annee);
  					
					fprintf(fichier, le_jour);  // on �crit dans le fichier la date
					fprintf(fichier, "\n");
					fprintf(fichier, le_mois);
					fprintf(fichier, "\n");
					fprintf(fichier, l_annee);
					fprintf(fichier, "\n");
					
					ppartx = ppartx->psuivant;
				}
				fprintf(fichier, ":"); // lorsque l'on a �crit tous les participants on �crit ":" pour passer au prochain lieu
				fprintf(fichier, "\n");
			}
			plieux = plieux->pavant;
		}
		fprintf(fichier, "$");  // on �crit "$" pour finaliser le fichier.
		system("cls");
		
		gotoligcol(9,9);
        printf("Fichier participants bien sauvgard�.");
        affichesucces();
        c = lireCaract();
	}
	else{ // si le fichier n'est pas bien ouvert on l'�crit juste
		printf("Impossible d'ouvrir le fichier des participants");
	}
	
    fclose(fichier); // on ferme le fichier
}

////////////////////////////////////////////////////////////////////

void ouvrir_lieu(Tlieu *pdeblieu, Tlieu *pfin) { //comment�
	//cette fonction permet d'ouvrir le fichier des lieux et de les mettre dans la liste des lieux
    FILE *fichier = NULL;
    Tlieu *plieux = NULL;
    char caractere[40];
    int c = 0,a = 0;

    plieux = pdeblieu;

    fichier = fopen("fichier_lieu.txt", "rt"); //on ouvre le fichier
    system("cls");

    while (TRUE) {
        fscanf(fichier, "%s", &caractere); //on lie chaque ligne du fichier

        if (!strcmp(caractere, "$")) { //on v�rifie que la chaine de caractere lu n'est pas un "$" sinon on casse la boucle
            break;
        }
        insertionlieu(plieux); // on insert un nouveau lieu
        plieux = plieux->pavant; //on va sur le lieu cr��
        plieux->pliste = NULL; // la liste des participants est nul
        strcpy(plieux->nomLieu, caractere); //on remplie le nom du lieu
    }
    gotoligcol(9,9);
    printf("Fichier lieu bien ouvert.\n");
    affichesucces();
    c = lireCaract();
    fclose(fichier);
}

////////////////////////////////////////////////////////////////////

void ouvrir_citoyen(Tcitoyen *pcitdeb, Tcitoyen *pcitfin) { //comment�
	//cette fonction permet d'ouvrir le fichier des citoyens et de cr�� la liste des citoyen
    FILE *fichier = NULL;
    char car_nom[40], car_prenom[40];
    int c = 0, oui = 0, non = 1;
    Tcitoyen *pcitx = NULL;

    pcitx = pcitdeb;

    fichier = fopen("fichier_citoyen.txt", "rt");//on ouvre le fichier
    system("cls");

    while (TRUE) {
        fscanf(fichier, "%s", &car_nom); //on lie chaque ligne du fichier
        fscanf(fichier, "%s", &car_prenom);

        if (strcmp(car_nom, "$") == oui) { //on v�rifie que la ligne impaire lu n'est pas un "$" sinon on sort de la boucle
            break;
        }
        
		insertioncitoyen(pcitx); //on insert un nouveau citoyen
        pcitx = pcitx->pnext; // on va sur ce nouveau citoyen
        strcpy(pcitx->nom, car_nom); //on copie le nom et le prenom dans les parametres du citoyen
        strcpy(pcitx->prenom, car_prenom);
    }
	gotoligcol(9,9);
    printf("Fichier citoyen bien ouvert.\n");
    
    affichesucces();
    c = lireCaract();
    fclose(fichier);
}

////////////////////////////////////////////////////////////////////

void ouvir_participant(Tlieu *plieudeb, Tcitoyen *pcitdeb) { //comment�
    FILE *fichier = NULL;
    char car_nom[40], car_prenom[40], car_nomlieu[40];
    int c = 0, le_jour = 0, le_mois = 0, l_annee = 0, non = 1, oui = 0, creation = 0,a=0;
    Date *ladate;
    Tlieu *plieux = NULL;
    Tparticipant *ppartx = NULL, *ppartdeb = NULL;
    Tcitoyen *pcitx = NULL, *pcitsauvgarde = NULL;

    fichier = fopen("fichier_participant.txt", "r");
    system("cls");

    plieux = plieudeb->pavant;

    if (fichier != NULL) { //on v�rifie que le fichier est bien ouvert
        while (TRUE) {
            fscanf(fichier, "%s", &car_nomlieu); //on scanf une premier ligne qui correspond au nom du lieu
            if (strcmp(car_nomlieu, "$") == oui){ // si ce nom de lieu est $ cela signifique que c est la fin du fichier donc je casse la coucle
            	break;
			}
            else if (strcmp(car_nomlieu, plieux->nomLieu) == oui) {  //on v�rifie que le nom du lieu inscrit dans le fichier est bien le m�me que celui dans la liste des lieux
                creation = oui; //on remet creation � oui pour cr�� la liste si il y a des participants
                while (TRUE) {
                    fscanf(fichier, "%s", &car_nom); //on lie une nouvelle ligne qui correspond au nom du citoyen
                    
                    if (strcmp(car_nom, ":") == oui) { // si le nom du citouen est ":" cela signifie qu'il n'y a plus de participant dans ce lieu et il passe donc au suivant
                        break;
                    }
                    
                    fscanf(fichier, "%s", &car_prenom); // on lit une deuxieme ligne qui correspond au nom du citoyen
                    pcitx = pcitdeb;
                    
                    while (pcitx->pnext != NULL) { //on parcourt la liste des citoyens pour trouver � quel citoyen correspont le nom et le prenom 
                        if (strcmp(car_nom, pcitx->nom) == oui && strcmp(car_prenom, pcitx->prenom) == oui) { // on compart le nom et le prenom de chaque citoyen avec ceux lu dans le fichier
                            pcitsauvgarde = pcitx; //quand il a trouver le bon il le sauvgarde dans un varible pour l'assigne au participant apr�s
                            break;
                        }
                        pcitx = pcitx->pnext;
                    }

                    if (creation == oui) { //on cr�� une fois la liste des participants si il y en a bien
                        ppartdeb = creationliste();  //on cr�e la liste des participants
                        plieux->pliste = ppartdeb; //on met le d�but de la liste des participants dans le pliste du lieux
                        ppartx = ppartdeb; // on initialise la varibla ppartx avec le d�but de la liste des participants
                        creation++; //on change la valeur de creation pour ne cr�� qu'une fois la liste
                    }
                    else {
                    	ppartx->psuivant = (Tparticipant *) malloc(sizeof(Tparticipant)); //on alloue une case de m�moire pour un nouvelle �l�ment si la liste a d�ja �t� cr��
                    	ppartx = ppartx->psuivant;
					}
					
                    ppartx->psuivant = NULL;
                    ppartx->ppersonne = pcitsauvgarde; //on met le citoyen sauvgard� plus haut dans le ppersonne du participant

                    fscanf(fichier, "%d", &le_jour); //on lit dans le fichier la date
                    fscanf(fichier, "%d", &le_mois);
                    fscanf(fichier, "%d", &l_annee);
					
					ladate = (Date *) malloc(sizeof(Date)); //on alloue une nouvelle case de memoire pour la date
					
                    ladate->jour = le_jour; //on met la date dans une variable 
                    ladate->mois = le_mois;
                    ladate->annee = l_annee;

                    ppartx->date = ladate; // on met la date dans le participant
                    //printf("lieu : %s \ncit : %s %s \ndate: %d/%d/%d\n", plieux->nomLieu,ppartx->ppersonne->nom, ppartx->ppersonne->prenom, ppartx->date->jour, ppartx->date->mois, ppartx->date->annee);
				}
            }
            plieux = plieux->pavant;
        }
    }
    gotoligcol(9,9);
    printf("Fichier participant bien ouvert.\n");
    affichesucces();
    oui = lireCaract(); //on met un lireCaract pour pouvoir voir le r�sultat
    fclose(fichier);
}

////////////////////////////////////////////////////////////////////

void affichemenusauvgarde() { //comment�
	//cette fonction sert � affich� le menu de la sauvegarde des listes
    system("cls");
    gotoligcol(11, 9);
    printf("Sauvegard� toutes les listes");
    gotoligcol(12, 9);
    printf("Sauvegard� la liste des citoyens");
    gotoligcol(13, 9);
    printf("Sauvegard� la liste des lieux");
    gotoligcol(14, 9);
    printf("Sauvegard� la liste des participants");
}

////////////////////////////////////////////////////////////////////

void menusauvgarde(Tlieu *pdeblieu, Tcitoyen *pcitdeb) { //comment�
    int c = 32, fleche = 11;

    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (TRUE) {
        affichemenusauvgarde();
        affichefichiers();
        affichefleche(fleche, hConsole);
        gotoligcol(25, 7);
        printf("Appuyer sur echap pour quitter.");
        c = lireCaract();

        if (c == 472) {
            if (fleche == 11) {}
            else {
                fleche = fleche - 1;  //fleche du haut
            }
        }
        if (c == 480) {
            if (fleche == 14) {}
            else {
                fleche = fleche + 1;  //fleche du bas
            }
        }
        if (c == 27) { //touche echap
            break;
        }
        if (c == 13) {
            if (fleche == 11) { //tous les fichiers
                sauvegardelieu(pdeblieu);
                sauvgardecitoyen(pcitdeb);
                sauvgardeparticipant(pdeblieu, pcitdeb);
                //sauvgarde tt les fichiers
            }
            if (fleche == 12) { //liste des citoyen
                sauvgardecitoyen(pcitdeb);
                //sauvgarde les citoyens
            }
            if (fleche == 13) { //liste des lieux
                sauvegardelieu(pdeblieu);  //sauvgarde la liste des lieux
            }
            if (fleche == 14) { //liste des participants
            	sauvgardeparticipant(pdeblieu, pcitdeb);
                //sauvgarde la liste des participants
            }
        }
    }
}

////////////////////////////////////////////////////////////////////

void affichemenuouvrir() { //comment�
    system("cls"); //fonction qui affiche juste des caracteres
    gotoligcol(11, 9);
    printf("Ouvrir toutes les listes");
    gotoligcol(12, 9);
    printf("Ouvrir la liste des citoyens");
    gotoligcol(13, 9);
    printf("Ouvrir la liste des lieux");
    gotoligcol(14, 9);
    printf("Ouvrir la liste des participants");
}

////////////////////////////////////////////////////////////////////

void menuouvrir(Tlieu *pdeblieu, Tlieu *pfin, Tcitoyen *pcitdeb, Tcitoyen *pcitfin) { //comment�
	//cette fonction permet de g�r� les fonctions d'ouverture des fichiers
    int c = 32, fleche = 11;

    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (TRUE) {
        affichemenuouvrir(); //on affche le menu � l'�cran
        affichefichiers();
        affichefleche(fleche, hConsole); //on affiche la fleche
        gotoligcol(25, 7);
        printf("Appuyer sur echap pour quitter.");
        c = lireCaract(); //on lit un caractere entr� au clavier par l'utilisateur

        if (c == 472) { //fleche du haut
            if (fleche == 11) {}
            else {
                fleche = fleche - 1;  
            }
        }
        if (c == 480) { //fleche du bas
            if (fleche == 14) {}
            else {
                fleche = fleche + 1;  
            }
        }
        if (c == 27) { //touche echap
            break;
        }
        if (c == 13) {
            if (fleche == 11) { // ouvre tous les fichiers
                ouvrir_lieu(pdeblieu, pfin);
                ouvrir_citoyen(pcitdeb, pcitfin);
                ouvir_participant(pdeblieu, pcitdeb);
            }
            if (fleche == 12) { //liste des citoyens
                ouvrir_citoyen(pcitdeb, pcitfin);
                //ouvrir les citoyens
            }
            if (fleche == 13) { //liste des lieux
                ouvrir_lieu(pdeblieu, pfin);  //ouvrir la liste des lieux
            }
            if (fleche == 14) { //liste des participants
                ouvir_participant(pdeblieu, pcitdeb);//ouvrir la liste des participants
            }
        }
    }
}

////////////////////////////////////////////////////////////////////

int compardate(Date *a,Date *b){
	//cette fonction permet de dire si la date a est strictement avant (reponse = 1) ou apres (reponse = 0) de la date b
	int reponse = 0;
	
	if (a->annee == b->annee){ // si l annee est la meme
		if (a->mois == b->mois){ // si le mois est le meme
			if (a->jour > b->jour){ // si le jour de la date rentr� est plus grand que celui de la date de la fete on met reponse � 1
				reponse = 1;
			}
		}
		else if (a->mois > b->mois){ // si le mois de la date rentr� est plus grand que celui de la date de la fete on met reponse � 1
			reponse = 1;
		}
	}
	else if (a->annee > b->annee){ // si l'ann�e de la date rentr� est plus grande que celui de la date de la fete on met reponse � 1
		reponse = 1;
	}
	
	return reponse;
}

////////////////////////////////////////////////////////////////////

void supprimer(Tlieu *plieudeb,Tpoubelle *ppoubelledeb){ // comment�
	Date * ladate = NULL;
	int rien =0, i=0;
	Tlieu * plieux = NULL;
	Tparticipant *ppartx = NULL, *pparty = NULL;
	Tpoubelle *ppoubellex = NULL;
	
	plieux = plieudeb->pavant;
	
	system("cls");
	gotoligcol(12,15);
	printf("Entrez la date � partir de laquelle vous voulez supprimer les �venements ant�rieurs :");
	ladate = ajoutdate();
	
	ppoubellex = ppoubelledeb;
	
	while (plieux->pavant != NULL){ // on parcourt la liste des lieux
		if (plieux->pliste != NULL){ // on v�rifie qu'il y a une liste de participants pour ce lieu
			ppartx = plieux->pliste;
			while (ppartx != NULL){ // on parcourt la liste des participants
				if (compardate(ladate,ppartx->date)==1){ // si la date est inferieur a celle rentr� par l'utilisateur on met ce parcicipant dans la poubelle et on le suprime de la liste des participants
					ppoubellex->seguente = (Tpoubelle *) malloc(sizeof(Tpoubelle)); //on alloue une case � un nouveau poubellex
					ppoubellex = ppoubellex->seguente; //on va sur le poubellex que l'on vient de cr��
					ppoubellex->part = ppartx; //on met fait pointer vers le participant que l'on supprime
					ppoubellex->seguente = NULL; //le prochain est nul
					
					pparty = plieux->pliste;
					while (pparty != NULL) { //on parcourt la liste des participants pour supprimer de la liste des participants
						if (pparty == ppartx){ // si c est le premier �l�ment on lit le pliste du lieu avec le 2 eme participant
							plieux->pliste = pparty->psuivant;
						}
						else if (pparty->psuivant == ppartx){ //si le participant est au milieu de la liste ou � la fin 
							pparty->psuivant = ppartx->psuivant; //on assigne le pointeur du participant � celui d apr�s celui que l'on veut enlever
						}
						pparty = pparty->psuivant;
					}
				}
				ppartx = ppartx->psuivant;
			}
		}
		plieux = plieux->pavant;
	}
	system("cls");
	affichesupprimer(); //on affiche le logo pour bien voir que la fonction s'est ex�cuter correctement
	gotoligcol(12,15);
	printf("Appuyer sur une touche pour continer.");
	rien=getch();
}

////////////////////////////////////////////////////////////////////

void affichagegeneral(Tcitoyen *pstartcit, Tcitoyen *pendcit, Tlieu *piniciolieu, Tlieu *pfinlieu,Tpoubelle *ppoubelledeb) { //comment�

    int fleche = 13, c = 32, poubelle=0;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (TRUE) {

        afficheMenu(hConsole); //on affiche le menu
        affichefleche(fleche, hConsole); //on affiche la fl�che
        c = lireCaract(); //on lie un caract�re entr� au clavier


        if (c == '1') { //si la touche entr� au clavier est 1 on ex�cute la fonction suivante
            affichagecitoyen(pstartcit);
            printf("Appuyer sur une touche pour continuer");
    		poubelle = lireCaract(); //on met un lirCaract pour attendre que l'utilisateur appuie sur une touche pour passer � la suite
        }
        if (c == '2') { //si la touche entr� au clavier est 2 on ex�cute la fonction suivante
            affichagenomlieu(piniciolieu);
            printf("Appuyer sur une touche pour continuer");
    		poubelle = lireCaract(); //on met un lirCaract pour attendre que l'utilisateur appuie sur une touche pour passer � la suite
        }
        if (c == '3') { //si la touche entr� au clavier est 3 on ex�cute la fonction suivante
            ajoutecitoyen(pstartcit, pendcit);
        }
        if (c == '4') { //si la touche entr� au clavier est 4 on ex�cute la fonction suivante
            ajoutelieunom(piniciolieu, pfinlieu);
        }
        if (c == '5') { //si la touche entr� au clavier est 5 on ex�cute la fonction suivante
            afficheparticipantfete(pstartcit, pendcit, piniciolieu, pfinlieu,ppoubelledeb);
        }
        if (c == '6') { //si la touche entr� au clavier est 6 on ex�cute la fonction suivante
            afficherencontrecitecran1(pstartcit, piniciolieu);
        }
        if (c == '7') { //si la touche entr� au clavier est 7 on ex�cute la fonction suivante
            menusauvgarde(piniciolieu, pstartcit);
        }
        if (c == '8') { //si la touche entr� au clavier est 8 on ex�cute la fonction suivante
            menuouvrir(piniciolieu, pfinlieu, pstartcit, pendcit);
        }
        if (c == '9') { //si la touche entr� au clavier est 9 on ex�cute la fonction suivante
            supprimer(piniciolieu,ppoubelledeb);
        }
        if (c == 'm') { //si la touche entr� au clavier est 9 on ex�cute la fonction suivante
            afficheparticipant(piniciolieu);
        }
        if ( c == 'p') {
        	affichepoubelle(ppoubelledeb);
		}

        if (c == 472) { //fleche du haut
            if (fleche == 13) {
				fleche = 22;
			} //si la fl�che est en haut de la liste et qu elle monte, elle revient en bas
            else {
                fleche = fleche - 1;  
            }
        }

        if (c == 480) { //fleche du bas
            if (fleche == 22) { //si la fl�che est en bas de la liste et qu elle descend, elle revient en haut
				fleche = 13;
			}
            else {
                fleche = fleche + 1;  
            }
        }

        if (c == 13) { //touche entr�e
            switch (fleche) {  //affichage selon l'emplacement du curseur (fleche)
                case 13: //si la fl�che est sur l'�l�ment 1 de la liste on ex�cute la fonction suivante
                    affichagecitoyen(pstartcit);
                    printf("Appuyer sur une touche pour continuer");
    				poubelle = lireCaract(); //on met un lirCaract pour attendre que l'utilisateur appuie sur une touche pour passer � la suite
                    break;
                case 14: //si la fl�che est sur l'�l�ment 2 de la liste on ex�cute la fonction suivante
                    affichagenomlieu(piniciolieu);
                    printf("Appuyer sur une touche pour continuer");
    				poubelle = lireCaract(); //on met un lirCaract pour attendre que l'utilisateur appuie sur une touche pour passer � la suite
                    break;
                case 15: //si la fl�che est sur l'�l�ment 3 de la liste on ex�cute la fonction suivante
                    ajoutecitoyen(pstartcit, pendcit);
                    break;
                case 16: //si la fl�che est sur l'�l�ment 4 de la liste on ex�cute la fonction suivante
                    ajoutelieunom(piniciolieu, pfinlieu);
                    break;
                case 17: //si la fl�che est sur l'�l�ment 5 de la liste on ex�cute la fonction suivante
                    afficheparticipantfete(pstartcit, pendcit, piniciolieu, pfinlieu,ppoubelledeb);
                    break;
                case 18: //si la fl�che est sur l'�l�ment 6 de la liste on ex�cute la fonction suivante
                    afficherencontrecitecran1(pstartcit, piniciolieu);
                    break;
                case 19: //si la fl�che est sur l'�l�ment 7 de la liste on ex�cute la fonction suivante
                    menusauvgarde(piniciolieu, pstartcit);
                    break;
                case 20: //si la fl�che est sur l'�l�ment 8 de la liste on ex�cute la fonction suivante
                    menuouvrir(piniciolieu, pfinlieu, pstartcit, pendcit);
                    break;
                case 21: //si la fl�che est sur l'�l�ment 9 de la liste on ex�cute la fonction suivante
                    supprimer(piniciolieu,ppoubelledeb);
                    break;
            }
        }
        if (c == '0') break;
    }
}

////////////////////////////////////////////////////////////////////

void main() { //comment�
    Tcitoyen *pstartcit = NULL, *pendcit = NULL;
    Tlieu *piniciolieu = NULL, *pfinlieu = NULL;
	Tpoubelle *ppoubelledeb = NULL;
	
    setlocale(LC_ALL, "");//sert � pouvoir �crire les accents sans probl�me

    ////Creation de la liste des citoyen//////
    pstartcit = (Tcitoyen *) malloc(sizeof(Tcitoyen));
    pendcit = (Tcitoyen *) malloc(sizeof(Tcitoyen));
    pstartcit->pprevious = NULL;
    pendcit->pnext = NULL;
    pstartcit->pnext = pendcit;
    pendcit->pprevious = pstartcit;


    ////Creation de la liste de lieu///////
    piniciolieu = (Tlieu *) malloc(sizeof(Tlieu));
    pfinlieu = (Tlieu *) malloc(sizeof(Tlieu));
    piniciolieu->pprecedent = NULL;
    pfinlieu->pavant = NULL;
    piniciolieu->pavant = pfinlieu;
    pfinlieu->pprecedent = piniciolieu;
    
    ppoubelledeb = (Tpoubelle *) malloc(sizeof(Tpoubelle));
	ppoubelledeb -> part = NULL;
	ppoubelledeb -> seguente = NULL; 

    affichagegeneral(pstartcit, pendcit, piniciolieu, pfinlieu,ppoubelledeb);
}
