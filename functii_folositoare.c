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

void elibereazaEchipa(Node* team){
     Node* echipaCurenta = team;
        for(int i=0;i<echipaCurenta->echipe->numarJucatori;i++)
        {
            free(echipaCurenta->echipe->jucatori[i].firstName);
            free(echipaCurenta->echipe->jucatori[i].secondName);
        }
        free(echipaCurenta->echipe->numeEchipa);
        free(echipaCurenta);
}

int minim(Node* curent,int min)
{
    while(curent != NULL)
    {    
        if(curent->echipe->PuncteEchipa < min)
        {
            min=curent->echipe->PuncteEchipa;
        }
        curent= curent->urmatorul;
    }
    return min;
}

void stergere_element(Node *curent, int min)
{
    if(curent==NULL) return;

    Node *copieCurent = curent;
    Node* anterior = NULL;

    anterior = curent;
    copieCurent=copieCurent->urmatorul;
    while(copieCurent != NULL)
    {
        if(copieCurent->echipe->PuncteEchipa == min)
        {
            anterior->urmatorul = copieCurent->urmatorul;
            elibereazaEchipa(copieCurent);
            return;
        }
        anterior= copieCurent;
        copieCurent = copieCurent->urmatorul;

    }

}

void eliminare_din_lista(Node** curent,int min)
{

 if((*curent)->echipe->PuncteEchipa == min)
    {
        Node *copieCurent = *curent;
        (*curent) = (*curent)->urmatorul;
        elibereazaEchipa(copieCurent);
        return;
    }
    while((*curent) != NULL)
       {
            if((*curent)->echipe->PuncteEchipa == min);
            {
                stergere_element((*curent),min);
                return;
            }
            
            (*curent)= (*curent)->urmatorul;
       }
       
}