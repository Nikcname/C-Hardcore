#include <stdio.h>
#include <stdlib.h>

typedef struct Nameval Nameval;
typedef struct Nvtab Nvtab;

struct Nameval{
    char *name;         //имя
    int value;          //значение
};

struct Nvtab {
    int nval;           //текущее кол-во элементов
    int max;            //количество выделенных ячеек
    Nameval *nameval    //массив пар имя-значение
}myArray;

enum{
    NVINIT = 1,
    NVGROW = 2
};

//добавляем новое имя и структуру в myArray
int addname(Nameval newname){
    
    Nameval *nvp;
    if(myArray.nameval == NULL){
        myArray.nameval = (Nameval *) malloc(NVINIT * sizeof(Nameval));
        if(myArray.nameval == NULL){
            return -1;
        }
        myArray.max = NVINIT;
        myArray.nval = 0;
    } else if(myArray.nval >= myArray.max){
        nvp = (Nameval *) realloc(myArray.nameval, (NVGROW*myArray.max) * sizeof(Nameval));
        if(nvp == NULL){
            return -1;
        }
        myArray.max *= NVGROW;
        myArray.nameval = nvp;
    }
    myArray.nameval[myArray.nval] = newname;
    return myArray.nval++;
}

//удаляем элемент с определённым именеи из myArray
int delname(char *name){
    int i;
    for(i=0; i < myArray.nval; i++){
        if(myArray.nameval[i].name == name){
            memmove(myArray.nameval+i, myArray.nameval+i+1, (myArray.nval-(i+1)) * sizeof(Nameval));
            myArray.nval--;
            return 1;
        }
    }
    return 0;
}

int main(int argc, char **argv)
{   
    int i;
    Nameval name1;
    name1.name = "One";
    name1.value = 1;
  
    Nameval name2;
    name2.name = "Two";
    name2.value = 2;
    
    Nameval name3;
    name3.name = "Tree";
    name3.value = 3;
    
    Nameval name4;
    name4.name = "Four";
    name4.value = 4;
    
    Nameval name5;
    name5.name = "Five";
    name5.value = 5;
    
    addname(name3);
    addname(name5);
    addname(name1);
    addname(name4);
    addname(name2);
    
    for(i=0; i < myArray.nval; i++){
        printf("%s\t%d\n", myArray.nameval[i].name, myArray.nameval[i].value);
    }
    
    delname("One");
    delname("Four");
    
    printf("Perform delete...\n");
    
    for(i=0; i < myArray.nval; i++){
        printf("%s\t%d\n", myArray.nameval[i].name, myArray.nameval[i].value);
    }
    
}
