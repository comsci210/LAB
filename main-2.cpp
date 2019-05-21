#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <stack>
#include <map>
#include <iomanip>
#include <queue>
using namespace std;

#define MAX_EDGES   5
#define MAX_ROUTE   25

// output if there is a direct route between two cities and its cost

struct cityNode {
    vector<string> neighbors;
    vector<int> distances;
    bool visited = false;
    int cost = -1;
    string previous;
};

struct tempNode {
    string name;
    string previous;
    int cost;
    bool operator<(const tempNode& t) const {
        return (cost > t.cost);
    }
};

stack<string> printStack;

#define FILENAME "cal_cities-1.csv"
#define IS_QUIT(s) (s == "X" || s == "x")
using namespace std;

void parse_line(const string &str,
        vector<string> &line) {
    istringstream istr(str);
    string tmp;
    while (getline(istr, tmp, ',')) {
        line.push_back(tmp);
    }
}

void computeShortestPaths(string startCity, string endCity,
        map<string, cityNode> &graph) {
    cityNode cur;
    tempNode tstart, tcur;
    priority_queue<tempNode> working;
    map<string, cityNode>::iterator ci;

    // reset all the state
    map<string, cityNode>::iterator g;
    for (g = graph.begin(); g != graph.end(); g++) {
        g->second.visited = false;
        g->second.cost = -1;
    }

    // initialize the working list
    tstart.name = startCity;
    tstart.cost = 0;
    working.push(tstart);
    while (!working.empty()) {
        // cout << "queue len " << working.size() << endl;
        tcur = working.top();
        cout << "processing " << tcur.name << " " << tcur.cost << endl;
        ci = graph.find(tcur.name);
        // This finds the cityNode in the graph.
        // 'ci' contains the key and a reference to the graph node

        // remove this element
        working.pop();

        // check to see if this element is visited:
        //
        // - ci.first contains to the key (name)
        // - ci.second contains the graph node
        // - tcur points to the most recent node popped from the
        //   priority queue
        //
        if (ci->second.visited)
            continue;

        // set this node to visited
        ci->second.visited = true;

        // set the final cost
        ci->second.cost = tcur.cost;

        // set the final parent
        ci->second.previous = tcur.previous;

        // See if we can stop here
        if (tcur.name == endCity)
            break;

        // Next, examine all the neighbors of this node
        for (int i = 0; i < ci->second.neighbors.size(); i++) {
            // Have we visited this node?
            string n = ci->second.neighbors[i];
            if (graph[n].visited)
                continue;

            tempNode t;

            // Fill in the metric and the parent for a NEW
            // tmpNode, add it to the queue
            // metric == path to THIS node + cost of edge from
            // THIS node to neighbor


            // TENT node consists of:
            // - This cost to the neighbor node (cost to us + cost of edge)
            // - Name of the neighbor node
            // - Parent node if this path is used
            t.cost = ci->second.distances[i] + tcur.cost;
            t.name = n;
            t.previous = tcur.name;
            working.push(t);


        }

    }

}

int main() {
    ifstream inFile("cal_cities-1.csv");
    string inputLine, inputStr;
    map<string, cityNode> graph;
    map<string, cityNode>::iterator cmi;
    string::size_type sz;
    string to, from;
    int i;

    while (getline(inFile, inputLine)) {
        vector<string> row;
        cityNode c;
        parse_line(inputLine, row);
        graph.insert(make_pair(row[0], c));

        // this creates the FROM city if not there, adds edge
        graph[row[0]].neighbors.push_back(row[1]);
        graph[row[0]].distances.push_back(stoi(row[2], &sz));

        // this creates the TO city if not there,
        // adds edge from the other direction (bidirectional)
        graph[row[1]].neighbors.push_back(row[0]);
        graph[row[1]].distances.push_back(stoi(row[2], &sz));
    }
/*
    map<string, cityNode>::iterator it;
    for (it = graph.begin(); it != graph.end(); it++) {
            cout << "city: " << it->first << endl;
            cout << "best cost: " << it->second.cost << endl;
            cout << "prev: " << it->second.previous << endl;
            cout << "\t" << "neighbors: " << endl;
            cityNode c = it->second;
            for (int i = 0; i < c.neighbors.size(); i++) {
                cout << "\t\t" << c.neighbors[i] << " cost: " << c.distances[i] << endl;
            }
     }
     */

    for (;;) {
        cout << endl << "Enter the FROM city name (X to quit): ";
        getline(cin, from);
        if (IS_QUIT(from))
            break;
        cout << endl << "Enter the TO city name (X to quit): ";
        getline(cin, to);
        if (IS_QUIT(to))
            break;
        if (graph.count(to) == 0 || graph.count(from) == 0) {
            cout << "You entered at least 1 invalid city.";
            continue;
        }
        computeShortestPaths(from, to, graph);
        cityNode fromNode = graph[from];
        cityNode toNode = graph[to];

        // print out the path starting from the target, backwards
        cout << "The cheapest route is: " << toNode.cost << endl;
        cout << "via the route: " << endl;
        cout << "\t\t";

        stack<string> Rstack;

        
        // for(int i = 0;i<2;i++){
        //     cout << toNode.previous;
        //     toNode = graph[toNode.previous];
        // }
        Rstack.push(to);
        while(toNode.previous != from){
            Rstack.push(toNode.previous);
            toNode = graph[toNode.previous];
        }
        Rstack.push(from);
        cout << Rstack.top();
        Rstack.pop();
        while(!Rstack.empty()){
            cout << "->" << Rstack.top();
            Rstack.pop();
        }

        // Start at the destination node, and push each
        // element in the path onto a stack.

        // Reverse the output (pop each element) and
        // print the path from source to destination
        cityNode tmpNode;
       // while (tmpNode.name != to) {
       //     // Walk each parent node until we hit the root
       // }

    }
    cout << "Exiting..." << endl;
}
