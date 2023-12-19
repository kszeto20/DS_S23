/*
animal.h - functions
*/
#include<iostream>
using std::string;

class Animal {
    public: 
        Animal();
        Animal(const string & name);

        // methods to get data
        string getName() const;
        int getWeight() const;
        bool landSurvive() const;
        bool waterSurvive() const;
        bool meatEat() const;
        bool plantEat() const;


        // modify data
        void setWeight(int w);
        void setLand(bool whether);
        void setWater(bool whether);
        void setMeat(bool whether);
        void setPlant(bool whether);

        bool omni() const;
        bool amphi() const;

    private:
    // variables of the animal
    string aName;
    int aWeight;
    bool landS;
    bool waterS;
    bool meatE;
    bool plantE;

}
