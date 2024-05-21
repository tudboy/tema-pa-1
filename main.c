#include "header.h"

int main(int argc, char *argv[]){

    int numarEchipe, taskVector[5];
    char spatiu;
    Node* head;
    head = NULL;

    Echipa* team;

    FILE *in, *out, *task;

    in=fopen(argv[2],"rt");

    if(in==NULL)
    {
        printf("fisierul nu poate fi accesat");
        exit(1);
    }

    out=fopen(argv[3],"wt");

    if(out==NULL)
    {
        printf("fisierul nu poate fi accesat");
        exit(1);
    }

    task=fopen(argv[1],"rt");

    if(task==NULL)
    {
        printf("fisierul nu poate fi accesat");
        exit(1);
    }

    // task1
    fscanf(in, "%d", &numarEchipe);
   
    for(int i=0;i<5;i++)
    {
        fscanf(task, "%d", &taskVector[i]);
    }
   
    for(int i=0;i<numarEchipe;i++)
    {
        team =(Echipa*)malloc(sizeof(Echipa));

        team->PuncteEchipa=0;

        fscanf(in, "%d", &team->numarJucatori);
        fscanf(in,"%c",&spatiu);

        team->numeEchipa=(char*)malloc(101);

        fgets(team->numeEchipa,100,in);

        if(team->numeEchipa[strlen(team->numeEchipa)-1]=='\n')
        {
            team->numeEchipa[strlen(team->numeEchipa)-1]=0;
        }

        team->jucatori=(Jucator*)malloc(team->numarJucatori*sizeof(Jucator));
        for(int j=0;j<team->numarJucatori;j++)
            {
            team->jucatori[j].firstName=(char*)malloc(101);
            team->jucatori[j].secondName=(char*)malloc(101);
            fscanf(in,"%s",team->jucatori[j].firstName);
            fscanf(in,"%s",team->jucatori[j].secondName);
            fscanf(in,"%d",&team->jucatori[j].points);
            team->PuncteEchipa=team->PuncteEchipa + team->jucatori[j].points;
            }
        fscanf(in,"%c",&spatiu);
        adaugaLaInceput(&head,team);
        
    }

    if(taskVector[0]==1 && taskVector[1]== 0)
    {
        Node* curent1=head;
        while(curent1 != NULL)
        {

            fprintf(out,"%s", curent1->echipe->numeEchipa);
            fprintf(out, "\n");
            curent1= curent1->urmatorul;
        }
    }


    // !task 1

    // task 2

    int CopieNumarEchipe = numarEchipe;
    while(! is_power2(CopieNumarEchipe))
    {
        int min=head->echipe->PuncteEchipa;
        min= minim(head, min);
        eliminare_din_lista(&head,min);
        CopieNumarEchipe--;
       
    }  
    if(taskVector[1]==1 && taskVector[2]== 0)
    {
        Node* curent2=head;
        while(curent2 != NULL)
        {
            fprintf(out,"%s", curent2->echipe->numeEchipa);
            fprintf(out, "\n");
            curent2= curent2->urmatorul;
        }
    }  
    // !task 2

    if(taskVector[2]==1 && taskVector[3]== 0)
    {
     
    }
    if(taskVector[3]==1 && taskVector[4]== 0)
    {
     
    }
    if(taskVector[4]==1 )
    {
    
    }
    fclose(in);
    fclose(out);
    elibereazaEchipe(head);

    return 0;


}

