#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nameval Nameval;
typedef struct Nvtab Nvtab;

struct Nameval{
    char *name;         //имя
    int value;          //значение
    Nameval *next;      //следующий в списке
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
    for(p = listp; p->next !=NULL; p = p->next)
        ;
    p->next = newp;
    return listp;
}

//поис элемента, возврат указателя на элемент
Nameval *lookup(Nameval *listp, char *name){
    for( ; listp!=NULL; listp = listp->next){
        if(strcmp(name, listp->name) == 0){
            return listp;
        }
    }
    return NULL;        //элемент не найден
}

/* printnv: вывести имя и значения по строке формата arg */
void printnv(Nameval *nameval, void *arg){
    char *fmt;
    
    fmt = (char *) arg;
    printf(fmt, nameval->name, nameval->value);
}

/* apply: выполняет fn для каждого элемента списка listp */
void apply(Nameval *listp, void (*fn)(Nameval*, void*), void *arg){
    
    for(; listp != NULL; listp = listp->next){
        (*fn)(listp, arg);  /* вызов функции */
    }
}

//счётчик количества элементов
void inccounter(Nameval *p, void *arg){
    int *ip;
    
    ip = (int *) arg;
    (*ip)++;
}

/* freeall: освобождение всех элементов списка listp */
void freeAll(Nameval *listp){
    Nameval *next;
    
    for(; listp != NULL; listp = next){
        next = listp -> next;
        free(listp);
    }
}

//освобождение лдного элемента
Nameval *delitem(Nameval *listp, char *name){
    Nameval *p, *prev;
    
    prev = NULL;
    for(p = listp; p != NULL; p = p->next){
        if(strcmp(name, p->name) == 0){
            if(prev == NULL){
                listp = p->next;
            } else{
                prev->next = p->next;
                free(p);
                return listp;
            }
        }
        prev = p;
    }
    //eprintf("delitem: %s not in list", name);
    return NULL;
}

int main(int argc, char **argv)
{   
    Nameval *nvlist;
    nvlist = addfront(nvlist, newitem("good", 2));
    nvlist = addfront(nvlist, newitem("bad", 3));
    nvlist = addend(nvlist, newitem("true", 1));
    nvlist = addfront(nvlist, newitem("false", 4));
    
    apply(nvlist, printnv, "%s: %d\n");
    //freeAll(nvlist);
    printf("\n");
    delitem(nvlist, "good");
    apply(nvlist, printnv, "%s: %d\n");
    //int np;
    //np = 0;
    //apply(nvlist, inccounter, &np);
    //printf("List have: %d elements\n", n);
    //из за malloc() не возможно выполнить apply с разными функциями
    //вызывает ошибку
    //nvlist = lookup(nvlist, "bad");
    //printf("%s: %x\n", nvlist->name, nvlist->value);
    
}
