// Übung zu Bäumen: Worte zählen (Grundversion)
//
// Aufruf: baum
//
// Klaus Kusche, 2018

#include <iostream>
#include <string>
// für isalpha
#include <cctype>

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

  // Alle Einträge des Baumes ausgeben
  cout << tree << endl;
  
  return 0;
}