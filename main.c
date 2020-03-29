#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <string.h>
// #include <wiringPi.h>

//-------------------------------------
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
//---------funtion/procedure-----------
void initialisation(tableau Jeu);
void affichage(tableau Jeu);
int colonneEstVide(tableau Jeu,int i);
void placerPion(tableau Jeu, int i, int joueur);
void enregistrerScore(tableau Jeu,int joueur,int cptTour);
//void initBoutonLed();
long random();
int estGagner(tableau Jeu);
int joueurcommence(int joueur1);
int tabelauEstRempli(tableau Jeu);

//---------Void main-------------------
void main(){
	tableau jeu;
	int valeurClavier;
	int cptTour = 1;
	int estGagne = 0;
	char non[] = "non";
	char oui[] = "oui";
	char rejouer[] = "oui";
	int reponses = 0;
	char reponse[] = "oui";
	//initBoutonLed();
	while(reponses != 1){
		initialisation(jeu);
		int joueur = random(); // peut prendre la valeur 1 ou 2 en fonction du joueur 
		if(joueur == 1){
			printf("joueur 1 à vous de commencer, ");
			// -------------- led---------------//
			// digitalWrite(LEDV,HIGH);
			// digitalWrite(LEDR,LOW);
			//---------------------------------//
		}else{
			printf("joueur 2 à vous de commencer, ");
			// -------------- led---------------//
			// digitalWrite(LEDV,LOW);
			// digitalWrite(LEDR,HIGH);
			//---------------------------------//
		}
		while(estGagne != 2 || estGagne != 1){
				//------------------ demande/placement du pionn----------------------
			printf(" dans quelle colonne voulez-vous placer vote pion ? [de 1 à 6]\n");
			scanf("%d",&valeurClavier);
			while(valeurClavier >= 7 || valeurClavier <= 0){
				printf("La colonne existe pas, choisez une colonne du tableau de [de 1 à 6] : \n");
				scanf("%d",&valeurClavier);
				//------------- Bouton ----------------//





				////////////////////////////////////////
			}
			while(colonneEstVide(jeu,valeurClavier) == 0){
				printf("La colonne est plein, choisiez une autre colonne du tabelau de [de 1 à 6] \n");
				scanf("%d",&valeurClavier);
			}

			placerPion(jeu,valeurClavier, joueur);
			affichage(jeu);
				//--------------------Cas ou le tableau et rempli---------------------
			if(tabelauEstRempli(jeu) == 1){
				printf("Match nul !\n");
				break;
			}
				// -----------------------------condition de victoire-----------------
			estGagne = estGagner(jeu);
			if(estGagne == 1){
				printf("Bravo joueur 1 vous avez gagné\n");
				 //-----------Led -----------------//
				// digitalWrite(LEDV,HIGH);
				// digitalWrite(LEDR,LOW);	
				//---------------------------------
				break;
			}
			if(estGagne == 2){
				printf("bravo joueur 2 vous avez gagné\n");
				 //-----------Led -----------------//
				// digitalWrite(LEDV,LOW);
				// digitalWrite(LEDR,HIGH);
				//---------------------------------
				break;
			}
				//---------------------------- Joueur --------------------------------
			if(joueur == 2){
				printf("Joueur 1 à vous de jouer,");
				joueur = 1;
				 //-----------Led -----------------//
				// digitalWrite(LEDV,HIGH);
				// digitalWrite(LEDR,LOW);
				//---------------------------------
			}else{
				printf("Joueur 2 à vous de jouer,");
				joueur = 2;
				//-----------Led -----------------//
				// digitalWrite(LEDV,LOW);
				// digitalWrite(LEDR,HIGH);
				//---------------------------------
			}
			cptTour+=1;
		}
		printf("voulez-vous recommencer une partie ? [oui/non]\n");
		scanf("%s",&rejouer);
		if(!strcmp(rejouer,oui)){
			reponses = 0;
			printf("Va partie va se relancé\n");
		}else{
			reponses = 1;
			printf("Vous avez décidés de ne pas rejouer \n");
		}

		printf("voulez-vous enregistré les scores de cette partie ?[oui/non]\n");
		scanf("%s",&reponse);
		if(!strcmp(reponse,oui)){
			enregistrerScore(jeu,joueur,cptTour);
			printf("Les scores on était sauvegardé\n");
		}else{
			printf("Pas d'enregistrement des scores\n");
		}

	}
}
