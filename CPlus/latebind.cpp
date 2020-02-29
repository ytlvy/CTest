#include <iostream>
using namespace std;
 
class Instrument{
public:
    virtual void play() const {cout<<"Instrument::play"<<endl;}
    virtual char* what() const {return "Instrument";}
    virtual void adjust(int) {}
};
 
class Wind : public Instrument{
public:
    void play() const {cout<<"Wind::play"<<endl;}
    char* what() const {return "Wind";}
    void adjust(int) {}
};
 
class Percussion : public Instrument{
public:
    void play() const {cout<<"Percussion::play"<<endl;}
    char* what() const {return "Percussion";}
    void adjust(int) {}
};
 
class Stringed : public Instrument{
public:
    void play() const {cout<<"Stringed::play"<<endl;}
    char* what() const {return "Stringed";}
    void adjust(int) {}
};
 
class Brass : public Wind{
public:
    void play() const{cout<<"Brass::play"<<endl;}
    char* what() const {return "Brass";}
};
 
class WoodWind : public Wind{
public:
    void play() const {cout<<"WoodWind::play"<<endl;}
    char* what() const {return "WoodWind";}
};
 
void tune(Instrument& i)
{
    i.play();
}
void f(Instrument& i)
{
    i.adjust(1);
}
 
int main()
{
    Wind flute;
    Percussion drum;
    Stringed violin;
    Brass flugelhron;
    WoodWind recorder;
    tune(flute);
    tune(drum);
    tune(violin);
    tune(flugelhron);
    tune(recorder);
    f(flugelhron);

    return 0;
}