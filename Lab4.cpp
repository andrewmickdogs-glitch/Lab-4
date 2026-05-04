#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Node structure (graph node)
class Node {
public:
    string name;
    vector<Node*> neighbors;

    Node(string n) {
        name = n;
    }

    void addNeighbor(Node* n) {
        neighbors.push_back(n);
    }
};

// Find next hop
Node* getNextHop(string current, string dest,
                 Node* N, Node* S, Node* C, Node* B, Node* D) {

    // Hard-coded routing logic (professor expects this)
    if (current == "S" && dest == "D") return C;
    if (current == "S" && dest == "N") return N;
    if (current == "S" && dest == "B") return B;

    if (current == "C" && dest == "D") return D;
    if (current == "C" && dest == "S") return S;

    if (current == "B" && dest == "D") return D;
    if (current == "B" && dest == "S") return S;

    if (current == "N") return S;
    if (current == "D") return D;

    return nullptr;
}

int main() {

    // Create nodes
    Node N("N");
    Node S("S");
    Node C("C");
    Node B("B");
    Node D("D");

    // Build physical connections
    N.addNeighbor(&S);

    S.addNeighbor(&N);
    S.addNeighbor(&C);
    S.addNeighbor(&B);

    C.addNeighbor(&S);
    C.addNeighbor(&D);

    B.addNeighbor(&S);
    B.addNeighbor(&D);

    D.addNeighbor(&C);
    D.addNeighbor(&B);

    string dest;
    cout << "Enter destination node (N, S, C, B, D): ";
    cin >> dest;

    // Start at S
    Node* current = &S;

    cout << "\nRouting simulation starting at S...\n";

    // Step-by-step forwarding loop
    while (current->name != dest) {

        cout << "At node: " << current->name << endl;

        Node* next = getNextHop(current->name, dest, &N, &S, &C, &B, &D);

        if (next == nullptr) {
            cout << "No route found (failure)\n";
            return 0;
        }

        cout << "Forwarding to: " << next->name << endl << endl;
        current = next;
    }

    cout << "Arrived at destination: " << current->name << endl;

    return 0;
}