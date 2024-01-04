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
        ofstream banaune(masterFileName, ios::app);//opening file and creates one if not there
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
            addingSpeed << name << '\t' << speed << endl;//writing name and their typing speed into file
            addingSpeed.close();
        }
        else
            cout << "Zero Value Error!";//cause no letter to count or time taken is 0 sec
    }
};

class fileData:public typingGame
{
public:
    string nameInFile;
    double speed;
    ifstream showing;
    vector<pair<string, double>> data;

    fileData()
    {
        showing.open(masterFileName);
    }

    void display()
    {
        while (showing >> nameInFile >> speed)
        {
            cout << "Name = " << nameInFile << '\t' << "Speed = " << speed << endl;
            data.push_back(make_pair(nameInFile, speed));
        }
    }

    void sortList()
    {
        // Sort the vector of pairs based on the second element (speed) in descending order
        sort(data.begin(), data.end(), [](const auto &a, const auto &b) {
            return a.second > b.second;
        });
    }

    void displaySorted()
    {
        // Display the sorted list
        for (const auto &pair : data)
        {
            cout << "Name = " << pair.first << '\t' << "Speed = " << pair.second << endl;
        }
    }
    void fileRewrite(){
        ofstream rewriting;
        rewriting.open(masterFileName);
        for (const auto &pair : data)
        {
            rewriting << pair.first << ' ' << pair.second << endl;
        }

        // Close the file after rewriting
        rewriting.close();

    }

    ~fileData()
    {
        showing.close();
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
    cout << endl;
    cin.ignore();
    if (r==1){
        typingGame t1;
        t1.WPM();
    }
    else if (r==2){
        fileData fd;
        fd.fileRewrite();
        fd.sortList();

    }
}
