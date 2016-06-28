#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define BUFFER_SIZE 1024

int bank_danych_size = 0;
extern int bank_danych_size;
int kolory_size = 0;
extern kolory_size;

void notatki_testy(){
/*
    char *tekst;
    for(i = 0; i < 100; i++){
        if(wzory[i] != NULL){
            printf("\nNieznanych %d:\n",i);
        }

        tekst = bank_wzorow_pop(i,wzory);
        while( tekst[0] != 0){
            printf("%s\n",tekst);
            tekst = bank_wzorow_pop(i,wzory);
        }
    }
    */
/*
for(i = 0 ; i < 100; i++){
        if(wzory[i] != NULL){
            bank_wzorow *ptr = wzory[i];
            j = 1;
            printf("%s\n",ptr->wzor);
            while(ptr->next != NULL){
            j++;
            ptr = ptr->next;
            printf("%s\n",ptr->wzor);
            }
        printf("Size tab[%d] = %d\n\n",i,j);
        }
    }
*/


return;
}

struct queue{
    char** queue;
    int size;
};
typedef struct queue queue;


struct ch_stack{
    char* val;
    struct ch_stack *next;
};
typedef struct ch_stack ch_stack;

struct stack{
    int val;
    struct stack *next;
};
typedef struct stack stack;

struct rule{
    char* rule;
};
typedef struct rule rule;

struct bank_danych{
    char *nazwa;
	int wartosc;
};
typedef struct bank_danych bank_danych;

struct bank_wzorow{
    char *wzor;
	struct bank_wzorow* next;
};
typedef struct bank_wzorow bank_wzorow;

void queue_put(char* x, queue *q){
    if(q->queue == NULL){
        q->queue = malloc(sizeof(char) * BUFFER_SIZE);
        q->size = 0;
    }
    if(q->queue[q->size] == NULL){
        q->queue[q->size] = malloc(sizeof(char) * BUFFER_SIZE);
    }
    strcpy(q->queue[q->size],x);
    q->size++;
}
char* queue_get(queue *q){
    if(q->queue == NULL || q->size == 0 ){
        return "";
    }
    char* res = malloc(sizeof(char)*BUFFER_SIZE);
    strcpy(res,q->queue[0]);
    int i = 1;
    while(i < q->size){
        strcpy(q->queue[i-1],q->queue[i]);
        i++;
    }
    q->size--;
    return res;
}
int queue_is_empty(queue *q){
    if(q->size == 0)return 1; /* pusta */
    else return 0; /* cos jest  */
}

int calc(int x, int y, int op){
    switch(op){ /*  tu jest dzialanie  */
                        case 1:
                            return AND(x,y);
                        case 2:
                            return OR(x,y);
                        default:
                            return 3;
                    }
}
int AND(int a, int b){
    if(a == 1 && b == 1)return 1;
    return 2;
}
int OR(int a, int b){
    if(a == 1 || b == 1)return 1;
    return 2;
}
void read_data(FILE* fdane_in, bank_danych** dane){

    if(fdane_in == NULL || dane == NULL)return ;
    char *nazwa, *wartosc;
    char line[BUFFER_SIZE];
    //char * linia = malloc(sizeof(char) * BUFFER_SIZE);
    char* pch;
    while(fgets(line,BUFFER_SIZE,fdane_in)){  // wczytuje dane i zapisuje do banku danych
        //printf("Taka linia :%s", line);
        pch = strtok (line, " = ");
        //printf ("%s " ,pch);     //nazwa
        nazwa = pch;
        pch = strtok (NULL," = ");
        //printf("%s", pch);          // wartosc
        wartosc = pch;
        bank_danych_add(nazwa,wartosc, dane);
    }
}
void read_rules(FILE* fwzory_in, bank_danych** dane, bank_wzorow ** wzory){
    if(fwzory_in == NULL || wzory == NULL )return ;
    char line[BUFFER_SIZE];
    while(fgets(line,BUFFER_SIZE,fwzory_in)){
        bank_wzorow_add(line,wzory,dane);

    }
}
void substr(char* dest, char*src, int start, int end){
    int j = 0;
    int i;
    for( i = start; i < end; i++)dest[j++] = src[i];
    dest[j] = 0;
}
void bank_danych_add(char *nazwa, char* wartosc, bank_danych *bank[] ){
	//printf("Dodaje dane!\n");
	//printf("%s >>%s<<\n", nazwa, wartosc);

	bank[bank_danych_size] = malloc( sizeof(bank_danych) );
	bank[bank_danych_size]->nazwa = malloc(sizeof(char) * strlen(nazwa));
	strcpy( bank[bank_danych_size]->nazwa, nazwa);
	if(strchr(wartosc,'T') != NULL )bank[bank_danych_size]->wartosc = 1;  //true
	else if(strchr(wartosc,'F') != NULL )bank[bank_danych_size]->wartosc = 2; //false
	//else if(strchr(wartosc,'N') != NULL ))bank[bank_danych_size]->wartosc = 3; //nondefined
    bank_danych_size++;
	//printf("Dodano :%s o wartosci: %d. Teraz bank ma size:%d\n", bank[bank_danych_size-1]->nazwa, bank[bank_danych_size-1]->wartosc, bank_danych_size);
	return;
}
int bank_danych_get(char*nazwa, bank_danych *bank[]){
    int i=0;
    while(strcmp(bank[i]->nazwa, nazwa) != 0){
        i++;
        if(i == bank_danych_size)return 3;
    }
    return bank[i]->wartosc;
}

void kolory_bank_danych_add(char *nazwa, char* wartosc, bank_danych *bank[] ){

	bank[kolory_size] = malloc( sizeof(bank_danych) );
	bank[kolory_size]->nazwa = malloc(sizeof(char) * strlen(nazwa));
	strcpy( bank[kolory_size]->nazwa, nazwa);
	if(strchr(wartosc,'T') != NULL )bank[kolory_size]->wartosc = 1;  //true
	else if(strchr(wartosc,'F') != NULL )bank[kolory_size]->wartosc = 2; //false
    kolory_size++;
	return;
}
int kolory_bank_danych_get(char*nazwa, bank_danych *bank[]){
    int i=0;
    if(bank[i] == NULL)return 3;
    while(strcmp(bank[i]->nazwa, nazwa) != 0){
        i++;
        if(i == kolory_size)return 3;
    }
    return bank[i]->wartosc;
}


void bank_wzorow_add(char* wzor, bank_wzorow **wzory, bank_danych **dane ){

    char *elem = malloc(sizeof(char) * BUFFER_SIZE);
    int nieznanych, i, j;
    nieznanych = 0;
    for(i = 0; i < strlen(wzor) ; i++){ //zliczanie ilosc nieznanych elementow
            if( (wzor[i] >= 65 && wzor[i] <= 90 ) || (wzor[i] >= 97 && wzor[i] <= 122 ) ){  // tzn A-Z lub a-z
                j = i;
                while((wzor[j] >= 65 && wzor[j] <= 90 ) || (wzor[j] >= 97 && wzor[j] <= 122 )){j++;} //przewin az to konca nazwy
                substr(elem, wzor, i ,j);
                if(bank_danych_get(elem,dane) == 3){nieznanych++;}
                i = j; //po przesunieciu, 2 razy nie skanujemy tego samego

            }
        if(wzor[i] == '>'){break;}
        j = 0;
        }
        if(wzory[nieznanych] == NULL){
        wzory[nieznanych] = malloc(sizeof(bank_wzorow));
        wzory[nieznanych]->wzor = malloc(sizeof(char) * BUFFER_SIZE);
        strcpy(wzory[nieznanych]->wzor,wzor);
        return;
        }

    bank_wzorow *ptr = wzory[nieznanych];

    while(ptr->next != NULL){
        ptr = ptr->next;
    }
    ptr->next = malloc(sizeof(bank_wzorow));
    ptr = ptr->next;
    ptr->wzor = malloc(sizeof(char) * BUFFER_SIZE);
    strcpy(ptr->wzor,wzor);
    //printf("%s\n",ptr->wzor);
}
char* bank_wzorow_pop(int index, bank_wzorow **wzory){  /* dostaje sie wzor spod konkretnego indeksu, ktory jest usuwany z bazy */
    //printf("Chcesz pop :%d >%s<\n",wzory[index]->wzor,wzory[index]->wzor);
    if(wzory == NULL || wzory[index] == NULL || wzory[index]->wzor == 0 ){
      //          printf("TU!\n");
                return "";}
    bank_wzorow* ptr,* poprz;

    ptr = wzory[index];
    poprz = ptr;

    while(ptr->next != NULL){  // szukamy przedostatniego
        //printf("Petla!\n");
        poprz = ptr;
        ptr = ptr->next;
    }

    char *wynik = malloc( sizeof(char) * BUFFER_SIZE);
    strcpy(wynik, ptr->wzor);
    ptr->wzor = 0;
    //if(wynik[0] != 0){free(ptr);}
    if(poprz != NULL)poprz->next = NULL;
    return wynik;

}
int bank_wzorow_size_at(int index, bank_wzorow ** wzory){
     //printf("Listing at %d\n",index);
     bank_wzorow* ptr;
     int j ;
     j = 0;
     ptr = wzory[index];
        while(ptr != NULL){
            //printf(">%s\n",ptr->wzor);
            if(ptr->wzor!=0)j++;
            ptr = ptr->next;
        }
      return j;
}
int bank_wzorow_not_empty(bank_wzorow **wzory){ /*  1 - jest cos do liczenia 0 - puste  */
    int i;
    for( i = 0; i < BUFFER_SIZE ; i++){
        if(bank_wzorow_size_at(i,wzory) != 0)return 1;
    }
    return  0;
}
int bank_wzorow_size_all(bank_wzorow **wzory){
    //printf("Size all!\n");
    int i, result;
    result = 0;
    for( i = 0; i < BUFFER_SIZE ; i++){
        result += bank_wzorow_size_at(i,wzory);
    }
    return  result;
}
queue* bank_wzorow_get_by_element(char* x, bank_wzorow **wzory){
    queue *res = malloc(sizeof(queue));
    int i,j;
    char *tmp;
    bank_wzorow *ptr;
    tmp = malloc(sizeof(char) * BUFFER_SIZE);
    for(i = 0; i < BUFFER_SIZE; i++){
        ptr = wzory[i];
        while(ptr != NULL && ptr->wzor != NULL){
            //printf("i: %d ptr->wzor:>%s<\n",i,ptr->wzor);
            for(j = 0; ptr->wzor[j]!='>'; j++){} /* przewija j do poczatku prawej strony */

            substr(tmp,ptr->wzor,j, strlen(ptr->wzor));
            //printf("i:%d wzor:%s tmp: %s\n", i ,ptr->wzor, tmp);
            if(strstr(tmp, x) != NULL){
                //printf("Poszukiwalismy %s wiec dodajemy %s\n",tmp, ptr->wzor);
                queue_put(ptr->wzor,res);
            }
            ptr = ptr->next;
            tmp[0]=0;
        }
    }
    return res;
}

int eval(char *wyrazenie, bank_danych** bank){  /* oblicza wartosc i dodaje do banku, 0 - porazka 1 - prawda 2 - falsz  */
    wyrazenie[strlen(wyrazenie)-1] = 0;
    //printf("Takie dostal wyrazenie: >>%s<<\n", wyrazenie);

    stack *stos_wart, *stos_dzial;
    stos_dzial = malloc(sizeof(stack));
    stos_wart = malloc(sizeof(stack));
    char *elem;
    elem = malloc(sizeof(char)* BUFFER_SIZE);
    int i, j, tmp, negacja, czyNegowac, czyLiczyc, A, B;
    czyNegowac = 0;
    czyLiczyc = 0;
    tmp = 0;
    negacja = 0;

    for(i = 0; i < strlen(wyrazenie) ; i++){
    if(wyrazenie[i] == '>'){break;} /* => jest rozgraniczeniem miedzy prawa a lewa strona  */
    //if(i > 98)printf("kreciola: %d\n",i);
        if(( wyrazenie[i-1] == '&') && (wyrazenie[i-1] == wyrazenie[i] )){
            //printf("AND\n");
            stack_push(1,stos_wart);
            czyLiczyc = 1;
            }

        if(( wyrazenie[i-1] == '|') && (wyrazenie[i-1] == wyrazenie[i] )){
            stack_push(2,stos_wart);
            czyLiczyc = 1;
            //printf("OR\n");
            }

        if( wyrazenie[i] == '(' ){
            //printf("Otwarto nawias!\n");
            czyLiczyc = 0;
            czyNegowac = 0;
            }

        if( wyrazenie[i] == ')' ){
        //printf("Zamykamy!\n");
            if(negacja > 0){
                tmp = stack_get(stos_wart);
                if (tmp == 1){ /* true */
                    tmp = 2; }
                else if(tmp == 2){ tmp = 1; }
                stack_push(tmp,stos_wart);
                negacja --;
            }

            tmp = stack_get(stos_dzial);
            if( tmp == 1 || tmp == 2){
                    A = stack_get(stos_wart);
                    B = stack_get(stos_wart);
                    stack_push(calc( A, B, tmp ),stos_wart);
            }
        }

        if( wyrazenie[i] == '!' ){
            negacja++;
            if(czyNegowac == 1 ){
                czyNegowac = 0;
                negacja -= 2;
                //printf("Wyrzucamy podwojna negacje! %d \n", negacja);
            }else {
                czyNegowac = 1;}
            /*printf("Zanegowano!\n")*/;}

        if( (wyrazenie[i] >= 65 && wyrazenie[i] <= 90 ) || (wyrazenie[i] >= 97 && wyrazenie[i] <= 122 ) ){  // tzn A-Z lub a-z
                j = i;
                while((wyrazenie[j] >= 65 && wyrazenie[j] <= 90 ) || (wyrazenie[j] >= 97 && wyrazenie[j] <= 122 )){j++;} //przewin az to konca nazwy
                substr(elem, wyrazenie, i ,j); /* elem = substr();  */
                /*printf("%s : %d\n",elem, bank_danych_get(elem,bank));*/
                //printf("%s : %d\n",elem, bank_danych_get(elem,bank));
                i = j-1; //po przesunieciu, 2 razy nie skanujemy tego samego
                tmp = bank_danych_get(elem,bank);
                if(czyNegowac == 1){

                        if (tmp == 1){ /* true */
                            tmp = 2; }
                        else if(tmp == 2){ tmp = 1; }

                        negacja--;
                        czyNegowac = 0;
                //printf("Zanegowano!\n");
                }
                stack_push(tmp,stos_wart);
                //printf("tmp : %d\n",tmp);
                if(czyLiczyc == 1){
                    A = stack_get(stos_wart);
                    B = stack_get(stos_wart);
                    stack_push(calc( A, B, tmp ),stos_wart);
                    czyLiczyc = 0;
                }
            }
        //printf("\n");

    }
    //printf("To sie wykonuje!\n");
    int result = stack_get(stos_wart);

    j = 0;
    negacja = 0; /* just to be sure */
    for( ; i < strlen(wyrazenie) ; i++){
        if(wyrazenie[i] == '!')negacja++;
        if( (wyrazenie[i] >= 65 && wyrazenie[i] <= 90 ) || (wyrazenie[i] >= 97 && wyrazenie[i] <= 122 ) ){  // tzn A-Z lub a-z
                j = i;
                while((wyrazenie[j] >= 65 && wyrazenie[j] <= 90 ) || (wyrazenie[j] >= 97 && wyrazenie[j] <= 122 )){j++;} //przewin az to konca nazwy
                substr(elem, wyrazenie, i ,j);
                i = j-1;
                }
    }
    //printf("Element to : >>%s<<\nNegacja :%d\n",elem, negacja);
    if(negacja % 2 == 1){
        if(result == 1){
            result = 2;
        }
        else if (result == 2){
            result = 1;
        }
    }
     if(result == 1){
            bank_danych_add(elem,"T",bank);
            //printf("Wynik to False\n");
            return 1;
        }
        else if (result == 2){
            bank_danych_add(elem,"F",bank);
            return 2;
            //printf("Wynik to True\n");
        }
    //printf("Wynik : %d\n", result);
    return 3;
}

int stack_get(stack *stos){
    stack* ptr;
    if(stos == NULL){return -3; /*ERROR!*/ }
    if(stos->next == NULL){
        int tmp = stos->val;
        stos = NULL;
        return tmp;
    }
    ptr = stos;
    while(ptr->next->next != NULL){ /*chcemy przedostatni*/
        ptr = ptr->next;
    }
    int tmp = ptr->next->val;
    ptr->next = NULL;
    return tmp;

}
void stack_push(int val, stack* stos){

    stack* ptr;
    ptr = stos;
    while(ptr->next != NULL){
        ptr = ptr->next;
    }
    ptr->next = malloc(sizeof(stack));
    ptr->next->val = val;
}
void count_all(bank_wzorow **wzory){
    int i;
    for( i=0;i<10;i++ ){
        printf("tab[%d] = %d\n",i, bank_wzorow_size_at(i, wzory));
    }
}

int ch_stack_get(ch_stack *stos){
    ch_stack* ptr;
    if(stos == NULL){return ""; /*ERROR!*/ }
    if(stos->next == NULL){
        char tmp = stos->val;
        stos = NULL;
        return tmp;
    }
    ptr = stos;
    while(ptr->next->next != NULL){ /*chcemy przedostatni*/
        ptr = ptr->next;
    }
    char* tmp = malloc(sizeof(char) * BUFFER_SIZE);
    strcpy(tmp,ptr->next->val);
    ptr->next = NULL;
    return tmp;

}
void ch_stack_push(char* val, ch_stack* stos){
    ch_stack* ptr;
    ptr = stos;
    while(ptr->next != NULL){
        ptr = ptr->next;
    }
    ptr->next = malloc(sizeof(stack));
    ptr->next->val = malloc(sizeof(char) * BUFFER_SIZE);
    strcpy(ptr->next->val,val);
}



void forward(char *szukana, bank_wzorow **wzory, bank_danych** dane){
    printf("Wnioskowanie w przód.\nChcemy szukać :%s.\n", szukana);
    char *wzor;
    int i,poprzedniaIloscWzorow, j, res;
    bank_wzorow* ptr;
    wzor = malloc(sizeof(char) * BUFFER_SIZE);
    poprzedniaIloscWzorow = -1; /* wartosc nie do uzyskania, zawsze jeden obieg petli i proba policzenia czegos  */

    while(poprzedniaIloscWzorow != bank_wzorow_size_all(wzory) && bank_wzorow_size_all(wzory) != 0){
        poprzedniaIloscWzorow = bank_wzorow_size_all(wzory);
        for( i = 0 ; i < BUFFER_SIZE ; i++){
             j = bank_wzorow_size_at(i,wzory);
             while(j -- > 0){
                //printf("i = %d j = %d\n", i,j);
                wzor = bank_wzorow_pop(i , wzory);
                res = eval(wzor, dane);
                if( res == 3 ){ /* nie zostalo obliczone - wraca do bazy  */
                   bank_wzorow_add(wzor,wzory,dane);}
                else{
                    printf("Obliczamy wartosc wyrazenia: \"%s\" ... ",wzor);
                    if(res == 1 )printf("PRAWDA!\n");
                    else printf("FAŁSZ!\n");
                }
                if(bank_danych_get(szukana,dane) != 3){ /* tzn. juz obliczylismy wynik*/
                    goto final_output;
                }
             }
        }
    }
    final_output:
    res = bank_danych_get(szukana,dane);
    if(res == 1){
        printf("\"%s\" jest prawdą.\n",szukana );
    }
    else if(res == 2){
        printf("\"%s\" jest fałszem.\n",szukana );
    }
    else if(res == 3){
        printf("Podane informacje nie pozwalają na obliczenie wartości \"%s\".\n",szukana);
    }

}
void backward(char *szukana, bank_wzorow **wzory, bank_danych** dane){

    printf("Wnioskowanie w tył.\nChcemy szukac:%s.\n",szukana);
    //Sprawdz czy nie jest juz znana wartosc!
    if(bank_danych_get(szukana,dane) == 1){
        printf("Obliczamy wartosc %s\n", szukana);
        printf("Z bazy danych wynosi ... PRAWDA!\n");
        return;
    }
        else if(bank_danych_get(szukana,dane) == 2 ){
        printf("Obliczamy wartosc %s\n", szukana);
        printf("Z bazy danych wynosi ... FAŁSZ!\n");
        return;
    }
    int i,j, licz;
    char* element,*wzor;
    queue *q, *q2;
    ch_stack *ch_stck;
    ch_stck = malloc(sizeof(ch_stack));
    q = malloc(sizeof(queue));
    q2 = malloc(sizeof(queue));
    bank_danych **kolory = malloc(sizeof(bank_danych) * BUFFER_SIZE);
    licz = 0;
    //wrzuc do kolejki pierwsze zapytanie+
    queue_put(szukana,q);

    while(!queue_is_empty(q)){ // do kiedy kolejka nie pusta:+
        element = queue_get(q); //     wez z kolejki lelement+
        //printf("Kolejna dana w kolejce! %s\n", element);
        q2 = bank_wzorow_get_by_element(element,wzory); // dostan liste wzorow w ktorych wystepuje poszukowany lellement+
        if(queue_is_empty(q2)){//jezeli lista wzorow jest pusta:
            printf("Nie mozna policzyc wartosci %s\n. Dane nie pozwalaja na to.\n");  //wywal blad! nie da sie policzyc
            return ; /* tu konczymy zabawe */
        }

            wzor = queue_get(q2);
            //printf("Element  poszukiwany! %s\n", wzor);
            ch_stack_push(wzor,ch_stck);
            licz++;
            for(i = 0; i < strlen(wzor) ; i++){             //dla kazdego wzoru w liscie:
                if( (wzor[i] >= 65 && wzor[i] <= 90 ) || (wzor[i] >= 97 && wzor[i] <= 122 ) ){  // tzn A-Z lub a-z

                    j = i;
                    while((wzor[j] >= 65 && wzor[j] <= 90 ) || (wzor[j] >= 97 && wzor[j] <= 122 )){j++;} //przewin az to konca nazwy
                    substr(element, wzor, i ,j);

                    if(bank_danych_get(element, dane) == 3){
                        if(kolory_bank_danych_get(element,kolory) == 3){   /* tzn. nie ma go */ /* przetestować */
                            //printf("Nie ma elementu %s, dodajem!\n",element);
                            kolory_bank_danych_add(element,"T",kolory);
                            queue_put(element,q);
                        }
                    }
                    i = j; //po przesunieciu, 2 razy nie skanujemy tego samego
                    }
                    if(wzor[i] == '>'){break;}
                j = 0;
                }

        //jezeli elementu nie ma na stosie:
            //wrzuc wzor na stos
            //zmien kolor wzoru ze juz jest na tym stosie
        }
    int x;
    while(licz--){
        element = ch_stack_get(ch_stck);
        //printf("%d. %s\n",licz, element);
        x = eval(element,dane);
        //printf("Wartosc: %d\n",x);
        element[strlen(element)] = 0; /* ucinamy nowe linie etc.*/
        printf("Obliczamy wartosc wyrazenia: \"%s\" ... ",element);
        if(x == 1){
            printf("PRAWDA!\n");
        }
        else if(x == 2){
            printf("FAŁSZ!\n");
        }
        else
            printf("Wartosc nie do obliczenia!\n");
    }
    x = bank_danych_get(szukana,dane);
    if(x == 1){
        printf("\"%s\" jest prawdą.\n",szukana );
    }
    else if(x == 2){
        printf("\"%s\" jest fałszem.\n",szukana );
    }
    else if(x == 3){
        printf("Podane informacje nie pozwalają na obliczenie wartości \"%s\".\n",szukana);
    }



}


int main(int argc, char* argv[]){ /* plik z danymi, wzorami, F - wnioskowanie w przód / B - wnioskowanie w tył */
    FILE *fdane_in;
    FILE *fwzory_in;
    bank_danych **dane;
    bank_wzorow ** wzory;

    fdane_in = fopen(argv[1], "r");
    fwzory_in = fopen(argv[2], "r");
    dane = malloc(sizeof(bank_danych) * BUFFER_SIZE);
    wzory  = malloc(sizeof(bank_wzorow) * BUFFER_SIZE);


    read_data(fdane_in, dane);
    read_rules(fwzory_in, dane, wzory);
    if(argv[3] == "F"){
        forward("mozGrst",wzory,dane);
    }
    if(argv[3] == "B"){
        backward("mozGrst",wzory,dane);}

    return 0;
}
