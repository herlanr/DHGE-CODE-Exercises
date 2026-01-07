//this-> und *this

class Beispiel {
private:
    int wert;

public:
    void setWert(int wert) {
        this->wert = wert;  // diferencia o parâmetro da variável da classe
    }
    
    Beispiel& aktualisiere() {
        // faz algo...
        return *this;  // retorna o próprio objeto
    }

};


