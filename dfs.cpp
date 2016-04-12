//routine for depth-first search of a graph G represented by adjacency lists A(v)
// Variable n denotes the last number assigned to a vertex
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>
using namespace std;

typedef pair<int, int> ii;

int n;
vector<vector<int>> A;  //adjacency list
vector<int> labels;     //labels for visited nodes
vector<ii> fronds;    //back edges
vector<ii> treeArcs;  //tree edge
vector<int> LOWPT1;
vector<int> LOWPT2;
int V;

void printE(vector<ii> e){
    cout << "Edges: " << endl;
    for(auto p : e){
        cout << p.first << " -> " << p.second << endl;
    }
}

void printL(vector<int> v){
    cout << "labels: ";
    for(auto l : v){
        cout << l << ", ";
    }
    cout << endl;
}

void printP(vector<ii> p){
    cout << "Path: " << endl;
    for(auto e : p){
        cout << e.first << " -> " << e.second << endl;
    }
}

void dfs(int v, int u){
    labels[v] = ++n;
    for(int i=0; i<A[v].size(); i++){
        int w = A[v][i];
        int lw = labels[w];
        int lv = labels[v];
        if(lw == 0){
            treeArcs.push_back(ii(v, w)); // as a tree arc
            dfs(w, v);
        }
        //This is a test necessary to avoid exploring an edge in both directions
        else if((lw < lv) && (w != u)){ 
            fronds.push_back(ii(v, w)); // as a frond
        }
    }
}

void dfsLPT(int v, int u){
    labels[v] = ++n;
    //a
    LOWPT1[v] = v;
    LOWPT2[v] = v;
    for(int i=0; i<A[v].size(); i++){
        int w = A[v][i];
        int lw = labels[w];
        int lv = labels[v];
        if(lw == 0){
            treeArcs.push_back(ii(v, w)); // as a tree arc
            dfs(w, v);
            //b
            if(LOWPT1[w] < LOWPT2[v]){
                LOWPT2[v] = min(LOWPT1[v], LOWPT2[w]);
                LOWPT1[v] = LOWPT1[w];
            }
            else if(LOWPT1[w] == LOWPT1[v]){
                LOWPT2[v] = min(LOWPT2[v], LOWPT2[w]);
            }
            else{
                LOWPT2[v] = min(LOWPT2[v], LOWPT1[w]);
            }
        }
        //This is a test necessary to avoid exploring an edge in both directions
        else if((lw < lv) && (w != u)){ 
            fronds.push_back(ii(v, w)); // as a frond
            //c
            if(lw < LOWPT1[v]){
                LOWPT2[v] = LOWPT1[v];
                LOWPT1[v] = lw;
            }
            else if(lw > LOWPT1[v]){
                LOWPT2[v] = min(LOWPT2[v], lw);
            }
        }
    }
}


void printG(vector<vector<int>> v){
    for(int i=0; i<v.size(); i++){
        cout << i << ": ";
        for(auto w : v[i]){
            cout << w << ", ";
        }
        cout << endl;
    }
}

int phi(int v, int w, bool isFrond){
    if(isFrond){
        return 2*w;
    }
    else{
        if(LOWPT2[w] >= v){
            return 2*LOWPT1[w];
        }
        else{
            return 2*LOWPT1[w] + 1;
        }
    }
}


void orderAdjacency(vector<vector<int>> &A){
    vector<vector<ii>> bucket(2*V);
    for(auto edge : fronds){
        int p = phi(edge.first, edge.second, true);
        bucket[p].push_back(ii(edge.first, edge.second));
    }
    for(auto edge : treeArcs){
        int p = phi(edge.first, edge.second, false);
        bucket[p].push_back(ii(edge.first, edge.second));
    }
    A.resize(V, vector<int>());
    for(int i=0; i<2*V; i++){
        for(auto p : bucket[i]){
            A[p.first].push_back(p.second);
        }
    }
}

bool isTreeArc(int v, int w){
    for(auto p : treeArcs){
        if(p.first == v && p.second == w){
            return true;
        }
    }
    return false;
}

vector<ii> path;
vector<vector<ii>> paths;
int s;
void PATHFINDER(int v){
    for(int w : A[v]){
        if(isTreeArc(v, w)){
            if(s == 0){
                s = v;
                if(path.size()) {paths.push_back(path);}
                path.clear();
            }
            path.push_back(ii(v, w));
            PATHFINDER(w);
        }
        else{ //is Frond
            if(s == 0){
                s = v;
                paths.push_back(path);
                path.clear();
            }
            path.push_back(ii(v, w));
            printP(path);
            s = 0;
        }
    }
}


int main(){
    int N;
    cin >> N;
    string garb;
    getline(cin, garb); //eat line
    A.push_back(vector<int>(0)); //for 1-indexing on nodes
    while(N--){
        string line;
        getline(cin, line);
        stringstream stream(line);
        vector<int> v;
        while(1){
            int x;
            stream >> x;
            if(!stream) break;
            v.push_back(x);
        }
        sort(v.begin(), v.end()); //To match paper results
        A.push_back(v);
    }
    V = A.size();
    labels.resize(V, 0);
    LOWPT1.resize(V, 0);
    LOWPT2.resize(V, 0);
    orderAdjacency(A);
    n = 0;
    printG(A);
    int start = 1; //starting node
    dfsLPT(start, 0);
    printE(fronds);
    printE(treeArcs);
    printL(labels);
    s = 0;
    PATHFINDER(1);
    return 0;
}




