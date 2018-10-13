#include <stdio.h>

typedef struct Nameval Nameval;
struct Nameval{
    char *name;
    int value;
    Nameval *left;  /* меньшее значение */
    Nameval *right; /* большее значение */
}myTree;

/* insert: вставляет newp в дерево treep, возвращает treep */
Nameval *insert(Nameval *treep, Nameval *newp){
    int cmp;
    
    if(treep == NULL){
        return newp;
    }
    cmp = strcmp(newp->name, treep->name);
    if(cmp == 0){
        printf("Dublicate %s is ignored", newp->name);
    }else if(cmp < 0){
        treep -> left = insert(treep -> left, newp);
    }else{
        treep -> right = insert(treep -> left, newp);
    }
    return treep;
}

/* lookup: ищет имя name в дереве treep */
Nameval *lookup(Nameval *treep, char *name){
    int cmp;
    
    if(treep == NULL){
        return NULL;
    }
    cmp = strcmp(name, treep->name);
    if(cmp == 0){
        return treep;
    }else if(cmp < 0){
        return lookup(treep -> left, name);
    }else{
        return lookup(treep -> right, name);
    }
}

/* applyInOrder: симметричное применение функции fn к treep https://www.cbar.az/hr/f?p=100:101:11044056071480:::::*/
void applyInOrder(Nameval *treep, void (*fn)(Nameval*, void*), void *arg){
    if (treep == NULL){
        return;
    }
    applyInOrder(treep->left, fn, arg);
    (*fn)(treep, arg);
    applyInOrder(treep->right, fn, arg);
}

/* applyPostOrder: концевой обход с вызовом fn */
void applyPostOrder(Nameval *treep, void (*fn)(Nameval*, void*), void *arg){
        if(treep == NULL){
            return;
        }
        applyPostOrder(treep->left, fn, arg);
        applyPostOrder(treep->right, fn, arg);
        (*fn)(treep, arg);
}

int main(int argc, char **argv)
{   
    //applyInOrder(myTree, printv, "%s: %x\n")
    //applyPostOrder(myTree, printv, "%s: %x\n")
	return 0;
}
