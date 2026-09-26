#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char key[20];
    struct Node *left;
    struct Node *right;
};

struct Node* createNode(char key[]) {
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

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

int bstSearch(struct Node *root, char key[]) {

    int comparisons = 0;

    while (root != NULL) {

        comparisons++;

        int result = strcmp(key, root->key);

        if (result == 0)
            return comparisons;

        else if (result < 0)
            root = root->left;

        else
            root = root->right;
    }

    return comparisons;
}

int linearSearch(char data[][20], int n, char key[]) {

    int comparisons = 0;

    for (int i = 0; i < n; i++) {

        comparisons++;

        if (strcmp(data[i], key) == 0)
            return comparisons;
    }

    return comparisons;
}

int main() {

    char data[][20] = {
        "A102", "A25", "A7", "B100",
        "B12", "A120", "B3", "A45"
    };

    int n = 8;

    struct Node *root = NULL;

    for (int i = 0; i < n; i++) {
        root = insert(root, data[i]);
    }

    printf("Inorder Traversal:\n");
    inorder(root);

    char key1[] = "A120";
    char key2[] = "A7";
    char key3[] = "B3";

    printf("\n\nSearch Key: %s\n", key1);
    printf("BST Search Comparisons: %d\n",
           bstSearch(root, key1));
    printf("Linear Search Comparisons: %d\n",
           linearSearch(data, n, key1));

    printf("\nSearch Key: %s\n", key2);
    printf("BST Search Comparisons: %d\n",
           bstSearch(root, key2));
    printf("Linear Search Comparisons: %d\n",
           linearSearch(data, n, key2));

    printf("\nSearch Key: %s\n", key3);
    printf("BST Search Comparisons: %d\n",
           bstSearch(root, key3));
    printf("Linear Search Comparisons: %d\n",
           linearSearch(data, n, key3));

    return 0;
}
