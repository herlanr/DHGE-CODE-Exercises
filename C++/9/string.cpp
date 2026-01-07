#include <iostream>
#include <cstring>

using namespace std;

class String{

    friend ostream &operator<<(ostream &outfile, const String &string);

    private:
        char *word;
    public:
        String(int size = 0): word(new char[size+1]){
            word[0] = '\0';
        }

        String(const String &string): word(new char[strlen(string.word) + 1]){
            strcpy(word, string.word);
        }

        String(const char *string) : word(new char[strlen(string) + 1]) {
            strcpy(word, string);
        }

        ~String(){
            delete[] word;
        }

        String operator+(const String &b) const;
        bool operator==(const String &b) const;
        bool operator<(const String &b) const;
        bool operator!() const;
        String &operator=(const String &b);
        String &operator+=(const String &b);

};

String String::operator+(const String &b) const{
    String result(strlen(word) + strlen(b.word));
    strcpy(result.word, word);
    strcpy(result.word, b.word);
    return result;
}

bool String::operator==(const String &b) const{
    return strcmp(word, b.word) == 0;
}

bool String::operator<(const String &b) const
{
  return (strcmp(word, b.word) < 0);
}

bool String::operator!() const{
    return word[0] == '\0';
}

String &String::operator=(const String &b){
    if (this != &b){
        delete [] word;
        word = new char[strlen(b.word) + 1];
        strcpy(word, b.word);
    }
    return *this;
}

String &String::operator+=(const String &b){
    char *newWord = new char[strlen(word) + strlen(b.word) + 1];
    strcpy(newWord, word);
    strcpy(newWord, b.word);
    delete [] word;
    word = newWord;
    return *this;
}

ostream &operator<<(ostream &outfile, const String &string){
    outfile << string.word;
    return outfile;
}

int main(){
  String nix;
  String a = "Äpfel";
  String aa = a;
  String b = "Birnen";
  String bb;
  String k = "Kompott";
  String ab = "ÄpfelBirnen";
  String res;

  bb = b;
  res = aa + String("") + bb;

  cout << "Ist 'nix' leer? " << (!nix ? "Ja!" : "Nein???") << endl;
  cout << "'" << bb << "' sind " << (!bb ? "auch" : "nicht") << " leer." << endl;
  cout << "'" << a << "' und '" << b << "' sind " <<
      ((a == b) ? "gleich" : "verschieden") << "." << endl;
  cout << "'" << bb << "' sind " << (bb < k ? "kleiner" : "größer") <<
      " als '" << k << "'" << endl;
  cout << "'" << k << "' ist " << (k < b ? "kleiner" : "größer") <<
      " als '" << b << "'" << endl;
  cout << "'" << aa << "' plus '" << bb << "' sind '" << res << "'." << endl;
  cout << "Sind es wirklich 'ÄpfelBirnen'? " <<
      ((ab == res) ? "Ja!" : "Nein???") << endl;

  // ab hier auskommentieren, solange du noch kein += hast
  a += bb;
  a += k;
  cout << "Und jetzt gibt es '" << a << "'." << endl;

  return 0;
}