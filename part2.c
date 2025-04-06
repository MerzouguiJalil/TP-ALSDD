#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include <unistd.h>
#include "table.h"
#include "part1.h"
#include "part2.h"
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
#define JAUNE "\033[1;33m"















//1.L'implementation des modules de la machine abstraite

//--------------------------------------------------------------------










// procedure qui alloue une case mémoir suffisante pour une famille 
void allouer_famille(pf *p) {
    *p = malloc(sizeof(struct famille)) ;
}

// procedure qui alloue une case mémoir suffisante pour une personne
void allouer_personne(pp *p) {
    *p = malloc(sizeof(struct personne)) ;
}

// procedure qui alloue une case mémoir suffisante pour une voiture
void allouer_voiture(pv *p) {
    *p = malloc(sizeof(struct voiture)) ;
} 

// procedure pour remplir un maillon personne
void aff_person(pp p,ch20 prenom , char sexe) {
    strcpy(p->prenom,prenom) ; // strcpy(a,b) : copy le contenue de a dans b
    p->sexe = sexe ;
}

// procedure pour remplir un maillon famille
void aff_famille(pf p , ch20 nom , pp parent , pp enfant , pv voiture) {
    strcpy(p->nom , nom );
    p->enfant  = enfant  ;
    p->parent  = parent  ;
    p->voiture = voiture ;
}

// procedure pour remplir un maillon voiture
void aff_voiture(pv p , ch20 marque , ch20 numero ) {
    strcpy(p->marque,marque) ;
    strcpy(p->nemero,numero) ;
}

// procedure pour affecter l'adress de prochain maillon personne
void aff_adress_person(pp p , pp suivant) {
    p->suivant = suivant ;
}

// procedure pour affecter l'adress de prochain maillon voiture
void aff_adresse_voiture(pv p , pv suivant ) {
    p->suivant = suivant ;
}

// procedure pour affecter l'adress de prochain maillon famille
void aff_adresse_famille(pf p , pf suivant){
    p->suivant = suivant ;
}

// fonction qui retourne l'adresse de prochain maillon personne
pp suivant_personne(pp p) {
    return p->suivant ;
}

// fonction qui retourne l'adresse de prochain maillon voiture
pv suivant_voiture(pv p) {
    return p->suivant ;
}

// fonction qui retourne l'adresse de prochain maillon famille
pf suivant_famille(pf p) {
    return p->suivant ;
}

// procedure qui retourne le contenue d'un maillon personne
void val_persone(pp p , ch20 * prenom , char * sexe) {
    strcpy(*prenom,p->prenom) ;
    * sexe = p->sexe ;
}

// procedure qui retourne le contenue d'un maillon voiture 
void val_voiture(pv p , ch20 * marque , ch20 *numero) {
    strcpy(*marque,p->marque) ;  
    strcpy(*numero,p->nemero) ;
}

// procedure qui retourne le contenue d'un maillon famille
void val_famille(pf p , ch20 * nom , pp * parent , pp * enfant , pv * voiture) {
    strcpy(*nom , p->nom) ;
    *parent = p->parent ;
    *enfant = p->enfant ;
    *voiture = p->voiture ;
}

// procedure qui liberer tout les cases memoires alloué par la liste personne
void liberer_person(pp head) {
    pp p = head ; // sauvegarder la tête
    pp temp = NULL ;
    while (p !=NULL) {
        temp = p ; // sauvegarder le maillon precedent
        p = suivant_personne(p) ; //avancer dans la liste 
        free(temp) ; // liberer le maillon
    }
}

// procedure qui liberer tout les cases memoires alloué par la liste voiture
void liberer_voiture(pv head) {
    pv p = head ; // sauvegarder la tête
    pv temp = NULL ;
    while (p !=NULL) {
        temp = p ;  // sauvegarder le maillon precedent
        p = suivant_voiture(p) ; // avancer dans la liste
        free(temp) ; // liberer le maillon
    }
}

// procedure qui liberer tout les cases memoires alloué par la liste famille
void liberer_famille(pf head) {
    pf p = head ;
    pf temp = NULL ;
    while (p != NULL) {
        liberer_person(p->enfant) ; // liberer enfant 
        liberer_person(p->parent) ; // liberer parent
        liberer_voiture(p->voiture) ; // liberer voiture
        temp = p ; // garder le maillon precedent 
        p = suivant_famille(p) ; // avancer dans la liste
        free(temp) ;  // liberer le maillon
    }
}

/******* Module de recherche  ******/
//Fonction qui retourne l'adresse d'une famille1 si elle existe (null sinon)
pf present_famille(pf pop, char *nom) {
    pf parcour = pop;

    while (parcour != NULL && ordre_alpha(parcour->nom,nom,0)) { 
        if (strcasecmp(parcour->nom, nom) == 0) {    //Comparaison entre le nom de la famille1 et le nom cherché
            return parcour;     //si l'element cherché est trouvé
        }  
        parcour = suivant_famille(parcour);        
    }
    return NULL ;
}  













//------------------------------------------------------------------------------------------------------------
// 2.Les modules demandés















//Fonction qui permet de calculer le nombres des familles sans parents dans pop
int nbfamillesansparent(pf pop){
    int cpt=0; //compteur des familles
    pf parcour=pop; //Pointeur de parcour

    while(parcour){ //ou (parcour!=NULL)
        if (parcour->parent==NULL) cpt++; //une famille sans parents trouvee
        parcour=suivant_famille(parcour); //Avancement dans la liste
    }
    return cpt;
}

//Fonction qui permet de calculer le nombre des enfants dans pop
int nbenfant(pf pop){
    int cpt=0;      //compteur des enfants
    pf parcour=pop;         //pointeur de parcour de pop
    pp enfant;       //pointeur de parcour des listes d'enfants

    while (parcour != NULL){
        enfant=parcour->enfant;

        while (enfant!= NULL){        //recuperation de la tete de la liste des enfants de la famille actuelle
            cpt++; //un enfant trouvé, on incremente le compteur
            enfant=suivant_personne(enfant); //avancement dans la liste d'enfants
        }
        parcour=suivant_famille(parcour); //avancement dans la liste de familles
    }
    return cpt;
}

//Fonction qui permet de calculer le nombre d'enfants dans une famille
int nbenfnomfam(pf pop, ch20 nomfam) {
    int cpt = 0;  // Compteur d'enfants
    pf parcour = pop;  // Pointeur pour parcourir la liste pop
    ch20 nom;  // Stockage du nom de famille
    pp enfant;  // Pointeur pour parcourir la liste d'enfants

    if (!pop) return 0; // Vérifier si la liste est vide
    parcour=present_famille(pop,nomfam); //recherche de la famille 
    if (!parcour) return 0; //si la famille n'existe pas
    else {
            enfant = parcour->enfant;  // Récupérer la tête de la liste d'enfants
            while (enfant) {
                cpt++; //incrementer chaque fois un enfant est trouvé
                enfant = suivant_personne(enfant); 
            }
        }
    return cpt;
}

//module qui permet d'inserer un nouveau ne d'une famille donnee
void naissanceTrie(pf pop, ch20 nomfam, ch20 prenom, char sexe) {
    if (!pop) return;
    pf parcour = present_famille(pop, nomfam); //localiser la famille
    if (!parcour) return; // si la famille n'existe pas
    pp nouveauNe = malloc(sizeof(struct personne));    // Creation du nouveau ne
    aff_person(nouveauNe, prenom, sexe); //remplissage du nouveau ne
    aff_adress_person(nouveauNe, NULL); // Dernier element donc NULL
    pp enfant = parcour->enfant;// Recuperer la liste des enfants
    if (!enfant) { // Si c'est le premier enfant de la famille
        parcour->enfant = nouveauNe; //changement de la tete
        return;
    }
    while (enfant->suivant) {// Parcourir la liste des enfants pour trouver la fin
        if (strncasecmp(enfant->prenom, prenom, strlen(enfant->prenom)) == 0) {
            free(nouveauNe); // si le prenom existe deja, on ne l'insere pas de nouveau
            return;
        }
        enfant = suivant_personne(enfant);
    }
    aff_adress_person(enfant,nouveauNe);// Ajouter le nouveau-ne a la fin de la liste
}

// Un module qui retourne l'addrees d'une famille possedant une voiture volé
pf RechFamVoit_1(pf head ,ch20 numero) {   
    pf p = head ; // sauvegarder head 
    pf nomfam_voiture_volee = NULL ; // initialisation
    while(p != NULL) { 
        pv temp = p->voiture ; //recuperation de la liste des voitures de la famille actuelle
        while (temp != NULL) { // parcourir la liste et rechercher le matricule
            if(strcmp(temp->nemero,numero)==0) { // si on a trouvé le matricule de  voiture  dans la liste
                return p ;
            }
            temp = suivant_voiture(temp) ;
        }
        
        p = suivant_famille(p) ;
    }
    return NULL ; // si on a pas trouvé le matricule de la voiture dans la liste
}


//Module qui permet de rechercher une famille ayant une voiture volée (après amélioration)
pnf RechFamVoit_2 (pnf pop, ch20 matricule){
    pnf parcour=pop; //pointeur de parcour de pop
    pv voit; //pointeur de parcours des champs de voitures volées
    while (parcour){ //fin de pop non atteinte (sur le plan algorithmique on ajoute un booléen pour sortir dès la voiture cherchée est trouvée
        voit=parcour->voitures_volees; //recuperation du champs voitures volées
        while(voit){
            if(strncmp(voit->nemero,matricule,strlen(matricule))==0) return parcour; //comparaison entre le matricule de la voiture cherchée et celui de la voiture déclarée volée; retourner le pointeur de la famille une fois l'égalité virifiée
            voit=suivant_voiture(voit); //avancement dans la liste des voitures volées
        }
        parcour=parcour->suivant;// Avancement dans pop
    }
    return NULL; //Si toute la liste est parcourue sans trouver la voiture cherchée
}














//----------------------------------------------------------------------------------------------------------
// 3.Des modules additionnels











//Fonction qui renvoie vrai si une chaine existe dans un tableau de chaine
bool existe_str(ch20 *arr, int size ,ch20 str) {
    for(int i = 0 ; i < size ; i++){ // parcourir le tableau
        if(strcasecmp(arr[i],str)==0) { // verifer si la valeur est dans la tableau
            return true ;
        }
    }
    return false ; // l'element n'existe pas
}

//Fonction qui renvoie vrai si le nom d'un enfant existe deja dans la famille (pour designer la possibilite d'insertion)
bool existe_str_liste(pp par,pp enf,ch20 str) {
    while(par){ // parcourir la liste des parents
        if(strcasecmp(par->prenom,str)==0) { // verifier si la valeur est dans la tableau
            return true ; // la valeur est truovée
        }
        par=suivant_personne(par);
    }
    while(enf){ //parcourir la liste d'enfants
        if(strcasecmp(enf->prenom,str)==0) { // verifer si la valeur est dans la tableau
            return true ;// la valeur est trouvée
        }
        enf=suivant_personne(enf);
    }
    return false ; // l'element n'existe pas
}

// Fonction qui verifier si une famille existe dans le pop (le pop n'est pas trié)  
bool present_famille_nonTrie(pf pop, char *nom) {
    pf parcour = pop;
    while (parcour != NULL) { 
        if (strcasecmp(parcour->nom, nom) == 0) {    //Comparaison entre le nom de la famille1 et le nom cherché
            return true;     //si l'element cherché est trouvé
        }  
        parcour = suivant_famille(parcour);        
    }
    return false ;
}  

pp creer_personne(int N, bool parent, int np, pp par) {
    if (N > sizeF || N > sizeH || N < 0) return NULL; // garantir un N valide

    if (!parent && np == 0) {
        N = (N == 0) ? 1 : N; // garantir l'existance d'un enfant ou moins si il n'exsite pas de parent
    }

    pp head = NULL, temp = NULL, current = NULL; // initialisation
    char sexe[2] = {'M', 'F'}; // tableau pour indique le sexe de personne
    int select = 0, inx = 0; // declaration et initialisation de inx et select / select : choisir le sex , 0 : M , 1 : F / inx : selectioner un prenom a partir les tableaux prenom

    int *indexH = (int *)malloc(sizeof(int) * N); // allocation de indexH : sauvegarder les indices deja choisit a partir  prenomH pour eviter la repition des memes prenoms dans la même sous-liste
    int *indexF = (int *)malloc(sizeof(int) * N); // alloctation de indexF : /// ///////               //////   //////     prenomF      ////////             //////////            / ////
    if (!indexH || !indexF) { // verifer que l'espace memoire etait bien alloue
        fprintf(stderr, "Erreur : allocation memoire echouee.\n"); // si non on sort et afficher un message
        free(indexH);
        free(indexF);
        exit(EXIT_FAILURE);
    }

    int cptH = 0, cptF = 0, i = 0;  // declaration et initialisation / cptH :remplir indexH / cptF : remplir indexF / i : un cpt aide a crier N maillon
        // Special case: Exactly 2 parents (1 Male, 1 Female)
        if (N == 2 && parent) {
            allouer_personne(&current); //allocation du maillon (pere)
            inx = rand() % sizeH; // choix aleatoire de l'indice du prenom du pere
            aff_person(current, prenomH[inx], 'M'); 
            aff_adress_person(current, NULL);
            head = current; //mettre le pere en tete
            allouer_personne(&current); // alocation du maillon (mere)
            inx = rand() % sizeF; // choix aleatoire de l'indice du prenom de la mere 
            aff_person(current, prenomF[inx], 'F');
            aff_adress_person(current, NULL);
            aff_adress_person(head, current); // chainer les parents
            free(indexH); // liberer les tableaux des indices
            free(indexF); 
            return head;
        }
    while (i < N) {
        allouer_personne(&current); // allocation d'une case memoire suffisante pour une personne
        if (!current) { // verifer l'etat d'allocation
            fprintf(stderr, "Erreur : allocation memoire echouee.\n");
            exit(EXIT_FAILURE);
        }

        select = rand() % 2; // choisir un sex aleatoirement
        if (select == 0) { // si choisit Homme
            do {
                inx = rand() % sizeH; // selectionner un indice de prenom aleatoirement
            } while (existe(indexH, cptH, inx) || existe_str_liste(par,head,prenomH[inx]) ); // repiter jusqu'a trouver un prenom n'est pas utilise
            aff_person(current, prenomH[inx], 'M'); // affecter le prenom et le sex a le maillon
            indexH[cptH++] = inx; // sauvgarder l'indice utilise
        } else { // si choisit Femme
            do {
                inx = rand() % sizeF;// selectionner un indice de prenom aleatoirement
            } while (existe(indexF, cptF, inx) || existe_str_liste(par,head,prenomF[inx])); // repiter jusqu'a trouver un prenom n'est pas utilise
            aff_person(current, prenomF[inx], 'F'); // affecter le prenom et le sex a le maillon
            indexF[cptF++] = inx; // sauvgarder l'indice utilise
        }

        aff_adress_person(current, NULL); // initialisation de champ suivant a NIL
        if (i == 0) { // si le maillon cree represente la tête
            head = current; // affecter l'adresse de maillon cree a la tête
            temp = current; // sauvegarder le maillon cree pour le chiner prochainement
        } else {
            aff_adress_person(temp, current); // chenage des maillons
            temp = current; // sauvegarder le maillon cree pour le chiner prochainement
        }
        i++; // incrementer le cpt qui indique le nombre des maillons crees
    }

    free(indexH); // liberer l'espace alloue par indexH
    free(indexF); // liberer l'espace alloue par indexF
    return head; // retourner la tête
}


// fonction pour creer une liste voiture de N maillon et retourner l'adresse de la tête
pv creer_voiture(int N) {
    if (N > size_mat || N <=0 ) return NULL ; // garantir un N validé
    pv temp , current , head ;
    head = temp = current = NULL ;
    int *index_matt = (int *) malloc(sizeof(int)*N) ; // un tableau contient les indices des matricule déja utilisé 
    if (!index_matt) { // vérifer l'etat d'allocation
        fprintf(stderr, "Erreur : allocation mémoire échouée.\n");
        exit(EXIT_FAILURE);
    }
    int taille_matt = 0 ; // declaration et initialisation de inx et select / cptH : remplir index_matt  / inx : selectioner un matricule à partir le tableaux matricules / i : un cpt pour creer N maillon
    int inx_matt = -1 ;
    int i = 0 ;
    while (i < N ){
        do {
            inx_matt = rand() % size_mat ; // selectionner un indice de matricule aléatoirement
        }while(existe(index_matt,taille_matt,inx_matt)) ; // repiter jusqu'à trouver un prenom n'est pas utilisé
            i ++ ; // incrementer le cpt qui indique le nombre des maillons creés
            allouer_voiture(&current) ; // allocation de nouveau maillon
            if (current == NULL) { // vérification d'etat d'allocation
                fprintf(stderr, "Erreur : allocation mémoire échouée.\n");
                exit(EXIT_FAILURE);
            }
            index_matt[taille_matt ++] = inx_matt; // sauvegarder le matricule utilisé
            aff_voiture(current,marques[rand() % size_marque],matricules[inx_matt]) ; // affecter le matricule et la marque 
            aff_adresse_voiture(current,NULL) ; // initialiser le champ suivant
            if (i == 1) { //si le maillon creé represente la tête
                head = current ; // affecter l'adresse de maillon creé à la tête
                temp = current ; // sauvegarder le maillon creé pour le chiner prochainement 
            }else {
                aff_adresse_voiture(temp , current) ; // chenage des maillons
                temp = current ; // sauvegarder le maillon creé pour le chiner prochainement 
            }   
    }
    free(index_matt) ; // liberer l'espace alloué par index_matt
    return head ; // retourner la tête
}      

pf creer_famille(int N) {
    if (N > taille) return NULL; // si le N est supperieur que la taille de notre base des donnes on retourne NIL
    int *tab = (int*) malloc(sizeof(int)*N) ; // creer un tableau pour sauvegrader les indices insere dans la liste pour eviter l'utilisation multiple de le même nom
    int tab_size = 0 ; // initialiser la taille de tableau
    int index = 0 ;    // initialiser index
    struct famille *temp , *current , *head ; // head : pointe sur la tête de la liste , current : pointe sur le nouveau mallion creer , temp : pointe sur le mallion precedent
    temp = current = head = NULL ;  // initialisation
    int i = 1 ; // i : un cpt pour creer N mallion
    while ((i <= N)){
        allouer_famille(&current) ; // on alloue une case memoire suffisante pour le maillon
        if (current == NULL) { //verifier l'etat de l'allocation
            fprintf(stderr, "Erreur : allocation memoire echouee.\n");
            exit(EXIT_FAILURE);
        }
        index =  rand() % taille ; // on choisi un nombre aleatroire inferieure a taille consederer comme un indice dans le tableau noms
        if(!existe(tab,tab_size,index)){ // verifier si l'element correspandant a l'indice pas n'etait pas dans la liste (element unique)
            tab[tab_size++] = index ;    // on insere l'indice choise pour le n'est pas reutiliser
            int np = rand()%3 ;
            pp par =creer_personne(np,true,0,NULL);
            aff_famille(current,names[index],par,creer_personne(rand()%6,false,np,par),creer_voiture(rand()%5)) ; // on affecte la valeur correspandante a l'inice choise a le mallion (nomfam reçoit la valeur)
            aff_adresse_famille(current,NULL) ;     // o, initialise le champ proc a Nil
            if (i == 1) {   // verifier si le mallion creer represente la tête
                head = current ; // affecte l'adress de ce mallion a la tête
                temp = current ; // sauvegarder l'adress de ce mallion pour le chener avec le prochain mallionn
            }else{
                aff_adresse_famille(temp,current) ; // chiner le nouveau mallion avec le precedent
                temp = current ;  // sauvegarder l'adress de ce mallion pour le chener avec le prochain mallionn
            }
            i ++ ; // incrementer i
        }
    }
    free(tab);
    return head ; // retourner la tête
}

// fonction pour creer une liste famille à partire de liste pop de partie 1

void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

// Un module qui affiche la population
void print_famille1(pf fam){
    pp parent,p,enfant,e; 
    pv v,voiture; 
    ch20 nom;
    int len;
    bool prem=true; // premiere iteration avec la famille actuelle
    while (fam){
        val_famille(fam,&nom,&parent,&enfant,&voiture); // recuperation des champs ded la famille actuelle 
        p=parent;
        e=enfant;
        v=voiture;
        len=strlen(nom); // pour designer la dimension de la box contenant le nom
        printf(JAUNE);
        for (int i=0; i<len+6; i++) printf("_"); 
        // Garder le format Xxxxx lors de l'affichage des familles
        if (nom[0] != '\0') nom[0] = toupper(nom[0]); // convertir le 1er caractère en maj
            for (int j = 1; nom[j] != '\0'; j++) {
                nom[j] = tolower(nom[j]); // Convertit les autres lettres en minuscules
            }
        printf("\n|"RESET"  %s  "JAUNE"|\n"RESET,nom); // afficher le cadre du nom de famille en jaune clair, et le nom en blanc
        for (int i=0; i<len+6; i++) printf("-");
        printf("         "); //Fin de l'affichage du nom de famille


        printf(BLUE"\n ___________           "BLEU);
        while(p){ //afficher la premiere ligne du schema selon le nb de parents et la longueur de leurs noms ex: ______    _______   ______
            strcpy(nom,p->prenom); 
            for (int i=0; i<strlen(nom)+12; i++) printf("_");
            printf("      ");
            p=suivant_personne(p);
        }
        printf(BLUE"\n|"RESET"  Parents  "BLUE"|         "); // afficher le mot "parents"
        p=parent;
        while(p){
            strcpy(nom,p->prenom);
            if (nom[0] != '\0') nom[0] = toupper(nom[0]); // pour le format Xxxxx comme deja expliqué
            for (int j = 1; nom[j] != '\0'; j++) {
                nom[j] = tolower(nom[j]); // Convertit les autres lettres en minuscules
            }
            printf(BLEU"|"RESET"  %s  "BLEU"|"RESET" %c "BLEU"| ",nom,p->sexe); // affichage des prenoms et sexes
            p=suivant_personne(p);
            if (p) printf(BLUE"*"BLEU"-|--->"); // chainage au cas de plusieurs parents
            else printf(BLUE"/ "BLEU"|"); // '/' represente nil
        }
        printf(BLUE"\n -----------           "BLEU);
        p=parent;
        while(p){ // affichage de la ligne de cloture des boxs
            strcpy(nom,p->prenom);
            for (int i=0; i<strlen(nom)+12; i++) printf("-");
            printf("      ");
            p=suivant_personne(p);
        }// fin de l'affichage des parents

        printf(BLUE" \n ___________          "BLEU);
        if(!enfant) printf(BLUE"\n|"RESET"  Enfants  "BLUE"|         \n -----------           \n"RESET); // cas de liste vide (pas d'enfants)
        while (enfant){
            if (!prem) printf("                       "); 
            for(int k=0;k<4&&e;k++){ // affichage des enfants 4 a la fois dans la meme ligne pour eviter les problemes de l'espace insuffisant dans le terminal
                strcpy(nom,e->prenom);
                for (int i=0; i<strlen(nom)+10; i++) printf("_");
                printf("      ");
                e=suivant_personne(e);
            }
            printf("\n"); // les meme
            if (prem) { // le booleen prem garantit l'affichage du mot " enfant", "voiture" la premiere fois uniquement et non pas chaque 4 elements
                printf(BLUE"|"RESET"  Enfants  "BLUE"|        "RESET);
            }
            else printf("                      ");
            e=enfant; 
            //les memes etapes que l'affichage des parents
            for(int k=0;k<4&&e;k++){
                strcpy(nom,e->prenom);
                if (nom[0] != '\0') nom[0] = toupper(nom[0]);
                for (int j = 1; nom[j] != '\0'; j++) {
                    nom[j] = tolower(nom[j]); // Convertit les autres lettres en minuscules
                }
                printf(BLEU"|"RESET" %s "BLEU"|"RESET" %c "BLEU"| ",nom,e->sexe);
                e=suivant_personne(e);
                if (e) printf(BLUE"*"BLEU"-|--->");
                else printf(BLUE"/"BLEU" |");
            }
            printf("\n");
            if (prem){
                printf(BLUE" -----------          "BLEU);
                prem=false;
            }
            else printf("                       ");
            e=enfant;
            for(int k=0;k<4&&e;k++){
                strcpy(nom,e->prenom);
                for (int i=0; i<strlen(nom)+10; i++) printf("-");
                printf("      ");
                e=suivant_personne(e);
            }//Fin de l'affichage de la liste d'enfants
            printf("\n");
            enfant=e;
        }

        //De même on affiche les voitures 3 par 3
        prem=true;
        printf(BLUE" ____________        "BLEU);
        if (!voiture) printf(BLUE"\n|"RESET"  Voitures  "BLUE"|      \n ------------        \n"RESET);
        while (voiture){
            if(!prem)  printf("                     ");
            for(int k=0;k<3&&v;k++){
                strcpy(nom,v->marque);
                if (nom[0] != '\0') nom[0] = toupper(nom[0]);
                for (int j = 1; nom[j] != '\0'; j++) {
                    nom[j] = tolower(nom[j]); // Convertit les autres lettres en minuscules
                }
                for (int i=0; i<strlen(nom)+20; i++) printf("_");
                printf("      ");
                v=suivant_voiture(v);
            }
            if (prem) {
                printf(BLUE"\n|"RESET"  Voitures  "BLUE"|      ");
            }
            else printf("\n                    ");
            v=voiture;
            for(int k=0;k<3&&v;k++){
                strcpy(nom,v->marque);
                printf(BLEU"|"RESET" %s "BLEU"|"RESET" %s "BLEU"|",nom,v->nemero);
                v=suivant_voiture(v);
                if (v) printf(BLUE" *"BLEU"-|--->");
                else printf(BLUE" / "BLEU"|");
            }
            if (prem){
                printf(BLUE"\n ------------        "BLEU);
                prem=false;
            }
            else printf("\n                     ");
            v=voiture;
            for(int k=0;k<3&&v;k++){
                strcpy(nom,v->marque);
                for (int i=0; i<strlen(nom)+20; i++) printf("-");
                printf("      ");
                v=suivant_voiture(v);
            }//Fin de l'affichage de la liste des voitures
            printf("\n");
            voiture=v;
        }
        prem=true;
        fam=suivant_famille(fam);
        if (fam) printf(JAUNE"   |\n   |\n   V\n"RESET);
        }
        printf(RESET);
}
 

// une fonction pour creer une liste parent manuellement
pp remplire_parent(int N) { // N est le nombre
    pp current = NULL ;
    pp temp = NULL ;
    switch (N)
    {
    case 0: // si il n'ya pas des parents on retourne NIL
        return NULL ;
    case 1 : // cas d'un seule parent
        allouer_personne(&current) ; // allouer une case memoire suffisante pour une personne
        if (current == NULL) { // verifier qu'une case memoire est alloue sinon on sort
            fprintf(stderr, "Erreur : allocation memoire echouee.\n"); // un message qui indique qu'il ya un erreur
            exit(EXIT_FAILURE);  // Quitter proprement le programme
        }
        printf(YELLOW "     -> "RESET"Veuillez entrer le prenom de parent : ") ;
        scanf("%s",current->prenom) ; // affecter le prenom entre par l'utilisateur
        getchar() ; // vider le buffer du saut de ligne laissé par scanf
        printf(YELLOW "     -> "RESET"Veuillez entrer le sexe de parent :") ;
        scanf("%c",&current->sexe) ; // affecter le sexe entré par l'utilisateur
        aff_adress_person(current,NULL) ;
        return current ; // retourne la tête
    case 2 : // dans ce cas on cree la maillon de pere et le rempli d'apres l'utilisateur , utilisant la même maniere on cree le maillon de mere apr on les chener
        allouer_personne(&current) ;
        if (current == NULL) { // verifier qu'une case memoire est alloue sinon on sort
            fprintf(stderr, "Erreur : allocation memoire echouee.\n"); // un message qui indique qu'il ya un erreur
            exit(EXIT_FAILURE);  // Quitter proprement le programme
        }
        printf("entrer le prenom de père : ") ;
        scanf("%s",current->prenom) ;
        current->sexe = 'M' ;
        aff_adress_person(current , NULL) ;
        allouer_personne(&temp) ;
        if (temp == NULL) { // verifier qu'une case memoire est alloue sinon on sort
            fprintf(stderr, "Erreur : allocation memoire echouee.\n"); // un message qui indique qu'il ya un erreur
            exit(EXIT_FAILURE);  // Quitter proprement le programme
        }
        printf(YELLOW "     -> "RESET"Veuillez enter le prenom de la mere :") ;
        scanf("%s",temp->prenom) ;
        temp->sexe = 'F' ;
        aff_adress_person(temp,NULL) ;
        aff_adress_person(current , temp) ;
        return current ; // retourne la tête
    default:
        break;
    }
}

pp remplire_enfant(pp fam,int N) {
    ch20 prenom;
    char sexe;
    if (N <= 0) return NULL; // Si l'utilisateur entre un nombre non valide
    pp head, current, temp; // head : tête de la liste / current : maillon en cours / temp : maillon precedent
    head = current = temp = NULL; // Initialisation des pointeurs

    for (int i = 1; i <= N; i++) { // Creer N maillons
        printf(YELLOW" -> "RESET"Veuillez entrer le prenom de l'enfant : ");
        scanf("%s", prenom); // Affecter le prenom entre par l'utilisateur
        getchar(); // Sauter la ligne

        if (existe_str_liste(fam,head, prenom)) { // Verifier si le prenom existe deja
            printf(RED"\nLe prenom existe deja dans la famille !\n"RESET);
            i--; // Redemander la saisie
        } else {
            allouer_personne(&current); // Allocation d'une case memoire suffisante pour une personne
            if (current == NULL) { // Verifier si l'allocation memoire a reussi
                fprintf(stderr, "Erreur : allocation memoire echouee.\n");
                exit(EXIT_FAILURE); // Quitter proprement le programme
            }

            strcpy(current->prenom, prenom); // Affecter le prenom

            // Verification du sexe avec une boucle
            do {
                printf(YELLOW" -> "RESET"Veuillez entrer le sexe de l'enfant (M/F) : ");
                scanf(" %c", &sexe);
                getchar(); // vider le buffer
                sexe=toupper(sexe);
            } while (sexe != 'M' && sexe != 'F');

            current->sexe = sexe; // Affecter le sexe valide

            aff_adress_person(current, NULL); // Initialisation du champ suivant

            if (i == 1) { // Si le maillon cree represente la tête
                head = current; // Affectation de la tête
                temp = current; // Sauvegarder le maillon precedent
            } else {
                aff_adress_person(temp, current); // Chaînage des maillons
                temp = current; // Sauvegarder le maillon precedent
            }
        }
    }
    return head; // Retourner la tête
}

// une fonction pour remplir une liste voiture manuellement 
pv remplire_voituer(int N) {
    if (N <= 0 ) return NULL ; // si l'utilisateur entre un nombre qui n'est pas valide 
    pv head, current , temp ; // head : indique la tête de la liste / current : utilisé pour creer les maillons / temp : utilisé pour sauvegarder le maillon precedent
    head = current = temp = NULL ; // initialisation des pointeurs
    for (int i = 1 ; i <= N ; i ++ ) { // creer N maillons
        allouer_voiture(&current) ; // allocarion d'une case mémoire suffisante pour une maillon personne
        if (current == NULL) { // verifier qu'une case mémoire est alloué sinon on sort 
            fprintf(stderr, "Erreur : allocation mémoire échouée.\n"); // un message qui indique qu'il ya un erreur
            exit(EXIT_FAILURE);  // Quitter proprement le programme 
        }
        printf(YELLOW "     -> "RESET"Veuillez entrer la marque de voiture : ") ;
        scanf("%s",current->marque) ; // affecter la marque entré par l'utilisateur
        printf(YELLOW "     -> "RESET"Veuillez entrer le matricule de voiture :") ;
        scanf("%s",current->nemero) ; // affecter le matricuke entré par l'utilisateur
        aff_adresse_voiture(current,NULL) ; // initialisation de le champs suivant 
        if(i == 1) { // si le maillon creer repreente la tête 
            head = current ; // affectation de la tête
            temp = current ; // sauvegarder le maillon precedent
        }else {
            aff_adresse_voiture(temp,current) ; // le chenage des maillons
            temp = current ; // sauvegarder le maillon precedent
        }
    }
    return head ; // retourne la tête 
}

bool reinserer(){ //1 pour ecraser/ 0 pour nouveau // 
    clear_screen();// nchoufha w n9oulk ida 3arfa l prblm
    printf(YELLOW"       ->"RESET" Cette famille existe deja dans la population \n         Voulez-vous saisir une autre famille ? \n\n      OUI(<-)                       NON(->)") ;
    int ch;
    while ((ch = _getch()) != 27 ) {
        if (ch == 0 || ch == 224) {
            ch = _getch();
            switch (ch){
                case 75:
                    moveCursorToTop();
                        printf(YELLOW"       ->"RESET" Cette famille existe deja dans la population \n         Voulez-vous inserer une autre famille ? \n\n    "GREEN"  OUI(<-)  "RESET"             NON(->)") ;
                    sleep(1);
                    break;
                case 77:
                    moveCursorToTop();
                        printf(YELLOW"       ->"RESET" Cette famille existe deja dans la population \n         Voulez-vous inserer une autre famille ? \n\n      OUI(<-)          "GREEN"     NON(->)"RESET) ;
                    sleep(1);
                    break;
            }
                if (ch==75) return true;
                else if (ch==77) return false;
        }
    } 
}

void clear_screen() {
    system("cls");
}
void moveCursorToTop() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0}; // Position en haut à gauche
    SetConsoleCursorPosition(hConsole, coord);
} 
void inserer_famille(pf *pop, ch20 nom, pp parents,pp enfants, pv voitures ) {
    if(present_famille(*pop,nom) != NULL)  return; // l'utilisateur doit entrer un nom qui n'existe pas sinon on sort
        pf  parcour = *pop , prec = NULL , nouvelle_cell = NULL;
        allouer_famille(&nouvelle_cell) ;
        if (nouvelle_cell == NULL) { // verifier qu'une case memoire est alloue sinon on sort
            fprintf(stderr, "Erreur : allocation memoire echouee.\n"); // un message qui indique qu'il ya un erreur
            exit(EXIT_FAILURE);  // Quitter proprement le programme
        }
        aff_famille(nouvelle_cell,nom,parents,enfants,voitures) ; // affecter le nom a le nouveau mallion
        if(*pop == NULL ||ordre_alpha(nom,(*pop)->nom,0)) { // verifier si on va inserer le nom dans la première position
        aff_adresse_famille(nouvelle_cell,*pop) ; // chiner la nouvelle tête avec le deuxieme element
        *pop = nouvelle_cell ;  // mis a jour pop qui pointe sur la tête
        return ; // on sort
        }
        else {
        prec = parcour ; // prec reçoit la valeur precedente de parcour
        parcour = suivant_famille(parcour) ; // on avance dans la liste utilisant parcour
        while(parcour) {
            if(ordre_alpha(nom,parcour->nom,0)) { // si on trouve la position valide pour le nouveu nom
                aff_adresse_famille(prec,nouvelle_cell) ; // chiner le mallion precedent avec le nouveau mallion
                aff_adresse_famille(nouvelle_cell,parcour) ; // chiner le nouveau mallion avec le prochain mallion
                return ; // on sort
            }else {
                prec = parcour ; // on avance dans la liste sauvegardant l'element precedent
                parcour = suivant_famille(parcour) ;
            }
        }
        // inserer le nouveau mallion dans la fin de liste
        aff_adresse_famille(prec,nouvelle_cell) ;
        aff_adresse_famille(nouvelle_cell,NULL) ;
    }
}

//Module qui permet de supprimer une famille1 de la liste si elle existe
void supp_famille(pf *head, char* nom){
    pf sup = NULL , parcour=*head;
    sup=present_famille(*head,nom);  //l'element à supprimer (si il existe)
    if (sup){   //l'element existe
        if(sup== *head)  //l'element à supprimer se trouve à la 1ere position
            *head = suivant_famille(*head) ;     //Avancer la tete
        else{
                while(suivant_famille(parcour)!=sup) parcour=suivant_famille(parcour);    //acceder au precedent de sup (pourr le chaianage)
                aff_adresse_famille(parcour,suivant_famille(sup));  // mettre à jour au chenage
            }
            liberer_person(sup->enfant) ; // liberer l'espace mémoire alloué par les enfants 
            liberer_person(sup->parent) ; // liberer l'espace mémoire alloué par les parents
            liberer_voiture(sup->voiture) ; // liberer l'espace mémoire alloué par les voitures
            free(sup);  //liberer le maillon sup
    }
}

//Module qui permet de supprimer une famille de la liste si elle existe sans vider les listes enfants , parents ....
void supp_famille_pop(pf *head, char* nom){
    pf sup = NULL , parcour=*head;
    sup=present_famille(*head,nom);  //l'element à supprimer (si il existe)
    if (sup){   //l'element existe
        if(sup== *head)  //l'element à supprimer se trouve à la 1ere position
            *head = suivant_famille(*head) ;     //Avancer la tete
        else{
                while(suivant_famille(parcour)!=sup) parcour=suivant_famille(parcour);    //acceder au precedent de sup (pourr le chaianage)
                aff_adresse_famille(parcour,suivant_famille(sup));  // mettre à jour au chenage
            }
            free(sup);  //liberer le maillon sup
    }
}

//Fonction qui permet de demenager une famille de pop1 vers pop2
void demenager_famille(pf *pop1, pf *pop2) {
    ch20 nom;
    pf famille;
    if (!(*pop1)) {
        printf(RED"\nLa population source est vide. Impossible de demenager une famille.\n"RESET);
        return; 
    }
    printf(YELLOW "     -> "RESET"Veuillez entrez le nom de la famille a demenager : ");
    scanf("%s", nom);
    while(present_famille(*pop2,nom) != NULL){ // l'utilisateur doit entrer un nom qui n'existe pas sinon on sort
        if(reinserer()) { // si l'utilisateur veut quand meme reinserer le nom
            printf(YELLOW"\n -> "RESET"Veuillez entrer le nom de famille a demenager ") ;
            scanf("%s",nom) ;
        }
        else return;
    }

    famille = present_famille(*pop1, nom); //rechercher la famille a demenager dans la source
    if (!famille) { //si elle n'existe pas
        printf(RED"\nLa famille '%s' n'existe pas dans la population source.\n"RESET, nom);
        return;
    }
    //sinon
    inserer_famille(pop2,nom,famille->parent,famille->enfant,famille->voiture);// Inserer la famille dans pop2
    supp_famille_pop(pop1, nom); // Supprimer la famille de pop1
    printf(GREEN"\nLa famille '%s' a ete demenagee avec succes.\n"RESET, nom);
}

//Module qui permet d'inserer une voiture dans une liste de voiture si elle n'existait pas
pv inserer_voiture(pv head, ch20 marque, ch20 matricule) {
    pv nouvelle_voiture;
    allouer_voiture(&nouvelle_voiture);//allocation du maillon

    aff_voiture(nouvelle_voiture, marque, matricule); 
    aff_adresse_voiture(nouvelle_voiture, NULL);

    if (!head) return nouvelle_voiture; // Si la liste est vide, la nouvelle voiture devient la tête
    pv temp = head;   // Parcourir la liste pour trouver le dernier element
    while (suivant_voiture(temp) != NULL) {// insertion de la liste a la fin  de la liste 
        if (strcasecmp(temp->nemero,matricule)==0){
            free(nouvelle_voiture);
            return head; //inchangée
        }
        temp = suivant_voiture(temp);
    }
    aff_adresse_voiture(temp, nouvelle_voiture);// Inserer la nouvelle voiture après le dernier element
    return head; // Retourner la tête inchangee
}

//Module qui permet de supprimer une voiture d'une liste de voitures si elle existe
pv supprimer_voiture(pv head, ch20 matricule) {
    if (!head) return NULL; // Liste vide
    pv temp = head, prev = NULL;

    if (strcmp(temp->nemero, matricule) == 0) {    // Verifier si la voiture a supprimer est la première de la liste
        head = suivant_voiture(temp); // Changer la tête de liste
        free(temp); // Liberer la memoire
        return head;
    }
    while (temp && strcmp(temp->nemero, matricule) != 0) {    // Rechercher la voiture dans la liste
        prev = temp;
        temp =suivant_voiture(temp);
    }

    if (!temp) {     // Si la voiture n'est pas trouvee
        printf("Voiture avec matricule %s non trouvee.\n", matricule);
        return head;
    }

    aff_adresse_voiture(prev,suivant_voiture(temp));    // Supprimer le maillon
    free(temp);

    return head;
}

//Module qui permet de supprimer un enfant, cas de deces par exemple
pp supprimer_enfant(pp head, ch20 prenom) {
    if (!head) return NULL; // Liste vide
    pp temp = head, prev = NULL;

    if (strcasecmp(temp->prenom, prenom) == 0) { // Si l'enfant a supprimer est en tête de liste
        head = suivant_personne(temp);
        liberer_person(temp);
        return head;
    }
    while (temp && strcasecmp(temp->prenom, prenom) != 0) { // Parcourir la liste pour trouver l'enfant a supprimer
        prev = temp;
        temp = suivant_personne(temp);
    }
    if (!temp) return head; // Si l'enfant n'est pas trouve
    aff_adress_person(prev, suivant_personne(temp)); // Supprimer l'enfant en changeant le chainage les liens
    liberer_person(temp);

    return head;
}

//Module qui permet de supprimer un parent de la liste si il existe
void supprimer_parent(pf famille, char sexe,bool* ext) {
    if (!famille || !famille->parent) return; // Verifier si la famille ou la liste des parents est vide
    pp temp = famille->parent;
    pp prev = NULL;

    while (temp && temp->sexe!=sexe){ //rechercher le parent par sexe (pere/mere)
        prev=temp;
        temp=suivant_personne(temp);
    }
    if(!temp) *ext=false;
    else *ext=true; // tahia ljazay
    if (prev&&temp) { //si c'est le 2eme element
        aff_adress_person(prev,suivant_personne(temp));
    }
    else if (temp) famille->parent=suivant_personne(temp); // si c'est la tete 
    liberer_person(temp);
}

//Module qui permet de creer une copie d'une liste pp
pp copier_personne(pp original) {
    if (!original) return NULL;  // liste vide
    pp copy=NULL,p,q=NULL;
    ch20 prenom;
    char sexe;

    //initialiser la tete
    allouer_personne(&copy);
    aff_person(copy,original->prenom,original->sexe);
    aff_adress_person(copy,NULL);
    original=suivant_personne(original);
    q=copy; 
    while(original){
        allouer_personne(&p); //creer le reste des maillons
        aff_person(p,original->prenom,original->sexe); 
        aff_adress_person(p,NULL);
        aff_adress_person(q,p);//chainage 
        q=p;
        original=suivant_personne(original);
    }

    return copy;
}

//Module qui permet de creer une copie d'une liste pv
pv copier_voit(pv original) {
    if (!original) return NULL;  // Liste vide
    pv copy, p, q;
    ch20 marque, numero;

    //creation de la tete
    allouer_voiture(&copy);
    aff_voiture(copy, original->marque, original->nemero);
    aff_adresse_voiture(copy, NULL);
    original = suivant_voiture(original);
    q = copy;

    while (original) {
        allouer_voiture(&p); //creation du reste des maillons
        aff_voiture(p, original->marque, original->nemero);
        aff_adresse_voiture(p, NULL);
        aff_adresse_voiture(q, p); //chainage
        q = p;
        original = suivant_voiture(original);
    }

    return copy;
}

//Module qui permet de creer une copie d'une population pour ne pas modifier la liste originale
pf copier_pop(pf pop){
    pf parcour=pop,copy,q,p=NULL;
    ch20 cp;
    pp pa,e;
    pv v;

    //creation de la tete
    allouer_famille(&copy);
    val_famille(parcour,&cp,&pa,&e,&v);
    pa=copier_personne(pa); //copie de la liste des parents
    e=copier_personne(e); // coipie de la liste des enfants 
    v=copier_voit(v); // copie de la liste des voitures
    aff_famille(copy,cp,pa,e,v);
    aff_adresse_famille(copy,NULL);
    parcour=suivant_famille(parcour);
    q=copy;
    while(parcour){
        allouer_famille(&p); //creation du reste des maillons
        val_famille(parcour,&cp,&pa,&e,&v); //lazm nzid copy t3 personne w voit
        pa=copier_personne(pa);
        e=copier_personne(e);
        v=copier_voit(v);
        aff_famille(p,cp,pa,e,v);
        aff_adresse_famille(q,p); // chainage
        aff_adresse_famille(p,NULL);
        q=p;
        parcour=suivant_famille(parcour);
    }
    return copy;
}
//Module qui permet de fusionner 2 populations
pf fusion1(pf pop1,pf pop2){ 
    pf pop3=pop1; // pointeur resultat
    ch20 nom;
    while(pop2){ 
        strcpy(nom,pop2->nom); 
        inserer_famille(&pop3,nom,pop2->parent,pop2->enfant,pop2->voiture);// Inserer la famille dans pop3
        supp_famille_pop(&pop2,nom); // supprimer la famille de pop2 sans toucher ses champs
    }
    return pop3;
}

//Module qui permet de permutter 2 famille 
void echanger_familles(pf a, pf b) { // chofi tele dork nab3at haja 
    char temp_nom[50]; // Supposons que le nom fasse 50 caractères max
    strcpy(temp_nom, a->nom);
    strcpy(a->nom, b->nom);
    strcpy(b->nom, temp_nom);

    // Échanger les autres champs
    void *temp_enfant = a->enfant;
    a->enfant = b->enfant;
    b->enfant = temp_enfant;

    void *temp_parent = a->parent;
    a->parent = b->parent;
    b->parent = temp_parent;

    void *temp_voiture = a->voiture;
    a->voiture = b->voiture;
    b->voiture = temp_voiture;
}

// Module qui permer de trier une population par ordre alphabetique
void treer_famille(pf head) {
    if (head == NULL) return; // Éviter une liste vide

    pf temp;
    allouer_famille(&temp);
    if (temp == NULL) { //verifier l'etat de l'allocation
        printf("Erreur d'allocation mémoire\n");
        return;
    }
    bool end = false; // booleen qui detecte les permutation, si il reste a vrai donc la liste est trie
    while (!end) { 
        end = true;
        pf parcour = head; 
        while (parcour->suivant != NULL) { 
            if (!ordre_alpha(parcour->nom, parcour->suivant->nom, 0)) {  //comparer l'ordre alphabetique les noms
                // Échanger les éléments correctement
                echanger_familles(parcour, parcour->suivant);
                end = false;
            }
            parcour = parcour->suivant;
        }
    }
}

//Fonction qui permet de creer une liste d'enfants ou de parents manuellement
pp creer_personne_manuel(int N, bool parent, int np, pp par) { //nb de personnes, parents ou pas, nb de parents, liste des parents si elle existe (null sinon) pour ne pas utiliser un nom existant dans la famille
    if (N <= 0 && ((!parent && np != 0)||parent)) return NULL; // Verification de la validite de N
    pp head = NULL, temp = NULL, current = NULL;
    char sexe;
    ch20 prenom;
    int i = 0;

    // Cas special : un seul parent
    if (N == 1 && parent) {
        allouer_personne(&current); // allouer une case memoire
        printf(YELLOW "     -> "RESET"Veuillez entrez le prenom du parent : ");
        scanf(" %[^\n]", prenom);
        do { // accepter les sexes valides uniquement
            printf(YELLOW "     -> "RESET"Veuillez entrez le sexe (M/F) du parent : ");
            scanf(" %c", &sexe);
            sexe=toupper(sexe);
        } while (sexe != 'M' && sexe != 'F');
        aff_person(current, prenom, sexe);
        aff_adress_person(current, NULL); // le seul element donc c'est le premier et la tete
        return current;
    }
    // Cas special : exactement 2 parents (1 Homme, 1 Femme)
    if (N == 2 && parent) {
        //creer pere
        allouer_personne(&current);
        printf(YELLOW "     -> "RESET"Veuillez entrez le prenom du pere : ");
        scanf(" %[^\n]", prenom);
        aff_person(current, prenom, 'M');
        aff_adress_person(current, NULL);
        head = current;
        // creer mere
        allouer_personne(&current);
        printf("Entrez le prenom de la mere : ");
        scanf(" %[^\n]", prenom);
        aff_person(current, prenom, 'F');
        aff_adress_person(current, NULL);
        aff_adress_person(head, current);

        return head;
    } 
    // liste d'enfant
    while (i < N) {
        printf(YELLOW "     -> "RESET"Veuillez entrez le prenom de l'enfant %d : ", i + 1);
        scanf(" %[^\n]", prenom);
        if (existe_str_liste(par,head,prenom)){ // si le nom saisi existe deja dans la famille (soit dans la liste d'enfants ou de parents)
            printf(RED"         Ce prenom existe deja dans la famille! veuillez resaisir le prenom.\n"RESET);
        }
        else{ 
            allouer_personne(&current);
            do { // accepter les sexes valides uniquement
                printf(YELLOW "     -> "RESET"Veuillez entrez le sexe (M/F) de l'enfant %d : ", i + 1);
                scanf(" %c", &sexe);
                sexe=toupper(sexe);
            } while (sexe != 'M' && sexe != 'F');

            aff_person(current, prenom, sexe);
            aff_adress_person(current, NULL);

            if (i == 0) { // insertion au niveau de la tete
                head = current;
                temp = current;
            } else {
                aff_adress_person(temp, current); // chainage avec le precedent
                temp = current;
            }
            i++;
        }
    }
    return head;
}

//Fonction qui permet de creer une liste de voiture manuellement
pv creer_voiture_manuel(int N) {
    if (N <= 0) return NULL; // Verification de la validite de N
    pv temp, current, head;
    head = temp = current = NULL;
    ch20 marque, matricule;
    int i = 0;
    while (i < N) {
        allouer_voiture(&current); // Allocation d'un nouveau maillon
        printf(YELLOW "\n     -> "RESET"Veuillez entrez la marque de la voiture %d : ", i + 1);
        scanf(" %[^\n]", marque);
        printf(YELLOW "\n     -> "RESET"Veuillez entrez le matricule de la voiture %d : ", i + 1);
        scanf(" %[^\n]", matricule);
        aff_voiture(current, marque, matricule); // Affectation des valeurs entrees
        aff_adresse_voiture(current, NULL); // Initialisation du champ suivant
        if (i == 0) { // Insertion au niveau de la tete
            head = current;
            temp = current;
        } else { // chainage avec le precedent
            aff_adresse_voiture(temp, current); // Chaînage des maillons
            temp = current;
        }
        i++;
    }
    return head; // Retourner la tête de la liste
}

//Fonction qui permet de creer une population manuellement
pf creer_famille_manuel(int N) {
    if (N <= 0) return NULL;
    pf head = NULL, temp = NULL, current = NULL;
    ch20 nomfam;
    int np, ne, nv; // nb enf, nb par, nb voit
    for (int i = 0; i < N; i++) {
        allouer_famille(&current);
        if (!current) { // verifier l'etat de l'allocation
            fprintf(stderr, "Erreur : allocation memoire echouee.\n");
            exit(EXIT_FAILURE);
        }
        printf(YELLOW "     -> "RESET"Veuillez entrez le nom de la famille %d : ", i + 1);
        scanf(" %s", nomfam);
        getchar() ;
        while(present_famille_nonTrie(head,nomfam)){ // l'utilisateur doit entrer un nom qui n'existe pas sinon on sort
                printf(RED"     Cette famille existe deja dans la population!\n"RESET);
                printf(YELLOW" -> "RESET"Veuillez entrer le nom de famille pour l'inserer ") ;
                scanf("%s",nomfam) ; 
        }
        printf(YELLOW "     -> "RESET"Veuillez entrez le nombre de parents (0, 1 ou 2) : ");
        scanf("%d", &np);
        getchar() ;
        pp parents = creer_personne_manuel(np, true, np,NULL);

        printf(YELLOW "     -> "RESET"Veuillez entrez le nombre d'enfants : ");
        scanf("%d", &ne);
        getchar() ;

        if (np == 0 && ne == 0) { // si nb par =nb enf = 0 // famille vide!!
            printf(RED"     Erreur : Une famille doit contenir au moins un parent ou un enfant.\n"RESET);
            free(current);
            i--;
            continue;
        }
        pp enfants = creer_personne_manuel(ne, false, np,parents);

        printf(YELLOW "     -> "RESET"Veuillez entrez le nombre de voitures : ");
        scanf("%d", &nv);
        pv voitures = creer_voiture_manuel(nv);

        aff_famille(current, nomfam, parents, enfants, voitures); 
        aff_adresse_famille(current, NULL); 

        if (i == 0) { // insertion au niveau de la tete
            head = current;
            temp = current;
        } else { // chainage avec le precedent
            aff_adresse_famille(temp, current);
            temp = current;
        }
    }
    return head;
}


// un module qui creer un rapport sur la voiture voleé
void ecrit_rapport_vol(pf  p) {
    // obtenir le temps actuel
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);

    // initialisation des chaines 
    char rapport[50];
    snprintf(rapport, sizeof(rapport), "Date du rapport : %02d-%02d-%04d",
    local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900);

    // Parents
    char parents[100] = "Parents : ";
    if (p->parent == NULL) {
        strcat(parents, "/");
    } else {
        pp current = p->parent;
        while (current) {
            strcat(parents, current->prenom);
            if (current->suivant) strcat(parents, " ");
            current = current->suivant;
        }
    }

    // Enfants
    char enfant[200] = "Enfants : ";
    if (p->enfant == NULL) {
        strcat(enfant, "/");
    } else {
        pp current = p->enfant;
        while (current) {
            strcat(enfant, current->prenom);
            if (current->suivant) strcat(enfant, " ");
            current = current->suivant;
        }
    }

    // creation de féchier
    FILE *fh_output = fopen("rapport_vol.doc", "w");
    if (fh_output == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    
    // remplir le féchier
    fprintf(fh_output, "Rapport de Vol de Véhicule\n");
    fprintf(fh_output, "%s\n", rapport);
    fprintf(fh_output, "1. Informations sur la famille propriétaire\n");
    fprintf(fh_output, "Nom de famille : %s\n", p->nom);
    fprintf(fh_output, "%s\n", parents);
    fprintf(fh_output, "%s\n", enfant);
    fprintf(fh_output, "2. Détails du véhicule volé\n");
    fprintf(fh_output, "Marque : %s\n", p->voiture ? p->voiture->marque : "Inconnue");
    fprintf(fh_output, "Matricule : %s\n", p->voiture ? p->voiture->nemero : "Inconnue");
    fprintf(fh_output, "Couleur : / \nAutres détails distinctifs : / \n");
    fprintf(fh_output, "4. Déclaration et actions entreprises\n");
    fprintf(fh_output, "La famille a signalé le vol aux autorités locales.\n");
    fprintf(fh_output, "Une plainte a été déposée sous le numéro 1234566789.\n");
    fprintf(fh_output, "Toute personne ayant des informations est priée de contacter 1055.\n");
    fprintf(fh_output, "Signature\n");
    fclose(fh_output);
}

int nbfamille(pf pop){
    int cpt=0;          //Compteur des elements
    pf temp=pop;
    while (temp){   //Parcour de la liste et incrementation du compteur
        cpt++;
        temp=suivant_famille(temp);
    }
    return cpt;
}

// fonction qui calcule le nombre des familles qui ont N parents
int nb_famille_Nparent(pf head,int N) {
    pf p = head ; // sauvegarder la tête 
    int cpt , nb ; // cpt : pour calculer le nombre des parents dans une famille , nb : calculer les familles Nparents 
    cpt = nb = 0 ; // initialisation
    pp q = NULL ;
    while (p) { // boucle pour parcourir la population
        q = p->parent ;// sauvegarder la tête de la liste parent
        cpt = 0 ;
        while(q) {// parcourir la liste parent 
            cpt ++ ; // incrementation
            q = suivant_personne(q) ; // avancement dans la liste parent
        }
        if(cpt == N) nb ++ ; // si la famiile est Nparent famille on incremente nb 
        p = suivant_famille(p) ; // avancer dans la population
    }
    return nb ;
}
// fonction qui calcule le nombre des familles qui ont N enfants
int nb_famille_Nenfants(pf head,int N) {
    pf p = head ; // sauvegarder la tête 
    int cpt , nb ; // cpt : pour calculer le nombre des enfants dans une famille , nb : calculer les familles Nenfants 
    cpt = nb = 0 ;// initialisation
    pp q = NULL ;
    while (p) { // boucle pour parcourir la population
        q = p->enfant ; // sauvegarder la tête de la liste enfant
        cpt = 0 ; 
        while(q) { // parcourir la liste enfant 
            cpt ++ ; // incrementation
            q = suivant_personne(q) ; // avancer dans la liste enfant 
        }
        if(cpt == N) nb ++ ; // si la famiile est Nenfant famille on incremente nb
        p = suivant_famille(p) ; // avancer dans la population
    }
    return nb ;
}
// fonction qui calcule le nombre des familles qui ont N voitures
int nb_famille_Nvoitures(pf head,int N) {
    pf p = head ; // sauvegarder la tête 
    int cpt , nb ; // cpt : pour calculer le nombre des voitures dans une famille , nb : calculer les familles Nvoitures
    cpt = nb = 0 ; // initialisation
    pv q = NULL ;
    while (p) { // parcourir la population
        q = p->voiture ; // sauvegarder la tête de la liste voiture
        cpt = 0 ;
        while(q) { // parcourir la liste voiture
            cpt ++ ; // incrementation
            q = suivant_voiture(q) ; // avancement dans la liste voiture
        }
        if(cpt == N) nb ++ ; // si la famiile est Nvoiture famille on incremente nb
        p = suivant_famille(p) ; // avancement dans la population
    }
    return nb ;
}
//procedure qui permet de calcueler le nombre des femmes et d'hommes dans pop
void nbsexe(pf head , int *nbH , int *nbF) {
    *nbH = *nbF = 0 ; // initialisation
    pf p = head ;
    while (p){ // parcourir la population
        pp parent = p->parent ;  // sauvegarder la tête de liste parent 
        while (parent){ // parcourir la liste parent
            if(parent->sexe == 'M' || parent->sexe == 'm') { // si le maillon represent un homme 
                (*nbH) ++ ; // incrementation dans le cpt d'hommes
            }else {
                (*nbF) ++ ; // incrementation dans le cpt des femmes 
            }
            parent = parent->suivant ; // avancement dans la liste parent 
        }
        pp enfant = p->enfant ;  // sauvegarder la tête de liste enfant 
        while(enfant) { // parcourir la liste enfant
            if(enfant->sexe == 'M' || enfant->sexe == 'm') {  // si le maillon represent un homme
                (*nbH) ++ ;  // incrementation dans le cpt d'hommes
            }else {
                (*nbF) ++ ; // incrementation dans le cpt des femmes
            }
            enfant = enfant->suivant ; // avancement dans la liste enfant 
        }
        p = p->suivant ; // avancement dans la population
    }
    


}
//Fonction qui permet de calculer le nombre des voitures dans pop
int nbVoiture(pf head) {
    int cpt = 0 ;
    pf p = head ; 
    while(p) { // parcourir la population
        pv voiture = p->voiture ; 
        while(voiture){ // parcourir la liste voiture
            cpt ++ ; // increment le cpt 
            voiture = suivant_voiture(voiture) ; // avancement 
        }
        p = suivant_famille(p) ; // avancement dans la population
    }
    return cpt ;
}
//Fonction qui permet de calculer le nombre des parents dans pop
int nbParent(pf head) {
    int cpt = 0 ;
    pf p = head ;
    while (p){ // parcourir la population
        pp parent = p->parent ;
        while(parent) { // parcourir la liste parent
            cpt ++ ; // increment le cpt 
            parent = suivant_personne(parent) ; // avancement 
        }
        p = suivant_famille(p) ; // avancement dans la population
    }
    return cpt ;
}
// un module qui ecrit rapport sur la population et tracer des graphs
void ecrit_rapport_pop(pf head) {
    FILE *graph = fopen("rapport_population.svg", "w"); // creer le fechier qui contient les graph
    if (graph == NULL) { // verifier si le fechier etait bien creer sinon on sort
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    fprintf(graph, "<svg width='2000' height='2000' xmlns='http://www.w3.org/2000/svg'>\n"); // allouer un espace dans la fenêtre
    
    int lenfamille = nbfamille(head) ; // sauvegarder le nombre des familles
    if (lenfamille == 0) lenfamille = 1; // eviter division par zero 
    // le premier graph
    int parents0 = nb_famille_Nparent(head, 0);
    int parents1 = nb_famille_Nparent(head, 1);
    int parents2 = nb_famille_Nparent(head, 2);
    // indiquer les cordoneé de chaque graph
    float y1 = ((float)parents0 / lenfamille) * 300;
    float y2 = ((float)parents1 / lenfamille) * 300;
    float y3 = ((float)parents2 / lenfamille) * 300;
    y1 = (y1 == 0) ? 5 : y1;
    y2 = (y2 == 0) ? 5 : y2;
    y3 = (y3 == 0) ? 5 : y3;
    // l'écriture de titre de fechier 
    fprintf(graph, "<text x='850' y='30' font-family='Arial' font-size='30' text-anchor='middle' fill='black'>Des statistiques sur la population</text>\n");
    // l'eciture de le titre de graph
    fprintf(graph, "<text x='850' y='80' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>1. Statistique sur la population selon le nombre de parents</text>\n");

    // Dessiner les bars
    fprintf(graph, "<rect x='750' y='%.2f' width='50' height='%.2f' fill='blue' />\n", 400 - y1, y1);
    fprintf(graph, "<rect x='850' y='%.2f' width='50' height='%.2f' fill='yellow' />\n", 400 - y2, y2);
    fprintf(graph, "<rect x='950' y='%.2f' width='50' height='%.2f' fill='red' />\n", 400 - y3, y3);

    // ajouter les valeurs de  bars
    fprintf(graph, "<text x='760' y='%.2f' font-size='18' fill='black'>%d</text>\n", 400 - y1 - 10, parents0);
    fprintf(graph, "<text x='860' y='%.2f' font-size='18' fill='black'>%d</text>\n", 400 - y2 - 10, parents1);
    fprintf(graph, "<text x='960' y='%.2f' font-size='18' fill='black'>%d</text>\n", 400 - y3 - 10, parents2);

    // Labels
    fprintf(graph, "<text x='760' y='420' font-size='18' fill='black'>0</text>\n");
    fprintf(graph, "<text x='860' y='420' font-size='18' fill='black'>1</text>\n");
    fprintf(graph, "<text x='960' y='420' font-size='18' fill='black'>2</text>\n");

    // deuxieme graph
    int enfants[6]; // un tableau dans lequel chaque indice contien le nombre de familles compatible avec lui
    for (int i = 0; i < 6; i++) {
        enfants[i] = nb_famille_Nenfants(head, i); // affectation des valeurs
    }
    // l'eciture de le titre de graph
    fprintf(graph, "<text x='850' y='450' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>2. Statistiques sur la population selon le nombre d'enfants</text>\n");

    for (int i = 0; i < 6; i++) {
        // indiquer les cordonés des bars
        float height = ((float)enfants[i] / lenfamille) * 300;
        height = (height == 0) ? 5 : height;
        int x = 550 + i * 100;
        // dessiner les bares
        fprintf(graph, "<rect x='%d' y='%.2f' width='50' height='%.2f' fill='green' />\n", x, 800 - height, height);
        // ajouter les valeurs
        fprintf(graph, "<text x='%d' y='%.2f' font-size='18' fill='black'>%d</text>\n", x + 10, 800 - height - 10, enfants[i]);
        // labels
        fprintf(graph, "<text x='%d' y='820' font-size='18' fill='black'>%d</text>\n", x + 10, i);
    }
    // avec le même principe on creer tout les graphs qui restent
    // graph 3
    int voiture[5]; // // un tableau dans lequel chaque indice contien le nombre de familles compatible avec lui 
    for (int i = 0; i < 5; i++) {
        voiture[i] = nb_famille_Nvoitures(head, i);
    }
    if (lenfamille == 0) lenfamille = 1; // Correction ici

    fprintf(graph, "<text x='850' y='850' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>3. Statistiques sur le nombre de voitures</text>\n");

    for (int i = 0; i < 5; i++) {
        float height = ((float)voiture[i] / lenfamille) * 300;
        height = (height == 0) ? 5 : height;
        int x = 580 + i * 100;
        fprintf(graph, "<rect x='%d' y='%.2f' width='50' height='%.2f' fill='orange' />\n", x, 1200 - height, height);
        fprintf(graph, "<text x='%d' y='%.2f' font-size='18' fill='black'>%d</text>\n", x + 10, 1200 - height - 10, voiture[i]);
        fprintf(graph, "<text x='%d' y='1220' font-size='18' fill='black'>%d</text>\n", x + 10, i);

        
    }

    // graph 4
    int nbH = 0, nbF = 0;
    nbsexe(head, &nbH, &nbF);
    int totale_pop = nbH + nbF;
    if (totale_pop == 0) totale_pop = 1;

    float heightH = ((float)nbH / totale_pop) * 300;
    float heightF = ((float)nbF / totale_pop) * 300;

    fprintf(graph, "<text x='850' y='1250' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>4. Statistiques sur le genre</text>\n");

    fprintf(graph, "<rect x='750' y='%.2f' width='50' height='%.2f' fill='blue' />\n", 1600 - heightH, heightH);
    fprintf(graph, "<rect x='850' y='%.2f' width='50' height='%.2f' fill='pink' />\n", 1600 - heightF, heightF);

    fprintf(graph, "<text x='760' y='%.2f' font-size='18' fill='black'>%d</text>\n", 1600 - heightH - 10, nbH);
    fprintf(graph, "<text x='860' y='%.2f' font-size='18' fill='black'>%d</text>\n", 1600 - heightF - 10, nbF);

    fprintf(graph, "<text x='760' y='1620' font-size='18' fill='black'>H</text>\n");
    fprintf(graph, "<text x='860' y='1620' font-size='18' fill='black'>F</text>\n");

    fprintf(graph, "</svg>\n");
    fclose(graph);
    // creer un file word
    FILE *word = fopen("rapport_populatation.doc","w") ; // creation de fechier 
    // remplir le fechier 
    fputs("Un rapport sur la population \n \n \n",word) ; 
    fprintf(word,"Le nombre totale des personnes dans la populations : %d \n",totale_pop) ;
    fprintf(word,"          Le nombre totale d'hommes dans la populations : %d \n",nbH) ;
    fprintf(word,"          Le nombre totale des femmes dans la populations : %d \n",nbF) ;
    fprintf(word, "Le nombre des parents dans la populations : %d \n",nbParent(head)) ;
    fprintf(word,"          le nombre des familles avec 0 parents : %d \n",parents0) ;
    fprintf(word,"          le nombre des familles avec 1 parents : %d \n",parents1) ;
    fprintf(word,"          le nombre des familles avec 2 parents : %d \n",parents2) ;
    fprintf(word, "Le nombre des enfants dans la populations : %d \n",nbenfant(head)) ;
    for(int i = 0 ; i < 6 ; i ++) {
        fprintf(word ,"          Le nombre des familles avec %d enfanfs : %d \n",i,enfants[i]) ;
    }
    fprintf(word, "Le nombre des voitures dans la populations : %d \n",nbVoiture(head)) ;
    for(int i = 0 ; i < 5 ; i ++) {
        fprintf(word ,"          Le nombre des familles avec %d voitures : %d \n",i,voiture[i]) ;
    }
    fclose(word) ;
    
}

// un module qui compare entre deux populations defferentes
void ecrit_rapport_cop(pf q, pf p) {
    FILE *graph = fopen("rapport_comparaison_population.svg", "w"); // creer le fechier qui contient les graph
    if (graph == NULL) { // verifier si le fechier etait bien creer sinon on sort
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    fprintf(graph, "<svg width='2000' height='2000' xmlns='http://www.w3.org/2000/svg'>\n"); // allouer un espace dans la fenêtre
    
    int lenfamille = nbfamille(q) ; // sauvegarder le nombre des familles
    if (lenfamille == 0) lenfamille = 1; // eviter division par zero 
    // le premier graph
    int parents0 = nb_famille_Nparent(q, 0);
    int parents1 = nb_famille_Nparent(q, 1);
    int parents2 = nb_famille_Nparent(q, 2);
    // indiquer les cordoneé de chaque graph
    float y1 = ((float)parents0 / lenfamille) * 300;
    float y2 = ((float)parents1 / lenfamille) * 300;
    float y3 = ((float)parents2 / lenfamille) * 300;
    y1 = (y1 == 0) ? 5 : y1;
    y2 = (y2 == 0) ? 5 : y2;
    y3 = (y3 == 0) ? 5 : y3;
    // l'écriture de titre de fechier 
    fprintf(graph, "<text x='650' y='30' font-family='Arial' font-size='30' text-anchor='middle' fill='black'>Comparaison entre deux population </text>\n");
    // l'eciture de le titre de graph
    fprintf(graph, "<text x='150' y='150' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>Pop 1</text>\n");
    fprintf(graph, "<text x='850' y='150' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>Pop 2</text>\n");
    fprintf(graph, "<text x='650' y='80' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>1.selon le nombre de parents</text>\n");

    // Dessiner les bars
    fprintf(graph, "<rect x='100' y='%.2f' width='50' height='%.2f' fill='blue' />\n", 400 - y1, y1);
    fprintf(graph, "<rect x='200' y='%.2f' width='50' height='%.2f' fill='yellow' />\n", 400 - y2, y2);
    fprintf(graph, "<rect x='300' y='%.2f' width='50' height='%.2f' fill='red' />\n", 400 - y3, y3);

    // ajouter les valeurs de  bars
    fprintf(graph, "<text x='110' y='%.2f' font-size='18' fill='black'>%d</text>\n", 400 - y1 - 10, parents0);
    fprintf(graph, "<text x='210' y='%.2f' font-size='18' fill='black'>%d</text>\n", 400 - y2 - 10, parents1);
    fprintf(graph, "<text x='310' y='%.2f' font-size='18' fill='black'>%d</text>\n", 400 - y3 - 10, parents2);

    // Labels
    fprintf(graph, "<text x='110' y='420' font-size='18' fill='black'>0</text>\n");
    fprintf(graph, "<text x='210' y='420' font-size='18' fill='black'>1</text>\n");
    fprintf(graph, "<text x='310' y='420' font-size='18' fill='black'>2</text>\n");

    // deuxieme graph
    int enfants[6]; // un tableau dans lequel chaque indice contien le nombre de familles compatible avec lui
    for (int i = 0; i < 6; i++) {
        enfants[i] = nb_famille_Nenfants(q, i); // affectation des valeurs
    }
    // l'eciture de le titre de graph
    fprintf(graph, "<text x='650' y='450' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>2.Selon le nombre d'enfants</text>\n");
    fprintf(graph, "<text x='150' y='520' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>Pop 1</text>\n");
    fprintf(graph, "<text x='850' y='520' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>Pop 2</text>\n");
    for (int i = 0; i < 6; i++) {
        // indiquer les cordonés des bars
        float height = ((float)enfants[i] / lenfamille) * 300;
        height = (height == 0) ? 5 : height;
        int x = 50 + i * 100;
        // dessiner les bares
        fprintf(graph, "<rect x='%d' y='%.2f' width='50' height='%.2f' fill='green' />\n", x, 800 - height, height);
        // ajouter les valeurs
        fprintf(graph, "<text x='%d' y='%.2f' font-size='18' fill='black'>%d</text>\n", x + 10, 800 - height - 10, enfants[i]);
        // labels
        fprintf(graph, "<text x='%d' y='820' font-size='18' fill='black'>%d</text>\n", x + 10, i);
    }
    // avec le même principe on creer tout les graphs qui restent
    // graph 3
    int voiture[5]; // // un tableau dans lequel chaque indice contien le nombre de familles compatible avec lui 
    for (int i = 0; i < 5; i++) {
        voiture[i] = nb_famille_Nvoitures(q, i);
    }
    if (lenfamille == 0) lenfamille = 1; // Correction ici

    fprintf(graph, "<text x='650' y='850' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>3.Selon le nombre de voitures</text>\n");
    fprintf(graph, "<text x='150' y='920' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>Pop 1</text>\n");
    fprintf(graph, "<text x='850' y='920' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>Pop 2</text>\n");
    for (int i = 0; i < 5; i++) {
        float height = ((float)voiture[i] / lenfamille) * 300;
        height = (height == 0) ? 5 : height;
        int x = 80 + i * 100;
        fprintf(graph, "<rect x='%d' y='%.2f' width='50' height='%.2f' fill='orange' />\n", x, 1200 - height, height);
        fprintf(graph, "<text x='%d' y='%.2f' font-size='18' fill='black'>%d</text>\n", x + 10, 1200 - height - 10, voiture[i]);
        fprintf(graph, "<text x='%d' y='1220' font-size='18' fill='black'>%d</text>\n", x + 10, i);

        
    }

    // graph 4
    int nbH = 0, nbF = 0;
    nbsexe(q, &nbH, &nbF);
    int totale_pop = nbH + nbF;
    if (totale_pop == 0) totale_pop = 1;

    float heightH = ((float)nbH / totale_pop) * 300;
    float heightF = ((float)nbF / totale_pop) * 300;

    fprintf(graph, "<text x='650' y='1250' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>4.Selon le genre</text>\n");
    fprintf(graph, "<text x='150' y='1320' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>Pop 1</text>\n");
    fprintf(graph, "<text x='850' y='1320' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>Pop 2</text>\n");
    fprintf(graph, "<rect x='250' y='%.2f' width='50' height='%.2f' fill='blue' />\n", 1600 - heightH, heightH);
    fprintf(graph, "<rect x='350' y='%.2f' width='50' height='%.2f' fill='pink' />\n", 1600 - heightF, heightF);

    fprintf(graph, "<text x='260' y='%.2f' font-size='18' fill='black'>%d</text>\n", 1600 - heightH - 10, nbH);
    fprintf(graph, "<text x='360' y='%.2f' font-size='18' fill='black'>%d</text>\n", 1600 - heightF - 10, nbF);

    fprintf(graph, "<text x='260' y='1620' font-size='18' fill='black'>H</text>\n");
    fprintf(graph, "<text x='360' y='1620' font-size='18' fill='black'>F</text>\n");

    int lenfamille1 = nbfamille(p) ; // sauvegarder le nombre des familles
    if (lenfamille1 == 0) lenfamille1 = 1; // eviter division par zero 
    // le premier graph
    parents0 = nb_famille_Nparent(p, 0);
    parents1 = nb_famille_Nparent(p, 1);
    parents2 = nb_famille_Nparent(p, 2);
    // indipuer les cordoneé de chapue graph
     y1 = ((float)parents0 / lenfamille1) * 300;
     y2 = ((float)parents1 / lenfamille1) * 300;
     y3 = ((float)parents2 / lenfamille1) * 300;
    y1 = (y1 == 0) ? 5 : y1;
    y2 = (y2 == 0) ? 5 : y2;
    y3 = (y3 == 0) ? 5 : y3;
    // l'écriture de titre de fechier 
    // l'eciture de le titre de graph

    // Dessiner les bars
    fprintf(graph, "<rect x='850' y='%.2f' width='50' height='%.2f' fill='blue' />\n", 400 - y1, y1);
    fprintf(graph, "<rect x='950' y='%.2f' width='50' height='%.2f' fill='yellow' />\n", 400 - y2, y2);
    fprintf(graph, "<rect x='1050' y='%.2f' width='50' height='%.2f' fill='red' />\n", 400 - y3, y3);

    // ajouter les valeurs de  bars
    fprintf(graph, "<text x='860' y='%.2f' font-size='18' fill='black'>%d</text>\n", 400 - y1 - 10, parents0);
    fprintf(graph, "<text x='960' y='%.2f' font-size='18' fill='black'>%d</text>\n", 400 - y2 - 10, parents1);
    fprintf(graph, "<text x='1060' y='%.2f' font-size='18' fill='black'>%d</text>\n", 400 - y3 - 10, parents2);

    // Labels
    fprintf(graph, "<text x='860' y='420' font-size='18' fill='black'>0</text>\n");
    fprintf(graph, "<text x='960' y='420' font-size='18' fill='black'>1</text>\n");
    fprintf(graph, "<text x='1060' y='420' font-size='18' fill='black'>2</text>\n");

    // deuxieme graph
     // un tableau dans lepuel chapue indice contien le nombre de familles compatible avec lui
    for (int i = 0; i < 6; i++) {
        enfants[i] = nb_famille_Nenfants(p, i); // affectation des valeurs
    }
    // l'eciture de le titre de graph

    for (int i = 0; i < 6; i++) {
        // indipuer les cordonés des bars
        float height = ((float)enfants[i] / lenfamille1) * 300;
        height = (height == 0) ? 5 : height;
        int x = 700 + i * 100;
        // dessiner les bares
        fprintf(graph, "<rect x='%d' y='%.2f' width='50' height='%.2f' fill='green' />\n", x, 800 - height, height);
        // ajouter les valeurs
        fprintf(graph, "<text x='%d' y='%.2f' font-size='18' fill='black'>%d</text>\n", x + 10, 800 - height - 10, enfants[i]);
        // labels
        fprintf(graph, "<text x='%d' y='820' font-size='18' fill='black'>%d</text>\n", x + 10, i);
    }
    // avec le même principe on creer tout les graphs pui restent
    // graph 3
    // // un tableau dans lepuel chapue indice contien le nombre de familles compatible avec lui 
    for (int i = 0; i < 5; i++) {
        voiture[i] = nb_famille_Nvoitures(p, i);
    }
    if (lenfamille1 == 0) lenfamille1 = 1; // Correction ici


    for (int i = 0; i < 5; i++) {
        float height = ((float)voiture[i] / lenfamille1) * 300;
        height = (height == 0) ? 5 : height;
        int x = 700 + i * 100;
        fprintf(graph, "<rect x='%d' y='%.2f' width='50' height='%.2f' fill='orange' />\n", x, 1200 - height, height);
        fprintf(graph, "<text x='%d' y='%.2f' font-size='18' fill='black'>%d</text>\n", x + 10, 1200 - height - 10, voiture[i]);
        fprintf(graph, "<text x='%d' y='1220' font-size='18' fill='black'>%d</text>\n", x + 10, i);

        
    }

    // graph 4
    nbH = 0, nbF = 0;
    nbsexe(p, &nbH, &nbF);
    totale_pop = nbH + nbF;
    if (totale_pop == 0) totale_pop = 1;

    heightH = ((float)nbH / totale_pop) * 300;
    heightF = ((float)nbF / totale_pop) * 300;


    fprintf(graph, "<rect x='850' y='%.2f' width='50' height='%.2f' fill='blue' />\n", 1600 - heightH, heightH);
    fprintf(graph, "<rect x='950' y='%.2f' width='50' height='%.2f' fill='pink' />\n", 1600 - heightF, heightF);

    fprintf(graph, "<text x='860' y='%.2f' font-size='18' fill='black'>%d</text>\n", 1600 - heightH - 10, nbH);
    fprintf(graph, "<text x='960' y='%.2f' font-size='18' fill='black'>%d</text>\n", 1600 - heightF - 10, nbF);

    fprintf(graph, "<text x='860' y='1620' font-size='18' fill='black'>H</text>\n");
    fprintf(graph, "<text x='960' y='1620' font-size='18' fill='black'>F</text>\n");
    fprintf(graph, "</svg>\n");
    fclose(graph);
    
}
// une fonction pour exporter les membres de la population sous un un fechier .txt
void exportTxT(pf head) {
    FILE  * fichier = fopen("population.txt", "w"); // ouvrir le fichier en mode écriture
    if (fichier == NULL) { // verifier si le fichier etait bien ouvert
        perror("Erreur lors de l'ouverture du fichier");
        return;
    } ;
    pf p = head ; // sauvegarder la tête
    fputs("les familles de la population : \n",fichier) ; // ecrire le titre
    fputs("Nom de famille : Parents : Enfants : Voitures : \n",fichier) ; // ecrire les titres des colonnes
    while(p) { // parcourir la population
        fputs(p->nom,fichier) ; // ecrire le nom de famille
        fputs(" : ",fichier) ; // ecrire le séparateur
        pp parent = p->parent ; // sauvegarder la tête de la liste parent
        if(parent == NULL) fputs("/",fichier) ; // si la famille n'a pas de parent
        while(parent) { // parcourir la liste parent
            fputs(parent->prenom,fichier) ; // ecrire le nom de parent
            fprintf(fichier,";%c",parent->sexe) ;
            if(suivant_personne(parent)) fputs(" ",fichier) ; // ecrire le séparateur
            parent = suivant_personne(parent) ; // avancer dans la liste parent
            if(parent != NULL) fputs(",",fichier) ; // ecrire le séparateur
        }
        fputs(" : ",fichier) ; // ecrire le séparateur
        pp enfant = p->enfant ; // sauvegarder la tête de la liste enfant
        if(enfant == NULL) fputs("/",fichier) ; // si la famille n'a pas d'enfant
        while(enfant) { // parcourir la liste enfant
            fputs(enfant->prenom,fichier) ; // ecrire le nom de enfant
            fprintf(fichier,";%c",enfant->sexe) ;
            if(suivant_personne(enfant)) fputs(" ",fichier) ; // ecrire le séparateur
            enfant = suivant_personne(enfant) ; // avancer dans la liste enfant
            if(enfant != NULL) fputs(",",fichier) ; // ecrire le séparateur
        }
        fputs(" : ",fichier) ; // ecrire le séparateur
        pv voiture = p->voiture ; // sauvegarder la tête de la liste voiture
        if(voiture == NULL) fputs("/",fichier) ; // si la famille n'a pas de voiture
        while(voiture) { // parcourir la liste voiture
            fputs(voiture->marque,fichier) ; // ecrire la marque de voiture
            fprintf(fichier,";%s",voiture->nemero) ;
            if(suivant_voiture(voiture)) fputs(" ",fichier) ; // ecrire le séparateur
            voiture = suivant_voiture(voiture) ; // avancer dans la liste voiture
            if(voiture != NULL) fputs(",",fichier) ; // ecrire le séparateur
        }
        fputs("\n",fichier) ; // sauter la ligne
        p = suivant_famille(p) ; // avancer dans la population
    }
    fclose(fichier) ; // fermer le fichier
}


// Un module qui cree un acte de naissance 
void cert_naissance(pf p, pp q) {
    FILE *cert = fopen("cert.doc", "w"); // ouvrir le fechier 
    if (cert == NULL) { // verification d'etat d'ouverture
        printf("Erreur lors de l'ouverture du fichier !\n");
        return;
    }

    printf("Entrez la date de naissance sous la forme YYYY-MM-DD: ");
    ch20 date;
    scanf("%s", date); // lecture de la date de naissance
    getchar();

    printf("Entrer le lieu de naissance : ");
    ch20 lieu;
    scanf("%s", lieu); // lecture de le lieu de naissance
    getchar();

    // remplir des donnés
    fputs("                             شهادة ميلاد  \n \n \n \n", cert);
    fputs("matricule :  \n ", cert);
    fputs("243251 \n \n \n", cert);
    fprintf(cert, " Le : %s \n \n \n", date);
    fprintf(cert, " l'heure : //                                     Commune : %s   \n \n \n", lieu);
    fprintf(cert, " Daira : %s                                      Wilaya : %s\n \n \n", lieu, lieu);
    fprintf(cert, " Nom complet : %s %s \n \n \n",p->nom , q->prenom);
    fprintf(cert, " Sexe : %c \n \n", q->sexe);
    fprintf(cert, " Fils de : %s \n \n \n", p->parent ? p->parent->prenom : "Inconnu");
    if (p->parent && p->parent->suivant != NULL) {
        fprintf(cert, " et : %s   \n \n \n", p->parent->suivant->prenom);
    } else {
        fprintf(cert, " et : //      \n \n \n");
    }
    // Ajout de la date actuelle
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);
    fputs("----------------------------------------------------------------------\n",cert) ;
    fputs("----------------------------------------------------------------------\n",cert) ;
    fputs("----------------------------------------------------------------------\n",cert) ; 
    fprintf(cert, "\n                       %02d-%02d-%04d : حررت بالجزائر العاصمة يوم\n",
            local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900);

    fclose(cert);
    printf("Certificat de naissance généré avec succès dans 'cert.doc'.\n");
}

// un module qui verife que le field n'est pas null (par example parent != '/')
bool not_Nil(char *str,int len){
    for(int i = 0 ; i < len ; i++){
        if(str[i]== '/') return false ;
    }
    return true ;
}

// un module qui extraire le sexe d'apres une chaine
char extract_sex(char *str, int len) {
    for(int i = 0 ; i < len ; i ++){
        if(str[i]=='F'|| str[i]=='M'){
            if(str[i]=='M') {
                return 'M' ;
            }else {
                return 'F' ;
            }
        } 
    }
    return '0' ;
}

// un module pour décompose un field en deux fields
void exrtact_sub_fields(char * field ,ch20 *a , ch20 *b){
    char * sub = strtok(field,";") ;
    strcpy(*a,sub) ;
    sub = strtok(NULL,";") ;
    strcpy(*b,sub) ;
}

// une fonction qui supprime les espaces around une chaine (ex : input : ' jalil ' , output : 'jalil' )
char *delete_space_around(char str[]){
    if(str[0]==' ') memmove(str,str+1,strlen(str)) ;
    if(str[strlen(str)-1]==' ') str[strlen(str)-1] = '\0' ;
    return str ;
}

// une fonction pour creer une liste person d'apres une chaine avec des delims معروفة
pp import_person(char field[]) {
    if(!not_Nil(field,strlen(field))) return NULL ; 
    pp head , current , temp ;
    head = current = temp = NULL ;
    char tab_sub_fields[6][30]  ;
    char *sub_field = strtok(field,",") ;
    strcpy(tab_sub_fields[0],sub_field) ;
    int i = 1 ;
    sub_field = strtok(NULL,",") ;
    while(sub_field != NULL) {
        strcpy(tab_sub_fields[i++],sub_field) ;
        sub_field = strtok(NULL,",") ;
    }
    for(int j = 0 ; j < i ; j ++) {
        allouer_personne(&current) ;
        ch20 pr , sex ;
        exrtact_sub_fields(tab_sub_fields[j],&pr,&sex) ;
        strcpy(pr,delete_space_around(pr)) ;
        strcpy(current->prenom,pr) ;
        current->sexe = extract_sex(sex,strlen(sex)) ;
        current->suivant = NULL ;
        if(head == NULL) {
            head = current ;
            temp = current ;
        }else {
            temp->suivant = current ;
            temp = current ;
        }
    }
    return head ;
}

// une fonction pour creer une liste voiture d'apres une chaine avec des delims معروفة
pv import_voiture(char field[]) {
    if(!not_Nil(field,strlen(field))) return NULL ; 
    pv head , current , temp ;
    head = current = temp = NULL ;
    char tab_sub_fields[5][40]  ;
    char *sub_field = strtok(field,",") ;
    strcpy(tab_sub_fields[0],sub_field) ;
    int i = 1 ;
    sub_field = strtok(NULL,",") ;
    while(sub_field != NULL) {
        strcpy(tab_sub_fields[i++],sub_field) ;
        sub_field = strtok(NULL,",") ;
    }
    for(int j = 0 ; j < i ; j ++) {
        allouer_voiture(&current) ;
        ch20 marq , matr ;
        exrtact_sub_fields(tab_sub_fields[j],&marq,&matr) ;
        strcpy(marq,delete_space_around(marq)) ;
        strcpy(matr,delete_space_around(matr)) ;
        aff_voiture(current,marq,matr) ;
        current->suivant = NULL ;
        if(head == NULL) {
            head = current ;
            temp = current ;
        }else {
            temp->suivant = current ;
            temp = current ;
        }
    }
    current->nemero[strlen(current->nemero)-1] = '\0' ;
    return head ;
}

// une fonction qui lire les donnes d'une population et la creer
pf import_famille() {
    FILE * fichier = fopen("data.txt","r") ;
    if(fichier == NULL) {
        printf("Ereure dans l'overture de fichier") ;
        return NULL ;
    }
    char line[300] ;
    char fields[4][120] ;
    char *str ;
    pf current , temp , head ;
    current = temp = head = NULL ;
    while(fgets(line , sizeof(line),fichier)){
        str = strtok(line,":") ;
        strcpy(fields[0],str) ;
        str = strtok(NULL,":") ;
        for(int i = 1 ; i < 4 ; i++){
            strcpy(fields[i],str) ;
            str = strtok(NULL,":") ;
        }
        allouer_famille(&current) ;
        aff_famille(current,delete_space_around(fields[0]),import_person(fields[1]),import_person(fields[2]),import_voiture(fields[3])) ;
        aff_adresse_famille(current,NULL) ;
        if(head == NULL) {
            head = current ;
            temp  = current ;
        }else {
            aff_adresse_famille(temp,current) ;
            temp = current ;
        }
    }
    return head ;
}


