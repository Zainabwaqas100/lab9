#include <iostream>
using namespace std;

// Container node
class ContainerNode
{
public:
    int id;
    int weight;
    ContainerNode* next;

    ContainerNode(int i, int w)
    {
        id = i;
        weight = w;
        next = NULL;
    }
};

// Singly Linked List
class ContainerList
{
public:
    ContainerNode* head;
    int count;

    ContainerList()
    {
        head = NULL;
        count = 0;
    }

    void insert(int id, int weight)
    {
        ContainerNode* newNode = new ContainerNode(id, weight);

        if (head == NULL)
        {
            head = newNode;
        }
        else
        {
            ContainerNode* temp = head;

            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newNode;
        }

        count++;
    }
};

// Truck node
class TruckNode
{
public:
    int capacity;
    TruckNode* next;

    TruckNode(int c)
    {
        capacity = c;
        next = NULL;
    }
};

// Queue of trucks
class TruckQueue
{
public:
    TruckNode* front;
    TruckNode* rear;
    int count;

    TruckQueue()
    {
        front = rear = NULL;
        count = 0;
    }

    void enqueue(int capacity)
    {
        TruckNode* newNode = new TruckNode(capacity);

        if (rear == NULL)
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }

        count++;
    }
};

// Calculate total remaining truck capacity
int totalCapacity(TruckNode* truck, int remaining)
{
    int total = remaining;

    if (truck != NULL)
        truck = truck->next;

    while (truck != NULL)
    {
        total += truck->capacity;
        truck = truck->next;
    }

    return total;
}

// Backtracking function
bool solve(ContainerNode* container,
           TruckNode* truck,
           int remainingCapacity,
           int remainingWeight,
           int containerIndex,
           int truckIndex,
           int assignedTruck[])
{
    
    if (container == NULL)
        return true;


    if (truck == NULL)
        return false;

   
    if (remainingWeight >
        totalCapacity(truck, remainingCapacity))
    {
        return false;
    }

    // Choice 1: Assign current container to current truck
    if (container->weight <= remainingCapacity)
    {
        assignedTruck[containerIndex] = truckIndex;

        if (solve(container->next,
                  truck,
                  remainingCapacity - container->weight,
                  remainingWeight - container->weight,
                  containerIndex + 1,
                  truckIndex,
                  assignedTruck))
        {
            return true;
        }

        // Backtrack: undo assignment
        assignedTruck[containerIndex] = -1;
    }

    // Choice 2: Skip current truck and try next truck
    return solve(container,
                 truck->next,
                 truck->next == NULL ? 0 : truck->next->capacity,
                 remainingWeight,
                 containerIndex,
                 truckIndex + 1,
                 assignedTruck);
}


void printAssignments(ContainerList& containers,
                      TruckQueue& trucks,
                      int assignedTruck[])
{
    TruckNode* truck = trucks.front;
    int truckIndex = 0;

    while (truck != NULL)
    {
        cout << "\nTruck " << truckIndex + 1 << ": ";

        bool found = false;
        int i = 0;

        ContainerNode* temp = containers.head;

        while (temp != NULL)
        {
            if (assignedTruck[i] == truckIndex)
            {
                cout << "C" << temp->id
                     << " (" << temp->weight << " tons) ";

                found = true;
            }

            temp = temp->next;
            i++;
        }

        if (!found)
            cout << "No containers assigned";

        truck = truck->next;
        truckIndex++;
    }
}

int main()
{
    ContainerList containers;
    TruckQueue trucks;

    // Insert containers
    containers.insert(1, 4);
    containers.insert(2, 3);
    containers.insert(3, 5);
    containers.insert(4, 2);


    trucks.enqueue(7);
    trucks.enqueue(7);
    trucks.enqueue(5);

    int* assignedTruck = new int[containers.count];

    for (int i = 0; i < containers.count; i++)
        assignedTruck[i] = -1;

    int totalWeight = 0;

    ContainerNode* temp = containers.head;

    while (temp != NULL)
    {
        totalWeight += temp->weight;
        temp = temp->next;
    }

    bool result = solve(containers.head,
                        trucks.front,
                        trucks.front == NULL ? 0 : trucks.front->capacity,
                        totalWeight,
                        0,
                        0,
                        assignedTruck);

    if (result)
    {
        cout << "All containers successfully loaded!\n";

        printAssignments(containers, trucks, assignedTruck);
    }
    else
    {
        cout << "Insufficient truck capacity.";
    }

    delete[] assignedTruck;

    return 0;
}
