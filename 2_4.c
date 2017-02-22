#include <stdio.h>

typedef struct voorwerp {
 int nummer;
 char naam[20];
 double gewicht, lengte;
} voorwerp;

int main (void) {
    voorwerp voorwerp;
    
    printf("nummer: ");
    scanf("%d", &voorwerp.nummer);
    printf("naam: ");
    scanf("%s", voorwerp.naam);
    printf("gewicht: ");
    scanf("%lf", &voorwerp.gewicht);
    printf("lengte: ");
    scanf("%lf", &voorwerp.lengte);
    
    printf("%s heeft nummer %d, weegt %lf kg en is %lf cm", voorwerp.naam, voorwerp.nummer, voorwerp.lengte, voorwerp.gewicht);
}
