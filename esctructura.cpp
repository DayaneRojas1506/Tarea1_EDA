#include <iostream>
class BinomialHeap{
    private:
        struct Node{
            int key; //clave
            int degree; //cantidad de hijos
            Node* parent; //Nodo padre
            Node* child; //Primer hijo
            Node* sibling; //Nodo hermano derecho
            Node(int k){
                key=k;
                degree = 0;
                parent = child = sibling = nullptr;
            }
        };
        Node* head;
    public:
        //Constructor
        BinomialHeap(){
            head=nullptr;
        }
        //Función de merge
        Node* merge(Node* b1,Node* b2){
            if(!b1){
                return b2;
            }
            else if(!b2){
                return b1;
            }
            Node* head = nullptr;
            Node* tail = nullptr;
            // inicializando head
        }
}
int main() {
}
