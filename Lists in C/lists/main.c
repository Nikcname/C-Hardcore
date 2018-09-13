#include <stdio.h>
#include <stdlib.h>

typedef struct Nameval Nameval;

struct Nameval{
    char *name;
    int value;
    Nameval *next;
};

Nameval *newitem(char *name, int value){
    Nameval *newp;
    
    newp = (Nameval *) malloc(sizeof(Nameval));
    newp->name = name;
    newp->value = value;
    newp->next = NULL;
    return newp;
}

Nameval *addfront(Nameval *listp, Nameval *newp){
    newp->next = listp;
    return newp;
}

Nameval *addend(Nameval *listp, Nameval *newp){
    
    Nameval *p;
    
    if(listp == NULL){
        return newp;
    }
    
    for(p = listp; p->next != NULL; p = p->next);
    
    p->next = newp;
    
    return listp;
}

Nameval *lookup(Nameval *lisp, char *name){
    
    for(; lisp != NULL; lisp = lisp->next)
    {
        if(name == lisp->name){
            return lisp;
        }
    }
    return NULL;
}

int main()
{      
    
    
}
