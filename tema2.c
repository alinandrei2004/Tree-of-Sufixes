#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char c;
    int nr;
    struct node *children[27];
} Node, *Tree;

// functie pentru initializarea arborelui
void init(Tree *t) {
    int i;
    *t = malloc(sizeof(Node));
    for (i = 0; i < 27; i++) {
        (*t)->children[i] = malloc(sizeof(Node));
        (*t)->children[i]->c = 0;
        (*t)->children[i]->nr = 0;
    }
    // (*t)->children[0]->c = '$';
    (*t)->nr = 1;
}

void bfs(Tree t) {
    int first = 0, last = 0, i, flag = 0;
    Tree queue[3000];
    Tree aux;
    for(i = 0; i < 27; i++) {
        if(t->children[i]->c != 0) {
            queue[last++] = t->children[i];
        }
    }
    while (first < last) {
        aux = queue[first++];
        // if(flag == 1 && aux->c == '$')
        //     printf("\n");
        printf("%c ", aux->c);
        if(aux->c == '$')
            flag = 1;
        for (i = 0; i < 27; i++) {
            if (aux->children[i] != NULL && aux->children[i]->c != 0) {
                if (last < t->nr) {
                    queue[last++] = aux->children[i];
                }
            }
        }
    }
    printf("\n");
}

void getSufix(Tree *t, char *s) {
    int i, j, len, index;
    Tree aux, current = *t;
    char *sufix = (char*) malloc(100 * sizeof(char));
    len = strlen(s);
    (*t)->nr = len;
    for (i = len - 1; i >= 0; i--) {
        sufix = s + i;
        // printf("%s\n", sufix);
        if(sufix[0] == '$')
            index = 0;
        else
            index = sufix[0] - 'a' + 1;
        if (current->children[index]->c == 0) {
            current->children[index]->c = sufix[0];
            // (*t)->children[index]->nr = (*t)->nr + 1;
            // printf("%c\n", sufix[0]);
            sufix++;
            while(sufix[0] != '\0') {
                // printf("%s\n", sufix);
                aux = current->children[index];
                for (j = 0; j < 27; j++) {
                    aux->children[j] = malloc(sizeof(Node));
                    aux->children[j]->c = 0;
                    aux->children[j]->nr = 0;
                }
                if(sufix[0] == '$')
                    index = 0;
                else
                    index = sufix[0] - 'a' + 1;
                aux->children[index]->c = sufix[0];
                // aux->children[index]->nr = aux->nr + 1;
                sufix++;
                if (current->children[index] != NULL) {
                    current = aux;
                }
            }
        }
        else {
            sufix++;
            if(sufix[0] == '$')
                index = 0;
            else
                index = sufix[0] - 'a' + 1;
            aux = current->children[index];
            while(sufix[0] != '\0') {
                // printf("%s\n", sufix);
                for (j = 0; j < 27; j++) {
                    aux->children[j] = malloc(sizeof(Node));
                    aux->children[j]->c = 0;
                    aux->children[j]->nr = 0;
                }
                if(sufix[0] == '$')
                    index = 0;
                else
                    index = sufix[0] - 'a' + 1;
                aux->children[index]->c = sufix[0];
                // aux->children[index]->nr = aux->nr + 1;
                sufix++;
                if (current->children[index] != NULL) {
                    current = aux;
                }
            }
            // current = current->children[index];

        }
        
    }
}

void task1(Tree *t, char **cuv, int n) {
    int i;
    for(i = 0; i < n; i++) {
        getSufix(&(*t), cuv[i]);
    }
    bfs(*t);
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
                task1(&t, cuv, n);
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
