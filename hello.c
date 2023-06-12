#include <stdio.h>

int main(){
    int a;
    printf("input a number: ");
    scanf("%d", &a);
    for(int i=0; i<a; i++)
        printf("hello world #%d\n", i+1);
    return 0;
}