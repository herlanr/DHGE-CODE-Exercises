#ifndef _RECT_H
#define _RECT_H

#include "color.h"

class Rect
{
  public:
    // Konstruktor wie oben: Lege einen neuen Punkt an und merke dir
    // seine Farbe, Position und Fluggeschwindigkeit in seinen Membern.
    // Objekte (hier: color) werden normalerweise
    // wenn möglich als Referenz übergeben!
    // Die Fluggeschwindigkeit kann man beim Aufruf weglassen,
    // dann wird 0 als Fluggeschwindigkeit gespeichert
    Rect(const Color &color, int x, int y, int w, int h, int sx = 0, int sy = 0):
    mRGB(color), mX(x), mY(y), mW(w), mH(h), mSX(sx), mSY(sy)
    {
      draw();             // Zeichne den Punkt gleich beim Anlegen des Objektes.
    }
    // Destruktor:
    // Lösche den angezeigten Punkt beim Freigeben des Objektes vom Bildschirm
    ~Rect() { undraw(); }

    // get-Methoden wie oben
    Color getColor() const { return mRGB; }
    int getX() const { return mX; }
    int getY() const { return mY; }
    int getH() const { return mH; }
    int getW() const { return mW; }
    int getSX() const { return mSX; }
    int getSY() const { return mSY; }

    void setSize(int h, int w);

    void scale(int percentX, int percentY);

    // eine set-Methode, die ein neues Farb-Objekt im Punkt speichert
    // (und ihn auch gleich frisch zeichnet).
    void setColor(const Color &color)
    {
      mRGB = color;
      draw();         // das ist dasselbe wie this->draw();
                      // d.h. ruft draw für den eigenen Punkt auf
    }

    // ändere die Flugrichtung bzw. Flugeschwindigkeit
    void setSpeed(int sx, int sy)
    {
      mSX = sx; mSY = sy;
    }
    
    // Der Code für die folgenden Methoden steht nicht im class,
    // sondern unten separat (==> wird nicht inline übersetzt)
    
    // Setze den Punkt an die angegebene Position
    void setPos(int x, int y);
    // Verschiebe den Punkt um die angegebene Anzahl von Pixeln
    void move(int dx, int dy);

    // Lass den Punkt gemäß seinem mSX und mSY einen Schritt fliegen
    // Wenn bounce true ist, wird der Punkt vom Rand zurückgeworfen
    // Wenn es false ist, bleibt der Punkt stehen, wenn er über den Rand käme
    // Returnwert: true wenn der Punkt normal geflogen ist
    // false wenn er am Rand ansteht bzw. abgeprallt ist
    bool fly(bool bounce = false);

    // Zeichne den eigenen Punkt
    void draw();
    // ... und lösche ihn wieder weg
    // (zeichne an Stelle des Punktes ein schwarzes Pixel).
    void undraw();

  private:
    Color mRGB;  // Jedes Punkt-Objekt enthält ein Farb-Objekt als Member
                 // (wirklich das Farb-Objekt selbst,
                 // nicht eine Referenz oder einen Pointer
                 // auf ein anderswo gespeichertes Objekt).
    int mX, mY;  // Jedes Punkt-Objekt merkt sich seine x- und y-Koordinate
    int mW, mH;
    int mSX, mSY;  // "SpeedX" und "SpeedY": Um wie viele Pixel 
                   // bewegt sich der Punkt bei jedem "fly()"?
};

#endif
