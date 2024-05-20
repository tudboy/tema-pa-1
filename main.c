#include "header.h"

int main(int argc, char *argv[]){
    //printf("task: %s\n", argv[1]);
    //printf("intrare: %s\n", argv[2]);
    //printf("Iesire: %s\n", argv[3]);

    int numarEchipe;
    char spatiu;
    Node* head;
    head = NULL;

    Echipa* team=(Echipa*)malloc(sizeof(Echipa));

    FILE *in, *out;

    in=fopen(argv[2],"rt");

    if(in==NULL)
    {
        printf("fisierul nu poate fi accesat");
        exit(1);
    }

    fscanf(in, "%d", &numarEchipe);
    //printf("%d \n", numarEchipe);



    for(int i=0;i<numarEchipe;i++)
    {
        team =(Echipa*)malloc(sizeof(Echipa));
        fscanf(in, "%d", &team->numarJucatori);
        //printf("%d ", team->numarJucatori);
        fscanf(in,"%c",&spatiu);

        team->numeEchipa=(char*)malloc(101);

        fgets(team->numeEchipa,100,in);
        if(team->numeEchipa[strlen(team->numeEchipa)-1]=='\n')
        {
            team->numeEchipa[strlen(team->numeEchipa)-1]=0;
        }
        //printf("%s\n", team->numeEchipa);

        team->jucatori=(Jucator*)malloc(team->numarJucatori*sizeof(Jucator));
        for(int j=0;j<team->numarJucatori;j++)
            {
            team->jucatori[j].firstName=(char*)malloc(101);
            team->jucatori[j].secondName=(char*)malloc(101);
            fscanf(in,"%s",team->jucatori[j].firstName);
            fscanf(in,"%s",team->jucatori[j].secondName);
            fscanf(in,"%d",&team->jucatori[j].points);
            //printf("%s %s %d \n",team->jucatori[j].firstName,team->jucatori[j].secondName,team->jucatori[j].points);
            }
        fscanf(in,"%c",&spatiu);
        //printf("\n");
        adaugaLaInceput(&head,team);
        
    }

    out=fopen(argv[3],"wt");
    if(out==NULL)
    {
        printf("fisierul nu poate fi accesat");
        exit(1);
    }

    while(head != NULL)
    {
        fprintf(out,"%s", head->echipe->numeEchipa);
        fprintf(out, "\n");
        head= head->urmatorul;

    }

    
    fclose(in);
    fclose(out);
    return 0;


}