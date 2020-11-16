#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GfxLib.h"
#include "BmpLib.h"
#include "ESLib.h"
#include "gereBouton.h"
#include "calcul.h"
#include "affichage.h"
#include "debug.h"

#define LargeurFenetre 800
#define HauteurFenetre 600

int mort ;
int score ;
int high_score = 0 ;

extern int nb_obstacles ;
extern obstacle liste_obstacles[] ;

void cercle(float centreX, float centreY, float rayon);

void gestionEvenement(EvenementGfx evenement);

int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);
	
	prepareFenetreGraphique("GfxLib", LargeurFenetre, HauteurFenetre);
	lanceBoucleEvenements();
	
	return 0;
}

void cercle(float centreX, float centreY, float rayon)
{
        const int Pas = 20;
        const double PasAngulaire = 2.*M_PI/Pas;
        int index;
        
        for (index = 0; index < Pas; ++index)
        {
                const double angle = 2.*M_PI*index/Pas;
                triangle(centreX, centreY,
                                 centreX+rayon*cos(angle), centreY+rayon*sin(angle),
                                 centreX+rayon*cos(angle+PasAngulaire), centreY+rayon*sin(angle+PasAngulaire));
        }
        
}


void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = false;
	static int B, L, S, Space, N, etat,i, n, p;
	static image menus, fonds, flip ;
	static imgRes ressort;
	static imgFlip flipper;
	static DonneesImageRGB *image = NULL;
	static coord a, v0, pos0;
	static int compte ;
	coord last_pos ;
	

	switch (evenement)
	{
		
		case Initialisation:
		
			B = L = S = Space = N = etat = 0;
			p = 1 ;
			i = 1;
			n = 11;
			
			v0.x = 0.00;
			v0.y = 0.00;
			pos0.x = 617;
			pos0.y = 48;

			mort = 0 ;
			//setDebugOff() ;
			score = 0 ;
		
			compte = 10 ;
	
			initMenu(menus);
			initFond(fonds);
			initFlip(flip) ;
			
			initialiseRessort(ressort);
			initialiseFlipper(flipper);

			initialiseObstacle() ;
			prepareObstacle() ;
		
			demandeTemporisation(10);
			break;
		
		
		case Temporisation:

			if(B != 0 && pos0.y < 540){
				
				a = acceleration();
			
				if (p == 1 && mort == 0) {		
					v0 = vitesse(a,v0);

					//if (isDebug() == 1 ) { printf("v0 vit : %f,%f <=> ",v0.x,v0.y) ; }
					v0 = collision(pos0,v0, L, S, Space);
					//if (isDebug() == 1 ) {
						//printf("v0 coll : %f,%f <=> ",v0.x,v0.y) ;
						//printf("Position dep : (%f,%f) _____ ",pos0.x,pos0.y) ;
					//}
					pos0 = position(pos0, v0);
					//if (isDebug() == 1 ) { printf("Position et vit arr : (%f,%f) -> (%f,%f)\n",pos0.x,pos0.y,v0.x,v0.y) ; }
					//if (isDebug() == 1) {
						//p = 0 ;
					//}

					if ( pos0.x == 617 && pos0.y < 50 && v0.y > -3.0 && v0.y < 3.0){
						pos0.x = 617 ;
						pos0.y = 48 ;
						v0.x = 0 ;
						v0.y = 0 ;
						B = 0 ;
						N = 0 ;
					}
				
					verifie_groupe(score) ;
				}
				
				if ( mort == 1 ) {
                                        pos0.x = 370 ;
                                        pos0.y = 10 ;
                                }

			}
			else if(B == 1 && pos0.y > 540 && pos0.x > 280 && pos0.x < 630){
				
				// v0.x = -7;
			
				a = acceleration();
				//v0 = vitesse(a,v0);
			
				if (p==1) {
	
					if(v0.y < 0.1 && v0.y > -0.1){
						printf("v0.y=0 !!!\n");
						v0.y = 0;
					}
					
					//if (isDebug() == 1 ) {
						//printf("v0 coll : %f,%f <=> ",v0.x,v0.y) ;
                                        	//printf("Position dep : (%f,%f) _____ ",pos0.x,pos0.y) ;				
					//}
					last_pos = pos0 ;
					pos0 = courbeParametre(i, n);
					if (pos0.x > last_pos.x) {
						pos0.x = last_pos.x - 4 ;
					}
					//if (isDebug() == 1 ) { printf("Position et vit arr : (%f,%f) -> (%f,%f)\n",pos0.x,pos0.y,v0.x,v0.y) ; }
					
					if(i < n){
						i++;
					}
					//if (isDebug() == 1) {
						//p = 0 ;
					//}
				}
				
				if ( pos0.y <= 540 || pos0.x <= 280 || pos0.x >= 630) {
					v0.y = -v0.y ;
					v0.x = -3 ; // JLP 3
					liste_obstacles[0].etat = 1 ;
				}

			}
			
			rafraichisFenetre();

			break;
			
			
		case Affichage:
		
			effaceFenetre (0, 0, 0);
			
			if(etat == 0){
				afficheMenu(menus);
				demandeTemporisation(30);
			}
			else if(etat == 1){
				//if (isDebug() == 0 ) {
				afficheFond(fonds);
				//}
				
				afficheRessort(ressort, N, B);
				afficheFlipper(flipper, L, S, Space);
				afficheFlip(flip) ;
				affichageScore(score,high_score) ;	
				afficheBalle(pos0, N, B);

				dessineObstacles(pos0,v0) ;

				//if (isDebug() == 1 ) {
					//ligne(pos0.x,pos0.y,pos0.x+v0.x,pos0.y+v0.y) ;  // Suivi direction de la balle
				//}

				if (mort == 1){
					compte = affichage_Restart(compte) ;
					demandeTemporisation(100);
				} else {
					demandeTemporisation(30);
				}

			}
			
			S = L = Space = 0 ;
			
			break;
			
			
		case Clavier:

			switch (caractereClavier())
			{
				
				case 'Q':
				case 'q':
					libereDonneesImageRGB(&image);
					
					termineBoucleEvenements();
					break;

				case 'F':
				case 'f':
					pleinEcran = !pleinEcran;
					if (pleinEcran)
						modePleinEcran();
					else
						redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					break;

				case 'L':
				case 'l':
					L = gereBoutonL(L);
					demandeTemporisation(50);
					break;

				case 'S':
				case 's':
					S = gereBoutonS(S);
					demandeTemporisation(50);
					break;
					
				case 'N':
				case 'n':
					if(etat == 1){
						N = gereBoutonN(N);
					}
					demandeTemporisation(50);
					break;
				
				case 'R':
				case 'r':
					if (mort == 1) {
						if (score > high_score) { high_score = score ; }
                                                
						B = L = S = Space = N = etat = 0;
                                                p = 1 ;
                                                i = 1;
                                                n = 11;
                                                
                                                v0.x = 0.00;
                                                v0.y = 0.00;
                                                pos0.x = 617;
                                                pos0.y = 48;
                                                
                                                mort = 0 ;
                                                score = 0 ;
                                                
                                                compte = 10 ;
                                                
                                                initialiseObstacle() ;
                                                prepareObstacle() ;
                                                
                                                demandeTemporisation(10);
                                        }
                                        break;
	
				case 'B':
				case 'b':
					if(etat == 1){
						B = gereBoutonB(B);
						v0 = gereRessort(B, N);
					}
					demandeTemporisation(50);
					break;
					
				case ' ':
					if(etat == 1){
						Space = gereBoutonEspace(Space);
					}
					demandeTemporisation(50);
					break;

				case 'd':
					//if (isDebug() == 1) {
						//setDebugOff() ;
						//p = 1;
					//} else {
						//setDebugOn() ;
						//p = 0;
					//}
					break ;

				case 'p':
					//if (isDebug() == 1) {
						//p = 1;
					//}
					break ;
			}
			break;
			
			
		case ClavierSpecial:
			break;

		case BoutonSouris:
		
			if (etatBoutonSouris() == GaucheAppuye)
			{
				
				printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
				
			}
			
			else if (etatBoutonSouris() == GaucheRelache)
			{
				
				//printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
				if(abscisseSouris() > 218 && ordonneeSouris() > 224 && abscisseSouris() < 563 && ordonneeSouris() < 316){
					etat = 1;
				}
				else{}
				
			}

			break;
		
		case Souris:
			break;
			
		
		case Inactivite:
			break;
			
		
		case Redimensionnement:			
			break;
	}
}

