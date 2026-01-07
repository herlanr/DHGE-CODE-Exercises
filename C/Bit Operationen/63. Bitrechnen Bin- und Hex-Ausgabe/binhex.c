// Ausgabe von Zahlen binär und hexadezimal
//
// Aufruf: binhex n1 n2 ...
//
// Klaus Kusche

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  if (argc < 2) {
    fprintf(stderr, "Aufruf: %s n1 n2 ...\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  for (int arg = 1; arg < argc; ++arg) {
    // bei normalem "int" könnte es Überraschungen bei >> geben!
    unsigned int n = atoi(argv[arg]);
    printf("%10u: ", n);

    // Hexadezimal = in Gruppen von 4 Bits
    for (int i = 28; i >= 0; i -= 4) {  // Schleife 28, 24, 20, ..., 0
      // bringe die auszugebenden 4 Bits ganz nach rechts:
      // Zahl um i Stellen nach rechts schieben
      // und alles bis auf die letzten 4 Bits wegmaskieren
      // ==> digit ist 0 bis 15
      unsigned int digit = (n >> i) & 0xf;
      if (digit < 10) putchar('0' + digit);
      else putchar('A' + digit - 10);
      // Alternative z.B.:
      //char ziffer[16] = "0123456789ABCDEF";
      //putchar(ziffer[digit]);
      if (i == 16) putchar(' ');    // nach Bits 16-19 Zwischenraum machen
    }

    putchar(' ');
    putchar(' ');

    // Binär
    for (int i = 31; i >= 0; --i) {
      // bringe das auszugebende Bit i ganz nach rechts
      // und maskiere alle Bits davor weg
      // ==> digit ist 0 oder 1
      unsigned int digit = (n >> i) & 1;
      putchar('0' + digit);
      // Alternative z.B. "prüfe das i-te Bit von n"
      //if ((n & (1 << i)) != 0) putchar('1');
      //else putchar('0');
      //
      // Mach nach den Bits 28, 24, 20, ..., 4 einen Zwischenraum
      // ((i & 3) == 0) liefert dasselbe Ergebnis wie (i % 4 == 0)
      if (((i & 3) == 0) && (i != 0)) putchar(' ');
    }

    putchar('\n');
  }

  exit(EXIT_SUCCESS);
}