#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enum.h"
#include "suffix.h"
#include "state.h"


State *stateTable[NHASH];           /*хеш таблица, должа быть глобальной переменной*/





/*первым делом создаём функцию для вычисления хеш кода для массива из NPREF строк*/
unsigned int hash(char *s[NPREF]){
    
    unsigned int h;
    unsigned char *p;
    int i;
    
    h = 0;
    for(i = 0; i<NPREF; i++){
        for(p = (unsigned char *) s[i]; *p != '\0'; p++)
        {
            h = h * MULTIPLIER + *p;
        }
    }
    return h % NHASH;
}





/*далее создаём функцию для поиска элементов в хеш-таблице
 * функция должна возвращять указатель на префикс
 * фуккция должна создавать новый элемент в таблице если её нет
 * функция должна возвращять NULL если не удалось создать элемент
 * при создании не вызывается strdub поэтому строки нельзя менять */
State* lookup(char *prefix[NPREF], int create){
    
    int i, h;
    State *sp;
    
    h = hash(prefix);           /*вычислили хеш-код*/
    
    for(sp = stateTable[h]; sp != NULL; sp = sp->next){
        
        for(i = 0; i<NPREF; i++){
            if(strcmp(sp->pref[i] , prefix[i]) != 0){
                break;          /*если слова в префиксе не равны словам в хеш таблице
                                * то выходим из дочернего цикла*/
            }
        }
        
        if(i == NPREF){
                return sp;      /*если все слова совпали то возвращаем указатель на элемет*/
        }
        
        /*цикл должен работать до конца перебирая все элементы*/
    }
        
    if(create){         /*если дана команда создать элемент*/
        sp = (State *) malloc(sizeof(State));
        
        for(i = 0; i<NPREF; i++){
            sp->pref[i] = prefix[i];
        }
        
        sp->suf = NULL;
        sp->next = stateTable[h];
        stateTable[h] = sp;
    }
    return sp;
}




/*считываем данные из файла и записываем в таблицу префиксов*/
void build(char *prefix[NPREF], FILE *file){
    
    char buf[100];          /*буфер для слов, размер буфера равен размеру массива buf*/
    
    char fmt[10];           /* формат в котором всё записывается в таблицу
                            * сторока будет сторого длинной размера буфера
                            * максимальная длинна слова тоже равна размеру массива buf-1*/
    
    sprintf(fmt, "%%%ds", (int) sizeof(buf)-1);
    while(fscanf(file, fmt, buf) != EOF){
        
        //add(prefix, buf);
    }
    
}



int main()
{   
    FILE *file;
    file = fopen("template.txt", "r");
    
    
    
    if(file != NULL){
        fclose(file);
        printf("File closed.\n");
    }
    
	printf("%d\n", NPREF);
	printf("%d\n", NHASH);
	printf("%d\n", MAXGEN);
    
}
