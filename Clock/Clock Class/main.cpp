#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

class Clock
{
private:
    double m_hour{};
    double m_minute{};

public:
    Clock (double hour=0, double minute=0): m_hour{hour}, m_minute{minute}
    {

    }

    int get_hour()
    {
        return m_hour;
    }
    int get_minute()
    {
        return m_minute;
    }

    friend double hour_deg(const Clock& c1);
    friend double minute_deg(const Clock& c1);
    friend istream& operator >>(istream& in, Clock& c1);

};

double hour_deg(const Clock&c1)
{
    if(c1.m_hour*30 + c1.m_minute*0.5 > 360)
    {
        return c1.m_hour*30 + c1.m_minute*0.5 - 360;
    }
    else
    {
        return c1.m_hour*30 + c1.m_minute*0.5;
    }
}

double minute_deg(const Clock&c1)
{
    return c1.m_minute*6;
}

istream& operator>>(istream& in, Clock& c1)
{
    in >> c1.m_hour;

    in.ignore(numeric_limits<streamsize>::max(), ':');

    in >> c1.m_minute;
}

int main()
{
    Clock c1;
    cin >> c1;

    while(c1.get_hour() != 0 || c1.get_minute() != 0)
    {
        double degrees = abs(hour_deg(c1) - minute_deg(c1));

        if(degrees > 180)
        {
            cout << 360.0 - degrees;
        }
        else
        {
            cout << degrees;
        }
        cout << endl;

        cin >> c1;
    }
    return 0;
}
