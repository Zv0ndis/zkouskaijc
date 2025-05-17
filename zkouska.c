#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int swit1() {
    static char str[10] = "ABCD";   // Statické pole 10 znaků. Víckrát se funkce nevolá takže je mi jedno že to je static
    char *s[10] = { str, "EFGH" };  // To stejný jako vejš 
    strcpy((*s) + 2, "1234");       // Od znaku 'C' se nakopíruje "1234". Závorka která je vcelku zbytečná * má větší prioritu než sčítání. V str je nyní {'A', 'B', '1', '2', '3', '4, \0, ...bordel}
    return ((*s)++)[5];
}

int main() {
    char sum = swit1();
    printf("sum: %c\n", sum);
    int p[9][10];
    printf("sizeof(p) = %ld\n", sizeof(p));  // Velikost pole 9x10 floatů
    return 0;
}