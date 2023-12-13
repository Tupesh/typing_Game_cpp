#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

string masterFileName = "playersData.txt";
string deletingPass = "SuperSecretPassword@123";

class filing
{

public:
    filing()
    {
        ofstream banaune(masterFileName, ios::app);
    }
};

class playerData
{
protected:
    char name[10];
    double speed;
    playerData()
    {
        cout << "Enter your name: ";
        cin >> name;
        cin.ignore();
    }
};

class typingGame : public playerData
{
private:
    string enter;
    int l;
    time_t currentTime()
    {
        return time(nullptr);
    }

public:
    double type()
    {
        cout << "\nEnter a sentence. I'll test your timing:\n";
        time_t startTime = currentTime();
        getline(cin, enter);
        // cout << " hey " << endl;
        time_t endTime = currentTime();
        l = enter.length();
        double timeTaken = difftime(endTime, startTime);
        cout << "It took you " << timeTaken << " seconds to type that much" << endl;
        cout << "You have typed " << l << " characters." << endl;

        return timeTaken;
    }

    void WPM()
    {
        double timeTaken = type();
        
        if (l != 0 && timeTaken != 0)
        {
            double speed = (double)l / timeTaken;
            cout << "Your speed is " << speed << " characters per second" << endl;
            ofstream addingSpeed(masterFileName, ios::app);
            addingSpeed << name << '\t' << speed << endl;
            addingSpeed.close();
        }
        else
            cout << "Zero Value Error!";
    }
};

int main()
{
    int r;
    cout << "\t\tWelcome to the typing console" << endl;
    cout << "Here you may practice typing to increase your typing speed and showoff" << endl;
    cout << "Enter 1 for new Game" << endl;
    cout << "Enter 2 to check the top five typing experts and their speed" << endl;
    cout << "Enter 3 for deleting existing player" << endl;
    cout << "Any other input will terminate the interface" << endl;
    cin>>r;
    cin.ignore();
    cout << endl;
    typingGame t1;
    t1.WPM();
}