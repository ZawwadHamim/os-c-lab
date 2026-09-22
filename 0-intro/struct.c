#include<stdio.h>
#include<string.h>

struct Students{
        char name[100];
        int id;
        char semester[20];
    };

int main(){

    struct Students s1;
    struct Students s2;

    strcpy(s1.name,"Rakin");
    s1.id = 230;
    strcpy(s1.semester,"fall");
    
    printf("student name is %s\n",s1.name);
    printf("student id is %d",s1.id);

}