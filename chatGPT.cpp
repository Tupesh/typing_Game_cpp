#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

string masterFileName = "ListOfPlayers.txt";

class master {
    ofstream add;
    ifstream masterFile;

public:
    int number_of_lines() {
        masterFile.open(masterFileName);

        if (!masterFile.is_open()) {
            cerr << "Failed to open the file." << endl;
            return 1;
        }

        int lineCount = 0;
        string line;

        while (getline(masterFile, line)) {
            lineCount++;
        }

        masterFile.close();

        return lineCount;
    }

    void addPlayer(const string& Name_of_player) {
        add.open(masterFileName, ios::app);
        add << Name_of_player << endl;
        add.close();
    }

    master() {

    }
};

class player : public master {
    string Name;
    int NumberOfGames;

public:
    void input();
    string createdDate();
    void playerFile();

    player() {
        input();
        playerFile();
    }
};

void player::input() {
    cout << "Enter your name: ";
    cin >> Name;
    addPlayer(Name);
}

string player::createdDate() {
    time_t now = time(0);
    char *dt = ctime(&now);
    return dt;
}

void player::playerFile() {
    string fileName = Name + ".txt";
    string date = createdDate();
    ofstream banaune(fileName);
    if (banaune.is_open()) {
        banaune << "NAME: " << Name << "\tDATE OF CREATION: " << date;
        banaune.close();
    } else {
        cerr << "Failed to create the player file." << endl;
    }
}

int main() {
    player p1;
    player p9;
}
