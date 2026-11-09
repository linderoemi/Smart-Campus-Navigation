#include "Graph.h"

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void Graph::addVertex(string v){
    if (adjList.find(v) == adjList.end()){
        adjList[v];
    }
}

void Graph::addEdge(string buildA, string buildB){
    adjList[buildA].push_back(buildB);
    adjList[buildB].push_back(buildA);
}

void Graph::printGraph(){
    if (adjList.empty()){
        cout << "Empty files given." << endl;
    }

    for (const auto& [node, neighbors] : adjList){
        cout << node << "|";
        if (neighbors.empty()){
            cout << "None";
        }
        else{
            for(const auto& neighbor : neighbors){
                cout << neighbor << ", ";
            }
        }
        cout << endl;
    }
}

void Graph::degreeCount(){
    if (adjList.empty()){
        cout << "Empty files given." << endl;
    }
    
    int totalConnections = 0;
    for (const auto& [node, neighbors] : adjList){
        int count = neighbors.size();
        totalConnections += count;
        cout << node << "|" << count << endl;
    }
    cout << "Total buildings:" << adjList.size() << ". ";
    cout << "Total connections:" << totalConnections / 2 << "." << endl;
}

void Graph::loadGraph(string vfilename, string efilename){
    ifstream vfile(vfilename);
    if (!vfile.is_open()){
        cout << "This file is empty." << endl;
    } else{
        string ignore_line;
        getline(vfile, ignore_line);
        cout << "Buildings file opened successfully." << endl;
        string vertex;
        while (getline(vfile, vertex)){
            addVertex(vertex);
        }
        vfile.close();
    }

    ifstream efile(efilename);
    if (!efile.is_open()){
        cout << "This file is empty." << endl;
    } else{
        string ignore_line;
        getline(efile, ignore_line);
        cout << "Connections file opened successfully." << endl;

        string edge;
        char delimiter = '|';
        while (getline(efile, edge)){
            stringstream ss(edge);

            string buildA;
            string buildB;
            getline(ss, buildA, delimiter);
            getline(ss, buildB, delimiter);
        
            addEdge(buildA, buildB);


        }
    efile.close();
    }
}

vector<string> Graph::getBuildingNames(){
    vector<string> buildingNames;
    for (const auto& [node, neighbors] : adjList){
        buildingNames.push_back(node);
    }
    return buildingNames;
}