// ABĂHNENCEI Alin Andrei - 312CC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char c[101];
    int nr;
    struct node *children[27];
} Node, *Tree;

typedef struct queue {
    Tree t;
    struct queue *next;
} Queue;

// functie pentru initializarea arborelui
void init(Tree *t) {
    int i;
    *t = calloc(1, sizeof(Node));
    for (i = 0; i < 27; i++) {
        (*t)->children[i] = calloc(1, sizeof(Node));
        (*t)->children[i]->c[0] = 0;
        (*t)->children[i]->nr = 1;
    }
    (*t)->nr = 0;
}

// parcurgem arborele in latime
void bfs(Tree t, FILE *g) {
    Queue *first = NULL, *last = NULL, *aux = NULL, *new = NULL;
    int i, flag = 1;
    // punem in coada copiii de pe primul nivel
    for (i = 0; i < 27; i++) {
        if(t->children[i]->c[0] != 0) {
            if(first == NULL) {
                first = calloc(1, sizeof(Queue));
                first->t = t->children[i];
                first->next = NULL;
                last = first;
            }
            else {
                aux = calloc(1, sizeof(Queue));
                aux->t = t->children[i];
                aux->next = NULL;
                last->next = aux;
                last = aux;
            }
        }
    }
    // afisam arborele pe nivele
    while (first != NULL) {
        aux = first;
        first = first->next;
        if(aux->t->nr != flag)
            fprintf(g, "\n");
        fprintf(g, "%c ", aux->t->c[0]);
        for (i = 0; i < 27; i++) {
            if (aux->t->children[i] != NULL && aux->t->children[i]->c[0] != 0) {
                if (last == NULL) {
                    first = calloc(1, sizeof(Queue));
                    first->t = aux->t->children[i];
                    first->next = NULL;
                    last = first;
                }
                else {
                    if (last == NULL) {
                        first = calloc(1, sizeof(Queue));
                        first->t = aux->t->children[i];
                        first->next = NULL;
                        last = first;
                    }
                    else {
                        new = calloc(1, sizeof(Queue));
                        new->t = aux->t->children[i];
                        new->next = NULL;
                        last->next = new;
                        last = new;
                    }
                }
            }
        }
        flag = aux->t->nr;
        free(aux);
    }
    if(last->t->c[0] != 0) {
        fprintf(g, "\n%c ", last->t->c[0]);
        free(last);
    }
    free(first);
    fprintf(g, "\n");
}

// generam arborele de sufixe
void getSufix(Tree *t, char *s) {
    int i, j, len = 0, index = 0;
    Tree aux = NULL, current = *t;
    // char *sufix = (char*) malloc(100 * sizeof(char));
    len = strlen(s);
    for (i = len - 1; i >= 0; i--) {
        char *sufix = s + i;
        // calculam pozitia pe care trebuie sa adaugam o litera
        if(sufix[0] == '$')
            index = 0;
        else
            index = sufix[0] - 'a' + 1;
        aux = current;
        // daca exista deja litera, coboram pe acea ramura
        while(sufix[0] != '\0' && aux->children[index] != NULL && aux->children[index]->c[0] != 0) {
            aux = aux->children[index];
            sufix++;
            if(sufix[0] == '$')
                index = 0;
            else
                index = sufix[0] - 'a' + 1;
        }
        // adaugam un nod nou in arbore
        while(sufix[0] != '\0') {
            if(aux->children[index] == NULL)
                for (j = 0; j < 27; j++) {
                    aux->children[j] = calloc(1, sizeof(Node));
                    aux->children[j]->c[0] = 0;
                    aux->children[j]->nr = aux->nr + 1;
                }
            if(sufix[0] == '$')
                index = 0;
            else
                index = sufix[0] - 'a' + 1;
            aux->children[index]->c[0] = sufix[0];
            aux = aux->children[index];
            sufix++;
        }
        // free(sufix);
    }
}

// numaram nodurile de tip frunza folosind parcurgerea in adancime
void leafCounter(Tree t, int *nr) {
    int i;
    for (i = 0; i < 27; i++) {
        if(t->children[i] != NULL && t->children[i]->c[0] != 0) {
            leafCounter(t->children[i], nr);
        }
    }
    if(t->c[0] == '$') {
        (*nr)++;
    }
}

// calculam numarul maxim de copii folosind parcurgerea in adancime
void maxChildren(Tree t, int *max) {
    int i, nr = 0;
    for (i = 0; i < 27; i++) {
        if(t->children[i] != NULL && t->children[i]->c[0] != 0) {
            nr++;
            maxChildren(t->children[i], max);
        }
    }
    if(nr > *max) {
        *max = nr;
    }
}

// calculam numarul de sufixe de lungime k
void numberKSuf(Tree t, int *nr, int k) {
    int i;
    for (i = 0; i < 27; i++) {
        if(t->children[i] != NULL && t->children[i]->c[0] != 0) {
            numberKSuf(t->children[i], nr, k);
        }
    }
    // daca un nod se afla pe nivelul k si are un copil '$' este numarat
    if(t->nr == k && t->c[0] != '$' && t->children[0] != NULL && t->children[0]->c[0] == '$') {
        (*nr)++;
    }
}

// verificam daca un sufix exista in arbore
int checkSuf(Tree t, char *suf) {
    int i, rez = 0;
    Tree aux = t;
    if(suf[0] == '\0') {
        return 1;
    }
    for(i = 0; i < 27; i++) {
        if(aux->children[i] != NULL) {
            if(suf[0] == aux->children[i]->c[0]) {
                rez += checkSuf(aux->children[i], suf + 1);
            }
        }
    }
    return rez;
}

// parcurgere in latime pentru arbore de siruri
// este folosita in cadrul taskului 4
void bfsCompakt(Tree t, FILE *g) {
    Queue *first = NULL, *last = NULL, *aux = NULL;
    int i, flag = 1;
    for (i = 0; i < 27; i++) {
        if(t->children[i] != NULL && t->children[i]->c[0] != 0) {
            if(first == NULL) {
                first = malloc(sizeof(Queue));
                first->t = t->children[i];
                first->next = NULL;
                last = first;
            }
            else {
                aux = malloc(sizeof(Queue));
                aux->t = t->children[i];
                aux->next = NULL;
                last->next = aux;
                last = aux;
            }
        }
    }
    while (first != NULL) {
        aux = first;
        first = first->next;
        if(aux->t->nr != flag)
            fprintf(g, "\n");
        fprintf(g, "%s ", aux->t->c);
        for (i = 0; i < 27; i++) {
            if (aux->t->children[i] != NULL && aux->t->children[i]->c[0] != 0) {
                if (last == NULL) {
                    first = malloc(sizeof(Queue));
                    first->t = aux->t->children[i];
                    first->next = NULL;
                    last = first;
                }
                else {
                    Queue *new = malloc(sizeof(Queue));
                    new->t = aux->t->children[i];
                    new->next = NULL;
                    last->next = new;
                    last = new;
                }
            }
        }
        flag = aux->t->nr;
        free(aux);
    }
    // if(last->t->c[0] != 0) {
    //     fprintf(g, "\n%s ", last->t->c);
    // }
    fprintf(g, "\n");
}

// compactam arborele de sufixe
void compakt(Tree *t) {
    int i, j, ok;
    for (i = 0; i < 27; i++) {
        if ((*t)->children[i] != NULL && (*t)->children[i]->c[0] != 0) {
            compakt(&(*t)->children[i]);
        }
    }

    if((*t)->c[0] != '$' && (*t)->c[0] != 0) {
        ok = 1;
        for(j = 0; j < 27; j++) {
            if((*t)->children[j] != NULL && (*t)->children[j]->c[0] != 0 && (*t)->children[j]->c[0] == '$') {
                ok = 0;
                break;
            }
        }
        if(ok) {
            for(i = 0; i < 27; i++) {
                if((*t)->children[i] != NULL && (*t)->children[i]->c[0] != 0) {
                    strcat((*t)->c, (*t)->children[i]->c);
                    for(j = 0; j < 27; j++) {
                        if((*t)->children[i]->children[j] != NULL && (*t)->children[i]->children[j]->c[0] != 0) {
                            (*t)->children[j] = (*t)->children[i]->children[j];
                            (*t)->children[j]->nr = (*t)->nr + 1;
                        }
                    }
                    free((*t)->children[i]);
                    (*t)->children[i] = NULL;
                    break;
                }
            }
        }
    }
}

// functii pentru rezolvarea taskurilor

// generam arborele si il afisam pe nivele
void task1(Tree *t, char **cuv, int n, FILE *g) {
    int i;
    for(i = 0; i < n; i++) {
        getSufix(&(*t), cuv[i]);
    }
    bfs(*t, g);
}

// aplicam operatiile de numarare de frunze, numar maxim de copii si
// aflarea numarului de sufixe de lungime k
void task2(Tree *t, FILE *g, char **cuv, int n, int k) {
    int nr = 0, i, max = 0, ksuf = 0;
    for(i = 0; i < n; i++) {
        getSufix(&(*t), cuv[i]);
    }
    leafCounter(*t, &nr);
    fprintf(g, "%d\n", nr);

    numberKSuf(*t, &ksuf, k);
    fprintf(g, "%d\n", ksuf);

    maxChildren(*t, &max);
    fprintf(g, "%d\n", max);
}

// verificam daca sufixele date ca parametru exista in arbore
void task3(Tree *t, char **cuv, char **suf, int n, int m, FILE *g) {
    int i;
    for(i = 0; i < n; i++) {
        getSufix(&(*t), cuv[i]);
    }
    for(i = 0; i < m; i++) {
        if(checkSuf(*t, suf[i])) {
            fprintf(g, "1\n");
        }
        else {
            fprintf(g, "0\n");
        }
    }
}

// compactam arborele si il afisam
void task4(Tree *t, char **cuv, int n, FILE *g) {
    int i;
    for(i = 0; i < n; i++) {
        getSufix(&(*t), cuv[i]);
    }
    compakt(&(*t));
    bfsCompakt(*t, g);
}

// eliberam memoria alocata pentru arbore
void freeMemory(Tree *t) {
    if (*t == NULL) {
        return;
    }
    int i;
    for (i = 0; i < 27; i++) {
        freeMemory(&((*t)->children[i]));
    }
    free(*t);
    *t = NULL;
}

int main (int argc, char *argv[]) {
    int n = 0, m = 0, i = 0, k = 0;
    Tree t = NULL;
    char opt, **cuv = NULL, **suf = NULL;
    FILE *f, *g;
    // deschidem fisierele
    if(strstr(argv[2], ".in") && strstr(argv[3], ".out")) {
        f = fopen(argv[2], "r");
        g = fopen(argv[3], "w");
    }
    else if(strstr(argv[3], ".in") && strstr(argv[4], ".out")) {
        f = fopen(argv[3], "r");
        g = fopen(argv[4], "w");
    }
        else {
            printf("Fisierele nu sunt introduse corect\n");
            return 1;
        }
    // initializam arborele
    init(&t);
    // verificam daca fisierele sunt introduse corect
    if(argc < 4) {
        printf("Fisierele nu sunt introduse corect\n");
        freeMemory(&t);
        // return 1;
    }
    else {
        // construim un meniu pentru cerinte
        opt = argv[1][2];
        switch (opt) {
            case '1':
                // citim datele din fisier
                fscanf(f, "%d", &n);
                cuv = (char**) malloc(n * sizeof(char*));
                for (i = 0; i < n; i++) {
                    cuv[i] = (char*) malloc(100 * sizeof(char));
                    fscanf(f, "%s", cuv[i]);
                    strcat(cuv[i], "$");
                }
                task1(&t, cuv, n, g);
                break;
            case '2':
                // citim datele din fisier
                fscanf(f, "%d", &n);
                cuv = (char**) malloc(n * sizeof(char*));
                for (i = 0; i < n; i++) {
                    cuv[i] = (char*) malloc(100 * sizeof(char));
                    fscanf(f, "%s", cuv[i]);
                    strcat(cuv[i], "$");
                }
                k = atoi(argv[2]);
                task2(&t, g, cuv, n, k);
                break;
            case '3':
                fscanf(f, "%d%d", &n, &m);
                cuv = (char**) malloc(n * sizeof(char*));
                suf = (char**) malloc(m * sizeof(char*));
                for (i = 0; i < n; i++) {
                    cuv[i] = (char*) malloc(100 * sizeof(char));
                    fscanf(f, "%s", cuv[i]);
                    strcat(cuv[i], "$");
                }
                for(i = 0; i < m; i++) {
                    suf[i] = (char*) malloc(100 * sizeof(char));
                    fscanf(f, "%s", suf[i]);
                    strcat(suf[i], "$");
                    suf[i][strlen(suf[i])] = '\0';
                }
                task3(&t, cuv, suf, n, m, g);
                break;
            case '4':
                fscanf(f, "%d", &n);
                cuv = (char**) malloc(n * sizeof(char*));
                for (i = 0; i < n; i++) {
                    cuv[i] = (char*) malloc(100 * sizeof(char));
                    fscanf(f, "%s", cuv[i]);
                    strcat(cuv[i], "$");
                }
                task4(&t, cuv, n, g);
                break;
            default:
                printf("Optiunea nu exista\n");
                return 1;
        }
        freeMemory(&t);
    }

    // eliberam memoria
    for (i = 0; i < n; i++) {
        free(cuv[i]);
    }
    free(cuv);
    for (i = 0; i < m; i++) {
        free(suf[i]);
    }
    free(suf);

    // inchidem fisierele utilizate
    fclose(f);
    fclose(g);
    return 0;
}
