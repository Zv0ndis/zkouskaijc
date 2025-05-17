////////////////////////////////// IJC v. 20.2 /////////////////////////////////
// Kolekce všech příkladů z písemek co jsem kde našel. V první části jsou ty  //
// krátký bait příklady v druhý pak ty delší prográmky. Je možný že jsem se   //
// někde u něčeho přehlídnul nebo kdoví co. Když cokoliv najdete že je blbě   //
// tak to hlašte. Já budu nadávat ale ve skutečnosti jsem rád. Řešení jsou    //
// jenom na oko a jelikož jsem autista tak můžu některý věci dělat jak kokot. //
// A určitě jsou tam někde nějaký chyby který teď nevidim. Sorry. Ale nevěšte //
// mě hned kvůli tomu za koule do průvanu. Děkuji.                            //
////////////////////////////////////////////////////////////////////////////////
// Licence neexistuje jako žádná jiná. Klidně si to vytiskněte, nastříhejte   //
// na pásky, narolujte a dejte si to na záchod jako hajzpapír. Klidně smaž    //
// tuhle hlavičku a vydávej to za svoje ale tak abych si toho nevšimnul.      //
//                                     !!!                                    //
//   Prosba na další generace aby to tady popřípadě rozšířili o nový příklady //
//             zase pro další generace protože takhle to funguje.             //
//                                     !!!                                    //
// U těch dlouhejch příkladů zásadně doporučuju zkusit si to nejdřív napsat   //
// bez pomoci a pak se teprv podívat na řešení. Koukáním se nikdy nikdo nic   //
// nenaučil. Tak je dobrý se v tom trochu pohrabat a zkoušet co a jak se      //
// stane když to a támlecto.                                                  //
////////////////////////////////////////////////////////////////////////////////
// Mělo by to jít zkompilovat přes make. Věci co nejdou tak se nekompilujou.  //
// Moduly jsou zvlášť aby to se to tak odzkoušelo. Na test jsem udělal skript //
// run.sh kterej pustí co je potřeba.                                         //
/////////////////////////////////// Credits ////////////////////////////////////
// + Kubosh           | 19.0 příklady do roku 2019 včetně                     //
//   + Berny12        |   .1 našel nesmyslnou větu                            //
//   + Templarian     |   .2 našel chybku v DELETE_N_BITS                     //
//   + Louda          |   .3 našel chybu v ulong2str                          //
//   + Fifinas        |   .4 našel nesrovnalost u fce2                        //
//   + Wecros         |   .5 našel nesrovnalost u expr3                       //
//   + ibinek         |   .6 našel překlep                                    //
// + Fifinas          | 20.0 příklady ze zkoušky 2020                         //
//   + Fifinas        |   .1 makra do do-while()                              //
//   + Precla         |   .2 našel chybu v mac3                               //
// + human            | 21.0 priklady ze zkousky 2021 bez diakritiky          //
//   + human          |   .1 upravil nektera makra. Typecast is bad!          //
//   + human          |   .2 upravil nektere funkce pracujici s retezci       //
////////////////////////////////////////////////////////////////////////////////

#include <limits.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

//TODO napsal jsem makra, ktere podle meho nazoru udelaji ty vystupy trochu prehlednejsi.
// pokud budede neco psat, pouzivejte je pro testy.
#define passed puts(" \033[0;32mPASSED\033[0m")
#define failed puts(" \033[1;31mFAILED\033[0m")
#define test(cond)do{ if(!(cond)) failed; else passed;}while(0)

///////////////////////////////// BAIT PŘÍKLADY ////////////////////////////////
//                                                                            //

// Jaký je výsledek výrazu:
char expr1() {
    return *("ABCD" "EFGH" + 4);  // Stringy odělené mezerou se spojí do jednoho. String "vrátí" jenom ukazatel na první znak takže když k němu přičtu 4 tak ukazuju na 5. znak. Dereference mi vrátí daný znak 'E'. Btw samotnej string se uloží do .data read-only
}
                                                                                #if 0
// Jaký je výsledek výrazu:
char expr2() {
    return ("1234" + 1 + "5678")[4];  // Ukazatele nelze sčítat. Střelba do nohy zaručená
}
                                                                                #endif
// Jakou má hodnotu výraz aa[1][1]?
const int aa[3][4] = { { 1, 2, }, { 3, }, { 4, 5, 6 } };
int expr3() {
    return aa[1][1];  // Když je pole globální, nebo částečně inicializované tak se pole nuluje (pro částečně zadané se zbytek prvků donuluje) proto i zdánlivě neiinicializovaná položka bude nula. Ta čárka nemá vliv
}

// Jakou má hodnotu výraz aaa[3][1]?
int aaa[3][3] = { { 1, 2, }, { 3, }, { 4, 5, 6 } };
int expr4() {
    //return aaa[3][1];  // Zkompilovat lze protože hranice polí kompilátor nekontroluje. Je to ale samozřejmě přistupování mimo pole. Přistupuju k paměti kam bych neměl může to segfaultnout. Zkuste si to pustit hodí vám to nějaku nesmyslnou hodnotu nebo dostanete po hubě od OSka
    return 69;
}
                                                                                #if 0
// Jaký je výsledek výrazu: 
void *expr5() {
    long double i; 
    long double *p = &i;
    return ((void*)(p+1)) - ((void*)p);  // Aritmetika (odčítání) s void pointerem. Způsob jak se elegantnně střelit do nohy. GCC to umí a bere ho jako 'char *' ale je to prostě C illegal
}
                                                                                #endif
// Jakou hodnotu bude mít sum?
int swit1() {
    int sum = 10;
    for(int i = 0; i < 10; i++) {
        printf("swit1: i:%d sum:%d\n", i, sum);
        switch(i) {                              // Switch skáče na case podle toho jakou hodnotu má i. Od case se prováděj příkazy dokud nenajde break ten ukončí switch. Pokud narazí na continue tak to ovládá venkovní for a ten započne další iteraci. Ty casy lze vidět jako návěští a switch jenom jako goto na ten case. Break je akoby goto na konec switche
            case 4: case 6: case 8: sum++;       // Možnosti 4 6 a 8 vždy přičte 1 a propadávají dál dokud nenajdou break který je až u možnosti 7
            case 7: break;                       // Možnost 7 neudělá nic ale ukonční switch. Continue ovládá for takže v tomhle případě je funkce podobná jako break protože za switchem není další kód
            default: sum--; continue;            // Vše ostatní odečte 1 a skočí na další iteraci foru
        }
        printf("skip continue");
    }
    return sum;
}

// Jakou hodnotu bude mít sum?
int swit2() {
    int sum = 0;
    for(int i = 0; i < 8; i++) {
        printf("swit2: i:%d sum:%d\n", i, sum);
        switch(i) {                                 // Princip stejnej jako vejš akorát jinej výsledek
            case 1: case 3: case 5: case 7: sum--;  // Tady se sice odečte sum ale hned zase přičte dál takže se to anuluje
            default: sum++; continue;
            case 6: break;                          // Break je až tady jo takže bacha
        }
    }
    return sum;
}

// Jakou hodnotu bude mít sum?
int swit3() {
    int sum = 10;
    for(int i = 0; i < 9; i++) {
        printf("swit3: i:%d sum:%d\n", i, sum);
        switch(i) {
            case 4: case 6: case 8: sum++;       // Jakmile se jednou dostanu sem 
            case 7: break;                       // tak propadnu až sem a vyskočim
            default: sum--; continue;
        }
        break;                                   // až sem a to vyskočim komplet z cyklu
    }
    return sum;
}

// Co vrátí funkce f1?
size_t f1(float p[9][10]) {
    printf("f1: sizeof(*p)      = %ld\n", sizeof(*p));       // Po dereferenci jsem se dostal na pole 10 floatů
    printf("f1: sizeof(p[0])    = %ld\n", sizeof(p[0]));
    printf("f1: sizeof(p[0][0]) = %ld\n", sizeof(p[0][0]));  // Zde už je jenom float
    printf("f1: sizeof(float)   = %ld\n", sizeof(float));    
    printf("f1: sizeof(p)       = %ld\n", sizeof(p));        // Když je pole parametr funkce tak se "první pole" automaticky přetypuje na ukazatel. p je ve skutečnosti: 'float (*p)[10]'. U jednorozměrného pole by to bylo jenom: 'float *p'
    printf("f1: sizeof(float *) = %ld\n", sizeof(float *));
    
    return sizeof(*p);                                     // Bacha do dopovědi psát "sizeof(float) * 10" protože float může bejt různě velkej na různejch systémech atd.
    //return sizeof(p);                                      // Objevila se i tadle varianta. Odpověď "sizeof(float *)" protože je to jenom ukazatel
}

// Jakou hodnotu vrátí funkce f2()?
int f2(void) {
    char str[10] = "ABCD";          // Pole 10 charů {'A', 'B', 'C', 'D', \0, ...bordel}
    char *s[10] = { str, "EFGH" };  // Pole 10 ukazatelů na char. Nultej prvek je ukazatel na první znak v str 'A' (pole bez závorek je ukazatel na první prvek). První ukazuje na první znak 'E' stringu kterej se uloží do .data readonly
    strcat( *s + 2, "1234" );       // *s přitupuje v nultýmu ukazateli. Spojení "CD" a "1234" protože (*s + 2) ukazuje na 'C' "AB" se jakoby ignoruje "1234" se prostě přidá za "CD". V str je nyní {'A', 'B', 'C', 'D', '1', '2', '3', '4, \0, ...bordel}
    return (*s)[3];                 // *s je str a 4. znak v str je 'D'
}

// Jakou hodnotu vrátí funkce f3()?
int f3(void) {
    static char str[10] = "ABCD";   // Statické pole 10 znaků. Víckrát se funkce nevolá takže je mi jedno že to je static
    char *s[10] = { str, "EFGH" };  // To stejný jako vejš 
    strcpy((*s) + 2, "1234");       // Od znaku 'C' se nakopíruje "1234". Závorka která je vcelku zbytečná * má větší prioritu než sčítání. V str je nyní {'A', 'B', '1', '2', '3', '4, \0, ...bordel}
    return ( (*s)++ )[5];           // Nejprve dereference s a mam str což je vlastně ukazatel na 'A'. Přičtu 1 ale vrátim furt ukazatel na 'A' protože postfix ++. Přičtu 5 a provedu dereferenci (tak funguje [5]) takže dostanu '4'
}

// Jakou hodnotu vrátí funkce f4(3)?
char f4(int x) {
    static char *s = "ABCDEFGH";           // Ukazatel na string v .data readonly. Že je statický je mi zase jedno
    const char (*p)[3] = (void *)(s + x);  // s mě ukazuje na 'A' posunu se o 3 a mam ukazatel na 'D'. Přetypuju ho na void pointer a ten uložím jako ukazatele na tříprvkové pole konstatních charů. Což se dá to je prostě přetypování ukazatele
    return * (const char *)(p + 1);        // Jelikož je p ukazatel na tří prvkové pole tak se skáče po třech znacích při přitení 1 (po kolika se skáče určuje právě typ ukazatele). Nyní ukazuju na 'G'. Je nutný přetypování na ukazatel na char jinak by mi jedna derefernce vrátila jenom pole a byla by potřeba ještě jedna dereference (Ukazatel na pole je jakoby ukazatel na ukazatel). Dereference a mam 'G'
    //return **(p + 1);                      // Funguje stejně
}

// Jakou hodnotu vrátí funkce f5(4)?
static int f5(int i) {
    static char pole[] = "ABCDEF";   // Pole charů že je statický je mi jedno protože se funcke nevolá vícekrát. Pole je velký 7 znaků (\0 se počítá taky)
    char *p1 = pole + sizeof(pole);  // Ukazatel p1 mi bude ukazovat za poslední znak v poli (\0) kde je nějakej bordel. Aneb posunu se o 7 od prvního znaku
    char **p2 = &p1;                 // Ukazatel p2 mi ukazuje na ukazatel p1 a už sme všichni v prdeli že
    (*p2) -= i;                      // Dereference p2 takže pracuju s p1 vrátim se o 4 znaky zpátky takže na 'D'
    return **p2;                     // Dvojitá dereference je znak 'D'
}

// Jakou hodnotu vrátí funkce f8()?
int f6(void) {
    char p[10][10] = { "ABC", "DEF", };  // Pole polí charů. Pohoda
    return * p[1];                       // Přistoupim k druhýmu prvku což je ukazatel na 'D'. Dereferencuju a mam znak 'D'
}

// Jakou hodnotu vrátí funkce f6()?
char f7(void) {
    char *s[] = { "1234", "5678", "ABCD", };  // Pole ukazatelů na chary. Stringy jsou v .data readonly 
    return s[2]++ , * ( ++ s[2] );            // Čárka zřetězí příkazy takže se provede nejdřív ten před a pak po čárce. Nejprve se třetí ukazatel zvětší o 1 a nyní již ukazuje na 'B'. Pak se znovu zvětší o 1 a zvětšená hodnota se i vrátí protože prefix ++. Dereference což je znak 'C'. (return vrátí hodnotu toho co je nejvíc napravo odělený čárkou)
}

// Jakou hodnotu vrátí funkce f7()?
char f8(void) {
    const char *s[] = { "012", "345", "678", };  // Pole ukazatelů na konstantní chary. Stringy jsou v .data readonly
    return * ++ (*s);                            // Nejprve se provede dereference z pole a získám nultej prvek a mam ukazatel na '0'. Přičtu jedna a ukazatel mi už ukazuje na '1' prefix ++ takže se mi zvětšený ukazatel i vrátí. Další dereference a dostanu znak '1'
}

// Jakou hodnotu vrátí funkce f9()?
char f9(void) {
    const char *s[] = { "0123", "4567", "89AB", };  // Pole ukazatelů na chary. Stringy jsou v .data readonly
    return s[2]++ , * ( * (s+2) + 1 );              // Stejná siuace s čárkou. Nejprve se posune ukazatel posledního stringu na '9'. Dereference má přednost před sčítátím. *(s+2) je jako s[2] v posledním stringu se posunu o další jeden znak a znova dereference což mi dá 'A'
}

// Jakou hodnotu vrátí funkce f10()?
char f10(void) {
    const char *s[] = { "0123", "4567", "89xy", };  // Pole ukazatelů na chary. Stringy jsou v .data readonly
    return * ++ (s[2]);                             // Nejprve přistoupm k poslednímu ukazateli pak se k němu přičte 1 a přičtený se i vrátí k dereferenci a vrátí '9'
}

// Jakou hodnotu vrátí funkce f()?
char f11(void) {
    const char *s[7] = { "0123456", "ABCDEF", "6543210", };  // Pole ukazatelů na chary. Stringy jsou v .data readonly
    return * (s[1]++ + 2);                                 // [1]++ má přednost před sčítáním. Přistoupim k druhým ukazateli na string a přičtu k němu 1 ale vrátí se původní hodnota (postfix ++). Nyní přičtu 2 takže se posunu na 'C'. Nyní mam ukazatel na 'C'. Dereference a mam 'C'
}
                                                                                #if 0
// Jakou hodnotu vrátí funkce f12()?
char f12(void) {
    char p[10] = "ABC";
    char *s[5] = {p, "CDEF"};
    strcpy(*s + 2, "123"); // upravuji 1. retezec v poli s, takze vznika "AB123", 2. retezec je nezmenen
    return *(*s++);        // Na zaklade precedence ma ++ prednost pred *, takze se to chova jako  *(*(s++)).
                           // s je pole ukazatelu na char, tedy provadime pole++, coz nejde -> chyba pri prekladu
}
                                                                                #endif
// Jakou hodnotu vrátí funkce f13()?
int f13(int *p[2][3][4]) {
    printf("f13: 3 * 4 * sizeof(int *) = %ld\n", 3 * 4 * sizeof(int *));

    return sizeof(*p); // p je pole v parametru funkce, tj. C to vnejsi pole predela na pointer, dostavame
                       // int *(*p)[3][4]. Dereference, dostavame pole poli int *. Takze velikost bude
                       // 3 * 4 * sizeof(int *)
}

// Co vrátí funkce main1?
static int g1(int i) {
    static int s1 = 10;  // Inicializace se provede jenom jednou pak je s1 jakoby globální
    int a = s1 + 3;      // Do a se uloží aktuální s1 + 3
    s1 -= i;             // Od s1 se odečte i a bacha fakt je s1 globální teď už. Po skončení funkce v s1 zůstane hodnota
    return a;
}
int main1(void) {
    g1(1);               // Po provedení funkce je v s1 9 a funkce vrátí 13
    return g1(2);        // Po provedení funkce je v s1 7 a funkce vrátí 12
}

// Co vrátí funkce main1?
static int g2(int i) {
    static int s2 = 4;  // Inicializace se provede jenom jednou pak je s2 zase jakoby globální
    int a = s2 + 3;     // Do a se uloží aktuální s2 + 3
    s2 -= i;            // Stejný jako g1
    return a;
}
int main2(void) {
    g2(2);              // Po provedení funkce je v s2 2 a funkce vrátí 7
    return g2(1);       // Po provedení funkce je v s2 1 a funkce vrátí 5
}

//                                                                            //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////// SHORT SHITS /////////////////////////////////
//                                                                            //

// 1) Napište:
// a) Deklaraci funkce AllocMatrix_double3x3 bez parametrů s návratovým 
//    typem "ukazatel na první řádek dvojrozměrného pole čísel" (rozměry a 
//    typ čísel viz jméno funkce).
double (*AllocMatrix_double3x3())[3];  // bez typedef
//typedef double (*mat_ret1)[3];       // s typedef
//mat_ret1 AllocMatrix_double3x3();

// b) Definici výše uvedené funkce takto: funkce dynamicky alokuje a 
//    NULUJE dvojrozměrné pole čísel o zadaném rozměru a vrací ukazatel na 
//    toto pole (POZOR NA TYP - viz výše), nebo NULL pokud alokace selže.
double (*AllocMatrix_double3x3())[3] {  // mat_ret1 AllocMatrix_double3x3() {
    return calloc(3*3, sizeof(double));
}

// c) Příklad volání této funkce: výsledek uložte do vámi správně definované 
//    proměnné a poslední prvek nastavte na 1.
void shrshi1() {                    // Pomocná funkce abych to nemusel psát do mainu
    double (*mat)[3];               // mat_ret1 mat;
    mat = AllocMatrix_double3x3();
    if(mat != NULL) {
        mat[2][2] = 1;
    }

    // Toto je už mimo zadání, jenom pro ukázku že to lítá
    if(mat != NULL) {
        for(int y = 0; y < 3; y++) {
            for(int x = 0; x < 3; x++) {
                printf("%.1f ", mat[x][y]);
            }
            printf("\n");
        }
        free(mat);
    }
}

// 2) Napište:
// a) Deklaraci funkce AllocIntMatrix100x100 bez parametrů vracející ukazatel
//    na dvojrozměrné pole čísel (rozměry a typ čísel viz jméno funkce).
int (*AllocIntMatrix100x100())[100][100];  // bez typedef
//typedef int (*mat_ret2)[100][100];       // s typedef
//mat_ret2 AllocIntMatrix100x100();

// b) Definujte tuto funkci: funkce dynamicky alokuje a nuluje dvojrozměrné 
//    pole čísel o zadaném rozměru a vrací ukazatel na toto pole
//    (pozor na typ), nebo NULL pokud alokace selže.
int (*AllocIntMatrix100x100())[100][100] {  // mat_ret2 AllocIntMatrix100x100() {
    int (*ptr)[100][100];                   // mat_ret2 ptr = NULL;
    ptr = calloc(100*100, sizeof(int));
    return ptr;
}

// c) Napište příklad volání této funkce, výsledek uložte do vámi správně
//    definované proměnné.
void shrshi2() {                    // Pomocná funkce abych to nemusel psát do mainu
    int (*mat)[100][100];           // mat_ret2 mat;
    mat = AllocIntMatrix100x100();

    // Toto je už mimo zadání 
    if(mat != NULL) {
        free(mat);
    }
}

// 3) 
// a) Definujte inline funkci AllocMAT1(size_t N), která dynamicky alokuje
//    dvojrozměrné pole (matici) čísel int o rozměru N*N a toto pole
//    inicializuje jako jednotkovou matici (1 na diagonále). Funkce vrací 
//    ukazatel na celé pole, nebo NULL pokud alokace selže.
extern void *AllocMAT1(size_t N);                 // Externí definice pro případ že se nepodaří inlinování aby se měla funkce kam dát
inline void *AllocMAT1(size_t N) {                // N je parametr takže nemůžu vrace konkrétní ukazatel třeba na pole [5][5]. Funkce musí bejt univerzální. 'void *' je na to ideálka protože si ho musim přetypovat abych pak moh pracovat dál když si zavolám někde tu funkci
    int (*ptr)[N][N] = calloc(N*N, sizeof(int));  // Uvnitř můžu mít konktrétní ukazatel a taky ho potřebuju abych mohl inicializovat tu jednotkovou matici

    if(ptr != NULL) {
        for(size_t i = 0; i < N; i++) {
            (*ptr)[i][i] = 1;                     // Nejdřív se dereferencuje ten ukazatel abych se dostal k poli
        }
    }

    return (void *)ptr;                           // Nakonec ho vrátim jako 'void *'. Ten kdo tu funkci volal ví jak snim pracovat a na co ho přetypovat protože funkci zadal daný N
}

// b) Napište příklad volání funkce a otestujte hodnotu prvku [0][0].
void shrshi3() {                      // Pomocná funkce abych to nemusel psát do mainu
    size_t N = 5;

    int (*mat)[N][N] = AllocMAT1(N);  // Tady vim kolik je N takže vim na co si 'void *' přetypovat
    if(mat != NULL) {
        if((*mat)[0][0] == 1) {
            printf("AllocMAT1 ok\n");
        } else {
            printf("AllocMAT1 err\n");
        }
    }

    // Toto je zase mimo zadání jenom hezky na otestování
    if(mat != NULL) {
        for(size_t y = 0 ; y < N; y++) {
            for(size_t x = 0 ; x < N; x++) {
                printf("%d ", (*mat)[x][y]);
            }
            printf("\n");
        }
        free(mat);
    }
}

// 4) Napište deklaraci funkce F s paramatrem P typu dvojrozměrné pole znaků
//    typu char, vracející ukazatel na pole čísel short.
short (*F(char P[][5]))[5];  // Velikost 5 je prostě nějaká vymyšlená ale musí tama bejt. jenom [] by se nezkompilovalo. Krom prvních [] u parametru funkce ty můžou bejt prázdný jako jediný

// 5) Napište deklaraci funkce typu void s parametrem typu pole ukazatelů na int.
void fce1(int *p[]);

// 6) Napište deklaraci funkce bez parametrů vracející pole ukazatelů na char.
char **fce2(void);  // Nemůžu napsat 'char *fce2(void)[5];' protože pole nemůže být navratový typ. Takže se tam musí loupnout asi takhle "ukazatel na první prvek" protože to funguje stejně jako pole. Nevidim jinou klounou cestu ako to urobiť. 
                    // Možná by šlo napsat že to prostě nejde udělat protože pole nelze vrátit. Lze ho ale nahradit ukazatelem který se chová podobně.
                    // Takže doslova nelze zadání splnit a lze to udělat jinak aby se to chovalos stejně.

// 7) 
// a) Definujte 2 struktury S1 a S2:
//      S1 obsahuje položku typu long a ukazatel ukS2 na S2,
//      S2 obsahuje položku typu char a ukazatel ukS1 na S1.
//struct S2;            // Nejdřív si musim deklarovat že vůbec něco jako S2 exituje abych v S1 na to moh ukazovat. Můžu ale bez obsahu je to jenom deklarace definice je potom. Jede to i bez deklarace struktury S2
struct S1 {
    long x;
    struct S2 *ukS2;
};
struct S2 {
    char x;
    struct S1 *ukS1;
};

// b) Definujte 2 globální proměnné: a typu struktura S1, b typu strutkura S2
//    a _inicializujte_ je tak, aby na sebe navzájem ukazovaly
//    (přes položky ukS1, ukS2).
extern struct S2 b;          // Řeknu kompilátoru že někde bude struct b abych
struct S1 a = {.ukS2 = &b};  // tady moh použít její adresu až jí kompilátor najde
struct S2 b = {.ukS1 = &a};  // zde

//                                                                            //
////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////// MAKRA ////////////////////////////////////
//                                                                            //

// !!!
// Makra vždy obalovat do do-while(0), i když je v zadání napsáno že se nesmí
// používat cyklus
// !!!

//pomocne makro, ktere budete moci napsat na zkousce, abyste zzbytecne nepsali tuto zdlouhavou sracku
#define BITS(x) sizeof(x)*CHAR_BIT

// 1) Definujte makro ASSIGN_BITFIELD(x, pos, n, val), které v L-hodnotě x
//    libovolného celočíselného typu nastaví zadaných n bitů od bitové pozice
//    pos na hodnotu val (Pozor: val obsahuje n-bitovou hodnotu). ZKONTROLUJTE
//    správnost hodnot všech parametrů pomocí assert. Pozice číslujte od 0 
//    (od LSB). Musíte použít CHAR_BIT. POZOR: Nesmíte změnit hodnoty pos, n,
//    val a nesmíte použít cyklus.
//    Příklad: (int32_t): pos=12, n=12, val=0xF0 0xabXXXcde -> 0xab0F0cde
//    Napište příklad správneho použítí makra.
//

// kubeshi, promin, ze jsem vymazal tvoje makro. Tady mate non oznuk reseni.
#define ASSIGN_BITFIELD(x, pos, n, val)do{\
    assert((val) <= ((1ull << (n))-1));/*1. "Pozor, val obsashuje n-bitovou hodnotu", coz znamena, ze maximalni hodnota, kterou muze nabyvat val je 1111...111 nkrat*/\
    assert((pos) >= 0 && (n) >= 0);\
    (x) = (x) & ~(((1ull << (n))-1) << (pos)) /*vinulujeme okinko pro val*/\
          |\
          ((val) << (pos)) & (((1ull << (n))-1) << (pos));/*posuneme val, aby jeho LSB zacinal od pozice pos a vynuluje vsechny ostatni bity, */\
                                                          /*protoze val muze byt zaporne cislo a posun vlevo u signed neni definovany*/\
} while(0)
    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //     hodnoty                                                    operace                  
    // --------------------------------------------------------------------------------------------------------
    //  0x0000000000000001                                    1ull 
    //  0x0000000001000000                                    ((1ull << (n)) 
    //  0x0000000000ffffff                                    ((1ull << (n))-1) 
    //  0x00000ffffff00000                                    ((1ull << (n))-1) << (pos) 
    //  0xfffff000000fffff                                    ~(((1ull << (n))-1) << (pos))   
    //  perfect bitmask is done :) 



// cau, human is here. jako dodatek sem upridam makro, ktere udela totez, co i ASSIGN_BITFIELD, ale v pripade, kdyz
// n je zaporne cislo, bude vkladat val napravo od pos. Princip je stejny
// Princip a postup:
//
// ((1ull << (n))-1) << (pos). Pravdepodobne budete z toho zmateni, ale ve skutecnosti to neni tak slozite. At to rozebereme!
// 1)    necht mame pouze 8 bitu, n je 3, pos je 2
// 2)    na zacatku posuneme 1ull, coz je 0b00000001 o n bitu doleva. Dostaneme 0b00001000.  (1ull << (n))
// 3)    odecteme 1, dostaneme 0b00000111                                                    (1ull << (n))-1 
// 4)    posuneme toto vsechno o pos doprava, coz nam da 0b00011100                          ((1ull << (n))-1) << (pos)
// P.S. kdyz toto znegujeme pomoci ~, dostaneme 0b11100011, coz je take docela krasna a uzitecna maska, ze jo?
// P.P.S. nejsem si jisty ohledne kuboshova reseni, nebot pouziva typecasty v makrech, coz neni dobre... I kdyz kubosh ma kratsi... myslim makro.
#define ASSIGN_BITFIELD_ULTIMATE(x,pos,n,val)do{\
    assert((n) && (pos) >= 0);\
    assert((n)+(pos) <= sizeof(x)*CHAR_BIT);\
    (x) = (n>0)\
          ?\
              ((x)              & ~(((1ull << (n))-1) << (pos))) /*vynulujeme "policko" pro bity, ktere budeme vkladat*/\
              | /*Chceme sjednotit cislo s vynulovanym polickem a udelame to pomoci or */\
              (((val) << (pos)) &  (((1ull << (n))-1) << (pos)))/*posunu val a vynuluji vsechno ostatni krome val pro jistotu*/\
          :\
          (\
              assert((pos)+(n) >= 0),/*here's mister operator carka*/\
              ((x)                    & ~(((1ull << -(n))-1) << ((pos)+(n))))\
              |\
              (((val) << ((pos)+(n))) &  (((1ull << -(n))-1) << ((pos)+(n))))\
          );\
}while(0)


void mac1() {
    int32_t bitA = 0xbadffcde;
    int64_t bitB = 0x0feeffffefffffff;
    
    printf("%x -> ", bitA);
    ASSIGN_BITFIELD(bitA, 8, 12, 0xba);
    printf("%x  ", bitA);
    test(bitA==(int32_t)0xbad0bade);

    printf("%llx -> ", bitB);
    ASSIGN_BITFIELD(bitB, 32, 16,(uint64_t) 0xdbab);
    printf("%llx  ", bitB);
    test(bitB==(int64_t)0xfeedbabefffffff);

    bitA = 0xbadffcde;
    bitB = 0x0feeffffefffffff;
    printf("%x -> ", bitA);
    ASSIGN_BITFIELD_ULTIMATE(bitA, 8+12, -12, 0xba);
    printf("%x\n", bitA);

    printf("%llx -> ", bitB);
    ASSIGN_BITFIELD_ULTIMATE(bitB, 32+16, -16,(uint64_t) 0xcdbab);
    printf("%llx  ", bitB);
    test(bitB==(int64_t)0xfeedbabefffffff);
}

// 2) Definujte makro ROT_BITS_LEFT(x, n), které v L-hodnotě x typu int 
//    rotuje bity o n pozic doleva (ty které "vypadnou" se vrací na druhé 
//    straně). Před provedením operace zajistěte, aby hodnota n nepřesáhla
//    počet bitů v x. Můžete předpokládat že CHAR_BIT = 8. POZOR: Nesmíte
//    změnit hodnotu n a nesmíte pužít cyklus.
//    Napište příklad správného použití makra.
//

// problemem reseni od kubose spociva v tom, ze ono funguje ne se vsemi datovymi typy
// type casting na unsigned is not a good idea, protoze urcite selze v pripade long long cisel, ktere maji hodnotu nad 
// 2^32-1.
// 
//      rozebereme moje reseni na priklade x = 0xccaabbbb a n = 8
//      1. krok: posunu cislo o n bitu vlevo a vynuluji n bitu zprava, protoze tam se muze objevit nejaky junk a to urcite nechceme, ze ano?
//            dostanu     0xaabbbb00
//      2. krok: posunu cislo o (pocet bitu v cisle)-n vpravo a vynuluji levou cast,
//            dostanu     0x000000cc
//      3. krok: sjednotim tyto 2 cisla pomoci operace bitwise or |
//            dostanu     0xaabbbbcc
//      4. krok: pujdu brcet, protoze jsem nedostal A z tohoto predmetu
#define ROT_BITS_LEFT(x, n)do{\
    assert((n) >= 0 && (n) < BITS(x));\
    (x) = (((x) << (n))           & ~((1ull << (n))-1))\
          |\
          (((x) >> (BITS(x)-(n))) &  ((1ull << (n))-1));\
}while(0)

// postup je stejny, jako ten vyse, jenom se musi zmenit poradi rotace. 
//       (1ull << (sizeof(x)*CHAR_BIT-(n)))-1     <- co to je za strasna sracka?
//       odpovidam: 1) vezmu si 1ull, coz je 0b000...0001. Kvuli tomu, ze tam je 64 pilicka, nebojim se, ze mi neco pretece
//                  2) posunu o pocet bitu v x minus n. Napr pro sizeof(x) == 4 a pro n == 8 budu posouvat o 32-8 = 24
//                  3) dostanu cislo, ktere na pozici 25 pocinajic LSB ma 1, vsude jinde jsou 0
//                  4) odectu od tohoto cisla 1, coz mi da 0b00..0111..111 . Hele pockat, to je maska. Bylo to velmi jednoduche, ze?
//                  9) pujdu brcet, protoze... viz vyse. POZOR na zavorky. Davejte je vsude, kde je potreba, protoze n muze byt treba vyraz
//                     a nechcete kvuli zavorkam dostat oznuk, ze jo? Navic POZOR^2 na to, ze operatory << a >> maji velmi nizkou precedanci
//                     (to znamena, ze se vyhodnoti jako posledni) a proto je MUSITE davat do zavorek. 
#define ROT_BITS_RIGHT(x,n)do{\
    assert((n) >= 0 && (n) < sizeof(x)*CHAR_BIT);\
    (x) = (((x) >> (n))           &  ((1ull << (BITS(x)-(n)))-1))\
          |\
          (((x) << (BITS(x)-(n))) & ~((1ull << (BITS(x)-(n)))-1));\
}while(0)

// kuboshove makro se mi nelibi, jelikoz provadi pretypovani, coz znamena, ze neni univezalni. Avsak ho necham, abyste se podivali na tuto krasnou tabulku,
// i kdyz bych tipnul, ze neni zcela spravna
                                    #if 0
#define ROT_BITS_LEFT(x, n) \
    do { \
        assert(n >= 0); \
        assert(n < sizeof(x) * 8); \
        x = ((unsigned)x << n)  |  ((unsigned)x >> ((sizeof(x) * 8) - n)); \
    } while(0)
    //  ~~~~~~~~~~~~~~~~~~     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //    posunutý bity                   přetečený bity
    // ---------------------------------------------------------------
    // Např. x=1100 1010, n=2  Kdyby se pracovalo s bytem normálně to bude int, byte je jenom jako ukázka)
    // x << n -> 0010 1000     sizeof(x) * 8             ->         8
    //                         (sizeof(x) * 8) - n       ->         6
    //                         x >> (sizeof(x) * 8) - n  -> 0000 0011
    //
    //            (x << n)  |  (x >> (sizeof(x)*8) - n)  -> 0010 1011

    // Zase bacha že jakýkoliv posuny nad číselem se znamínkem se nedělajó. Stačí přetypovat na unsigend (unsigned = unsigned int) a je to cajk, hope so
// Na ukázku i posun doprava aby se neřeklo. Posuny jsou jenom obráceně
#define ROT_BITS_RIGHT(x, n) \
    do { \
        assert(n >= 0); \
        assert(n < sizeof(x) * 8); \
        x = ((unsigned)x >> n)  |  ((unsigned)x << ((sizeof(x) * 8) - n)); \
    } while(0)
                                    #endif
    
void mac2() {
    int bitA = 0xee02c0ff;
    int bitB = 0xcefacefa;

    printf("%08x -> ", bitA);
    ROT_BITS_LEFT(bitA, 16);
    printf("%08x  ", bitA);
    test(bitA==(int)0xc0ffee02); 

    printf("%08x -> ", bitB);
    ROT_BITS_RIGHT(bitB, 8);
    printf("%08x  ", bitB);
    test(bitB==(int)0xfaceface); 
}

// 3) Definujte makro DELETE_N_BITS(x, pos, n), které v L-hodnotě x typu 
//    signed int "zruší" n bitů od libvolné bitové pozice pos. Do horních 
//    bitů x se šíří znaménkový bit. Pozice číslujte od nuly (od LSB).
//    Například (32 bit): pos=8, n=12  0xabcNNNde -> 0xFFFabcde
//    Zkotrolujte správnost hodnot parametrů pos, n pomocí assert. POZOR: 
//    Nesmíte změnit hodnoty pos, n a nesmíte použít cyklus.
//    Musíte použít CHAR_BIT.
//
//vysvetleni tohoto makra viz obrazek na discordu: //TODO napsat vysvetleni
#define DELETE_N_BITS(x, pos, n)do{\
    assert((pos) >= 0 && (n) > 0); \
    assert((pos) + (n) < BITS(x)); \
    (x) =   (((x) >> (n)) & (((1ull << (BITS(x)-(pos)-(n)))-1)<<(pos)))\
          | ((x)          & ~(~0ull << (pos))) \
          | (((x) < 0) ? (~0ull << (BITS(x)-(n))) : 0ull);/*pro zaporna cisla pridame na n MSB pozic jednicky*/\
} while(0)

void mac3() {
    int bitA = 0xcac123a0;
    int bitB = 0x7da12dff;
    int bitC = 0x9abcffde;
    int bitD = 0xaaaaaaff;

    printf("%08x -> ", bitA);
    DELETE_N_BITS(bitA, 8, 12);
    printf("%08x  ", bitA);
    test(bitA==(int)0xfffcaca0);

    printf("%08x -> ", bitB);
    DELETE_N_BITS(bitB, 12, 8);
    printf("%08x  ", bitB);
    test(bitB==(int)0x007dadff);

    printf("%08x -> ", bitC);
    DELETE_N_BITS(bitC, 8, 8);
    printf("%08x  ", bitC);
    test(bitC==(int)0xff9abcde);

    printf("%08x -> ", bitD);
    DELETE_N_BITS(bitD, 0, 8);
    printf("%08x  ", bitD);
    test(bitD==(int)0xffaaaaaa);
}

#if 0
// Pořád 3), ale jednodušší řešení:
#define DELETE_N_BITS(x, pos, n)do{\
    assert((pos) >= 0 && (n) > 0); \
    assert((pos) + (n) < (sizeof(x)*CHAR_BIT)); \
    x = ((x >> n) & (~0ull << pos)) | (x & ((1ull << pos) - 1)); \
} while(0)
// Využíváme toho, že nám zaručují SIGNED int, z ISU můžete vědět,
// že při shiftu doprava u SIGNED čísla se používá instrukce SAR,
// která zachovává znaménko čísla.

//  ----------------------------------------------------------------
//          počáteční hodnota x                 0b 10011001
//          pos                                 3
//          n                                   2
//  ----------------------------------------------------------------
//          (x >> n)                            0b 11100110 (automaticky se doplní)
//          (~0ull << pos)                      0b 11111000 (u shift left to neplatí samozřejmě)
//  A:      (x >> n) & (~0ull << pos)           0b 11100000
//
//          x                                   0b 10011001
//          ((1ull << pos) - 1)                 0b 00000111
//  B:      x & ((1ull << pos) - 1)             0b 00000001
//      
//          A | B                               0b 11100001  
#endif




// 4) Definujte makro NBIT_INSERT(x, Pos, n, y), které v L-hodnotě x 
//    libovolného celočíselného typu posune bity na pozicích vyšších než Pos
//    tak, aby vzniklo místo pro n nejméně významných bitů z y, které budou 
//    vloženy na pozici Pos. Pozice bitů číslujte od LSB.
//    Příklad: x=0x12345678, Pos=4, n=12, y=0xCDEF -> 0x4567DEF8
//    Zkontrolujte správnost hodnot paramaterů Pos, n pomocí assert.
//    POZOR: NEsmíte použít cyklus ani změnit hodnoty Pos, n a y.
//    Napište _příklad_ správného použití makra.
//
#define NBIT_INSERT(x, Pos, n, y) \
    do { \
        assert(Pos >= 0 && n > 0); \
        assert(Pos < sizeof(x) * CHAR_BIT && n < sizeof(x) * CHAR_BIT); \
        x = (~((unsigned long long)(~0) << Pos) & x)  |  ((~((unsigned long long)(~0) << n) & y) << Pos)  |  ((((unsigned long long)(~0) << Pos) & x) << n); \
    } while(0)
    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //          bity napravo co se nemění                              vkládané bity                          bity co se posunou aby se uvolnilo místo
    // -------------------------------------------------------------------------------------------------------------------------------------------------
    // Např. x=1001 1010, Pos=2, n=3, y=0000 0101 
    // ~0                           -> 1111 1111     ~0                                 -> 1111 1111     ~0                                -> 1111 1111
    // ~0 << Pos                    -> 1111 1100     ~0 << n                            -> 1111 1000     ~0 << Pos                         -> 1111 1100
    // ~(~0 << Pos)                 -> 0000 0011     ~(~0 << n)                         -> 0000 0111     (~0 << Pos) & x                   -> 1001 1000
    // ~(~0 << Pos) & x             -> 0000 0010     ~(~0 << n) & y                     -> 0000 0101     ((~0 << Pos) & x) << n            -> 1100 0000
    //                                                   (~(~0 << n) & y) << Pos            -> 0001 0100
    //
    //                       (~(~0 << Pos) & x )  |            ((~(~0 << n) & y) << Pos)              |  (((~0 << Pos) & x) << n)          -> 1101 0110
void mac4() {
    int32_t bitA = 0xacdcacee;
    int64_t bitB = 0xfffffffff123abcd;

    printf("%08x -> ", bitA);
    NBIT_INSERT(bitA, 12, 8, 0xfe);
    printf("%08x\n", bitA);

    printf("%0llx -> ", bitB);
    NBIT_INSERT(bitB, 16, 24, 0x456789);
    printf("%llx\n", bitB);
}

//                                                                            //
////////////////////////////////////////////////////////////////////////////////

////////////////////////// FUCKIN LONG MTHRFCKR SHITS //////////////////////////
//                                                                            //

// 1) Napište funkci
//
//       bool ulong2str(unsigned long x, int r, char *s, int n)
//
//    která převede číslo x typu unsigned long na řetězec s. Základ použité 
//    číselné soustavy je r. Použijte assert na kontrolu rozsahu základu 
//    (od 2 do 36). Výstup může obsahovat znaky z množiny [0-9A-Z]. 
//    Předpokládáme, že pole s má velikost n znaků. Pokud délka výsledku
//    přesáhne maximum, vrací funkce hodnotu false a obsah pole má  
//    nedefinovanou hodnotu. Jinak funkce vrací true a správnou hodnotu v 
//    řetězci s. Pozor na x==0.
//
//    Nepoužívejte žádné standartní funkce kromě assert (jinak 0b).
//
//    Napište PŘÍKLAD volání této funkce s vhodně zvolenými argumenty (včetne
//    jejich deklarací/definic)
//
char char_from_number(int i) {
    if(i < 10) {
        return '0' + i;
    } else {
        return 'A' + (i - 10);
    }
}
bool ulong2str(unsigned long x, int r, char *s, int n) {
    assert(r >= 2 && r <= 36);
    if(s == NULL || n < 2) {
        return false;
    }

    char temp[n];      // Dočasné pole pro uložení znaků které jsou ale pozpátku 
    int ch_count = 0;  // Počet znaků bez \0
    temp[0] = '\0';    // \0 musí bejt nakoci výslednýho pole -> na začátku toho dočasnýho

    // Pro případ x==0
    if(x == 0) {
        temp[1] = '0';
        ch_count = 1;
    } else {
        // Postupný dělení a ukládání si znaků
        for(ch_count = 0; (ch_count < (n - 1)) && (x != 0); ch_count++) {
            temp[1 + ch_count] = char_from_number(x % r); // Převody mezi soustavama to snad každej ví jak lítá
            x = x / r;
        }
        // Pokud jsem nedodělil do nuly nevešel jsem se
        if(x != 0) {
            return false;
        }
    }    

    // Reverznutí pole
    for(int i = 0; i < ch_count + 1; i++) {
        s[i] = temp[ch_count - i];
    }
    return true;
}
void mthrfckr1() {
    char buffer[100];
    if(ulong2str(255, 16, buffer, 100)) {
        printf("%s\n", buffer);
    } else {
        printf("ovf\n");
    }
    if(ulong2str(5, 2, buffer, 100)) {
        printf("%s\n", buffer);
    } else {
        printf("ovf\n");
    }
    if(ulong2str(255, 2, buffer, 100)) {
        printf("%s\n", buffer);
    } else {
        printf("ovf\n");
    }
    if(ulong2str(255, 2, buffer, 5)) {
        printf("%s\n", buffer);
    } else {
        printf("ovf\n");
    }
}

// 2) Napište program SORTCHECK, který čte ze zadaného souboru (první
//    argument programu) slova a kontroluje zda vyhovují vzestupnému 
//    uspořádání (každé následující slovo je větší nebo rovno předchozímu).
//    Není-li soubor zadán, čte stdin. Program vrací exit kód nula, pokud
//    uspořádání vyhovuje (nebo je prázdný soubor), jinak vrací 1.
//
//    Pro čtení slova ze souboru musíte napsat funkci 
//      
//       int ReadWord(char *s, unsigned m, FILE *f)
//
//    která přeskočí odělovače a načte slovo ze souboru f do řetězce s, kam
//    uloží maximálně m bajtů. Pokud je slovo delší, hlásí chybu na stderr a 
//    _ukončí_ program. Nesmíte použít fscanf(). Funkce vrací délku slova
//    nebo EOF, když narazí na konec souboru.
//
//   Pro porovnání obsahu řetězců použijte standartní funkci
//       int strcmp(const char *s1, const char *s2);
//
#define WORD_LENGTH 128
int ReadWord(char *s, unsigned m, FILE *f) {
    if(s == NULL || f == NULL) {
        return 0;
    }

    unsigned word_length = 0;
    int loaded_char;

    // Přeskočení bílých znaků
    while(isspace(loaded_char = fgetc(f)) && loaded_char != EOF);
    if(loaded_char == EOF) {
        return EOF;
    }

    // Načtení znaků
    do {
        if(loaded_char == EOF) {
            s[word_length] = '\0';
            return EOF;
        }
        if(word_length >= m - 1) {
            fprintf(stderr, "Přetečení bufferu\n");
            exit(1);
        }

        s[word_length] = loaded_char;
        word_length++;
    } while(!isspace(loaded_char = fgetc(f)));

    s[word_length] = '\0';
    return word_length;
}
int mthrfckr2(int argc, char *argv[]) {  // Tohle je jakoby main
    FILE *file = stdin;
    if(argc >= 2) {
        file = fopen(argv[1], "r");
    }
    if(file == NULL) {
        return 1;
    }

    char buffer_old[WORD_LENGTH];
    char buffer_new[WORD_LENGTH];
    int read_return;
    if(ReadWord(buffer_old, WORD_LENGTH, file) == EOF) {
        if(argc >= 2) {
            fclose(file);
        }
        return 0;
    }
    do {
        read_return = ReadWord(buffer_new, WORD_LENGTH, file);
        if(strcmp(buffer_new, buffer_old) < 0) {
            if(argc >= 2) {
                fclose(file);
            }
            return 1;
        }
        strcpy(buffer_old, buffer_new);
    } while(read_return != EOF);

    if(argc >= 2) {
        fclose(file);
    }
    return 0;
}

// 3) Napište funkci
//       
//       int SearchReplace(char *Str, int Max, const char *s1, const char *s2);
//    
//    která v řetězci Str zamění všechny výskyty podřetězce s1 za obsah s2.
//    Funkce vrací počet úspěšných záměn. Když s2 obsahuje s1 funkce končí.
//    Předpokládáme, že Str může obsahovat Max bajtů a pokud by měl výsledek 
//    překročit tuto mez, funkce další záměny neprovádí a vrátí záporné číslo
//    udávající počet provedených záměn.
//    (Například: Str="STRING", Max=9, s1="ST", s1="", výsledek=1, Str="RING")
//
//    Musíte napsat a použít pomocnou funkci
//       const char *StrStr(const char *Str, const char *s1);
//    který vrátí pozici výskytu podřetězce s1 ve Str nebo NULL v případě
//    neúspěchu.
//
//    Obě funkce musí zvládnout i prázdné řetězce
//
//    POZOR: Nesmíte použít žádné standardní funkce kromě strlen() ani žádná
//    pomocná pole (jinak 0b).
//
//    Nakonec napište PŘÍKLAD volání SearchReplace() s vhodně zvolenými
//    argumenty (včetně jejich deklarací/definic).
//
                                     #if 0
Tady by mela byt kuboshova funkce, ale smazal jsem ji, protoze byla prilis velka... RIP kuboshova funkce...
                                     #endif

char *StrStr(const char *Str, const char *s2){
    char *S = (char*)Str,*s = (char*)s2;
    int i=0;
    while(*S && *s){
        if(*S == *s){ s++; i++; }
        else if(i){ i = 0; s = (char*)s2; }
        S++;
    }
    return (i)?S-i:NULL;
}

int SearchReplace(char *Str, int Max, const char *s1, const char *s2){
    //----proste vsechny potrebne kontroly-----
    if(!Str||!s1||!s2||Max<=0)return 0;
    int count=0,s1Len=strlen(s1),s2Len=strlen(s2);
    if(StrStr(s2,s1))return 0; //retezec s2 obsahuje s1 jako podretezec
    int diff=s1Len-s2Len, sLen,iter;

    //----hledame podretezce, dokud jsou----
    char *S=Str;
    while((S=StrStr(S,s1))){
    //casem se tento string bude zmensovat a na  konci se stane NULL,
    //protoze zadne podretezce uz nebudou
        if((sLen=strlen(S))+diff >= Max)return -count;//prisli jsme o misto :(

        //posun, ktery se vyskytuje v kazde pisemce. Doporucuji si to nakreslt na papir
        //a pochopit, jak to funguje. To je fakt trivilni.
        if(diff > 0){//mame prilis mnoho volneho mista a musime zkratit nas puvodni string
            iter=sLen-s2Len+1;//pocet iteraci. napr str = aaaXXXbb,
                              //chceme z nej udelat aaaMMbb. 
                              //Vysledny pocet iteraci je delka XXXbb - delka MM + 1 pro '\0',
                              //coz je 4
            for(int i=0;i<iter;i++) *(S+s2Len+i) = *(S+s1Len+i);
        }else if (diff){//diff neni vetsi nez nula a zaroven neni nula.
                        //Jsem linej human, abych psal diff < 0 a ted pisu
                        //k tomuto zdlouhavy komentar 20iq
            iter=sLen-s1Len+1;//pocet iteraci, ten samy princip. 
                              //Nezapomente na 0, ja jsem fakt dulezity
                              //(haha you got it i mean i am zero, nothing haha)
            //pozor, diff je < 0, a proto pisu -, coz pricita diff
            for(int i=0;i<iter;i++) *(S+sLen-diff-i) = *(S+sLen-i); 
        }

        //nahradime chary
        for(int i=0;i<s2Len;i++) *(S+i) = *(s2+i);//trapne trivialne
        count++;
    }
    return count;
}
void mthrfckr3() {
    char buffer[10] = "STRING";
    printf("%s -> ", buffer);
    SearchReplace(buffer, 10, "ST", "");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    SearchReplace(buffer, 10, "RI", "STRO");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    SearchReplace(buffer, 10, "G", "HOP");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    SearchReplace(buffer, 10, "HOP", "K");
    printf("%s\n", buffer);
}

// 4) Napište program
//       WORDS Délka [soubor]
//    který z textového souboru zadaného jako druhý argument proramu (není-li
//    zadán použije stdin) čte slova funkcí ReadWord() a na stdout tiskne jen 
//    slova s délkou Délka +-1 znak (například při zadání délky 10 tiskne 
//    slova o délce 9, 10, 11). Délka je zadaná jako první argument programu.
//    Na konverzi použijte
//       int atoi(const char *nptr);
//    Každé slovo program tiskne na zvláštní řádek, před něj navíc vytiskne
//    jeho délku.
//
//    Pro čtení slova ze souboru napiště funkci
//       int ReadWord(FILE *f, char *str, unsigned n);
//    která přeskočí oddělovače (použijte !isalnum()) a čte jedno slovo ze
//    ze souboru f do řetězce str, kam uloží maximálně n bajtů (n si zvolte,
//    delší slova zkraťte a zbytek slova přeskočte). Nesmíte použít fscanf.
//    Funkce vrací SKUTEČNOU délku slova před zkrácením nebo EOF, když narazí
//    na konec souboru
//
#define WORD_LENGTH 128
int ReadWord2(FILE *f, char *str, unsigned n) {
    unsigned word_length = 0;
    int loaded_char;

    // Přeskočení bílých znaků
    while(!isalnum(loaded_char = fgetc(f)) && loaded_char != EOF);
    if(loaded_char == EOF) {
        return EOF;
    }

    // Načtení znaků
    do {
        if(loaded_char == EOF) {
            if(word_length < n) {
                str[word_length] = '\0';
            } else {
                str[n - 1] = '\0';
            }
            return EOF;
        }
        if(word_length < n - 1) {
            str[word_length] = loaded_char;
        }
        word_length++;
    } while(isalnum(loaded_char = fgetc(f)));

    if(word_length < n) {
        str[word_length] = '\0';
    } else {
        str[n - 1] = '\0';
    }
    return word_length;
}
int mthrfckr4(int argc, char *argv[]) {  // Tohle je jakoby main
    FILE *file = stdin;
    int length = 0;
    int loaded_length = 0;

    if(argc < 2) {
        fprintf(stderr, "Neplatný počet argumentů\n");
        return 1;
    }
    length = atoi(argv[1]);
    if(argc >= 3) {
        file = fopen(argv[2], "r");
        if(file == NULL) {
            fprintf(stderr, "Nepodařilo se otevřít soubor\n");
            return 1;
        }
    }

    char buffer[WORD_LENGTH];
    do {
        loaded_length = ReadWord2(file, buffer, WORD_LENGTH);
        if(loaded_length >= length - 1 && loaded_length <= length + 1) {
            printf("%d %s\n", loaded_length, buffer);
        }
    } while(loaded_length != EOF);

    if(argc >= 3) {
        fclose(file);
    }

    return 0;
}

// 5) Napište funkci
//
//       bool Edit(char *Str, int Max, unsigned Pos, unsigned N, const char *Ins)
//    
//   která v řetězci Str zamění N znaků od pozice Pos za obsah řetězce Ins.
//   Funkce vrací true, pokud dojde k úspěšnému zapsání všech znaků řetězce
//   Ins. Předpokládáme, že Str může obsahovat maximálně Max bajtů a pokud by
//   výsledek překročil tuto mez, funkce vrátí false a _nezmění_ Str.
//   (Například: Str="PUK", Max=9, Pos=1, Ins="íse", N=1, výsledek="PíseK", true)
//   Funkce _musí_ zvládnout všechny možné situace, tj. i prázdné řetězce a N==0.
//
//   POZOR: Nesmíte použít žádné standartní funcke kromě strlen() ani žádná
//          pomocná pole (jinak 0b).
//
//   Napište PŘÍKLAD volání této funkce a vhodně zvolenými argumenty (včetně
//   jejich deklarací/definic)
//
bool Edit(char *Str, int Max, unsigned Pos, unsigned N, const char *Ins) {
    if(Str == NULL || Ins == NULL) {
        return false;
    }

    int shift = strlen(Ins) - N;
    if(strlen(Str) + shift >= (unsigned)Max) {
        return false;
    }

    if(shift > 0) {  // Posun doprava
        for(unsigned i = Max - 1; i >= Pos + shift; i--) {
            Str[i] = Str[i - shift];
        }
    }
    if(shift < 0) {  // Posun doleva
        for(unsigned i = Pos; i < (unsigned)Max + shift; i++) {
            Str[i] = Str[i - shift];
        }
    }
    for(size_t i = 0; i < strlen(Ins); i++) {
        Str[Pos + i] = Ins[i];
    }

    return true;
}
void mthrfckr5() {
    char buffer[10] = "PUK";
    printf("%s -> ", buffer);
    Edit(buffer, 10, 1, 1, "ise");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    Edit(buffer, 10, 1, 3, "U");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    Edit(buffer, 10, 3, 0, "ER");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    Edit(buffer, 10, 2, 0, "N");
    printf("%s\n", buffer);
}

// 6) Napište program 
//       SwapColCSV číslo_sloupce1 číslo_sloupce2 [CVSsoubor]
//    který z CSV souboru zadaného jako třetí argument programu (není-li zadán
//    použije stdin) čte CSV-položky a na stdout tiskne obsah CSV souboru s 
//    navzájem zaměněnými (swap) sloupci zadanými jako první dva argumenty
//    programu (číslo_sloupce1 a číslo sloupce2). Položky na řádku i řádky
//    číslujeme od 1. Můžete omezit maximální počet položek na jednom řádku 
//    na 1024. Na stderr program nakonec vytiskne celkový počet zpracovaných
//    řádků.
//
//    Pro čtení jedné položky z CSV souboru musíte napsat funkci 
//  
//       int ReadCSVItem(FILE *f, char Delimiter, char *Str, unsigned m)
// 
//    která načte další položku ze souboru f do řetězce Str, kam uloží
//    maximálně m bajtů (vhodně zvolte). Pokud je položka delší, přečte jí 
//    celou, ale uloží jen prvních m-1 znaků. Musíte číst pomocí fgetc(f).
//    Znak Delimiter je zadaný oddělovač položek CSV souboru.
//    Funkce vrací jednu z následujících hodnot:
//     - (vámi správně definovanou) konstanu EOL pro poslední položku řádku
//     - standardní konstatnu EOF když je konec souboru
//     - jinak vrací 0
//
//    Poznámka: CSV (Coma Separated Value) = na řádku jsou položky-řetězce
//    oddělené speciálním oddělovacím znakem (použijte středník), pro naše
//    účely předpokládáme, že nikdy neoobsahují tento oddělovač. 
//    Příklad vstupníjho řádku: položka1;položka2; ... ;položka100
//
#define WORD_LENGTH 128
#define LINE_MAX 1024
int ReadCSVItem(FILE *f, char Delimiter, char *Str, unsigned m) {
    if(f == NULL || Str == NULL) {
        return 0;
    }
    int loaded_char;
    unsigned word_length = 0;

    // Načtení znaků
    while((loaded_char = fgetc(f)) != Delimiter) {
        if(loaded_char == EOF) {
            if(word_length < m) {
                Str[word_length] = '\0';
            } else {
                Str[m - 1] = '\0';
            }
            return EOF;
        }
        if(loaded_char == '\n') {
            if(word_length < m) {
                Str[word_length] = '\0';
            } else {
                Str[m - 1] = '\0';
            }
            return -2;
        }
        if(word_length < m - 1) {
            Str[word_length] = loaded_char;
        }
        word_length++;
    }

    if(word_length < m) {
        Str[word_length] = '\0';
    } else {
        Str[m - 1] = '\0';
    }
    return 0;
}
#define EOL 10
#define xchg(a,b)do{a^=b;b^=a;a^=b;}while(0)
#define err(msg)do{fprintf(stderr,"Wrong arguments!\n");return -1;}while(0)
int mthrfckr6(int argc, char *argv[]) {
    FILE*fp=stdin;
    unsigned tnor=0,r1,r2,n,i=0;
    const unsigned m=30;
    int rV;
    char*junk;
    char line[1024][m];//vazne,omlouvam se za coding style.Vim,ze nekomu to pijde jako hnus...
    if(argc!=4 && argc !=3)               err("Bad arguments!");
    r1 = (unsigned)strtoul(argv[1],&junk,10)-1;
    if(!r1||*junk||r1>1024)               err("Bad arguments!");
    r2 = (unsigned)strtoul(argv[2],&junk,10)-1;
    if(!r2||*junk||r2>1024)               err("Bad arguments!");
    if(argc==4&&!(fp=fopen(argv[3],"r"))) err("Cannot open the file!");

    while(1){
        tnor++;
        if((rV=ReadCSVItem(fp,';',line[i],m))==EOF)break;
        if(rV==EOL){
            for(n=0;n<m ;n++) xchg(line[r1][n],line[r2][n]);
            for(n=0;n<=i;n++) printf("%s%c",line[n],(n==i)?'\n':';');
            i=0;
        }   
        i++;
    }   
    if(fp!=stdin)fclose(fp);
    fprintf(stderr,"Lines: %d\n",tnor);
    return 0;
}

// 7) Napište funkci
//
//       int ReplaceSP(char *Str, int Max, const char *s2);
//
//    která v řetězci Str zamění _poslední_ sekvenci mezer (délky 1..x) za 
//    obsah řetězce s2 (může být i prázdný). Funkce vrací délku sekvence
//    mezer, pokud dojde k úspěšné záměně, jinak vrací délku nulu. Str může
//    obsahovat maximálně Max bajtů a pokud by výsledek překročil tuto mez, 
//    funkce vrátí nulu a _nezmění_ Str.
//    Příklad: Str="text  text", Max=99, s2="XXX", výsledek="textXXXtext", 2
//
//    Musíte napsat a použít pomocnou funkci 
//       const char *SearchSP(const char *Str, int *ptr);
//    která vrátí pozici _poslední_ sekvence mezer ve Str nebo NULL v 
//    případě neúspěchu. Funkce přes ukazatel ptr vrátí také délku 
//    nalezené sekvence (jen když ptr!=NULL).
//
//    Obě funkce musí zvládnout i prázdné řetězce.
//    POZOR: Nesmíte použít žádné standardní funkce krom strlen() ani žádná
//           pomocná pole (jinak 0b).
//
//    Napište příkald volání ReplaceSP() s vhodně zvolenými argumenty
//    (včetně jejich deklarací/definicí)
//
const char *SearchSP(const char *Str, int *ptr) {
    if(!Str)return NULL;
    int len=strlen(Str),n=0,i;

    //hledame od konce
    for(i=len-1;i>=0;i--){
        if(Str[i]==' ')n++;
        else if(n)break;
    }   

    if(ptr)*ptr=n;//nechceme se kamaradit s NULL(a proto ja nemam kamarady)
    return(n)?Str+i+1:NULL;//i je pozice znaku pred sekvenci mezer,a proto pridam 1
}
int ReplaceSP(char *Str, int Max, const char *s2) {
    if(!Str||!s2||Max<=0)return 0;//zkladni kontrly zejo. 1 !Str bude true iff Str je NULL
    
    // pocet ws              pocet posunutych znaku
    int n, s2len=strlen(s2), iter;
    char *S=(char*)SearchSP((const char*)Str,&n);
    if(!S)return 0;//nenasli jme nic.
    
    //                 delka casti, ktera nam zbyva.
    int diff=s2len-n, sLen=strlen(S);
    if((int)strlen(Str)+diff+1 > Max)return 0;//zkontrolujeme, zda je mozne nacpat znaky

    if(diff>0){//musime rozsirit string
        iter=sLen-n+1;//sLen+ten nejkratsi string + koncova nula
        for(int i=0;i<iter;i++)*(S+sLen+diff-i)=*(S+sLen-i);
    }else if(diff){//"diff neni vetsi nez nula a je nenulovy"
        iter=sLen-s2len+1;// -//-
        for(int i=0;i<iter;i++)*(S+s2len+i)=*(S+n+i);
    }

    for(int i=0;i<s2len;i++)*(S+i)=*(s2+i);
    return n;
}
void mthrfckr7() {
    char buffer[40] = "text text      text  text";
    printf("%s -> ", buffer);
    ReplaceSP(buffer, 40, "XXX");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    ReplaceSP(buffer, 40, "A");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    ReplaceSP(buffer, 40, "PUSSY");
    printf("%s\n", buffer);
}

// 8) Napište program CONVERT, který čte ze zadaného souboru (první
//    argument programu, není-li zadán, čte stdin) znaky a opisuje je na
//    stdout tak, že všechny sekvence velkých písmen A-Z (isupper) v textu
//    nahradí za jejich reverzi (znaky pozpátku, napište si funkci strrev).
//
//    Pro kopii ne A-Z znaků napište funci
//
//       int CopyNonUPPER(FILE *in, FILE *out);
//
//    která kopíruje až po první znak A-Z, který nezpracuje - použijte 
//    ungetc(c, in). Pokud narazí na konec souboru, vrací EOF, jinak 0.
//
//    Pro čtení sekvence A-Z ze souboru musíte napsat funkci
//
//       int ReadUPPER(char *s, unsigned m, FILE *f);
//
//    která přečte znaky A-Z ze souboru f do _řetězce_ s, kam uloží maximálně
//    m bajtů. Pokud je sekvence delší, hlásí chybu na stderr a _ukončí_ 
//    program. Nesmíte použít fscanf(). Funkce vrací délku přečtené sekvence 
//    A-Z (1..m-1).
//
#define WORD_LENGTH 128
void strrev(char *l) {
    if(l == NULL)return; // vazne nechceme pracovat s NULL 
    for(int i=0, j=strlen(l); i<(j>>1); i++) xchg(l[i],l[j-i-1]);//vyuzijeme makra xchg
}
int CopyNonUPPER(FILE *in, FILE *out) {
    if(in == NULL || out == NULL) {
        return 0;
    }

    int loaded_char;
    while((loaded_char = fgetc(in)) != EOF) {
        if(!isupper(loaded_char)) {
            fputc(loaded_char, out);
        } else {
            ungetc(loaded_char, in);
            return 0;
        }
    }

    return EOF;
}
int ReadUPPER(char *s, unsigned m, FILE *f) {
    if(s == NULL || f == NULL) {
        return 0;
    }

    unsigned seq_length = 0;
    int loaded_char;

    while(isupper(loaded_char = fgetc(f))) {
        if(loaded_char == EOF) {
            s[seq_length] = '\0';
            return EOF;
        }
        if(seq_length >= m - 1) {
            fprintf(stderr, "Přetečení bufferu");
            exit(1);
        }
        s[seq_length] = loaded_char;
        seq_length++;
    }
    ungetc(loaded_char, f);
    s[seq_length] = '\0';

    return seq_length;
}
int mthrfckr8(int argc, char *argv[]) {
    FILE *f = stdin;
    char buffer[WORD_LENGTH];
    int read_return;

    if(argc >= 2) {
        f = fopen(argv[1], "r");
        if(f == NULL) {
            fprintf(stderr, "Nepodařilo se otevřít soubor\n");
            return 1;
        }
    }

    while(CopyNonUPPER(f, stdout) != EOF) {
        read_return = ReadUPPER(buffer, WORD_LENGTH, f);
        strrev(buffer);
        printf("%s", buffer);
        if(read_return == EOF) {
            break;
        }
    }

    return 0;
}

// 9) Napište funkci
//       
//       int WordReplace(char *Str, int Max, const char *s2);
//
//    která v řetězci Str zamění _první_ slovo (sekvenci znaků isalpha) za
//    obsah řetězce s2 (může být i prázdný). Funkce vrací délku slova pokud 
//    dojde k úspěšné záměně, jinak vrací nulu. Str může obsahovat maximálně 
//    Max bajtů a pokud by výsledek překročil tuto mez, funkce vrátí nulu a 
//    _nezmění_ Str.
//    (Příklad: Str:"_abc_def_", Max=99, s2="XX", výsledek="_XX_def_", 3)
//   
//    Musíte napsat a použít pomocnou funkci
//       const char *WordSearch(const char *Str, int *ptr);
//    která vrátí pozici _první_ sekvence isalpha znaků ve Str nebo NULL v
//    případě neúspěchu. Funkce přes ukazatel ptr vrátí také délku nalezené
//    sekvence (jen když ptr!=NULL).
//
//    Obě funkce _musí_ zvládnout i prázdné řetězce.
//    POZOR: Nesmíte použít žádné standartní funkce kromě strlen(), isalpha()
//           ani žádná pomocná pole (jinak 0b).
//
//    Napište příklad volání WordReplac() s vhodně zvolenými argumenty
//    (včetně jejich) deklarací/definic).
//
const char *WordSearch(const char *Str, int *ptr) {
    if(Str == NULL) {
        return NULL;
    }
    size_t start = 0;
    int length = 0;

    while(start < strlen(Str)) {
        if(isalpha(Str[start])) {
            break;
        }
        start++;
    }
    for(size_t i = start; i < strlen(Str); i++) {        
        if(!isalpha(Str[i])) {
            if(ptr != NULL) {
                *ptr = length;                
            }
            return &(Str[start]);
        }        
        length++;
        if(i == (strlen(Str) - 1)) {
            if(ptr != NULL) {
                *ptr = length;
            }
            return &(Str[start]);
        }
    }
    return NULL;
}
int WordReplace(char *Str, int Max, const char *s2) {
    if(Str == NULL || s2 == NULL) {
        return 0;
    }

    int word_length = 0;    
    char *replace = (char *)WordSearch(Str, &word_length);    
    if(replace == NULL) {
        return 0;
    }
    int shift = strlen(s2) - word_length;

    if(shift > 0) {  // Posun doprava
        if(strlen(Str) + shift >= (unsigned)Max) {
            return 0;
        }

        for(int i = Max - 1; i >= 0; i--) {
            if(&(Str[i - shift]) == replace) {
                break;
            }
            Str[i] = Str[i - shift];
        }
    }
    if(shift < 0) {  // Posun doleva
        for(int i = 0; i < Max - 1; i++) {
            replace[i] = replace[i - shift];         
            if(replace[i - shift] == '\0') {
                break;
            }
        }
    }

    for(size_t i = 0; i < strlen(s2); i++) {
        replace[i] = s2[i];
    }

    return word_length;
}
void mthrfckr9() {
    char buffer[40] = "_abc_def_";
    printf("%s -> ", buffer);
    WordReplace(buffer, 40, "XX");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    WordReplace(buffer, 40, "A");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    WordReplace(buffer, 40, "TITS");
    printf("%s\n", buffer);
}

//10) Napiště program REVERSE_WORDS který čte ze zadaného souboru (první
//    argument programu) slova a tiskne je obráceně ("abc"->"cba") do souboru
//    stejného jména s přidanou připonou ".out". Na obrácení slova máte k 
//    dispozici funkci strrev(char *str); Není-li soubor zadán, čte ze stdin
//    a zapisuje na stdout. Slovo je souvislá posloupost písmen --- použijte
//    isalpha(). Pro čtení slova ze souboru napište funkci:
//
//       int read_word(FILE *f, char *Str, size_t m);
//
//    která přeskočí oddělovače a čte slovo ze souboru f do řetězce Str, kam
//    uloží maximálně m znaků. Pokud je slovo delší hlásí chybu na stderr a 
//    ukončí program. Nesmíte použít fscanf(). Funkce vrací délku nebo EOF,
//    když narazí na konec souboru.
//
#define WORD_LENGTH 128
int read_word(FILE *f, char *Str, size_t m) {
    if(f == NULL || Str == NULL) {
        return 0;
    }

    unsigned word_length = 0;
    int loaded_char;

    // Přeskočení bílých znaků
    while(!isalpha(loaded_char = fgetc(f)) && loaded_char != EOF);

    // Načtení znaků
    do {
        if(loaded_char == EOF) {
            Str[word_length] = '\0';
            return EOF;
        }
        if(word_length >= m - 1) {
            fprintf(stderr, "Přetečení bufferu\n");
            exit(1);
        }

        Str[word_length] = loaded_char;
        word_length++;
    } while(isalpha(loaded_char = fgetc(f)));

    Str[word_length] = '\0';
    return word_length;
}
int mthrfckr10(int argc, char *argv[]) {
    FILE *in = stdin;
    FILE *out = stdout;
    char buffer[WORD_LENGTH];
    int read_return;

    if(argc >= 2) {
        in = fopen(argv[1], "r");
        if(in == NULL) {
            fprintf(stderr, "Nepodařilo se otevřít soubor\n");
            return 1;
        }

        char name[strlen(argv[1]) + 5];
        strcpy(name, argv[1]);
        strcat(name, ".out");
        out = fopen(name, "w");
        if(out == NULL) {
            fclose(in);
            fprintf(stderr, "Nepodařilo se otevřít soubor\n");
            return 1;
        }
    }
    do {
        read_return = read_word(in, buffer, WORD_LENGTH);
        strrev(buffer);
        fprintf(out, "%s ", buffer);
    } while(read_return != EOF);

    return 0;
}

//11) Napiste funkci Edit2, ktera do retezce Str na pozici pos vlozi retezec s2.
//    Retezec Str muze obsahovat maximalne Max bytu. pos muze byt zaporne, v
//    takovem pripade vkladame na pozici od konce (pos == -1 <=> vkladame za
//    konec retezce). V pripade, ze se novy retezec nevejde do Max bytu,
//    funkce vraci -1.
//    
//    Mame osetrit vsechny mozne pripady (prazdne retezce, pos mimo rozsah a
//    podobne). Nesmime pouzit zadnou funkci standardni knihovny krome strlen.
//    Funkce vraci -1 pri neuspechu, jinak novou delku retezce.
//   
//    Napiste priklad volani funkce.
//                                                  (Zadání z paměti by Fifinas)
int Edit2(char *Str, int pos, int Max, const char *s2) {
    if (Str == NULL || s2 == NULL)
        return -1;

    // Prevedeni zaporneho pos
    if (pos < 0) {
        pos = strlen(Str) + pos + 1; // +1, aby to ukazovalo spravne. Pro -1 chci, aby mi pos ukazovalo na koncovou 0.
    }

    // Kontrola mezi
    if (pos < 0 || pos > (int)strlen(Str)) {
        return -1;
    }
    int difference = strlen(s2);
    if ((int)strlen(Str) + difference >= Max) {
        // Neni dost prostoru
        return -1;
    }
    // Musim udelat prostor pro nove znaky retezce, posouvam od pos znaky doprava. Musim ale zacit
    // na konci retezce, abych si "neslapal na paty". Posouvam i koncovou 0.
    for (int i = strlen(Str); i >= pos; i--) {
        Str[i+difference] = Str[i];
    }

    // Ted uz staci jen zapsat retezec do vytvoreneho mista.
    for (int i = 0; i < difference; i++) {
        Str[pos+i] = s2[i];
    }
    return strlen(Str);
}
void mthrfckr11() {
    char str[20] = "Ahoj svete!";
    printf("start: %s\n", str);
    int res = Edit2(str, 4, 20, " kruty");
    printf("po Edit2(str, 4, 20, \" kruty\"); return: %d | vysledek: %s\n", res, str);
    res = Edit2(str, -1, 20, "xx");
    printf("po Edit2(str, -1, 20, \"xx\"); return: %d | vysledek: %s\n", res, str);
    res = Edit2(str, -1, 20, "x");
    printf("po Edit2(str, -1, 20, \"x\"); - doslo misto: return: %d | vysledek: %s\n", res, str);
}

//12) Napiste program REVERSE, ktery cte ze souboru zadaneho jako 1. argument
//    (stdin, pokud neni zadan) po radcich a pokud se na radku vyskytuje nejaky
//    C-string, otoci jeho obsah("abc" -> "cba"). Pro cteni po radcich napiste
//    funkci: int read_line(FILE *in, char *Str, int Max), ktera precte radek a
//    vrati pocet nactenych znaku. Nesmite pouzit funkci fgets. V pripade, ze se
//    radek nevejde do Max bytu, vypise chybove hlaseni na stderr a konci
//    program. V pripade, ze narazi na EOF, vraci EOF. Pro otaceni retezcu si
//    napiste pomocnou funkci s vhodne zvolenym prototypem
//
//                                                  (Zadání z paměti by Fifinas)
#define STR_LEN 1024
int read_line(FILE *in, char *Str, int Max) {
    // Poznamka: nebylo specifikovano, jestli mame nacitat i \n, ve svem reseni
    // jsem se rozhodl, ze jej nacitat nebudu.
    if (in == NULL || Str == NULL)
        return 0;
    int c;
    int read = 0;
    while ((c = getc(in)) != EOF && c != '\n') {
        if (read + 1 >= Max) {
            fprintf(stderr, "Nedostatek mista v retezci\n");
            exit(1);
        }
        Str[read] = c;
        read++;
    }
    // Hlavne nezapomenout ukoncit retezec.
    Str[read] = '\0';
    if (c == EOF)
        return EOF;
    return read;
}
char *reverse(char *str) {
    // Tohle je asi docela straight-forward, proste jen otocim pres pomocnou promennou retezec.
    // Slo by to samozrejme delat pres fancy XOR metodu, ale whatever.
    if (str == NULL)
        return NULL;
    int len = strlen(str);
    for (int i = 0; i < len/2; i++) {
        char tmp = str[i];
        str[i] = str[len-1-i];
        str[len-1-i] = tmp;
    }
    return str;
}
int mthrfckr12(int argc, char *argv[]) {
    FILE *in = stdin;
    if (argc > 1) {
        // Cteme ze souboru
        in = fopen(argv[1], "r");
        // Nezapomenout zkontrolovat return fopen
        if (in == NULL) {
            fprintf(stderr, "nepovedlo se otevrit soubor\n");
            return 1;
        }
    }

    char line[STR_LEN];
    char buffer[STR_LEN];
    int buffer_index = 0;
    int read;
    do {
        read = read_line(in, line, STR_LEN);
        // Jdu pres radek a hledam C-stringy
        for (int i = 0; i < (int)strlen(line); i++) {
            if (line[i] == '"') {
                // Nasel jsem potencialni zacatek C-stringu, musim ho cely nacist
                int j;
                for (j = i + 1; j < (int)strlen(line); j++) {
                    if (line[j] == '"')
                        break; // nasel jsem ukoncovaci ", OK
                    buffer[buffer_index] = line[j];
                    buffer_index++;
                }
                buffer[buffer_index] = '\0';
                if (line[j] == '"') {
                    // vypsat otocene to, co je v bufferu
                    printf("\"%s\"", reverse(buffer));
                } else {
                    // Nenasel jsem ukoncovaci uvozovku, neotacim.
                    printf("\"%s", buffer);
                }
                buffer_index = 0;
                i = j; // Musim zmenit i, protoze jsem cast radku zpracoval, nechci ho zpracovavat znova
            } else {
                putchar(line[i]); // Normalni znak mimo C-string, jen ho vypisu
            }
        }
        putchar('\n'); // Protoze jsem neukladal \n do radku, tak ho ted vypisu, aby se nespojovaly radky
    } while(read != EOF);

    // Nezapomenout uzavrit soubor
    if (argc > 1)
        fclose(in);
    return 0;
}

// Napiste funkci
//     int ReplaceCharSeq(char *Str, int Max, char c, const char *s2);
// ktera v retezci Str nejde (NAPISTE na to pomocnou funkci FindSeq) privni
// sekvenci 2 a vice znaku c a tuto sekvenci nahradi obsahem retezce s2.
// Vyreste vrechny situace, vcetne prazdnych retezcu.
// Funkce vraci delku Str po uspesne zamene, jinak vraci -1.
// Str muze obsahovat maximalne Max bajtu a pokud by vysledek
// prekrocil tuto mez, funkce vrati -1 a NEZMENI Str.
// (Priklad: Str:"texxt", Max=9, c='x',s2="XXX", vysledek="teXXXt".
// POZOR: V teto funkci nesmite pouzit zadne pstandardni funkce 
//        krome strlen() ani zadna pomocna pole (jinak oznuk).
//
// Napiste PRIKLAD VOLANI teto funkce s vhodne zvolenymi argumenty
// (vcetne jejich deklaraci/definic)
char *FindSeq(char *Str, char c, int *n) {
    //zakladni kontroly...
    if(!Str)return NULL;
    int i=0; char *S=Str;//pocet vyskytu a iterator

    //hlavni smycka prochazejici string a hledajici sekvenci znaku
    while(*S){
        if(*S++==c)i++;//omlouvam se vsem ze coding style.
        else if(i)break;//Toto je nasledkem projektu z IZG... Klidne to upravte
    }

    if(n)*n=i;//zapisu do n pocet znaku posloupnosti
    return(i)?S-i-1:NULL;//pozor na -1. Ma tady byt, jinak str ukazuje na 2. prvek posloupnosti
}
int ReplaceCharSeq(char *Str, int Max, char c, char *s2) {
    if(!Str||!s2||!c)return -1;//kontrola

    int s2len=strlen(s2), n=0;
    char *S=FindSeq(Str, c, &n);
    if(n<2)return -1;//pocet prvku posoupnosti musi byt vetsi jako 2

    int diff=s2len-n, iter, slen=strlen(S), Strlen=strlen(Str)+diff;
    if(Strlen+1>Max)return -1;//doslo nam misto, vratime -1

    //standardni pattern, ktery se vyskytuje v kazde pisemce
    if(diff<0){
        iter=slen-s2len+1;
        for(int i=0;i<iter;i++)*(S+s2len+i)=*(S+n+i);
    }else if(diff){
        iter=slen-n+1;
        for(int i=0;i<iter;i++)*(S+slen+diff-i)=*(S+slen-i);
    }

    //a nakonec to vsechno nacpeme do stringu
    for(int i=0;i<s2len;i++)*(S+i)=*(s2+i);

    return Strlen;
}
int mthrfckr13() {
    int ret;
    char str1[128]="text  text\0arsttsar";
    ret=ReplaceCharSeq(str1,128,' ',"A");
    printf("1: return=%.3d, string=\"%s\"  ",ret,str1);
    test(ret==strlen("textAtext")&&!strcmp(str1, "textAtext"));
        
    char str2[128]="text      text\0arstarstarstarst";
    ret=ReplaceCharSeq(str2,128,' '," anxious ");
    printf("2: return=%.3d, string=\"%s\"  ",ret,str2);
    test(ret==strlen("text anxious text")&&!strcmp(str2, "text anxious text"));

    char str3[30]="text      text\0arsts";
    ret=ReplaceCharSeq(str3,128,' ', "XXX  XXX");
    printf("3: return=%.3d, string=\"%s\"  ",ret,str3);
    test(ret==strlen("textXXX  XXXtext")&&!strcmp(str3, "textXXX  XXXtext"));
    
    ret=ReplaceCharSeq(str3,128,'X', NULL);
    printf("4: return=%.3d, string=\"%s\"  ",ret, str3);
    test(ret==-1&&!strcmp(str3,"textXXX  XXXtext"));
    
    char str5[128]="privet\0arst";
    ret=ReplaceCharSeq(str5,128,0, "milet");
    printf("5: return=%.3d, string=\"%s\"  ",ret,str3);
    test(ret==-1&&!strcmp(str5, "privet"));
    return 0;
}


// Napiste program REVERSE_ODD, ktery cte ze zadaneho souboru(prvni
// argument programu) radky textu. Pokud radek obsahuje lichy pocet znaku,
// obrati v nem poradi znaku ("abc"->"cba") a jen tyto upravene radky
// tiskne do souboru stejneho jmena s pridanou priponou ".rev".
// Neni-li soubor zadan, cte ze stdin a zapisuje do stdout.
// Na obraceni radku mate k dispozici funkci strrev(char *str);
// Zvolte implementacni limit maximalne 127 znaku na radek.
//
// Pro cteni zadku napiste funkci:
//
//     int ReadLn(FILE * in, char * line, unsigned max);
// ktera cte jeden radek a vraci jeho delku. Pokud narazi na konec
// souboru, vraci EOF. Kdyz je radek delsi, nez ma BAJTU, ukonci program
// s chybovym hlasenim na stderr. Nesmite pouzit funkci fgets().
int ReadLn(FILE *in, char *line, unsigned m){
    unsigned i;
    int ch;
    for(i=0;i<m-1 && (ch=fgetc(in))!=EOF && ch!='\n';i++)line[i]=ch;
    if(ch==EOF)return EOF;
    if(ch=='\n'){line[i]='\0';return i;}
    return -2;
}
//#define err(msg) do{fprintf(stderr,"%s\n",(msg));exit(-1);}while(0)
int mthrfckr14(int argc, char **argv){
    FILE *in=stdin,*out=stdout;
    if(argc==2){
        if(!(in=fopen(argv[1],"r")))err("Cannot open the file!");//otevrime soubor pro cteni

        char *n = calloc(strlen(argv[1])+strlen(".rst")+1,1);//velikost + 1 pro '\0'
        if(!n){fclose(in);err("Cannot allocate memory!");}//in je jiz otevreny a je potreba ho zavrit

        //2krat zkopirujeme do n.Na zacatku jmeno, pak priponu
        // proste kopie      n+strlen je ukazatel na posledni bajt retezce, tam dame nasi priponu
        strcpy(n,argv[1]); strcpy(n+strlen(argv[1]),".rev");

        if(!(out=fopen(n,"w"))){fclose(in);free(n);err("Cannot open the file!");}//pokusime se otevrit out
        free(n);//jmeno jiz nepotrebujeme
    }

    int c=0, r=0; const unsigned m=128;
    char line[m];//at na zacatku bude prazdny radek

    // pozor, na zacatku jde !r, protoze v pripade chyby(t.j r == 1) se dal divat nebude,
    // a proto mame zajisteno, ze uz nic nenacteme
    while(!r && (c=ReadLn(in, line, m))!=EOF){
        if(c==-2)r=1;
        if(c%2){
            strrev(line);
            fprintf(out, "%s\n", line);
        }
    }

    // chceme zavrit obab soubory, protoze jsme vytvorili 2
    if(in!=stdin){fclose(in); fclose(out);}
    if(r) err("Too long!");

    return 0;
}


//                                                                            //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////// MAIN ////////////////////////////////////
//                                                                            //

int main() {
    float temp[9][10];
    int *temp2[2][3][4];
    puts("1. ZADANI - jednoduche funkce\n");
    puts("-----------------------------\n");
    printf("++ Expr1: %c\n", expr1());
    printf("++ Expr2: nope\n");
    printf("++ Expr3: %d\n", expr3());
    printf("++ Expr4: %d\n", expr4());
    printf("++ Expr5: nope\n");
    printf("++ Swit1: %d\n", swit1());
    printf("++ Swit2: %d\n", swit2());
    printf("++ Swit3: %d\n", swit3());
    printf("++ f1: %ld\n", f1(temp));
    printf("++ f2: %c\n", f2());
    printf("++ f3: %c\n", f3());
    printf("++ f4: %c\n", f4(3));
    printf("++ f5: %c\n", f5(4));
    printf("++ f6: %c\n", f6());
    printf("++ f7: %c\n", f7());
    printf("++ f8: %c\n", f8());
    printf("++ f9: %c\n", f9());
    printf("++ f10: %c\n", f10());
    printf("++ f11: %c\n", f11());
    printf("++ f12: nope\n");
    printf("++ f13: %d\n", f13(temp2));
    printf("++ main1: %d\n", main1());
    printf("++ main2: %d\n", main2());
    printf("\n\n\n");

    puts("2. ZADANI - deklarovat/definovat funkce, ktere alokuji matice\n");
    puts("-----------------------------\n");
    printf("++ shrshi1:\n");shrshi1();
    printf("++ shrshi2:\n");shrshi2();
    printf("++ shrshi3:\n");shrshi3();
    printf("\n\n\n");

    puts("2. ZADANI - jednoducha makra\n");
    puts("-----------------------------\n");
    printf("++ mac1:\n");mac1();
    printf("++ mac2:\n");mac2();
    printf("++ mac3:\n");mac3();
    printf("++ mac4:\n");mac4();
    printf("\n\n\n");

    puts("3. ZADANI - prace se soubory a retezci\n");
    puts("-----------------------------\n");
    char *args1[] = { "mthrfckr2", "file1" };
    char *args2[] = { "mthrfckr4", "4", "file2" };
    char *args3[] = { "mthrfckr6", "2", "4", "file3" };
    char *args4[] = { "mthrfckr8", "file4" };
    char *args5[] = { "mthrfckr10", "file5" };
    char *args6[] = { "mthrfckr12", "file6" };
    char *args7[] = { "mthrfckr14", "file7" };
    printf("++ mthrfckr1:\n"); mthrfckr1();
    printf("++ mthrfckr2:\n"); printf("returns: %d\n", mthrfckr2(2, args1));
    printf("++ mthrfckr3:\n"); mthrfckr3();
    printf("++ mthrfckr4:\n"); mthrfckr4(3, args2);
    printf("++ mthrfckr5:\n"); mthrfckr5();
    printf("++ mthrfckr6:\n"); mthrfckr6(4, args3);
    printf("++ mthrfckr7:\n"); mthrfckr7();
    printf("++ mthrfckr8:\n"); mthrfckr8(2, args4);
    printf("++ mthrfckr9:\n"); mthrfckr9();
    printf("++ mthrfckr10:\n");mthrfckr10(2, args5);
    printf("++ mthrfckr11:\n");mthrfckr11();
    printf("++ mthrfckr12:\n");mthrfckr12(2, args6);
    printf("++ mthrfckr13:\n");mthrfckr13();
    printf("++ mthrfckr14:\n");mthrfckr14(2, args7);
    return 0;
}

//                                                                            //
////////////////////////////////////////////////////////////////////////////////
// This is the end, hold your breath and count to 90 minutes, uuuu you need to 
// act a fool arrr, cause hit or miss, guess pepe never miss, leg huh, 
// everything is too late, everything is too late, everything is too late and
// everything is too late, im your light, Tokyo by night, i wonder if you know,
// how they live in FIT, if you seen it, then you mean it, then you know you have 
// to go, mother looking at me, tell me what do you see, YES Ive lost my mind,
// hmmm where is my mind, where is my mind, where is my mind, maybe its in the 
// gutter, where i left my lover, what an expensive fate, well here we are
// dont turn away now.
// 
// Remeber:
// Love is not for real if it doesn't hurt.
// Up is hard to reach.
// It takes a lot to ask for help.
// The only way to fly is to never fall.
// What if I believe, sweat, grind, bleed, and nothing changes.
//
// Optimální rozdělení času:
// Baity:               5  minut
// Deklarace, definice: 10 minut
// Makro:               15 minut
// 1. dlouhej příklad:  30 minut
// 2. dlouhej příklad:  30 minut
//
