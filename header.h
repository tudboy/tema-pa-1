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
    int PuncteEchipa;
    char* numeEchipa;
    struct Player* jucatori;
};
typedef struct echipa Echipa;

struct Elem{
    struct echipa* echipe;
    struct Elem* urmatorul;
};

typedef struct Elem Node;

void adaugaLaInceput(Node**, Echipa*);
void elibereazaEchipe(Node*);
char is_power2(int);
void eliminare_din_lista(Node**,int);
int minim(Node*,int);