// Cross-Reference-Liste, mit Hashtable
//
// Aufruf: xref-hash file ...
//
// Klaus Kusche, 2002

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

// Größe der Hashtable
// Kleine Primzahl
//#define HASHPRIME 10007
// Große Primzahl
#define HASHPRIME 1000003
// Schlecht: Große Zweierpotenz
//#define HASHPRIME 1048576
// Ganz schlecht: Kleine Zweierpotenz
//#define HASHPRIME 8192

// Max. Länge einer Input-Zeile
#define LINELEN 16384

// Welche Buchstaben sind Anfang eines Wortes?
#define iswordbeg(c) (isalpha(c) || ((c) == '_'))

// Welche Buchstaben gehören zu einem Wort?
#define isinword(c) (isalnum(c) || ((c) == '_'))

// Max. Listenlänge in der Statistik-Ausgabe
#define MAXLEN  50

// Typ eines Eintrags der Positionsliste
typedef struct _pos_entry {
  const char *filename;      // File, in dem die Position liegt (= argv[...])
  int line;                  // Zeilennummer
  int column;                // Spaltennummer
  struct _pos_entry *next;   // Verkettung zur nächsten Position
} pos_entry;

// Typ eines Eintrags der Wortliste
typedef struct _word_entry {
  const char *text;          // Text des Wortes
  pos_entry *first_pos;      // Head der Positionsliste des Wortes
  pos_entry *last_pos;       // Tail der Positionsliste des Wortes
  struct _word_entry *next;  // Verkettung der Wortliste eines Hashwerts
} word_entry;


// Die Hashfunktion: Berechnet aus einem Wort den Index in die Hashtable
unsigned int hash(const char *text);
// Liefert einen Pointer auf n mit malloc angeforderte Bytes, mit Fehlerprüfung
void *mymalloc(size_t n);
// Liefert einen Pointer auf eine strdup-Kopie von s, mit Fehlerprüfung
char *strsave(const char *s);
// Liefert einen Pointer auf einen neu angelegten Positionsknoten
pos_entry *new_pos(const char *filename, int linenr, int colnr);
// Liefert einen Pointer auf einen neu angelegten Wortknoten
word_entry *new_word(const char *word, pos_entry *pos, word_entry *next);
// Hängt die Position pos *hinten* an die Positionsliste von word an
void add_pos(pos_entry *pos, word_entry *word);
// Speichert eine neue Position des (neuen oder bekannten) Wortes word
void save_word(const char *filename, int linenr, int colnr, const char *word);
// Ermittelt und speichert alle Worte in der Zeile line
void read_line(const char *filename, int linenr, char *line);
// Liest und verarbeitet den angegebenen File zeilenweise
void read_file(const char *filename);
// Gibt alle Positionen der Positionsliste des Wortes word aus
void list_pos(const word_entry *word);
// Sucht das angegebene Wort word im Hashspeicher, gibt seine Positionen aus
void process_word(const char *word);
// Liest und verarbeitet den Input vom Terminal (ein Wort pro Zeile!)
void process_input(void);
// Gibt Statistiken über die Hash-Verteilung aus
void statistics(void);


// Die Hashtable: Enthält die Head-Pointer der Wortlisten
word_entry *hashtable[HASHPRIME];

// Der Programmname (für Fehlermeldungen)
const char *progname;

// Die Hashfunktion: Berechnet aus einem Wort den Index in die Hashtable
// Verwendet eine 7-Bit-Rotation und Xor pro Zeichen
// und liefert diese Zahl mod Arraygröße
unsigned int hash(const char *text)
{
  unsigned int h = 0;  // muss wegen >> unsigned sein!
  const char *p;

  for (p = text; *p != '\0'; ++p) {
    // Einfach, aber gut:
    // Alten Wert 7 Bits nach links rotieren (weil Bit 8 bei ASCII immer 0 ist),
    // Bits des Buchstabens mit Xor dazu
    h = ((h << 7) ^ (h >> 25)) ^ *p;
    // Etwas schlechter: 8 Bit Rotate
    //h = (h << 8) ^ (h >> 24) ^ *p;
    // Schlecht: 7 Bit Shift (nur die letzten 4,5 Zeichen zählen!)
    //h = (h << 7) ^ *p;
    // Ganz schlecht: 8 Bit Shift (nur die letzten 4 Zeichen zählen!)
    //h = (h << 8) ^ *p;
  }
  // das Ergebnis in den gewünschten Bereich bringen
  return h % HASHPRIME;
}

// Liefert einen Pointer auf n mit malloc angeforderte Bytes, mit Fehlerprüfung
void *mymalloc(size_t n)
{
  void *p;

  if ((p = malloc(n)) == NULL) {
    fprintf(stderr, "%s: Out of memory\n", progname);
    exit(EXIT_FAILURE);
  }

  return p;
}

// Liefert einen Pointer auf eine mit strdup angelegte Kopie von s,
// mit Fehlerprüfung
char *strsave(const char *s)
{
  char *p;

  if ((p = strdup(s)) == NULL) {
    fprintf(stderr, "%s: Out of memory\n", progname);
    exit(EXIT_FAILURE);
  }

  return p;
}

// Liefert einen Pointer auf einen neu angelegten Positionsknoten
// Die Argumente enthalten die im Knoten einzutragende Position
// Die Verkettung des neuen Knotens wird auf NULL gesetzt
pos_entry *new_pos(const char *filename, int linenr, int colnr)
{
  pos_entry *p;

  p = (pos_entry *) (mymalloc(sizeof (pos_entry)));
  p->filename = filename;
  p->line = linenr;
  p->column = colnr;
  p->next = NULL;
  return p;
}

// Liefert einen Pointer auf einen neu angelegten Wortknoten
// word ist das im Knoten einzutragende Wort, pos dessen erste Position,
// und next ist als Verkettung auf den nächsten Wortknoten einzutragen
// Achtung: word darf nicht direkt gespeichert werden
// (weil es auf den internen Zeilenpuffer von read_file zeigt
// und daher beim Lesen der nächsten Zeile überschrieben wird),
// sondern es muss eine dynamisch erzeugte *Kopie* im Knoten gespeichert werden!
word_entry *new_word(const char *word, pos_entry *pos, word_entry *next)
{
  word_entry *w;

  w = (word_entry *) (mymalloc(sizeof (word_entry)));
  w->text = strsave(word);
  w->first_pos = w->last_pos = pos;
  w->next = next;
  return w;
}

// Hängt die Position pos *hinten* an die (nichtleere!) Positionsliste
// des Wortknotens wort an
void add_pos(pos_entry *pos, word_entry *word)
{
  word->last_pos->next = pos;
  word->last_pos = pos;
}

// Es wird mit new_pos ein frischer Positionseintrag
//   (filename/linenr/colnr) angelegt
// Dann wird das Wort word im Hash-Speicher gesucht
// Gibt es das Wort noch nicht, wird mittels new_word
// ein neuer Worteintrag erzeugt (mit dem neuen Pos-Eintrag)
// und *vorne* an die richtige Hashliste angehängt
// Gibt es das Wort schon,
// wird an dessen Positionsliste mittels add_pos der neue Pos-Eintrag angehängt
void save_word(const char *filename, int linenr, int colnr, const char *word)
{
  word_entry *w;
  pos_entry *pos;
  unsigned int h;

  // Wir brauchen in jedem Fall einen neuen Pos-Eintrag
  pos = new_pos(filename, linenr, colnr);

  h = hash(word);
  for (w = hashtable[h]; w != NULL; w = w->next) {
    if (strcmp(w->text, word) == 0) {
      add_pos(pos, w);
      return;
    }
  }

  hashtable[h] = new_word(word, pos, hashtable[h]);
}

// Ermittelt und speichert alle Worte in der Zeile line
// Achtung: line wird dabei modifiziert!
// filename und linenr sind die Position der Zeile
void read_line(const char *filename, int linenr, char *line)
{
  char *line_end;            // Zeiger auf das \0 am Zeilenende
  char *word_beg;            // Zeiger auf den ersten Char des nächsten Wortes
  char *word_end;            // Zeiger auf den ersten Char hinter dem Wort
  int colnr;                 // Spalte

  line_end = strchr(line, '\0');
  for (word_beg = line; ; word_beg = word_end) { // Ein Durchlauf pro Wort
    // Suche den ersten Buchstaben des nächsten Wortes
    for ( ; !iswordbeg(*word_beg); ++word_beg) {
      if (word_beg == line_end) {      // Am Zeilenende, nichts gefunden:
        return;                        // Die Zeile ist fertig verarbeitet
      }
    }

    // Suche den ersten Buchstaben hinter dem Wort
    for (word_end = word_beg + 1; isinword(*word_end); ++word_end) {
    }

    // Mach aus dem Wort einen einzelnen String: Schreib \0 ans Ende (Pfui!)
    *word_end = '\0';
    // Spalte = Entfernung vom Zeilenanfang (ab 1, nicht ab 0)
    colnr = (word_beg - line) + 1;
    // Speichere das Wort und seine Position
    save_word(filename, linenr, colnr, word_beg);
  }
}

// Liest und verarbeitet den angegebenen File zeilenweise
// Bricht bei zu langen Zeilen mit Fehler ab!
void read_file(const char *filename)
{
  FILE *f;
  char line[LINELEN + 2];
  int linenr;

  if ((f = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "%s: Can't open %s: %s\n", progname, filename,
            strerror(errno));
    exit(EXIT_FAILURE);
  }

  for (linenr = 1; fgets(line, sizeof (line), f); ++linenr) {
    if ((strlen(line) == sizeof(line) - 1) &&
        (line[sizeof(line) - 2] != '\n')) {
      fprintf(stderr, "%s: Line too long on %s\n", progname, filename);
      exit(EXIT_FAILURE);
    }
    read_line(filename, linenr, line);
  }

  if (ferror(f)) {
    fprintf(stderr, "%s: Can't read %s: %s\n", progname, filename,
            strerror(errno));
    exit(EXIT_FAILURE);
  }
  if (fclose(f) != 0) {
    fprintf(stderr, "%s: Can't close %s: %s\n", progname, filename,
            strerror(errno));
    exit(EXIT_FAILURE);
  }
}

// Gibt alle Positionen der Positionsliste des Wortes word aus
// Alle Positionen aus einem File werden in einer Zeile ausgegeben
// (mit dem Filenamen einmal am Zeilenanfang)
// Kommt eine Position aus einem neuen File, wird eine neue Zeile begonnen
void list_pos(const word_entry *word)
{
  const pos_entry *p;
  const char *oldfile = NULL; // Name des Files der vorigen Pos

  for (p = word->first_pos; p != NULL; p = p->next) {
    if (p->filename != oldfile) {
      oldfile = p->filename;
      printf("\n%s:", p->filename);
    }
    printf(" %u/%u", p->line, p->column);
  }

  putchar('\n');
}

// Sucht das angegebene Wort word im Hashspeicher
// Gibt das Wort und seine Positionen (mittels list_pos)
// oder "nicht gefunden" aus
void process_word(const char *word)
{
  word_entry *w;

  for (w = hashtable[hash(word)]; w != NULL; w = w->next) {
    if (strcmp(w->text, word) == 0) {
      printf("*** %s:", word);
      list_pos(w);
      return;
    }
  }

  printf("*** %s: Not found! ***\n", word);
}

// Liest und verarbeitet den Input vom Terminal (ein Wort pro Zeile!)
void process_input(void)
{
  char line[LINELEN + 2];
  char *p;

  while (fgets(line, sizeof (line), stdin)) {
    if ((p = strchr(line, '\n')) == NULL) {
      fprintf(stderr, "%s: Line too long on stdin\n", progname);
      exit(EXIT_FAILURE);
    }
    *p = '\0';   // '\n' entfernen
    process_word(line);
  }

  if (ferror(stdin)) {
    fprintf(stderr, "%s: Can't read stdin: %s\n", progname, strerror(errno));
    exit(EXIT_FAILURE);
  }
}

// Gibt Statistiken über die Hash-Verteilung aus
void statistics(void)
{
  int cnt[MAXLEN]; // Anzahl der Listen mit Länge i
  int cntmax = 0;  // Anzahl der Listen mit Länge >= MAXLEN
  int total = 0;   // Anzahl der Wortknoten
  int maxlen = 0;  // Länge der längsten Liste

  int i, len;
  word_entry *w;

  for (i = 0; i < MAXLEN; ++i) {
    cnt[i] = 0;
  }

  for (i = 0; i < HASHPRIME; ++i) {
    for (len = 0, w = hashtable[i]; w != NULL; ++len, w = w->next) {
      ++total;
    }
    if (len > maxlen) {
      maxlen = len;
    }
    if (len >= MAXLEN) {
      ++cntmax;
    } else {
      ++cnt[len];
    }
  }

  for (i = 0; i < MAXLEN; ++i) {
    if (cnt[i] > 0) {
      printf("%5d Listen mit Länge  %2d (%6.2f %%)\n", cnt[i], i,
             (cnt[i] * 100) / ((double) HASHPRIME));
    }
  }
  if (cntmax > 0) {
    printf("%5d Listen mit Länge >%2d (%6.2f %%), längste Liste %d\n", cntmax,
           MAXLEN, (cntmax * 100) / ((double) HASHPRIME), maxlen);
  }
  printf("Insgesamt %d Knoten, mittlere Listenlänge ideal %5.3f, real %5.3f\n",
         total, total / ((double) HASHPRIME), 
         total / ((double) (HASHPRIME - cnt[0])));
}

// Liest und speichert alle Worte aus allen als Argument angegebenen Files
// Liest Worte vom Terminal und gibt deren gespeicherte Position aus
int main(int argc, const char *argv[])
{
  int i;

  progname = argv[0];

  //// Files einlesen und speichern
  if (argc == 1) {
    fprintf(stderr, "Usage: %s file ...\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  for (i = 1; i < argc; ++i) {
    read_file(argv[i]);
  }

  // Statistik ausgeben
  statistics();

  //// Wörter einlesen und suchen
  process_input();

  exit(EXIT_SUCCESS);
}