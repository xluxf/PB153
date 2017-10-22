#define BRICK_BENCHMARK_REG
#define BRICK_BENCHMARK_MAIN

// benchmark of hashtables

/* ./bench category:stack | gnuplot > soubor.pdf */

#include "hashTables.h"
#include <brick-benchmark>
#include <stack>
#include <deque>
#include <list>
#include <queue>


using namespace brick;

struct HashTable : benchmark::Group
{

    HashTable()
    {

        x.type = benchmark::Axis::Quantitative;
        x.name = "items";
        x.min = 100000;
        x.max = 1000000;
        x.step = 100000;

        y.type = benchmark::Axis::Qualitative;
        y.name = "implementation";
        y.min = 1;
        y.max = 4;
        y._render = []( int i )
        {
            switch ( i )
            {
                case 1: return "set";
                case 2: return "unordered set";
                case 3: return "linked list";
                case 4: return "linear probing";
            }
        };
    }

    std::string describe() { return "category:hashInsert"; }

    BENCHMARK( insert )
    {
        switch ( q )
        {
            case 1: do_insert< HashTableS<int> >(); break;
            case 2: do_insert< HashTableUS<int> >(); break;
            case 3: do_insert< HashTableLL<int> >(); break;
            case 4: do_insert< HashTableLPR<int> >(); break;
        }
    }

    template< class H>
    void do_insert()
    {
        H table;
        srand ( time(NULL) );
        for ( int i = 0; i < p; ++i ) {
            int number = rand();
            table.insert(number);
        }
    }
};

struct HashTable_erase : benchmark::Group
{

    HashTable_erase()
    {

        x.type = benchmark::Axis::Quantitative;
        x.name = "items";
        x.min = 100000;
        x.max = 1000000;
        x.step = 100000;

        y.type = benchmark::Axis::Qualitative;
        y.name = "implementation";
        y.min = 1;
        y.max = 4;
        y._render = []( int i )
        {
            switch ( i )
            {
                case 1: return "set";
                case 2: return "unordered set";
                case 3: return "linked list";
                case 4: return "linear probing";
            }
        };
    }

    std::string describe() { return "category:hashErase"; }


    BENCHMARK( erase )
    {
        switch ( q )
        {
            case 1: do_erase< HashTableS<int> >(); break;
            case 2: do_erase< HashTableUS<int> >(); break;
            case 3: do_erase< HashTableLL<int> >(); break;
            case 4: do_erase< HashTableLPR<int> >(); break;
        }
    }

    template< class H>
    void do_erase()
    {
        H table;

        for ( int i = 0; i < p; ++i ) {
            table.insert(i);
        }
        for ( int i = 1; i < p; ++i ) {
            table.erase(i);
        }
        
    }
};

struct Node {
    std::set<Node *> child;
    int degree;
    int value;

    Node( const int value ) : value(value) {}
    void addChild (Node * new_child) {
        child.insert(new_child);
        degree++;

    }

};

class Graph {

private:
    std::vector <Node *> vertices;
    int size;

public:
    Node * root;

    Graph(const int size) : size(size) {

        // initialize all vertices
        std::vector <Node *> vertices;
        for (int i = 0; i < size; ++i) {
            Node * new_node = new Node(i);
            vertices.push_back(new_node);
        }

        // set random connections
        srand ( time(NULL) );
        for (int i = 1; i < size; i++) {
            int number = rand();
            while (number % 1000 == 0) {  // 
                int parent = number % i;
                vertices[parent]->addChild(vertices[i]);
                number = rand();
            }
        }

        // set root
        root = vertices[0];
    }

    void print() {
        std::cout << "list of nodes and their childs.\n";
        for (int i = 0; i < size; i++) {
            std::cout << i << ": ";
            Node * node_i = vertices[i];
            std::set<Node *> set = node_i->child;
            for (auto it=set.begin(); it!=set.end(); ++it)
                std::cout << " " << *it;
            std::cout << " \n";

        }
    }

    bool findBFS(const int & value ) {
        std::queue< Node *, std::deque< Node *, std::allocator< Node * > > > queue;
        HashTableLPR< Node * > table;
        table.insert(root);
        queue.push(root);
        while (queue.size() != 0 ) {
            Node * vertex = queue.front();
            std::set<Node *> set = vertex->child;
            for (auto it=set.begin(); it!=set.end(); ++it) {
                    Node * tmp = *it;
                    if (tmp->value == value)
                        return true;
                    if (!table.find(tmp)) {
                        table.insert(tmp);
                        queue.push(tmp);
                    }
                }
            queue.pop();
        }
        return false;
    }

};

struct BFS : benchmark::Group
{
    BFS()
    {
        x.type = benchmark::Axis::Quantitative;
        x.name = "items";
        x.min = 100000000;
        x.max = 1000000000;
        x.step = 100000000;

        y.type = benchmark::Axis::Qualitative;
        y.name = "implementation";
        y.min = 1;
        y.max = 1;
        y._render = []( int i )
        {
            switch ( i )
            {
                case 1: return "BFS";
            }
        };
    }

    std::string describe() { return "category:BFS5"; }

    BENCHMARK( insert )
    {
        switch ( q )
        {
            case 1: 
                makeGraph();
                break;
        }
    }


    void makeGraph()
    {
        Graph * g = new Graph(q);
        g->findBFS(1000000001);
    }

};



