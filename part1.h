#ifndef PART1_H
#define PART1_H

// Structure definition
typedef char ch20[20];
struct famille1 {
    ch20 nomfam;
    struct famille1* prochaine; 
};

// Function declarations
void allouer(struct famille1 **p);// procedure pour allouer une case mémoire
void aff_nom(struct famille1 *pop, char *nom); // procdure pour l'affectation des noms
void aff_adresse(struct famille1 *head_dest, struct famille1 *head_source);// procedure pour l'affectation des adresses
char* nom_fam(struct famille1 *pop);// fonction qui retourne le nom 
struct famille1 *proc(struct famille1 *pop);// fonction qui retourne l'adresse de maillon prochain
void liberer(struct famille1 *p);// fonction pour libirer tout les cases mémoire alloué par une liste


bool present_nonTrie(struct famille1 *pop, char *nom); // Fonction qui verifier si une famille existe dans le pop (le pop n'est pas trie)
bool existe(int *arr, int size, int val); //Fonction qui indique si un nom du tableau existe dans la liste (son indice a déjà était utilisé)
struct famille1 *creer_pop(int N); //Fonction qui permet de creer une liste de N noms aleatoires 
int nbfamille1(struct famille1* pop); //Fonction qui calcule le nombre des famille1s (longueur de la liste)
bool ordre_alpha(char chaine1[], char chaine2[], int pos);//Fonction qui permet de detecter si deux chaine sont dans l'ordre alphabetique (chaine1<chaine2 => vrai)
void trier_pop(struct famille1* pop);//Module qui permet de trier une liste de nom dans l'ordre alphabetique
struct famille1* present(struct famille1 * pop, char *nom); //Fonction qui retourne l'adresse d'une famille1 si elle existe (null sinon)
void inser(struct famille1 **pop, char *nom); // Un module utilisé pour inserer une famille1 dans la liste si elle n'existe pas
void supp(struct famille1** pop, char* nom); //Module qui permet de suprimer une famille1 de la liste si elle existe


void afficher_pop1(struct famille1 *pop);//Module qui permet d'afficher une liste de noms
void inser_n_fam_m(struct famille1 **fam, int n);//Fonction qui permet d'inserer n familles manuellement a la fois dans une population triee
void inser_n_fam_a(struct famille1** fam,int n); //Fonction qui permet d'inserer n famille automatiquement (aleatoirement) dans une population triee
struct famille1* fusion_pops(struct famille1 *pop1,struct famille1 *pop2); //Fonction qui permet de fusionner 2 populations
struct famille1* creer_pop_manuel(int n); //Fonction qui permet de creer une population manuellement
struct famille1* copier_liste(struct famille1 *original); //Fonction qui permet de copier une liste (si on souhaite voir le resultat d'une modification sans modifier la liste original, utilise dans la fusion)
char * eff_espace(char * word); //Fonction qui permet d'effacer les espaces avant et apres une chaine
struct famille1* creer_fichier(); //Fonction qui permet de creer une liste a partir d'un fichier avec '/' comme separateur
void export_pop(struct famille1 *pop); //Fonction qui permet d'exporter la population avec '/' comme separateur

#endif /* PART1_H */