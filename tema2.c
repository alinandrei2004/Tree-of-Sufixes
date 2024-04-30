#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char c;
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
    *t = malloc(sizeof(Node));
    for (i = 0; i < 27; i++) {
        (*t)->children[i] = malloc(sizeof(Node));
        (*t)->children[i]->c = 0;
        (*t)->children[i]->nr = 1;
    }
    // (*t)->children[0]->c = '$';
    (*t)->nr = 0;
}

void bfs(Tree t, FILE *g) {
    Queue *first = NULL, *last = NULL, *aux;
    int i, flag = 1;
    for (i = 0; i < 27; i++) {
        if(t->children[i]->c != 0) {
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
        fprintf(g, "%c ", aux->t->c);
        for (i = 0; i < 27; i++) {
            if (aux->t->children[i] != NULL && aux->t->children[i]->c != 0) {
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
    if(last->t->c != 0) {
        fprintf(g, "\n%c ", last->t->c);
    }
    fprintf(g, "\n");
}

void getSufix(Tree *t, char *s) {
    int i, j, len, index;
    Tree aux, current = *t;
    char *sufix = (char*) malloc(100 * sizeof(char));
    len = strlen(s);
    for (i = len - 1; i >= 0; i--) {
        sufix = s + i;
        if(sufix[0] == '$')
            index = 0;
        else
            index = sufix[0] - 'a' + 1;
        aux = current;
        while(sufix[0] != '\0' && aux->children[index] != NULL && aux->children[index]->c != 0) {
            aux = aux->children[index];
            sufix++;
            if(sufix[0] == '$')
                index = 0;
            else
                index = sufix[0] - 'a' + 1;
        }
        while(sufix[0] != '\0') {
            if(aux->children[index] == NULL)
                for (j = 0; j < 27; j++) {
                    aux->children[j] = malloc(sizeof(Node));
                    aux->children[j]->c = 0;
                    aux->children[j]->nr = aux->nr + 1;
                }
            if(sufix[0] == '$')
                index = 0;
            else
                index = sufix[0] - 'a' + 1;
            aux->children[index]->c = sufix[0];
            aux = aux->children[index];
            sufix++;
        }
    }
}

void leafCounter(Tree t, int *nr) {
    int i;
    for (i = 0; i < 27; i++) {
        if(t->children[i] != NULL && t->children[i]->c != 0) {
            leafCounter(t->children[i], nr);
        }
    }
    if(t->c == '$') {
        (*nr)++;
    }
}

void maxChildren(Tree t, int *max) {
    int i, nr = 0;
    for (i = 0; i < 27; i++) {
        if(t->children[i] != NULL && t->children[i]->c != 0) {
            nr++;
            maxChildren(t->children[i], max);
        }
    }
    if(nr > *max) {
        *max = nr;
    }
}

void numberKSuf(Tree t, int *nr, int k) {
    int i;
    for (i = 0; i < 27; i++) {
        if(t->children[i] != NULL && t->children[i]->c != 0) {
            numberKSuf(t->children[i], nr, k);
        }
    }
    if(t->nr == k && t->c != '$' && t->children[0] != NULL && t->children[0]->c == '$') {
        (*nr)++;
    }
}

int checkSuf(Tree t, char *suf) {
    int i, rez = 0;
    Tree aux = t;
    if(suf[0] == '\0') {
        return 1;
    }
    for(i = 0; i < 27; i++) {
        if(aux->children[i] != NULL) {
            if(suf[0] == aux->children[i]->c) {
                rez += checkSuf(aux->children[i], suf + 1);
            }
        }
    }
    return rez;
}

void compakt();


void task1(Tree *t, char **cuv, int n, FILE *g) {
    int i;
    for(i = 0; i < n; i++) {
        getSufix(&(*t), cuv[i]);
    }
    bfs(*t, g);
}

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

void task4(Tree *t, char **cuv, int n, FILE *g) {
    int i;
    for(i = 0; i < n; i++) {
        getSufix(&(*t), cuv[i]);
    }
    bfs(*t, g);
}

void freeMemory(Tree *t) {
    int i;
    for (i = 0; i < 27; i++) {
        if ((*t)->children[i]->c != 0) {
            freeMemory(&(*t)->children[i]);
        }
    }
    free(t);
}

int main (int argc, char *argv[]) {
    int n, m, i, k;
    Tree t;
    char opt, **cuv, **suf;
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
        return 1;
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
                    // printf("%s\n", cuv[i]);
                    strcat(cuv[i], "$");
                }
                for(i = 0; i < m; i++) {
                    suf[i] = (char*) malloc(100 * sizeof(char));
                    fscanf(f, "%s", suf[i]);
                    strcat(suf[i], "$");
                    suf[i][strlen(suf[i])] = '\0';
                    // printf("%s\n", suf[i]);
                }
                task3(&t, cuv, suf, n, m, g);
                break;
            case '4':
                // citim datele din fisier
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
    }

    // eliberam memoria
    for (i = 0; i < n; i++) {
        free(cuv[i]);
    }
    free(cuv);
    // freeMemory(&t);

    fclose(f);
    fclose(g);
    return 0;
}
