#ifndef GFXLIB_H
#define GFXLIB_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <stdbool.h>
/*#define bool int
#define true (0==0)
#define false (!true)*/



/* Partie publique basique
   Cette partie est relative a toutes les informations utiles pour
   mettre en place simplement un environnement graphique portable */


typedef enum {Inactivite, Affichage, Clavier, ClavierSpecial, Souris, BoutonSouris, Initialisation, Redimensionnement, Temporisation}
	EvenementGfx;
typedef enum {GaucheAppuye, GaucheRelache, DroiteAppuye, DroiteRelache}
	EtatBoutonSouris;
typedef enum {SuiteDePoints, SuiteDeLignes, SuiteDeTriangles, SuiteDeRectangles, BandeDeTriangles, BandeDeRectangles}
	PrimitiveGfxLib;
typedef enum {ToucheF1 = 1, ToucheF2, ToucheF3, ToucheF4, ToucheF5, ToucheF6, ToucheF7, ToucheF8, ToucheF9, ToucheF10, ToucheF11, ToucheF12,
	ToucheFlecheHaut, ToucheFlecheBas, ToucheFlecheGauche, ToucheFlecheDroite, ToucheNonGeree} TouchesSpeciales;

typedef struct
	{
		int largeur; // Largeur des donnees
		int hauteur; // Hauteur des donnees
		float proportionX;
		float proportionY;
		int *donnees; // Les donnees de la texture
		unsigned int numero; // L'identifiant OpenGL de la texture
	} Texture2D;


// Pour initialiser la partie graphie de la bibliotheque
void initialiseGfx(int argc, char **argv);

/* Prepare une fenetre en specifiant son nom, sa largeur et sa hauteur.
   La fenetre presente un repere orthonorme classique (premier quadrant),
   de largeur pixels sur hauteur pixels */
void prepareFenetreGraphique(const char *nom, int largeur, int hauteur);
/* Lance la boucle de gestion des evenements */
void lanceBoucleEvenements(void);
/* Termine le programme proprement */
void termineBoucleEvenements(void);


/* Fonction de gestion des evenements graphiques, a definir par l'utilisateur */
extern void gestionEvenement(EvenementGfx evenement);



/* Demande la mise a jour du contenu graphique de la fenetre, en lancant un message d'affichage */
void rafraichisFenetre(void);

/* Efface la fenetre avec la couleur donnee
	Les composantes rouge, vert et bleu s'etendent de 0 a 255 inclus */
void effaceFenetre(int rouge, int vert, int bleu);

/* Selectionne la couleur courante de dessin
	Les composantes rouge, vert et bleu s'etendent de 0 a 255 inclus */
void couleurCourante(int rouge, int vert, int bleu);

/* Definit l'epaisseur de trait EN PIXELS DE LA FENETRE servant a afficher les points et les lignes */
void epaisseurDeTrait(float epaisseur);

/* Dessine un point de couleur courante aux coordonnees donnees */
void point(float x, float y);

/* Dessine une ligne de couleur courante aux coordonnees donnees */
void ligne(float xDepart, float yDepart, float xArrivee, float yArrivee);

// Dessine un triangle de couleur courante aux coordonnees donnees
void triangle(float xCoin1, float yCoin1, float xCoin2, float yCoin2, float xCoin3, float yCoin3);

/* Dessine un rectangle de couleur courante aux coordonnees donnees */
void rectangle(float xCoin1, float yCoin1, float xCoin2, float yCoin2);

/* Affiche une chaine de caracteres de taille donnee a la position specifiee */
void afficheChaine(const char *chaine, float taille, float x, float y);

/* Renvoie l'espace occupe par la chaine de caracteres de taille donnee */
float tailleChaine(const char *chaine, float taille);

/* Envoie un message Affichage apres la duree specifiee */
void demandeRedessinDans_ms(int millisecondes);

// Demarre l'envoi periodique de messages Temporisation
void demandeTemporisation(int millisecondesEntreAppels);


/* Lis une portion de la fenetre, couvrant largeur*hauteur et demarrant en (x, y)
Les donnees lues sont sauvees comme une succession de valeurs B, V, R de type
unsigned char */
void lisImage(int x, int y, int largeur, int hauteur, unsigned char *donnees);

// Ecris dans la fenetre une image BVR couvrant largeur*hauteur et demarrant en (x, y) */
void ecrisImage(int x, int y, int largeur, int hauteur, const unsigned char *donnees);

#ifndef _WIN32
// Ecris une image couvrant largeur*hauteur, demarrant en (x, y) et faite de
// pixels ARVB (stockes dans des int little endian) dans la fenetre */
void ecrisImageARVB(int x, int y, int largeur, int hauteur, const int *donneesARVB);

// Cree une texture reutilisable de largeur et hauteur donnees, faite de pixels ABVR little endian
Texture2D *creeTexture2D(int largeur, int hauteur, const int *pixelsABVR);
// Permet de modifier les pixels de la texture prealablement definie, en donnant un nouveau tableau de pixels ABVR little endian
void modifieTexture2D(const Texture2D *texture, const int *pixelsABVR);
// Affiche la texture passee en parametre aux coordonnees fournies
void rectangleSelonTexture(float x, float y, const Texture2D *texture);
// Libere les ressources associees a la gestion de la texture
void libereTexture(Texture2D **texture);
#endif


/* Renvoie l'abscisse de souris correspondant au dernier evenement Clavier, Souris ou BoutonSouris */
int abscisseSouris(void);
/* Renvoie l'ordonnee de souris correspondant au dernier evenement Clavier, Souris ou BoutonSouris */
int ordonneeSouris(void);
/* Renvoie le dernier etat de bouton souris traite par l'evenement BoutonSouris */
EtatBoutonSouris etatBoutonSouris(void);
/* Renvoie le dernier caractere clavier traite par l'evenement Clavier */
char caractereClavier(void);
/* Renvoie la derniere touche speciale du clavier traitee par l'evenement ClavierSpecial */
int toucheClavier(void);

/* Indique l'etat de la touche Shift lors du dernier evenement Clavier */
bool toucheShiftAppuyee(void);
/* Indique l'etat de la touche Ctrl lors du dernier evenement Clavier */
bool toucheCtrlAppuyee(void);
/* Indique l'etat de la touche Alt lors du dernier evenement Clavier */
bool toucheAltAppuyee(void);


// Renvoie la largeur actuelle de la fenetre
int largeurFenetre(void);
// Renvoie la hauteur actuelle de la fenetre
int hauteurFenetre(void);
// Demande au systeme de redimensionner la fenetre
void redimensionneFenetre(int largeur, int hauteur);
// Demande au systeme de passer la fenetre en plein ecran
void modePleinEcran(void);
// Affiche un message d'erreur de maniere standard pour l'OS
void messageDErreur(const char *message);


/* Active la gestion du deplacement passif de la souris */
void activeGestionDeplacementPassifSouris(void);



/* Partie publique elaboree
   Cette partie est relative a toutes les informations utiles pour
   personnaliser et mieux controler l'environnement graphique de base */


#endif
