#include "header.h"


void adaugaLaInceput(Node** head, Echipa* team)
{
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->echipe = team;
    newNode->urmatorul = *head;
    *head=newNode;
}

char is_power2(int n)
{
    return !(n&(n-1));
}

void elibereazaEchipe(Node* team)
{
    Node* echipaCurenta = team;
    while(echipaCurenta != NULL)
    {
        Node* urmator= echipaCurenta->urmatorul;
        for(int i=0;i<echipaCurenta->echipe->numarJucatori;i++)
        {
            free(echipaCurenta->echipe->jucatori[i].firstName);
            free(echipaCurenta->echipe->jucatori[i].secondName);
        }

        free(echipaCurenta->echipe->jucatori);
        free(echipaCurenta->echipe->numeEchipa);
        free(echipaCurenta->echipe);
        free(echipaCurenta);
        echipaCurenta=urmator;
    }
}