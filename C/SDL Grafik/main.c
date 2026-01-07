// Kleines Grafik-Demo-Beispiel: Diagonale Linien, Ellipsen...
//
// Aufruf: demo2
//
// Klaus Kusche, 2010

#include "sdlinterf.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  double x;
  double y;
}punkt;

typedef struct {
  double wert;
  double min_wert;
  double max_wert;
  double schritt;
}koeff;

typedef struct {
  int proz_rot;
  int proz_gruen;
  int proz_blau;
  int dazu_rot;
  int dazu_gruen;
  int dazu_blau;
}farbinfo;

#include "ifs-daten-header/farn.h"

punkt punkte[ANZAHL];

int main(void)
{

  srand(time(NULL));

  sdlInit();       // mach das Grafik-Fenster auf

  double xmin = -1e300;
  double xmax = 1e300;
  double ymin = -1e300;
  double ymax = 1e300;

  punkte[0].x = 0;
  punkte[0].y = 0; 

  for(int i = 1; i < ANZAHL; ++i){
    
    int r = rand() % 100;
    int n;

    for(n = 0; r >= prozent[n]; ++n){

    }

    punkte[i].x = c[n][0].wert * punkte[i-1].x + c[n][1].wert * punkte[i-1].y + c[n][2].wert;
    punkte[i].y = c[n][3].wert * punkte[i-1].x + c[n][4].wert * punkte[i-1].y + c[n][5].wert;

    int x = punkte[i].x;
    int y = punkte[i].y;

    if (i >= ERSTER){

      if(x > xmax){
        xmax = x;
      } 
      
      if (x < xmin){
        xmin = x;
      } 
      
      if (y > ymax){
        ymax = y;
      }
      
      if (y < ymin){
        ymin = y;
      }
    }

  }

  for (int i = ERSTER; i < ANZAHL; ++i) {
    sdlDrawPoint(((punkte[i].x - xmin) / (xmax - xmin)) * (SDL_X_SIZE - 1),
                 (1 - (punkte[i].y - ymin) / (ymax - ymin)) * (SDL_Y_SIZE - 1),
                 0, 255, 0);
  }

  sdlUpdate();
  // "ewig" anzeigen, dabei alle 100 ms auf "beenden" prüfen
  for (;;) sdlMilliSleep(100);
  
  sdlExit();       // mach das Grafikfenster wieder zu

  exit(EXIT_SUCCESS);
}