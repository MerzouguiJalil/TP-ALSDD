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
#define DELAY 10000
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



// Module qui permet de recuperer le choix de l'utilisateur a partir du clavier et / ou de la souris
int detecte( int *cpt , int taille , bool * enter) {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD events, saveMode;
    INPUT_RECORD inputRecord[128];
    bool stop = false ;

    // Sauvegarde du mode actuel et activation du mode console
    GetConsoleMode(hInput, &saveMode);
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT);

    while (!stop) {
        // Lire les événements en attente
        ReadConsoleInput(hInput, inputRecord, 128, &events);

        for (DWORD i = 0; i < events; i++) {
            switch (inputRecord[i].EventType) {
                case KEY_EVENT: {
                    KEY_EVENT_RECORD keyEvent = inputRecord[i].Event.KeyEvent;

                    if (keyEvent.bKeyDown) { // Key is pressed down
                        // Restaurer le mode d'origine
                        SetConsoleMode(hInput, saveMode);
                        switch (keyEvent.wVirtualKeyCode) {
                            case VK_UP:
                                (*cpt)--;
                                if(*cpt<1) *cpt=taille;
                                return -1;
                            case VK_DOWN:
                                (*cpt)++;
                                if(*cpt > taille) *cpt=1;
                                return -1;
                            case VK_RETURN: // Enter key
                                *enter = true;
                                return -1;
                        }
                    }
                }
                case MOUSE_EVENT: {
                    MOUSE_EVENT_RECORD mouseEvent = inputRecord[i].Event.MouseEvent;
                    if (mouseEvent.dwEventFlags == MOUSE_MOVED) {
                        break ;  // Ignore et recommence la boucle
                    }
                    int y = mouseEvent.dwMousePosition.Y;
                    SetConsoleMode(hInput, saveMode);
                    // Detection du clic sur une option
                    switch (y) {
                        case 7: return 1;
                        case 8: return 2;
                        case 9: return 3;
                        case 10: return 4;
                        case 11: return 5;
                        case 12: return 6;
                        case 13: return 7;
                        case 14: return 8;
                        case 15: return 9;
                        case 16: return 10;
                        case 17: return 11 ;
                        case 18: return 12 ;
                        case 19: return 13 ;
                        case 20: return 14 ;
                        default: return -1;
                    }
                }

            }
        }
        // Vider le buffer pour éviter les événements en attente
        FlushConsoleInputBuffer(hInput);
    }

}

bool choix(){
    printf(GREEN"\n\n    OUI                      "RED"                             NON \n"RESET);
    int ch;
    while ((ch = _getch()) != 27 ) {
        if (ch == 0 || ch == 224) {
            ch = _getch();
                if (ch==75) return true;
                else if (ch==77) return false;
        }
    }
}

//confirmation des actions
bool confirmation(){ //1 pour oui / 0 pour non
    clear_screen() ;
    Color(4,0);
    printf("                         "YELLOW" -> "RESET"Etes-vous sur d'effectuer cette action? \n\n");
    printf("               Continuer                                                   Annuler \n\n");
    int ch;
    while ((ch = _getch()) != 27 ) {
        if (ch == 0 || ch == 224) {
            ch = _getch();
            switch (ch){
                case 75:
                    moveCursorToTop();
                    printf("                         "YELLOW" -> "RESET"Etes-vous sur d'effectuer cette action? \n\n");
                    printf(GREEN"               Continuer          "RESET"                                         Annuler \n\n");
                    sleep(1);
                    break;
                case 77:
                    moveCursorToTop();
                    printf("                         "YELLOW" -> "RESET"Etes-vous sur d'effectuer cette action? \n\n");
                    printf("               Continuer                                      "GREEN"             Annuler \n\n"RESET);
                    sleep(1);
                    break;
            }
                if (ch==75) return true;
                else if (ch==77) return false;
        }
    }
}

bool methode_ins(){ //1 pour manuellement/ 0 pour automatiquement
    clear_screen() ;
    printf("                         "YELLOW" -> "RESET"Comment voulez-vous effectuer l'insertion? \n\n");
    printf("              Manuellement                                    Automatiquement(aleatoirement)\n\n");
    int ch;
    while ((ch = _getch()) != 27 ) {
        if (ch == 0 || ch == 224) {
            ch = _getch();
            switch (ch){
                case 75:
                    moveCursorToTop();
                    printf("                         "YELLOW" -> "RESET"Comment voulez-vous effectuer l'insertion? \n\n");
                    printf(GREEN"              Manuellement           "RESET"                         Automatiquement(aleatoirement)\n\n");
                    sleep(1);
                    break;
                case 77:
                    moveCursorToTop();
                    printf("                         "YELLOW" -> "RESET"Comment voulez-vous effectuer l'insertion? \n\n");
                    printf("              Manuellement                 "GREEN"                   Automatiquement(aleatoirement)\n\n"RESET);
                    sleep(1);
                    break;
            }
                if (ch==75) return true;
                else if (ch==77) return false;
        }
    }
}

bool manip(){ //1 pour pop1/ 0 pour pop2
    clear_screen() ;
    printf("                       "YELLOW" -> "RESET"Voulez-vous utiliser la 1ere ou la 2eme population? \n");
    printf("                  Pop1 (<-)                                              pop2 (->)\n\n");
    int ch;
    while ((ch = _getch()) != 27 ) {
        if (ch == 0 || ch == 224) {
            ch = _getch();
                switch (ch){
                    case 75:
                        moveCursorToTop();
                        printf("                       "YELLOW" -> "RESET"Voulez-vous utiliser la 1ere ou la 2eme population? \n");
                        printf(GREEN"                  Pop1 (<-)            "RESET"                                  pop2 (->)\n\n");
                        sleep(1);
                        return true;
                    case 77:
                        moveCursorToTop();
                        printf("                       "YELLOW" -> "RESET"Voulez-vous utiliser la 1ere ou la 2eme population? \n");
                        printf("                  Pop1 (<-)              "GREEN"                                pop2 (->)\n\n"RESET);
                        sleep(1);
                        return false;
                }
        }
    }
}

bool ecraser(){ //1 pour ecraser/ 0 pour nouveau
    clear_screen() ;
    printf("                "YELLOW" -> "RESET"         Voulez-vous ecraser la premiere liste? \n\n");
    printf("             Oui ecraser (<-)                           Non creer une 2eme population (->)\n\n");

    int ch;
    while ((ch = _getch()) != 27 ) {
        if (ch == 0 || ch == 224) {
            ch = _getch();
            switch (ch){
                case 75:
                    moveCursorToTop();
                    printf("                "YELLOW" -> "RESET"         Voulez-vous ecraser la premiere liste? \n\n");
                    printf(GREEN"             Oui ecraser (<-)       "RESET"                    Non creer une 2eme population (->)\n\n");
                    sleep(1);
                    break;
                case 77:
                    moveCursorToTop();
                    printf("                "YELLOW" -> "RESET"         Voulez-vous ecraser la premiere liste? \n\n");
                    printf("             Oui ecraser (<-)         "GREEN"                  Non creer une 2eme population (->)\n\n"RESET);
                    sleep(1);
                    break;
            }
                if (ch==75) return true;
                else if (ch==77) return false;
        }
    }
}

char methode_cr(){ //M pour Manuellement/ A pour automatiquement/ F pour fichier
    clear_screen() ;
    printf("                      "YELLOW" -> "RESET"   Comment voulez-vous effectuer la creation? \n\n");
    printf("             Manuellement(<-)                                  Automatiquement(aleatoirement)(->)\n                                    A partir d'un fichier(v)\n\n");
    int ch;
    while ((ch = _getch()) != 27 ) {
        if (ch == 0 || ch == 224) {
            ch = _getch();
            switch (ch){
                case 75:
                    moveCursorToTop();
                    printf("                      "YELLOW" -> "RESET"   Comment voulez-vous effectuer la creation? \n\n");
                    printf(GREEN"             Manuellement(<-)          "RESET"                        Automatiquement(aleatoirement)(->)\n                                    A partir d'un fichier(v)\n\n");
                    sleep(1);
                    break;
                case 77:
                    moveCursorToTop();
                    printf("                      "YELLOW" -> "RESET"   Comment voulez-vous effectuer la creation? \n\n");
                    printf("             Manuellement(<-)                            "GREEN"      Automatiquement(aleatoirement)(->)\n    "RESET"                                A partir d'un fichier(v)\n\n");
                    sleep(1);
                    break;
                case 80:
                    moveCursorToTop();
                    printf("                      "YELLOW" -> "RESET"   Comment voulez-vous effectuer la creation? \n\n");
                    printf("             Manuellement(<-)                                  Automatiquement(aleatoirement)(->)\n                   "GREEN"                 A partir d'un fichier(v)"RESET"\n\n");
                    sleep(1);
                    break;
            }
                if (ch==75) return 'M';
                else if (ch==77) return 'A';
                    else if (ch==80) return 'F';
        }
    }
    return 'E';
}

char methode_fu(){ //1 pour pop1/ 2 pour pop2 /3 pour pop3
    clear_screen() ;
    printf("                       "YELLOW" -> "RESET"  Comment voulez-vous effectuer la fusion? \n\n");
    printf("              Resultat dans pop1(<-)                      Resultat dans pop2(->)\n                              Resultat dans une 3eme liste pop3(v)\n\n");
    int ch;
    while ((ch = _getch()) != 27 ) {
        if (ch == 0 || ch == 224) {
            ch = _getch();
            switch (ch){
                case 75:
                    moveCursorToTop();
                    printf("                       "YELLOW" -> "RESET"  Comment voulez-vous effectuer la fusion? \n\n");
                    printf("             "GREEN"  Resultat dans pop1(<-)    "RESET"                  Resultat dans pop2(->)\n                               Resultat dans une 3eme liste pop3(v)\n\n");
                    sleep(1);
                    break;
                case 77:
                    moveCursorToTop();
                    printf("                     "YELLOW" -> "RESET"  Comment voulez-vous effectuer la fusion? \n\n");
                    printf("               Resultat dans pop1(<-)                 "GREEN"     Resultat dans pop2(->)\n    "RESET"                            Resultat dans une 3eme liste pop3(v)\n\n");
                    sleep(1);
                    break;
                case 80:
                    moveCursorToTop();
                    printf("                      "YELLOW" -> "RESET"  Comment voulez-vous effectuer la fusion? \n\n");
                    printf("               Resultat dans pop1(<-)                      Resultat dans pop2(->)\n                 "GREEN"               Resultat dans une 3eme liste pop3(v)"RESET"\n\n");
                    sleep(1);
                    break;
            }
                if (ch==75) return '1';
                else if (ch==77) return '2';
                    else if (ch==80) return '3';
        }
    }
    return 'E';
}


void menu_1(int *choix){
    int ch,cpt=0;

    printf("                                    _______________________________________________________    \n ");
    printf("                                  |                                                        |   \n ");
    printf("                                  |                "YELLOW"  Menu de la PARTIE-I     "RESET"              |   \n ");
    printf("                                  |                                                        |   \n ");
    printf("                                  |                                                        |   \n ");
    printf("                                  |         Veuillez choisir parmi ces options:            |   \n ");
    printf("                                  |                                                        |   \n ");
    printf("                                  |  1. Creer une population .                             |   \n ");
    printf("                                  |  2. Afficher la population creee .                     |   \n ");
    printf("                                  |  3. Trier la population deja creee .                   |   \n ");
    printf("                                  |  4. Calculer le nombre de familles dans la population .|   \n ");
    printf("                                  |  5. Rechercher une famille dans la population .        |   \n ");
    printf("                                  |  6. Inserer N familles .                               |   \n ");
    printf("                                  |  7. Supprimer une famille .                            |   \n ");
    printf("                                  |  8. Fusionner 2 populations .                          |   \n ");
    printf("                                  |  9. Exporter la population .                           |   \n ");
    printf("                                  |  10. Retour au menu principal .                        |   \n ");
    printf("                                  |  "RED"11. Quitter .   "RESET"                                      |   \n ");
    printf("                                  |                                                        |   \n ");
    printf("                                  |________________________________________________________|   \n\n ");
    bool enter =false ;
    while (!enter){
        *choix = detecte(&cpt , 11,&enter) ;
        if (*choix > 0) return ;
            switch(cpt){
                case 1:
                    moveCursorToTop();
                    printf("                                    _______________________________________________________    \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |          "YELLOW"        Menu de la PARTIE-I     "RESET"              |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |         Veuillez choisir parmi ces options:            |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |  "GREEN"1. Creer une population . "RESET"                            |   \n ");
                    printf("                                  |  2. Afficher la population creee .                     |   \n ");
                    printf("                                  |  3. Trier la population deja creee .                   |   \n ");
                    printf("                                  |  4. Calculer le nombre de familles dans la population .|   \n ");
                    printf("                                  |  5. Rechercher une famille dans la population .        |   \n ");
                    printf("                                  |  6. Inserer N familles .                               |   \n ");
                    printf("                                  |  7. Supprimer une famille .                            |   \n ");
                    printf("                                  |  8. Fusionner 2 populations .                          |   \n ");
                    printf("                                  |  9. Exporter la population .                           |   \n ");
                    printf("                                  |  10. Retour au menu principal .                        |   \n ");
                    printf("                                  |  "RED"11. Quitter .   "RESET"                                      |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |________________________________________________________|   \n \n");
                    break;
                case 2:
                    moveCursorToTop();
                    printf("                                    _______________________________________________________    \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |          "YELLOW"        Menu de la PARTIE-I      "RESET"             |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |         Veuillez choisir parmi ces options:            |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |  1. Creer une population .                             |   \n ");
                    printf("                                  |  "GREEN"2. Afficher la population creee .  "RESET"                   |   \n ");
                    printf("                                  |  3. Trier la population deja creee .                   |   \n ");
                    printf("                                  |  4. Calculer le nombre de familles dans la population .|   \n ");
                    printf("                                  |  5. Rechercher une famille dans la population .        |   \n ");
                    printf("                                  |  6. Inserer N familles .                               |   \n ");
                    printf("                                  |  7. Supprimer une famille .                            |   \n ");
                    printf("                                  |  8. Fusionner 2 populations .                          |   \n ");
                    printf("                                  |  9. Exporter la population .                           |   \n ");
                    printf("                                  |  10. Retour au menu principal .                        |   \n ");
                    printf("                                  |  "RED"11. Quitter .   "RESET"                                      |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |________________________________________________________|   \n ");
                    break;
                case 3:
                    moveCursorToTop();
                    printf("                                    _______________________________________________________    \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |           "YELLOW"       Menu de la PARTIE-I     "RESET"              |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |         Veuillez choisir parmi ces options:            |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |  1. Creer une population .                             |   \n ");
                    printf("                                  |  2. Afficher la population creee .                     |   \n ");
                    printf("                                  |  "GREEN"3. Trier la population deja creee .  "RESET"                 |   \n ");
                    printf("                                  |  4. Calculer le nombre de familles dans la population .|   \n ");
                    printf("                                  |  5. Rechercher une famille dans la population .        |   \n ");
                    printf("                                  |  6. Inserer N familles .                               |   \n ");
                    printf("                                  |  7. Supprimer une famille .                            |   \n ");
                    printf("                                  |  8. Fusionner 2 populations .                          |   \n ");
                    printf("                                  |  9. Exporter la population .                           |   \n ");
                    printf("                                  |  10. Retour au menu principal .                        |   \n ");
                    printf("                                  |  "RED"11. Quitter .   "RESET"                                      |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |________________________________________________________|   \n\n ");
                    break;
                case 4:
                    moveCursorToTop();
                    printf("                                    _______________________________________________________    \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |            "YELLOW"      Menu de la PARTIE-I     "RESET"              |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |         Veuillez choisir parmi ces options:            |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |  1. Creer une population .                             |   \n ");
                    printf("                                  |  2. Afficher la population creee .                     |   \n ");
                    printf("                                  |  3. Trier la population deja creee .                   |   \n ");
                    printf("                                  |  "GREEN"4. Calculer le nombre de familles dans la population ."RESET"|   \n ");
                    printf("                                  |  5. Rechercher une famille dans la population .        |   \n ");
                    printf("                                  |  6. Inserer N familles .                               |   \n ");
                    printf("                                  |  7. Supprimer une famille .                            |   \n ");
                    printf("                                  |  8. Fusionner 2 populations .                          |   \n ");
                    printf("                                  |  9. Exporter la population .                           |   \n ");
                    printf("                                  |  10. Retour au menu principal .                        |   \n ");
                    printf("                                  |  "RED"11. Quitter .   "RESET"                                      |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |________________________________________________________|   \n\n ");
                    break;
                case 5:
                    moveCursorToTop();
                    printf("                                    _______________________________________________________    \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |            "YELLOW"      Menu de la PARTIE-I      "RESET"             |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |         Veuillez choisir parmi ces options:            |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |  1. Creer une population .                             |   \n ");
                    printf("                                  |  2. Afficher la population creee .                     |   \n ");
                    printf("                                  |  3. Trier la population deja creee .                   |   \n ");
                    printf("                                  |  4. Calculer le nombre de familles dans la population .|   \n ");
                    printf("                                  |  "GREEN"5. Rechercher une famille dans la population . "RESET"       |   \n ");
                    printf("                                  |  6. Inserer N familles .                               |   \n ");
                    printf("                                  |  7. Supprimer une famille .                            |   \n ");
                    printf("                                  |  8. Fusionner 2 populations .                          |   \n ");
                    printf("                                  |  9. Exporter la population .                           |   \n ");
                    printf("                                  |  10. Retour au menu principal .                        |   \n ");
                    printf("                                  |  "RED"11. Quitter .   "RESET"                                      |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |________________________________________________________|   \n\n ");
                    break;
                case 6:
                    moveCursorToTop();
                    printf("                                    _______________________________________________________    \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |            "YELLOW"      Menu de la PARTIE-I      "RESET"             |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |         Veuillez choisir parmi ces options:            |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |  1. Creer une population .                             |   \n ");
                    printf("                                  |  2. Afficher la population creee .                     |   \n ");
                    printf("                                  |  3. Trier la population deja creee .                   |   \n ");
                    printf("                                  |  4. Calculer le nombre de familles dans la population .|   \n ");
                    printf("                                  |  5. Rechercher une famille dans la population .        |   \n ");
                    printf("                                  |  "GREEN"6. Inserer N familles .  "RESET"                             |   \n ");
                    printf("                                  |  7. Supprimer une famille .                            |   \n ");
                    printf("                                  |  8. Fusionner 2 populations .                          |   \n ");
                    printf("                                  |  9. Exporter la population .                           |   \n ");
                    printf("                                  |  10. Retour au menu principal .                        |   \n ");
                    printf("                                  |  "RED"11. Quitter .   "RESET"                                      |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |________________________________________________________|   \n\n ");
                    break;
                case 7:
                    moveCursorToTop();
                    printf("                                    _______________________________________________________    \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |            "YELLOW"      Menu de la PARTIE-I      "RESET"             |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |         Veuillez choisir parmi ces options:            |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |  1. Creer une population .                             |   \n ");
                    printf("                                  |  2. Afficher la population creee .                     |   \n ");
                    printf("                                  |  3. Trier la population deja creee .                   |   \n ");
                    printf("                                  |  4. Calculer le nombre de familles dans la population .|   \n ");
                    printf("                                  |  5. Rechercher une famille dans la population .        |   \n ");
                    printf("                                  |  6. Inserer N familles .                               |   \n ");
                    printf("                                  |  "GREEN"7. Supprimer une famille ."RESET"                            |   \n ");
                    printf("                                  |  8. Fusionner 2 populations .                          |   \n ");
                    printf("                                  |  9. Exporter la population .                           |   \n ");
                    printf("                                  |  10. Retour au menu principal .                        |   \n ");
                    printf("                                  |  "RED"11. Quitter .   "RESET"                                      |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |________________________________________________________|   \n\n ");
                    break;
                case 8:
                    moveCursorToTop();
                    printf("                                    _______________________________________________________    \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |              "YELLOW"    Menu de la PARTIE-I     "RESET"              |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |         Veuillez choisir parmi ces options:            |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |  1. Creer une population .                             |   \n ");
                    printf("                                  |  2. Afficher la population creee .                     |   \n ");
                    printf("                                  |  3. Trier la population deja creee .                   |   \n ");
                    printf("                                  |  4. Calculer le nombre de familles dans la population .|   \n ");
                    printf("                                  |  5. Rechercher une famille dans la population .        |   \n ");
                    printf("                                  |  6. Inserer N familles .                               |   \n ");
                    printf("                                  |  7. Supprimer une famille .                            |   \n ");
                    printf("                                  |  "GREEN"8. Fusionner 2 populations . "RESET"                         |   \n ");
                    printf("                                  |  9. Exporter la population .                           |   \n ");
                    printf("                                  |  10. Retour au menu principal .                        |   \n ");
                    printf("                                  |  "RED"11. Quitter .   "RESET"                                      |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |________________________________________________________|   \n\n ");
                    break;
                case 9:
                    moveCursorToTop();
                    printf("                                    _______________________________________________________    \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |              "YELLOW"    Menu de la PARTIE-I       "RESET"            |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |         Veuillez choisir parmi ces options:            |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |  1. Creer une population .                             |   \n ");
                    printf("                                  |  2. Afficher la population creee .                     |   \n ");
                    printf("                                  |  3. Trier la population deja creee .                   |   \n ");
                    printf("                                  |  4. Calculer le nombre de familles dans la population .|   \n ");
                    printf("                                  |  5. Rechercher une famille dans la population .        |   \n ");
                    printf("                                  |  6. Inserer N familles .                               |   \n ");
                    printf("                                  |  7. Supprimer une famille .                            |   \n ");
                    printf("                                  |  8. Fusionner 2 populations .                          |   \n ");
                    printf("                                  |  "GREEN"9. Exporter la population .   "RESET"                        |   \n ");
                    printf("                                  |  10. Retour au menu principal .                        |   \n ");
                    printf("                                  |  "RED"11. Quitter .   "RESET"                                      |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |________________________________________________________|   \n\n ");
                    break;
                case 10:
                    moveCursorToTop();
                    printf("                                    _______________________________________________________    \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |              "YELLOW"    Menu de la PARTIE-I       "RESET"            |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |         Veuillez choisir parmi ces options:            |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |  1. Creer une population .                             |   \n ");
                    printf("                                  |  2. Afficher la population creee .                     |   \n ");
                    printf("                                  |  3. Trier la population deja creee .                   |   \n ");
                    printf("                                  |  4. Calculer le nombre de familles dans la population .|   \n ");
                    printf("                                  |  5. Rechercher une famille dans la population .        |   \n ");
                    printf("                                  |  6. Inserer N familles .                               |   \n ");
                    printf("                                  |  7. Supprimer une famille .                            |   \n ");
                    printf("                                  |  8. Fusionner 2 populations .                          |   \n ");
                    printf("                                  |  9. Exporter la population .                           |   \n ");
                    printf("                                  |  "GREEN"10. Retour au menu principal ."RESET"                        |   \n ");
                    printf("                                  |  "RED"11. Quitter .   "RESET"                                      |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |________________________________________________________|   \n\n ");
                    break;
                case 11:
                    moveCursorToTop();
                    printf("                                    _______________________________________________________    \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |              "YELLOW"    Menu de la PARTIE-I   "RESET"                |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |         Veuillez choisir parmi ces options:            |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |  1. Creer une population .                             |   \n ");
                    printf("                                  |  2. Afficher la population creee .                     |   \n ");
                    printf("                                  |  3. Trier la population deja creee .                   |   \n ");
                    printf("                                  |  4. Calculer le nombre de familles dans la population .|   \n ");
                    printf("                                  |  5. Rechercher une famille dans la population .        |   \n ");
                    printf("                                  |  6. Inserer N familles .                               |   \n ");
                    printf("                                  |  7. Supprimer une famille .                            |   \n ");
                    printf("                                  |  8. Fusionner 2 populations .                          |   \n ");
                    printf("                                  |  9. Exporter la population .                           |   \n ");
                    printf("                                  |  10. Retour au menu principal .                        |   \n ");
                    printf("                                  |  "GREEN"11. Quitter .   "RESET"                                      |   \n ");
                    printf("                                  |                                                        |   \n ");
                    printf("                                  |________________________________________________________|   \n\n ");
                    break;
            }
        *choix=cpt;
    }
}

void partie_1(){
    ch20 rech,mod;
    struct famille1* pop1=NULL, *pop2=NULL, *pop3,*pop4,*pop5;
    int choix1;
    int val,n;
    bool menu1=true,ordre=false, ecr,tri1=false,tri2=false;
    char res;
                menu1=true;
                while(menu1){
                    sleep(1);
                    clear_screen();
                    menu_1(&choix1);
                    switch (choix1){
                        case 1://creer pop
                            ordre =true;
                            if(pop1){
                                ecr=ecraser();
                                res=methode_cr();
                                if (ecr){
                                    tri1=false;
                                    switch(res){
                                        case 'A':
                                            printf(YELLOW"      -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                            scanf("%d",&val);
                                            while(val<1){
                                                printf(YELLOW"       -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                                scanf("%d",&val);
                                            }
                                            pop1=creer_pop(val);
                                            export_pop(pop1);
                                            break;

                                        case 'M':
                                            printf(YELLOW"       -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                            scanf("%d",&val);
                                            while(val<1){
                                                printf(YELLOW"       -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                                scanf("%d",&val);
                                            }
                                            getchar();
                                            pop1=creer_pop_manuel(val);
                                            break;
                                        case 'F':
                                            pop1=creer_fichier();
                                            break;
                                    }
                                    printf ("\n\n     -> "RESET"Voulez-vous exporter la population?");
                                    if (choix()){
                                        export_pop(pop1);
                                        printf(GREEN"\n\n   Fichier exporté avec succes!"RESET);
                                    }
                                }
                                else{
                                    tri2=false;
                                    switch(res){
                                        case 'A':
                                            printf(YELLOW"       -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                            scanf("%d",&val);
                                            while(val<1){
                                                printf(YELLOW"       -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                                scanf("%d",&val);
                                            }
                                            pop2=creer_pop(val);
                                            break;

                                        case 'M':
                                            printf(YELLOW"      -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                            scanf("%d",&val);
                                            while(val<1){
                                                printf(YELLOW"      -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                                scanf("%d",&val);
                                            }
                                            getchar();
                                            pop2=creer_pop_manuel(val);
                                            break;
                                        case 'F':
                                        pop2=creer_fichier();
                                        break;
                                }
                                printf ("\n\n     -> "RESET"Voulez-vous exporter la population?");
                                if (choix()){
                                    export_pop(pop2);
                                    printf(GREEN"\n\n   Fichier exporté avec succes!"RESET);
                                }
                            }
                        }
                        else {
                            res=methode_cr();
                            switch(res){
                                case 'A':
                                    printf(YELLOW"       -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                    scanf("%d",&val);
                                    while(val<1){
                                        printf(YELLOW"       -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                        scanf("%d",&val);
                                    }
                                    pop1=creer_pop(val);
                                    export_pop(pop1);
                                    break;

                                case 'M':
                                    printf(YELLOW"       -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                    scanf("%d",&val);
                                    while(val<1){
                                        printf(YELLOW"      -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                        scanf("%d",&val);
                                    }
                                    getchar();
                                    pop1=creer_pop_manuel(val);
                                    break;
                                case 'F':
                                pop1=creer_fichier();
                                break;
                            }
                            printf ("\n\n     -> "RESET"Voulez-vous exporter la population?");
                            if (choix()){
                                export_pop(pop1);
                                printf(GREEN"\n\n   Fichier exporté avec succès!"RESET);
                            }
                        }
                            break;
                        case 2://Afficher pop
                            if(ordre){
                                if(pop2){
                                    if (manip())
                                        afficher_pop1(pop1);
                                    else
                                        afficher_pop1(pop2);
                                }
                                else afficher_pop1(pop1);
                                
                            }
                            else{
                                printf("\n      "RED"Vous devez d'abord creer la population."RESET"");
                            }
                            break;
                        case 3: // tri
                            if (ordre){
                              if (pop2){
                                if(manip()){
                                    tri1=true;
                                    printf(RED"\n         -> "RESET"Voici la population non triee: \n\n");
                                    afficher_pop1(pop1);
                                    trier_pop(pop1);
                                    printf(GREEN"\n\n\n         -> "RESET"Voici le resultat du tri: \n\n");
                                    afficher_pop1(pop1);
                                }
                                else{
                                    tri2=true;
                                    printf(RED"\n        -> "RESET"Voici la population non triee: \n\n");
                                    afficher_pop1(pop2);
                                    trier_pop(pop2);
                                    printf(GREEN"\n\n\n         -> "RESET"Voici le resultat du tri: \n\n");
                                    afficher_pop1(pop2);
                                }
                              }
                              else {
                                    tri1=true;
                                    printf(RED"\n         -> "RESET"Voici la population non triee: \n\n");
                                    afficher_pop1(pop1);
                                    trier_pop(pop1);
                                    printf(GREEN"\n\n\n         -> "RESET"Voici le resultat du tri: \n\n");
                                    afficher_pop1(pop1);
                                }
                            }
                            else{
                                printf("\n      "RED"Vous devez d'abord creer la population."RESET"");
                            }
                            break;
                        case 4://Nombre de familles
                            if(ordre){
                                if (pop2){
                                    if (manip()) printf("\n\n       "YELLOW" -> "RESET"Le nombre de familles de la population 1 est :    %d",nbfamille1(pop1));
                                    else printf("\n\n       "YELLOW" -> "RESET"Le nombre de familles la population 2 est :    %d",nbfamille1(pop2));
                                }
                                else printf("\n\n       "YELLOW" -> "RESET"Le nombre de familles de la population est :    %d",nbfamille1(pop1));

                            }
                            else{
                                printf("\n      "RED"Vous devez d'abord creer la population."RESET"");
                            }
                            break;
                        case 5://Rechercher une famille
                            if(ordre){
                                if (pop2){
                                    if (manip()){
                                        if (tri1){
                                            printf("\n\n        "YELLOW" -> "RESET"Veuillez saisir le nom de la famille dont vous cherchez :  ");
                                            scanf(" %[^\n]", rech);
                                            if (present(pop1,rech))
                                                printf("\n"GREEN"\n         -> La famille %s existe dans la population.\n"RESET,rech);
                                            else{
                                                printf(RED"\n       La famille saisie n'existe pas dans la population!\n"RESET);
                                            }
                                        }
                                        else printf(RED"        Vous devez d'abord trier la population!"RESET);
                                    }
                                    else {
                                        if (tri2){
                                            printf("\n\n        "YELLOW" -> "RESET"Veuillez saisir le nom de la famille dont vous cherchez :  ");
                                            scanf(" %[^\n]", rech);
                                            if (present(pop2,rech))
                                                printf("\n"GREEN"\n         -> La famille %s existe dans la population.\n"RESET,rech);
                                            else{
                                                printf(RED"\n       La famille saisie n'existe pas dans la population!\n"RESET);
                                            }
                                        }
                                        else printf(RED"        Vous devez d'abord trier la population!"RESET);
                                    }
                                }
                                else {
                                    if (tri1){
                                        printf("\n\n        "YELLOW" -> "RESET"Veuillez saisir le nom de la famille dont vous cherchez :  ");
                                        scanf(" %[^\n]", rech);
                                        if (present(pop1,rech))
                                            printf("\n"GREEN"\n         -> La famille %s existe dans la population.\n"RESET,rech);
                                        else{
                                            printf(RED"\n       La famille saisie n'existe pas dans la population!\n"RESET);
                                        }
                                    }
                                    else printf(RED"        Vous devez d'abord trier la population!"RESET);
                                }

                            }
                            else{
                                printf("\n"RED"       Vous devez d'abord creer la population.\n"RESET"");
                            }
                            break;
                        case 6://inserer une famille
                            if(ordre){
                                printf("\n\n"YELLOW"         -> "RESET"Veuillez saisir le nombre de familles a inserer :  ");
                                scanf(" %d",&n);
                                if(pop2){
                                    if(manip()){
                                        if(tri1){
                                            if(methode_ins()) inser_n_fam_m(&pop1,n);
                                            else inser_n_fam_a(&pop1,n);
                                            printf(GREEN"\n      Familles inseree avec succes!"RESET);
                                        }
                                        else printf(RED"        Vous devez d'abord trier la population!"RESET);
                                    }
                                    else
                                        if(tri2){
                                            if(methode_ins()) inser_n_fam_m(&pop2,n);
                                            else inser_n_fam_a(&pop2,n);
                                            printf(GREEN"\n      Familles inseree avec succes!"RESET);
                                        }
                                        else printf(RED"        Vous devez d'abord trier la population!"RESET);
                                }
                                else
                                    if(tri1){
                                            if(methode_ins()) inser_n_fam_m(&pop1,n);
                                            else inser_n_fam_a(&pop1,n);
                                            printf(GREEN"\n      Familles inseree avec succes!"RESET);
                                        }
                                    else printf(RED"        Vous devez d'abord trier la population!"RESET);
 
                            }
                            else{
                                printf("\n"RED"     Vous devez d'abord creer la population."RESET"");
                            }
                            break;
                        case 7: //supprimer une famille
                            if(ordre){
                                if(pop2){
                                    if (manip()){
                                        if(tri1){
                                            printf(YELLOW"\n        -> "RESET"Veuillez entrer le nom de la famille dont vous souhaitez supprimer :");
                                            scanf("%s",mod);
                                            getchar();
                                            if (present(pop1, mod)){
                                                supp(&pop1,mod);
                                                printf(GREEN"\n         Famille supprimee avec succes!"RESET);
                                            }
                                            else{
                                                printf(RED"\n       La famille saisie n'existe pas dans la population!"RESET);
                                            }
                                        }
                                        else printf(RED"        Vous devez d'abord trier la population!"RESET);
                                    }
                                    else {
                                        if(tri2){
                                            printf(YELLOW"\n        -> "RESET"Veuillez entrer le nom de la famille dont vous souhaitez supprimer :");
                                            scanf("%s",mod);
                                            getchar();
                                            if (present(pop2, mod)){
                                                supp(&pop2,mod);
                                                printf(GREEN"\n         Famille supprimee avec succes!"RESET);
                                            }
                                            else{
                                                printf(RED"\n       La famille saisie n'existe pas dans la population!"RESET);
                                            }
                                        }
                                        else printf(RED"        Vous devez d'abord trier la population!"RESET);
                                    }
                                }
                                else {
                                    if(tri1){
                                            printf(YELLOW"\n        -> "RESET"Veuillez entrer le nom de la famille dont vous souhaitez supprimer :");
                                            scanf("%s",mod);
                                            getchar();
                                            if (present(pop1, mod)){
                                                supp(&pop1,mod);
                                                printf(GREEN"\n         Famille supprimee avec succes!"RESET);
                                            }
                                            else{
                                                printf(RED"\n       La famille saisie n'existe pas dans la population!"RESET);
                                            }
                                        }
                                        else printf(RED"        Vous devez d'abord trier la population!"RESET);
                                }
                            }
                            else{
                                printf("\n"RED"       Vous devez d'abord creer la population."RESET"");
                            }
                            break;
                        case 8: //fusionner 2 familles
                            if (ordre){
                                if(pop2){
                                    printf("\n"YELLOW"       -> "RESET"Voici la 1ere population :\n\n");
                                    afficher_pop1(pop1);
                                    printf("\n\n"YELLOW"         -> "RESET"Voici la 2eme population :\n\n");
                                    afficher_pop1(pop2);
                                    printf("\n      Appuyez sur une touche pour continuer...");
                                    _getch();
                                    res=methode_fu();
                                    if(res=='1'){
                                            pop1=fusion_pops(pop1,pop2);
                                            printf("\n      Appuyez sur une touche pour continuer...");
                                            _getch();
                                            clear_screen();
                                            printf(YELLOW"       -> "RESET"Voici le resultat de la fusion :\n");
                                            afficher_pop1(pop1);
                                    }
                                    else
                                    if(res=='2'){
                                            if (confirmation()){
                                            pop2=fusion_pops(pop2,pop1);
                                            printf("\n      Appuyez sur une touche pour continuer...");
                                            _getch();
                                            clear_screen();
                                            printf(YELLOW"       -> "RESET"Voici le resultat de la fusion :\n");
                                            afficher_pop1(pop2);
                                        }
                                        else printf(RED"\n      Operation anuulee"RESET);
                                        }
                                        else if(res=='3'){
                                                if (confirmation()){
                                                    pop3=copier_liste(pop1);
                                                    pop3=fusion_pops(pop3,pop2);
                                                    printf("\n      Appuyez sur une touche pour continuer...");
                                                    _getch();
                                                    clear_screen();
                                                    printf(YELLOW"       -> "RESET"Voici le resultat de la fusion :\n");
                                                    afficher_pop1(pop3);
                                                }
                                                else printf(RED"\n      Operation anuulee"RESET);
                                            }
                                }
                                else printf(""RED"      Vous devez d'abord creer la 2eme population"RESET"");

                            }
                            else{
                                printf("\n"RED"       Vous devez d'abord creer la population."RESET"");
                            }
                            break;
                        case 9: // exporter
                            if (pop1){
                                if (pop2){
                                    if (manip()) export_pop(pop1);
                                    else export_pop(pop2);
                                }
                                else export_pop(pop1);
                                printf(GREEN"       Rapport exporte avec succes. "RESET);
                            }
                            else printf("\n"RED"       Vous devez d'abord creer la population."RESET"");
                            break;
                        case 10://revenir
                            menu1=false;
                            return;
                            break;
                        case 11://quitter
                            printf(RED"\n       Quitter le programme...\n"RESET);
                            exit(0);
                            break;
                        default:
                            printf(""RED"\n     Option invalide! Veuillez choisir un des choix du menu."RESET"");
                            break;
                    }
                    printf("\n        Appuyez sur une touche pour continuer...");
                    _getch();
                }
}

void menu_2(int *choix){
    int cpt=0;
    bool enter = false ;
    printf("                                    _____________________________________________________________________\n ");
    printf("                                  |                                                                      |   \n ");
    printf("                                  |                     "YELLOW"  Menu de la PARTIE-II            "RESET"               |   \n ");
    printf("                                  |                                                                      |   \n ");
    printf("                                  |                                                                      |   \n ");
    printf("                                  |                Veuillez choisir parmi ces options:                   |   \n ");
    printf("                                  |                                                                      |   \n ");
    printf("                                  |  1. Creer une population .                                           |   \n ");
    printf("                                  |  2. Afficher la population triee .                                   |   \n ");
    printf("                                  |  3. Calculer le nombre de familles sans parents dans la population . |   \n ");
    printf("                                  |  4. Calculer le nombre d'enfants de la population .                  |   \n ");
    printf("                                  |  5. Calculer le nombre d'enfants d'une famille .                     |   \n ");
    printf("                                  |  6. Modifier la population .                                         |   \n ");
    printf("                                  |  7. Modifier une famille .                                           |   \n ");
    printf("                                  |  8. Fusionner 2 populations triees .                                 |   \n ");
    printf("                                  |  9. Demenager un famille d'une population vers une autre .           |   \n ");
    printf("                                  |  10. Rechercher si la famille possédant une voiture appartient à pop.|   \n ");
    printf("                                  |  11. Exporter un fichier .                                           |   \n ");
    printf("                                  |  12. Retour au menu principal .                                      |   \n ");
    printf("                                  |  "RED"13. Quitter .   "RESET"                                                    |   \n ");
    printf("                                  |                                                                      |   \n ");
    printf("                                  |______________________________________________________________________|   \n\n ");
    while (!enter){
       *choix = detecte(&cpt , 13 , &enter) ;
        if(*choix > 0) return ;
            switch(cpt){
                case 1:
                    moveCursorToTop();
                    printf("                                    _____________________________________________________________________\n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                   "YELLOW"    Menu de la PARTIE-II      "RESET"                     |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                Veuillez choisir parmi ces options:                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |  "GREEN"1. Creer une population .    "RESET"                                       |   \n ");
                    printf("                                  |  2. Afficher la population triee .                                   |   \n ");
                    printf("                                  |  3. Calculer le nombre de familles sans parents dans la population . |   \n ");
                    printf("                                  |  4. Calculer le nombre d'enfants de la population .                  |   \n ");
                    printf("                                  |  5. Calculer le nombre d'enfants d'une famille .                     |   \n ");
                    printf("                                  |  6. Modifier la population .                                         |   \n ");
                    printf("                                  |  7. Modifier une famille .                                           |   \n ");
                    printf("                                  |  8. Fusionner 2 populations triees .                                 |   \n ");
                    printf("                                  |  9. Demenager un famille d'une population vers une autre .           |   \n ");
                    printf("                                  |  10. Rechercher si la famille possédant une voiture appartient à pop.|   \n ");
                    printf("                                  |  11. Exporter un fichier .                                           |   \n ");
                    printf("                                  |  12. Retour au menu principal .                                      |   \n ");
                    printf("                                  |  "RED"13. Quitter .    "RESET"                                                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |______________________________________________________________________|   \n\n ");
                    break;
                case 2:
                    moveCursorToTop();
                    printf("                                    _____________________________________________________________________\n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                   "YELLOW"    Menu de la PARTIE-II       "RESET"                    |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                Veuillez choisir parmi ces options:                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |  1. Creer une population .                                           |   \n ");
                    printf("                                  |  "GREEN"2. Afficher la population triee .        "RESET"                           |   \n ");
                    printf("                                  |  3. Calculer le nombre de familles sans parents dans la population . |   \n ");
                    printf("                                  |  4. Calculer le nombre d'enfants de la population .                  |   \n ");
                    printf("                                  |  5. Calculer le nombre d'enfants d'une famille .                     |   \n ");
                    printf("                                  |  6. Modifier la population .                                         |   \n ");
                    printf("                                  |  7. Modifier une famille .                                           |   \n ");
                    printf("                                  |  8. Fusionner 2 populations triees .                                 |   \n ");
                    printf("                                  |  9. Demenager un famille d'une population vers une autre .           |   \n ");
                    printf("                                  |  10. Rechercher si la famille possédant une voiture appartient à pop.|   \n ");
                    printf("                                  |  11. Exporter un fichier .                                           |   \n ");
                    printf("                                  |  12. Retour au menu principal .                                      |   \n ");
                    printf("                                  |  "RED"13. Quitter .    "RESET"                                                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |______________________________________________________________________|   \n\n ");
                    break;
                case 3:
                    moveCursorToTop();
                    printf("                                    _____________________________________________________________________\n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                   "YELLOW"    Menu de la PARTIE-II    "RESET"                       |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                Veuillez choisir parmi ces options:                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |  1. Creer une population .                                           |   \n ");
                    printf("                                  |  2. Afficher la population triee .                                   |   \n ");
                    printf("                                  |  "GREEN"3. Calculer le nombre de familles sans parents dans la population . "RESET"|   \n ");
                    printf("                                  |  4. Calculer le nombre d'enfants de la population .                  |   \n ");
                    printf("                                  |  5. Calculer le nombre d'enfants d'une famille .                     |   \n ");
                    printf("                                  |  6. Modifier la population .                                         |   \n ");
                    printf("                                  |  7. Modifier une famille .                                           |   \n ");
                    printf("                                  |  8. Fusionner 2 populations triees .                                 |   \n ");
                    printf("                                  |  9. Demenager un famille d'une population vers une autre .           |   \n ");
                    printf("                                  |  10. Rechercher si la famille possédant une voiture appartient à pop.|   \n ");
                    printf("                                  |  11. Exporter un fichier .                                           |   \n ");
                    printf("                                  |  12. Retour au menu principal .                                      |   \n ");
                    printf("                                  | "RED" 13. Quitter .    "RESET"                                                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |______________________________________________________________________|   \n\n ");
                    break;
                case 4:
                    moveCursorToTop();
                    printf("                                    _____________________________________________________________________\n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                   "YELLOW"    Menu de la PARTIE-II    "RESET"                       |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                Veuillez choisir parmi ces options:                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |  1. Creer une population .                                           |   \n ");
                    printf("                                  |  2. Afficher la population triee .                                   |   \n ");
                    printf("                                  |  3. Calculer le nombre de familles sans parents dans la population . |   \n ");
                    printf("                                  |  "GREEN"4. Calculer le nombre d'enfants de la population .   "RESET"               |   \n ");
                    printf("                                  |  5. Calculer le nombre d'enfants d'une famille .                     |   \n ");
                    printf("                                  |  6. Modifier la population .                                         |   \n ");
                    printf("                                  |  7. Modifier une famille .                                           |   \n ");
                    printf("                                  |  8. Fusionner 2 populations triees .                                 |   \n ");
                    printf("                                  |  9. Demenager un famille d'une population vers une autre .           |   \n ");
                    printf("                                  |  10. Rechercher si la famille possédant une voiture appartient à pop.|   \n ");
                    printf("                                  |  11. Exporter un fichier .                                           |   \n ");
                    printf("                                  |  12. Retour au menu principal .                                      |   \n ");
                    printf("                                  | "RED" 13. Quitter .   "RESET"                                                    |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |______________________________________________________________________|   \n\n ");
                    break;
                case 5:
                    moveCursorToTop();
                    printf("                                    _____________________________________________________________________\n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                   "YELLOW"    Menu de la PARTIE-II       "RESET"                    |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                Veuillez choisir parmi ces options:                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |  1. Creer une population .                                           |   \n ");
                    printf("                                  |  2. Afficher la population triee .                                   |   \n ");
                    printf("                                  |  3. Calculer le nombre de familles sans parents dans la population . |   \n ");
                    printf("                                  |  4. Calculer le nombre d'enfants de la population .                  |   \n ");
                    printf("                                  | "GREEN" 5. Calculer le nombre d'enfants d'une famille .    "RESET"                 |   \n ");
                    printf("                                  |  6. Modifier la population .                                         |   \n ");
                    printf("                                  |  7. Modifier une famille .                                           |   \n ");
                    printf("                                  |  8. Fusionner 2 populations triees .                                 |   \n ");
                    printf("                                  |  9. Demenager un famille d'une population vers une autre .           |   \n ");
                    printf("                                  |  10. Rechercher si la famille possédant une voiture appartient à pop.|   \n ");
                    printf("                                  |  11. Exporter un fichier .                                           |   \n ");
                    printf("                                  |  12. Retour au menu principal .                                      |   \n ");
                    printf("                                  |  "RED"13. Quitter .    "RESET"                                                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |______________________________________________________________________|   \n\n ");
                    break;
                case 6:
                    moveCursorToTop();
                    printf("                                    _____________________________________________________________________\n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                   "YELLOW"    Menu de la PARTIE-II       "RESET"                    |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                Veuillez choisir parmi ces options:                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |  1. Creer une population .                                           |   \n ");
                    printf("                                  |  2. Afficher la population triee .                                   |   \n ");
                    printf("                                  |  3. Calculer le nombre de familles sans parents dans la population . |   \n ");
                    printf("                                  |  4. Calculer le nombre d'enfants de la population .                  |   \n ");
                    printf("                                  |  5. Calculer le nombre d'enfants d'une famille .                     |   \n ");
                    printf("                                  |  "GREEN"6. Modifier la population .   "RESET"                                      |   \n ");
                    printf("                                  |  7. Modifier une famille .                                           |   \n ");
                    printf("                                  |  8. Fusionner 2 populations triees .                                 |   \n ");
                    printf("                                  |  9. Demenager un famille d'une population vers une autre .           |   \n ");
                    printf("                                  |  10. Rechercher si la famille possédant une voiture appartient à pop.|   \n ");
                    printf("                                  |  11. Exporter un fichier .                                           |   \n ");
                    printf("                                  |  12. Retour au menu principal .                                      |   \n ");
                    printf("                                  |  "RED"13. Quitter .     "RESET"                                                  |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |______________________________________________________________________|   \n\n ");
                    break;
                case 7:
                    moveCursorToTop();
                    printf("                                    _____________________________________________________________________\n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                   "YELLOW"    Menu de la PARTIE-II        "RESET"                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                Veuillez choisir parmi ces options:                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |  1. Creer une population .                                           |   \n ");
                    printf("                                  |  2. Afficher la population triee .                                   |   \n ");
                    printf("                                  |  3. Calculer le nombre de familles sans parents dans la population . |   \n ");
                    printf("                                  |  4. Calculer le nombre d'enfants de la population .                  |   \n ");
                    printf("                                  |  5. Calculer le nombre d'enfants d'une famille .                     |   \n ");
                    printf("                                  |  6. Modifier la population .                                         |   \n ");
                    printf("                                  |  "GREEN"7. Modifier une famille .    "RESET"                                       |   \n ");
                    printf("                                  |  8. Fusionner 2 populations triees .                                 |   \n ");
                    printf("                                  |  9. Demenager un famille d'une population vers une autre .           |   \n ");
                    printf("                                  |  10. Rechercher si la famille possédant une voiture appartient à pop.|   \n ");
                    printf("                                  |  11. Exporter un fichier .                                           |   \n ");
                    printf("                                  |  12. Retour au menu principal .                                      |   \n ");
                    printf("                                  |  "RED"13. Quitter .     "RESET"                                                  |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |______________________________________________________________________|   \n\n ");
                    break;
                case 8:
                    moveCursorToTop();
                    printf("                                    _____________________________________________________________________\n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                  "YELLOW"     Menu de la PARTIE-II        "RESET"                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                Veuillez choisir parmi ces options:                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |  1. Creer une population .                                           |   \n ");
                    printf("                                  |  2. Afficher la population triee .                                   |   \n ");
                    printf("                                  |  3. Calculer le nombre de familles sans parents dans la population . |   \n ");
                    printf("                                  |  4. Calculer le nombre d'enfants de la population .                  |   \n ");
                    printf("                                  |  5. Calculer le nombre d'enfants d'une famille .                     |   \n ");
                    printf("                                  |  6. Modifier la population .                                         |   \n ");
                    printf("                                  |  7. Modifier une famille .                                           |   \n ");
                    printf("                                  | "GREEN" 8. Fusionner 2 populations triees .    "RESET"                             |   \n ");
                    printf("                                  |  9. Demenager un famille d'une population vers une autre .           |   \n ");
                    printf("                                  |  10. Rechercher si la famille possédant une voiture appartient à pop.|   \n ");
                    printf("                                  |  11. Exporter un fichier .                                           |   \n ");
                    printf("                                  |  12. Retour au menu principal .                                      |   \n ");
                    printf("                                  |  "RED"13. Quitter .       "RESET"                                                |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |______________________________________________________________________|   \n\n ");
                    break;
                case 9:
                    moveCursorToTop();
                    printf("                                    _____________________________________________________________________\n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                  "YELLOW"     Menu de la PARTIE-II         "RESET"                  |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                Veuillez choisir parmi ces options:                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |  1. Creer une population .                                           |   \n ");
                    printf("                                  |  2. Afficher la population triee .                                   |   \n ");
                    printf("                                  |  3. Calculer le nombre de familles sans parents dans la population . |   \n ");
                    printf("                                  |  4. Calculer le nombre d'enfants de la population .                  |   \n ");
                    printf("                                  |  5. Calculer le nombre d'enfants d'une famille .                     |   \n ");
                    printf("                                  |  6. Modifier la population .                                         |   \n ");
                    printf("                                  |  7. Modifier une famille .                                           |   \n ");
                    printf("                                  |  8. Fusionner 2 populations triees .                                 |   \n ");
                    printf("                                  | "GREEN" 9. Demenager un famille d'une population vers une autre .    "RESET"       |   \n ");
                    printf("                                  |  10. Rechercher si la famille possédant une voiture appartient à pop.|   \n ");
                    printf("                                  |  11. Exporter un fichier .                                           |   \n ");
                    printf("                                  |  12. Retour au menu principal .                                      |   \n ");
                    printf("                                  |  "RED"13. Quitter .            "RESET"                                           |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |______________________________________________________________________|   \n\n ");
                    break;
                case 10:
                    moveCursorToTop();
                    printf("                                    _____________________________________________________________________\n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                     "YELLOW"  Menu de la PARTIE-II         "RESET"                  |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                Veuillez choisir parmi ces options:                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |  1. Creer une population .                                           |   \n ");
                    printf("                                  |  2. Afficher la population triee .                                   |   \n ");
                    printf("                                  |  3. Calculer le nombre de familles sans parents dans la population . |   \n ");
                    printf("                                  |  4. Calculer le nombre d'enfants de la population .                  |   \n ");
                    printf("                                  |  5. Calculer le nombre d'enfants d'une famille .                     |   \n ");
                    printf("                                  |  6. Modifier la population .                                         |   \n ");
                    printf("                                  |  7. Modifier une famille .                                           |   \n ");
                    printf("                                  |  8. Fusionner 2 populations triees .                                 |   \n ");
                    printf("                                  |  9. Demenager un famille d'une population vers une autre .           |   \n ");
                    printf("                                  | "GREEN" 10. Rechercher si la famille possédant une voiture appartient à pop."RESET"|   \n ");
                    printf("                                  |  11. Exporter un fichier .                                           |   \n ");
                    printf("                                  |  12. Retour au menu principal .                                      |   \n ");
                    printf("                                  |  "RED"13. Quitter .    "RESET"                                                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |______________________________________________________________________|   \n\n ");
                    break;
                case 11:
                    moveCursorToTop();
                    printf("                                    _____________________________________________________________________\n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                    "YELLOW"   Menu de la PARTIE-II        "RESET"                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                Veuillez choisir parmi ces options:                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |  1. Creer une population .                                           |   \n ");
                    printf("                                  |  2. Afficher la population triee .                                   |   \n ");
                    printf("                                  |  3. Calculer le nombre de familles sans parents dans la population . |   \n ");
                    printf("                                  |  4. Calculer le nombre d'enfants de la population .                  |   \n ");
                    printf("                                  |  5. Calculer le nombre d'enfants d'une famille .                     |   \n ");
                    printf("                                  |  6. Modifier la population .                                         |   \n ");
                    printf("                                  |  7. Modifier une famille .                                           |   \n ");
                    printf("                                  |  8. Fusionner 2 populations triees .                                 |   \n ");
                    printf("                                  |  9. Demenager un famille d'une population vers une autre .           |   \n ");
                    printf("                                  |  10. Rechercher si la famille possédant une voiture appartient à pop.|   \n ");
                    printf("                                  | "GREEN" 11. Exporter un fichier .      "RESET"                                     |   \n ");
                    printf("                                  |  12. Retour au menu principal .                                      |   \n ");
                    printf("                                  |  "RED"13. Quitter .    "RESET"                                                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |______________________________________________________________________|   \n\n ");
                    break;
                case 12:
                    moveCursorToTop();
                    printf("                                    _____________________________________________________________________\n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                   "YELLOW"    Menu de la PARTIE-II       "RESET"                    |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                Veuillez choisir parmi ces options:                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |  1. Creer une population .                                           |   \n ");
                    printf("                                  |  2. Afficher la population triee .                                   |   \n ");
                    printf("                                  |  3. Calculer le nombre de familles sans parents dans la population . |   \n ");
                    printf("                                  |  4. Calculer le nombre d'enfants de la population .                  |   \n ");
                    printf("                                  |  5. Calculer le nombre d'enfants d'une famille .                     |   \n ");
                    printf("                                  |  6. Modifier la population .                                         |   \n ");
                    printf("                                  |  7. Modifier une famille .                                           |   \n ");
                    printf("                                  |  8. Fusionner 2 populations triees .                                 |   \n ");
                    printf("                                  |  9. Demenager un famille d'une population vers une autre .           |   \n ");
                    printf("                                  |  10. Rechercher si la famille possédant une voiture appartient à pop.|   \n ");
                    printf("                                  |  11. Exporter un fichier .                                           |   \n ");
                    printf("                                  |  "GREEN"12. Retour au menu principal .   "RESET"                                   |   \n ");
                    printf("                                  |  "RED"13. Quitter .      "RESET"                                                 |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |______________________________________________________________________|   \n\n ");
                    break;
                case 13:
                    moveCursorToTop();
                    printf("                                    _____________________________________________________________________\n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                   "YELLOW"    Menu de la PARTIE-II        "RESET"                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |                Veuillez choisir parmi ces options:                   |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |  1. Creer une population .                                           |   \n ");
                    printf("                                  |  2. Afficher la population triee .                                   |   \n ");
                    printf("                                  |  3. Calculer le nombre de familles sans parents dans la population . |   \n ");
                    printf("                                  |  4. Calculer le nombre d'enfants de la population .                  |   \n ");
                    printf("                                  |  5. Calculer le nombre d'enfants d'une famille .                     |   \n ");
                    printf("                                  |  6. Modifier la population .                                         |   \n ");
                    printf("                                  |  7. Modifier une famille .                                           |   \n ");
                    printf("                                  |  8. Fusionner 2 populations triees .                                 |   \n ");
                    printf("                                  |  9. Demenager un famille d'une population vers une autre .           |   \n ");
                    printf("                                  |  10. Rechercher si la famille possédant une voiture appartient à pop.|   \n ");
                    printf("                                  |  11. Exporter un fichier .                                           |   \n ");
                    printf("                                  |  12. Retour au menu principal .                                      |   \n ");
                    printf("                                  |  "GREEN"13. Quitter . "RESET"                                                      |   \n ");
                    printf("                                  |                                                                      |   \n ");
                    printf("                                  |______________________________________________________________________|   \n\n ");
                    break;
            }
        
    }
    *choix=cpt;

}

void sous_menu_modp(int * choix){
    int cpt=0;
    bool enter = false ;
    printf("                                    __________________________________________________   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |            "YELLOW"  Modifier la population    "RESET"          |   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |    Veuillez choisir une option                   |   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |   1. Ajouter une famille .                       |   \n ");
    printf("                                  |   2. Supprimer une famille .                     |   \n ");
    printf("                                  |   3. Revenir au menu principal .                 |   \n ");
    printf("                                  |   "RED"4. Quitter . "RESET"                                  |   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |__________________________________________________|   \n\n ");
    while (!enter){
        *choix = detecte(&cpt , 4 , &enter) ;
        if(*choix > 0) return ;
            switch(cpt){
                case 1:
                    moveCursorToTop();
                    printf("                                    __________________________________________________   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |            "YELLOW"  Modifier la population   "RESET"           |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |    Veuillez choisir une option                   |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |   "GREEN"1. Ajouter une famille ."RESET"                       |   \n ");
                    printf("                                  |   2. Supprimer une famille .                     |   \n ");
                    printf("                                  |   3. Revenir au menu principal .                 |   \n ");
                    printf("                                  |   "RED"4. Quitter ."RESET"                                   |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |__________________________________________________|   \n\n ");
                    break;
                case 2:
                    moveCursorToTop();
                    printf("                                    __________________________________________________   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |            "YELLOW"  Modifier la population   "RESET"           |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |    Veuillez choisir une option                   |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |   1. Ajouter une famille .                       |   \n ");
                    printf("                                  |   "GREEN"2. Supprimer une famille . "RESET"                    |   \n ");
                    printf("                                  |   3. Revenir au menu principal .                 |   \n ");
                    printf("                                  |   "RED"4. Quitter ."RESET"                                   |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |__________________________________________________|   \n\n ");
                    break;
                case 3:
                    moveCursorToTop();
                    printf("                                    __________________________________________________   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |            "YELLOW"  Modifier la population   "RESET"           |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |    Veuillez choisir une option                   |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |   1. Ajouter une famille .                       |   \n ");
                    printf("                                  |   2. Supprimer une famille .                     |   \n ");
                    printf("                                  |   "GREEN"3. Revenir au menu principal .  "RESET"               |   \n ");
                    printf("                                  |   "RED"4. Quitter . "RESET"                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |__________________________________________________|   \n\n ");
                    break;
                case 4:
                    moveCursorToTop();
                    printf("                                    __________________________________________________   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |            "YELLOW"  Modifier la population    "RESET"          |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |    Veuillez choisir une option                   |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |   1. Ajouter une famille .                       |   \n ");
                    printf("                                  |   2. Supprimer une famille .                     |   \n ");
                    printf("                                  |   3. Revenir au menu principal .                 |   \n ");
                    printf("                                  |   "GREEN"4. Quitter .  "RESET"                                 |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |__________________________________________________|   \n\n ");
            }
        }
    *choix=cpt;
}

void sous_menu_modf(int *choix){
    int ch,cpt=0;
    bool enter = false ;
    printf("                                    __________________________________________________   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |             "YELLOW"  Modifier une famille    "RESET"           |   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |    Veuillez choisir une option :                 |   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |   1. Supprimer un parent .                       |   \n ");
    printf("                                  |   2. Supprimer un enfant .                       |   \n ");
    printf("                                  |   3. Supprimer une voiture .                     |   \n ");
    printf("                                  |   4. Inserer un enfant (nouveau ne) .            |   \n ");
    printf("                                  |   5. Inserer une voiture .                       |   \n ");
    printf("                                  |   6. Revenir au menu principal .                 |   \n ");
    printf("                                  |   "RED"7. Quitter . "RESET"                                  |   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |__________________________________________________|   \n \n");

    while (!enter){
        *choix = detecte(&cpt , 7 , &enter) ;
        if(*choix > 0) return ;
            switch(cpt){
                case 1:
                    moveCursorToTop();
                    printf("                                    __________________________________________________   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |             "YELLOW"  Modifier une famille   "RESET"            |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |    Veuillez choisir une option :                 |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |   "GREEN"1. Supprimer un parent .  "RESET"                     |   \n ");
                    printf("                                  |   2. Supprimer un enfant .                       |   \n ");
                    printf("                                  |   3. Supprimer une voiture .                     |   \n ");
                    printf("                                  |   4. Inserer un enfant (nouveau ne) .            |   \n ");
                    printf("                                  |   5. Inserer une voiture .                       |   \n ");
                    printf("                                  |   6. Revenir au menu principal .                 |   \n ");
                    printf("                                  |   "RED"7. Quitter . "RESET"                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |__________________________________________________|   \n\n ");
                    break;
                case 2:
                    moveCursorToTop();
                    printf("                                    __________________________________________________   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |            "YELLOW"   Modifier une famille    "RESET"           |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |    Veuillez choisir une option :                 |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |   1. Supprimer un parent .                       |   \n ");
                    printf("                                  |   "GREEN"2. Supprimer un enfant . "RESET"                      |   \n ");
                    printf("                                  |   3. Supprimer une voiture .                     |   \n ");
                    printf("                                  |   4. Inserer un enfant (nouveau ne) .            |   \n ");
                    printf("                                  |   5. Inserer une voiture .                       |   \n ");
                    printf("                                  |   6. Revenir au menu principal .                 |   \n ");
                    printf("                                  |   "RED"7. Quitter . "RESET"                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |__________________________________________________|   \n\n ");
                    break;
                case 3:
                    moveCursorToTop();
                    printf("                                    __________________________________________________   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |            "YELLOW"   Modifier une famille   "RESET"            |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |    Veuillez choisir une option :                 |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |   1. Supprimer un parent .                       |   \n ");
                    printf("                                  |   2. Supprimer un enfant .                       |   \n ");
                    printf("                                  |   "GREEN"3. Supprimer une voiture . "RESET"                    |   \n ");
                    printf("                                  |   4. Inserer un enfant (nouveau ne) .            |   \n ");
                    printf("                                  |   5. Inserer une voiture .                       |   \n ");
                    printf("                                  |   6. Revenir au menu principal .                 |   \n ");
                    printf("                                  |   "RED"7. Quitter . "RESET"                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |__________________________________________________|   \n\n ");
                    break;
                case 4:
                    moveCursorToTop();
                    printf("                                    __________________________________________________   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |             "YELLOW"  Modifier une famille    "RESET"           |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |    Veuillez choisir une option :                 |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |   1. Supprimer un parent .                       |   \n ");
                    printf("                                  |   2. Supprimer un enfant .                       |   \n ");
                    printf("                                  |   3. Supprimer une voiture .                     |   \n ");
                    printf("                                  |   "GREEN"4. Inserer un enfant (nouveau ne) .  "RESET"          |   \n ");
                    printf("                                  |   5. Inserer une voiture .                       |   \n ");
                    printf("                                  |   6. Revenir au menu principal .                 |   \n ");
                    printf("                                  |   "RED"7. Quitter . "RESET"                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |__________________________________________________|   \n\n ");
                    break;
                case 5:
                    moveCursorToTop();
                    printf("                                    __________________________________________________   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |             "YELLOW"  Modifier une famille    "RESET"           |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |    Veuillez choisir une option :                 |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |   1. Supprimer un parent .                       |   \n ");
                    printf("                                  |   2. Supprimer un enfant .                       |   \n ");
                    printf("                                  |   3. Supprimer une voiture .                     |   \n ");
                    printf("                                  |   4. Inserer un enfant (nouveau ne) .            |   \n ");
                    printf("                                  |   "GREEN"5. Inserer une voiture . "RESET"                      |   \n ");
                    printf("                                  |   6. Revenir au menu principal .                 |   \n ");
                    printf("                                  |   "RED"7. Quitter . "RESET"                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |__________________________________________________|   \n\n ");
                    break;
                case 6:
                    moveCursorToTop();
                    printf("                                    __________________________________________________   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |              "YELLOW" Modifier une famille   "RESET"            |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |    Veuillez choisir une option :                 |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |   1. Supprimer un parent .                       |   \n ");
                    printf("                                  |   2. Supprimer un enfant .                       |   \n ");
                    printf("                                  |   3. Supprimer une voiture .                     |   \n ");
                    printf("                                  |   4. Inserer un enfant (nouveau ne) .            |   \n ");
                    printf("                                  |   5. Inserer une voiture .                       |   \n ");
                    printf("                                  |   "GREEN"6. Revenir au menu principal .  "RESET"               |   \n ");
                    printf("                                  |   "RED"7. Quitter . "RESET"                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |__________________________________________________|   \n\n ");
                    break;
                case 7:
                    moveCursorToTop();
                    printf("                                    __________________________________________________   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |               "YELLOW"Modifier une famille   "RESET"            |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |    Veuillez choisir une option :                 |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |   1. Supprimer un parent .                       |   \n ");
                    printf("                                  |   2. Supprimer un enfant .                       |   \n ");
                    printf("                                  |   3. Supprimer une voiture .                     |   \n ");
                    printf("                                  |   4. Inserer un enfant (nouveau ne) .            |   \n ");
                    printf("                                  |   5. Inserer une voiture .                       |   \n ");
                    printf("                                  |   6. Revenir au menu principal .                 |   \n ");
                    printf("                                  |   "GREEN"7. Quitter . "RESET"                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |__________________________________________________|   \n\n ");
                    break;
            }
        
    }
    *choix=cpt;
}

void sous_menu_exporter(int *choix){
    //clear_screen();
    int cpt=0;
    bool enter = false ;
    printf("                                    __________________________________________________   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |           "YELLOW"    Exporter un fichier  "RESET"              |   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |    Veuillez choisir le fichier à exporter :      |   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |   1. Rapport sur la population .                 |   \n ");
    printf("                                  |   2. Statistiques sur la population .            |   \n ");
    printf("                                  |   3. Comparaison entre deux populations .        |   \n ");
    printf("                                  |   4. Extrait de naissance d'un nouveau ne .      |   \n ");
    printf("                                  |   5. Rapport sur le vol de voiture .             |   \n ");
    printf("                                  |   6. Revenir au menu principal .                 |   \n ");
    printf("                                  |   "RED"7. Quitter .  "RESET"                                 |   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |__________________________________________________|   \n\n ");
    while (!enter){
        *choix = detecte(&cpt , 7 , &enter) ;
        if(*choix > 0) return ;
        switch (cpt){
            case 1:
                moveCursorToTop();
                printf("                                    __________________________________________________   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |           "YELLOW"    Exporter un fichier      "RESET"          |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |    Veuillez choisir le fichier à exporter :      |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |   "GREEN"1. Rapport sur la population . "RESET"                |   \n ");
                printf("                                  |   2. Statistiques sur la population .            |   \n ");
                printf("                                  |   3. Comparaison entre deux populations .        |   \n ");
                printf("                                  |   4. Extrait de naissance d'un nouveau ne .      |   \n ");
                printf("                                  |   5. Rapport sur le vol de voiture .             |   \n ");
                printf("                                  |   6. Revenir au menu principal .                 |   \n ");
                printf("                                  |   "RED"7. Quitter .  "RESET"                                 |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |__________________________________________________|   \n\n ");
                break;
            case 2:
                moveCursorToTop();
                printf("                                    __________________________________________________   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |           "YELLOW"    Exporter un fichier    "RESET"            |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |    Veuillez choisir le fichier à exporter :      |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |   1. Rapport sur la population .                 |   \n ");
                printf("                                  |   "GREEN"2. Statistiques sur la population . "RESET"           |   \n ");
                printf("                                  |   3. Comparaison entre deux populations .        |   \n ");
                printf("                                  |   4. Extrait de naissance d'un nouveau ne .      |   \n ");
                printf("                                  |   5. Rapport sur le vol de voiture .             |   \n ");
                printf("                                  |   6. Revenir au menu principal .                 |   \n ");
                printf("                                  |   "RED"7. Quitter .  "RESET"                                 |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |__________________________________________________|   \n\n ");
                break;
            case 3:
                moveCursorToTop();
                printf("                                    __________________________________________________   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |           "YELLOW"    Exporter un fichier  "RESET"              |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |    Veuillez choisir le fichier à exporter :      |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |   1. Rapport sur la population .                 |   \n ");
                printf("                                  |   2. Statistiques sur la population .            |   \n ");
                printf("                                  |   "GREEN"3. Comparaison entre deux populations . "RESET"       |   \n ");
                printf("                                  |   4. Extrait de naissance d'un nouveau ne .      |   \n ");
                printf("                                  |   5. Rapport sur le vol de voiture .             |   \n ");
                printf("                                  |   6. Revenir au menu principal .                 |   \n ");
                printf("                                  |   "RED"7. Quitter .  "RESET"                                 |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |__________________________________________________|   \n\n ");
                break;
            case 4:
                moveCursorToTop();
                printf("                                    __________________________________________________   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |            "YELLOW"   Exporter un fichier  "RESET"              |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |    Veuillez choisir le fichier à exporter :      |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |   1. Rapport sur la population .                 |   \n ");
                printf("                                  |   2. Statistiques sur la population .            |   \n ");
                printf("                                  |   3. Comparaison entre deux populations .        |   \n ");
                printf("                                  |   "GREEN"4. Extrait de naissance d'un nouveau ne . "RESET"     |   \n ");
                printf("                                  |   5. Rapport sur le vol de voiture .             |   \n ");
                printf("                                  |   6. Revenir au menu principal .                 |   \n ");
                printf("                                  |   "RED"7. Quitter .  "RESET"                                 |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |__________________________________________________|   \n\n ");
                break;
            case 5:
                moveCursorToTop();
                printf("                                    __________________________________________________   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |          "YELLOW"     Exporter un fichier  "RESET"              |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |    Veuillez choisir le fichier à exporter :      |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |   1. Rapport sur la population .                 |   \n ");
                printf("                                  |   2. Statistiques sur la population .            |   \n ");
                printf("                                  |   3. Comparaison entre deux populations .        |   \n ");
                printf("                                  |   4. Extrait de naissance d'un nouveau ne .      |   \n ");
                printf("                                  |   "GREEN"5. Rapport sur le vol de voiture ."RESET"             |   \n ");
                printf("                                  |   6. Revenir au menu principal .                 |   \n ");
                printf("                                  |   "RED"7. Quitter .  "RESET"                                 |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |__________________________________________________|   \n\n ");
                break;
            case 6:
                moveCursorToTop();
                printf("                                    __________________________________________________   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |            "YELLOW"   Exporter un fichier  "RESET"              |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |    Veuillez choisir le fichier à exporter :      |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |   1. Rapport sur la population .                 |   \n ");
                printf("                                  |   2. Statistiques sur la population .            |   \n ");
                printf("                                  |   3. Comparaison entre deux populations .        |   \n ");
                printf("                                  |   4. Extrait de naissance d'un nouveau ne .      |   \n ");
                printf("                                  |   5. Rapport sur le vol de voiture .             |   \n ");
                printf("                                  |   "GREEN"6. Revenir au menu principal .   "RESET"              |   \n ");
                printf("                                  |   "RED"7. Quitter .  "RESET"                                 |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |__________________________________________________|   \n\n ");
                break;
            case 7:
                moveCursorToTop();
                printf("                                    __________________________________________________   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |           "YELLOW"    Exporter un fichier     "RESET"           |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |    Veuillez choisir le fichier à exporter :      |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |   1. Rapport sur la population .                 |   \n ");
                printf("                                  |   2. Statistiques sur la population .            |   \n ");
                printf("                                  |   3. Comparaison entre deux populations .        |   \n ");
                printf("                                  |   4. Extrait de naissance d'un nouveau ne .      |   \n ");
                printf("                                  |   5. Rapport sur le vol de voiture .             |   \n ");
                printf("                                  |   6. Revenir au menu principal .                 |   \n ");
                printf("                                  |   "GREEN"7. Quitter .  "RESET"                                 |   \n ");
                printf("                                  |                                                  |   \n ");
                printf("                                  |__________________________________________________|   \n\n ");
                break;
            }
        
    }
    *choix=cpt;
}

void menu_principal(int * choix){
    int ch,cpt=0;
    printf("                                    __________________________________________________   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |               "YELLOW"  TP1 realise par    "RESET"              |   \n ");
    printf("                                  |   "JAUNE"Merzougui Mohamed Abdeljalil & Ladjouzi Imene "RESET" |   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |            Bienvenu au menu principal   "RESET"         |   \n ");
    printf("                                  |           "GREEN" --------------------------  "RESET"          |   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |    Veuillez choisir une option                   |   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |   1. Partie-I .                                  |   \n ");
    printf("                                  |   2. Partie-II .                                 |   \n ");
    printf("                                  |   "RED"3. Quitter . "RESET"                                  |   \n ");
    printf("                                  |                                                  |   \n ");
    printf("                                  |__________________________________________________|   \n ");
    bool enter = false;
    while (!enter){
       *choix = detecte(&cpt , 3 , &enter) - 4 ;
        if (*choix > 0) return ;
            switch(cpt){
                case 1:
                    moveCursorToTop();
                    printf("                                    __________________________________________________   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |              "YELLOW"   TP1 realise par     "RESET"             |   \n ");
                    printf("                                  |  "JAUNE" Merzougui Mohamed Abdeljalil & Ladjouzi Imene "RESET" |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |            Bienvenu au menu principal   "RESET"         |   \n ");
                    printf("                                  |         "GREEN"   --------------------------   "RESET"         |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |    Veuillez choisir une option                   |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |  "GREEN" 1. Partie-I . "RESET"                                 |   \n ");
                    printf("                                  |   2. Partie-II .                                 |   \n ");
                    printf("                                  |   "RED"3. Quitter . "RESET"                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |__________________________________________________|   \n ");
                    break;
                case 2:
                    moveCursorToTop();
                    printf("                                    __________________________________________________   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |              "YELLOW"   TP1 realise par     "RESET"             |   \n ");
                    printf("                                  |  "JAUNE" Merzougui Mohamed Abdeljalil & Ladjouzi Imene "RESET" |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |            Bienvenu au menu principal   "RESET"         |   \n ");
                    printf("                                  |           "GREEN" --------------------------    "RESET"        |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |    Veuillez choisir une option                   |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |   1. Partie-I .                                  |   \n ");
                    printf("                                  |  "GREEN" 2. Partie-II . "RESET"                                |   \n ");
                    printf("                                  |   "RED"3. Quitter . "RESET"                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |__________________________________________________|   \n ");
                    break;
                case 3:
                    moveCursorToTop();
                    printf("                                    __________________________________________________   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |            "YELLOW"     TP1 realise par      "RESET"            |   \n ");
                    printf("                                  |  "JAUNE" Merzougui Mohamed Abdeljalil & Ladjouzi Imene "RESET" |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |            Bienvenu au menu principal   "RESET"         |   \n ");
                    printf("                                  |           "GREEN" --------------------------    "RESET"        |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |    Veuillez choisir une option                   |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |   1. Partie-I .                                  |   \n ");
                    printf("                                  |   2. Partie-II .                                 |   \n ");
                    printf("                                  |   "GREEN"3. Quitter . "RESET"                                  |   \n ");
                    printf("                                  |                                                  |   \n ");
                    printf("                                  |__________________________________________________|   \n ");
                    break;
            }
        
     }
     *choix=cpt;
}

void modifier_famille(pf famille,ch20 nomfam) {
    int choix;
    pp temp1;
    pv temp2;
    pf copie2=NULL;


    do {
        sleep(1);
        clear_screen();
        printf(RESET);
        sous_menu_modf(&choix);
        switch (choix) {

            case 1: {//supprimer parent
                char sexe;
                do{
                    printf("\n    Entrez le sexe du parent a supprimer (M/F) : ");
                    scanf(" %c", &sexe);
                    sexe=toupper(sexe);
                }while (sexe!='M'&&sexe!='F');
                if (confirmation()) {
                    bool ext=false; 
                    supprimer_parent(famille,sexe,&ext);
                    if (ext){
                        allouer_famille(&copie2);
                        aff_famille(copie2,nomfam,famille->parent,famille->enfant,famille->voiture);
                        aff_adresse_famille(copie2,NULL);
                        
                        printf(GREEN"\n   Parent supprime avec succes.\n"RESET);
                        printf(YELLOW"\n\n\n        -> "RESET"Voici la famille apres modification :\n\n");
                        print_famille1(copie2);
                    }
                    else printf (RED"\n     Le parent n'existe pas dans cette famille!\n\n"RESET);
                } else {
                    printf(RED"\n     Operation annulee.\n");
                }
                break;
            }
            case 2: {//supprimer enfant
                ch20 nom_enfant;
                printf("\n    Entrez le prenom de l'enfant a supprimer : ");
                scanf("%s", nom_enfant);
                if (confirmation()) {
                    temp1=famille->enfant;
                    if(existe_str_liste(NULL,temp1,nom_enfant)){
                        famille->enfant=supprimer_enfant(temp1, nom_enfant);
                        allouer_famille(&copie2);
                        aff_famille(copie2,nomfam,famille->parent,famille->enfant,famille->voiture);
                        aff_adresse_famille(copie2,NULL);
                        printf(GREEN"\n   Enfant supprime avec succes.\n"RESET);
                        printf(YELLOW"\n\n\n        -> "RESET"Voici la famille apres modification :\n\n");
                        print_famille1(copie2);
                    }
                    else printf(RED"\n      L'enfant n'existe pas dans la famille!\n\n"RESET);
                } else {
                    printf(RED"     Operation annulee.\n"RESET);
                }
                break;
            }
            case 3: {//supprimer voiture
                ch20 matricule;
                printf("\n    Entrez le matricule de la voiture a supprimer : ");
                scanf("%s", matricule);
                if (confirmation()) {
                    temp2=famille->voiture;
                    if (RechFamVoit_1(famille,matricule)==famille){
                        temp2=supprimer_voiture(temp2, matricule);
                        allouer_famille(&copie2);
                        aff_famille(copie2,nomfam,famille->parent,famille->enfant,famille->voiture);
                        aff_adresse_famille(copie2,NULL);
                        printf(GREEN"   Voiture supprimee avec succes.\n\n"RESET);
                        printf(YELLOW"\n\n\n        -> "RESET"Voici la famille apres modification :\n\n");
                        print_famille1(copie2);
                    }
                    else printf(RED"\n      La voiture n'est pas possedée par cette famille!\n\n"RESET);
                } else {
                    printf(RED"     Operation annulee.\n"RESET);
                }
                break;
            }
            case 4: {// inserer enfant
                char sexe;
                ch20 nom_enfant;
                printf("    Entrez le nom du nouveau-ne : ");
                scanf("%s", nom_enfant);
                do{
                printf("    Entrez le sexe du nouveau-ne (M/F) : ");
                scanf(" %c", &sexe);
                sexe=toupper(sexe);
                }while (sexe!='M'&&sexe!='F');
                if (confirmation ()) {
                    naissanceTrie(famille, nomfam, nom_enfant, sexe);
                    allouer_famille(&copie2);
                    aff_famille(copie2,nomfam,famille->parent,famille->enfant,famille->voiture);
                    aff_adresse_famille(copie2,NULL);
                    printf(GREEN"    Enfant insere avec succes.\n"RESET);
                    printf(YELLOW"\n\n\n        -> "RESET"Voici la famille apres modification :\n\n");
                    print_famille1(copie2);
                } else {
                    printf(RED"\n   Operation annulee.\n"RESET);
                }
                break;
            }
            case 5: {// inserer voiture
                ch20 matricule, marque;
                printf("    Entrez le matricule de la nouvelle voiture : ");
                scanf("%s", matricule);
                printf("    Entrez la marque de la voiture : ");
                scanf("%s", marque);
                if (confirmation ()) {
                    temp2=famille->voiture;
                    famille->voiture=inserer_voiture(temp2, marque, matricule);
                    allouer_famille(&copie2);
                    aff_famille(copie2,nomfam,famille->parent,famille->enfant,famille->voiture);
                    aff_adresse_famille(copie2,NULL);
                    printf(GREEN"   Voiture inseree avec succes.\n"RESET);
                    printf(YELLOW"\n\n\n        -> "RESET"Voici la famille apres modification :\n\n");
                    print_famille1(copie2);
                } else {
                    printf(RED"\n    Operation annulee.\n"RESET);
                }
                break;
            }
            case 6:// revenir
                return;
            case 7:
                printf(RED"Quitter le programme...\n"RESET);
                exit(0);
            default:
                printf(RED"Choix invalide. Veuillez reessayer.\n"RESET);
        }
        printf("        Appuyez sur une touche pour continuer...");
        _getch();
    } while (choix != 6);
}

void modifier_pop(pf *pop){
    int choix;
    bool menu=true;
    pf temp;
    ch20 nom,name_copy,arr[25];
    bool ext = false ;
    while(menu) {
        sleep(1);
        clear_screen();
        sous_menu_modp(&choix);
        switch (choix) {  
            case 1: //Ajouter famille      //lalaaaaaaaa ana ma 9ritch mlih
                printf(YELLOW" -> "RESET"Veuillez entrer le nom de la famille a inserer ") ;
                scanf("%s",nom) ;
                while(present_famille(*pop,nom) != NULL){ // l'utilisateur doit entrer un nom qui n'existe pas sinon on sort
                    if(reinserer()) { // si l'utilisateur veut quand meme reinserer le nom
                        printf(YELLOW"\n -> "RESET"Veuillez entrer le nom de la famille a inserer ") ;
                        scanf("%s",nom) ;
                    } 
                    else {
                        ext = true ;
                        break ;
                    } 
                } 
                if(ext) break ; 
                if (confirmation) {
                    strcpy(name_copy,nom) ; // sauvegarder le nom
                    name_copy[0] = (name_copy[0] >= 'a' && name_copy[0] <= 'z') ? name_copy[0] - 32 : name_copy[0];  // ecrire le nom sur le format Xxxxxx
                    int N,np ;
                    printf(YELLOW" -> "RESET"Veuillez entrer le nombre de parent :") ;
                    scanf("%d",&np) ; // lire le choix de l'utilisateur
                    pp parents = remplire_parent(np) ; // creer la liste parents
                    printf(YELLOW" -> "RESET"Veuillez entrer le nombre d'enfants :") ;
                    scanf("%d",&N) ;
                    if(np == 0) {
                        while(N == 0) {
                            printf(RED"     Erreur : Une famille doit contenir au moins un enfant.\n"RESET);
                            printf(YELLOW" -> "RESET"Veuillez entrer le nombre d'enfants :") ;
                            scanf("%d",&N) ;
                        }
                    }
                    pp enfants = remplire_enfant(parents,N) ; // creer la liste enfant
                    printf(YELLOW" -> "RESET"Veuillez entrer le nombre de voitures :") ;
                    scanf("%d",&N) ;
                    pv voitures = remplire_voituer(N);
                    inserer_famille(pop,nom,parents,enfants,voitures); // probleme hna 
                    printf(GREEN"Famille inseree avec succes.\n"RESET);
                }
                else printf(RED"Operation annulee!"RESET);
                break;
            case 2: {//supprimer famille
                ch20 nomfam;
                printf(YELLOW" -> "RESET" Entrez le nom de la famille a supprimer : ");
                scanf("%s",nomfam);
                if (present_famille(*pop,nomfam)){
                    if (confirmation()) {
                        supp_famille(pop,nomfam);
                        printf(GREEN"Famille supprimee avec succes.\n"RESET);
                    } else {
                        printf(RED"Operation annulee.\n");
                    }
                } 
                else printf(RED"\n        La famille saisie n'existe pas dans la population!"RESET);
                break;
            }
            case 3:// revenir
                menu=false;
                break;
            case 4:
                printf("Quitter le programme...\n");
                exit(0);
            default:
                printf(""RED"Choix invalide. Veuillez reessayer."RESET"\n");
        }
    }
}

void exporter_fichier(pf pop1, pf pop2) {
    ch20 nom, prenom, mat;
    int choix;
    bool menu = true;
    pp temp1;
    pv temp2;

    while (menu) {
        sleep(1);
        clear_screen();
        sous_menu_exporter(&choix);
        switch (choix) {
            case 1: { // Rapport pop
                exportTxT(pop1);
                printf("\n" GREEN " -> Rapport ecrit avec succes." RESET "\n");
                break;
            }
            case 2: { // Stats sur la population
                ecrit_rapport_pop(pop1);
                printf("\n" GREEN " -> Graphs exportes avec succes." RESET "\n");
                break;
            }
            case 3: { // Comparaison
                if (pop2) {
                    ecrit_rapport_cop(pop1, pop2);
                    printf(GREEN "-> Comparaison exportee avec succes." RESET "\n");
                } else {
                    printf(RED " Veuillez d'abord creer pop2 ! " RESET "\n");
                }
                break;
            }
            case 4: { // Extrait de naissance
                printf("Veuillez saisir le nom de famille: ");
                scanf("%s", nom);

                if (present_famille(pop1, nom)) {
                    printf("Veuillez saisir le prenom de l'enfant: ");
                    scanf("%s", prenom) ;
                    temp1 = present_famille(pop1, nom)->enfant;

                    while (temp1 && strcasecmp(temp1->prenom, prenom) != 0) {
                        temp1 = suivant_personne(temp1);
                    }

                    if (temp1) {
                        cert_naissance(present_famille(pop1, nom), temp1);
                        printf(GREEN "-> Extrait de naissance exporte avec succes." RESET "\n");
                    } else {
                        printf(RED "-> Impossible de trouver l'enfant recherche." RESET "\n");
                    }
                } else {
                    printf(RED "-> Aucune famille trouvee avec ce nom!" RESET "\n");
                }
                break;
            }
            case 5: { // Rapport vol
                printf("Veuillez entrer le matricule de la voiture volee: ");
                scanf("%s", mat);

                pf famille = RechFamVoit_1(pop1, mat);
                if (famille) {
                    ecrit_rapport_vol(famille);
                    printf(GREEN " Rapport ecrit avec succes." RESET "\n");
                }
                else {
                    printf(RED "-> Aucune voiture trouvee avec ce matricule !" RESET "\n");
                }
                break;
            }
            case 6: // Revenir au menu precedent
                menu = false;
                break;
            case 7: // Quitter le programme
                printf("\nQuitter le programme...\n");
                exit(0);
            default:
                printf(RED "Choix invalide. Veuillez reessayer." RESET "\n");
        }
    }
}

bool sens_demenagement() { // Retourne true pour Pop1 -> Pop2, false pour Pop2 -> Pop1
    clear_screen();
    printf(YELLOW"          -> "RESET"Dans quel sens voulez-vous demenager une famille ? \n");
    printf("             Pop1 vers Pop2 (<-)                                  Pop2 vers Pop1 (->)\n\n");

    int ch;
    while ((ch = _getch()) != 27) {
        if (ch == 0 || ch == 224) {
            ch = _getch();
            if (ch == 75) {
                moveCursorToTop();
                printf(YELLOW"           -> "RESET"Dans quel sens voulez-vous demenager une famille ? \n");
                printf(GREEN"             Pop1 vers Pop2 (<-) "RESET"                              Pop2 vers Pop1 (->)\n\n");
                sleep(1);
                return true;
            }
            if (ch == 77) {
                moveCursorToTop();
                printf(YELLOW"           -> "RESET"Dans quel sens voulez-vous demenager une famille ? \n");
                printf("              Pop1 vers Pop2 (<-)                              "GREEN"Pop2 vers Pop1 (->)\n\n"RESET);
                sleep(1);
                return false;
            }
        }
    }
}

void partie_2(){
    ch20 rech,mod;
    pf pop1=NULL, pop2=NULL, pop3,pop4,pop5;
    int choix1;
    int val,n,val2;
    bool menu2=true,ordre=false, ecr;
    char res;

                menu2=true;
                while(menu2){
                    sleep(1);
                    clear_screen();
                    menu_2(&choix1);
                    switch (choix1){
                        case 1://creer pop
                            ordre =true;
                            if(pop1){
                                ecr=ecraser();
                                res=methode_cr();
                                if (ecr){
                                    liberer_famille(pop1);
                                    pop1=NULL;
                                    switch(res){
                                        case 'A':
                                            printf(YELLOW"       -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                            scanf("%d",&val);
                                            while(val<1){
                                                printf(YELLOW"       -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                                scanf("%d",&val);
                                            }
                                            while (getchar() != '\n');
                                            pop1=creer_famille(val);
                                            break;
                                        case 'M':
                                            printf(YELLOW"      -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                            scanf("%d",&val);
                                            while(val<1){
                                                printf(YELLOW"       -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                                scanf("%d",&val);
                                            }
                                            while (getchar() != '\n');
                                            pop1=creer_famille_manuel(val);
                                            break;
                                        case 'F':
                                            pop1=import_famille();
                                            break;
                                        printf ("\n\n     -> "RESET"Voulez-vous exporter un rapport sur la population?");
                                        if (choix()){
                                            ecrit_rapport_pop(pop1);
                                            printf(GREEN"\n\n   Rapport exporte avec succes!"RESET);
                                        }
                                    }
                                    printf ("\n\n     -> "RESET"Voulez-vous exporter un rapport sur la population?");
                                    if (choix()){
                                        ecrit_rapport_pop(pop1);
                                        printf(GREEN"\n\n    Rapport exporte avec succes!"RESET);
                                        
                                    }
                                    treer_famille(pop1);
                                }
                                else{
                                    liberer_famille(pop2);
                                    pop2=NULL;
                                    switch(res){
                                        case 'A':
                                            printf(YELLOW"      -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                            scanf("%d",&val);
                                            while(val<1){
                                                printf(YELLOW"      -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                                scanf("%d",&val);
                                            }
                                            while (getchar() != '\n');
                                            pop2=creer_famille(val);
                                            break;

                                        case 'M':
                                            printf(YELLOW"      -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                            scanf("%d",&val);
                                            while(val<1){
                                                printf(YELLOW"       -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                                scanf("%d",&val);
                                            }
                                            while (getchar() != '\n');
                                            pop2=creer_famille_manuel(val);
                                            break;
                                        case 'F':
                                        pop2=import_famille();
                                        break;
                                }
                                printf ("\n\n     -> "RESET"Voulez-vous exporter une comparaison entre les pop1 et pop2?");
                                if (choix()){
                                        ecrit_rapport_cop(pop1,pop2);
                                        printf(GREEN"\n\n   Rapport exporte avec succes!"RESET);
                                    }
                                treer_famille(pop2);
                            }
                        }
                        else {
                            res=methode_cr();
                            switch(res){
                                case 'A':
                                    printf(YELLOW"       -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                    scanf("%d",&val);
                                    while(val<1){
                                        printf(YELLOW"       -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                        scanf("%d",&val);
                                    }
                                    while (getchar() != '\n');
                                    pop1=creer_famille(val);
                                    break;

                                case 'M':
                                    printf(YELLOW"      -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                    scanf("%d",&val);
                                    getchar() ;
                                    while(val<1){
                                        printf(YELLOW"      -> "RESET"Veuillez entrer le nombre de famille de la population : ");
                                        scanf("%d",&val);
                                        getchar() ;
                                    }
                                    pop1=creer_famille_manuel(val);
                                    break;
                                case 'F':
                                    pop1=import_famille();
                                    break;

                            }
                            printf ("\n\n     -> "RESET"Voulez-vous exporter un rapport sur la population?");
                            if (choix()){
                                ecrit_rapport_pop(pop1);
                                printf(GREEN"\n\n    Rapport exporte avec succes!"RESET);
                                
                            }
                            treer_famille(pop1);
                        }
                            break;
                        case 2://Afficher pop
                            if(ordre){
                                if(pop2){
                                    treer_famille(pop1) ;
                                    treer_famille(pop2) ;
                                    if (manip())
                                        print_famille1(pop1);
                                    else
                                        print_famille1(pop2);
                                }
                                else print_famille1(pop1);
                                _getch();
                            }
                            else{
                                printf("\n\n      "RED"Vous devez d'abord creer la population."RESET"");
                            }
                            break;
                        case 3: // nb de familles sant parents
                            if (ordre){
                                if (pop2){
                                if(manip())
                                    printf(YELLOW"       -> "RESET"Le nombre de familles sans parents dans la population 1 est:   %d .",nbfamillesansparent(pop1));
                                else
                                    printf(YELLOW"       -> "RESET"Le nombre de familles sans parents dans la population 2 est:   %d .",nbfamillesansparent(pop2));
                                }
                                else printf(YELLOW"        -> "RESET"Le nombre de familles sans parents dans la population 1 est:   %d .",nbfamillesansparent(pop1));
                                _getch();
                            }
                            else{
                                printf("\n\n"RED"         Vous devez d'abord creer la population."RESET"");
                            }
                            break;
                        case 4://Nbenfpop
                            if(ordre){
                                if (pop2){
                                    if (manip()) printf("\n\n"YELLOW"        -> "RESET"Le nombre d'enfants total dans la population 1 est :    %d",nbenfant(pop1));
                                    else printf("\n\n"YELLOW"        -> "RESET"Le nombre d'enfants total dans la population 2 est :    %d",nbenfant(pop2));
                                }
                                else printf("\n\n"YELLOW"        -> "RESET"Le nombre d'enfants total dans la population est :    %d",nbenfant(pop1));
                                _getch();
                            }
                            else{
                                printf("\n\n      "RED"Vous devez d'abord creer la population."RESET"");
                            }
                            break;
                        case 5://nombre d'enfant d'une famille
                            if(ordre){
                                if (pop2){
                                    if (manip()){
                                        printf("\n\n"YELLOW"        -> "RESET"Veuillez saisir le nom de la famille dont vous souhaitez calculer le nombre d'enfant :  ");
                                        scanf("%s",rech);
                                        getchar();
                                        if (present_famille(pop1, rech))
                                            printf("\n"YELLOW"      -> "RESET"Le nombre d'enfants de la famille %s est: %d",rech,nbenfnomfam(pop1,rech));
                                        else{
                                            printf(RED"\n       La famille saisie n'existe pas dans la population!"RESET);
                                        }
                                    }
                                    else {
                                        printf("\n\n"YELLOW"        -> "RESET"Veuillez saisir le nom de la famille dont vous souhaitez calculer le nombre d'enfant :  ");
                                        scanf("%s",rech);
                                        getchar();
                                        if (present_famille(pop2, rech))
                                            printf("\n"YELLOW"       -> "RESET"Le nombre d'enfants de la famille %s est: %d",rech,nbenfnomfam(pop2,rech));
                                        else{
                                            printf(RED"\n        La famille saisie n'existe pas dans la population!"RESET);
                                        }
                                    }
                                }
                                else {
                                    printf("\n\n"YELLOW"     -> "RESET"Veuillez saisir le nom de la famille dont vous souhaitez calculer le nombre d'enfant :  ");
                                    scanf("%s",rech);
                                    getchar();
                                    if (present_famille(pop1, rech))
                                        printf("\n"YELLOW"       -> "RESET"Le nombre d'enfants de la famille %s est: %d",rech,nbenfnomfam(pop1,rech));
                                    else{
                                        printf(RED"         La famille saisie n'existe pas dans la population!"RESET);
                                    }
                                }
                                _getch();
                            }
                            else{
                                printf("\n\n"RED"         Vous devez d'abord creer la population."RESET"");
                            }
                            break;
                        case 6://Modifier pop
                            if(ordre){
                                if(pop2){
                                    if(manip()) modifier_pop(&pop1);
                                    else modifier_pop(&pop2);
                                }
                                else
                                    modifier_pop(&pop1);
                                continue;
                            }
                            else{
                                printf("\n\n"RED"         Vous devez d'abord creer la population."RESET"");
                            }
                            break;
                        case 7: //Modifier famille
                            if(ordre){
                                if(pop2){
                                    if (manip()){
                                        printf(YELLOW"       -> "RESET"Veuillez entrer le nom de la famille a modifier :");
                                        scanf("%s",mod);
                                        getchar();
                                        if (present_famille(pop1, mod))
                                            modifier_famille(present_famille(pop1,mod),mod);
                                        else{
                                            printf(RED"\n       La famille saisie n'existe pas dans la population!"RESET);
                                        }
                                    }
                                    else {
                                        printf(YELLOW"      -> "RESET"Veuillez entrer le nom de la famille a modifier :");
                                        scanf("%s",mod);
                                        getchar();
                                        if (present_famille(pop2, mod))
                                            modifier_famille(present_famille(pop2,mod),mod);
                                        else{
                                            printf("\n      La famille saisie n'existe pas dans la population!");
                                        }
                                    }
                                }
                                else {
                                    printf(YELLOW"      -> "RESET"Veuillez entrer le nom de la famille a modifier :");
                                    scanf("%s",mod);
                                    if (present_famille(pop1, mod))
                                        modifier_famille(present_famille(pop1,mod),mod);
                                    else{
                                        printf(RED"\n       La famille saisie n'existe pas dans la population!"RESET);
                                    }
                                }
                                continue;
                            }
                            else{
                                printf("\n\n          "RED"Vous devez d'abord creer la population."RESET"");
                            }
                            break;
                        case 8: //fusion
                            if (ordre){
                                if(pop2){
                                    printf("\n"YELLOW"       -> "RESET"Voici la 1ere population :\n\n");
                                    print_famille1(pop1);
                                    printf("\n\n"YELLOW"         -> "RESET"Voici la 2eme population :\n\n");
                                    print_famille1(pop2);
                                    _getch();
                                    res=methode_fu();
                                    if(res=='1'&&confirmation()){
                                        pop3=copier_pop(pop2); 
                                        pop1=fusion1(pop1,pop3);
                                        printf("\n      Appuyez sur une touche pour continuer..."); 
                                        _getch();
                                        clear_screen();
                                        printf(YELLOW"          -> "RESET"Voici le resultat de la fusion :\n");
                                        print_famille1(pop1);
                                    }
                                    else if(res=='2'&&confirmation()){
                                            pop3=copier_pop(pop1);
                                            pop2=fusion1(pop2,pop3);
                                            printf("\n      Appuyez sur une touche pour continuer...");
                                            _getch();
                                            clear_screen();
                                            printf(YELLOW"          -> "RESET"Voici le resultat de la fusion :\n");
                                            print_famille1(pop2);
                                        }
                                        else if(res=='3'&&confirmation()){
                                                pop4=copier_pop(pop1);
                                                pop5=copier_pop(pop2);
                                                pop3=fusion1(pop4,pop5);
                                                printf("\n     Appuyez sur une touche pour continuer...");
                                                _getch();
                                                clear_screen();
                                                printf(YELLOW"          -> "RESET"Voici le resultat de la fusion :\n");
                                                print_famille1(pop3);
                                            }
                                }
                                else printf(""RED"          Vous devez d'abord creer la 2eme population"RESET"");
                                _getch();
                            }
                            else{
                                printf("\n\n"RED"         Vous devez d'abord creer la population."RESET"");
                            }
                            break;
                        case 9: //demenagement
                            if (pop1 && pop2) {
                                if (sens_demenagement()) {
                                    demenager_famille(&pop1, &pop2); // Pop1 -> Pop2
                                } else {
                                    demenager_famille(&pop2, &pop1); // Pop2 -> Pop1
                                }
                                _getch();
                            } else {
                                printf(RED"\n           Les deux populations doivent exister pour effectuer un demenagement.\n"RESET);
                            }
                            break ;
                        case 10: //Rechvoit
                            if (ordre){
                                if (pop2){
                                    if(manip()){
                                        printf(YELLOW"       -> "RESET"Veuillez saisir le matricule de la voiture volee: ");
                                        scanf("%s",&rech);
                                        pop5=RechFamVoit_1(pop1,rech);
                                        if(pop5){
                                            printf("\n\n"YELLOW"         -> "RESET"La voiture volee appartient a la famille  %s ",pop5->nom);
                                            printf (YELLOW"\n\n       -> "RESET"Voulez-vous exporter un rapport sur le vol?");
                                            if (choix()){
                                                ecrit_rapport_vol(pop5);
                                                printf(GREEN"\n\n     Rapport exporte avec succes!"RESET);
                                            }
                                        }
                                        else {
                                            printf("\n\n"RED"       La voiture volee n'appartient a aucune famille de la population!"RESET"");
                                        }
                                    }
                                    else {
                                        printf(YELLOW"      -> "RESET"Veuillez saisir le matricule de la voiture volee: ");
                                        scanf("%s",&rech);
                                        pop5=RechFamVoit_1(pop2,rech);
                                        if(pop5){
                                            printf("\n\n"YELLOW"         -> "RESET"La voiture volee appartient a la famille  %s ",pop5->nom);
                                            printf (YELLOW"\n\n       -> "RESET"Voulez-vous exporter un rapport sur le vol?");
                                            if (choix()){
                                                ecrit_rapport_vol(pop5);
                                                printf(GREEN"\n\n         Rapport exporte avec succes!"RESET);
                                            }
                                        }
                                        else {
                                            printf("\n\n        "RED"La voiture volee n'appartient a aucune famille de la population!"RESET"");
                                        }
                                    }
                                }
                                else {
                                    printf(YELLOW"         -> "RESET"Veuillez saisir le matricule de la voiture volee: ");
                                    scanf("%s",&rech);
                                    pop5=RechFamVoit_1(pop1,rech);
                                    if(pop5){
                                        printf("\n\n"YELLOW"        -> "RESET"La voiture volee appartient a la famille  %s ",pop5->nom);
                                        printf (YELLOW"\n\n       -> "RESET"Voulez-vous exporter un rapport sur le vol?");
                                        if (choix()){
                                            ecrit_rapport_vol(pop5);
                                            printf(GREEN"\n\n        Rapport exporte avec succes!"RESET);
                                        }
                                    }
                                    else {
                                        printf("\n\n            "RED"La voiture volee n'appartient a aucune famille de la population!"RESET"");
                                    }
                                }
                            }
                            else{
                                printf("\n\n            "RED"Vous devez d'abord creer la population."RESET"");
                            }
                            break;
                        case 11: //exporter
                            if (ordre){
                                if(pop2){
                                    if(manip()){
                                        exporter_fichier(pop1,pop2);
                                    }
                                    else exporter_fichier(pop2,pop1);
                                }
                                else exporter_fichier(pop1,pop2);
                                continue;
                            }
                            else printf("\n\n"RED"          Vous devez d'abord creer la population."RESET"");
                            break;
                        case 12://revenir
                            menu2=false;
                            return;
                            break;
                        case 13://quitter
                            printf(RED"\n\n         Quitter le programme...\n"RESET);
                            exit(0);
                            break;
                        default:
                            printf(""RED"\n\n       Option invalide! Veuillez choisir un des choix du menu."RESET"");
                            break;
                    }
                    printf("\n          Appuyez sur une touche pour continuer...");
                    _getch();
                }
}

void menuTP(){
    int choix;
    while (1) { // Boucle infinie jusqu'a ce que l'utilisateur choisisse de quitter
        clear_screen();
        menu_principal(&choix);
        switch (choix) {
            case 1:
                partie_1();
                break;
            case 2:
                partie_2();
                break;
            case 3:
                printf(RED"\n\n        Quitter le programme...\n"RESET);
                return; // Sortie de la boucle et fin du programme
            default:
                printf(RED"\n\n        Option invalide, veuillez reessayer.\n"RESET);
                break;
        }
    }
}

void print_slow(char *text, int delay) {
    for (int i=0;text[i]!='\0';i++) {
        printf("%c",text[i]);  // Print one character at a time
        if( text[i]!=' ') usleep(delay); // Convert milliseconds to microseconds
    }
}


void moveCursorTo28() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 29}; // Position en haut à gauche
    SetConsoleCursorPosition(hConsole, coord);
}

void moveCursorTo17() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 19}; // Position en haut à gauche
    SetConsoleCursorPosition(hConsole, coord);
}

void print_name_tran(){

    moveCursorTo28();
    printf("\033[38;5;153m      ╔╦╗   ╔═╗╔╦╗╔═╗╦    ╦╔═╔═╗╦═╗╔╦╗╦\n");
    printf("\033[38;5;153m      ║║║   ╠═╣ ║║║╣ ║    ╠╩╗║╣ ╠╦╝║║║║\n");
    printf("\033[38;5;153m      ╩ ╩o  ╩ ╩═╩╝╚═╝╩═╝  ╩ ╩╚═╝╩╚═╩ ╩╩\n");
    usleep(DELAY);

    moveCursorTo28();
    printf("\033[38;5;153m           ╔╦╗   ╔═╗╔╦╗╔═╗╦    ╦╔═╔═╗╦═╗╔╦╗╦\n");
    printf("\033[38;5;153m           ║║║   ╠═╣ ║║║╣ ║    ╠╩╗║╣ ╠╦╝║║║║\n");
    printf("\033[38;5;153m           ╩ ╩o  ╩ ╩═╩╝╚═╝╩═╝  ╩ ╩╚═╝╩╚═╩ ╩╩\n");
    usleep(DELAY);

    moveCursorTo28();
    printf("\033[38;5;153m                ╔╦╗   ╔═╗╔╦╗╔═╗╦    ╦╔═╔═╗╦═╗╔╦╗╦\n");
    printf("\033[38;5;153m                ║║║   ╠═╣ ║║║╣ ║    ╠╩╗║╣ ╠╦╝║║║║\n");
    printf("\033[38;5;153m                ╩ ╩o  ╩ ╩═╩╝╚═╝╩═╝  ╩ ╩╚═╝╩╚═╩ ╩╩\n");
    usleep(DELAY);

    moveCursorTo28();
    printf("\033[38;5;153m                     ╔╦╗   ╔═╗╔╦╗╔═╗╦    ╦╔═╔═╗╦═╗╔╦╗╦\n");
    printf("\033[38;5;153m                     ║║║   ╠═╣ ║║║╣ ║    ╠╩╗║╣ ╠╦╝║║║║\n");
    printf("\033[38;5;153m                     ╩ ╩o  ╩ ╩═╩╝╚═╝╩═╝  ╩ ╩╚═╝╩╚═╩ ╩╩\n");
    usleep(DELAY);

    moveCursorTo28();
    printf("\033[38;5;153m                          ╔╦╗   ╔═╗╔╦╗╔═╗╦    ╦╔═╔═╗╦═╗╔╦╗╦\n");
    printf("\033[38;5;153m                          ║║║   ╠═╣ ║║║╣ ║    ╠╩╗║╣ ╠╦╝║║║║\n");
    printf("\033[38;5;153m                          ╩ ╩o  ╩ ╩═╩╝╚═╝╩═╝  ╩ ╩╚═╝╩╚═╩ ╩╩\n");
    usleep(DELAY);

    moveCursorTo28();
    printf("\033[38;5;153m                               ╔╦╗   ╔═╗╔╦╗╔═╗╦    ╦╔═╔═╗╦═╗╔╦╗╦\n");
    printf("\033[38;5;153m                               ║║║   ╠═╣ ║║║╣ ║    ╠╩╗║╣ ╠╦╝║║║║\n");
    printf("\033[38;5;153m                               ╩ ╩o  ╩ ╩═╩╝╚═╝╩═╝  ╩ ╩╚═╝╩╚═╩ ╩╩\n");
    usleep(DELAY);

    moveCursorTo28();
    printf("\033[38;5;153m                                   ╔╦╗   ╔═╗╔╦╗╔═╗╦    ╦╔═╔═╗╦═╗╔╦╗╦\n");
    printf("\033[38;5;153m                                   ║║║   ╠═╣ ║║║╣ ║    ╠╩╗║╣ ╠╦╝║║║║\n");
    printf("\033[38;5;153m                                   ╩ ╩o  ╩ ╩═╩╝╚═╝╩═╝  ╩ ╩╚═╝╩╚═╩ ╩╩\n");
    usleep(DELAY);

    moveCursorTo28();
    printf("\033[38;5;153m                                        ╔╦╗   ╔═╗╔╦╗╔═╗╦    ╦╔═╔═╗╦═╗╔╦╗╦\n");
    printf("\033[38;5;153m                                        ║║║   ╠═╣ ║║║╣ ║    ╠╩╗║╣ ╠╦╝║║║║\n");
    printf("\033[38;5;153m                                        ╩ ╩o  ╩ ╩═╩╝╚═╝╩═╝  ╩ ╩╚═╝╩╚═╩ ╩╩\n");
    usleep(DELAY);
    moveCursorTo28();
    printf("\033[38;5;153m                                            ╔╦╗   ╔═╗╔╦╗╔═╗╦    ╦╔═╔═╗╦═╗╔╦╗╦\n");
    printf("\033[38;5;153m                                            ║║║   ╠═╣ ║║║╣ ║    ╠╩╗║╣ ╠╦╝║║║║\n");
    printf("\033[38;5;153m                                            ╩ ╩o  ╩ ╩═╩╝╚═╝╩═╝  ╩ ╩╚═╝╩╚═╩ ╩╩\n");
    usleep(DELAY);

    moveCursorTo28();
    printf("\033[38;5;153m                                                ╔╦╗   ╔═╗╔╦╗╔═╗╦    ╦╔═╔═╗╦═╗╔╦╗╦\n");
    printf("\033[38;5;153m                                                ║║║   ╠═╣ ║║║╣ ║    ╠╩╗║╣ ╠╦╝║║║║\n");
    printf("\033[38;5;153m                                                ╩ ╩o  ╩ ╩═╩╝╚═╝╩═╝  ╩ ╩╚═╝╩╚═╩ ╩╩\n");
    usleep(DELAY);

    moveCursorTo28();
    printf("\033[38;5;153m                                                      ╔╦╗   ╔═╗╔╦╗╔═╗╦    ╦╔═╔═╗╦═╗╔╦╗╦\n");
    printf("\033[38;5;153m                                                      ║║║   ╠═╣ ║║║╣ ║    ╠╩╗║╣ ╠╦╝║║║║\n");
    printf("\033[38;5;153m                                                      ╩ ╩o  ╩ ╩═╩╝╚═╝╩═╝  ╩ ╩╚═╝╩╚═╩ ╩╩\n");
}

void prin_names(){
    usleep(DELAY);

    moveCursorTo17() ;
    printf(" \033[38;5;153m     ╦  ╔═╗╔╦╗ ╦╔═╗╦ ╦╔═╗╦  ╦╔╦╗╔═╗╔╗╔╔═╗   \033[38;5;32m ╔═╗ ╔╗╔═╗\n");
    printf(" \033[38;5;153m     ║  ╠═╣ ║║ ║║ ║║ ║╔═╝║  ║║║║║╣ ║║║║╣    \033[38;5;32m ║ ╦  ║╠═╗\n");
    printf(" \033[38;5;153m     ╩═╝╩ ╩═╩╝╚╝╚═╝╚═╝╚═╝╩  ╩╩ ╩╚═╝╝╚╝╚═╝   \033[38;5;32m ╚═╝  ╩╚═╝\n\n\n\n");
    usleep(DELAY);

    moveCursorTo17() ;
    printf("\033[38;5;32m ║║ \033[38;5;153m     ╦  ╔═╗╔╦╗ ╦╔═╗╦ ╦╔═╗╦  ╦╔╦╗╔═╗╔╗╔╔═╗   \033[38;5;32m ╔═╗ ╔╗╔═╗\n");
    printf("\033[38;5;32m ║║ \033[38;5;153m     ║  ╠═╣ ║║ ║║ ║║ ║╔═╝║  ║║║║║╣ ║║║║╣    \033[38;5;32m ║ ╦  ║╠═╗\n");
    printf("\033[38;5;32m ║║ \033[38;5;153m     ╩═╝╩ ╩═╩╝╚╝╚═╝╚═╝╚═╝╩  ╩╩ ╩╚═╝╝╚╝╚═╝   \033[38;5;32m ╚═╝  ╩╚═╝\n\n\n\n");
    usleep(DELAY);

    moveCursorTo17() ;
    printf("    \033[38;5;21m  ║║ \033[38;5;153m     ╦  ╔═╗╔╦╗ ╦╔═╗╦ ╦╔═╗╦  ╦╔╦╗╔═╗╔╗╔╔═╗   \033[38;5;32m ╔═╗ ╔╗╔═╗\n");
    printf("    \033[38;5;21m  ║║ \033[38;5;153m     ║  ╠═╣ ║║ ║║ ║║ ║╔═╝║  ║║║║║╣ ║║║║╣    \033[38;5;32m ║ ╦  ║╠═╗\n");
    printf("    \033[38;5;21m  ║║ \033[38;5;153m     ╩═╝╩ ╩═╩╝╚╝╚═╝╚═╝╚═╝╩  ╩╩ ╩╚═╝╝╚╝╚═╝   \033[38;5;32m ╚═╝  ╩╚═╝\n\n\n\n");
    usleep(DELAY);

    moveCursorTo17() ;
    printf("\033[38;5;32m ╔═╗ ╔╗╔═╗    \033[38;5;21m  ║║ \033[38;5;153m     ╦  ╔═╗╔╦╗ ╦╔═╗╦ ╦╔═╗╦  ╦╔╦╗╔═╗╔╗╔╔═╗   \033[38;5;32m ╔═╗ ╔╗╔═╗\n");
    printf("\033[38;5;32m ║ ╦  ║╠═╗    \033[38;5;21m  ║║ \033[38;5;153m     ║  ╠═╣ ║║ ║║ ║║ ║╔═╝║  ║║║║║╣ ║║║║╣    \033[38;5;32m ║ ╦  ║╠═╗\n");
    printf("\033[38;5;32m ╚═╝  ╩╚═╝    \033[38;5;21m  ║║ \033[38;5;153m     ╩═╝╩ ╩═╩╝╚╝╚═╝╚═╝╚═╝╩  ╩╩ ╩╚═╝╝╚╝╚═╝   \033[38;5;32m ╚═╝  ╩╚═╝\n\n\n\n");
    usleep(DELAY);

    moveCursorTo17() ;
    printf("╔╦╗   \033[38;5;32m ╔═╗ ╔╗╔═╗    \033[38;5;21m  ║║ \033[38;5;153m     ╦  ╔═╗╔╦╗ ╦╔═╗╦ ╦╔═╗╦  ╦╔╦╗╔═╗╔╗╔╔═╗   \033[38;5;32m ╔═╗ ╔╗╔═╗\n");
    printf(" ║║   \033[38;5;32m ║ ╦  ║╠═╗    \033[38;5;21m  ║║ \033[38;5;153m     ║  ╠═╣ ║║ ║║ ║║ ║╔═╝║  ║║║║║╣ ║║║║╣    \033[38;5;32m ║ ╦  ║╠═╗\n");
    printf("═╩╝   \033[38;5;32m ╚═╝  ╩╚═╝    \033[38;5;21m  ║║ \033[38;5;153m     ╩═╝╩ ╩═╩╝╚╝╚═╝╚═╝╚═╝╩  ╩╩ ╩╚═╝╝╚╝╚═╝   \033[38;5;32m ╚═╝  ╩╚═╝\n\n\n\n");
    usleep(DELAY);

    moveCursorTo17() ;
    printf("╔═╗╔╦╗   \033[38;5;32m ╔═╗ ╔╗╔═╗    \033[38;5;21m  ║║ \033[38;5;153m     ╦  ╔═╗╔╦╗ ╦╔═╗╦ ╦╔═╗╦  ╦╔╦╗╔═╗╔╗╔╔═╗   \033[38;5;32m ╔═╗ ╔╗╔═╗\n");
    printf("║╣  ║║   \033[38;5;32m ║ ╦  ║╠═╗    \033[38;5;21m  ║║ \033[38;5;153m     ║  ╠═╣ ║║ ║║ ║║ ║╔═╝║  ║║║║║╣ ║║║║╣    \033[38;5;32m ║ ╦  ║╠═╗\n");
    printf("╚═╝═╩╝   \033[38;5;32m ╚═╝  ╩╚═╝    \033[38;5;21m  ║║ \033[38;5;153m     ╩═╝╩ ╩═╩╝╚╝╚═╝╚═╝╚═╝╩  ╩╩ ╩╚═╝╝╚╝╚═╝   \033[38;5;32m ╚═╝  ╩╚═╝\n\n\n\n");
    usleep(DELAY);

    moveCursorTo17() ;
    printf("╔╦╗╔═╗╔╦╗   \033[38;5;32m ╔═╗ ╔╗╔═╗    \033[38;5;21m  ║║ \033[38;5;153m     ╦  ╔═╗╔╦╗ ╦╔═╗╦ ╦╔═╗╦  ╦╔╦╗╔═╗╔╗╔╔═╗   \033[38;5;32m ╔═╗ ╔╗╔═╗\n");
    printf("║║║║╣  ║║   \033[38;5;32m ║ ╦  ║╠═╗    \033[38;5;21m  ║║ \033[38;5;153m     ║  ╠═╣ ║║ ║║ ║║ ║╔═╝║  ║║║║║╣ ║║║║╣    \033[38;5;32m ║ ╦  ║╠═╗\n");
    printf("╩ ╩╚═╝═╩╝   \033[38;5;32m ╚═╝  ╩╚═╝    \033[38;5;21m  ║║ \033[38;5;153m     ╩═╝╩ ╩═╩╝╚╝╚═╝╚═╝╚═╝╩  ╩╩ ╩╚═╝╝╚╝╚═╝   \033[38;5;32m ╚═╝  ╩╚═╝\n\n\n\n");
    usleep(DELAY);

    moveCursorTo17() ;
    printf("╔═╗╔╦╗╔═╗╔╦╗   \033[38;5;32m ╔═╗ ╔╗╔═╗    \033[38;5;21m  ║║ \033[38;5;153m     ╦  ╔═╗╔╦╗ ╦╔═╗╦ ╦╔═╗╦  ╦╔╦╗╔═╗╔╗╔╔═╗   \033[38;5;32m ╔═╗ ╔╗╔═╗\n");
    printf("╠═╣║║║║╣  ║║   \033[38;5;32m ║ ╦  ║╠═╗    \033[38;5;21m  ║║ \033[38;5;153m     ║  ╠═╣ ║║ ║║ ║║ ║╔═╝║  ║║║║║╣ ║║║║╣    \033[38;5;32m ║ ╦  ║╠═╗\n");
    printf("╩ ╩╩ ╩╚═╝═╩╝   \033[38;5;32m ╚═╝  ╩╚═╝    \033[38;5;21m  ║║ \033[38;5;153m     ╩═╝╩ ╩═╩╝╚╝╚═╝╚═╝╚═╝╩  ╩╩ ╩╚═╝╝╚╝╚═╝   \033[38;5;32m ╚═╝  ╩╚═╝\n\n\n\n");
    usleep(DELAY);

    moveCursorTo17() ;
    printf("╦ ╦╔═╗╔╦╗╔═╗╔╦╗   \033[38;5;32m ╔═╗ ╔╗╔═╗    \033[38;5;21m  ║║ \033[38;5;153m     ╦  ╔═╗╔╦╗ ╦╔═╗╦ ╦╔═╗╦  ╦╔╦╗╔═╗╔╗╔╔═╗   \033[38;5;32m ╔═╗ ╔╗╔═╗\n");
    printf("╠═╣╠═╣║║║║╣  ║║   \033[38;5;32m ║ ╦  ║╠═╗    \033[38;5;21m  ║║ \033[38;5;153m     ║  ╠═╣ ║║ ║║ ║║ ║╔═╝║  ║║║║║╣ ║║║║╣    \033[38;5;32m ║ ╦  ║╠═╗\n");
    printf("╩ ╩╩ ╩╩ ╩╚═╝═╩╝   \033[38;5;32m ╚═╝  ╩╚═╝    \033[38;5;21m  ║║ \033[38;5;153m     ╩═╝╩ ╩═╩╝╚╝╚═╝╚═╝╚═╝╩  ╩╩ ╩╚═╝╝╚╝╚═╝   \033[38;5;32m ╚═╝  ╩╚═╝\n\n\n\n");
    usleep(DELAY);

    moveCursorTo17() ;
    printf("╔╦╗╔═╗╦ ╦╔═╗╔╦╗╔═╗╔╦╗   \033[38;5;32m ╔═╗ ╔╗╔═╗    \033[38;5;21m  ║║ \033[38;5;153m     ╦  ╔═╗╔╦╗ ╦╔═╗╦ ╦╔═╗╦  ╦╔╦╗╔═╗╔╗╔╔═╗   \033[38;5;32m ╔═╗ ╔╗╔═╗\n");
    printf("║║║║ ║╠═╣╠═╣║║║║╣  ║║   \033[38;5;32m ║ ╦  ║╠═╗    \033[38;5;21m  ║║ \033[38;5;153m     ║  ╠═╣ ║║ ║║ ║║ ║╔═╝║  ║║║║║╣ ║║║║╣    \033[38;5;32m ║ ╦  ║╠═╗\n");
    printf("╩ ╩╚═╝╩ ╩╩ ╩╩ ╩╚═╝═╩╝   \033[38;5;32m ╚═╝  ╩╚═╝    \033[38;5;21m  ║║ \033[38;5;153m     ╩═╝╩ ╩═╩╝╚╝╚═╝╚═╝╚═╝╩  ╩╩ ╩╚═╝╝╚╝╚═╝   \033[38;5;32m ╚═╝  ╩╚═╝\n\n\n\n");
    usleep(DELAY);

    moveCursorTo17() ;
    printf("╦ ╦╦  ╔╦╗╔═╗╦ ╦╔═╗╔╦╗╔═╗╔╦╗   \033[38;5;32m ╔═╗ ╔╗╔═╗    \033[38;5;21m  ║║ \033[38;5;153m     ╦  ╔═╗╔╦╗ ╦╔═╗╦ ╦╔═╗╦  ╦╔╦╗╔═╗╔╗╔╔═╗   \033[38;5;32m ╔═╗ ╔╗╔═╗\n");
    printf("║ ║║  ║║║║ ║╠═╣╠═╣║║║║╣  ║║   \033[38;5;32m ║ ╦  ║╠═╗    \033[38;5;21m  ║║ \033[38;5;153m     ║  ╠═╣ ║║ ║║ ║║ ║╔═╝║  ║║║║║╣ ║║║║╣    \033[38;5;32m ║ ╦  ║╠═╗\n");
    printf("╚═╝╩  ╩ ╩╚═╝╩ ╩╩ ╩╩ ╩╚═╝═╩╝   \033[38;5;32m ╚═╝  ╩╚═╝    \033[38;5;21m  ║║ \033[38;5;153m     ╩═╝╩ ╩═╩╝╚╝╚═╝╚═╝╚═╝╩  ╩╩ ╩╚═╝╝╚╝╚═╝   \033[38;5;32m ╚═╝  ╩╚═╝\n\n\n\n");
    usleep(DELAY);

    moveCursorTo17() ;
    printf("╔═╗╦ ╦╦  ╔╦╗╔═╗╦ ╦╔═╗╔╦╗╔═╗╔╦╗   \033[38;5;32m ╔═╗ ╔╗╔═╗    \033[38;5;21m  ║║ \033[38;5;153m     ╦  ╔═╗╔╦╗ ╦╔═╗╦ ╦╔═╗╦  ╦╔╦╗╔═╗╔╗╔╔═╗   \033[38;5;32m ╔═╗ ╔╗╔═╗\n");
    printf("║ ╦║ ║║  ║║║║ ║╠═╣╠═╣║║║║╣  ║║   \033[38;5;32m ║ ╦  ║╠═╗    \033[38;5;21m  ║║ \033[38;5;153m     ║  ╠═╣ ║║ ║║ ║║ ║╔═╝║  ║║║║║╣ ║║║║╣    \033[38;5;32m ║ ╦  ║╠═╗\n");
    printf("╚═╝╚═╝╩  ╩ ╩╚═╝╩ ╩╩ ╩╩ ╩╚═╝═╩╝   \033[38;5;32m ╚═╝  ╩╚═╝    \033[38;5;21m  ║║ \033[38;5;153m     ╩═╝╩ ╩═╩╝╚╝╚═╝╚═╝╚═╝╩  ╩╩ ╩╚═╝╝╚╝╚═╝   \033[38;5;32m ╚═╝  ╩╚═╝\n\n\n\n");
    usleep(DELAY);

    moveCursorTo17() ;
    printf("╦ ╦╔═╗╦ ╦╦  ╔╦╗╔═╗╦ ╦╔═╗╔╦╗╔═╗╔╦╗   \033[38;5;32m ╔═╗ ╔╗╔═╗    \033[38;5;21m  ║║ \033[38;5;153m     ╦  ╔═╗╔╦╗ ╦╔═╗╦ ╦╔═╗╦  ╦╔╦╗╔═╗╔╗╔╔═╗   \033[38;5;32m ╔═╗ ╔╗╔═╗\n");
    printf("║ ║║ ╦║ ║║  ║║║║ ║╠═╣╠═╣║║║║╣  ║║   \033[38;5;32m ║ ╦  ║╠═╗    \033[38;5;21m  ║║ \033[38;5;153m     ║  ╠═╣ ║║ ║║ ║║ ║╔═╝║  ║║║║║╣ ║║║║╣    \033[38;5;32m ║ ╦  ║╠═╗\n");
    printf("╚═╝╚═╝╚═╝╩  ╩ ╩╚═╝╩ ╩╩ ╩╩ ╩╚═╝═╩╝   \033[38;5;32m ╚═╝  ╩╚═╝    \033[38;5;21m  ║║ \033[38;5;153m     ╩═╝╩ ╩═╩╝╚╝╚═╝╚═╝╚═╝╩  ╩╩ ╩╚═╝╝╚╝╚═╝   \033[38;5;32m ╚═╝  ╩╚═╝\n\n\n\n");
    usleep(DELAY);

    moveCursorTo17() ;
    printf("╔═╗╦ ╦╔═╗╦ ╦╦  ╔╦╗╔═╗╦ ╦╔═╗╔╦╗╔═╗╔╦╗   \033[38;5;32m ╔═╗ ╔╗╔═╗    \033[38;5;21m  ║║ \033[38;5;153m     ╦  ╔═╗╔╦╗ ╦╔═╗╦ ╦╔═╗╦  ╦╔╦╗╔═╗╔╗╔╔═╗   \033[38;5;32m ╔═╗ ╔╗╔═╗\n");
    printf("║ ║║ ║║ ╦║ ║║  ║║║║ ║╠═╣╠═╣║║║║╣  ║║   \033[38;5;32m ║ ╦  ║╠═╗    \033[38;5;21m  ║║ \033[38;5;153m     ║  ╠═╣ ║║ ║║ ║║ ║╔═╝║  ║║║║║╣ ║║║║╣    \033[38;5;32m ║ ╦  ║╠═╗\n");
    printf("╚═╝╚═╝╚═╝╚═╝╩  ╩ ╩╚═╝╩ ╩╩ ╩╩ ╩╚═╝═╩╝   \033[38;5;32m ╚═╝  ╩╚═╝    \033[38;5;21m  ║║ \033[38;5;153m     ╩═╝╩ ╩═╩╝╚╝╚═╝╚═╝╚═╝╩  ╩╩ ╩╚═╝╝╚╝╚═╝   \033[38;5;32m ╚═╝  ╩╚═╝\n\n\n\n");
    usleep(DELAY);

    moveCursorTo17() ;
    printf("╔═╗╔═╗╦ ╦╔═╗╦ ╦╦  ╔╦╗╔═╗╦ ╦╔═╗╔╦╗╔═╗╔╦╗   \033[38;5;32m ╔═╗ ╔╗╔═╗    \033[38;5;21m  ║║ \033[38;5;153m     ╦  ╔═╗╔╦╗ ╦╔═╗╦ ╦╔═╗╦  ╦╔╦╗╔═╗╔╗╔╔═╗   \033[38;5;32m ╔═╗ ╔╗╔═╗\n");
    printf("╔═╝║ ║║ ║║ ╦║ ║║  ║║║║ ║╠═╣╠═╣║║║║╣  ║║   \033[38;5;32m ║ ╦  ║╠═╗    \033[38;5;21m  ║║ \033[38;5;153m     ║  ╠═╣ ║║ ║║ ║║ ║╔═╝║  ║║║║║╣ ║║║║╣    \033[38;5;32m ║ ╦  ║╠═╗\n");
    printf("╚═╝╚═╝╚═╝╚═╝╚═╝╩  ╩ ╩╚═╝╩ ╩╩ ╩╩ ╩╚═╝═╩╝   \033[38;5;32m ╚═╝  ╩╚═╝    \033[38;5;21m  ║║ \033[38;5;153m     ╩═╝╩ ╩═╩╝╚╝╚═╝╚═╝╚═╝╩  ╩╩ ╩╚═╝╝╚╝╚═╝   \033[38;5;32m ╚═╝  ╩╚═╝\n\n\n\n");
    usleep(DELAY);

    moveCursorTo17() ;
    printf("╦═╗╔═╗╔═╗╦ ╦╔═╗╦ ╦╦  ╔╦╗╔═╗╦ ╦╔═╗╔╦╗╔═╗╔╦╗   \033[38;5;32m ╔═╗ ╔╗╔═╗    \033[38;5;21m  ║║ \033[38;5;153m     ╦  ╔═╗╔╦╗ ╦╔═╗╦ ╦╔═╗╦  ╦╔╦╗╔═╗╔╗╔╔═╗   \033[38;5;32m ╔═╗ ╔╗╔═╗\n");
    printf("╠╦╝╔═╝║ ║║ ║║ ╦║ ║║  ║║║║ ║╠═╣╠═╣║║║║╣  ║║   \033[38;5;32m ║ ╦  ║╠═╗    \033[38;5;21m  ║║ \033[38;5;153m     ║  ╠═╣ ║║ ║║ ║║ ║╔═╝║  ║║║║║╣ ║║║║╣    \033[38;5;32m ║ ╦  ║╠═╗\n");
    printf("╩╚═╚═╝╚═╝╚═╝╚═╝╚═╝╩  ╩ ╩╚═╝╩ ╩╩ ╩╩ ╩╚═╝═╩╝   \033[38;5;32m ╚═╝  ╩╚═╝    \033[38;5;21m  ║║ \033[38;5;153m     ╩═╝╩ ╩═╩╝╚╝╚═╝╚═╝╚═╝╩  ╩╩ ╩╚═╝╝╚╝╚═╝   \033[38;5;32m ╚═╝  ╩╚═╝\n\n\n\n");
    usleep(DELAY);

    moveCursorTo17() ;
    printf("╔═╗╦═╗╔═╗╔═╗╦ ╦╔═╗╦ ╦╦  ╔╦╗╔═╗╦ ╦╔═╗╔╦╗╔═╗╔╦╗   \033[38;5;32m ╔═╗ ╔╗╔═╗    \033[38;5;21m  ║║ \033[38;5;153m     ╦  ╔═╗╔╦╗ ╦╔═╗╦ ╦╔═╗╦  ╦╔╦╗╔═╗╔╗╔╔═╗   \033[38;5;32m ╔═╗ ╔╗╔═╗\n");
    printf("║╣ ╠╦╝╔═╝║ ║║ ║║ ╦║ ║║  ║║║║ ║╠═╣╠═╣║║║║╣  ║║   \033[38;5;32m ║ ╦  ║╠═╗    \033[38;5;21m  ║║ \033[38;5;153m     ║  ╠═╣ ║║ ║║ ║║ ║╔═╝║  ║║║║║╣ ║║║║╣    \033[38;5;32m ║ ╦  ║╠═╗\n");
    printf("╚═╝╩╚═╚═╝╚═╝╚═╝╚═╝╚═╝╩  ╩ ╩╚═╝╩ ╩╩ ╩╩ ╩╚═╝═╩╝   \033[38;5;32m ╚═╝  ╩╚═╝    \033[38;5;21m  ║║ \033[38;5;153m     ╩═╝╩ ╩═╩╝╚╝╚═╝╚═╝╚═╝╩  ╩╩ ╩╚═╝╝╚╝╚═╝   \033[38;5;32m ╚═╝  ╩╚═╝\n\n\n\n");
    usleep(DELAY);

    moveCursorTo17() ;
    printf("╔╦╗╔═╗╦═╗╔═╗╔═╗╦ ╦╔═╗╦ ╦╦  ╔╦╗╔═╗╦ ╦╔═╗╔╦╗╔═╗╔╦╗   \033[38;5;32m ╔═╗ ╔╗╔═╗    \033[38;5;21m  ║║ \033[38;5;153m     ╦  ╔═╗╔╦╗ ╦╔═╗╦ ╦╔═╗╦  ╦╔╦╗╔═╗╔╗╔╔═╗   \033[38;5;32m ╔═╗ ╔╗╔═╗\n");
    printf("║║║║╣ ╠╦╝╔═╝║ ║║ ║║ ╦║ ║║  ║║║║ ║╠═╣╠═╣║║║║╣  ║║   \033[38;5;32m ║ ╦  ║╠═╗    \033[38;5;21m  ║║ \033[38;5;153m     ║  ╠═╣ ║║ ║║ ║║ ║╔═╝║  ║║║║║╣ ║║║║╣    \033[38;5;32m ║ ╦  ║╠═╗\n");
    printf("╩ ╩╚═╝╩╚═╚═╝╚═╝╚═╝╚═╝╚═╝╩  ╩ ╩╚═╝╩ ╩╩ ╩╩ ╩╚═╝═╩╝   \033[38;5;32m ╚═╝  ╩╚═╝    \033[38;5;21m  ║║ \033[38;5;153m     ╩═╝╩ ╩═╩╝╚╝╚═╝╚═╝╚═╝╩  ╩╩ ╩╚═╝╝╚╝╚═╝   \033[38;5;32m ╚═╝  ╩╚═╝\n\n\n\n");
    usleep(DELAY);

    moveCursorTo17() ;
    printf("\033[38;5;153m     ╔╦╗╔═╗╦═╗╔═╗╔═╗╦ ╦╔═╗╦ ╦╦  ╔╦╗╔═╗╦ ╦╔═╗╔╦╗╔═╗╔╦╗   \033[38;5;32m ╔═╗ ╔╗╔═╗    \033[38;5;21m  ║║ \033[38;5;153m     ╦  ╔═╗╔╦╗ ╦╔═╗╦ ╦╔═╗╦  ╦╔╦╗╔═╗╔╗╔╔═╗   \033[38;5;32m ╔═╗ ╔╗╔═╗\n");
    printf("\033[38;5;153m     ║║║║╣ ╠╦╝╔═╝║ ║║ ║║ ╦║ ║║  ║║║║ ║╠═╣╠═╣║║║║╣  ║║   \033[38;5;32m ║ ╦  ║╠═╗    \033[38;5;21m  ║║ \033[38;5;153m     ║  ╠═╣ ║║ ║║ ║║ ║╔═╝║  ║║║║║╣ ║║║║╣    \033[38;5;32m ║ ╦  ║╠═╗\n");
    printf("\033[38;5;153m     ╩ ╩╚═╝╩╚═╚═╝╚═╝╚═╝╚═╝╚═╝╩  ╩ ╩╚═╝╩ ╩╩ ╩╩ ╩╚═╝═╩╝   \033[38;5;32m ╚═╝  ╩╚═╝    \033[38;5;21m  ║║ \033[38;5;153m     ╩═╝╩ ╩═╩╝╚╝╚═╝╚═╝╚═╝╩  ╩╩ ╩╚═╝╝╚╝╚═╝   \033[38;5;32m ╚═╝  ╩╚═╝\n\n\n\n\n");
    usleep(DELAY);
}

void animation (){
    print_slow("\033[38;5;20m                                                       ╔═╗╔═╗╦  ╔═╗╦  ╔═╗╔═╗╦═╗\n",1000);
    print_slow("\033[38;5;21m                                                       ║╣ ╚═╗║  ╠═╣║  ║ ╦║╣ ╠╦╝\n",1000);
    print_slow("\033[38;5;32m                                                       ╚═╝╚═╝╩  ╩ ╩╩═╝╚═╝╚═╝╩╚═\n\n\n",1000);
    print_slow("\033[38;5;23m                                                        ████████╗██████╗  ██╗\n",1000);
    print_slow("\033[38;5;24m                                                        ╚══██╔══╝██╔══██╗███║\n",1000);
    print_slow("\033[38;5;25m                                                           ██║   ██████╔╝╚██║\n",1000);
    print_slow("\033[38;5;26m                                                           ██║   ██╔═══╝  ██║\n",1000);
    print_slow("\033[38;5;27m                                                           ██║   ██║      ██║\n",1000);
    print_slow("\033[38;5;28m                                                           ╚═╝   ╚═╝      ╚═╝\n\n\n\n\n\n",1000);
    printf("\x1B[0m                                                    ╦═╗╔═╗╔═╗╦  ╦╔═╗╔═╗  ╔═╗╔═╗╦═╗   \n");
    printf("\x1B[0m                                                    ╠╦╝║╣ ╠═╣║  ║╚═╗║╣   ╠═╝╠═╣╠╦╝  o\n");
    printf("\x1B[0m                                                    ╩╚═╚═╝╩ ╩╩═╝╩╚═╝╚═╝  ╩  ╩ ╩╩╚═  o\n\n");
    prin_names();
    printf("\x1B[0m                                       ╔═╗╔═╗╦ ╦╔═╗  ╦  ╔═╗  ╔═╗╦ ╦╔═╗╔═╗╦═╗╦  ╦╦╔═╗╦╔═╗╔╗╔  ╔╦╗╔═╗  \n");
    printf("\x1B[0m                                       ╚═╗║ ║║ ║╚═╗  ║  ╠═╣  ╚═╗║ ║╠═╝║╣ ╠╦╝╚╗╔╝║╚═╗║║ ║║║║   ║║║╣   o\n");
    printf("\x1B[0m                                       ╚═╝╚═╝╚═╝╚═╝  ╩═╝╩ ╩  ╚═╝╚═╝╩  ╚═╝╩╚═ ╚╝ ╩╚═╝╩╚═╝╝╚╝  ═╩╝╚═╝  o\n\n");
    print_name_tran();
    _getch();
}

int main() {
    SetConsoleOutputCP(65001);
    print_slow(RED "\n\n\n\n\n\n\n\n\n\n\n\n\n\n                   Veuiller mettre votre terminal en plein écran avant de commencer \n                " RESET,DELAY) ;
    system("pause") ;
    clear_screen() ;
    animation();
    srand(time(0));
    menuTP();
}