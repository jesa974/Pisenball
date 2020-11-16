#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "BmpLib.h"
#include "gereBouton.h"

int gereBoutonN(int N){ // gère la touche clavier N
    if(N > -1 && N < 2){
        N=N+1;
    }
    else if(N> 1){
        N=0;
	}
	printf("N = %d\n",N);
    return N;
}


int gereBoutonB(int B){ // gère la touche clavier B
        B = 1;
	printf("B = %d\n",B);
    return B;
}


int gereBoutonL(int L){ // gère la touche clavier L
    if(L==0){
        L=1;
    }
    else{
        L=0;
	}
	printf("L = %d\n",L);
    return L;
}


int gereBoutonS(int S){  // gère la touche clavier S
    if(S==0){
        S=1;
	}
    else{
        S=0;
	}
	printf("S = %d\n",S);
    return S;
}


int gereBoutonEspace(int Space){  // gère la touche clavier Espace
  //  if(Space==0){
        Space=1;
  //  }
  //  else{
  //      Space=0;
//	}
	printf("Space = %d\n",Space);
    return Space;
}
