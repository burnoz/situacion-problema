#include <iostream>
#include <sstream>
#include <cstring>
#include <math.h>
#include <string>

using namespace std;

// Clase para restaurantes
class Restaurant{
    public:
        string name;
        int numOrders;
        float revenue;

        // Constructor sin parametros
        Restaurant(){
            name = "";
            numOrders = 0;
            revenue = 0;
        }

        // Constructor con parametros
        Restaurant(string name, int numOrders, float revenue){
            this->name = name;
            this->numOrders = numOrders;
            this->revenue = revenue;
        }

        void show();
};

// Muestra los datos de un restaurante
// Complejidad: O(1)
void Restaurant::show(){
    cout << name << " " << numOrders << " " << revenue << endl;
}

// Funcion para obtener la ganancia de una orden
// Complejidad: O(1)
float get_revenue(string order){
    int revenue_start_index = order.find("(");
    int revenue_end_index = order.find(")");

    string revenue = order.substr(revenue_start_index + 1, revenue_end_index - revenue_start_index - 1);

    return stof(revenue);
}

// Funcion para obtener el nombre del restaurante de una orden
// Complejidad: O(1)
string get_restaurant(string order){
    string restaurant;

    // Encuentra los indices en los que inicia y termina el nombre del restaurante
    int restaurant_start_index = order.find("R:");
    int restaurant_end_index = order.find(" O:");

    // Extrae el nombre del restaurante
    restaurant = order.substr(restaurant_start_index + 2, restaurant_end_index - restaurant_start_index - 2);
    
    return restaurant;
}

// Clase para max heap de restaurantes
class Heap{
    public:
        Restaurant *restaurants;
        string type; // "revenue" o "numOrdenes"
        int maxSize;
        int currentSize;

        // Constructor
        Heap(int maxSize, string type){
            this->maxSize = maxSize;
            this->currentSize = 0;
            this->type = type;
            this->restaurants = new Restaurant[maxSize];
        }

        // Destructor
        ~Heap(){
            delete[] restaurants;
            maxSize = 0;
            currentSize = 0;
        }

        // Funciones
        bool isEmpty();
        bool isFull();

        int parent(int);
        int left(int);
        int right(int);

        void push(Restaurant);
        Restaurant pop();
        void heapify(int);
        void swap(int, int);
        void show();
};

// Verifica si el heap esta vacio
// Complejidad: O(1)
bool Heap::isEmpty(){
    return currentSize == 0;
}

// Verifica si el heap esta lleno
// Complejidad: O(1)
bool Heap::isFull(){
    return currentSize == maxSize;
}

// Devuelve el indice del padre
// Complejidad: O(1)
int Heap::parent(int i){
    return (i - 1) / 2;
}

// Devuelve el indice del hijo izquierdo
// Complejidad: O(1)
int Heap::left(int i){
    return 2 * i + 1;
}

// Devuelve el indice del hijo derecho
// Complejidad: O(1)
int Heap::right(int i){
    return 2 * i + 2;
}

// Inserta un elemento en el heap
void Heap::push(Restaurant restaurant){
    if(!isFull()){
        int i = currentSize;
        int p = parent(i);

        // Verifica si es un max heap por ganancia
        if(type == "revenue"){
            while(i > 0 && restaurant.revenue > restaurants[p].revenue){
                restaurants[i] = restaurants[p];
                i = p;
                p = parent(i);
            }
        }

        // Verifica si es un max heap por numero de ordenes
        else if(type == "numOrdenes"){
            while(i > 0 && restaurant.numOrders > restaurants[p].numOrders){
                restaurants[i] = restaurants[p];
                i = p;
                p = parent(i);
            }
        }

        // Inserta el elemento en el heap y aumenta el numero de elementos
        restaurants[i] = restaurant;
        currentSize++;
    }

    else{
        cout << "Heap lleno" << endl;
    }
}

// Regresa el elemento superior del heap
// Complejidad: O(log(n)) por heapify
Restaurant Heap::pop(){
    if(!isEmpty()){
        Restaurant top = restaurants[0];
        restaurants[0] = restaurants[currentSize - 1];
        currentSize--;
        heapify(0);
        return top;
    }

    else{
        cout << "Heap vacio" << endl;
        return Restaurant();
    }
}

// Reordena el heap
// Complejidad: O(log(n))
void Heap::heapify(int i){
    int l = left(i);
    int r = right(i);
    int largest = i;
    
    // Verifica si es un max heap por ganancia
    if(type == "revenue"){
        if(l < currentSize && restaurants[l].revenue > restaurants[largest].revenue){
            largest = l;
        }

        if(r < currentSize && restaurants[r].revenue > restaurants[largest].revenue){
            largest = r;
        }
    }

    // Verifica si es un max heap por numero de ordenes
    else if(type == "numOrdenes"){
        if(l < currentSize && restaurants[l].numOrders > restaurants[largest].numOrders){
            largest = l;
        }

        if(r < currentSize && restaurants[r].numOrders > restaurants[largest].numOrders){
            largest = r;
        }
    }

    // Si el elemento actual no es el mayor
    if(largest != i){
        // Intercambia el elemento actual con su hijo mayor
        swap(i, largest);
        heapify(largest);
    }
}

// Intercambia dos elementos del heap
// Complejidad: O(1)
void Heap::swap(int i, int j){
    Restaurant aux = restaurants[i];
    restaurants[i] = restaurants[j];
    restaurants[j] = aux;
}

// Muestra el heap
void Heap::show(){
    for(int i = 0; i < currentSize; i++){
        restaurants[i].show();
    }
}

int main(){

    string orders[7] = {
        "Jun 24 19:39:45 R:La Terraza del Mar O:Falafel con Hummus(284)",
        "Feb 13 19:25:24 R:El Barzon O:ensalada Griega(140)", 
        "Feb 7 17:8:30 R:El Cafe de la Plaza O:Curry de Pollo(273)",
        "Dic 24 14:50:39 R:The Rustic Spoon O:Tiradito de Pescado(279)",
        "Ago 4 13:25:11 R:El Pueblo O:Fideua(276)",
        "ene 4 17:51:54 R:El Rinconcito Tropical O:Fettuccine Alfredo(299)",
        "Nov 2 13:5:23 R:Aere and Now O:Carne de Res en Salsa(292) " };

    Heap *heap = new Heap(7, "revenue");

    for(int i = 0; i < 7; i++){
        string order = orders[i];
        string restaurant = get_restaurant(order);
        float revenue = get_revenue(order);

        Restaurant newRestaurant(restaurant, i + 1, revenue);
        heap->push(newRestaurant);
    }

    cout << "Elementos en el heap" << endl;

    for(int i = 0; i < 7; i++){
        heap->pop().show();
    }
}