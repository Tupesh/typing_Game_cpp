#include <iostream>
#include <string>    // for using string date type and other string operations as needed
#include <vector>    //dynamic array in cpp
#include <algorithm> //sorting vector array
#include <fstream>   //file handle
#include <ctime>     //taking system time and date
#include <cstdlib>   //contains cls command to clear the output console

using namespace std;

string masterFileName = "ListOfPlayers.txt";

class userInterface
{
public:
    int userResponse()
    {
        int r;
        cin >> r;
        cin.ignore();
        system("cls");
        return r;
    }
    userInterface()
    {
        cout << "\t\tWelcome to the typing console" << endl;
        cout << "Here you may practice typing to increase your typing speed and showoff" << endl;
        cout << "Enter 1 for new user Sign-in" << endl;
        cout << "Enter 2 for existing user login" << endl;
        cout << "Enter 3 to check the top five typing experts and their speed" << endl;
        cout << "Enter 4 to delete existing user" << endl;
        cout << "Any other input will terminate the login/Sign-in interface\n"
             << endl;
        switch (userResponse())
        {
        case 1:
            cout << "Log-in console\n"
                 << endl;
            cout << "At present the log-in console under construction so you will have to proceed with the functionality of signin console" << endl;

            break;
        case 2:
            cout << "Sign-in console\n"
                 << endl;
            break;
        case 3:
            cout << "Player checking console\n"
                 << endl;
            cout << "At present the checking console under construction so you will have to proceed with the functionality of signin console" << endl;
            break;
        case 4:
            cout << "Deleting user console\n"
                 << endl;
            cout << "At present the deleting console under construction so you will have to proceed with the functionality of signin console" << endl;
            break;

        default:
            exit(0);
        }
    }
};

class master : public userInterface
{
protected:
    ofstream add;
    ifstream masterFile;

    int number_of_lines()
    {
        masterFile.open(masterFileName);

        int lineCount = 0;
        string line;

        while (getline(masterFile, line))
        {
            lineCount++;
        }

        masterFile.close();

        return lineCount;
    }

    void addPlayer(const string &Name_of_player)
    {
        add << Name_of_player << endl;
    }

public:
    master()
    {
        int num = number_of_lines();
        add.open(masterFileName, ios::app);
    }

    ~master()
    {
        add.close();
    }
};

class player : public master
{
protected:
    string Name, nickName, fileName;
    int NumberOfGames;

    void input()
    {
        cout << "Enter your name: ";
        cin >> Name;
        cout << "What would you like your nickname to be in the game? ";
        cin >> nickName;
        cin.ignore();
    }

    string createdDate()
    {
        time_t now = time(0);
        string dt = ctime(&now);
        return dt;
    }

    void playerFile()
    {
        fileName = Name + ".txt";
        string date = createdDate();
        ofstream banaune(fileName);
        banaune << "NAME: " << Name << "\t"
                << "NICKNAME: " << nickName << "\t"
                << "DATE OF CREATION: " << date;
        banaune.close();
    }

public:
    player()
    {
        input();
        playerFile();
        addPlayer(Name);
    }
};

class typingGame : public player
{
private:
    string enter;

    time_t currentTime()
    {
        return time(nullptr);
    }

public:
    double type()
    {

        cout << "Enter a sentence. I'll test your timing:\n";
        time_t startTime = currentTime();
        getline(cin, enter);
        cout << " hey " << endl;
        time_t endTime = currentTime();
        double timeTaken = difftime(endTime, startTime);
        cout << "It took you " << timeTaken << " seconds to type that much" << endl;

        return timeTaken;
    }

    void WPM()
    {
        double timeTaken = type();
        if (timeTaken == 0 || enter.length() == 0)
            cout << "Error!";
        else
        {

            int l = enter.length();
            double speed = (double)l / timeTaken;
            cout << "You have typed " << l << " characters." << endl;
            cout << "Your speed is " << speed << " characters per second" << endl;
            ofstream addingSpeed(fileName, ios::app);
            addingSpeed << speed;
            addingSpeed.close();
        }
    }

    typingGame() {}
};
int main()
{
    typingGame t1;
    t1.WPM();
}
