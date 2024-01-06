#include <bits/stdc++.h>
// #include <iostream>
// #include <string>
// #include <fstream>
// #include <ctime>
// #include <algorithm>
// #include <vector>

using namespace std;

string masterFileName = "playersData.txt";
string deletingPass = "SuperSecretPassword@123";

class TypingGame
{
private:
    char name[10];
    string enter;
    int l;
    vector<pair<string, double>> data;

    time_t currentTime()
    {
        return time(nullptr);
    }

public:
    TypingGame()
    {

    }
    ~TypingGame()
    {
        
        

    }
    void getData()
    {
        cout << "Enter your name: ";
        cin >> name;
        cin.ignore();
    }
    double type()
    {
        cout << "\nEnter a sentence. I'll test your timing:\n";
        time_t startTime = currentTime();
        getline(cin, enter);
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
            double speed = static_cast<double>(l) / timeTaken;
            cout << "Your speed is " << speed << " characters per second" << endl;
            ofstream addingSpeed(masterFileName, ios::app);
            addingSpeed << name << '\t' << speed << endl;
            addingSpeed.close();
        }
        else
            cout << "Zero Value Error!";
        getchar();
        system("cls");
    }

    void displayTopFive()
    {
        ifstream showing(masterFileName);
        string nameInFile;
        double speed;

        while (showing >> nameInFile >> speed)
        {
            // cout << "Name = " << nameInFile << '\t' << "Speed = " << speed << endl;
            data.push_back(make_pair(nameInFile, speed));
        }

        sort(data.begin(), data.end(), [](const auto &a, const auto &b)
             { return a.second > b.second; });

        cout << "\nTop Five Typing Experts:\n";
        for (size_t i = 0; i < min(data.size(), static_cast<size_t>(5)); ++i)
        {
            cout << "Name = " << data[i].first << '\t' << "Speed = " << data[i].second << endl;
        }

        showing.close();
    }

    void deletePlayer()
    {
        string password;
        cout << "Enter the deletion password: ";
        cin >> password;

        if (password == deletingPass)
        {
            cout << "Password correct. Deleting player data...\n";
            // Implement deletion logic here
        }
        else
        {
            cout << "Incorrect password. Deletion failed.\n";
        }
    }
};

int main()
{
    int choice;
    while (true)
    {
        TypingGame typingGame;
        cout << "\t\tWelcome to the typing console" << endl;
        cout << "Here you may practice typing to increase your typing speed and showoff" << endl;
        cout << "Enter 1 for new Game" << endl;
        cout << "Enter 2 to check the top five typing experts and their speed" << endl;
        cout << "Enter 3 for deleting existing player" << endl;
        cout << "Any other input will terminate the interface" << endl;

        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            typingGame.getData();
            typingGame.WPM();
            break;
        case 2:
            typingGame.displayTopFive();
            break;
        case 3:
            typingGame.deletePlayer();
            break;
        default:
            cout << "Terminating the interface.\n";
            return 0;
        }
        cout << "\n\n\n\n";
    }
}