#include <iostream>
#include <string>

using namespace std;

/************** Start of Family of Algorithms: Gun ****************/
//Strategy Class (Abstract)
class IGun
{
    public:
    virtual string get_gun_name() = 0;
};

//Concrete Strategy
class MachineGun : public IGun
{
    string gun_name;
    public:
    MachineGun()
    {
        gun_name = "Machine Gun";
    }
    virtual string get_gun_name()
    {
        return gun_name;
    }
};

//Concrete Strategy
class AircraftGun : public IGun
{
    string gun_name;
    public:
    AircraftGun()
    {
        gun_name = "Aircraft Gun";
    }
    virtual string get_gun_name()
    {
        return gun_name;
    }
};

//Concrete Strategy
class NoGun : public IGun
{
    string gun_name;
    public:
    NoGun()
    {
        gun_name = "Doesn't have a Special category Gun";
    }
    virtual string get_gun_name()
    {
        return gun_name;
    }
};

/************** End of Family of Algorithms: Gun ****************/

/************** Start of Family of Algorithms: Vehicle ****************/
//Strategy Class
class IVehicle
{
    public:
    virtual string getVehicle() = 0;
};

//Concrete Strategy
class Tank : public IVehicle
{
    string vehicle_name;

    public:
    Tank()
    {
        vehicle_name = "Tank";
    }
    virtual string getVehicle()
    {
        return vehicle_name;
    }

};

//Concrete Strategy
class FighterJet : public IVehicle
{
    string vehicle_name;

    public:
    FighterJet()
    {
        vehicle_name = "Fighter Jet";
    }
    virtual string getVehicle()
    {
        return vehicle_name;
    }

};

//Concrete Strategy
class Submarine : public IVehicle
{
    string vehicle_name;

    public:
    Submarine()
    {
        vehicle_name = "Submarine";
    }
    virtual string getVehicle()
    {
        return vehicle_name;
    }

};

//Concrete Strategy
class NoVehicle : public IVehicle
{
    string vehicle_name;

    public:
    NoVehicle()
    {
        vehicle_name = "No Vehicle";
    }
    virtual string getVehicle()
    {
        return vehicle_name;
    }

};

/************** End of Family of Algorithms: Vehicle ****************/

/************** Start of Client Class *****************/
//Abstract Client
class Army
{
    protected:
    IGun* gun;
    IVehicle* vehicle;
    string troop_name;

    public:
    Army()
    {
        // gun = new NoGun();
        // vehicle = new NoVehicle();
        // troop_name = "Army";
    }
    virtual string get_troop_name() = 0;
    virtual string get_gun() = 0;
    virtual string get_vehicle() = 0;
};

//Concrete Client
class GroundForce : public Army
{
    public:
    GroundForce()
    {
        gun = new MachineGun();
        vehicle = new Tank();
        troop_name = "Ground Force";
    }

    ~GroundForce()
    {
        if(gun)
        {
            delete gun;
        }

        if(vehicle)
        {
            delete vehicle;
        }
    }

    virtual string get_troop_name() override
    {
        return troop_name;
    }

    virtual string get_gun() override
    {
        return gun->get_gun_name();
    }

    virtual string get_vehicle() override
    {
        return vehicle->getVehicle();
    }

};

//Concrete Client
class Comando : public Army
{
    public:
    Comando()
    {
        // Comando is using the same Gun (Algorithm),
        // as GroundForce is also using --- (Code Reusability)
        gun = new MachineGun();

        // Comando is using the same Vehicle (Algorithm),
        // as AirForce is also using  --- (Code Reusability)
        vehicle = new FighterJet();

        troop_name = "Special Force";
    }

    ~Comando()
    {
        if(gun)
        {
            delete gun;
        }

        if(vehicle)
        {
            delete vehicle;
        }
    }

    virtual string get_troop_name() override
    {
        return troop_name;
    }

    virtual string get_gun() override
    {
        return gun->get_gun_name();
    }

    virtual string get_vehicle() override
    {
        return vehicle->getVehicle();
    }

};

//Concrete Client
class AirForce : public Army
{
    public:
    AirForce()
    {
        gun = new AircraftGun();
        vehicle = new FighterJet();
        troop_name = "Air Force";
    }

    ~AirForce()
    {
        if(gun)
        {
            delete gun;
        }

        if(vehicle)
        {
            delete vehicle;
        }
    }

    virtual string get_troop_name() override
    {
        return troop_name;
    }

    virtual string get_gun() override
    {
        return gun->get_gun_name();
    }

    virtual string get_vehicle() override
    {
        return vehicle->getVehicle();
    }
};

//Concrete Client
class Navy : public Army
{
    public:
    Navy()
    {
        // Navy is using the blank implementation of gun
        gun = new NoGun();
        vehicle = new Submarine();
        troop_name = "Naval Force";
    }

    ~Navy()
    {
        if(gun)
        {
            delete gun;
        }

        if(vehicle)
        {
            delete vehicle;
        }
    }

    virtual string get_troop_name() override
    {
        return troop_name;
    }
    
    virtual string get_gun() override
    {
        return gun->get_gun_name();
    }
    

    virtual string get_vehicle() override
    {
        return vehicle->getVehicle();
    }
};
/*************** End of Client **************/

int main()
{
    Army* a1 = new Comando();
    Army* a2 = new Navy();
    Army* a3 = new GroundForce();
    Army* a4 = new AirForce();

    cout<<"Comando"<<endl;
    cout<<"-----------------"<<endl;
    cout<<"Registered Name:\t"<<a1->get_troop_name()<<endl;
    cout<<"Special Weapon:\t\t"<<a1->get_gun()<<endl;
    cout<<"Special Vehicle:\t"<<a1->get_vehicle()<<endl;
    cout<<endl;

    cout<<"Navy"<<endl;
    cout<<"-----------------"<<endl;
    cout<<"Registered Name:\t"<<a2->get_troop_name()<<endl;
    cout<<"Special Weapon:\t\t"<<a2->get_gun()<<endl;
    cout<<"Special Vehicle:\t"<<a2->get_vehicle()<<endl;
    cout<<endl;

    cout<<"Ground Force"<<endl;
    cout<<"-----------------"<<endl;
    cout<<"Registered Name:\t"<<a3->get_troop_name()<<endl;
    cout<<"Special Weapon:\t\t"<<a3->get_gun()<<endl;
    cout<<"Special Vehicle:\t"<<a3->get_vehicle()<<endl;
    cout<<endl;

    cout<<"Air Force"<<endl;
    cout<<"-----------------"<<endl;
    cout<<"Registered Name:\t"<<a4->get_troop_name()<<endl;
    cout<<"Special Weapon:\t\t"<<a4->get_gun()<<endl;
    cout<<"Special Vehicle:\t"<<a4->get_vehicle()<<endl;
    cout<<endl;

    return 0;

}