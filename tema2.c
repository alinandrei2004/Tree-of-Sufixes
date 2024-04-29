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
    (*t)->nr = 1;
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
    // (*t)->nr = 0;
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

void task1(Tree *t, char **cuv, int n, FILE *g) {
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
    int n, i;
    Tree t;
    char opt, **cuv;

    // deschidem fisierele
    FILE *f = fopen(argv[2], "r");
    FILE *g = fopen(argv[3], "w");

    // citim datele din fisier
    fscanf(f, "%d", &n);
    cuv = (char**) malloc(n * sizeof(char*));
    for (i = 0; i < n; i++) {
        cuv[i] = (char*) malloc(100 * sizeof(char));
        fscanf(f, "%s", cuv[i]);
        strcat(cuv[i], "$");
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
                task1(&t, cuv, n, g);
                break;
            case '2':
                break;
            case '3':
                break;
            case 4:
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
