#include "Graph.h"
#include "HashTable.h"
#include "FacilityDatabase.h"
#include "DepartmentTree.h"

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
    cout << "8. Display department hierarchy" << endl;
    cout << "9. Run preorder traversal" << endl;
    cout << "10. Exit" << endl;

    cout << endl;
    cout << "Enter Choice: ";
}

int main(){

    Graph g;
    FacilityDatabase facilityDatabase;
    DepartmentTree departmentTree;


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

    int facilitiesAccepted = 0, facilitiesRejected = 0;
    facilityDatabase.loadFromFile(ffilename, g.getBuildingNames(), facilitiesAccepted, facilitiesRejected);

    int departmentsAccepted = 0, departmentsRejected = 0;
    departmentTree.loadFromFile(dfilename, departmentsAccepted, departmentsRejected);

    

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
            facilityDatabase.displayAll();
        }
        else if (choice == 2){
            //Search Facility by ID function
            string ID;
            cout << "Enter facility ID: ";
            cin >> ID;
            facilityDatabase.searchByID(ID);
        }
        else if (choice == 3){
            //Display graph through adjacency list
            g.printGraph();
        }
        else if (choice == 4){
            //Display count and degrees
            g.degreeCount();
        }
        else if (choice == 5){
            //Find Reachable Buildings (BFS) function
        }
        else if (choice == 6){
            //Add Department function
            string department;
            string parent;
            cout << "Enter department name: ";
            cin >> department;
            cout << "Enter parent department: ";
            cin >> parent;
            departmentTree.addDepartment(department, parent);

        }
        else if (choice == 7){
            //Search Department function
            string department;
            cout << "Enter department name: ";
            cin >> department;
            departmentTree.searchDepartment(department);
        }
        else if (choice == 8){
            //Display department hierarchy function
            departmentTree.displayHierarchy();
        }
        else if (choice == 9){
            //Run preorder traversal function
            departmentTree.displayPreorder();
        }
        
        
    } while (choice != 10);

    if (choice == 10){
        cout << "Exiting..." << endl;
    }




    return 0;

}