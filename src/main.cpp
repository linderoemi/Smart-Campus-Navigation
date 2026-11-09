#include "Graph.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <limits>
#include <algorithm>
#include <cctype>

using namespace std;

void displayMenu()
{
    cout << endl;
    cout << "==============================================================" << endl;
    cout << "    Smart Campus Navigation and Facility Analytics System " << endl;
    cout << "==============================================================" << endl;

    cout << endl;
    cout << "1. View All Facilities" << endl;
    cout << "2. Search Facility by ID" << endl;
    cout << "3. View Campus Graph" << endl;
    cout << "4. Display Graph Counts and Degrees" << endl;
    cout << "5. Find Reachable Buildings (BFS)" << endl;
    cout << "6. Add Department" << endl;
    cout << "7. Search Department" << endl;
    cout << "8. Run preorder traversal" << endl;
    cout << "9. Exit" << endl;

    cout << endl;
    cout << "Enter Choice: ";
}

int main(){

    Graph g;


    string bfilename;
    string cfilename;
    string dfilename;
    string ffilename;

    cout << "Enter buildings file name (e.g., data/file.txt): " << endl;
    cin >> bfilename;
    cout << "Enter connections file name (e.g., data/file.txt): " << endl;
    cin >> cfilename;
    cout << "Enter departments file name (e.g., data/file.txt): " << endl;
    cin >> dfilename;
    cout << "Enter facilities file name (e.g., data/file.txt): "<< endl;
    cin >> ffilename;

    
    g.loadGraph(bfilename, cfilename);


    int choice;
    do
    {
        displayMenu();

        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        if (choice == 1){
            //View All Facilities function
            cout << "Viewing all facilities..." << endl;
        }
        else if (choice == 2){
            //Search Facility by ID function
        }
        else if (choice == 3){
            g.printGraph();
        }
        else if (choice == 4){
            g.degreeCount();
        }
        else if (choice == 5){
            //Find Reachable Buildings (BFS) function
        }
        else if (choice == 6){
            //Add Department function
        }
        else if (choice == 7){
            //Search Department function
        }
        else if (choice == 8){
            //Run preorder traversal function
        }
        
        
    } while (choice != 9);

    if (choice == 9){
        cout << "Exiting..." << endl;
    }




    return 0;

}