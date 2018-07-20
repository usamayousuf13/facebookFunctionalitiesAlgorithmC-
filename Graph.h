#include "list.h"
#include <map>
#include <string>
using namespace std;

#ifndef GRAPH_H
#define GRAPH_H


class Graph {
protected :
    int sizeOfMap;
    adjList* array;
    map<int,string> user;
public:
    Graph();
    void storeUsersInMap();
    int totalSizeOfMap();
    adjList* makeArray();
    adjListNode* newAdjListNode(string dest);
    int convertValueToKey(string item);
    void addEdge(string,string);
    void makeFriendList();
    void printGraph();
    void deleteItem(string,int);
    void unfriend();
    void suggestFriends();
    void mutualFriends();
    void printToFile();

};

#endif // GRAPH_H
