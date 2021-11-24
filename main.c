#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


int nombre_compte = 0;
int currentSize = 5;


typedef struct compte_bancaire
{
    char * CIN;
    char * Nom;
    char * Prenom;
    double Montant;
} compte_bancaire;



void addCompteBancaire(compte_bancaire** comptes, char *);
void printCompteBancaire(compte_bancaire *);
void printCompteBancaireDesc(compte_bancaire *);
void printCompteBancaireSup(compte_bancaire *, double );
void printCompteBancaireSupDesc(compte_bancaire *, double );
void introduireCompte(compte_bancaire *);
void appSystem(compte_bancaire **,int );
char * removeNewLine(char * );
int searchCIN(compte_bancaire *,char *);
void printMenu();
void insertionSort(compte_bancaire **, int);
void affichage(compte_bancaire *, int);
void printAffichageMenu();
void operation(compte_bancaire *, int);
void printOperationMenu();



int main()
{
    int a;
    compte_bancaire * comptes = (compte_bancaire * )malloc(currentSize*sizeof(compte_bancaire));
    comptes->CIN = NULL;
    comptes->Nom = NULL;
    comptes->Prenom = NULL;
    if(comptes == NULL)
    {
        printf("Allocation Error in malloc()");
        exit(EXIT_SUCCESS);
    }

    do
    {
        system("cls");
        printMenu();
        printf("Merci de choisir un operation a effectue : \n");
        scanf("%d",&a);
        getchar();
        if(a == 0)
            break;
        appSystem(&comptes,a);
    }
    while(1);
    if(comptes->CIN != NULL )
    {
        free(comptes->CIN);
        free(comptes->Nom);
        free(comptes->Prenom);
    }

    free(comptes);

    return 0;
}




void addCompteBancaire(compte_bancaire** comptes, char * CIN)
{

    nombre_compte++;
    if(currentSize == nombre_compte)
    {
        currentSize+=5;
        *comptes = (compte_bancaire *)realloc(*comptes,sizeof(compte_bancaire)*currentSize);
        if(*comptes == NULL)
        {
            printf("Allocation Error in realloc() %d",nombre_compte);
            exit(EXIT_SUCCESS);
        }
    }

    size_t len = 0;


    (*comptes)[nombre_compte-1].CIN = NULL;
    (*comptes)[nombre_compte-1].Nom = NULL;
    (*comptes)[nombre_compte-1].Prenom = NULL;


    (*comptes)[nombre_compte-1].CIN = (char *)malloc(sizeof(char)*strlen(CIN));
    strcpy((*comptes)[nombre_compte-1].CIN,CIN);


    printf("Entrer le Nom de compte %d : \n",nombre_compte);
    getline(&(*comptes)[nombre_compte-1].Nom,&len,stdin);
    (*comptes)[nombre_compte-1].Nom = removeNewLine((*comptes)[nombre_compte-1].Nom);

    printf("Entrer le Prenom de compte %d : \n",nombre_compte);
    getline(&(*comptes)[nombre_compte-1].Prenom,&len,stdin);
    (*comptes)[nombre_compte-1].Prenom = removeNewLine((*comptes)[nombre_compte-1].Prenom);

    do
    {
        printf("Entrer le Montant de compte %d : \n",nombre_compte);
        scanf(" %lf",&(*comptes)[nombre_compte-1].Montant);
    }
    while((*comptes)[nombre_compte-1].Montant < 0.0);
    getchar();
    system("cls");
    printCompteBancaire(*comptes);
    system("pause");


}


void printCompteBancaire(compte_bancaire * comptes)
{

    printf("|  %-20s|  %-25s|  %-25s|  %-20s|\n", "CIN", "Nom", "Prenom", "Montant");
    for(int i = 0; i < nombre_compte; i++)
        printf("|  %-20s|  %-25s|  %-25s|  %-20.2f|\n",comptes[i].CIN,comptes[i].Nom,comptes[i].Prenom,comptes[i].Montant);
}

void printCompteBancaireDesc(compte_bancaire * comptes)
{

    printf("|  %-20s|  %-25s|  %-25s|  %-20s|\n", "CIN", "Nom", "Prenom", "Montant");
    for(int i = nombre_compte-1; i >= 0; i--)
        printf("|  %-20s|  %-25s|  %-25s|  %-20.2f|\n",comptes[i].CIN,comptes[i].Nom,comptes[i].Prenom,comptes[i].Montant);
}

void printCompteBancaireSup(compte_bancaire * comptes,double montant)
{

    printf("|  %-20s|  %-25s|  %-25s|  %-20s|\n", "CIN", "Nom", "Prenom", "Montant");
    for(int i = 0; i < nombre_compte; i++)
    {
        if(comptes[i].Montant < montant)
            continue;
        printf("|  %-20s|  %-25s|  %-25s|  %-20.2f|\n",comptes[i].CIN,comptes[i].Nom,comptes[i].Prenom,comptes[i].Montant);
    }

}

void printCompteBancaireSupDesc(compte_bancaire * comptes, double montant)
{

    printf("|  %-20s|  %-25s|  %-25s|  %-20s|\n", "CIN", "Nom", "Prenom", "Montant");
    for(int i = nombre_compte-1; i >= 0; i--)
    {
        if(comptes[i].Montant <= montant)
            break;
        printf("|  %-20s|  %-25s|  %-25s|  %-20.2f|\n",comptes[i].CIN,comptes[i].Nom,comptes[i].Prenom,comptes[i].Montant);
    }
}



void appSystem(compte_bancaire ** comptes,int chosen)
{

    char CIN[10];
    int  option;
    int nombreCB;
    int count =0;
    int index;


    switch(chosen)
    {
    case  1:
        printf("Entrer le CIN de compte %d : \n",nombre_compte+1);
        do
        {
            scanf("%s",CIN);
            getchar();
            if(searchCIN(*comptes,CIN) == -1 || strcmp(CIN,"0") == 0 )
                break;
            printf("Compte deja existe .. Reessayer SVP Ou entrer 0 pour retourner au menu Operation   !!\n");
        }
        while(1);
        if(strcmp(CIN,"0") == 0)
            break;
        addCompteBancaire(comptes,CIN);
        insertionSort(comptes,nombre_compte);
        break;
    case  2:
        do
        {
            printf("Entrer le nombre des comptes a introduire : ");
            scanf("%d",&nombreCB);
            getchar();
        }
        while(nombreCB <= 0);
        for(int i = 0; i < nombreCB; i++)
        {
            printf("Entrer le CIN de compte %d : \n",nombre_compte+1);
            do
            {
                scanf("%s",CIN);
                getchar();
                if(searchCIN(*comptes,CIN) == -1 || strcmp(CIN,"0") == 0 )
                    break;
                printf("Compte deja existe .. Reessayer SVP Ou entrer 0 pour retourner au menu Operation   !!\n");
            }
            while(1);
            if(strcmp(CIN,"0") == 0)
                break;
            addCompteBancaire(comptes,CIN);
        }
        insertionSort(comptes,nombre_compte);
        break;

    case  3:
        if(nombre_compte == 0)
        {

            printf("No Data !");
            system("pause");

        }
        else
        {
            do
            {
                system("cls");
                printOperationMenu();
                scanf("%d",&option);
                if(option == 0)
                    break;
                operation(*comptes,option);
            }
            while(1);
        }

        break;
    case  4:

        if(nombre_compte == 0)
        {
            printf("No Data !");
            system("pause");
        }
        else
        {
            do
            {
                system("cls");
                printAffichageMenu();
                scanf("%d",&option);
                if(option == 0)
                    break;
                affichage(*comptes,option);
            }
            while(1);
        }
        break;
    case  5:

        if(nombre_compte == 0)
        {
            printf("No Data !");
            system("pause");
        }
        else
        {
            if(nombre_compte <= 3)
            {
                for(int i = 0; i < nombre_compte; i++)
                    (*comptes)[i].Montant += (*comptes)[i].Montant*0.013;
            }
            else
            {
                for(int i = nombre_compte-1; i >= 0; i--)
                {
                    if((*comptes)[i].Montant > (*comptes)[i-1].Montant)
                        count++;
                    if(count == 3)
                    {
                        index = i;
                        printf("index : %d\n",index);
                        break;
                    }
                }
                for(int i = nombre_compte-1; i >= index; i--)
                {
                    (*comptes)[i].Montant += (*comptes)[i].Montant*0.013;
                }
            }
            printf("Fedilisation fait avec succees.\n");
            system("pause");
        }


        break;
    default:
        printf("Choix non valide !!!\n");
        system("pause");
        break;

    }
}


void printMenu()
{

    printf("================== MENU PRINCIPALE ==================\n\n");
    printf("\t1- Introduire un compte\n");
    printf("\t2- Introduire plusieurs compte\n");
    printf("\t3- Operation\n");
    printf("\t4- Affichage\n");
    printf("\t5- Fidelisation\n");
    printf("\t0- Quitter l'application\n\n");


}


char * removeNewLine(char * C)
{

    if(C[strlen(C)-1] == '\n')
        C[strlen(C)-1] = '\0';
    return C;
}

int searchCIN(compte_bancaire * comptes,char * CIN)
{
    for(int i = 0; i < nombre_compte; i++)
    {
        if(!strcmp(comptes[i].CIN,CIN))
            return i;
    }
    return -1;
}


void insertionSort(compte_bancaire ** comptes,int length)
{

    int i, j, ins_key;

    for (i = 1; i < length; i++)
    {
        ins_key = (*comptes)[i].Montant; // select element to insert
        j = i - 1;

        // find right insertion place
        while (j >= 0 && (*comptes)[j].Montant > ins_key)
        {
            (*comptes)[j + 1].Montant = (*comptes)[j].Montant;
            j = j - 1;
        }
        (*comptes)[j + 1].Montant = ins_key; // insert
    }
}

void printAffichageMenu()
{
    printf("================== AFFICHAGE ==================\n\n");

    printf("\t1- Affichage par ordre Ascendant\n");
    printf("\t2- Affichage par ordre Descendant\n");
    printf("\t3- Affichage par ordre Ascendant (superieur a un montant)\n");
    printf("\t4- Affichage par ordre Descendant (superieur a un montant)\n");
    printf("\t5- Recherche par CIN\n");
    printf("\t0- Revenir au menu principale\n");
    printf("Merci de choisir un type d'affichage : \n");

}

void affichage(compte_bancaire * comptes, int choix)
{

    char  CIN[10];
    int id;
    double montant;

    switch(choix)
    {

    case  1:
        printCompteBancaire(comptes);
        system("pause");
        break;
    case  2:
        printCompteBancaireDesc(comptes);
        system("pause");
        break;
    case  3:
        do
        {
            printf("Entrer le montant : ");
            scanf("%lf",&montant);
        }
        while(montant <= 0.0);
        printCompteBancaireSup(comptes,montant);
        system("pause");

        break;
    case  4:
        do
        {
            printf("Entrer le montant : ");
            scanf("%lf",&montant);
        }
        while(montant <= 0.0);
        getchar();
        printCompteBancaireSupDesc(comptes,montant);
        system("pause");

        break;
    case  5:
        printf("Entrer le CIN : ");
        do
        {
            scanf("%s",CIN);
            getchar();
            if(searchCIN(comptes,CIN) != -1 || strcmp(CIN,"0") == 0 )
                break;
            printf("Compte n'existe pas.. Reessayer SVP Ou entrer 0 pour retourner au menu Affichage   !!\n");
        }
        while(1);
        if(strcmp(CIN,"0") == 0)
            break;
        id = searchCIN(comptes,CIN);
        if(searchCIN(comptes,CIN) != -1)
        {
            printf("|  %-20s|  %-25s|  %-25s|  %-20s|\n", "CIN", "Nom", "Prenom", "Montant");
            printf("|  %-20s|  %-25s|  %-25s|  %-20.2f|\n",comptes[id].CIN,comptes[id].Nom,comptes[id].Prenom,comptes[id].Montant);
        }
        else
            printf("Compte n'existe pas !!!\n");
        system("pause");
        break;

    case 0:
        break;
    }
}

void printOperationMenu()
{
    printf("================== OPERATION ==================\n\n");

    printf("\t1- Retrait\n");
    printf("\t2- Depot\n");
    printf("\t0- Revenir au menu principale\n");
    printf("Merci de choisir un type d'affichage : \n");

}

void operation(compte_bancaire * comptes, int choix)
{

    char  CIN[10];
    int id;
    double montant;

    switch(choix)
    {

    case  1:

        printf("Entrer le CIN : ");
        do
        {
            scanf("%s",CIN);
            getchar();
            if(searchCIN(comptes,CIN) != -1 || strcmp(CIN,"0") == 0 )
                break;
            printf("Compte n'existe .. Reessayer SVP Ou entrer 0 pour retourner au menu Operation   !!\n");
        }
        while(1);
        if(strcmp(CIN,"0") == 0)
            break;
        id = searchCIN(comptes,CIN);
        do
        {
            printf("Entrer le montant de retrait Ou entrer 0 pour retourner au menu Operation: ");
            scanf("%lf",&montant);
            getchar();
            if(montant == 0)
                break;
        }
        while(montant <= 0.0 || montant > comptes[id].Montant);
        if(montant == 0)
        {
            break;
        }
        comptes[id].Montant -= montant;
        break;

    case  2:

        printf("Entrer le CIN : ");
        do
        {
            scanf("%s",CIN);
            getchar();
            if(searchCIN(comptes,CIN) != -1 || strcmp(CIN,"0") == 0 )
                break;
            printf("Compte n'existe .. Reessayer SVP Ou entrer 0 pour retourner au menu Operation   !!\n");
        }
        while(1);
        if(strcmp(CIN,"0") == 0)
            break;
        id = searchCIN(comptes,CIN);
        do
        {
            printf("Entrer le montant de depot : ");
            scanf("%lf",&montant);
            getchar();
        }
        while(montant <= 0.0);
        comptes[id].Montant += montant;
        break;


    case  0:
        break;
    }
}
