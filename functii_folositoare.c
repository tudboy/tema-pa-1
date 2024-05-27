#include "header.h"

// functie adaugare in lista principala
void adaugaLaInceput(Node** head, Echipa* team)
{
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->echipe = team;
    newNode->urmatorul = *head;
    *head=newNode;
}

void adaugaLaInceputCastigatori8(NodeCastigatori** head,Echipa* team)
{
    NodeCastigatori* newNode=(NodeCastigatori*)malloc(sizeof(NodeCastigatori));
    newNode->numeEchipa = team->numeEchipa;
    newNode->PuncteEchipa = team->PuncteEchipa/team->numarJucatori;
    newNode->urmatorul = *head;
    *head=newNode;
}


// functie adaugare in lista pentru coada
void adaugaLaInceputListaCoada(Node_lista_coada** head, Echipa* echipa1, Echipa* echipa2)
{
    Node_lista_coada* newNode=(Node_lista_coada*)malloc(sizeof(Node_lista_coada));
    newNode->echipa1 = echipa1;
    newNode->echipa2 = echipa2;
    newNode->urmatorul = *head;
    *head=newNode;
}

// functie adaugare la finalul listei pentru coada
void adaugaLaFinalListaCoada(Node_lista_coada** head, Echipa* echipa1, Echipa* echipa2)
{
    Node_lista_coada *aux= *head;
    Node_lista_coada* newNode=(Node_lista_coada*)malloc(sizeof(Node_lista_coada));
    newNode->echipa1 = echipa1;
    newNode->echipa2 = echipa2;
    if(*head == NULL) adaugaLaInceputListaCoada(&*head,echipa1,echipa2);
    else
    {
        while(aux->urmatorul != NULL) aux = aux->urmatorul;
        aux->urmatorul = newNode;
        newNode->urmatorul = NULL;

    }
}

//functie verificare daca un numar este putere a lui 2 (se verifica pe biti) 
char is_power2(int n)
{
    //returneaza 1 sau 0: daca returneaza 1 nu este putere a lui 2, dar daca returneaza 0 este putere a lui 2
    return !(n&(n-1));
}

// functie de eliberare a memoriei pentru toate echipele
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

// functie eliberare memorie doar pentru o echipa
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

// functie gasire minimul punctelor unei echipe prin parcurgerea listei o singura data
int minim(Node* curent,float min)
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

// functie de stergere a unui element din lista
void stergere_element(Node *curent, float min)
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

//functia principala de stergere a unui element din lista
void eliminare_din_lista(Node** curent,float min)
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

//functie creare coada 
coada* creareCoada()
{
    coada *q;
    q=(coada*)malloc(sizeof(coada));
    if(q==NULL) return NULL;
    q->front=q->rear=NULL;
    return q;
}


//functie adaugare in coada
void AdaugareInCoada(coada*q, Node_lista_coada* team)
{
    Node_lista_coada* newNode = (Node_lista_coada*)malloc(sizeof(Node_lista_coada));
    newNode->echipa1 = team->echipa1;
    newNode->echipa2 = team->echipa2;
    newNode->urmatorul = NULL;
    if(q->rear==NULL) q->rear = newNode;
    else
    {
        (q->rear)->urmatorul = newNode;
        (q->rear)=newNode;
    }
    if(q->front == NULL) q->front = q->rear;
}

void BagaInStivaEchipa1(Stiva** top, Node_lista_coada* team )
{
    Stiva* newNode=(Stiva*)malloc(sizeof(Stiva));
    newNode->echipaStiva=team->echipa1;
    newNode->urmatorul = *top;
    *top = newNode;
}

void BagaInStivaEchipa2(Stiva** top, Node_lista_coada* team )
{
    Stiva* newNode=(Stiva*)malloc(sizeof(Stiva));
    newNode->echipaStiva=team->echipa2;
    newNode->urmatorul = *top;
    *top = newNode;
}

int isEmpty(coada* q)
{
    return(q->front == NULL);
}

void stergereCoada(coada *q)
{
    Node_lista_coada* aux;
    while(!isEmpty(q))
    {
        aux=q->front;
        q->front=q->front->urmatorul;
        free(aux);
    }
    free(q);
    
}

void AdaugareInCoadaStiva(coada*q, Echipa* team1, Echipa* team2)
{
    Node_lista_coada* newNode = (Node_lista_coada*)malloc(sizeof(Node_lista_coada));
    newNode->echipa1 = team1;
    newNode->echipa2 = team2;
    newNode->urmatorul = NULL;
    if(q->rear==NULL) q->rear = newNode;
    else
    {
        (q->rear)->urmatorul = newNode;
        (q->rear)=newNode;
    }
    if(q->front == NULL) q->front = q->rear;
}

void stergereStiva(Stiva **top)
{
    Stiva *temp;
    while((*top)!=NULL)
    {
        temp=*top;
        *top=(*top)->urmatorul;
        free(temp);
    }

}

int putere_doi(int i)
{
    int putere=1;
    for(int j=0; j<i;j++)
    {
        putere=putere*j;
    }
    return putere;
}

NodeBST* newNode(char* nume,float puncte)
{
    NodeBST* node = (NodeBST*)malloc(sizeof(NodeBST));
    node->numeEchipa = nume;
    node->PuncteEchipa=puncte;
    node->left = node->right = NULL;
    return node;
}

NodeBST* insert(NodeBST* node, char* nume,float puncte)
{
    if(node == NULL) return newNode (nume, puncte);
    if(puncte < node->PuncteEchipa)
    {
        node->left = insert(node->left, nume,puncte);  
    }
    if(puncte > node->PuncteEchipa)
    {
        node->right = insert(node->right, nume,puncte);  
    }
    if(puncte == node->PuncteEchipa)
    {
        if(strcmp(nume,node->numeEchipa)>0)
        {
            node->right = insert(node->right, nume,puncte);
        }
        else node->left = insert(node->left, nume,puncte);
    }
    return node;
}

void printare(NodeBST* root,FILE* out)
{
    if (root != NULL)
     {
        printare(root->right,out);
        fprintf(out,"%-32s  -  %.2f\n", root->numeEchipa,root->PuncteEchipa);
        printare(root->left,out);

    }
}



int max(int a, int b)
{
    return((a>b)?a:b);
}

int nodeHeight(NodeAVL* root)
{
    if(root == NULL) return -1;
    else return root->height;
}

NodeAVL *RightRotation(NodeAVL *z)
{
    NodeAVL *y = z->left;
    NodeAVL *T3 = y->right;

    y->right = z;
    z->left = T3;

    z->height = max(nodeHeight(z->left),nodeHeight(z->right))+1;
    y->height = max(nodeHeight(y->left),nodeHeight(y->right))+1;
    return y;
}

NodeAVL *LeftRotation(NodeAVL *z)
{
    NodeAVL *y = z->right;
    NodeAVL *T2 = y->left;

    y->left = z;
    z->right = T2;

    z->height = max(nodeHeight(z->left),nodeHeight(z->right))+1;
    y->height = max(nodeHeight(y->left),nodeHeight(y->right))+1;
    return y;
}

NodeAVL* insertAVL(NodeAVL* node, float puncte, char* nume)
{
    if(node == NULL)
    {
        node=(NodeAVL*)malloc(sizeof(NodeAVL));
        node->numeEchipa=nume;
        node->puncteEchipa=puncte;
        node->height=0;
        node->left=node->right=NULL;
        return node;
    }
    if(puncte > node->puncteEchipa)
    {
        node->right = insertAVL(node->right, puncte, nume);
    }
    else
    {
        node->left = insertAVL(node->left, puncte, nume);
    }

    node->height = 1 + max(nodeHeight(node->left),nodeHeight(node->right));

    int k =(nodeHeight(node->left) - nodeHeight(node->right));

    if(k > 1 && puncte <= node->left->puncteEchipa)
    {
        return RightRotation(node);
    }
    if(k < -1 && puncte >= node->right->puncteEchipa)
    {
        return LeftRotation(node);
    }
    return node;
}

void bagareInAVL(NodeBST* root,NodeAVL** rootAVL)
{
    if (root != NULL)
     {
        bagareInAVL(root->right,rootAVL);
        *rootAVL=insertAVL(*rootAVL,root->PuncteEchipa,root->numeEchipa);
        bagareInAVL(root->left,rootAVL);
        
    }
}

void printLevel(NodeAVL* root, int level,FILE* out)
{
    if(root == NULL) return;
    if(level == 1)
    {
        fprintf(out,"%s\n",root->numeEchipa);
    }
    else if(level>1)
    {
       
        printLevel(root->right, level-1,out);
        printLevel(root->left, level-1,out);
    }
}
void elibereazaEchipeListaCastigatori(NodeCastigatori* team)
{
    NodeCastigatori* echipaCurenta = team;
    while(echipaCurenta != NULL)
    {
        NodeCastigatori* urmator= echipaCurenta->urmatorul;
        free(echipaCurenta->numeEchipa);
        free(echipaCurenta);
        echipaCurenta=urmator;
    }
}

