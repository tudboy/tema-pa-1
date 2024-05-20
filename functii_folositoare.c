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

