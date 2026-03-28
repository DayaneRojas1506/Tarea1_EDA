#include <iostream>
class BinomialHeap{
    private:
        struct Node{
            int key; //clave
            int cantidadH; //cantidad de hijos
            Node* parent; //Nodo padre
            Node* child; //Nodo hijo
            Node* brother; //Nodo hermano derecho
            Node(int k){
                key=k;
                cantidadH = 0;
                parent = child = brother = nullptr;
            }
        };
        Node* heap;
    public:
        //Constructor
        BinomialHeap(){
            head=nullptr;
        }
        //Función de union
}
int main() {
}