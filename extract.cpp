#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string masterFileName = "playersData.txt";

class fileData
{
public:
    string name;
    double speed;
    ifstream showing;
    vector<pair<string, double>> data;

    fileData()
    {
        showing.open(masterFileName);
    }

    void display()
    {
        while (showing >> name >> speed)
        {
            cout << "Name = " << name << '\t' << "Speed = " << speed << endl;
            data.push_back(make_pair(name, speed));
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
    fileData d;
    d.display();
    d.sortList();
    cout << "\nSorted List:\n";
    d.displaySorted();
    d.fileRewrite();
    return 0;
}
