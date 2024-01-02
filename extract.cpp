#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string masterFileName = "playersData.txt";
class data
{
    public:
    string details;
    ifstream showing;
    
    data(){
        showing.open(masterFileName);
    }

    void display(){
        if (!showing.is_open())
        {
            cerr << "Error opening file for reading." << endl;
            return;
        }

        while(getline(showing,details))
        cout<<details<<endl;
    }

    ~data()
    {
        showing.close();
    }
};

int main()
{
    data d;
    d.display();
    return 0;
}

// #include <iostream>
// #include <fstream>

// int main() {
//     // Input mode
//     std::ifstream inputFile("playersData.txt", std::ios::in);

//     if (!inputFile.is_open()) {
//         std::cerr << "Error opening file for reading." << std::endl;
//         return 1;
//     }

//     // Read and print integers from the file
//     int intValue;

//     while (inputFile >> intValue) {
//         std::cout << "Read from file: " << intValue << std::endl;
//     }

//     inputFile.close(); // Close the file

//     return 0;
// }
