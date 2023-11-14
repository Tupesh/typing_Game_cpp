


#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;
string masterFileName = "ListOfPlayers.txt";

class master
{
    ofstream add;
    ifstream masterFile;

protected:
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
    void addPlayer(string Name_of_player);
    master()
    {
        int num = number_of_lines();
        string pNames[num];
        add.open(masterFileName, ios::app);
    };
};

void master::addPlayer(string Name_of_player)
{
    add << Name_of_player << endl;
}

class player : public master
{
protected:
    string Name;
    char *nickName;
    int NumberOfGames;

    void input();
    char *createdDate();
    void infoRetrun();
    void playerFile();
    player()
    {
        input();
        playerFile();
        addPlayer(Name);
    }
};

void player::input()
{
    cout << "Enter your name: ";
    cin >> Name;
    cout << "What would you like your nickname to be in the game? ";
    cin >> nickName;
}
char *player::createdDate()
{
    time_t now = time(0);
    char *dt = ctime(&now);
    return dt;
}
void player::playerFile()
{
    string fileName = Name + ".txt";
    string date = createdDate();
    ofstream banaune(fileName);
    banaune << "NAME: " << Name << "\tNICKNAME: " << nickName << "\tDATE OF CREATION: " << date;
    // banaune.close();
}




class typingGame : public player
{
    string enter;
    inline time_t currentTime()
    {
        return time(nullptr);
    }
public:
    int type()
    {
        cout << "Enter your name I'l test your timing: ";
        time_t starTime=currentTime();
        cin >> enter;
        time_t endTime=currentTime();
        int timeTaken=difftime(endTime,starTime);
        cout<<"It took you "<<timeTaken<<" seconds to type that much"<<endl;
        return timeTaken*1000;
    }
    void WPM(){
        int timeTaken=type();
        cout<<"your speed is "<<12000/timeTaken;
    }
    typingGame(){

    }
};

int main()
{
    typingGame t1;
    t1.WPM();
}
