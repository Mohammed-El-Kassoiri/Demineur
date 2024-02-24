/**
 * @author MOHAMMED EL KASSOIRI
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
int Etat = 0;
int grille[SIZE][SIZE];
int Case_Revelees[SIZE][SIZE];
int drapeau[SIZE][SIZE];

void setup() {
    printf(" *****     ******  **      **  *******  **      *  ******  *        *  ****\n"
           " *     *   *       * *    * *     *     * *     *  *       *        *  *    *\n"
           " *      *  *       *  *  *  *     *     *  *    *  *       *        *  *    *\n"
           " *      *  ******  *   **   *     *     *   *   *  ******  *        *  ***\n"
           " *      *  *       *        *     *     *    *  *  *       *        *  *  *\n"
           " *     *   *       *        *     *     *     * *  *        *      *   *    *\n"
           " *****     ******  *        *  *******  *      **  *******     **      *     *.MADE BY MOHAMMED EL KASSOIRI\n");
    printf(" ENJOY WITH US!\n");
    printf("\n");
    printf("Taper pour commencer : ");
    getch();
    printf("\n\n");
    Affiche_la_grille();
    printf("\n");
}

void Initialise_grille() {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            grille[i][j] = 0;
            Case_Revelees[i][j] = 0;
            drapeau[i][j] = 0;
        }
    }
}

void placeMines(int difficulty) {
    int i, j, count = 0;
    int n = 10 * difficulty;
    while (count < n) {
        i = rand() % SIZE;
        j = rand() % SIZE;
        if (grille[i][j] != -1) {
            grille[i][j] = -1;
            count++;
        }
    }
}

int Mine_Adjacente(int x, int y) {
    int count = 0, i, j;
    for (i = x - 1; i <= x + 1; i++) {
        for (j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < SIZE && j >= 0 && j < SIZE && grille[i][j] == -1) {
                count++;
            }
        }
    }
    return count;
}

void Reveler_une_case(int x, int y) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || Case_Revelees[x][y] || drapeau[x][y]) {
        return;
    }
    Case_Revelees[x][y] = 1;
    if (grille[x][y] == -1) {
        return;
    }
    if (Mine_Adjacente(x, y) == 0) {
        Reveler_une_case(x - 1, y - 1);
        Reveler_une_case(x - 1, y);
        Reveler_une_case(x - 1, y + 1);
        Reveler_une_case(x, y - 1);
        Reveler_une_case(x, y + 1);
        Reveler_une_case(x + 1, y - 1);
        Reveler_une_case(x + 1, y);
        Reveler_une_case(x + 1, y + 1);
    }
}

void Drapeau(int x, int y) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || Case_Revelees[x][y]) {
        return;
    }
    drapeau[x][y] = !drapeau[x][y];
}

void Affiche_la_grille(int X, int Y) {
    int i, j;
    printf("      |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |\n");
    printf("       ___________________________________________________________\n");
    for (i = 0; i < SIZE; i++) {
        printf("| %d | |",i);
        for (j = 0; j < SIZE; j++) {
            if (grille[i][j] == -1 && !(i == X && j == Y) && Etat == 1) {
                printf("  m  |");
            } else if(grille[i][j] == -1 && (i == X && j == Y) && Etat == 1 ){
                if (i == X && j == Y) {
                    printf("  *  |");
                } else {
                    printf(" %d:%d |", i, j);
                }
            }
            else if (Case_Revelees[i][j]) {
                    int MineAdjacente = Mine_Adjacente(i, j);
                    if (MineAdjacente > 0) {
                        printf("  %d  |", Mine_Adjacente(i, j));
                    } else {
                        printf("     |");
                    }

            } else if (drapeau[i][j]) {
                printf("  d  |");
            } else {
                printf(" %d:%d |", i, j);
            }
        }
        printf("\n");
        printf("|---| |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|\n");
    }
    printf("\n");
}

int Verifie_Etat() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grille[i][j] != -1 && Case_Revelees[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    setup();
    srand(time(NULL));
    int difficulty;
    printf(" Choisissez la difficulte :\n"
           " 1 : facile\n"
           " 2 : moyen\n"
           " 3 : difficile\n");
    scanf(" %d", &difficulty);
    Initialise_grille();
    placeMines(difficulty);
    int x, y, Choix;
    int X, Y;
    while (1) {
        printf(" 1 : pour Entrez les coordonnees (x y) : \n"
               " 2 : pour basculer le Drapeau\n");
        scanf("%d", &Choix);
        if (Choix == 1) {
            printf("Entrez les coordonnees (x y) : \n");
            scanf("%d %d", &x, &y);
            printf("Reveler (%d, %d)\n", x, y);
            if (grille[x][y] == -1) {
                printf("Jeu termine. Vous avez perdu !\n");
                printf("Grille finale :\n");
                Reveler_une_case(x, y);
                Etat = 1;
                X = x;
                Y = y;
                Affiche_la_grille(X, Y);
                break;
            }
            Reveler_une_case(x, y);
            Affiche_la_grille(X,Y);
        } else if (Choix == 2) {
            printf("Basculez le Drapeau aux coordonnees (x y) : \n");
            scanf(" %d %d", &x, &y);
            Drapeau(x, y);
            Affiche_la_grille(X,Y);
        } else {
            printf("Choix invalide !\n");
        }
        if (Verifie_Etat()) {
            printf("felicitations! vous avez gagne.\n");
            break;
        }
    }
    return 0;
}
