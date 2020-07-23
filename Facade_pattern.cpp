/*
We will build a Kitchen Automation system.
This is basically a Facade, which will control
all objects in the house.
*/

#include <iostream>

using namespace std;

//Subsystem1
class CoffeeMaker
{
    static CoffeeMaker* coffeemaker;
    string status;

    public:
    CoffeeMaker(){}
    static CoffeeMaker* getCoffeeMaker(){
        if(!CoffeeMaker::coffeemaker){
            coffeemaker = new CoffeeMaker();
            coffeemaker->status = "OFF";
        }

        return coffeemaker;
    }

    void switchON(){
        coffeemaker->status = "ON";
    }

    void getCoffee(){
        cout<<"Your Coffee is Ready!"<<endl;
    }

    void getTea(){
        cout<<"Your Tea is Ready!"<<endl;
    }

    void switchOFF(){
        coffeemaker->status = "OFF";
    }
};

CoffeeMaker* CoffeeMaker::coffeemaker = nullptr;

//Subsystem2
class SandwitchMaker
{
    static SandwitchMaker* sandwitchMaker;
    string status;
    public:
    SandwitchMaker(){}
    static SandwitchMaker* getSandwitchMaker(){
        if(!sandwitchMaker){
            sandwitchMaker = new SandwitchMaker();
            sandwitchMaker->status = "OFF";
        }

        return sandwitchMaker;
    }

    void switchON(){
        sandwitchMaker->status = "ON";
    }

    void getSandwitch(){
        cout<<"Your Sandwitch is Ready!"<<endl;
    }

    void switchOFF(){
        sandwitchMaker->status = "OFF";
    }
};

SandwitchMaker* SandwitchMaker::sandwitchMaker = nullptr;

//Subsystem3
class Refrigerator
{
    static Refrigerator* refrigerator;
    string status;

    public:
    Refrigerator(){}

    static Refrigerator* getRefrigerator(){
        if(!refrigerator){
            refrigerator = new Refrigerator();
            refrigerator->status = "OFF";
        }

        return refrigerator;
    }

    void switchON(){
        refrigerator->status = "ON";
        cout<<"your Refrigerator is switched ON"<<endl;
    }

    void switchOFF(){
        refrigerator->status = "OFF";
        cout<<"your Refrigerator is switched OFF"<<endl;
    }
};

Refrigerator* Refrigerator::refrigerator = nullptr;

//Facade
class Kitchen
{
    CoffeeMaker* coffeeMaker;
    SandwitchMaker* sandwitchMaker;
    Refrigerator* refrigerator;

    public:
    Kitchen(){
        coffeeMaker = CoffeeMaker::getCoffeeMaker();
        sandwitchMaker = SandwitchMaker::getSandwitchMaker();
        refrigerator = Refrigerator::getRefrigerator();
    }

    void makeCoffee(){
        coffeeMaker->switchON();
        coffeeMaker->getCoffee();
        coffeeMaker->switchOFF();
    }

    void makeTea(){
        coffeeMaker->switchON();
        coffeeMaker->getTea();
        coffeeMaker->switchOFF();
    }

    void makeSandwitch(){
        sandwitchMaker->switchON();
        sandwitchMaker->getSandwitch();
        sandwitchMaker->switchOFF();
    }

    void switchONRefrigerator(){
        refrigerator->switchON();
    }

    void switchOFFRefrigerator(){
        refrigerator->switchOFF();
    }
};

int main(){
    Kitchen* kitchen = new Kitchen();
    kitchen->makeCoffee();
    kitchen->makeSandwitch();
    kitchen->switchONRefrigerator();
    kitchen->makeTea();
    kitchen->switchOFFRefrigerator();

    return 0;
}