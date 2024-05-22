#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Player
{
    char* firstName;
    char* secondName;
    int points;
};

typedef struct Player Jucator;

struct echipa{
    int numarJucatori;
    float PuncteEchipa;
    char* numeEchipa;
    struct Player* jucatori;
};
typedef struct echipa Echipa;

struct Elem{
    struct echipa* echipe;
    struct Elem* urmatorul;
};

typedef struct Elem Node;

struct elem{
    Echipa* echipa1;
    Echipa* echipa2;
    struct elem* urmatorul;
};

typedef struct elem Node_lista_coada;

struct stiva{
    Echipa* echipaStiva;
    struct stiva* urmatorul;
};

typedef struct stiva Stiva;

struct Q{
    Node_lista_coada *front, *rear;
};

typedef struct Q coada;

void adaugaLaInceput(Node**, Echipa*);
void elibereazaEchipe(Node*);
char is_power2(int);
void eliminare_din_lista(Node**,float);
int minim(Node*,float);
coada* creareCoada();
void AdaugareInCoada(coada*,Node_lista_coada*);
void adaugaLaInceputListaCoada(Node_lista_coada**,Echipa*,Echipa*);
void adaugaLaFinalListaCoada(Node_lista_coada**,Echipa*,Echipa*);
void BagaInStivaEchipa1(Stiva**,Node_lista_coada*);
void BagaInStivaEchipa2(Stiva**,Node_lista_coada*);
void stergereCoada(coada*);
void AdaugareInCoadaStiva(coada*,Echipa*,Echipa*);
void stergereStiva(Stiva **);
