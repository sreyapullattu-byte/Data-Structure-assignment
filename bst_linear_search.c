#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 8

// Structure of a BST node
struct Node {
    char key[20];
    struct Node *left;
    struct Node *right;
};

// Create a new node
struct Node* createNode(char key[]) {
    struct Node* newNode =
        (struct Node*)malloc(sizeof(struct Node));

    strcpy(newNode->key, key);
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Insert a key into BST
struct Node* insert(struct Node* root, char key[]) {

    if (root == NULL)
        return createNode(key);

    if (strcmp(key, root->key) < 0)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

// Inorder traversal
void inorder(struct Node* root) {

    if (root != NULL) {
        inorder(root->left);
        printf("%s ", root->key);
        inorder(root->right);
    }
}

// BST Search
int bstSearch(struct Node* root, char key[], int *comparisons) {

    *comparisons = 0;

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

// Linear Search
int linearSearch(char arr[][20], int n,
                 char key[], int *comparisons) {

    *comparisons = 0;

    for (int i = 0; i < n; i++) {

        (*comparisons)++;

        if (strcmp(arr[i], key) == 0)
            return 1;
    }

    return 0;
}

// Calculate tree height
int height(struct Node* root) {

    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}

int main() {

    char keys[N][20] = {
        "A102",
        "A25",
        "A7",
        "B100",
        "B12",
        "A120",
        "B3",
        "A45"
    };

    struct Node* root = NULL;

    // Construct BST
    for (int i = 0; i < N; i++)
        root = insert(root, keys[i]);

    printf("IDENTIFICATION NUMBERS\n");
    printf("----------------------\n");

    for (int i = 0; i < N; i++)
        printf("%s ", keys[i]);

    printf("\n\nINORDER TRAVERSAL\n");
    printf("-----------------\n");
    inorder(root);

    printf("\n\nBST HEIGHT = %d levels\n", height(root));

    // Selected search keys
    char searchKeys[][20] = {
        "A102",
        "A120",
        "A7",
        "B12",
        "B3",
        "A45"
    };

    int m = 6;

    printf("\n\nSEARCH PERFORMANCE\n");
    printf("------------------\n");
    printf("Key\tBST\tLinear\n");

    for (int i = 0; i < m; i++) {

        int bstComp, linearComp;

        bstSearch(root, searchKeys[i], &bstComp);

        linearSearch(keys, N, searchKeys[i], &linearComp);

        printf("%s\t%d\t%d\n",
               searchKeys[i],
               bstComp,
               linearComp);
    }

    // Sorted insertion order
    char sortedKeys[N][20] = {
        "A102",
        "A120",
        "A25",
        "A45",
        "A7",
        "B100",
        "B12",
        "B3"
    };

    struct Node* sortedRoot = NULL;

    for (int i = 0; i < N; i++)
        sortedRoot = insert(sortedRoot, sortedKeys[i]);

    printf("\nINSERTION ORDER ANALYSIS\n");
    printf("-----------------------\n");

    printf("Original insertion order height : %d levels\n",
           height(root));

    printf("Sorted insertion order height   : %d levels\n",
           height(sortedRoot));

    return 0;
}
