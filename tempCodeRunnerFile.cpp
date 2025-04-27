#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int source, destination, weight;

    Edge(int src, int dest, int w) : source(src), destination(dest), weight(w) {}
};

// Function to compare edges based on their weights for sorting
bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

// Class to represent a disjoint-set data structure
class DisjointSet {
private:
    vector<int> parent, rank;

public:
    // Constructor
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    // Find operation with path compression
    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // Union operation by rank
    void unionSet(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV])
                swap(rootU, rootV);
            parent[rootV] = rootU;
            if (rank[rootU] == rank[rootV])
                rank[rootU]++;
        }
    }
};

// Class to represent a graph and find its Minimum Spanning Tree using Kruskal's algorithm
class Graph {
private:
    vector<Edge> edges;
    int numVertices;

public:
    // Constructor
    Graph(int n) : numVertices(n) {}

    // Add an edge to the graph
    void addEdge(int source, int destination, int weight) {
        edges.emplace_back(source, destination, weight);
    }

    // Function to find Minimum Spanning Tree using Kruskal's algorithm
    vector<Edge> findMST() {
        vector<Edge> MST; // Minimum Spanning Tree
        // Sort edges based on weight
        sort(edges.begin(), edges.end(), compareEdges);
        DisjointSet ds(numVertices);
        
        for (const Edge& edge : edges) {
            int u = edge.source;
            int v = edge.destination;
            int uRoot = ds.find(u);
            int vRoot = ds.find(v);
            
            // If adding this edge doesn't create a cycle, include it in MST
            if (uRoot != vRoot) {
                MST.push_back(edge);
                ds.unionSet(uRoot, vRoot);
            }
        }
        
        return MST;
    }
};

int main() {
    // Example: Suppose we have 4 offices (0, 1, 2, 3) with the following connections and costs:
    // 0-1: $10, 0-2: $6, 0-3: $5, 1-2: $15, 1-3: $8, 2-3: $7
    Graph graph(4);
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 6);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 2, 15);
    graph.addEdge(1, 3, 8);
    graph.addEdge(2, 3, 7);

    // Find Minimum Spanning Tree (MST)
    vector<Edge> MST = graph.findMST();

    // Display Minimum Spanning Tree
    cout << "Minimum Spanning Tree (MST) edges: " << endl;
    for (const Edge& edge : MST) {
        cout << edge.source << " - " << edge.destination << " : $" << edge.weight << endl;
    }

    return 0;
}
