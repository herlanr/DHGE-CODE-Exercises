//abstract classes ... rein virtuelle methoden

class Form {
public:
    virtual double flaeche() const = 0;  // rein virtuell
};

class Kreis : public Form {
private:
    double radius;
public:
    Kreis(double r) : radius(r) {}
    double flaeche() const override {
        return 3.1415 * radius * radius;
    }
};