#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
// #include <wiringPi.h>

 //------------Define------------------------
#define LIGNE 7
#define COLONNE 6
// #define LEDR 22
// #define LEDV 26
// #define DELAI 500 
// #define LED0 7
// #define LED1 0
// #define LED2 1
// #define LED3 2
// #define LED4 3
// #define LED5 4
// #define LED6 5
// #define LED7 6
// #define BTG 29
// #define BTD 21
typedef char tableau[LIGNE][COLONNE];

//------------procedure---------------------

void initialisation(tableau Jeu);
void affichage(tableau Jeu);
void placerPion(tableau Jeu, int i, int joueur);
void enregistrerScore(tableau Jeu,int joueur,int cptTour);
//void initBoutonLed();
long random();
int colonneEstVide(tableau Jeu,int i);
int estGagner(tableau Jeu);
int joueurcommence(int joueur1);
int tabelauEstRempli(tableau Jeu);

//------------Corp des procedures------------

void initialisation(tableau Jeu ){
	for(int i=0; i <= LIGNE; i++){
		for(int j=0; j <= COLONNE; j++){
			Jeu[i][j]=' ';
		}
	}
}
  
void affichage(tableau Jeu){
	for(int j = 0; j<COLONNE;j++){
		printf("[%c]",Jeu[1][j]);
		printf("[%c]",Jeu[2][j]);
		printf("[%c]",Jeu[3][j]);
		printf("[%c]",Jeu[4][j]);
		printf("[%c]",Jeu[5][j]);
		printf("[%c]\n",Jeu[6][j]);
	}
}

int colonneEstVide(tableau Jeu,int i){
	int nbjetonDansUneColonne = 0;
	for(int j = 0; j < COLONNE; j++){
		if(Jeu[i][j] == ' '){
			nbjetonDansUneColonne += 1;
		}else{
			nbjetonDansUneColonne += 0;
		}
	}
	return nbjetonDansUneColonne;
}

void placerPion(tableau Jeu, int i, int joueur){
	if(joueur == 1){
		int valeurTableauEstVide = colonneEstVide(Jeu,i);
		if( valeurTableauEstVide == 0){
			Jeu[i][valeurTableauEstVide]= 'X';
		}else{
			Jeu[i][valeurTableauEstVide-1]= 'X';
		}
	}
	if(joueur == 2){
		int valeurTableauEstVide = colonneEstVide(Jeu,i);
		if( valeurTableauEstVide == 0){
			Jeu[i][valeurTableauEstVide]= 'O';
		}else{
			Jeu[i][valeurTableauEstVide-1]= 'O';
		}
	}
}

long random(){
	srand(time(NULL));
	long random = rand()%2+1;
	while( rand == 0){
		random = rand()%2+1;
	}
	return random;
}
int joueurcommence(int joueur1){
	int aleatoir= random();
	if( aleatoir %2 ==  0 ){
		printf("joueur 1 à vous de commencez, ");
		return joueur1 = 1;
	}else{
		printf("joueur 2 à vous de commencez, ");
		return joueur1 = 2;
	}
}

int tabelauEstRempli(tableau Jeu){ 
	int cptColloneVide = 0;
	for(int i = 0; i <= COLONNE; i++){
		if(colonneEstVide(Jeu,i) == 0){
			cptColloneVide += 1;
		}
	}
	if(cptColloneVide == 6){
		return 1;
	} 
}

void enregistrerScore(tableau Jeu,int joueur,int cptTour){
	FILE* fichier = NULL;
	fichier = fopen("Score.txt","a");
	if(fichier != NULL){
		for(int j = 0; j<COLONNE;j++){
			fprintf(fichier,"[%c]",Jeu[1][j]);
			fprintf(fichier,"[%c]",Jeu[2][j]);
			fprintf(fichier,"[%c]",Jeu[3][j]);
			fprintf(fichier,"[%c]",Jeu[4][j]);
			fprintf(fichier,"[%c]",Jeu[5][j]);
			fprintf(fichier,"[%c]\n",Jeu[6][j]);
		}
		if(joueur == 1){
			fprintf(fichier,"\nBravo joueur 1 vous avez gagné\n");
			fprintf(fichier,"Vous avez gagné en %d tour bien joué\n\n", cptTour);
		}else{
			fprintf(fichier,"\nBravo joueur 2 vous avez gagné\n");
			fprintf(fichier,"Vous avez gagné en %d tour bien joué\n\n", cptTour);
		}
		fprintf(fichier,"-----------------------------------------------------------\n\n");
	}else{
		printf("Erreur à l'ouverture du fichier f1\n");
		fclose(fichier);
	}
}

// void initBoutonLed(){
// 	pinMode(BTG,INPUT);
// 	pinMode(BTD,INPUT);
// 	pinMode(LEDV,OUTPUT);
// 	pinMode(LEDR,OUTPUT);
// 	pinMode(LED0,OUTPUT);
// 	pinMode(LED1,OUTPUT);
// 	pinMode(LED2,OUTPUT);
// 	pinMode(LED3,OUTPUT);
// 	pinMode(LED4,OUTPUT);
// 	pinMode(LED5,OUTPUT);
// 	pinMode(LED6,OUTPUT);
// 	pinMode(LED7,OUTPUT);
// }

int estGagner(tableau Jeu){
	int gagner = 0 ;
	int nbJetonRouge = 0;
	int nbJetonVert = 0;
	for (int x=0; x<LIGNE; x++){
		for (int y=0; y<COLONNE; y++){
							// -----------------Vérification de la Colonne---------------------------------
			if (Jeu[x][y]==Jeu[x][y+1] && Jeu[x][y]==Jeu[x][y+2] && Jeu[x][y]==Jeu[x][y+3] && Jeu[x][y]=='X' ){
				nbJetonRouge = 4;
				return gagner = 1;
				break;				
			}else{
				nbJetonRouge=0;
			}
			if (Jeu[x][y]==Jeu[x][y+1] && Jeu[x][y]==Jeu[x][y+2] && Jeu[x][y]==Jeu[x][y+3] && Jeu[x][y]=='O' ){
				nbJetonVert=4;
				return gagner=2;
				break;
			}else{
				nbJetonVert=0;
			}
						//-----------------------Vérification de la ligne ---------------------------------
			if(Jeu[x][y]==Jeu[x+1][y] && Jeu[x][y]==Jeu[x+2][y] && Jeu[x][y]==Jeu[x+3][y] && Jeu[x][y]=='X'){
				nbJetonRouge=4;
				return gagner = 1;
				break;
			}else{
				nbJetonRouge=0;
			}
			if(Jeu[x][y]==Jeu[x+1][y] && Jeu[x][y]==Jeu[x+2][y] && Jeu[x][y]==Jeu[x+3][y] && Jeu[x][y]=='O'){
				nbJetonVert=4;
				return gagner=2;
				break;
			}else{
				nbJetonVert=0;
			}
							//------------------Vérification de la diagonale joueur 1--------------------------------
			if(Jeu[x][y]==Jeu[x+1][y+1] && Jeu[x][y]==Jeu[x+2][y+2] && Jeu[x][y]==Jeu[x+3][y+3]  && Jeu[x][y]=='X' ){
				nbJetonRouge = 4;
				return gagner = 1;
				break;
			}else{
				nbJetonRouge=0;
			}
			if(Jeu[x][y]==Jeu[x-1][y-1] && Jeu[x][y]==Jeu[x-2][y-2] && Jeu[x][y]==Jeu[x-3][y-3]  && Jeu[x][y]=='X' ){
				nbJetonRouge = 4;
				return gagner = 1;
				break;
			}else{
				nbJetonRouge=0;
			}
			if(Jeu[x][y]==Jeu[x-1][y+1] && Jeu[x][y]==Jeu[x-2][y+2] && Jeu[x][y]==Jeu[x-3][y+3] && Jeu[x][y]=='X' ){
				nbJetonRouge = 4;
				return gagner = 1;
				break;
			}else{
				nbJetonRouge=0;
			}
			if(Jeu[x][y]==Jeu[x+1][y-1] && Jeu[x][y]==Jeu[x+2][y-2] && Jeu[x][y]==Jeu[x+3][y-3] && Jeu[x][y]=='X' ){
				nbJetonRouge = 4;
				return gagner = 1;
				break;
			}else{
				nbJetonRouge=0;
			}
							//-----------------Vérification des diagonale pour le joueur 2--------------------------
			if(Jeu[x][y]==Jeu[x+1][y+1] && Jeu[x][y]==Jeu[x+2][y+2] && Jeu[x][y]==Jeu[x+3][y+3] && Jeu[x][y]=='0' ){
				nbJetonVert=4;
				return gagner=2;
				break;
			}else{
				nbJetonVert=0;
			}
			if(Jeu[x][y]==Jeu[x-1][y-1] && Jeu[x][y]==Jeu[x-2][y-2] && Jeu[x][y]==Jeu[x-3][y-3] && Jeu[x][y]=='O' ){
				nbJetonVert=4;
				return gagner=2;
				break;
			}else{
				nbJetonVert=0;
			}
			if(Jeu[x][y]==Jeu[x-1][y+1] && Jeu[x][y]==Jeu[x-2][y+2] && Jeu[x][y]==Jeu[x-3][y+3] && Jeu[x][y]=='O' ){
				nbJetonVert=4;
				return gagner=2;
				break;
			}else{
				nbJetonVert=0;
			}
			if( Jeu[x][y]==Jeu[x+1][y-1] && Jeu[x][y]==Jeu[x+2][y-2] && Jeu[x][y]==Jeu[x+3][y-3] && Jeu[x][y]=='O' ){
				nbJetonVert=4;
				return gagner=2;
				break;
			}else{
				nbJetonVert=0;
			}
			
		}
	}
}



//-------------- trace de recherche-----------------------

/*tab jeu;
tab *j =&jeu;
//char *J = (char *)malloc(LIGNE * COLONNE * sizeof(char)); 
initialisation(j);
	for (int i = 0; i <= LIGNE; i++) {
     	for (int j = 0; j <= COLONNE; j++) {
       	printf("[%c]", *(jeu + i*COLONNE + j));
       	if(j == COLONNE){
       		printf("\n");
       	} 
   	}
}

			if(Jeu[x][y]==Jeu[x+1][y+1] && Jeu[x][y]==Jeu[x+2][y+2] && Jeu[x][y]==Jeu[x+3][y+3] || Jeu[x][y]==Jeu[x-1][y-1] && Jeu[x][y]==Jeu[x-2][y-2] && Jeu[x][y]==Jeu[x-3][y-3] || Jeu[x][y]==Jeu[x-1][y+1] && Jeu[x][y]==Jeu[x-2][y+2] && Jeu[x][y]==Jeu[x-3][y+3] || Jeu[x][y]==Jeu[x+1][y-1] && Jeu[x][y]==Jeu[x+2][y-2] && Jeu[x][y]==Jeu[x+3][y-3] && Jeu[x][y]=='1' ){
				nbJetonRouge=4;
				printf("Bon");
			}else{
				nbJetonRouge=0;
			}

			if(Jeu[x][y]==Jeu[x+1][y+1] && Jeu[x][y]==Jeu[x+2][y+2] && Jeu[x][y]==Jeu[x+3][y+3] || Jeu[x][y]==Jeu[x-1][y-1] && Jeu[x][y]==Jeu[x-2][y-2] && Jeu[x][y]==Jeu[x-3][y-3] || Jeu[x][y]==Jeu[x-1][y+1] && Jeu[x][y]==Jeu[x-2][y+2] && Jeu[x][y]==Jeu[x-3][y+3] || Jeu[x][y]==Jeu[x+1][y-1] && Jeu[x][y]==Jeu[x+2][y-2] && Jeu[x][y]==Jeu[x+3][y-3] && Jeu[x][y]=='0' ){
				nbJetonVert=4;
			}else{
				nbJetonVert=0;
			}

	Jeu = malloc(LIGNE * sizeof(*Jeu));

	for(int i=0 ; i < LIGNE; i++){
	     Jeu[i] = malloc(COLONNE * sizeof(**Jeu) ); 
	}*/

	/*tab jeu;
	tab *j =&jeu;

	//char *J = (char *)malloc(LIGNE * COLONNE * sizeof(char)); 
	initialisation(j);

	for (int i = 0; i <= LIGNE; i++) {
      	for (int j = 0; j <= COLONNE; j++) {
        	printf("[%c]", *(jeu + i*COLONNE + j));
        	if(j == COLONNE){
        		printf("\n");
        	} 
      	}
    }



			if(Jeu[x][y]=='1'){
				if(Jeu[x][y]==Jeu[x][y+1]){
					if(Jeu[x][y]==Jeu[x][y+2]){
						if(Jeu[x][y]==Jeu[x][y+3]){
							printf("coucou\n");
							nbJetonRouge = 4;
						}
					}
				}
			}

    */