#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "GfxLib.h"
#include "calcul.h"
#include "debug.h"

extern int mort ;
extern int score ;

coord getIntersectionPoint(coord A, coord B, coord C, coord D) ;
int isCollision(coord A, coord B, coord C, coord D) ;

int nb_obstacles = 50 ;
obstacle liste_obstacles[50] ;

coord acceleration(void) {
	coord a;
	
	a.x = 0;
	a.y = -9.81*sin(6.5);

	return a;
}


coord vitesse(coord a , coord v0) {
	coord v=v0;
	
	v.x = (a.x) + (v.x);
	v.y = (a.y) + (v.y);
	
	return v;
}


// coord position(coord v0, coord pos0) {
coord position(coord pos0, coord v0) {
	coord pos=pos0;
	
	pos.x = (pos.x) + (v0.x);
	pos.y = (pos.y) + (v0.y);
	if(pos.y < 10){
		pos.y = 9;
	}
	
	return pos;
}


coord gereRessort(int B, int N) {
	coord V;
	int i=0, v = 0;
	
	while(i==0)	{
		if(B==1) {
			v = N == 0 ? 10 : v;
			v = N == 1 ? 35 : v;
			v = N == 2 ? 50 : v;
			V.y=v;
			V.x=0;
		}
		i++;
	}
	
	return V;
}


coord collision(coord pos0, coord v0, int L, int S, int Space) {

	if ( pos0.x == 617 && (pos0.y < 48 || pos0.y + v0.y < 48)) {  // ralentissement de la balle dans rampe de lancement suite à non sortie dans le flipper
		v0.y = -(v0.y/2) ;
	}

	float s1 ;
	float d1,d2 ;
	coord T ;

	for (int i=0;i<nb_obstacles;i++){
		if (liste_obstacles[i].type == 1 && liste_obstacles[i].etat == 1) {
			if (isCollision(liste_obstacles[i].p1,liste_obstacles[i].p2,pos0,v0) == 1){
				v0.x= (v0.x + liste_obstacles[i].acceleration.x) * liste_obstacles[i].coef.x ;
				v0.y= (v0.y + liste_obstacles[i].acceleration.y) * liste_obstacles[i].coef.y ;
				score += liste_obstacles[i].points ;
				//if (isDebug() == 1 ) { printf("Collision %d\n",i); }
				//goto sortie ;
			}
		} else if (liste_obstacles[i].type == 2 && liste_obstacles[i].etat == 1) {
			s1 = liste_obstacles[i].rayon * liste_obstacles[i].rayon ;
			d1 = (pos0.x - liste_obstacles[i].p1.x)*(pos0.x - liste_obstacles[i].p1.x) + (pos0.y - liste_obstacles[i].p1.y)*(pos0.y - liste_obstacles[i].p1.y);
                	d2 = (pos0.x+v0.x - liste_obstacles[i].p1.x)*(pos0.x+v0.x - liste_obstacles[i].p1.x) + (pos0.y+v0.y - liste_obstacles[i].p1.y)*(pos0.y+v0.y - liste_obstacles[i].p1.y);

			if (d1 < s1 ){
                 	       //if (isDebug() == 1 ) { printf("Collision Cercle 1a (%f,%f)-(%f,%f) : %f\n",liste_obstacles[i].p1.x,liste_obstacles[i].p1.y,pos0.x,pos0.y,d1); }
                        	v0.x = (v0.x + liste_obstacles[i].acceleration.x) * liste_obstacles[i].coef.x ;
                        	v0.y = (v0.y + liste_obstacles[i].acceleration.y) * liste_obstacles[i].coef.y ;
				score += liste_obstacles[i].points ;
				goto sortie ;
                	} else if (d2 < s1) {
                        		//if (isDebug() == 1 ) { printf("Collision Cercle 1b (%f,%f)-(%f,%f) : %f\n",liste_obstacles[i].p1.x,liste_obstacles[i].p1.y,pos0.x,pos0.y,d2); }
                        		v0.x = (v0.x + liste_obstacles[i].acceleration.x) * liste_obstacles[i].coef.x ;
                        		v0.y = (v0.y + liste_obstacles[i].acceleration.y) * liste_obstacles[i].coef.y ;
					score += liste_obstacles[i].points ;
					goto sortie ;

                	}
		} else if (liste_obstacles[i].type == 3 && liste_obstacles[i].etat == 1) {
			T.x = liste_obstacles[i].p1.x + liste_obstacles[i].p2.x ;
                        T.y = liste_obstacles[i].p1.y + liste_obstacles[i].p2.y ;
                        if (isCollision(liste_obstacles[i].p1,T,pos0,v0) == 1){
                                v0.x= (v0.x + liste_obstacles[i].acceleration.x) * liste_obstacles[i].coef.x ;
                                v0.y= (v0.y + liste_obstacles[i].acceleration.y) * liste_obstacles[i].coef.y ;
                                score += liste_obstacles[i].points ;
                                liste_obstacles[i].etat = 0 ;
				//if (isDebug() == 1 ) { printf("Collision %d\n",i); }
                                goto sortie ;
                        }
		}
	}

sortie: printf("") ;

	coord T1 = {318,9} ;
	coord T2 = {417,8} ;
	if (isCollision(T1,T2,pos0,v0) == 1) {
		//if (isDebug() == 1 ) { printf("MMMMMMMort\n") ; }
		v0.x = 0 ;
		v0.y = 0 ;
		mort = 1 ;
	}
	
	if (pos0.y <10) {
		v0.y = -v0.y ;
	}
	
	return v0;
}

float coordonneeVecteur(float Ax, float Ay, float Bx, float By, float Px, float Py){
	coord A, B, P;
	float h;
	
	A.x = Ax;
	A.y = Ay;
	B.x = Bx;
	B.y = By;
	P.x = Px;
	P.y = Py;
	
	h = collisionFace(A, B, P);
	
	return h;
}

float transformeCoordonnees(float val)
{
    float reslt;
    reslt=val+540;
    return reslt;
}

float calculeAbscisse(float t)
{
    float a=150;
    float x;
    x=a*(float)cos((double)t)-80; //JLP : 80
    return x;
}


float calculeOrdonnee(float t)
{
    float b=50;
    float y;
    y=b*(float)sin((double)t);
    return y;
}

float collisionFace(coord A, coord B, coord P){
	coord D, T;
	float h;
	
	D.x = B.x - A.x;
	D.y = B.y - A.y;
	
	T.x = P.x - A.x;
	T.y = P.y - A.y;
	
	h = (D.x * T.y) - (D.y * T.x);
	
	return h;
}

coord courbeParametre(int i, int n){
	coord courbe;
	float xt2, yt2, t2;
	
	t2 = (PI / n) * (i+1);
	
	xt2 = calculeAbscisse(t2);
	
	yt2 = calculeOrdonnee(t2);
	
	courbe.x = transformeCoordonnees(xt2);
	courbe.y = transformeCoordonnees(yt2);

	return courbe;
}

coord getIntersectionPoint2(coord A, coord B, coord C, coord D)
{

	coord I ;

	I.x=(((A.y-B.y)/(A.x-B.x))*A.x-A.y-((C.y-D.y)/(C.x-D.x))*C.x+C.y) / (((A.y-B.y)/(A.x-B.x))-((C.y-D.y)/(C.x-D.x))) ;
	I.y=((C.y-D.y)/(C.x-D.x))*(I.x-C.x)+C.y ;

	return I ;

}

int isCollision(coord A, coord B, coord C, coord vitesse)
{
	coord inter ;
	coord D ;

        D.x = C.x + vitesse.x ;
        D.y = C.y + vitesse.y ;

	inter = getIntersectionPoint2(A,B,C,D) ;
	
	if (((B.x < inter.x && A.x > inter.x) || (A.x < inter.x && B.x > inter.x)) && ((A.y < inter.y && B.y > inter.y) || (B.y < inter.y && A.y > inter.y)) && ((D.x < inter.x && C.x > inter.x) || (C.x < inter.x && D.x > inter.x)) && ((C.y < inter.y && D.y > inter.y) || (D.y < inter.y && C.y > inter.y))) {
		//if (isDebug() == 1 ) { printf("Coupe A(%f,%f) B(%f,%f) C(%f,%f) D(%f,%f) inter(%f,%f)\n",A.x,A.y,B.x,B.y,C.x,C.y,D.x,D.y,inter.x,inter.y) ; }
		return 1;
	} else {
		return 0;
	}
}

void verifie_groupe(int score) {

	int points_gagnes ;
	int groupe_complet ;

	for (int j = 1 ; j<20 ; j++) {
		groupe_complet = 1 ;
		points_gagnes = 0 ;
		for (int i = 1 ; i < nb_obstacles;i++){
                	if (liste_obstacles[i].type == 3 && liste_obstacles[i].groupe == j) {
				if (liste_obstacles[i].etat == 1) {
					groupe_complet = 0 ;
				} else {
					points_gagnes += liste_obstacles[i].points ;
				}
			}
		}
		if (groupe_complet == 1) {
			score += points_gagnes ;
			for (int i = 1 ; i < nb_obstacles;i++){
                        	if (liste_obstacles[i].type == 3 && liste_obstacles[i].groupe == j) {
                                        	liste_obstacles[i].etat = liste_obstacles[i].etatIni ;
                        	}
                	}
		}
	}

}

void initialiseObstacle(){
	for (int i = 0;i < nb_obstacles; i++) {
		liste_obstacles[i].type = 0 ;
		liste_obstacles[i].etat = 0 ;
		liste_obstacles[i].etatIni = 0 ;
		liste_obstacles[i].points = 0 ;
		liste_obstacles[i].groupe = 0 ;
	}
}

void prepareObstacle(){
	int i = 0 ;

        // clapet
        liste_obstacles[i].type = 1 ;
        liste_obstacles[i].p1.x = 283 ;
        liste_obstacles[i].p1.y = 540 ;
        liste_obstacles[i].p2.x = 320 ;
        liste_obstacles[i].p2.y = 539 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 0.9 ;
        liste_obstacles[i].coef.y = -0.9 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=255;
        liste_obstacles[i].c.B=255;
        liste_obstacles[i].etat=0;
        liste_obstacles[i].etatIni=0;
	liste_obstacles[i].points=0 ;
	liste_obstacles[i].groupe=0 ;

        i++ ;
	// flipper bas gauche leve haut
        liste_obstacles[i].type = 1 ;
        liste_obstacles[i].p1.x = 292 ;
        liste_obstacles[i].p1.y = 58 ;
        liste_obstacles[i].p2.x = 352 ;
        liste_obstacles[i].p2.y = 66 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 1.5 ;
        liste_obstacles[i].coef.y = -1.5 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=150;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=0;
        liste_obstacles[i].etatIni=0;
	liste_obstacles[i].points=0 ;
        liste_obstacles[i].groupe=0 ;

        i++ ;
        // flipper bas gauche leve median
        liste_obstacles[i].type = 1 ;
        liste_obstacles[i].p1.x = 292 ;
        liste_obstacles[i].p1.y = 58 ;
        liste_obstacles[i].p2.x = 352 ;
        liste_obstacles[i].p2.y = 52 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 1.5 ;
        liste_obstacles[i].coef.y = -1.5 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=150;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=0;
        liste_obstacles[i].etatIni=0;
	liste_obstacles[i].points=0 ;
        liste_obstacles[i].groupe=0 ;

        i++ ;
        // flipper bas droite leve haut
        liste_obstacles[i].type = 1 ;
        liste_obstacles[i].p1.x = 390 ;
        liste_obstacles[i].p1.y = 66 ;
        liste_obstacles[i].p2.x = 454 ;
        liste_obstacles[i].p2.y = 59 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 1.5 ;
        liste_obstacles[i].coef.y = -1.5 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=200;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=0;
        liste_obstacles[i].etatIni=0;
	liste_obstacles[i].points=0 ;
        liste_obstacles[i].groupe=0 ;

        i++ ;
        // flipper bas droite leve median
        liste_obstacles[i].type = 1 ;
        liste_obstacles[i].p1.x = 390 ;
        liste_obstacles[i].p1.y = 52 ;
        liste_obstacles[i].p2.x = 454 ;
        liste_obstacles[i].p2.y = 59 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 1.5 ;
        liste_obstacles[i].coef.y = -1.5 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=200;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=0;
        liste_obstacles[i].etatIni=0;
	liste_obstacles[i].points=0 ;
        liste_obstacles[i].groupe=0 ;

        i++ ;
	// Ligne bas gauche oblique
	liste_obstacles[i].type = 1 ;
	liste_obstacles[i].p1.x = 209 ;
        liste_obstacles[i].p1.y = 97 ;
        liste_obstacles[i].p2.x = 291 ;
        liste_obstacles[i].p2.y = 58 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
	liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 1 ;
        liste_obstacles[i].coef.y = -1 ;
	liste_obstacles[i].c.R=255;
	liste_obstacles[i].c.G=255;
	liste_obstacles[i].c.B=0;
	liste_obstacles[i].etat=1;
	liste_obstacles[i].etatIni=1;
	liste_obstacles[i].points=0 ;
        liste_obstacles[i].groupe=0 ;

	i++ ;
        // Ligne bas gauche verticale
        liste_obstacles[i].type = 1 ;
        liste_obstacles[i].p1.x = 207 ;
        liste_obstacles[i].p1.y = 142 ;
        liste_obstacles[i].p2.x = 208 ;
        liste_obstacles[i].p2.y = 97 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = -1 ;
        liste_obstacles[i].coef.y = 1 ;
	liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=255;
        liste_obstacles[i].c.B=100;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
	liste_obstacles[i].points=0 ;
        liste_obstacles[i].groupe=0 ;

        i++ ;
        // Ligne bas gauche haut
        liste_obstacles[i].type = 1 ;
        liste_obstacles[i].p1.x = 198 ;
        liste_obstacles[i].p1.y = 143 ;
        liste_obstacles[i].p2.x = 207 ;
        liste_obstacles[i].p2.y = 141 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 1 ;
        liste_obstacles[i].coef.y = -0.5 ;
	liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=255;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
	liste_obstacles[i].points=0 ;
        liste_obstacles[i].groupe=0 ;

        i++ ;
        // Ligne bas droite oblique
        liste_obstacles[i].type = 1 ;
        liste_obstacles[i].p1.x = 455 ;
        liste_obstacles[i].p1.y = 59 ;
        liste_obstacles[i].p2.x = 532 ;
        liste_obstacles[i].p2.y = 99 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 1 ;
        liste_obstacles[i].coef.y = -1 ;
	liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=0;
        liste_obstacles[i].c.B=255;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
	liste_obstacles[i].points=0 ;
        liste_obstacles[i].groupe=0 ;

        i++ ;
        // Ligne bas droite verticale
        liste_obstacles[i].type = 1 ;
        liste_obstacles[i].p1.x = 535 ;
        liste_obstacles[i].p1.y = 144 ;
        liste_obstacles[i].p2.x = 533 ;
        liste_obstacles[i].p2.y = 99 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = -1 ;
        liste_obstacles[i].coef.y = 1 ;
	liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=0;
        liste_obstacles[i].c.B=100;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
	liste_obstacles[i].points=0 ;
        liste_obstacles[i].groupe=0 ;

	i++ ;
        // Ligne bas droite haut
        liste_obstacles[i].type = 1 ;
        liste_obstacles[i].p1.x = 535 ; 
        liste_obstacles[i].p1.y = 145 ;
        liste_obstacles[i].p2.x = 544 ;
        liste_obstacles[i].p2.y = 147 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 1 ;
        liste_obstacles[i].coef.y = -0.5 ;
	liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=0;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
	liste_obstacles[i].points=0 ;
        liste_obstacles[i].groupe=0 ;

        i++ ;
        // flipper bas gauche
        liste_obstacles[i].type = 1 ;
        liste_obstacles[i].p1.x = 290 ; // 292
        liste_obstacles[i].p1.y = 60 ;  // 58
        liste_obstacles[i].p2.x = 352 ;
        liste_obstacles[i].p2.y = 36 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 1 ;
        liste_obstacles[i].coef.y = -0.9 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=150;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
	liste_obstacles[i].points=0 ;
        liste_obstacles[i].groupe=0 ;

        i++ ;
        // flipper bas droite
        liste_obstacles[i].type = 1 ;
        liste_obstacles[i].p1.x = 390 ;
        liste_obstacles[i].p1.y = 38 ;
        liste_obstacles[i].p2.x = 454 ;
        liste_obstacles[i].p2.y = 59 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 1 ;
        liste_obstacles[i].coef.y = -0.9 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=200;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
	liste_obstacles[i].points=0 ;
        liste_obstacles[i].groupe=0 ;

        i++ ;
        // cercle haut 
        liste_obstacles[i].type = 2 ;
        liste_obstacles[i].p1.x = 294 ;
        liste_obstacles[i].p1.y = 437 ;
	liste_obstacles[i].rayon = 20 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 1 ;
        liste_obstacles[i].coef.y = -1 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=200;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
	liste_obstacles[i].points=50 ;
        liste_obstacles[i].groupe=0 ;

        i++ ;
        // cercle haut 2
        liste_obstacles[i].type = 2 ;
        liste_obstacles[i].p1.x = 282 ;
        liste_obstacles[i].p1.y = 359 ;
        liste_obstacles[i].rayon = 20 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 1 ;
        liste_obstacles[i].coef.y = -1 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=200;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
	liste_obstacles[i].points=75 ;
        liste_obstacles[i].groupe=0 ;

	i++ ;
        // cercle centre haut
        liste_obstacles[i].type = 2 ;
        liste_obstacles[i].p1.x = 398 ;
        liste_obstacles[i].p1.y = 359 ;
        liste_obstacles[i].rayon = 20 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 1.2 ;
        liste_obstacles[i].coef.y = -1.2 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=200;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
	liste_obstacles[i].points=150 ;
        liste_obstacles[i].groupe=0 ;

        i++ ;
        // cercle centre bas
        liste_obstacles[i].type = 2 ;
        liste_obstacles[i].p1.x = 396 ;
        liste_obstacles[i].p1.y = 437 ;
        liste_obstacles[i].rayon = 20 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 1.2 ;
        liste_obstacles[i].coef.y = -1.2 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=200;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
        liste_obstacles[i].points=150 ;
        liste_obstacles[i].groupe=0 ;

        i++ ;
        // cercle centre droite haut
        liste_obstacles[i].type = 2 ;
        liste_obstacles[i].p1.x = 493 ;
        liste_obstacles[i].p1.y = 466 ;
        liste_obstacles[i].rayon = 20 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 1.2 ;
        liste_obstacles[i].coef.y = -1.2 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=200;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
        liste_obstacles[i].points=200 ;
        liste_obstacles[i].groupe=0 ;


	i++ ;
        // diagonale bas gauche
        liste_obstacles[i].type = 1 ;
        liste_obstacles[i].p1.x = 164 ;
        liste_obstacles[i].p1.y = 82 ;
        liste_obstacles[i].p2.x = 326 ;
        liste_obstacles[i].p2.y = 5 ;
        liste_obstacles[i].acceleration.x = 5.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 0.7 ;
        liste_obstacles[i].coef.y = -0.7 ;
        liste_obstacles[i].c.R=200;
        liste_obstacles[i].c.G=200;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
	liste_obstacles[i].points=0 ;
        liste_obstacles[i].groupe=0 ;

	i++ ;
        // diagonale bas droite
        liste_obstacles[i].type = 1 ;
        liste_obstacles[i].p1.x = 575 ;
        liste_obstacles[i].p1.y = 82 ;
        liste_obstacles[i].p2.x = 408 ;
        liste_obstacles[i].p2.y = 5 ;
        liste_obstacles[i].acceleration.x = -5.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 0.7 ;
        liste_obstacles[i].coef.y = -0.7 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=200;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
	liste_obstacles[i].points=0 ;
        liste_obstacles[i].groupe=0 ;

	i++ ;
        // bordure gauche
        liste_obstacles[i].type = 1 ;
        liste_obstacles[i].p1.x = 163 ;
        liste_obstacles[i].p1.y = 539 ;
        liste_obstacles[i].p2.x = 164 ;
        liste_obstacles[i].p2.y = 83 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = -0.9 ;
        liste_obstacles[i].coef.y = 0.9 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=200;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
	liste_obstacles[i].points=0 ;
        liste_obstacles[i].groupe=0 ;

        i++ ;
        // bordure droite
        liste_obstacles[i].type = 1 ;
        liste_obstacles[i].p1.x = 576 ;
        liste_obstacles[i].p1.y = 539 ;
        liste_obstacles[i].p2.x = 575 ;
        liste_obstacles[i].p2.y = 83 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = -0.9 ;
        liste_obstacles[i].coef.y = 0.9 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=200;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
	liste_obstacles[i].points=0 ;
        liste_obstacles[i].groupe=0 ;

        i++ ;
        // bordure haute gauche
        liste_obstacles[i].type = 1 ;
        liste_obstacles[i].p1.x = 163 ;
        liste_obstacles[i].p1.y = 540 ;
        liste_obstacles[i].p2.x = 283 ;
        liste_obstacles[i].p2.y = 539 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 0.9 ;
        liste_obstacles[i].coef.y = -0.9 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=200;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
	liste_obstacles[i].points=0 ;
        liste_obstacles[i].groupe=0 ;

        i++ ;
        // bordure haute droite
        liste_obstacles[i].type = 1 ;
        liste_obstacles[i].p1.x = 320 ;
        liste_obstacles[i].p1.y = 540 ;
        liste_obstacles[i].p2.x = 576 ;
        liste_obstacles[i].p2.y = 539 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 0.9 ;
        liste_obstacles[i].coef.y = -0.9 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=200;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
	liste_obstacles[i].points=0 ;
        liste_obstacles[i].groupe=0 ;

        i++ ;
	// flip 1
        liste_obstacles[i].type = 3 ;
        liste_obstacles[i].p1.x = 175 ;
        liste_obstacles[i].p1.y = 204 ;
        liste_obstacles[i].p2.x = 21 ;
        liste_obstacles[i].p2.y = 17 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 1.2 ;
        liste_obstacles[i].coef.y = -1.2 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=200;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
        liste_obstacles[i].points=200 ;
        liste_obstacles[i].groupe=1 ;

        i++ ;
        // flip 2
        liste_obstacles[i].type = 3 ;
        liste_obstacles[i].p1.x = 200 ;
        liste_obstacles[i].p1.y = 224 ;
        liste_obstacles[i].p2.x = 21 ;
        liste_obstacles[i].p2.y = 17 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 1.2 ;
        liste_obstacles[i].coef.y = -1.2 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=200;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
        liste_obstacles[i].points=200 ;
        liste_obstacles[i].groupe=1 ;

        i++ ;
        // flip 3
        liste_obstacles[i].type = 3 ;
        liste_obstacles[i].p1.x = 225 ;
        liste_obstacles[i].p1.y = 244 ;
        liste_obstacles[i].p2.x = 21 ;
        liste_obstacles[i].p2.y = 17 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 1.2 ;
        liste_obstacles[i].coef.y = -1.2 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=200;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
        liste_obstacles[i].points=200 ;
        liste_obstacles[i].groupe=1 ;

        i++ ;
        // flip 4
        liste_obstacles[i].type = 3 ;
        liste_obstacles[i].p1.x = 250 ;
        liste_obstacles[i].p1.y = 264 ;
        liste_obstacles[i].p2.x = 21 ;
        liste_obstacles[i].p2.y = 17 ;
        liste_obstacles[i].acceleration.x = 0.0 ;
        liste_obstacles[i].acceleration.y = 0.0 ;
        liste_obstacles[i].coef.x = 1.2 ;
        liste_obstacles[i].coef.y = -1.2 ;
        liste_obstacles[i].c.R=255;
        liste_obstacles[i].c.G=200;
        liste_obstacles[i].c.B=150;
        liste_obstacles[i].etat=1;
        liste_obstacles[i].etatIni=1;
        liste_obstacles[i].points=200 ;
        liste_obstacles[i].groupe=1 ;


}

