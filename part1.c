#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include "table.h"
#include "part1.h"
#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"
#define BLEU "\033[38;5;153m"
#define pink "\033[38;5;225m"
#define gris "\033[38;5;250m"
#define green "\033[38;5;157m"
#define lavender "\033[38;5;147m"


// Machine abstraite

// procedure pour allouer une case mémoire
void allouer(struct famille1 **p) {
    *p = malloc(sizeof(struct famille1)) ; 
}

// procdure pour l'affectation des noms
void aff_nom(struct famille1 *pop ,char *nom) {
    strcpy(pop->nomfam,nom) ;
}

// procedure pour l'affectation des adresses
void aff_adresse(struct famille1 *head_dest , struct famille1 *head_source) {
    (*head_dest).prochaine = head_source ;
}

// fonction qui retourne le nom 
char* nom_fam(struct famille1*pop) {
    return (*pop).nomfam ;
}
// fonction qui retourne l'adresse de maillon prochain
struct famille1 *proc(struct famille1 *pop) {
    return (*pop).prochaine ;
}

// fonction pour liberer toutes les cases mémoires allouées par une liste
void liberer(struct famille1 *p) {
    while (p != NULL) {
        struct famille1 *temp = p;
        p = p->prochaine;
        free(temp);
    }
}






/********************* Modules Demandés ************************/





// Fonction qui verifier si une famille existe dans pop non trié (utilisé dans le module de creation)
bool present_nonTrie(struct famille1 *pop, char *nom) {
    struct famille1 * parcour = pop;
    while (parcour != NULL) {
        if (strcasecmp(parcour->nomfam, nom) == 0) {    //Comparaison entre le nom de la famille1 et le nom cherche
            return true;     //si l'element cherche est trouve
        }
        parcour = proc(parcour);
    }
    return false ;
}

//Fonction qui permet de detecter si deux chaine sont dans l'ordre alphabetique (chaine1<chaine2 => vrai)(utilisé dans le module de creation)
bool ordre_alpha(char chaine1[],char chaine2[],int pos){
    char ch1=toupper(chaine1[pos]),ch2=toupper(chaine2[pos]);  // Mettre les lettres a comparer en majuscule pour eviter les faux resultats dus a la case
    if (ch1 == '\0' && ch2 == '\0') return true; //Si on a atteint la fin des deux chaines -char nul- (les chaines sont identique donc l'ordre n'importe pas)
    if (ch1 == '\0') return true;  //on a atteint la fin de la 1ere chaine (elle est d'ordre alphabetique inferieur)
    if (ch2 == '\0') return false; //on a atteint la fin de la 2eme chaine (la 1ere est d'ordre alphabetique superieur)

    if(ch1<ch2) return true; //comparaison caractère par caractère selon le code ASCII
    else if (ch1>ch2) return false;
        else return ordre_alpha(chaine1,chaine2,pos+1); // recursivite pour avancer dans la chaine
}

//Fonction qui permet de creer une liste de N noms aleatoires
struct famille1 *creer_pop(int N) {
    if (N > taille) return NULL; // si le N est supperieur que la taille de notre base des donnes on retourne NIL
    int index = 0 ;    // initialiser index
    struct famille1 *temp , *current , *head ; // head : pointe sur la tête de la liste , current : pointe sur le nouveau mallion creer , temp : pointe sur le mallion precedent
    temp = current = head = NULL ;  // initialisation
    int i = 1 ; // i : un cpt pour creer N mallion
    while ((i <= N)){
        allouer(&current) ; // on alloue une case memoire suffisante pour le maillon
        if (current == NULL) { // verifier qu'une case memoire est alloue sinon on sort
            fprintf(stderr, "Erreur : allocation memoire echouee.\n"); // un message qui indique qu'il ya un erreur
            exit(EXIT_FAILURE);  // Quitter proprement le programme
        }
        index =  rand() % taille ; // on choisi un nombre aleatroire inferieure à taille consederer comme un indice dans le tableau noms
        if(!present_nonTrie(head,names[index])){ // verifier si l'element correspandant à l'indice pas n'etait pas dans la liste (element unique)
            aff_nom(current,names[index]) ; // on affecte la valeur correspandante à l'inice choise à le mallion (nomfam reçoit la valeur)
            aff_adresse(current,NULL) ;     // on initialise le champ proc à Nil
            if (i == 1) {   // verifier si le mallion crée represente la tête
                head = current ; // affecte l'adress de ce mallion à la tête
                temp = current ; // sauvegarder l'adress de ce mallion pour le chener avec le prochain mallionn
            }else{
                aff_adresse(temp,current) ; // chainer le nouveau mallion avec le precedent
                temp = current ;  // sauvegarder l'adress de ce mallion pour le chener avec le prochain mallionn
            }
            i ++ ; // incrementer i
        }
    }
    return head ; // retourner la tête
}

//Fonction qui calcule le nombre des famille1s (longueur de la liste)
int nbfamille1(struct famille1* pop){
    int cpt=0;          //Compteur des elements
    struct famille1* temp=pop;
    while (temp){   //Parcour de la liste et incrementation du compteur
        cpt++;
        temp=proc(temp);
    }
    return cpt;
}


//Module qui permet de trier une liste de nom dans l'ordre alphabetique
void trier_pop(struct famille1* pop){
    struct famille1* parcour;
    char* temp;
    bool trie=true; //detecte les permutation, si il reste a faux la liste est donc ordonnee
    while (trie){
        trie=false;
        parcour = pop;  //le pointeur utilise pour parcourir la liste
        while (proc(parcour)!=NULL){ //on s'arrete un fois le dernier element atteint
            if (! ordre_alpha(nom_fam(parcour),nom_fam(proc(parcour)),0)){
                temp = malloc(strlen(nom_fam(parcour))+1) ;//allouer un espace memoire pour copier la chaine
                strcpy(temp,nom_fam(parcour));
                aff_nom(parcour,nom_fam(proc(parcour)));//permutter les noms
                aff_nom(proc(parcour),temp);
                trie=true;
                free(temp) ;//liberer la case memoire allouee
            }
            parcour=proc(parcour); //avancer dans la liste
        }
    }
}

//Fonction qui retourne l'adresse d'une famille1 si elle existe (null sinon)
struct famille1* present(struct famille1 * pop, char *nom) {
    struct famille1 *parcour = pop;

    while (parcour != NULL && ordre_alpha(parcour->nomfam,nom,0)) { //Puisque pop est triee, il suffit d'arreter la recherche une fois l'ordre alphabetique du nom depasse
        if (strcasecmp(nom_fam(parcour), nom) == 0) {    //Comparaison entre le nom de la famille1 et le nom cherche
            return parcour;     //si l'element cherche est trouve
        }
        parcour = proc(parcour);
    }
    return NULL ;
}

// Un module utilise pour inserer une famille1 dans la liste si elle n'existe pas
void inser(struct famille1 **pop , char *nom) {
    if(present(*pop,nom) == NULL) { // verifier si la famille1 n'existe pas
        struct famille1 * parcour = *pop , *prec = NULL , *nouvelle_cell = NULL;
        allouer(&nouvelle_cell) ;

        if (nouvelle_cell == NULL) { // verifier qu'une case memoire est alloue sinon on sort
            fprintf(stderr, "Erreur : allocation memoire echouee.\n"); // un message qui indique qu'il ya un erreur
            exit(EXIT_FAILURE);  // Quitter proprement le programme
        }
        char *name_copy = malloc(strlen(nom)+1) ; // allouer une case memoire suffisante pour sauvegarder le nom
        if (name_copy == NULL) {
            fprintf(stderr, "Erreur : allocation memoire echouee.\n");
            exit(EXIT_FAILURE);
        }
        strcpy(name_copy,nom) ; // sauvegarder le nom
        name_copy[0] = (name_copy[0] >= 'a' && name_copy[0] <= 'z') ? name_copy[0] - 32 : name_copy[0];  // ecrire le nom sur le format Xxxxxx
        aff_nom(nouvelle_cell,name_copy) ; // affecter le nom à le nouveau mallion
        if(!*pop) {
            aff_adresse(nouvelle_cell,NULL);
            *pop=nouvelle_cell;

            return;
        }
        if(ordre_alpha(nom_fam(nouvelle_cell),nom_fam(*pop),0)) { // verifier si on va inserer le nom dans la première position
        aff_adresse(nouvelle_cell,*pop) ; // chiner la nouvelle tête avec le deuxieme element
        *pop = nouvelle_cell ;  // mis à jour pop qui pointe sur la tête
        return ; // on sort
        }else {
        prec = parcour ; // prec reçoit la valeur precedente de parcour
        parcour = proc(parcour) ; // on avance dans la liste utilisant parcour
        while(parcour) {
            if(ordre_alpha(name_copy,nom_fam(parcour),0)) { // si on trouve la position valide pour le nouveu nom
                aff_adresse(prec,nouvelle_cell) ; // chiner le mallion precedent avec le nouveau mallion
                aff_adresse(nouvelle_cell,parcour) ; // chiner le nouveau mallion avec le prochain mallion
                return ; // on sort
            }else {
                prec = parcour ; // on avance dans la liste sauvegardant l'element precedent
                parcour = proc(parcour) ;
            }
        }
        // inserer le nouveau maillon dans la fin de liste
        aff_adresse(prec,nouvelle_cell) ;
        aff_adresse(nouvelle_cell,NULL) ;
        }
    }
    else {
        return ;
    }

}

//Module qui permet de supprimer une famille1 de la liste si elle existe
void supp(struct famille1** pop, char* nom){
    struct famille1* sup,*parcour=*pop;
    sup=present(*pop,nom);  //l'element à supprimer (si il existe)
    if (sup){   //l'element existe
        if(sup==*pop)  //l'element à supprimer se trouve à la 1ere position
            *pop=proc(*pop);    //Avancer la tete
        else{
                while(proc(parcour)!=sup) parcour=proc(parcour);    //acceder au precedent de sup (pourr le chaianage)
                aff_adresse(parcour,proc(sup));
            }
            free(sup);  //liberer le maillon sup
    }
}





/******************* Modules supplementaires *********************/





//Fonction qui affiche une population
void afficher_pop1(struct famille1 *pop ){
    ch20 nom;
    struct famille1 * parcour;

    if(pop) printf(CYAN"   POP \n     |    \n     V  \n"RESET);
    while(pop){
        parcour=pop;
        for(int i=0; i<5&&parcour;i++){
            strcpy(nom,nom_fam(parcour));
            for(int j=0;j<strlen(nom)+9;j++) printf(BLEU"_");
            printf("     ");
            parcour=proc(parcour);
        }
        parcour=pop;
        printf("\n");
        for(int i=0;i<5&&parcour;i++){
            strcpy(nom,nom_fam(parcour));
            if (nom[0] != '\0') nom[0] = toupper(nom[0]);//forcer la premiere lettre a devenir majuscule pour garder le format Xxxxx
            for (int j = 1; nom[j] != '\0'; j++) {
                nom[j] = tolower(nom[j]); // Convertit les autres lettres en minuscules
            }
            if(proc(parcour)) printf(BLEU"|"RESET"  %s  "BLEU"|"CYAN" *"BLEU"-|--->"RESET,nom);
            else printf(BLEU"|"RESET"  %s  "BLEU"|"CYAN" / "BLEU"|"RESET,nom);
            parcour=proc(parcour);
        }
        printf("\n"BLEU);
        parcour=pop;
        for(int i=0; i<5&&parcour;i++){
            strcpy(nom,nom_fam(parcour));
            for(int j=0;j<strlen(nom)+9;j++) printf("-");
            printf("     ");
            parcour=proc(parcour);
        }
        printf("\n"RESET);
        if(parcour) pop=parcour;
        else pop=NULL;
    }
}

//Fonction qui permet d'inserer n familles manuellement a la fois dans une population triee
void inser_n_fam_m(struct famille1 **fam, int n){
    ch20 str;
    struct famille1 *temp=*fam;
    for(int i=0;i<n;i++){
        printf("\nVeuillez saisir le nom de la famille %d a inserer: ",i+1);
        scanf(" %[^\n]", str);
        if (present(temp,str)) {
            printf(RED"         Cette famille existe deja dans la population! veuillez resaisir le nom.\n"RESET);
            i--;
        }
        else
            inser(&temp,str);
    }
    *fam=temp;
}

//Fonction qui permet d'inserer n famille automatiquement (aleatoirement) dans une population triee
void inser_n_fam_a(struct famille1 ** fam,int n){
    struct famille1 *pop2=NULL, *pop3=*fam ;
    int len=nbfamille1(*fam)+n,len2=nbfamille1(pop3);
    while(len2!=len){ 
        n=len-len2; //haka normaalement mrigl
        pop2=creer_pop(n); // n - ka
        pop3=fusion_pops(pop3,pop2);
        len2=nbfamille1(pop3) ;
    }
    *fam = pop3 ;
}

//Fonction qui permet de creer une population manuellement
struct famille1* creer_pop_manuel(int n){
    struct famille1 *fam = NULL, *temp = NULL, *current = NULL;
    ch20 nom;

    for (int i = 0; i < n; i++) {
        printf("\nEntrez le nom de la famille %d : ", i + 1);
        scanf("%s", nom);
        if (present_nonTrie(fam,nom)) {
            printf(RED"         Cette famille existe deja dans la population! veuillez resaisir le nom.\n"RESET);
            i--;
        }
        else {
            allouer(&current);         // Allocation d'un maillon
            aff_nom(current, nom);     //remplissage du maillon
            aff_adresse(current, NULL);
            if (!fam) {  //ou fam=NULL
                fam = current;  // Premier element de la liste
            } else {
                aff_adresse(temp, current); // Chainage du dernier maillon avec le nouveau
            }
            temp = current; // Mise à jour du dernier element
        }

    }
    return fam;
}

//Fonction qui permet de copier une liste (si on souhaite voir le resultat d'une modification sans modifier la liste original, utilise dans la fusion)
struct famille1* copier_liste(struct famille1 *original) {
    if (!original) return NULL;  // Si la liste d'origine est vide, retourner NULL
    struct famille1 *copie = NULL, *temp = NULL, *current = NULL;
    while (original) {
        allouer(&current);  // Allouer un nouveau maillon
        aff_nom(current, nom_fam(original)); // Copier le nom
        aff_adresse(current, NULL); // Initialiser l'adresse à NULL

        if (!copie) {
            copie = current;  // Premier element de la liste copiee
        } else
            aff_adresse(temp, current); //chainer les elements
        temp = current;
        original = proc(original);  // Passer à l'element suivant de l'original
    }
    return copie;
}

//Fonction qui permet de fusionner 2 populations
struct famille1* fusion_pops(struct famille1 *pop1,struct famille1 *pop2){
    if(!pop1)return pop2; //le resultat de la fusion est pop2
    if(!pop2)return pop1; //le resultat de la fusion est pop1
    struct famille1 *pop3=pop1; //liste resultante 
    ch20 nom;
    while(pop2){
        strcpy(nom,nom_fam(pop2)); //recuperation du nom de famille
        inser(&pop3,nom); // insertion du nom de famille
        pop2=proc(pop2); //avancement dans la liste
    }
    return pop3;
}

//Fonction qui indique si un nom du tableau existe dans la liste (son indice a dejà etait utilise)
bool existe(int *arr, int size ,int val) {
    for(int i = 0 ; i < size ; i++){ // parcourir le tableau
        if(arr[i]==val) { // verifer si la valeur est dans la tableau
            return true ;
        }
    }
    return false ; // l'element n'existe pas
}

//Fonction qui permet d'effacer les espaces avant et apres une chaine
char * eff_espace(char * word){
    while(word[0]==' ') word++; //supprimer les escpaces du debut
    int len=strlen(word)-1;
    while (len > 0 && word[len - 1] == ' ') {// supprimer les espaces de la fin
        word[len - 1] = '\0';  // Remplacer l'espace par '\0'
        len--;  // decrementer la longueur
    }
    return word;
}

//Fonction qui permet de creer une liste a partir d'un fichier avec '/' comme separateur
struct famille1* creer_fichier() {
    FILE *fichier = fopen("TP1.txt", "r");
    if (!fichier) {
        printf("Erreur d'ouverture du fichier\n");
        return NULL;
    }

    char ligne[256];//pour stocker une ligne
    struct famille1 *temp = NULL, *current = NULL, *pop = NULL;
    ch20 nom;
    while (fgets(ligne, sizeof(ligne), fichier)) { //recuperer une ligne
        ligne[strlen(ligne)-1] = '\0'; // Supprimer '\n' laisse par fgets
        
        char *temp1 = strtok(ligne, "/"); //recuperer un champs (un nom de famille)
        if (temp1) {
            strcpy(nom, eff_espace(temp1)); //supprimer les espaces avant et apres le nom
        }
        while (temp1) {//creer la famille
            if (!present_nonTrie(pop,nom)){
                allouer(&current); // Allocation du maillon
                aff_nom(current, nom); //remplissage du maillon
                aff_adresse(current, NULL);
                if (!temp) { //si c'est le premier maillon
                    pop = current; //definir la tete
                } else {
                    aff_adresse(temp, current); // Chainer le precedent avec le nouveau
                }
                temp = current;
            }
            temp1 = strtok(NULL, "/"); // Passer au nom suivant
            if (temp1) {
                strcpy(nom, eff_espace(temp1));
            }
        }
    }

    fclose(fichier);
    return pop;
}

//Module qui permet d'epxorter la population 
void export_pop(struct famille1 *pop){
    FILE *fichier=fopen("Rapport_pop1.txt","w"); //ouvrir le fichier en mode write
    if (fichier == NULL) { //si il y a une erreur dan l'ouverture du fichier
        printf("Erreur dans l'ouvertue du fichier.\n");
        return;
    }
    while (proc(pop)){
        fprintf(fichier," %s /",nom_fam(pop)); //ecrire les noms de familles dans le fichier avec '/' comme separateur
        pop=proc(pop);
    }
    fprintf(fichier," %s ",nom_fam(pop)); // ecrire le dernier nom sans separateur
    fclose(fichier); //fermer le fichier
}

// il faut initialiser srand(time(0)) dans le main


