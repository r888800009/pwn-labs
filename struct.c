#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  struct student {
    char name[20];
    int age;
    char id[20];
  };

  struct student *s1;
  s1 = (struct student *)malloc(sizeof(struct student));

  printf("Enter name: ");
  scanf("%s", s1->name);
  printf("Enter age: ");
  scanf("%d", &s1->age);
  printf("Enter id: ");
  scanf("%s", s1->id);

  printf("Name: %s\n", s1->name);
  printf("Age: %d\n", s1->age);
  printf("Id: %s\n", s1->id);

  return 0;
}
