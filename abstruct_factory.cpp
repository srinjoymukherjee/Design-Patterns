#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Product1
class ICricketer
{
    public:
    virtual void setName(string name) = 0;
    virtual void setTeam(string team) = 0;
    virtual void setType(string t_type) = 0;

    virtual string getName() = 0;
    virtual string getTeam() = 0;
    virtual string getType() = 0;
};

ostream& operator<<(ostream& out, ICricketer* cricketer)
{
    out<<cricketer->getName()<<"\t";
    out<<cricketer->getTeam()<<"\t";
    out<<cricketer->getType()<<endl;

    return out;
}

//Concrete Product1
class Batsman : public ICricketer
{
    string name;
    string team;
    string type;

    public:
    Batsman(string t_name, string t_team, string t_type){
        name = t_name;
        team = t_team;
        type = t_type;
    }

    virtual void setName(string t_name) override
    {
        name = t_name;
    }
    virtual void setTeam(string t_team) override
    {
        team = t_team;
    }
    virtual void setType(string t_type) override
    {
        team = t_type;
    }

    virtual string getName() override
    {
        return name;
    }
    virtual string getTeam() override
    {
        return team;
    }
    virtual string getType() override
    {
        return type;
    }

    friend ostream& operator<<(ostream& out, Batsman* batsman);
};

//Concrete Product1
class Bowler : public ICricketer
{
    string name;
    string team;
    string type;

    public:
    Bowler(string t_name, string t_team, string t_type){
        name = t_name;
        team = t_team;
        type = t_type;
    }

    virtual void setName(string t_name) override
    {
        name = t_name;
    }
    virtual void setTeam(string t_team) override
    {
        team = t_team;
    }
    virtual void setType(string t_type) override
    {
        team = t_type;
    }

    virtual string getName() override
    {
        return name;
    }
    virtual string getTeam() override
    {
        return team;
    }
    virtual string getType() override
    {
        return type;
    }
};


//Product 2
class IUmpire
{
    public:
    virtual string getName() = 0;
    virtual string getCountry() = 0;
};

ostream& operator<<(ostream& out, IUmpire* umpire)
{
    out<<umpire->getName()<<"\t";
    out<<umpire->getCountry()<<endl;

    return out;
}

//Concrete Product2
class FieldUmpire : public IUmpire
{
    string name;
    string country;

    public:
    FieldUmpire(string t_name, string t_country){
        name = t_name;
        country = t_country;
    }

    virtual string getName(){
        return name;
    }
    virtual string getCountry(){
        return country;
    }
};

//Concrete Product2
class ThirdUmpire : public IUmpire
{
    string name;
    string country;

    public:
    ThirdUmpire(string t_name, string t_country){
        name = t_name;
        country = t_country;
    }

    virtual string getName(){
        return name;
    }
    virtual string getCountry(){
        return country;
    }
};

//Abstruct Factory
class ICricketMatch
{
    public:
    virtual ICricketer* addCricketer(string name, string team, string type, string c_type) = 0;
    virtual IUmpire* addUmpire(string name, string Country, string type) = 0;
};

//Abstruct Factory -- Concrete Implementation
class BoxingDay : public ICricketMatch
{
    public:
    BoxingDay(){}

    //Factory Method1
    virtual ICricketer* addCricketer(string name, 
                                     string team, 
                                     string type, 
                                     string c_type) 
    override
    {
        ICricketer* cricketer = nullptr;

        if(c_type == "Batsman"){
            cricketer = new Batsman(name, team, type);
        }
        else if(c_type == "Bowler"){
           cricketer = new Bowler(name, team, type);
        }

        return cricketer;
    }

    //Factory Method2
    virtual IUmpire* addUmpire(string name,
                               string country,  
                               string type) 
    override
    {
        IUmpire* umpire = nullptr;

        if(type == "Field"){
            umpire = new FieldUmpire(name, country);
        }
        else if(type == "Third"){
            umpire = new ThirdUmpire(name, country);
        }

        return umpire;
    }
};

//Client
class Match
{
    vector<ICricketer*> cricketer;
    vector<IUmpire*> umpire;

    public:
    Match(ICricketMatch* match)
    {
        cricketer.push_back(match->addCricketer("Kohli",
                                         "IND", 
                                         "Right Handed",    
                                         "Batsman"));

        cricketer.push_back(match->addCricketer("Rohit", 
                                         "IND",
                                         "Right Handed", 
                                         "Batsman"));

        cricketer.push_back(match->addCricketer("Dhawan",  
                                         "IND",
                                         "Left Handed", 
                                         "Batsman"));

        cricketer.push_back(match->addCricketer("Rahane",  
                                         "IND",
                                         "Right Handed", 
                                         "Batsman"));

        cricketer.push_back(match->addCricketer("Bumrah",  
                                         "IND",
                                         "Fast Bowler", 
                                         "Bowler"));

        cricketer.push_back(match->addCricketer("Shami",  
                                         "IND",
                                         "Fast Bowler", 
                                         "Bowler"));

        cricketer.push_back(match->addCricketer("Kuldeep",  
                                         "IND",
                                         "Fast Bowler", 
                                         "Bowler"));

        cricketer.push_back(match->addCricketer("Chwahal",  
                                         "IND",
                                         "Fast Bowler", 
                                         "Bowler"));


        umpire.push_back(match->addUmpire("Steve", "WI", "Field"));
        umpire.push_back(match->addUmpire("Bilie", "NZ", "Field"));
        umpire.push_back(match->addUmpire("Prasad", "IND", "Third"));
    }

    
    vector<ICricketer*> getCricketers()
    {
        return cricketer;
    }
    vector<IUmpire*> getUmpires()
    {
        return umpire;
    }
};

int main()
{
    ICricketMatch* boxingDayTest = new BoxingDay();
    Match* match = new Match(boxingDayTest);

    for(auto cricketer : match->getCricketers()){
        cout<<cricketer<<endl;
    }

    for(auto umpire : match->getUmpires()){
        cout<<umpire<<endl;
    }

    return 0;
}