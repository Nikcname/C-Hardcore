typedef struct State State; /*элемент префикс*/

struct State{
    
    char    *pref[NPREF];   /*указатель на строку символов размером NPREF
                            количество слов префиксов*/
    Suffix  *suf;           /*указатель на список суффиксов*/
    State   *next;          /*указатель на следующий элемент в хеш таблице*/
    
};