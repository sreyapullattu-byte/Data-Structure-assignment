#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

struct Node {
    char key[MAX];
    struct Node *left;
    struct Node *right;
};

struct Node* createNode(char key[]) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

    strcpy(newNode->key, key);
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

struct Node* insert(struct Node *root, char key[]) {
    if (root == NULL)
        return createNode(key);

    if (strcmp(key, root->key) < 0)
        root->left = insert(root->left, key);
    else if (strcmp(key, root->key) > 0)
        root->right = insert(root->right, key);

    return root;
}

void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%s ", root->key);
        inorder(root->right);
    }
}

int bstSearch(struct Node *root, char key[], int *comparisons) {
    while (root != NULL) {
        (*comparisons)++;

        if (strcmp(key, root->key) == 0)
            return 1;

        if (strcmp(key, root->key) < 0)
            root = root->left;
        else
            root = root->right;
    }

    return 0;
}

int linearSearch(char data[][MAX], int n, char key[], int *comparisons) {
    int i;

    for (i = 0; i < n; i++) {
        (*comparisons)++;

        if (strcmp(data[i], key) == 0)
            return 1;
    }

    return 0;
}

void freeTree(struct Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    FILE *file;
    struct Node *root = NULL;

    char data[20][MAX];
    char searchKey[MAX];

    int n, searches;
    int i;
    int bstComparisons, linearComparisons;

    file = fopen("input.txt", "r");

    if (file == NULL) {
        printf("Error: input.txt file not found.\n");
        return 1;
    }

    /* Read number of identification numbers */
    fscanf(file, "%d", &n);

    /* Read identification numbers */
    for (i = 0; i < n; i++) {
        fscanf(file, "%19s", data[i]);
        root = insert(root, data[i]);
    }

    printf("QUESTION 11 - BST AND LINEAR SEARCH\n");
    printf("------------------------------------\n");

    printf("\nGiven Identification Numbers:\n");
    for (i = 0; i < n; i++)
        printf("%s ", data[i]);

    printf("\n\nBST Inorder Traversal:\n");
    inorder(root);

    /* Read number of searches */
    fscanf(file, "%d", &searches);

    printf("\n\nSearch Results:\n");

    for (i = 0; i < searches; i++) {

        fscanf(file, "%19s", searchKey);

        bstComparisons = 0;
        linearComparisons = 0;

        int bstFound = bstSearch(root, searchKey, &bstComparisons);
        int linearFound = linearSearch(data, n, searchKey,
                                       &linearComparisons);

        printf("\nSearch Key: %s\n", searchKey);

        if (bstFound)
            printf("BST Search: Found\n");
        else
            printf("BST Search: Not Found\n");

        printf("BST Comparisons: %d\n", bstComparisons);

        if (linearFound)
            printf("Linear Search: Found\n");
        else
            printf("Linear Search: Not Found\n");

        printf("Linear Search Comparisons: %d\n",
               linearComparisons);
    }

    printf("\nComplexity Analysis:\n");
    printf("BST Search - Best Case: O(1)\n");
    printf("BST Search - Average Case: O(log n)\n");
    printf("BST Search - Worst Case: O(n)\n");
    printf("Linear Search - Best Case: O(1)\n");
    printf("Linear Search - Average Case: O(n)\n");
    printf("Linear Search - Worst Case: O(n)\n");
    printf("BST Space Complexity: O(n)\n");
    printf("Linear Search Space Complexity: O(1)\n");

    fclose(file);
    freeTree(root);

    return 0;
}
