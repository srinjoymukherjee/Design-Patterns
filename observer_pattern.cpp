/***********************************************************
 * 
 *  Implementation of Observer Pattern
 * 
 **********************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Observer Interface
class IObserver
{
    public:
    virtual void update() = 0;
    virtual void display() = 0;
};

// Subject Interface
class IWeatherForecast
{
    public:
    virtual void register_observer(IObserver*) = 0;
    virtual void delete_observer(IObserver*) = 0;
    virtual void notify_observers() = 0;
};

// Concrete Subject
class WeatherForecast : public IWeatherForecast 
{
    // Forecast for temperature
    string temp_forecast;
    
    // Precipitation Forecast
    string precp_forecast;

    // List of observers
    vector<IObserver*> observer_list;

    public:
    WeatherForecast(){}
    WeatherForecast(string temp, string precp)
        : temp_forecast(temp), precp_forecast(precp)
    {}

    virtual void register_observer(IObserver* obs) override
    {
        observer_list.push_back(obs);
    }

    virtual void delete_observer(IObserver* obs) override
    {
        observer_list.erase(
                find(observer_list.begin(), 
                     observer_list.end(), 
                     obs));
    }

    virtual void notify_observers() override
    {
        for(auto obs : observer_list)
        {
            obs->update();
        }
    }

    string get_temp_forecast()
    {
        return this->temp_forecast;
    }

    string get_rain_forecast()
    {
        return this->precp_forecast;
    }

    void set_temp_forecast(string temp)
    {
        this->temp_forecast = temp;
    }

    void set_rain_forecast(string rain)
    {
        this->precp_forecast = rain;
    }
};

// Concrete Observer
class TempForecast : public IObserver
{
    WeatherForecast& l_weather_forecast;

    public:
    TempForecast(WeatherForecast& weather_forecast)
        : l_weather_forecast(weather_forecast)
    {}

    virtual void update() override
    {
        display();
    }

    /* This will basically generate a Push notification
    in the subscribed devices*/
    virtual void display() override
    {
        cout<<"Temp Forecast:\t"<<endl;
        cout<<l_weather_forecast.get_temp_forecast()<<endl;
    }
};

// Concrete Observer
class RainForecast : public IObserver
{
    WeatherForecast& l_weather_forecast;

    public:
    RainForecast(WeatherForecast& weather_forecast)
        : l_weather_forecast(weather_forecast)
    {}

    virtual void update() override
    {
        display();
    }

    /* This will basically generate a Push notification
    in the subscribed devices*/
    virtual void display() override
    {
        cout<<"Precipitation Forecast:\t"<<endl;
        cout<<l_weather_forecast.get_rain_forecast()<<endl;
    }
};

int main()
{
    WeatherForecast f_weather;
    IObserver* f_temp = new TempForecast(f_weather);
    IObserver* f_rain = new RainForecast(f_weather);

    f_weather.register_observer(f_temp);
    f_weather.register_observer(f_rain);

    f_weather.set_temp_forecast("24' C");
    f_weather.set_rain_forecast("50%");

    f_weather.notify_observers();

    f_weather.set_temp_forecast("32' C");
    f_weather.notify_observers();

    f_weather.delete_observer(f_temp);
    
    f_weather.set_rain_forecast("95%");
    f_weather.notify_observers();


    delete f_temp;
    delete f_rain;

    return 0;
}