#include <iostream>
using namespace std;
struct Node {
    int key;
    int priority;
    Node* left;
    Node* right;

    Node(int k, int p) : key(k), priority(p), left(nullptr), right(nullptr) {}
};

class Treap {
public:
    Node* head = nullptr;
    void split(Node* root, int key, Node*& left, Node*& right) {
        if (!root) {
            left = right = nullptr;
        }
        else if (root->key <= key) {
            split(root->right, key, root->right, right);
            left = root;
        }
        else {
            split(root->left, key, left, root->left);
            right = root;
        }
    }

    Node* merge(Node* left, Node* right) {
        if (!left || !right) {
            return left ? left : right;
        }

        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            return left;
        }
        else {
            right->left = merge(left, right->left);
            return right;
        }
    }

    void insert(int key, int priority) {
        Node* newNode = new Node(key, priority);
        Node* left, * right;
        split(head, key, left, right);
        head = merge(merge(left, newNode), right);
    }

    void remove(int key) {
        Node* left, * right, * mid;
        split(head, key - 1, left, right);
        split(right, key, mid, right);
        delete mid;
        head = merge(left, right);
    }

    void printTree(Node* root, string margin) {
        if (root) {          
            printTree(root->right, margin + "   ");
            cout << margin + "   " << root->key << " (" << root->priority << ") " << endl;
            printTree(root->left, margin + "   ");
        }
    }
};
int main() {
    Treap treap;
    int option;
    int value;
    treap.insert(15, 55);
    treap.insert(10, 28);
    treap.insert(25, 15);
    treap.insert(15, 55);
    while (true) {
        cout << "1.Insert node" << endl;
        cout << "2.Delete node" << endl;
        cout << "3.Print" << endl;
        cin >> option;
        switch (option) {
        case 1:
            cout << "Enter value" << endl;
            cin >> value;
            treap.insert(value, rand());
            break;
        case 2:
            cout << "Enter value" << endl;
            cin >> value;
            treap.remove(value);
            break;
        case 3:
            treap.printTree(treap.head, "");
        }
    }
}