#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char c;
    int nr;
    struct node *children[27];
} Node, *Tree;

// functie pentru initializarea arborelui
void init(Tree *t) {
    int i;
    for (i = 0; i < 27; i++) {
        (*t)->children[i] = malloc(sizeof(Node));
        (*t)->children[i]->c = 0;
    }
    (*t)->children[0]->c = '$';
    (*t)->nr = 1;
}

void bfs(Tree t) {
    int first = 0, last = 0, i;
    Tree queue[t->nr];
    for(i = 0; i < 27; i++)
        if(t->children[i]->c != 0)
            queue[last++] = t->children[i];

    while (first < last) {
        Tree current = queue[first++];
        printf("%c", current->c);

        for (i = 0; i < 27; i++) {
            if (current->children[i] != NULL && current->children[i]->c != 0) {
                if (last < t->nr) {
                    queue[last++] = current->children[i];
                }
            }
        }
    }
    printf("\n");
}


void task1();

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
    int n;
    Tree t;
    char opt;

    // deschidem fisierele
    FILE *f = fopen(argv[2], "r");
    FILE *g = fopen(argv[3], "w");
    fscanf(f, "%d", &n);
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
                bfs(t);
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

    fclose(f);
    fclose(g);
    return 0;
}
