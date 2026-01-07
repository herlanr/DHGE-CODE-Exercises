// Klassen für Zahlenlose
//
// Aufruf: lose
//
// Klaus Kusche, 2016

#include <iostream>                                                      
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;                                                     

// Achtung:
// Das funktioniert unter Linux,
// weil rand() eine Zahl 0...2147483647 liefert.
// Unter Windows werden nie 6- oder 7-stellige Zahlen gezogen,
// weil rand() nur Zahlen 0...32767 liefern kann.
// Unter Windows sollte man daher
// anzZiffern = 4 und maxZahl = 9999 einstellen
// (und die Zahlen unten im main anpassen!)
const int anzZiffern = 7;                                                
const int maxZahl = 9999999;

class Los                                                                
{
  public:                                                                
    Los(string kunde) :                                                  
      mKunde(kunde), mLosNr(++sAktNr)                                    
    {}                                                                   

    virtual ~Los() {}                                                   

    virtual int gewinnRang() = 0;                                    

  protected:                                                             
    string mKunde;                                                       
    int mLosNr;                                                         

  private:                                                               
    static int sAktNr;                                                   
};

int Los::sAktNr = 0;                                                     

class ZahlenLos: public Los                                              
{
  public:                                                                
    ZahlenLos(string kunde, int zahl) :                                  
      Los(kunde), mZahl(zahl)                                            
    {}                                                                 

    virtual int gewinnRang()                                         
    {
      int t1, t2, anz;                                                  

      t1 = mZahl; t2 = gezZahl;                                          
      anz = 0;
      // gewinnRang = Anzahl übereinstimmender Ziffern
      // ==> ziffernweiser Vergleich von t1 und t2                                                           
      for (int i = 0; i < anzZiffern; ++i) {
        // In jedem Durchgang:
        // Hinterste Ziffer vergleichen und dann wegdividieren
        if (t1 % 10 == t2 % 10) {                                        
          ++anz;                                                         
        }
        t1 /= 10; t2 /= 10;                                              
      }

      return anz;                                                        
    }

    // mach eine Ziehung (klassenweite Methode, nicht für ein bestimmtes Los)
    static void Ziehung()                                            
    {
      gezZahl = rand() % (maxZahl + 1);
    }

  protected:                                                             
    int mZahl;            // Zahl, auf die das Los wettet                                                        

    static int gezZahl;   // bei der letzten Ziehung gezogene Zahl
                          // (für alle Lose gemeinsam = klassenweit)                
};

int ZahlenLos::gezZahl;                                                  

class ZahlenLosStat: public ZahlenLos                                    
{
  public:                                                                
    ZahlenLosStat(string kunde, int zahl) :                              
      ZahlenLos(kunde, zahl), mZiehungen(0)                              
    {
      for (int i = 0; i <= anzZiffern; ++i) {                            
        mRang[i] = 0;                                                    
      }
    }

    virtual int gewinnRang()                                         
    {
      int r;                                                             
      r = ZahlenLos::gewinnRang();                                       
      ++mZiehungen;                                                      
      ++mRang[r];                                                        
      return r;                                                          
    }

    ~ZahlenLosStat()                                                     
    {
      cout << "Los " << mLosNr << " (" << mKunde << ") = "               
           << mZahl << ", " << mZiehungen << " Runden:\n";
      for (int i = 0; i <= anzZiffern; ++i) {                            
        cout << i << ":" << mRang[i] << " ";                             
      }
      cout << endl;                                                      
    }

  private:                                                               
    int mZiehungen;                                                      
    int mRang[anzZiffern + 1];                                           
};

int main()                                                           
{
  Los *z1, *z2;                                                          

  srand(time(nullptr));                                                     
  
  z1 = new ZahlenLosStat("franz", 1234567);                              
  z2 = new ZahlenLosStat("xaver", 6666666);
                              
  for (int i = 0; i < 1000000; ++i) {                                    
    ZahlenLos::Ziehung();                                                
    z1->gewinnRang();                                                    
    z2->gewinnRang();                                                    
  }

  // damit die Statistiken ausgegeben werden
  delete z1;                                                             
  delete z2;

  exit(EXIT_SUCCESS);                                                    
}