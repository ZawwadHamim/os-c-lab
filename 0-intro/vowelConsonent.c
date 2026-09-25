#include<stdio.h>
#include<ctype.h>
int main(){
    char c;
    printf("Enter a alphabet: ");
    scanf("%c",&c);

    if(!isalpha(c)){
        printf("Chracter is not an alphabet");
        return 0;
    }
    char ch = tolower(c);

    if(ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u'){
        printf("%c is a vowel",c);
    }
    else{
        printf("%c is a consonent",c);
    }

    return 0;

}