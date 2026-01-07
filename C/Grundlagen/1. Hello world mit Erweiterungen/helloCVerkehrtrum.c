// Unser drittes Programm: Hallo mit Ausgabe eines oder mehrerer Namen
//
// Aufruf: hello3 name1 name2 ...
//
// Klaus Kusche, 2010

#include <stdio.h>

int main(int argc, const char *argv[])
{
  if (argc == 1) {
    printf("Hallo, ich bin %s wer bist du?\n", argv[0]);
  } else {
    for (int i = argc - 1; i >= 1; --i) {
			
			if (argc - 1 > 10){
				printf("Hallo an alle!\n");
				break;
			} 
			
			if (i == argc - 1){
	      printf("Hallo, %s du bist Erster!\n", argv[i]);
			} else {
	      printf("Hallo, %s, %d. Platz!\n", argv[i], (i - argc) * -1);
			}

    }

    printf("Ihr seid %d Leute\n", argc - 1);

  }

  return 0;
}