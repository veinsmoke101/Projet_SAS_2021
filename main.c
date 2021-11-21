#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


int nombre_compte = 0;
int currentSize = 5;

typedef struct compte_bancaire{
    char * CIN;
    char * Nom;
    char * Prenom;
    double Montant;
}compte_bancaire;


void addCompteBancaire(compte_bancaire* comptes);
void printCompteBancaire(compte_bancaire *);
void printCompteBancaireDesc(compte_bancaire *);
void printCompteBancaireSup(compte_bancaire *, double );
void printCompteBancaireSupDesc(compte_bancaire *, double );
void introduireCompte(compte_bancaire *);
void appSystem(compte_bancaire * ,char );
char * removeNewLine(char * );
int searchCIN(compte_bancaire *,char *);
void printMenu();
void insertionSort(compte_bancaire * comptes,int length);




int main()
{
    char a;
    compte_bancaire * comptes = (compte_bancaire * )malloc(currentSize*sizeof(compte_bancaire));
    if(comptes == NULL){
        printf("Allocation Error in malloc()");
        exit(EXIT_SUCCESS);
    }
    //addCompteBancaire(comptes);
    //printCompteBancaireDesc(comptes);


    do{
        system("cls");
        printMenu();
        printf("Merci de choisir un operation a effectue : \n");
        scanf("%c",&a);
        getchar();
        if(a == 'q')
            break;
        appSystem(comptes,a);
    }while(1);

    //system("cls");
    //introduireCompte(comptes);


    free(comptes);
    return 0;
}




 void addCompteBancaire(compte_bancaire* comptes){


    nombre_compte++;
    if(currentSize == nombre_compte){
        currentSize+=5;
        comptes = (compte_bancaire *)realloc(comptes,sizeof(compte_bancaire)*currentSize);
        if(comptes == NULL){
        printf("Allocation Error in realloc() %d",nombre_compte);
        exit(EXIT_SUCCESS);
        }
    }

    size_t len = 0;

    comptes[nombre_compte-1].CIN = NULL;
    comptes[nombre_compte-1].Nom = NULL;
    comptes[nombre_compte-1].Prenom = NULL;


    printf("Entrer le CIN de compte %d : \n",nombre_compte);
    getline(&comptes[nombre_compte-1].CIN,&len,stdin);
    comptes[nombre_compte-1].CIN = removeNewLine(comptes[nombre_compte-1].CIN);

    printf("Entrer le Nom de compte %d : \n",nombre_compte);
    getline(&comptes[nombre_compte-1].Nom,&len,stdin);
    comptes[nombre_compte-1].Nom = removeNewLine(comptes[nombre_compte-1].Nom);

    printf("Entrer le Prenom de compte %d : \n",nombre_compte);
    getline(&comptes[nombre_compte-1].Prenom,&len,stdin);
    comptes[nombre_compte-1].Prenom = removeNewLine(comptes[nombre_compte-1].Prenom);

    do{
        printf("Entrer le Montant de compte %d : \n",nombre_compte);
        scanf(" %lf",&comptes[nombre_compte-1].Montant);
    }while(comptes[nombre_compte-1].Montant < 0.0);
    getchar();
    system("cls");
    printCompteBancaire(comptes);


}


void printCompteBancaire(compte_bancaire * comptes){

    printf("|  %-20s|  %-25s|  %-25s|  %-20s|\n", "CIN", "Nom", "Prenom", "Montant");
    for(int i = 0; i < nombre_compte; i++)
        printf("|  %-20s|  %-25s|  %-25s|  %-20.2f|\n",comptes[i].CIN,comptes[i].Nom,comptes[i].Prenom,comptes[i].Montant);
}

void printCompteBancaireDesc(compte_bancaire * comptes){

    printf("|  %-20s|  %-25s|  %-25s|  %-20s|\n", "CIN", "Nom", "Prenom", "Montant");
    for(int i = nombre_compte-1; i >= 0; i--)
        printf("|  %-20s|  %-25s|  %-25s|  %-20.2f|\n",comptes[i].CIN,comptes[i].Nom,comptes[i].Prenom,comptes[i].Montant);
}

void printCompteBancaireSup(compte_bancaire * comptes,double montant){

    printf("|  %-20s|  %-25s|  %-25s|  %-20s|\n", "CIN", "Nom", "Prenom", "Montant");
    for(int i = 0; i < nombre_compte; i++){
        if(comptes[i].Montant < montant)
            continue;
        printf("|  %-20s|  %-25s|  %-25s|  %-20.2f|\n",comptes[i].CIN,comptes[i].Nom,comptes[i].Prenom,comptes[i].Montant);
    }

}

void printCompteBancaireSupDesc(compte_bancaire * comptes, double montant){

    printf("|  %-20s|  %-25s|  %-25s|  %-20s|\n", "CIN", "Nom", "Prenom", "Montant");
    for(int i = nombre_compte-1; i >= 0; i--){
        if(comptes[i].Montant < montant)
            break;
        printf("|  %-20s|  %-25s|  %-25s|  %-20.2f|\n",comptes[i].CIN,comptes[i].Nom,comptes[i].Prenom,comptes[i].Montant);
    }
}




void appSystem(compte_bancaire * comptes,char chosen){

    char  CIN[10], option;
    int nombreCB, id;
    double montant;

    switch(chosen){
        case  '1':
            addCompteBancaire(comptes);
            insertionSort(comptes,nombre_compte);
            break;
        case  '2':
            do{
            printf("Entrer le nombre des comptes a introduire : ");
            scanf("%d",&nombreCB);
            getchar();
            }while(nombreCB <= 0);
            for(int i = 0; i < nombreCB; i++)
                addCompteBancaire(comptes);
            insertionSort(comptes,nombre_compte);
            break;

        case  '3':

            printf("Entrer le CIN : ");
            do{
                scanf("%s",CIN);
                if(searchCIN(comptes,CIN) != -1)
                    break;
                printf("Compte n'existe .. Reessayer SVP !!\n");
            }while(1);
            id = searchCIN(comptes,CIN);
            do{
                printf("Entrer le montant de retrait : ");
                scanf("%lf",&montant);
                getchar();
            }while(montant <= 0.0);
            comptes[id].Montant -= montant;
            break;

        case  '4':

            printf("Entrer le CIN : ");
            do{
                scanf("%s",CIN);
                if(searchCIN(comptes,CIN) != -1)
                    break;
                printf("Compte n'existe .. Reessayer SVP !!\n");
            }while(1);
            id = searchCIN(comptes,CIN);
            do{
                printf("Entrer le montant de depot : ");
                scanf("%lf",&montant);
            }while(montant <= 0.0);
            comptes[id].Montant += montant;
            break;
        case  '5':
            printCompteBancaire(comptes);
            printf("Cliquer un button pour revenir au menu principale : ");
            getchar();
            scanf("%c",&option);
            if(option == 'q')
                exit(EXIT_SUCCESS);
            break;
        case  '6':
            printCompteBancaireDesc(comptes);
            printf("Cliquer un button pour revenir au menu principale ou bien 'q' pour quitter : ");
            getchar();
            scanf("%c",&option);
            if(option == 'q')
                exit(EXIT_SUCCESS);
            break;
        case  '7':
            do{
                printf("Entrer le montant : ");
                scanf("%lf",&montant);
            }while(montant <= 0.0);
            getchar();
            printCompteBancaireSup(comptes,montant);
            printf("Cliquer un button pour revenir au menu principale ou bien 'q' pour quitter : ");
            getchar();
            scanf("%c",&option);
            if(option == 'q')
                exit(EXIT_SUCCESS);
            break;
        /*case  8:
        case  9:
            if(searchCIN(comptes,"hh") != -1)
                printf("Trouvee\n");
            else
                printf("NonTrouvee\n");
            break;
        case  10:
        case  00:*/
    }
}


void printMenu(){

    printf("================== MENU ==================\n\n");
    printf("\t1- Introduire un compte\n");
    printf("\t2- Introduire plusieurs compte\n");
    printf("\t3- Retrait\n");
    printf("\t4- Depot\n");
    printf("\t5- Affichage par ordre Ascendant\n");
    printf("\t6- Affichage par ordre Descendant\n");
    printf("\t7- Affichage par ordre Ascendant (superieur a un montant)\n");
    printf("\t8- Affichage par ordre Descendant (superieur a un montant)\n");
    printf("\t9- Recherche par CIN\n");
    printf("\t10- Fidelisation\n");
    printf("\tq- Quitter l'application\n");


}

//int choisirMenu(){
//
//}

//void introduireCompte(compte_bancaire * comptes){
//
//    char CIN, * Nom = NULL, * Prenom = NULL;
//    double Montant;
//    size_t len = 0;
//
//    printf("Entrer le CIN : \n");
//    getline(&CIN,&len,stdin);
//    printf("Entrer le Nom : \n");
//    getline(&Nom,&len,stdin);
//    printf("Entrer le Prenom : \n");
//    getline(&Prenom,&len,stdin);
//
//    do{
//        printf("Entrer le Montant : \n");
//        scanf(" %lf",&Montant);
//    }while(Montant < 0.0);
//    printf("%s%s%s",CIN,Nom,Prenom);
//    addCompteBancaire(comptes,CIN,Nom,Prenom,Montant);
//
//}

char * removeNewLine(char * C){

        if(C[strlen(C)-1] == '\n')
            C[strlen(C)-1] = '\0';
        return C;
}

int searchCIN(compte_bancaire * comptes,char * CIN){
    for(int i = 0; i < nombre_compte; i++){
        if(!strcmp(comptes[i].CIN,CIN))
            return i;
    }
    return -1;
}


void insertionSort(compte_bancaire * comptes,int length){

    int i, j, ins_key;

    for (i = 1; i < length; i++) {
    ins_key = comptes[i].Montant; // select element to insert
    j = i - 1;

    // find right insertion place
    while (j >= 0 && comptes[j].Montant > ins_key)
    {
        comptes[j + 1].Montant = comptes[j].Montant;
        j = j - 1;
    }
    comptes[j + 1].Montant = ins_key; // insert
    }
}
