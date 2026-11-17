#include <iostream>
using namespace std;

// Tree Node
class Node
{
public:
    int serviceID;
    int cost;
    Node* left;
    Node* right;

    Node(int id, int c)
    {
        serviceID = id;
        cost = c;
        left = right = NULL;
    }
};

// Binary Search Tree
class BST
{
public:
    Node* root;

    BST()
    {
        root = NULL;
    }

    Node* insert(Node* root, int id, int cost)
    {
        if (root == NULL)
            return new Node(id, cost);

        if (cost < root->cost)
            root->left = insert(root->left, id, cost);
        else
            root->right = insert(root->right, id, cost);

        return root;
    }

    void insert(int id, int cost)
    {
        root = insert(root, id, cost);
    }
};

// Count total nodes
int countNodes(Node* root)
{
    if (root == NULL)
        return 0;

    return 1 + countNodes(root->left)
             + countNodes(root->right);
}

// Store nodes in sorted order
void inorder(Node* root, Node* arr[], int& index)
{
    if (root == NULL)
        return;

    inorder(root->left, arr, index);

    arr[index++] = root;

    inorder(root->right, arr, index);
}

// Print selected subset
void printSubset(Node* selected[], int size)
{
    cout << "{ ";

    for (int i = 0; i < size; i++)
    {
        cout << "Service " << selected[i]->serviceID
             << "(" << selected[i]->cost << ") ";

    }

    cout << "}";
}

// Backtracking function
void findSubsets(Node* nodes[],
                 int n,
                 int index,
                 long long currentSum,
                 long long target,
                 Node* selected[],
                 int selectedCount,
                 int& solutions)
{
    // Target reached
    if (currentSum == target)
    {
        cout << "\nSubset " << ++solutions << ": ";

        printSubset(selected, selectedCount);

        cout << " = " << target << endl;

        return;
    }

    // All nodes considered
    if (index == n)
        return;

    // Pruning using BST ordering
    if (currentSum + nodes[index]->cost > target)
        return;

    // Choice 1: Include current node
    selected[selectedCount] = nodes[index];

    findSubsets(nodes,
                n,
                index + 1,
                currentSum + nodes[index]->cost,
                target,
                selected,
                selectedCount + 1,
                solutions);

    // Backtrack: remove current node
    selected[selectedCount] = NULL;

    // Choice 2: Exclude current node
    findSubsets(nodes,
                n,
                index + 1,
                currentSum,
                target,
                selected,
                selectedCount,
                solutions);
}

int main()
{
    BST tree;

    // Insert service IDs and monthly costs
    tree.insert(1, 10);
    tree.insert(2, 5);
    tree.insert(3, 12);
    tree.insert(4, 3);
    tree.insert(5, 7);

    long long target = 15;

    int n = countNodes(tree.root);

    // Arrays for sorted nodes and selected subset
    Node** nodes = new Node*[n];
    Node** selected = new Node*[n];

    for (int i = 0; i < n; i++)
        selected[i] = NULL;

    int index = 0;

    // Store BST nodes in sorted order
    inorder(tree.root, nodes, index);

    int solutions = 0;

    cout << "Subsets with total cost " << target << ":\n";

    findSubsets(nodes,
                n,
                0,
                0,
                target,
                selected,
                0,
                solutions);

    if (solutions == 0)
        cout << "No matching subsets found.";

    delete[] nodes;
    delete[] selected;

    return 0;
}

