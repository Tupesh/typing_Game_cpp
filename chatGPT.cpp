#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> myVector = {5, 2, 8, 1, 7};

    // Sort the elements in ascending order
    sort(myVector.begin(), myVector.end());

    int l= myVector.size();
    
    //  Display the sorted elements

    for (int i = 0; i < l; i++)
    {
        cout<<myVector[i]<<" ";
    }
    

    
    
    //  Display the sorted elements
    // for (const auto& element : myVector) {
    //     cout << element << " ";
    // }

    return 0;
}