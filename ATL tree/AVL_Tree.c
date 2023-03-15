#include "math.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int max(int num1, int num2) { return (num1 > num2) ? num1 : num2; }

// AVL tree node
struct AVLNode {
  int key;
  int height;
  struct AVLNode *left;
  struct AVLNode *right;
};

// Create a new node with given key
struct AVLNode *createNewNode(int key) {
  struct AVLNode *node = (struct AVLNode *)malloc(sizeof(struct AVLNode));
  node->key = key;
  node->height = 1;
  node->left = NULL;
  node->right = NULL;
  return node;
}

// Get height of a node
int getHeight(struct AVLNode *node) {
  if (node == NULL)
    return 0;
  else
    return node->height;
}

// Get balance factor of a node
int getBalanceFactor(struct AVLNode *node) {
  if (node == NULL)
    return 0;
  else
    return getHeight(node->left) - getHeight(node->right);
}

// Rotate right at node
struct AVLNode *rotateRight(struct AVLNode *node) {
  struct AVLNode *leftChild = node->left;
  struct AVLNode *rightGrandchild = leftChild->right;
  leftChild->right = node;
  node->left = rightGrandchild;
  node->height = 1 + max(getHeight(node->left), getHeight(node->right));
  leftChild->height =
      1 + max(getHeight(leftChild->left), getHeight(leftChild->right));
  return leftChild;
}

// Rotate left at node
struct AVLNode *rotateLeft(struct AVLNode *node) {
  struct AVLNode *rightChild = node->right;
  struct AVLNode *leftGrandchild = rightChild->left;
  rightChild->left = node;
  node->right = leftGrandchild;
  node->height = 1 + max(getHeight(node->left), getHeight(node->right));
  rightChild->height =
      1 + max(getHeight(rightChild->left), getHeight(rightChild->right));
  return rightChild;
}

// Rotate left at node, then right at its left child
struct AVLNode *rotateLeftToRight(struct AVLNode *node) {
  node->left = rotateLeft(node->left);
  return rotateRight(node);
}

// Rotate right at node, then left at its right child
struct AVLNode *rotateRightToLeft(struct AVLNode *node) {
  node->right = rotateRight(node->right);
  return rotateLeft(node);
}

// Insert a node with given key in the tree rooted at root
struct AVLNode *insertNode(struct AVLNode *root, int key) {
  if (root == NULL)
    return createNewNode(key);
  if (key < root->key)
    root->left = insertNode(root->left, key);
  else if (key > root->key)
    root->right = insertNode(root->right, key);
  else
    return root;
  root->height = 1 + max(getHeight(root->left), getHeight(root->right));
  int balanceFactor = getBalanceFactor(root);
  if (balanceFactor > 1 && key < root->left->key)
    return rotateRight(root);
  if (balanceFactor < -1 && key > root->right->key)
    return rotateLeft(root);
  if (balanceFactor > 1 && key > root->left->key)
    return rotateLeftToRight(root);
  if (balanceFactor < -1 && key < root->right->key)
    return rotateRightToLeft(root);
  return root;
}

// Utility function to display the AVL tree using inorder traversal
void displayTree(struct AVLNode *root) {
  if (root == NULL)
    return;
  displayTree(root->left);
  printf("%d ", root->key);
  displayTree(root->right);
}

// Search for an element with given key in the tree rooted at root
struct AVLNode *searchElement(struct AVLNode *root, int key) {
  if (root == NULL || root->key == key)
    return root;
  if (key < root->key)
    return searchElement(root->left, key);
  else
    return searchElement(root->right, key);
}

int main() {
  struct AVLNode *root = NULL; // variable use to store our tree
  int keyToSearch = 0;         // variable use to store searching value
  int arr[MAX]; // array to store our input values that will be feeding to our
                // tree
  int i, n;     // iteration variable and size of our array

  printf("Enter elements of the array separated by space: ");
  for (i = 0; i < MAX && scanf("%d,", &arr[i]) == 1 && getchar() != '\n'; i++)
    ;        // receive inputs and store them into our array
  n = i + 1; // saving the inputs size

  printf("size = %d\n", n);
  for (int i = 0; i < n; i++) {
    root = insertNode(root, arr[i]);
  }

  printf("AVL tree: ");
  displayTree(root);
  printf("\n");

  printf("What's the value that you want to find: ");
  scanf("%d", &keyToSearch);
  struct AVLNode *searchResult = searchElement(root, keyToSearch);
  if (searchResult == NULL)
    printf("%d not found in the AVL tree\n", keyToSearch);
  else
    printf("%d found in the AVL tree\n", searchResult->key);

  return 0;
}