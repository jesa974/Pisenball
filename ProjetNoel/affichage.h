#define LCH 100
#define DIM 20
#define NB_ATTITUDE 4
#define NB_RESSORT 3
#define RAIDEUR 0.495
#define NB_PT_TRAJ 100


//définie la structure de la balle
typedef struct balle
{
	int x,y,t;
	float vx,vy;
	float P;
}balle;

void cercle(float centreX, float centreY, float rayon);


typedef DonneesImageRGB *image[NB_ATTITUDE];

typedef DonneesImageRGB *imgFlip[NB_ATTITUDE];

typedef DonneesImageRGB *imgRes[NB_RESSORT];

int affichage_Restart(int compte) ;

void initFond(image fonds); // crée le lien de l'image de fond

void initMenu(image menus); //crée le lien de l'image du menu

void initialiseRessort(imgRes ressort); // créé le lien de l'image du ressort

void initialiseFlipper(imgFlip flipper); // créé le lien de l'image du flipper

void dessineObstacles(coord pos0,coord v0);

void afficheRessort(imgRes ressort, int N, int B); // affiche le sprite du ressort

void afficheFlipper(imgFlip flipper, int L, int S, int Space); // affiche le sprite du flipper

void affichageScore(int val_score, int high_score) ;  // affiche le score

void afficheFond(image fonds); // affiche l'image de fond

void afficheMenu(image menus); // affiche l'image du menu

coord courbeParametre(int i, int n); // calcule la courbe en demi-ovale


void afficheBalle(coord pos0, int N, int B); // affiche le deplacement de la balle

void initFlip(image flip) ;
void afficheFlip(image flip);

