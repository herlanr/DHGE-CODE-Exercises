// Erstes C++: Geom. Objekte: Punkt
//
// Aufruf: point
//
// Klaus Kusche, 2020

// Die C++-Version von stdlib.h (u.a. für exit(...) )
#include <cstdlib>
// Wir haben kein Terminal-I/O, daher brauchen wir <iostream> nicht.

// Der Header für meine Grafik-Funktionen
// Im selben Verzeichnis wie der aktuelle File, daher "", nicht <>
#include "sdlinterf.h"

#include "rect.h"

//für srand
#include <ctime>

const int OBJEKT_ANZAHL = 50;

// damit wir die Funktionen aus <cstdlib> ohne std::... aufrufen können
using namespace std;

inline int randPM(int n){
  return ((rand() % n) + 1) - ((rand() % 2) * (n + 1));
}

int main(void)
{

  Rect* elemente[OBJEKT_ANZAHL];

  for(int i = 0; i < OBJEKT_ANZAHL; ++i){
    Color c(rand() % 255, rand() % 255, rand() % 255);
    elemente[i] = new Rect(c, SDL_X_SIZE/2, SDL_Y_SIZE/2, 
      rand() % 30 + 1, rand() % 30 + 1, randPM(10), randPM(10));
  }

  srand(time(NULL));
  sdlInit();  // Grafik-Fenster aufmachen

  // Hier braucht man eigene { } um die Punkt-Variablen,
  // damit die Punkt-Objekte am Ende der { }
  // wieder automatisch freigegeben werden,
  // *bevor* die SDL mit sdlExit abgedreht wird
  // (sonst würde der Destruktor des Punktes p am Programmende versuchen,
  // den Punkt mit undraw() zu löschen, obwohl das Grafik-Fenster schon weg ist
  // ==> Absturz!)
  { 

    for (int n = OBJEKT_ANZAHL; n > 0; ) {
      sdlMilliSleep(20);   // "Bremse"
      for(int i = 0; i < OBJEKT_ANZAHL; ++i){
        if(elemente[i] == nullptr){
          continue;
        } else {
          if(!elemente[i]->fly(true)){
            elemente[i]->scale(90, 90);
            if(elemente[i]->getW() == 0 || elemente[i]->getH() == 0){
              delete elemente[i];
              elemente[i] = nullptr;
              --n;
            }
          }
        }
      }
                      // für das Point-Objekt p
      sdlUpdate();    // die von fly intern ausgeführten Grafik-Operationen
                      // wirklich auf dem Bildschirm an zeigen
    } 
  }

  sdlExit();  // Grafik-Fenster zumachen

  exit(EXIT_SUCCESS);
}
