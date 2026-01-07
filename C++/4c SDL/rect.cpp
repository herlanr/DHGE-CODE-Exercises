#include "sdlinterf.h"
#include "rect.h"

#include <algorithm>

using namespace std;

//Implementierung Copy Constructor mit Initialisierungsliste
//mRGB(), mX(), mY() chamam o construtor, não é nenhum Zuweisung...
Rect::Rect(const Rect& orig): 
    mRGB(max(0, orig.mRGB.getR() - 5),
         max(0, orig.mRGB.getG() - 5),
         max(0, orig.mRGB.getB() - 5)),
  mX(orig.mX), mY(orig.mY),
  mW(max(1, orig.mW - 3)), mH(max(1, orig.mH - 3)),
  mSX(orig.mSX), mSY(orig.mSY)
{
  
}

// Wenn man Methoden außerhalb des class deklariert,
// muss man den Klassennamen mit :: davorschreiben,
// damit der Compiler weiß, zu welcher Klasse die Methodendefinition gehört
// (weil es ja mehrere Methoden mit gleichem Namen *und* gleichen Parametern
// in mehreren verschiedenen Klassen geben dürfte!):
// "das ist die Methode setPos der Klasse Point"
void Rect::setPos(int x, int y)
{
  undraw();  // Lösch den eigenen Punkt an der alten Position weg
  mX = x;    // ... speichere die neuen Koordinaten im eigenen Punkt
  mY = y;
  draw();    // ... und zeichne ihn dort neu
}

// analog zu setPos: 
// Weglöschen, Verschiebung zur internen Position addieren, neu zeichnen
void Rect::move(int dx, int dy)
{
  undraw();
  mX += dx;
  mY += dy;
  draw();
}
  
bool Rect::fly(bool bounce)
{
  bool ret = true;
  // Die Ursprungs-Koordinaten (0/0) des SDL-Fensters sind links oben
  // ==> x wächst nach rechts von 0 bis SDL_X_SIZE - 1
  // ==> y wächst nach unten von 0 bis SDL_Y_SIZE - 1
  // Prüfung auf Rand in waagrechter Richtung (x-Richtung): Rand, wenn ...
  // ... der Punkt nach rechts fliegt (mSX > 0) 
  //     und weniger als mSX vom rechten Rand (SDL_X_SIZE) entfernt ist
  // ... oder der Punkt nach links fliegt (mSX < 0)
  //     und weniger als mSX (-mSX weil mSX < 0) vom linken Rand (0) weg ist
  if (((mSX > 0) && (mX >= SDL_X_SIZE - mSX - mW)) ||
      ((mSX < 0) && (mX < -mSX +mW))) {
    // Punkt würde in x-Richtung rausfliegen
    if (bounce) {
      // Vorzeichen der x-Richtung umdrehen ==> Punkt fliegt in Gegenrichtung
      mSX = -mSX;
      ret = false;
    }
    else {
      // nicht fliegen!
      return false;
    }
  }
  // dieselbe Prüfung für die y-Position des Punktes:
  // fliegt nach unten ==> mindestens mSY Abstand vom unteren Rand (SDL_Y_SIZE)
  // fliegt nach oben ==> mindestens -mSY Abstand vom oberen Rand (0)
  if (((mSY > 0) && (mY >= SDL_Y_SIZE - mSY - mH)) ||
      ((mSY < 0) && (mY < -mSY + mH))) {
    if (bounce) {
      mSY = -mSY;
      ret = false;
    }
    else {
      return false;
    }
  }

  move(mSX, mSY);
  return ret;
}

void Rect::draw()
{
  // Zeichne für das eigene Punkt-Objekt ein Pixel im Grafik-Fenster:
  // * Die Koordinaten sind die,
  //   die im eigenen Punkt-Objekt als Member gespeichert sind.
  // * Die Farb-Werte bekommt man, indem man aus dem eigenen Farb-Member mRGB
  //   (einem Objekt!) dessen rot / grün / blau-Werte mittels get-Methode liest
  //   (weil der direkte Zugriff auf die Farb-Member nicht erlaubt ist)
  sdlDrawRect(mX, mY, mW, mH, mRGB.getR(), mRGB.getG(), mRGB.getB());
}

void Rect::undraw()
{
  // Weglöschen: Zeichne an der aktuellen eigenen Position ein schwarzes Pixel.
  sdlDrawRect(mX, mY, mW, mH, 0, 0, 0);
}

void Rect::setSize(int h, int w){
  undraw();
  mH = h;
  mW = w;
  draw();
}

void Rect::scale(int percentX, int percentY){
  undraw();
  mH = (mH * percentY) / 100;
  mW = (mW * percentX) / 100;
  draw();
}
