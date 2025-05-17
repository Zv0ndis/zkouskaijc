#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t fa(void *pole[4][5][6]) { return sizeof((*pole)[4]); }

int f(void) {
    static const char s[][10] = {
        "12345",
        "ABCDE",
    };
    printf("%s\n", s[1] + 2);
    // printf("%s\n", s[0]);
    return strlen(s[1] + 2);
}

int fx(int x) {
 static char *s = "ABCDEFGHIJKL";
 const char (*p)[4] = (void*)(s + x);
 return * (const char*)(p - 1);
}

int main() {
    printf("%c", *("01"
                   "23" +
                   5 - 1));
    printf("Funkce fa vrati:%d\n", fa(NULL));
    printf("Velikost jednoho radu je 6x * sizeof(void ukazatel): %d\n", 6 * sizeof(void *));

    printf("Funkce f vrati:%d\n", f());
    printf("Funkce fx vrati:%d\n", fx(3));
}