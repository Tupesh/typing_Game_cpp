#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

string masterFileName = "playersData.bin";
string pass = "Password@123";
string emptyMessage = "At the moment database is empty";

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
        cout << "\n\n\t\t\tWelcome to the typing console beta version" << endl;
        cout << "\n\t\tHere you may practice typing to increase your typing speed" << endl;
        cout << "\n\tThis game is in it's beta stage so accuracy isn't taken into consideration\n" << endl;
    }
    ~TypingGame()
    {
        cout << "Terminating the interface.\n";
    }

    void getData()
    {
        cout << "Enter your name: ";
        cin >> name;
        cin.ignore();
    }

    double type()
    {
        cout << "\nType anything. Your test begins now:\n";
        time_t startTime = currentTime();
        getline(cin, enter);
        time_t endTime = currentTime();
        l = enter.length();
        double timeTaken = difftime(endTime, startTime);
        cout << "It took you " << timeTaken << " seconds to complete the test." << endl;
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

            // Check if the user already exists in the data vector
            auto existingUser = find_if(data.begin(), data.end(),
                                        [this](const auto &entry)
                                        { return entry.first == name; });

            if (existingUser != data.end())
            {
                cout << "\n\nThe player " << name << " already exists so max speed is being added to the database" << endl;
                // If the user already exists and the new speed is greater, update the speed
                if (speed > existingUser->second)
                {
                    existingUser->second = speed;
                }
            }
            else
            {
                // If the user is new, add a new entry
                data.push_back(make_pair(name, speed));
            }

            // Read the existing data from the file
            vector<pair<string, double>> existingData;
            ifstream existingFile(masterFileName);
            string nameInFile;
            double speedInFile;

            while (existingFile >> nameInFile >> speedInFile)
            {
                existingData.push_back(make_pair(nameInFile, speedInFile));
            }

            // Update the vector with the latest data
            for (const auto &entry : data)
            {
                auto iter = find_if(existingData.begin(), existingData.end(),
                                    [&entry](const auto &existingEntry)
                                    {
                                        return existingEntry.first == entry.first;
                                    });

                if (iter != existingData.end())
                {
                    // Update the speed only if the new speed is greater
                    if (entry.second > iter->second)
                    {
                        iter->second = entry.second;
                    }
                }
                else
                {
                    existingData.push_back(entry);
                }
            }

            existingFile.close();

            // Rewrite the entire file with the updated data
            ofstream updating(masterFileName, ios::out);
            for (const auto &entry : existingData)
            {
                updating << entry.first << '\t' << entry.second << endl;
            }
            updating.close();
        }
        else
        {
            cout << "Zero Value Error!";
        }
        getchar();
    }

    void sortingPair()
    {
        ifstream showing(masterFileName);
        string nameInFile;
        double speed;
        data.clear();

        while (showing >> nameInFile >> speed)
        {
            data.push_back(make_pair(nameInFile, speed));
        }

        sort(data.begin(), data.end(), [](const auto &a, const auto &b)
             { return a.second > b.second; });
        showing.close();
    }

    void displayTopFive()
    {
        sortingPair();
        if (data.empty())
        {
            cout << emptyMessage << endl;
        }
        else
        {
            cout << "\nTop Five Typing Experts:\n";
            for (size_t i = 0; i < min(data.size(), static_cast<size_t>(5)); ++i)
            {
                cout << "Name = " << data[i].first << '\t' << "Speed = " << data[i].second << endl;
            }
        }
    }

    void deletePlayer()
    {
        if (data.empty())
        {
            cout << emptyMessage << endl;
        }
        else
        {
            string password, dName;
            cout << "Enter the player's name to delete: ";
            cin >> dName;
            cout << "Enter the deletion password: ";
            cin >> password;

            if (password == pass)
            {
                cout << "Password correct. Deleting player data...\n";

                // Read existing data into a vector
                sortingPair();

                // Exclude the player to be deleted
                data.erase(remove_if(data.begin(), data.end(),
                                     [dName](const auto &entry)
                                     { return entry.first == dName; }),
                           data.end());

                // Rewrite the entire file with the updated data
                ofstream deleting(masterFileName, ios::out);
                for (const auto &entry : data)
                {
                    deleting << entry.first << '\t' << entry.second << endl;
                }
                cout << "Deletion successful" << endl;
            }
            else
            {
                cout << "Incorrect password. Deletion failed.\n";
            }
        }
    }
    void findPlayer()
    {
        if (data.empty())
        {
            cout << emptyMessage << endl;
        }
        else
        {
            string playerName;
            cout << "Whose speeed do you want to see? ";
            cin >> playerName;
            // Check if the player exists in the data vector
            auto it = find_if(data.begin(), data.end(),
                              [playerName](const auto &entry)
                              { return entry.first == playerName; });

            if (it != data.end())
            {
                // Player found, print their speed
                cout << "Player's speed: " << it->second << endl;
            }
            else
            {
                // Player not found
                cout << "Player not found in the data base." << endl;
            }
        }
    }
    void allPlayers()
    {
        sortingPair();
        if (data.empty())
        {
            cout << emptyMessage << endl;
        }
        else
        {
            int i = 1;
            for (auto it = data.begin(); it != data.end(); it++)
            {
                cout << i << "\tName = " << it->first << '\t' << "Speed = " << it->second << endl;
                i++;
            }
        }
    }
};

int main()
{
    int choice;
    TypingGame typingGame;
    //int t = 1;
    while (true)
    {

        cout << "1. Start new game" << endl;
        cout << "2. Check top players" << endl;
        cout << "3. Delete existing player" << endl;
        cout << "4. Check a player's speed" << endl;
        cout << "5. View players list\n" << endl;
        cout << "Any other input will terminate the interface\n" << endl;
        cout << "Enter your choice: " ;
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
        case 4:
            typingGame.findPlayer();
            break;
        case 5:
            typingGame.allPlayers();
            break;
        default:
            return 0;
        }
        cout << "\n\n\n\n";
    }
}
