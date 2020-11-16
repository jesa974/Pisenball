#define PI 3.14

typedef struct coord
{
    float x,y;
}coord;

typedef struct RGBColor
{
    int R,G,B ;
}RGBColor ;

typedef struct obstacle
{
    int type;  // 1 : Ligne    // 2 : Circle     // 3 : Flip
    coord p1 ; // si c'est un cercle alors c'est le centre   // si c'est un flip c'est coordonnee depart
    coord p2 ;						     // si c'est un flip c'est la taille
    float rayon ;
    coord acceleration ;
    coord coef ;
    RGBColor c ;
    int etat ;  // 0 : inactif   // 1 : actif
    int etatIni ;
    int points ;
    int groupe ;   // Si c'est un groupe alors > 0
} obstacle ;

void prepareObstacle() ;

coord acceleration(void);

coord vitesse(coord a , coord v0);

coord position(coord v0, coord pos0);

coord gereRessort(int B, int N); // calcul de la vitesse donné à la balle par le ressort

coord collision(coord pos0, coord v0, int L, int S, int Space);

float collisionFace(coord A, coord B, coord P);

float coordonneeVecteur(float Ax, float Ay, float Bx, float By, float Px, float Py);

float transformeCoordonnees(float val);

float calculeAbscisse(float t);

float calculeOrdonnee(float t);

coord getIntersectionPoint2(coord A, coord B, coord C, coord D) ;

void verifie_groupe(int score) ;

void initialiseObstacle() ;


