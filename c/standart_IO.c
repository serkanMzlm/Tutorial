#include <stdio.h>

int number;
char ch;
char name[20];

int main(){
  printf("Enter a char: ");
  ch = getchar();
  putchar(ch);  
  while (getchar() != '\n') { // Tampon belleği boşaltmak için yapılır.
      continue;
  }
  printf("\nchar : %c\n", getchar());
  printf("Enter a number: ");
  scanf("%d", &number);
  printf("number: %d\n", number);

  while (getchar() != '\n') {
        continue;
  }
  puts("what is your name: ");
  fgets(name, sizeof(name), stdin);
  puts(name);
  return 0;
}