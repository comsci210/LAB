#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

#define FILENAME "input.txt"
#define N_NODES  10

// A tree node
    struct Node {
    int val;      // The (integer) value
    int bf;       // Balance factor of this node
    Node *left;   // Left child pointer
    Node *right;  // Right child pointer
};

// Insert a node into the tree, balancing if needed.
// *tp is a pointer to the root of the tree (reference variable);
// 'nv' is the new (integer) value to add.
// 'allNodes' is an array of all of the nodes we've allocated, for easy clean-up
// 'allNodesN' is the number of nodes set in allNodes

int insertNode(Node *&tp, int nv, Node *allNodes[], int allNodesN) {
    Node *newp;
    if (tp == 0) {
        // Setup our new node
        newp = new Node;
        newp->val = nv;
        newp->bf = 0;
        newp->left = 0;
        newp->right = 0;
        tp = newp;
        allNodes[allNodesN] = newp;
        return (1);
    }
    
    // Ignore existing values
    if (nv == tp->val)
        return (0);
        
    if (nv < tp->val) {
        // Insert into the LEFT subtree
    } 
    
    else {
        // Insert into the RIGHT subtree
    }
}

int main() {
    Node *rootp = 0;           // Root of the tree
    Node *allNodes[N_NODES];   // Bookkeeping array so we can free everything
    string ent;                // Input string from file
    ifstream infile(FILENAME); // Input file
    int nums[N_NODES];         // Input integers
    int i, j, status;
    
    while (true) {
        // Read a set of insertions
        i = 0, j = 0;
        rootp = 0;
        while (getline(infile, ent)) {
            nums[i++] = atoi(ent.c_str());
            if (i == N_NODES)
            break;
        }
        
        if (i != N_NODES)
            break;
        
        cout << "Read " << i << " nodes." << endl;
        
        for (; j < N_NODES; j++) {
            status = insertNode(rootp, nums[j], allNodes, j);
            if (status == -1)
            break;
        }
        
        if (j == N_NODES) {
            cout << "No imbalances detected." << endl;
        }
        
        // Free everything
        for (int k = 0; k < j; k++) {
            delete allNodes[k];
            allNodes[k] = 0;
        }
    }
    
    cout << "Done." << endl;
    return (0);
}
