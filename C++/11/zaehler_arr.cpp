#include <iostream>
#include <cstdlib>

using namespace std;

class Counter{

    friend ostream &operator<<(ostream &outfile, const Counter &counter);

    private:
        unsigned int size;
        int *numbers;
    public:
        Counter(unsigned int s); //ok
        ~Counter(); // ok
        Counter (const Counter &counter); // ok
        unsigned int getSize(){ return size; } //ok
        int getIndex(int index); // ok
        int operator[](unsigned int val) const { return (val < size) ? numbers[val] : 0;}
        Counter operator+(const Counter &counter) const; //ok
        Counter operator+(unsigned int value) const; //ok
        int operator~(); //ok
        bool operator<=(const Counter &counter) const;
        //nao precisa de const, vai modificiar o original
        Counter &operator=(const Counter &counter);

};

Counter::Counter(unsigned int s): size(s), numbers(new int[size]){
    for (int i = 0; i < size; i++){
        numbers[i] = 0;
    }
}

Counter::Counter(const Counter &counter): size(counter.size), numbers(new int [counter.size]){
    for (int i = 0; i < size; i++){
        numbers[i] = counter.numbers[i];
    }
}

Counter::~Counter(){
    delete[] numbers;
}

int Counter::getIndex(int index){
    if (index > size || index < 0){
        return 0;
    }

    return numbers[index];
}

Counter Counter::operator+(const Counter &counter) const{

    if(counter.size != size){
        cerr << "different size";
        exit(EXIT_FAILURE);
    }

    Counter res(size);

    for (int i = 0; i < size; i++){
        res.numbers[i] = counter.numbers[i] + numbers[i];
    }

    return res;

}

Counter Counter::operator+(unsigned int value) const
{
  // Bei einem val außerhalb unserer Länge
  // machen wir das Ergebnis entsprechend länger
  unsigned int s = max(size, value + 1);
  Counter res(s);
  for (unsigned int i = 0; i < s; ++i) {
    res.numbers[i] = (*this)[i];  // siehe Kommentar bei operator +
  }
  ++res.numbers[value];

  return res;
}

int Counter::operator~(){

    int res = 0;

    for (int i = 0; i < size; i++){
        res += numbers[i];
    }

    return res;

}
bool Counter::operator<=(const Counter &counter) const{

    if(counter.size != size){
        cerr << "different size";
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < size; i++){
        if (numbers[i] <= counter.numbers[i]){
            continue;
        } else {
            return false;
        }
    }

    return true;
}
Counter &Counter::operator=(const Counter &counter){

    if(this != &counter){
        if(size != counter.size){
            delete[] numbers;
            size = counter.size;
            numbers = new int[size];
        }

        for(int i = 0; i < size; i++){
            numbers[i] = counter.numbers[i];
        }

    }

return *this;
}

ostream &operator<<(ostream &outfile, const Counter &counter){
    for(int i = 0; i < counter.size; i++){
        if (counter.numbers[i] > 0) {   // Nur die Zähler größer 0 werden ausgegeben
             outfile << i << ':' << counter.numbers[i] << ' ';
        }
    }
    return outfile;
}

const int kugeln = 49;
const int zahlen = 6;

Counter ziehe(){

    Counter counter(kugeln);

    while(~counter < zahlen){
        int random = rand() % kugeln;
        if (counter[random] == 0){
            counter = counter + random;
        }
    }

    return counter;

}

int main(){

    srand(time(NULL));

    Counter ziehung(kugeln), gezogen(kugeln);

    int i;

    for (i = 1; ; ++i){
        ziehung = ziehe();
        if(ziehung <= gezogen) break;
        gezogen = gezogen + ziehung;
    }

    cout << i << " Runden" << endl;
    cout << ziehung << endl;
    cout << gezogen << endl;

    exit(EXIT_SUCCESS);


}