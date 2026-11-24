/*
 * heap.cpp
 *
 *  Created on: 23/11/2026
 *      Author: Daniel Cortizo
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;

class Graph {
private:
    int nodes;
    int edgesList;
    int edgesMat;
    vector<int> *adjList;
    int *adjMatrix;

    void sortAdjList();
    bool contains(list<int>, int);
    string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int>>&);
    string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int>>&);
    string print_visited(list<int>);
    string print_path(vector<vector<int>>&, int, int);

public:
    Graph();
    Graph(int);

    void loadGraphList(string, int);
    void loadGraphMat(string, int, int);

    void addEdgeAdjList(int, int);
    void addEdgeAdjMatrix(int, int);

    string printAdjList();
    string printAdjMat();

    string DFS(int, int);
    string BFS(int, int);
};

Graph::Graph() {
    edgesList = 0;
    edgesMat = 0;
}

Graph::Graph(int n) {
    nodes = n;
    adjList = new vector<int>[nodes];
    adjMatrix = new int[nodes * nodes];
    for (int i = 0; i < nodes * nodes; i++) {
        adjMatrix[i] = 0;
    }
    edgesList = 0;
    edgesMat = 0;
}

void Graph::addEdgeAdjList(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
    edgesList++;
}

void Graph::addEdgeAdjMatrix(int u, int v) {
    adjMatrix[u * nodes + v] = 1;
    adjMatrix[v * nodes + u] = 1;
    edgesMat++;
}

void Graph::sortAdjList() {
    for (int i = 0; i < nodes; i++) {
        sort(adjList[i].begin(), adjList[i].end());
    }
}

void Graph::loadGraphList(string data, int a) {
    nodes = a;
    adjList = new vector<int>[nodes];
    string line;
    stringstream lee(data);
    int u, v;
    while (getline(lee, line, ' ')) {
        if (line.size() >= 5) {
            u = stoi(line.substr(1, 1));
            v = stoi(line.substr(3, 1));
            addEdgeAdjList(u, v);
        }
    }
    sortAdjList();
}

void Graph::loadGraphMat(string data, int a, int b) {
    nodes = a;
    adjMatrix = new int[a * b];
    for (int i = 0; i < a * b; i++) {
        adjMatrix[i] = 0;
    }
    string line;
    stringstream lee(data);
    int u, v;
    while (getline(lee, line, ' ')) {
        if (line.size() >= 5) {
            u = stoi(line.substr(1, 1));
            v = stoi(line.substr(3, 1));
            addEdgeAdjMatrix(u, v);
        }
    }
}

string Graph::printAdjList() {
    stringstream aux;
    for (int i = 0; i < nodes; i++) {
        aux << "vertex " << i << " :";
        for (size_t j = 0; j < adjList[i].size(); j++) {
            aux << " " << adjList[i][j];
        }
        aux << " ";
    }
    return aux.str();
}

string Graph::printAdjMat() {
    stringstream aux;
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            aux << adjMatrix[i * nodes + j] << " ";
        }
    }
    return aux.str();
}

bool Graph::contains(list<int> ls, int node) {
    list<int>::iterator it;
    it = find(ls.begin(), ls.end(), node);
    if (it != ls.end()) {
        return true;
    } else {
        return false;
    }
}

string Graph::print_visited(list<int> q) {
    stringstream aux;
    aux << "visited: ";
    while (!q.empty()) {
        aux << q.front() << " ";
        q.pop_front();
    }
    return aux.str();
}

string Graph::print_path(vector<vector<int>> &path, int start, int goal) {
    int node = path[goal][0];
    stack<int> reverse;
    reverse.push(goal);
    stringstream aux;
    aux << "path:";
    while (node != start) {
        reverse.push(node);
        node = path[node][0];
    }
    reverse.push(start);
    while (!reverse.empty()) {
        aux << " " << reverse.top();
        reverse.pop();
    }
    return aux.str();
}

string Graph::DFS(int start, int goal) {
    stack<int> st;
    list<int> visited;
    vector<vector<int>> paths(nodes, vector<int>(1, -1));
    st.push(start);
    string ans = depthHelper(start, goal, st, visited, paths);
    ans = ans + print_path(paths, start, goal);
    return ans;
}

string Graph::depthHelper(int current,
                          int goal,
                          stack<int> &st,
                          list<int> &visited,
                          vector<vector<int>> &paths) {
    if (current == goal) {
        return print_visited(visited);
    } else if (st.empty()) {
        return " node not found";
    } else {
        current = st.top();
        st.pop();
        visited.push_back(current);
        for (size_t i = 0; i < adjList[current].size(); i++) {
            if (!contains(visited, adjList[current][i])) {
                st.push(adjList[current][i]);
                paths[adjList[current][i]][0] = current;
            }
        }
        return depthHelper(current, goal, st, visited, paths);
    }
}

string Graph::BFS(int start, int goal) {
    queue<int> qu;
    list<int> visited;
    vector<vector<int>> paths(nodes, vector<int>(0));
    qu.push(start);
    string ans = breadthHelper(start, goal, qu, visited, paths);
    ans = ans + print_path(paths, start, goal);
    return ans;
}

string Graph::breadthHelper(int current,
                            int goal,
                            queue<int> &qu,
                            list<int> &visited,
                            vector<vector<int>> &paths) {
    if (current == goal) {
        return print_visited(visited);
    } else if (qu.empty()) {
        return " node not found";
    } else {
        current = qu.front();
        qu.pop();
        visited.push_back(current);
        for (size_t i = 0; i < adjList[current].size(); i++) {
            if (!contains(visited, adjList[current][i])) {
                qu.push(adjList[current][i]);
                paths[adjList[current][i]].push_back(current);
            }
        }
        return breadthHelper(current, goal, qu, visited, paths);
    }
}

#endif /* GRAPH_H_ */