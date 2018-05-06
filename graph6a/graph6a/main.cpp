// Pre Final Problem1
// By Alana Martin

// Author: John Maslanka
// Date: 27-Dec-2002
// Installation: Home PC with MicroSoft Visual C++ V6.0
// Elementary Illustration of a Directed Graph adapted from
// Figures 15.2 and 15.3 in Main and Savitch, but terminal
// input is available. The program asks the user how many
// vertices to enter. If the user enters 100,
// the vertex numbers are from 0 to 99. The user then enters the
// edges by giving the start vertex followed by the end vertex
// up to the product of the number of vertices times the
// number of vertices less 1, or you can terminate edge input
// with control-z. Note: FWIW an edge looping back to its first
// vertex is disallowed in this code. Also, an edge with a
// beginning vertex greater than its ending vertex is not allowed.
//
// May 2016 Thomas Dattilo contributed Edge class, also Wrapper
// code for tree_level recursive method.
//
// JM 4/23/18 Add Test to input to produce pass-thru graph.
// JM 4/26/18  The test from 4/23 commented out.

#include <iostream>
#include <cstdlib>
#include <queue>
using namespace std;

class Edge {
private:
    int arraySize;
    bool **edgeArray;
public:
    Edge(int size) {
        arraySize = size;
        edgeArray = new bool*[size];
        for (int x = 0; x<size; x++) {
            edgeArray[x] = new bool[size];
        }
        for (int y = 0; y<size; y++) {
            for (int z = 0; z<size; z++) {
                edgeArray[y][z] = false;
            }
        }
    }
    Edge(const Edge& original) {
        this->arraySize = original.arraySize;
        this->edgeArray = new bool*[arraySize];
        for (int x = 0; x<arraySize; x++) {
            this->edgeArray[x] = new bool[arraySize];
        }
        for (int y = 0; y<arraySize; y++) {
            for (int z = 0; z<arraySize; z++) {
                this->edgeArray[y][z] = original.edgeArray[y][z];
            }
        }
    }
    bool getEdge(int from, int to) const {
        return edgeArray[from][to];
    }
    void setEdge(int from, int to) {
        edgeArray[from][to] = true;
    }
    void useEdge(int from, int to) {
        edgeArray[from][to] = false;
    }
};

class Graph {
private:
    Edge    *edge;
    int     count_of_vertices;
public:
    Graph() { count_of_vertices = 0; }
    int size() const { return count_of_vertices; }
    void add_vertexes(const int);
    void add_edge(int source, int target);
    bool get_edge(int a, int b) { return edge->getEdge(a, b); }
    bool is_edge(int source, int target) const;
    void tree_level(int, int);  // Wrapper
    void tree_level(int, int, const Edge&);
    Edge* getEdges();
};

Edge* Graph::getEdges() {
    return edge;
}

void Graph::add_vertexes(const int nr) {
    count_of_vertices = nr;
    edge = new Edge(count_of_vertices);
}

void Graph::add_edge(int source, int target) {
    edge->setEdge(source, target);
}

bool Graph::is_edge(int source, int target) const {
    return edge->getEdge(source, target);
}

void Graph::tree_level(int x, int level)
{
    int j, i;
    ++level;
    Edge temp(*edge);
    for (j = 0; j < size(); ++j)
    {
        if (edge->getEdge(x, j))
        {
            for (i = 1; i < level; cout << "   ", ++i);
            cout << "  (" << x << ", " << j << ")" << endl;
            temp.useEdge(x, j);
            if (x != j)
                tree_level(j, level, temp);
        }
    }
}

void Graph::tree_level(int x, int level, const Edge &original)
{
    if ( 0 != x ) {
        int j, i;
        ++level;
        Edge temp(original);
        for (j = 0; j < size(); ++j)
        {
            if (original.getEdge(x, j))
            {
                for (i = 1; i < level; cout << "   ", ++i);
                cout << "  (" << x << ", " << j << ")" << endl;
                temp.useEdge(x, j);
                if (x != j)
                    tree_level(j, level, temp);
            }
        }
    }
}
int main() {
    Graph G;
    int i, j, nr, x;
    cout << "Enter number of vertices (nr > 1) ";
    cin >> nr;
    if (cin.eof())
        exit(1);
    else
        if(!cin.good() || nr < 2)
        {
            cout << "Invalid input for number of vertices. "
            << "Program terminating." << endl;
            exit(2);
        }
    G.add_vertexes(nr);
    cout << "Number of vertices is " << G.size() << endl << endl;
    cout << "Beginning and Terminating vertexes must be between 0 and "
    << (nr - 1) << " inclusive" << endl;
    cout << "Beginning and terminating vertexes must not be "
    << "the same for an edge in this graph." << endl;
    cout << "Enter EOF at keyboard to view displays." << endl;
    for (x = 0; x < nr*(nr - 1) && !cin.eof();)
    {
        cout << "Enter the two bounding vertexes of an edge or EOF" << endl;
        cin >> i >> j;
        if (!cin.eof())
        {
            if (!cin.good())
            {
                cout << "Invalid input for an edge. " << endl;
                cin.clear();
                cin.ignore(256);
                cout << "Enter the two bounding Vertexes of an edge or EOF" << endl;
            }
            else if (i >= nr || j >= nr)
                cout << "Value of Beginning or End vertex must not be >= "
                << nr << endl;
            else if (i == j)
                cout << "Beginning and terminating vertexes must not be "
                << "the same for an edge in this graph." << endl;
            //            else if (i > j)
            //                cout << "Beginning vertex must not be greater than "
            //                << "terminating vertex for an edge in this graph." << endl;
            else
            {
                G.add_edge(i, j);
                ++x;
            }
        }
    }
    cout << "Directed List of Nearest Neighbor Vertexes for each Vertex"
    << endl;
    for (i = 0; i < G.size(); ++i)
    {
        cout << "For Vertex " << i << "     ";
        for (j = 0; j < G.size(); ++j)
            if (G.is_edge(i, j))
                cout << "   " << j;
        cout << endl;
    }
    cout << endl;
    system("PAUSE");
    for (i = 0; i < G.size(); ++i)
    {
        cout << "Depth-First Traversal of Trees on Graph "
        << "starting with Vertex " << i << endl;
        G.tree_level(i, 0);
    }
    system("PAUSE");
    return 0;
}
