// Übung zu Bäumen: Worte zählen (Grundversion + Statistik + grafische Ausgabe)
//
// Aufruf: baum-stat
//
// Klaus Kusche, 2018

#include <iostream>
#include <string>
// für isalpha
#include <cctype>
// für max
#include <algorithm>

using namespace std;

// Klasse für einen Baumknoten
class Node
{
  // "Node" soll nur innerhalb von "Tree" verwendbar sein
  // wir machen daher alles in Node privat (==> keiner kann darauf zugreifen)
  // und erklären Tree zum Freund (==> aber Tree darf alles)
  friend class Tree;
  // die Ausgabe-Operatoren müssen auch auf die Member zugreifen können,
  // gehören aber zu keiner Klasse
  // wir schreiben gleich zwei Ausgabe-Operatoren:
  // einen für ein Knoten-Objekt, der nur diesen einen Knoten ausgibt
  friend ostream &operator<<(ostream &outfile, const Node &nodeObj);
  // ... und einen für einen Knoten-Pointer,
  // der den gesamten (Teil-) Baum ab diesem Knoten ausgibt
  // (bzw. nichts ausgibt, wenn er als Pointer den nullptr bekommt)
  friend ostream &operator<<(ostream &outfile, const Node *node);

  private:
    // Konstruktor:
    // Im neuen Knoten wird das angegebene Wort gespeichert
    // und die Anzahl seiner Vorkommen auf 1 gesetzt
    // Bei Binärbäumen werden neue Knoten immer als Blätter eingefügt,
    // daher haben neue Knoten beim Anlegen nie Söhne
    Node(const string &w) : word(w), cnt(1), left(nullptr), right(nullptr) {}
    // Baumknoten soll man weder kopieren noch zuweisen können,
    // nur die Pointer darauf werden kopiert und zugewiesen
    Node(const Node &node) = delete;  
    Node &operator=(const Node &node) = delete;  

    const string word;    // Nutzdaten: Ein Wort (nachträglich nicht änderbar!)
    int cnt;              // ... und die Anzahl seiner Vorkommen
    Node *left, *right;   // Pointer auf die Söhne
};

// Klasse für einen Baum
class Tree
{
  // wir erlauben dem Ausgabe-Operator für Bäume den Zugriff auf "root"
  friend ostream &operator<<(ostream &outfile, const Tree &tree);

  public:
    // Konstruktor:
    // Ein neuer Baum hat noch keine Knoten
    Tree() : root(nullptr) {}
    // Vorläufig sind unsere Bäume nicht als Ganzes kopierbar
    Tree(const Tree &orig) = delete;  
    // Destruktor: Alle Knoten des Baumes rekursiv löschen
    ~Tree() {
      delRec(root);
    }
    // Die Zuweisung ganzer Bäume (würde Kopieren erfordern) ist auch verboten
    Tree &operator=(const Tree &tree) = delete;

    // zähle das Wort "word":
    // Wenn es schon im Baum vorhanden ist, erhöhe seinen Zähler um 1
    // sonst füge einen neuen Knoten für word in den Baum ein
    void count(const string &word) {
      if (root == nullptr) {
        // der Baum ist bisher leer
        // ==> neuen Knoten erzeugen, er wird neue Wurzel
        root = new Node(word);
      } else {
        Node *ptr;  // der Knoten, den wir uns gerade anschauen
        ptr = root; // oben mit der Wurzel anfangen
        for (;;) {  // und den Baum durchlaufen
          if (ptr->word < word) {
            // zu zählendes Wort muss rechts vom aktuellen Knoten sein
            if (ptr->right == nullptr) {
              // rechts gibt es noch keine Knoten
              // ==> neuen Knoten erzeugen
              // ... und rechts an den aktuellen Knoten hängen
              ptr->right = new Node(word);
              return;  // fertig!
            } else {
              // im nächsten Schleifendurchlauf beim rechten Sohn weitersuchen
              ptr = ptr->right;  
            }
          } else if (ptr->word > word) {
            // dasselbe für links
            if (ptr->left == nullptr) {
              ptr->left = new Node(word);
              return;
            } else {
              ptr = ptr->left;
            }
          } else {
            // ptr->word == word: Wort ist schon im Baum, ptr zeigt darauf
            // Zählerstand erhöhen
            ++(ptr->cnt);
            return;  // fertig!
          }
        } 
      }
    }

    // Anzahl der Knoten im Baum: Rekursive Hilfsfunktion aufrufen
    int size() const { return recSize(root); }

    // Berechnung und Ausgabe der Tiefen-Statistiken
    void statistics() const {
      // in dieser Funktion gilt:
      // der leere Baum hat Tiefe 0,
      // die Wurzel ist auf Tiefe 1,
      // ihre Söhne auf Tiefe 2 usw.

      int total = recSize(root);         // Gesamtzahl der Knoten
      int maxDepth = getMaxDepth(root);  // Tiefe des tiefsten Knotens
      // Array zum Zählen der Anzahl der Knoten pro Ebene
      // Achtung:
      // Lokale Arrays mit variabler Größe sind in C++ offiziell verboten
      // ==> Array dynamisch statt lokal anlegen
      int *depthArr = new int[maxDepth];

      // Anzahl aller Ebenen auf 0 setzen
      for (int d = 0; d < maxDepth; ++d) {
        depthArr[d] = 0;
      }
      // ... mit rekursiver Funktion befüllen
      depthCnt(root, depthArr, 0);
      // ... und ausgeben
      for (int d = 0; d < maxDepth; ++d) {
        // Array-Index d entspricht Tiefe d + 1
        cout << "Tiefe " << d + 1 << ": " << depthArr[d] << " Knoten ("
             << 100 * depthArr[d] / double(total) << "%)" << endl;
      }

      // berechne die mittlere Tiefe aller Knoten
      int depthSum = 0;
      for (int d = 0; d < maxDepth; ++d) {
        // summiere über alle Ebenen:
        // Anzahl der Knoten auf dieser Ebene * Tiefe der Ebene
        depthSum += depthArr[d] * (d + 1);
      }
      // 1. Vermeide Division durch 0 bei leerem Baum!
      // 2. Erzwinge double-Division statt int-Division
      double avgDepth = (total == 0) ? 0 : (depthSum / double(total));

      cout << "Max. Tiefe " << maxDepth
           << ", mittlere Tiefe " << avgDepth << endl
           << "(optimale mittlere Tiefe: " << optDepth(total) << ")" << endl;

      delete [] depthArr;
    }

    // gesamten Baum grafisch ausgeben
    void printTree() const {
      // rekursiv, beginnend mit der Wurzel und leerer Einrückung
      printRec(root, false, "");
    }

  private:
    Node *root;  // Zeiger auf die Wurzel (den obersten Knoten)

    // alle rekursiven Hilfsfunktionen
    // werden mit einem Pointer auf den zu bearbeitenden Teilbaum aufgerufen
    // ==> sie brauchen weder "root",
    // noch rufen sie eine Methode für den ganzen Baum auf
    // ==> sie brauchen kein "this"
    // ==> aus Performance-Gründen "static" deklarieren!

    // rekursive Baum-Lösch-Funktion:
    // löscht den Knoten node und alle Knoten in seinen Unterbäumen
    static void delRec(Node *node) {
      if (node != nullptr) {
        delRec(node->left);
        delRec(node->right);
        delete node;        // Knoten erst nach seinen Unterbäumen löschen!
      }
    }

    // rekursive Hilfsfunktion zum Knoten zählen
    static int recSize(const Node *node) {
      if (node == nullptr) {
        // ein leerer (Teil-) Baum hat 0 Knoten
        return 0;
      }
      // sonst: 1 für den eigenen Knoten + Anzahl der Knoten in den Unterbäumen
      return 1 + recSize(node->left) + recSize(node->right);
    }

    // Statistiken: Rekursive Hilfsfunktion zur Berechnung der max. Baum-Tiefe
    static int getMaxDepth(const Node *node) {
      if (node == nullptr) {
        // ein leerer Baum hat Tiefe 0
        return 0;  
      }
      // sonst: 1 für die aktuelle Ebene + größere der beiden Unterbaum-Tiefen
      return 1 + max(getMaxDepth(node->left), getMaxDepth(node->right));
    }

    // Statistiken: Rekursive Hilfsfunktion zur Zählung der Knoten pro Ebene
    // arrIndex ist der Index der aktuellen Ebene (von node) im Zähler-Array arr
    static void depthCnt(const Node *node, int arr[], int arrIndex) {
      if (node == nullptr) {
        return;  // aktueller Teilbaum ist leer: nichts zu zählen 
      }
      ++(arr[arrIndex]);  // zähle den aktuellen Knoten auf der aktuellen Ebene
      // zähle die beiden Unterbäume beginnend ab der nächsten Ebene
      depthCnt(node->left, arr, arrIndex + 1);
      depthCnt(node->right, arr, arrIndex + 1);
    }

    // Statistiken:
    // Berechne als Vergleichswert die mittlere Tiefe
    // eines optimalen (= möglichst flachen) Baumes mit "total" vielen Knoten
    // Optimaler Baum:
    // alle Ebenen von oben beginnend komplett gefüllt
    // (Knotenanzahl pro Ebene = aufsteigende Zweierpotenz)
    // nur unterste Ebene teilweise gefüllt
    // (mit so vielen Knoten wie nach den oberen Ebenen übriggeblieben)
    static double optDepth(int total) {
      if (total == 0) {
        return 0;  // der optimale Baum ohne Knoten hat Tiefe 0
      }
      int toCnt = total;  // noch verbliebene zu zählende Knoten
      int depth = 1;      // aktuelle Tiefe
      // Aufsteigende Zweierpotenz:
      // Maximal mögliche Anzahl der Knoten auf der aktuellen Ebene
      int pow2 = 1;       
      int depthSum = 0;  // Summe von Knotenanzahl * Knotentiefe
      // die Schleife kümmert sich um alle voll besetzten Ebenen:
      // solange noch mindestens so viele Knoten übrig sind,
      // wie die nächste Ebene maximal enthalten kann
      while (toCnt >= pow2) {
        depthSum += pow2 * depth;  // pow2 viele Knoten (*Ebene) zur Summe dazu
        toCnt -= pow2;             // ... und von den noch offenen Knoten weg
        pow2 *= 2;                 // nächste Ebene hat doppelt so viele Knoten
        ++depth;                   // ... und liegt um 1 tiefer
      }
      // verbleibende Knotenanzahl auf der untersten Ebene dazuzählen
      depthSum += toCnt * depth;
      // Mittelwert = Tiefensumme / Knotenanzahl, als Komma-Rechnung
      return depthSum / double(total);
    }

    // Hilfsfunktion für printTree:
    // Gib den (Teil-) Baum mit der Wurzel node zeilenweise aus
    // und zwar grafisch als liegender Baum mit der Wurzel links
    // below...ist dieser Teilbaum grafisch über oder unter seinem Vater-Knoten?
    // prefix...Einrückungs-Text vorne in jeder Zeile dieses Teilbaumes
    static void printRec(const Node *node, bool below, const string &prefix) {
      if (node == nullptr) {
        return;   // Baum ist leer ==> nichts auszugeben
      }
      if (prefix.length() > 70) {
        // Einrückung ist zu lang, d.h. Baum zu tief
        // ==> gib nur ... statt den Knoten des Teilbaumes aus
        cout << prefix << "+--..." << endl;
        return;
      }
      // unser linker Unterbaum kommt grafisch gesehen oben,
      // mit mehr Einrückung als der eigene Baum
      // Wenn wir unterhalb des Vaters gezeichnet werden,
      // wird in der Einrückung ein Strich gezeichnet
      // für die Verbindung vom Vater zur Wurzel dieses Teilbaumes
      printRec(node->left, false, prefix + (below ? "|  " : "   "));
      // dann kommt die Wurzel unseres Teilbaums
  const char *pref2;
  if (prefix.empty()) { pref2 = "---"; }
  else if (below) { pref2 = "\\--"; }
  else { pref2 = "/--"; }
  cout << prefix << pref2 << *node << endl;
      // und dann kommt unser rechter Unterbaum, wieder eingerückt
      // mit dem Strich nur dann, wenn wir oberhalb des Vaters sind
      printRec(node->right, true, prefix +
               (below || prefix.empty() ? "   " : "|  "));
    }
};

// Ausgabe-Operator für den einzelnen Knoten nodeObj (*kein* Pointer):
// Gibt "wort: anzahl" aus
ostream &operator<<(ostream &outfile, const Node &nodeObj)
{
  outfile << nodeObj.word << ": " << nodeObj.cnt;
  return outfile;
}

// Ausgabe-Operator für den (Teil-) Baum mit Wurzel node:
// Zeilenweise, sortierte Ausgabe des gesamten Baumes
ostream &operator<<(ostream &outfile, const Node *node)
{
  if (node != nullptr) {  // bei nullptr: Nicht zugreifen, nichts ausgeben!
    // Ausgabe in sortierter Reihenfolge:
    // Zuerst rekursiv den linken Unterbaum
    outfile << node->left;
    // ... dann die Wurzel unseres Teilbaumes (Achtung: Nicht den Pointer!) ...
    outfile << *node << endl;
    // ... und dann rekursiv den rechten Unterbaum
    outfile << node->right;
  }
  return outfile;
}

// Ausgabe-Operator für ein Tree-Objekt
ostream &operator<<(ostream &outfile, const Tree &tree)
{
  // Ausgabe für die Wurzel aufrufen
  outfile << tree.root;
  return outfile;
}

// Hilfsfunktion für main:
// Lies ein Wort (= Folge von Buchstaben) und speichere es in str
// Returnwert true bei Erfolg, false bei Dateiende oder Fehler
bool getword(string &str)
{
  char c;

  str.clear();             // str auf leer setzen
  while (cin.get(c)) {     // zeichenweise lesen bis EOF oder Fehler
    if (isalpha(c)) {      // Das Zeichen c ist ein Buchstabe (a bis z, A bis Z)
      str += c;            // ==> hänge den Buchstaben an das Ergebnis-Wort an
    } else {               // c ist kein Buchstabe
      if (!str.empty()) {  // wir hatten davor schon Buchstaben
                           // ==> das aktuelle Zeichen ist das Ende des Wortes
        return true;       // bisher gelesenes Wort zurückgeben, Erfolg
      }
      // else: Gelesenes Zeichen ist Nicht-Buchstabe *vor* dem zu lesenden Wort
      // ==> Zeichen ignorieren, weiterlesen bis ein Buchstabe kommt
    }
  }
  // Hierher kommen wir nur bei EOF oder Fehler
  // Wenn davor schon Buchstaben gelesen wurden ==> Erfolg
  // Wenn das Ergebnis noch leer ist ==> Fehler
  return !str.empty();
}

int main()
{
  Tree tree;
  string str;

  // Worte lesen und zählen bzw. im Baum speichern, bis kein Wort mehr kommt
  while (getword(str)) {
    tree.count(str);
  }

  // Alle Einträge des Baumes + seine Größe ausgeben
  cout << tree << endl;
  cout << "Insgesamt " << tree.size() << " verschiedene Worte" << endl << endl;

  // Baum grafisch ausgeben
  tree.printTree();
  cout << endl;

  // Tiefen-Statistiken ausgeben
  tree.statistics();  
  
  return 0;
}