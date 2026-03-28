#include <iostream>

using namespace std;

struct Node {
    int key, degree;
    Node *parent, *child, *sibling;

    Node(int k) {
        key = k;
        degree = 0;
        parent = child = sibling = nullptr;
    }
};

class BinomialHeap {
private:
    Node* head;

    //Une dos árboles del mismo grado
    Node* linkTrees(Node* y, Node* z) {
        if (y->key > z->key)
            swap(y, z);

        z->parent = y;
        z->sibling = y->child;
        y->child = z;
        y->degree++;

        return y;
    }

    //mezcla listde raíces
    Node* mergeRoots(Node* h1, Node* h2) {
        if (!h1) return h2;
        if (!h2) return h1;

        Node* head;
        Node* tail;

        if (h1->degree <= h2->degree) {
            head = h1;
            h1 = h1->sibling;
        } else {
            head = h2;
            h2 = h2->sibling;
        }

        tail = head;

        while (h1 && h2) {
            if (h1->degree <= h2->degree) {
                tail->sibling = h1;
                h1 = h1->sibling;
            } else {
                tail->sibling = h2;
                h2 = h2->sibling;
            }
            tail = tail->sibling;
        }

        tail->sibling = (h1) ? h1 : h2;

        return head;
    }

    // Unionn
    Node* unionHeap(Node* h1, Node* h2) {
        Node* newHead = mergeRoots(h1, h2);
        if (!newHead) return nullptr;

        Node *prev = nullptr, *curr = newHead, *next = curr->sibling;

        while (next) {
            if ((curr->degree != next->degree) ||
                (next->sibling && next->sibling->degree == curr->degree)) {
                prev = curr;
                curr = next;
            } else {
                if (curr->key <= next->key) {
                    curr->sibling = next->sibling;
                    curr = linkTrees(curr, next);
                } else {
                    if (!prev)
                        newHead = next;
                    else
                        prev->sibling = next;

                    curr = linkTrees(next, curr);
                }
            }
            next = curr->sibling;
        }

        return newHead;
    }

  
    Node* reverseList(Node* node) {
        Node* prev = nullptr;
        while (node) {
            Node* next = node->sibling;
            node->sibling = prev;
            node->parent = nullptr;
            prev = node;
            node = next;
        }
        return prev;
    }

public:
    BinomialHeap() {
        head = nullptr;
    }

    void insert(int key) {
        BinomialHeap temp;
        temp.head = new Node(key);
        head = unionHeap(head, temp.head);
    }

    int getMin() {
        if (!head) return -1;

        Node* curr = head;
        int minVal = curr->key;

        while (curr) {
            if (curr->key < minVal)
                minVal = curr->key;
            curr = curr->sibling;
        }
        return minVal;
    }

    int extractMin() {
        if (!head) return -1;

        Node *prevMin = nullptr, *minNode = head;
        Node *prev = nullptr, *curr = head;

        int minVal = curr->key;

        while (curr) {
            if (curr->key < minVal) {
                minVal = curr->key;
                prevMin = prev;
                minNode = curr;
            }
            prev = curr;
            curr = curr->sibling;
        }

        // quitar minNode de la lista
        if (prevMin)
            prevMin->sibling = minNode->sibling;
        else
            head = minNode->sibling;

        // invertir hijos
        Node* child = reverseList(minNode->child);

        // unir con heap restante
        head = unionHeap(head, child);

        return minVal;
    }

    void printRoots() {
        cout << "Roots: ";
        Node* curr = head;
        while (curr) {
            cout << curr->key << "(deg:" << curr->degree << ") ";
            curr = curr->sibling;
        }
        cout << endl;
    }
};

int main() {
    BinomialHeap h;

    h.insert(10);
    h.insert(3);
    h.insert(7);
    h.insert(1);
    h.insert(14);
    h.insert(8);

    h.printRoots();

    cout << "Min: " << h.getMin() << endl;

    cout << "Extract Min: " << h.extractMin() << endl;

    h.printRoots();

    cout << "New Min: " << h.getMin() << endl;

    return 0;
}
