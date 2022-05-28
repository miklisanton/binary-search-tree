#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node *left;
    struct node *right;
    int data;
}node_t;

node_t *new_node(int data){
    node_t *node = malloc(sizeof (node_t));

    node->left = NULL;
    node->right = NULL;
    node->data = data;
    return node;
}

node_t *insert(node_t *root, int data){
    if (root == NULL){
        root = new_node(data);
    } else if (data > root->data){
        root->right = insert(root->right, data);
    } else if (data < root->data){
        root->left = insert(root->left, data);
    }
    return root;
}

node_t *get_max(node_t *root){
    if (root->right != NULL){
        return get_max(root->right);
    }
    return root;
}

node_t *delete(node_t *root, int data){
    if (root == NULL){
        return root;
    } else if (data > root->right){
        root->right =  delete(root->right, data);
    } else if (data < root->left){
        root->left = delete(root->left, data);
    } else if (data == root->data){
        if (root->right == NULL && root->left == NULL){
            free(root);
            return NULL;
        } else if (root->left == NULL){
            node_t *tmp = root;
            root = root->right;
            free(tmp);
            return root;
        } else if (root->right == NULL){
            node_t *tmp = root;
            root = root->left;
            free(tmp);
            return root;
        } else{
            node_t *tmp = get_max(root->left);
            root->data = tmp->data;
            root->left = delete(root->left, tmp->data);
        }
    }
    return root;
}

// returns 1 if data is in list, 0 if not
int find(node_t *root, int data){
    if (root == NULL){
        return 0;
    } else if (data > root->data){
        return find(root->right, data);
    } else if (data < root->data){
        return find(root->left, data);
    } else if (data == root->data){
        return 1;
    } else{
        return 0;
    }
}

void delete_tree(node_t *root){
    if (root != NULL){
        if (root->left != NULL){
            delete_tree(root->left);
        }
        if (root->right != NULL){
            delete_tree(root->right);
        }
        free(root);
        root = NULL;
    }
}

void print_inline(node_t *root){
    if (root != NULL){
        print_inline(root->left);
        printf("( %d ),", root->data);
        print_inline(root->right);
    }
}

int main() {
    node_t *root = NULL;
    root = insert(root, 3);
    root = insert(root, 34);
    root = insert(root, 4);

    print_inline(root);
    delete_tree(root);
    return 0;
}
