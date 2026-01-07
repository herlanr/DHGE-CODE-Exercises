// Unser drittes Programm: Hallo mit Ausgabe eines oder mehrerer Namen
//
// Aufruf: hello3 name1 name2 ...
//
// Klaus Kusche, 2010

#include <stdio.h>

int main(int argc, const char *argv[])
{
  if (argc == 1) {
    printf("Hallo, wer bist du?\n");
  } else {

      printf("Hallo");

      for (int i = 1; i < argc; ++i) {
        
          printf(" %s,", argv[i]);
        }
  }

  return 0;
}