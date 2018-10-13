#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRING_DATA "5+3-4+2-1-6-9+7"

typedef int T;

typedef struct Node
{
    T data;
    
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node;

Node* getFreeNode(T value, Node *parent){
    Node* tmp = (Node*)malloc(sizeof(Node));
    
    tmp->left = tmp->right = NULL;
    
    tmp->data = value;
    tmp->parent = parent;
    
    return tmp;
}

void insert(Node **head, T value){
    
    Node *tmp = NULL;
    
    if(*head == NULL){
        *head = getFreeNode(value, NULL);
        return;
    }
    
    tmp = *head;
    
    while(tmp){
        if(value > tmp->data){
            if(tmp->right){
                tmp = tmp->right;
                continue;
            } else {
                tmp->right = getFreeNode(value, tmp);
                return;
            }
        }else if(value < tmp->data){
            if(tmp->left){
                tmp = tmp->left;
                continue;
            } else {
                tmp->left = getFreeNode(value, tmp);
                return;
            }
        }
    }
    
}


void printTree(Node *root, const *dir, int level){
    if(root){
        printTree(root->left, "left", level+1);
        
        if(43 == root->data){
            printf("lvl %d %s = +\n", level, dir);
        }else if(45 == root->data){
            printf("lvl %d %s = -\n", level, dir);
        }else{
            printf("lvl %d %s = %d\n", level, dir, root->data);
        }
        
        printTree(root->right, "right", level+1);
    }
}

int calculate(Node *root){
    
    if(root->left){
        calculate(root->left);
        if((root->data) == '+'){
            return (root->data) = (root->left->data) + (root->right->data);
        } else if((root->data) == '-'){
            return (root->data) = (root->left->data) - (root->right->data);
        }
    }
}

Node* insrt(Node *child, int data, int value){
    
    Node *tmp = getFreeNode(data, NULL);
    tmp->left = child;
    tmp->right = getFreeNode(value, tmp);
    
    return tmp;
}

int main(int argc, char **argv)
{
    
    char* string = malloc(sizeof(char)*strlen(STRING_DATA));
    strcpy(string, STRING_DATA);
    int i;
    
    Node *first = NULL;
    first = getFreeNode(string[1], NULL);
    first->left = getFreeNode(string[0] - '0', &first);
    first->right = getFreeNode(string[2] - '0', &first);
    
    Node *prev = first;
    Node *root = NULL;
    
    for(i = 3; i < strlen(STRING_DATA); i+=2){
        printf("%c ", string[i]);
        if(string[i] == '-'||string[i] == '+'){
            int data = string[i+1] - '0';
            root = insrt(prev, string[i], data);
            prev = root;
        }
    }
    
    printf("\n");

    //printTree(root, "root", 0);
    
    printf("%d\n", calculate(root));
}
