#include <iostream>
using namespace std;

// Operation
class Operation
{
public:
    char symbol;
    int operand;

    Operation()
    {
        symbol = '+';
        operand = 0;
    }

    Operation(char s, int o)
    {
        symbol = s;
        operand = o;
    }
};

// Stack Node
class StackNode
{
public:
    Operation op;
    StackNode* next;

    StackNode(Operation o)
    {
        op = o;
        next = NULL;
    }
};

// Operation Stack
class Stack
{
public:
    StackNode* top;

    Stack()
    {
        top = NULL;
    }

    void push(Operation op)
    {
        StackNode* newNode = new StackNode(op);

        newNode->next = top;
        top = newNode;
    }

    void pop()
    {
        if (top == NULL)
            return;

        StackNode* temp = top;
        top = top->next;

        delete temp;
    }

    bool isEmpty()
    {
        return top == NULL;
    }
};

// Print stack in execution order
void printOperations(StackNode* current)
{
    if (current == NULL)
        return;

    printOperations(current->next);

    cout << current->op.symbol;

    if (current->op.symbol != '*')
        cout << current->op.operand;
    else
        cout << current->op.operand;

    cout << " ";
}

// Apply an operation
long long applyOperation(long long current, Operation op)
{
    switch (op.symbol)
    {
        case '+':
            return current + op.operand;

        case '-':
            return current - op.operand;

        case '*':
            return current * op.operand;

        case '/':
            return current / op.operand;
    }

    return current;
}

// Backtracking function
void solve(long long current,
           long long target,
           int operationsUsed,
           int maxOperations,
           long long overflowBound,
           Operation operations[],
           int operationCount,
           Stack& s,
           int& solutions)
{
    // Target reached: print this sequence
    if (current == target)
    {
        cout << "\nSequence " << ++solutions << ": ";

        if (s.isEmpty())
            cout << "No operations";

        printOperations(s.top);

        cout << " = " << target << endl;
    }

    // Maximum operation budget reached
    if (operationsUsed == maxOperations)
        return;

    // Try every allowed operation
    for (int i = 0; i < operationCount; i++)
    {
        Operation op = operations[i];

        // Division by zero is invalid
        if (op.symbol == '/' && op.operand == 0)
            continue;

        // Exact integer division only
        if (op.symbol == '/' && current % op.operand != 0)
            continue;

        // Calculate next state
        long long nextValue = applyOperation(current, op);

        // Pruning: negative or overflow value
        if (nextValue < 0 || nextValue > overflowBound)
            continue;

        // Make a choice
        s.push(op);

        // Explore the next state
        solve(nextValue,
              target,
              operationsUsed + 1,
              maxOperations,
              overflowBound,
              operations,
              operationCount,
              s,
              solutions);

        // Undo the choice
        s.pop();
    }
}

int main()
{
    long long initial, target, overflowBound;
    int maxOperations;

    cout << "Enter initial state: ";
    cin >> initial;

    cout << "Enter target state: ";
    cin >> target;

    cout << "Enter maximum operation budget: ";
    cin >> maxOperations;

    cout << "Enter overflow bound: ";
    cin >> overflowBound;

    int operationCount;

    cout << "Enter number of allowed operations: ";
    cin >> operationCount;

    Operation* operations = new Operation[operationCount];

    cout << "Enter operations (symbol operand):\n";

    for (int i = 0; i < operationCount; i++)
    {
        char symbol;
        int operand;

        cin >> symbol >> operand;

        operations[i] = Operation(symbol, operand);
    }

    Stack s;
    int solutions = 0;

    if (initial >= 0 && initial <= overflowBound &&
        maxOperations >= 0)
    {
        solve(initial,
              target,
              0,
              maxOperations,
              overflowBound,
              operations,
              operationCount,
              s,
              solutions);
    }

    if (solutions == 0)
        cout << "\nNo valid sequence found.";

    delete[] operations;

    return 0;
}
