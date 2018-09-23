typedef struct Suffix Suffix; /*элемент типа суффикса*/

struct Suffix{
    
    char *word;         /*указатель на слово в списке суффиксов*/
    Suffix *next;       /*указатель на следующий элемент в списке суффиксов*/
    
};