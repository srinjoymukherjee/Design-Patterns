//We are Preparing 2 types of Menu,
//Veg and Non Veg, using Builder pattern.
//Here the product is a Menu
#include <iostream>

using namespace std;

//Sub-Product1
class Starter
{
    string m_name;

    public:
    Starter(){}
    string getName(){ return m_name; }
    void setName(string name) { m_name = name; }
};

//Sub-Product2
class MainCourse
{
    string m_name;

    public:
    MainCourse(){}
    string getName(){ return m_name; } 
    void setName(string name) { m_name = name; }
};

//Product
class Menu
{
    Starter* m_starter;
    MainCourse* m_mainCourse;

    public:
    Menu(){}

    void addStarter(Starter* starter)
    {
        //Dependency Inversion
        m_starter = starter;
    }

    void addMainCourse(MainCourse* mainCourse)
    {
        //Dependency Inversion
        m_mainCourse = mainCourse;
    }

    friend ostream& operator<<(ostream& out, Menu* menu);
};

ostream& operator<<(ostream& out, Menu* menu){
    out<<menu->m_starter->getName()<<endl;
    out<<menu->m_mainCourse->getName();

    return out;
}

//Abstruct builder
class IMenuBuilder
{
    public:
    virtual void addMainCourse(string name) = 0;
    virtual void addStarter(string name) = 0;
    virtual Menu* getMenu() = 0;
};

//Concrete Builder1
class VegMenuBuilder : public IMenuBuilder
{
    Menu* vegMenu;

    public:
    VegMenuBuilder(){
        vegMenu = new Menu();
    }

    virtual void addMainCourse(string name){
        MainCourse* mainCourse = new MainCourse();
        mainCourse->setName(name);
        //Dependency Injection
        vegMenu->addMainCourse(mainCourse);
    }

    virtual void addStarter(string name){
        Starter* starter = new Starter();
        starter->setName(name);
        //Dependency Injection
        vegMenu->addStarter(starter);
    }

    virtual Menu* getMenu(){
        return this->vegMenu;
    }
};

//Concrete Builder2
class NonVegMenuBuilder : public IMenuBuilder
{
    Menu* nonVegMenu;

    public:
    NonVegMenuBuilder(){
        nonVegMenu = new Menu();
    }
    
    virtual void addMainCourse(string name){
        MainCourse* mainCourse = new MainCourse();
        mainCourse->setName(name);
        //Dependency Injection
        nonVegMenu->addMainCourse(mainCourse);
    }

    virtual void addStarter(string name){
        Starter* starter = new Starter();
        starter->setName(name);
        //Dependency Injection
        nonVegMenu->addStarter(starter);
    }

    virtual Menu* getMenu(){
        return this->nonVegMenu;
    }
};

//Director
class PrepareMenu
{
    IMenuBuilder* menuBuilder;

    public:
    PrepareMenu(string type)
    {
        if(type == "NonVeg"){
            menuBuilder = new NonVegMenuBuilder();
        }
        else if(type == "Veg"){
            menuBuilder = new VegMenuBuilder();
        }
    }

    //The API for constructing Menu
    void constructMenu(string starterName, 
                       string mainCourseName)
    {
        menuBuilder->addStarter(starterName);
        menuBuilder->addMainCourse(mainCourseName);
    }

    Menu* getMenu()
    {
        return menuBuilder->getMenu();
    }
};

int main(){
    PrepareMenu* prepVegMenu = new PrepareMenu("Veg");
    PrepareMenu* prepNonVegMenu = new PrepareMenu("NonVeg");

    prepVegMenu->constructMenu("Paneer Tikka", "Paneer Makhwani");
    prepNonVegMenu->constructMenu("Chicken Tikka", "Kadai Chicken");

    auto menu = prepVegMenu->getMenu();

    cout<<prepVegMenu->getMenu()<<endl;
    cout<<prepNonVegMenu->getMenu()<<endl;
}