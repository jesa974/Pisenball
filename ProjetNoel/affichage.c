#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "GfxLib.h"
#include "BmpLib.h"
#include "calcul.h"
#include "gereBouton.h"
#include "affichage.h"
#include "imageSF.h"
#include "debug.h"

extern int nb_obstacles ;
extern obstacle liste_obstacles[] ;

//Initialisation du fond
void initFond(image fonds){
	
	fonds[0] = lisBMPRGB("plateau.bmp");
}

//Affichage du fond
void afficheFond(image fonds){
		
	ecrisImage(0, 0, fonds[0]->largeurImage, fonds[0]->hauteurImage, fonds[0]->donneesRGB);

}


//Initialisation du menu
void initMenu(image menus){
	
	menus[0] = lisBMPRGB("menu.bmp");
}

//Affichage du menu
void afficheMenu(image menus){
		
	ecrisImage(0, 0, menus[0]->largeurImage, menus[0]->hauteurImage, menus[0]->donneesRGB);
}


void dessineObstacles(coord pos0,coord v0){

	int i = 0 ;
	coord inter ;
	coord D ;
	coord T ;
	char numero[10] ;

	couleurCourante(255, 0, 0);
	for (i=0;i<nb_obstacles;i++) {
		if (liste_obstacles[i].type == 1 && liste_obstacles[i].etat == 1) {
			couleurCourante(liste_obstacles[i].c.R, liste_obstacles[i].c.G, liste_obstacles[i].c.B);
			ligne(liste_obstacles[i].p1.x,liste_obstacles[i].p1.y,liste_obstacles[i].p2.x,liste_obstacles[i].p2.y) ;
			//if (isDebug() == 1) {
				//D.x = pos0.x + v0.x ;
				//D.y = pos0.y + v0.y ;
		        	//inter = getIntersectionPoint2(liste_obstacles[i].p1,liste_obstacles[i].p2,pos0,D) ;
        			//cercle(inter.x,inter.y,5) ;
        			//sprintf(numero, "%2d", i);
        			//couleurCourante(255, 255, 255);
        			//afficheChaine(numero,10,inter.x,inter.y) ;
			//}
		} else if (liste_obstacles[i].type == 2 && liste_obstacles[i].etat == 1) {
			cercle(liste_obstacles[i].p1.x,liste_obstacles[i].p1.y,liste_obstacles[i].rayon);
		} else if (liste_obstacles[i].type == 3 && liste_obstacles[i].etat == 1) {
                        couleurCourante(liste_obstacles[i].c.R, liste_obstacles[i].c.G, liste_obstacles[i].c.B);
                        ligne(liste_obstacles[i].p1.x,liste_obstacles[i].p1.y,liste_obstacles[i].p1.x + liste_obstacles[i].p2.x,liste_obstacles[i].p1.y + liste_obstacles[i].p2.y) ;
                       //if (isDebug() == 1) {
                                //D.x = pos0.x + v0.x ;
                                //D.y = pos0.y + v0.y ;
				//T.x = liste_obstacles[i].p1.x + liste_obstacles[i].p2.x ;
				//T.y = liste_obstacles[i].p1.y + liste_obstacles[i].p2.y ;
                                //inter = getIntersectionPoint2(liste_obstacles[i].p1,T,pos0,D) ;
                                //cercle(inter.x,inter.y,5) ;
                                //sprintf(numero, "%2d", i);
                                //couleurCourante(255, 255, 255);
                                //afficheChaine(numero,10,inter.x,inter.y) ;
                        //}
                }
	}

}



//initialisation du ressort
void initialiseRessort(imgRes ressort){
	int i;
	char image[40], numero[3];
	
	for(i = 1; i < NB_ATTITUDE+1; i++){
		strcpy(image, "ressort");
		sprintf(numero, "%d", i);
		strcat(image, numero);
		strcat(image, ".bmp");
		ressort[i-1] = lisBMPRGB(image);
	}
}

//Affichage du ressort
void afficheRessort(imgRes ressort, int N, int B){
	couleur RGB;
	RGB.r = 255;
	RGB.v = 255;
	RGB.b = 255;
	
	if(B == 1){
		N = 0;
	}	
	if(N == 0){
		ecrisImageSansFond(603, 0, 26, 38, ressort[2]->donneesRGB, RGB);
	}
	else if(N == 1){
		ecrisImageSansFond(603, 0, 26, 38, ressort[1]->donneesRGB, RGB);
	}
	else if(N == 2){
		ecrisImageSansFond(603, 0, 26, 38, ressort[0]->donneesRGB, RGB);
	}
	else{
		ecrisImageSansFond(603, 0, 26, 38, ressort[2]->donneesRGB, RGB);
	}
}

//Initialisation du flip (bump point)
void initFlip(image flip){
        flip[0] = lisBMPRGB("flip.bmp");
}

void afficheFlip(image flip) {
	couleur RGB;
        RGB.r = 255;
        RGB.v = 255;
        RGB.b = 255;

	for (int i=0;i<nb_obstacles;i++) {
		if (liste_obstacles[i].type == 3 && liste_obstacles[i].etat == 1) {
			ecrisImageSansFond(liste_obstacles[i].p1.x,liste_obstacles[i].p1.y, liste_obstacles[i].p2.x,liste_obstacles[i].p2.y, flip[0]->donneesRGB, RGB);
		}
	}

}

//Initialisation des Flipper
void initialiseFlipper(imgFlip flipper){
	
		flipper[0] = lisBMPRGB("flipperdroitbas.bmp");
		flipper[1] = lisBMPRGB("flipperdroithaut.bmp");
		flipper[2] = lisBMPRGB("flippergauchebas.bmp");
		flipper[3] = lisBMPRGB("flippergauchehaut.bmp");
		
}

//Affichage des Flipper
void afficheFlipper(imgFlip flipper, int L, int S, int Space){
	couleur RGB;
	RGB.r = 255;
	RGB.v = 255;
	RGB.b = 255;

	if ( S == 0 && L == 0 && Space == 0 ) {
		ecrisImageSansFond(390, 32, 63, 52, flipper[0]->donneesRGB, RGB);
		ecrisImageSansFond(288, 32, 63, 52, flipper[2]->donneesRGB, RGB);
		liste_obstacles[1].etat = 0 ;
		liste_obstacles[2].etat = 0 ;
		liste_obstacles[3].etat = 0 ;
		liste_obstacles[4].etat = 0 ;
	} else {
		if ( S == 1 || Space == 1 ) {
			ecrisImageSansFond(288, 32, 63, 52, flipper[3]->donneesRGB, RGB);
			liste_obstacles[1].etat = 1 ;
                	liste_obstacles[2].etat = 1 ;
		}
		if ( S == 0 && Space == 0 ) {
			ecrisImageSansFond(288, 32, 63, 52, flipper[2]->donneesRGB, RGB);
			liste_obstacles[1].etat = 0 ;
                	liste_obstacles[2].etat = 0 ;
		}
		if (( L == 1 || Space == 1)) {
			ecrisImageSansFond(390, 32, 63, 52, flipper[1]->donneesRGB, RGB);
			liste_obstacles[3].etat = 1 ;
                	liste_obstacles[4].etat = 1 ;
		}
		if ( L == 0 && Space == 0 ) {
			ecrisImageSansFond(390, 32, 63, 52, flipper[0]->donneesRGB, RGB);
			liste_obstacles[3].etat = 0 ;
                	liste_obstacles[4].etat = 0 ;
		}
	}
}


void affichageScore(int val_score, int high_score){
	char valeur[40], high_valeur[40] ;

        sprintf(valeur, "%5d", val_score);

        couleurCourante(255,0 , 0);
	sprintf(high_valeur, "%5d", high_score);
	afficheChaine("HIGH SCORE",25,15,555) ;
	afficheChaine(high_valeur,25,15,515) ;

	couleurCourante(0, 255, 0);
	sprintf(valeur, "%5d", val_score);
	afficheChaine("SCORE",25,15,480) ;
	afficheChaine(valeur,25,15,440) ;

}

int affichage_Restart(int compte) {
	float taille ;

	couleurCourante(255, 0, 0);
	taille = tailleChaine("Press R to RESTART",abs(compte)+10) ;
        afficheChaine("Press R to RESTART",abs(compte)+10,366-taille/2,200-(abs(compte)+10)/2) ;
	compte=(compte>15)?-15:compte+1;
	return compte ;
}

void afficheBalle(coord pos0, int N, int B){

	// printf("%f,%f\n",pos0.x,pos0.y) ;
	
	if(B != 0 && pos0.x == 617 && pos0.y < 48){
		pos0.y = 48;
	}
	else if(B == 0 && N == 0 && pos0.x == 617){
		pos0.y = 47;
	}
	else if(B == 0 && N == 1 && pos0.x == 617){
		pos0.y = 36;
	}
	else if(B == 0 && N == 2 && pos0.x == 617){
		pos0.y = 25;
	}
	
	couleurCourante(255, 0, 0);
	cercle(pos0.x, pos0.y, 10);

}


