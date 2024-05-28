#include "header.h"

int main(int argc, char *argv[]){

    int numarEchipe, taskVector[5];
    char spatiu;
    Node* head;
    head = NULL;
    Node_lista_coada* headListaCoada=NULL;
    Echipa* team;
    //deschiderea si verificarea fisierelor
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
    // numarul de echipe
    fscanf(in, "%d", &numarEchipe);
    // vectorul in care este argumentul ce arata ce task se va verifica
    for(int i=0;i<5;i++)
    {
        fscanf(task, "%d", &taskVector[i]);
    }
    //citirea din fisier si bagarea in lista principala a echipelor
    for(int i=0;i<numarEchipe;i++)
    {
        team =(Echipa*)malloc(sizeof(Echipa));

        team->PuncteEchipa=0;

        fscanf(in, "%d", &team->numarJucatori);
        fscanf(in,"%c",&spatiu);

        team->numeEchipa=(char*)malloc(101);
        fgets(team->numeEchipa,100,in);
        team->numeEchipa[strcspn(team->numeEchipa,"\r\n")]=0;
        if(team->numeEchipa[strlen(team->numeEchipa)-1]==' ')
            team->numeEchipa[strlen(team->numeEchipa)-1]='\0';

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
    // afisarea task ului 1 (toate echipele)
    if(taskVector[0]==1 && taskVector[1]== 0)
    {
        Node* copieHead=head;
        while(copieHead != NULL)
        {

            fprintf(out,"%s", copieHead->echipe->numeEchipa);
            fprintf(out, "\n");
            copieHead= copieHead->urmatorul;
        }
    }
    // !task 1

    // task 2
    //eliminarea din lista a echipelor pana se ajunge la o putere de 2
    while(! is_power2(numarEchipe))
    {
        float min=head->echipe->PuncteEchipa;
        min= minim(head, min);
        eliminare_din_lista(&head,min);
        numarEchipe--;
    }  
    // afisarea task ului 2 (echipele ramase)
    if(taskVector[1]==1 || taskVector[2]==1 || taskVector[3]== 1 || taskVector[4] == 1)
    {
        Node* copieHead=head;
        while(copieHead != NULL)
        {
            fprintf(out,"%s", copieHead->echipe->numeEchipa);
            fprintf(out, "\n");
            copieHead= copieHead->urmatorul;
        }
    }  
    // !task 2

    // !task 3
    //bagarea in lista asociata cozii
    Node* copieHead=head;
    Echipa *primaEchipa, *aDouaEchipa;
    for(;copieHead != NULL && copieHead->urmatorul != NULL;copieHead=copieHead->urmatorul->urmatorul)
    {
        primaEchipa = copieHead->echipe;
        aDouaEchipa = copieHead->urmatorul->echipe;
        adaugaLaFinalListaCoada(&headListaCoada,primaEchipa, aDouaEchipa);
    }
    //bagarea in coada
    coada* coadaMeciuri=creareCoada();
    Node_lista_coada* copieHeadListaCoada=headListaCoada;
    for(int i=0;i<numarEchipe/2;i++)
    {
        AdaugareInCoada(coadaMeciuri,copieHeadListaCoada);
        copieHeadListaCoada=copieHeadListaCoada->urmatorul;
        
    } 
    // afisare meciurilor si numarul rundei
    NodeCastigatori* headListaUltimii8 = NULL;
    int i=1;
    while(numarEchipe != 1)
    {
        if(taskVector[2]==1 || taskVector[3]== 1 || taskVector[4] == 1)
        {
            fprintf(out,"\n");
            fprintf(out,"--- ROUND NO:%d\n",i);
            Node_lista_coada* temp= coadaMeciuri->front;
            while(temp != NULL)
            {
                fprintf(out,"%-32s - ", temp->echipa1->numeEchipa);
                fprintf(out,"%32s", temp->echipa2->numeEchipa);
                temp=temp->urmatorul;
                fprintf(out,"\n");
            }
            fprintf(out,"\n");
        }
        // craerea a 2 stive cu castigaori si pierzatori si bagarea in ele
        Stiva *stivaCastigatoriTop=NULL, *stivaPierzatoriTop=NULL;
        Node_lista_coada* temp = coadaMeciuri->front;
        while(temp != NULL)
        {
            if(temp->echipa1->PuncteEchipa > temp->echipa2->PuncteEchipa)
            {
                BagaInStivaEchipa1(&stivaCastigatoriTop,temp);
                BagaInStivaEchipa2(&stivaPierzatoriTop,temp);
            }
            if(temp->echipa1->PuncteEchipa < temp->echipa2->PuncteEchipa)
            {
                BagaInStivaEchipa1(&stivaPierzatoriTop,temp);
                BagaInStivaEchipa2(&stivaCastigatoriTop,temp);
            }
            if(temp->echipa1->PuncteEchipa == temp->echipa2->PuncteEchipa)
            {
                BagaInStivaEchipa1(&stivaPierzatoriTop,temp);
                BagaInStivaEchipa2(&stivaCastigatoriTop,temp);
            }
            temp=temp->urmatorul;
        }
        // adaugarea unui punct fiecarui jucator dintr-o echipa castigatoare si adaugarea unui punct pentru echipa
        Stiva* stivaCastigatoriTop1=stivaCastigatoriTop;
        while(stivaCastigatoriTop1 != NULL)
        {
            for(int i=0;i<stivaCastigatoriTop1->echipaStiva->numarJucatori;i++)
            {
                stivaCastigatoriTop1->echipaStiva->jucatori[i].points= stivaCastigatoriTop1->echipaStiva->jucatori[i].points+1;
                stivaCastigatoriTop1->echipaStiva->PuncteEchipa=stivaCastigatoriTop1->echipaStiva->PuncteEchipa+1;
            }
            stivaCastigatoriTop1=stivaCastigatoriTop1->urmatorul;
        }
        //afisarea castigatorilor unei runde
        stivaCastigatoriTop1=stivaCastigatoriTop;
        if(taskVector[2]==1 || taskVector[3]== 1 || taskVector[4] == 1)
        {
            fprintf(out,"WINNERS OF ROUND NO:%d\n",i);
            while(stivaCastigatoriTop1 != NULL)
            {
                fprintf(out,"%-32s  -  %.2f\n",stivaCastigatoriTop1->echipaStiva->numeEchipa,stivaCastigatoriTop1->echipaStiva->PuncteEchipa/stivaCastigatoriTop1->echipaStiva->numarJucatori);
                stivaCastigatoriTop1=stivaCastigatoriTop1->urmatorul;
            }
        }
        //bagarea in lista a ultimilor 8
        if(numarEchipe==16)
        {
            stivaCastigatoriTop1=stivaCastigatoriTop;
            while(stivaCastigatoriTop1 != NULL)
            {
                adaugaLaInceputCastigatori8(&headListaUltimii8,stivaCastigatoriTop1->echipaStiva);
                stivaCastigatoriTop1=stivaCastigatoriTop1->urmatorul;
            }
        }

        coadaMeciuri->rear=NULL;
        coadaMeciuri->front=NULL;
        //bagarea din stiva de castigatori in coada
        stivaCastigatoriTop1=stivaCastigatoriTop;
        while(stivaCastigatoriTop1 != NULL && stivaCastigatoriTop1->urmatorul != NULL)
        {
            AdaugareInCoadaStiva(coadaMeciuri,stivaCastigatoriTop1->echipaStiva,stivaCastigatoriTop1->urmatorul->echipaStiva);
            stivaCastigatoriTop1=stivaCastigatoriTop1->urmatorul->urmatorul;
        }
        stergereStiva(&stivaCastigatoriTop);
        stergereStiva(&stivaPierzatoriTop);

        numarEchipe=numarEchipe/2;
        i++;
    }
    // !task 3

    // task 4
    NodeBST *root=NULL;
    //bagarea in BST 
    NodeCastigatori* CopieHeadListaUltimii8=headListaUltimii8;
    while(CopieHeadListaUltimii8 != NULL)
    {
        root=insert(root,CopieHeadListaUltimii8->numeEchipa,CopieHeadListaUltimii8->PuncteEchipa);
        CopieHeadListaUltimii8=CopieHeadListaUltimii8->urmatorul;
    }  
    //afisarea BST ului 
    if(taskVector[3]==1)
    {
        fprintf(out,"\n");
        fprintf(out,"TOP 8 TEAMS:\n");
        printare(root, out);
    }
    // !task 4

    // task 5
    //bagarea si afisarea nivelului 2 al AVL ului
    if(taskVector[4]==1 )
    {
        NodeBST *copieRoot=root;
        NodeAVL *rootAVL=NULL;
        bagareInAVL(copieRoot, &rootAVL);
        fprintf(out,"\n");
        fprintf(out,"THE LEVEL 2 TEAMS ARE: \n");
        printLevel(rootAVL,3,out);
    }
    // !task 5
    //inchiderea fisierelor si eliberarea de memorie
    fclose(in);
    fclose(out);
    elibereazaEchipe(head);
    elibereazaEchipeListaCastigatori(headListaUltimii8);
    stergereCoada(coadaMeciuri);
    return 0;
}

