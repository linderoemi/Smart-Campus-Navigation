#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Graph{
    private:
        unordered_map<string, vector<string>> adjList;

    public:
        void addVertex(string v);
        void addEdge(string buildA, string buildB);
        void printGraph();
        void degreeCount();
        void loadGraph(string vfilename, string efilename);

        //for member a loadfile argument
        vector<string> getBuildingNames();

};

#endif
