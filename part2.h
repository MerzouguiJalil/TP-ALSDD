#ifndef PART2_H
#define PART2_H

// Structure definitions
typedef char ch20[20];

struct personne {
    ch20 prenom;
    char sexe;
    struct personne * suivant;
};
typedef struct personne * pp;

struct voiture {
    ch20 marque;
    ch20 nemero;
    struct voiture *suivant;
};
typedef struct voiture * pv;

struct famille {
    ch20 nom;
    pp parent;
    pp enfant;
    pv voiture;
    struct famille *suivant;
};
typedef struct famille * pf;


            /***** Amelioration de la structure *****/
typedef struct nouvelle_fam{
    ch20 nom_fam;
    pp parents;
    pp enfants;
    pv voitures;
    pv voitures_volees;
    struct nouvelle_fam* suivant;
} *pnf;


// Function declarations

// 1.La machine abstraite
void allouer_famille(pf *p); // procedure qui alloue une case mémoir suffisante pour une famille 
void allouer_personne(pp *p);// procedure qui alloue une case mémoir suffisante pour une personne
void allouer_voiture(pv *p);// procedure qui alloue une case mémoir suffisante pour une voiture
void aff_person(pp p, ch20 prenom, char sexe); // procedure pour remplir un maillon personne
void aff_famille(pf p, ch20 nom, pp parent, pp enfant, pv voiture); // procedure pour remplir un maillon famille
void aff_voiture(pv p, ch20 marque, ch20 numero); // procedure pour remplir un maillon voiture
void aff_adress_person(pp p, pp suivant); // procedure pour affecter l'adress de prochain maillon personne
void aff_adresse_voiture(pv p, pv suivant); // procedure pour affecter l'adress de prochain maillon voiture
void aff_adresse_famille(pf p, pf suivant); // procedure pour affecter l'adress de prochain maillon famille
pp suivant_personne(pp p); // fonction qui retourne l'adresse de prochain maillon personne
pv suivant_voiture(pv p); // fonction qui retourne l'adresse de prochain maillon voiture
pf suivant_famille(pf p); // fonction qui retourne l'adresse de prochain maillon famille
void val_persone(pp p, ch20 * prenom, char * sexe); // procedure qui retourne le contenue d'un maillon personne
void val_voiture(pv p, ch20 * marque, ch20 *numero); // procedure qui retourne le contenue d'un maillon voiture
void val_famille(pf p, ch20 * nom, pp * parent, pp * enfant, pv * voiture); // procedure qui retourne le contenue d'un maillon famille
void liberer_person(pp head); // procedure qui liberer tout les cases memoires alloué par la liste personne
void liberer_voiture(pv head); // procedure qui liberer tout les cases memoires alloué par la liste voiture
void liberer_famille(pf head); // procedure qui liberer tout les cases memoires alloué par la liste famille
pp creer_personne(int N, bool parent, int np, pp par); // fonction pour creer une liste personne de N maillon et retourner l'adresse de la tête
pv creer_voiture(int N);// fonction pour creer une liste personne de N maillon et retourner l'adresse de la tête
pf creer_famille(int N); // fonction pour creer une liste personne de N maillon et retourner l'adresse de la tête




// 2.Les modules demandés
int nbfamillesansparent(pf pop) ; //Fonction qui permet de calculer le nombres des familles sans parents dans pop
int nbenfant(pf pop) ;  //Fonction qui permet de calculer le nombre des enfants dans pop
int nbenfnomfam(pf pop, ch20 nomfam) ; //Fonction qui permet de calculer le nombre d'enfants dans une famille
void naissanceTrie(pf pop,ch20 nomfam, ch20 prenom, char sexe) ; //module qui permet d'inserer un nouveau ne d'une famille donnee
pf RechFamVoit_1(pf head, ch20 numero); // fonction qui renvoie l’adresse de la famille possédant cette voiture si son numéro appartient à pop
pnf RechFamVoit_2 (pnf pop, ch20 matricule); // fonction qui renvoie l’adresse de la famille possédant cette voiture si son numéro appartient à pop apres amelioration de la structure
void treer_famille(pf head) ; // procedure pour mettre la liste famille en ordre alphabétique





// 3.Des modules additionnels
bool existe_str(ch20 *arr, int size ,ch20 str); //Fonction qui renvoie vrai si une chaine existe dans un tableau de chaine
bool existe_str_liste(pp par,pp enf,ch20 str) ;//Fonction qui renvoie vrai si le nom d'un enfant existe deja dans la famille (pour designer la possibilite d'insertion)
void demenager_famille(pf *pop1, pf *pop2);//Fonction qui permet de demenager une famille de pop1 vers pop2
pp creer_personne_manuel(int N, bool parent, int np, pp par);//Fonction qui permet de creer une liste d'enfants ou de parents manuellement
pv creer_voiture_manuel(int N);//Fonction qui permet de creer une liste de voiture manuellement
pf creer_famille_manuel(int N);//Fonction qui permet de creer une population manuellement
int nbParent(pf head) ; //Fonction qui permet de calculer le nombre des parents dans pop
int nbVoiture(pf head); //Fonction qui permet de calculer le nombre des voitures dans pop
void print_famille1(pf fam); // un module qui affiche les cordonnés d'une famille
void nbsexe(pf head , int *nbH , int *nbF) ; //procedure qui permet de calcueler le nombre des femmes et d'hommes dans pop
int nb_famille_Nvoitures(pf head,int N) ; // foncion qui permet de calculer le nombre des famille qui ont N voitures
int nb_famille_Nenfants(pf head,int N) ;// fonction qui calcule le nombre des familles qui ont N enfants
int nb_famille_Nparent(pf head,int N) ;// fonction qui calcule le nombre des familles qui ont N parents
void supp_famille(pf *head, char* nom) ; //Module qui permet de suprimer une famille1 de la liste si elle existe
pp remplire_parent(int N) ; // une fonction pour creer une liste parent manuellement
pp remplire_enfant(pp fam,int N) ; // une fonction pour remplir une liste d'enfant manuellement 
pv remplire_voituer(int N) ; // une fonction pour remplir une liste voiture manuellement
bool reinserer(); //Fonction qui renvoie vrai si l'utilisateur veut reinserer un nom existant
void inserer_famille(pf *pop, ch20 nom, pp parents,pp enfants, pv voitures ) ;// Un module utilisé pour inserer une famille1 dans la liste si elle n'existe pas
pv inserer_voiture(pv head, ch20 marque, ch20 matricule) ;
pv supprimer_voiture(pv head, ch20 matricule)  ;
pp supprimer_enfant(pp head, ch20 prenom) ;
void supprimer_parent(pf famille, char sexe,bool *ext)  ;
pp copier_personne(pp original) ;
pv copier_voit(pv original); 
pf copier_pop(pf pop) ;
pf fusion1(pf pop1,pf pop2) ;
void Color(int couleurDuTexte,int couleurDeFond); // fonction d'affichage de couleurs
void ecrit_rapport_vol(pf p) ; // un module qui creer un rapport sur la voiture voleé
int nbfamille(pf pop) ; // un module qui calcule le nombre des familles dans la population
void ecrit_rapport_pop(pf head) ; // un module qui ecrit rapport sur la population et tracer des graphs
void ecrit_rapport_cop(pf q, pf p) ; // un module qui compare entre deux populations defferentes
void exportTxT(pf head) ; // une fonction pour exporter les membres de la population sous un un fechier .txt
bool present_famille_nonTrie(pf pop, char *nom) ; // Fonction qui verifier si une famille existe dans le pop (le pop n'est pas trié)  
pf present_famille(pf pop, char *nom) ;
void clear_screen() ;
void moveCursorToTop() ;
pp import_person(char field[]); // une fonction pour creer une liste person d'apres une chaine avec des delims معروفة
pv import_voiture(char field[]); // une fonction pour creer une liste voiture d'apres une chaine avec des delims معروفة 
pf import_famille() ;// une fonction qui lire les donnes d'une population et la creer
char *delete_space_around(char str[]) ; // une fonction qui supprime les espaces around une chaine (ex : input : ' jalil ' , output : 'jalil' )
void exrtact_sub_fields(char * field ,ch20 *a , ch20 *b) ; // un module pour décompose un field en deux fields
char extract_sex(char *str, int len) ; // un module qui extraire le sexe d'apres une chaine
bool not_Nil(char *str,int len) ; // un module qui verife que le field n'est pas null (par example parent != '/')
void cert_naissance(pf p, pp q) ; // un module qui creer un acte de naissance 

#endif /* PART2_H */