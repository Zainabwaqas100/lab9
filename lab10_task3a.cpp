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

// BST
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

// Dynamic path array
class Path
{
public:
    int* arr;
    int size;
    int capacity;

    Path()
    {
        capacity = 10;
        size = 0;
        arr = new int[capacity];
    }

    void push(int value)
    {
        if (size == capacity)
        {
            capacity *= 2;

            int* temp = new int[capacity];

            for (int i = 0; i < size; i++)
                temp[i] = arr[i];

            delete[] arr;
            arr = temp;
        }

        arr[size++] = value;
    }

    void pop()
    {
        if (size > 0)
            size--;
    }

    void print()
    {
        for (int i = 0; i < size; i++)
        {
            cout << arr[i];

            if (i != size - 1)
                cout << " -> ";
        }
    }

    ~Path()
    {
        delete[] arr;
    }
};

// Find paths starting from a particular node
void findFromNode(Node* root, int target,
                  int currentSum, Path& path,
                  int& count)
{
    if (root == NULL)
        return;

    // Add current node
    path.push(root->cost);
    currentSum += root->cost;

    // Check target
    if (currentSum == target)
    {
        cout << "Path " << ++count << ": ";
        path.print();
        cout << " = " << target << endl;
    }

    // Explore left and right
    findFromNode(root->left, target,
                 currentSum, path, count);

    findFromNode(root->right, target,
                 currentSum, path, count);

    // Backtrack
    path.pop();
}

// Start a path from every node
void findAllPaths(Node* root, int target, int& count)
{
    if (root == NULL)
        return;

    Path path;

    findFromNode(root, target, 0, path, count);

    findAllPaths(root->left, target, count);
    findAllPaths(root->right, target, count);
}

int main()
{
    BST tree;

    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(12, 12);
    tree.insert(3, 3);
    tree.insert(7, 7);

    int target = 15;
    int count = 0;

    cout << "Paths with sum " << target << ":\n";

    findAllPaths(tree.root, target, count);

    if (count == 0)
        cout << "No matching paths found.";

    return 0;
}
