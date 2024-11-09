#include <string>
// #include <vector>
#include <iostream>
#include <fstream>

using namespace std;

// Clase para restaurantes
class Restaurant{
    public:
        string name; // Nombre del restaurante
        int numOrders; // Numero de ordenes
        float revenue; // Ganancias

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

// Funcion para asignar un valor a cada orden de acuerdo a su fecha y hora
// Complejidad: O(1)
int get_value(string order){
    string months[12] = {"ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"};
    string aux;

    int month_end_index = order.find(" ");
    string month = order.substr(0, month_end_index);

    aux = order.substr(month_end_index + 1);

    int day_end_index = aux.find(" ");
    string day = aux.substr(0, day_end_index);

    aux = aux.substr(day_end_index + 1);
    
    int time_end_index = aux.find(" ");
    string time = aux.substr(0, time_end_index);

    int value = 0;

	// Pasa por el arreglo de meses
	for(int i = 0; i < 12; i++){
		if(month == months[i]){
			// Asigna un valor segun el mes
			value += (i + 1) * 100000000;
            break;
		}
	}

    value += stoi(day) * 1000000;

    int hour_end_index = aux.find(":");
    string hour = time.substr(0, hour_end_index);

    aux = time.substr(hour_end_index + 1);

    int minute_end_index = aux.find(":");
    string minute = aux.substr(0, minute_end_index);

    aux = aux.substr(minute_end_index + 1);

    int second_end_index = aux.find(" ");
    string second = aux.substr(0, second_end_index);

    value += stoi(hour) * 10000;
    value += stoi(minute) * 100;
    value += stoi(second);

    return value;
}

// Clase para max heap de restaurantes
class Heap{
    public:
        Restaurant *restaurants; // Arreglo de restaurantes
        string type; // "revenue" o "numOrdenes"
        int maxSize; // Numero maximo de elementos en el heap
        int currentSize; // Numero actual de elementos

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
// Complejidad: O(log(n))
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
        // Guarda el elemento superior
        Restaurant top = restaurants[0];

        // Mueve el ultimo elemento al inicio
        restaurants[0] = restaurants[currentSize - 1];

        // Reduce el numero de elementos y reordena el heap
        currentSize--;
        heapify(0);

        // Regresa el elemento superior
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
    int l = left(i); // Indice del hijo izquierdo
    int r = right(i); // Indice del hijo derecho
    int largest = i; // Indice del elemento actual
    
    // Verifica si es un max heap por ganancia
    if(type == "revenue"){
        // Compara el elemento actual con su hijo izquierdo
        if(l < currentSize && restaurants[l].revenue > restaurants[largest].revenue){
            largest = l;
        }

        // Compara el elemento actual con su hijo derecho
        if(r < currentSize && restaurants[r].revenue > restaurants[largest].revenue){
            largest = r;
        }
    }

    // Verifica si es un max heap por numero de ordenes
    else if(type == "numOrdenes"){
        // Compara el elemento actual con su hijo izquierdo
        if(l < currentSize && restaurants[l].numOrders > restaurants[largest].numOrders){
            largest = l;
        }

        // Compara el elemento actual con su hijo derecho
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

// Clase de nodo para lista enlazada doble
template <class T>
class Node{	
	public:
		T value; // Valor del nodo, tipo de dato generico
		Node<T> *prev; // Puntero al nodo anterior
		Node<T> *next; // Puntero al nodo siguiente

        // Constructor
		Node(T value){	
            this->value = value;
			this->prev = NULL;
			this->next = NULL;
		}
};

// Clase de lista enlazada doble
template <class T>
class List{
    Node<T> *first; // Puntero al primer elemento
	Node<T> *last; // Puntero al ultimo elemento
	int size; // Numero de elementos

	public:
        // Constructor
		List(){	
            this->first = NULL; 
			this->last = NULL; 
			this->size = 0;
		}
		
        // Funciones
		int getSize(){ return size; }
		void showList();
        Node<T>* getIndex(int index);
		
		void insertFirst(T);		
		void insertLast(T);	

		void deleteFirst();					

		Node<T>* getFirst();
		Node<T>* getLast();		
};

// Devuelve el primer nodo de la lista
// Complejidad: O(1)
template<class T>
Node<T>* List<T>::getFirst(){	
	return first;
}

// Devuelve el ultimo nodo de la lista
// Complejidad: O(1)
template<class T>
Node<T>* List<T>::getLast(){	
	return last;
}

// Elimina el primer nodo de la lista
// Complejidad: O(1)
template<class T>
void List<T>::deleteFirst(){
    // Nodo auxiliar para guardar el primer nodo
    Node<T> *aux = first;

    // Enlaza el ultimo nodo con el segundo nodo
	Node<T> *second = first->next;
	second->prev = last;
	last->next = second;

    // Elimina el primer nodo
	delete aux;
    
    // El segundo nodo se convierte en el primero
	first = second;

    // Disminuye el numero de elementos
	size--;
}

// Inserta al inicio
// Complejidad: O(1)
template<class T>
void List<T>::insertFirst(T newValue){	
    // Nodo nuevo
    Node<T> *node = new Node<T>(newValue);

    // Nodo auxiliar para guardar el primer nodo
	Node<T> *aux = first;

    // Enlaza el nuevo nodo con el primer nodo
	node->next = aux;

    // El nuevo nodo se convierte en el primer nodo
	first = node;

    // Si la lista estaba vacia, el nuevo nodo tambien es el ultimo
	if(size == 0){	
		last = node;   
	}

    // Si no, el nodo anterior al primer nodo es el nuevo nodo
	else{	
		aux->prev = node;
	}

	// Enlaza el ultimo nodo con el nodo nuevo
	first->prev = last;
	last->next = first;

    // Aumenta el numero de elementos
	size++;	
}

// Inserta al final
// Complejidad: O(1)
template<class T>
void List<T>::insertLast(T newValue){
    // Nodo nuevo	
    Node<T> *node = new Node<T>(newValue);

    // Nodo auxiliar para guardar el ultimo nodo
	Node<T> *secondLast = last;

    // Enlaza el nuevo nodo con el ultimo nodo
	node->prev = secondLast;

    // El nuevo nodo se convierte en el ultimo nodo
	last = node;

    // Si la lista estaba vacia, el nuevo nodo tambien es el primer nodo
	if(size == 0){
        first = node; 
    }	

    // Si no, el nodo siguiente al ultimo nodo es el nuevo nodo
	else{
        secondLast->next = node; 
    }

	// Enlaza el primer nodo con el nodo nuevo
	first->prev = last;
	last->next = first;

    // Aumenta el numero de elementos
	size++;
}

// Muestra la lista
// Complejidad: O(n)
template<class T>
void List<T>::showList(){	
    Node<T> *aux = first;
	int i = 0;

	cout << "Size: " << size << endl;

	while(i < size){	
        cout << aux->value << endl ;
		aux = aux->next;
		i++;
	}

	cout << endl << endl;
}

// Devuelve el nodo en la posicion index
// Complejidad: O(n)
template<class T>
Node<T>* List<T>::getIndex(int index){
    Node<T> *aux = first;
    int i = 0;

    while(i < index){
        aux = aux->next;
        i++;
    }

    return aux;
}

// Clase para stack
template <class T>
class Stack{	
    public:
		List<T> lista; // Lista de elementos genericos
		int size = 0; // Numero de elementos

        // Constructor sin parametros
		Stack(){
        }

        // Funciones
		void show();		
		bool isEmpty();
		void push(T);
		T pop();
};

// Mostrar es solo llamar a la funcion show de la lista
// Complejidad: O(n)
template<class T>
void Stack<T>::show(){	
	this->lista.showList();
}

// Verifica si la lista esta vacia
// Complejidad: O(1)
template<class T>
bool Stack<T>::isEmpty(){	
    return lista.getSize() == 0; 
}


// Agrega un elemento en el top de la stack (inicio de la lista)
// Complejidad: O(1) 
template<class T>
void Stack<T>::push(T  item){	
    this->lista.insertFirst(item);
	this->size = this->lista.getSize();
}

// Consulta y guarda el primer elemento de la lista
// Elimina el top de la lista y devuelve el valor guardado
// Complejidad: O(1)
template<class T>
T Stack<T>::pop(){	
    T topValue = lista.getFirst()->value;
	lista.deleteFirst();

	return topValue;
}

// Funcion para particionar la lista de ordenes (ordenar por restaurantes)
template<class T>
Node<T>* partitionR(List<T> datos, Node<T> *L, Node<T> *R){	
	Node<T> *j = L; 	
	Node<T> *i = NULL; 
	Node<T> *pivot = R; 
	
	T aux = "";
	
	//	Compara con pivot e intercambia
	while(j != R){
		// cout << "\tComaparo " <<  j->value << " y " << pivot->value << endl;
		if(get_restaurant(j->value) < get_restaurant(pivot->value)){	
            if(i == NULL){	
                i = L; 
            }

			else{	
                i = i->next; 
            }

			aux = j->value;
			j->value = i->value;
			i->value = aux; 
		}

		j = j->next;
	}

	//	Coloca el valor pivote en su sitio
	if(i == NULL){	
        i = L; 
    }
	
    else{	
        i = i->next; 
    }
	
	aux = i->value;
	i->value = pivot->value;
	pivot->value = aux; 

	return i;	// Devuelve la direccion de donde quedo el valor pivote
}

// quicksort
// Ordena por restaurantes
// Complejidad: O(nlog(n))
template<class T>
void quickSortR(List<T> datos){	
	Stack<Node<string>*> stack;

	Node<T> *L = datos.getFirst();
	Node<T> *R = datos.getLast();
	Node<T> *pivot = NULL;

	//	El primer par de L y R entran en la stack
	//	Esta particion inicial son el inicio y fin de la lista de datos
	stack.push(L);
    stack.push(R);

	//	En cada iteracion un par L y R salen de la stak
	// 	La particion de L a R es reordenada 
	//	Y segun donde quede el pivote, agrega nuevos pares de L y R a la stack
	while(stack.isEmpty() == false){	
		R = stack.pop();
		L = stack.pop();

		pivot = partitionR(datos, L, R);

		if(pivot != L && pivot->next != L){	
			stack.push(L);
			stack.push(pivot->prev);
		}

		if(pivot != R && pivot->prev != R){	
			stack.push(pivot->next);
			stack.push(R);
		}

		// datos.showList();   // <---- Descomenta para ver el paso a paso
	}
}

//    Funcion para particionar la lista de ordenes (ordenar por fechas)
template<class T>
Node<T>* partition(List<T> datos, Node<T> *L, Node<T> *R){	
	Node<T> *j = L; 	
	Node<T> *i = NULL; 
	Node<T> *pivot = R; 
	
	T aux = "";
	
	//	Compara con pivot e intercambia
	while(j != R){	
		// cout << "\tComaparo " <<  j->value << " y " << pivot->value << endl;
		if(get_value(j->value) < get_value(pivot->value)){	
            if(i == NULL){	
                i = L; 
            }
			
            else{	
                i = i->next; 
            }

			aux = j->value;
			j->value = i->value;
			i->value = aux; 
		}

		j = j->next;
	}

	//	Coloca el valor pivote en su sitio
	if(i == NULL){	
        i = L; 
    }
	
    else{
        i = i->next;
    }
	
	aux = i->value;
	i->value = pivot->value;
	pivot->value = aux; 

	return i;	//	Devuelve la direccion de donde quedo el valor pivote
}

//	quicksort
//	Ordena por fechas
// Complejidad: O(nlog(n))
template<class T>
void quickSort(List<T> datos){	
	Stack<Node<string>*> stack;

	Node<T> *L = datos.getFirst();
	Node<T> *R = datos.getLast();
	Node<T> *pivot = NULL;
	
	//	El primer par de L y R entran en la stack
	//	Esta particion inicial son el inicio y fin de la lista de datos
	stack.push(L);
    stack.push(R);

	//	En cada iteracion un par L y R salen de la stak
	// 	La particion de L a R es reordenada 
	//	Y segun donde quede el pivote, agrega nuevos pares de L y R a la stack
	while(stack.isEmpty() == false){	
		R = stack.pop();
		L = stack.pop();

		pivot = partition(datos, L, R);

		if(pivot != L && pivot->next != L){	
			stack.push(L);
			stack.push(pivot->prev);
		}

		if(pivot != R && pivot->prev != R){	
			stack.push(pivot->next);
			stack.push(R);
		}

		// datos.showList();   // <---- Descomenta para ver el paso a paso
	}
}


int main(int argc, char* argv[]){
    // Abre el archivo de ordenes
    ifstream file("orders.txt");

    // Crea (o escribe sobre) los archivos de salida
    ofstream sorted_numOrders("sorted_numOrders.txt");
    ofstream sorted_revenue("sorted_revenue.txt");

    int option;
    int busqueda;
    int i = 0;

    string start_date;
    string end_date;
    string restaurant;
    int start_date_value;
    int end_date_value;

    // Variable auxiliar para leer cada linea del archivo
    string line;

    // Vector para almacenar las ordenes
    // vector<string> orders(10000);

    // Lista para almacenar los datos de las ordenes
    List<string> datos;
    
    // Pasa por cada linea del archivo
    while(getline(file, line)){
        // Copia la linea al vector de ordenes
        // orders[i] = line;
        datos.insertLast(line);
        i++;
    }

    // Ordena las ordenes por restaurante
    quickSortR(datos);

    // Heaps para ordenar los restaurantes por numero de ordenes y ganancias
    Heap heap_numOrders(10000, "numOrdenes");
    Heap heap_revenue(10000, "revenue");

    // Variables para crear los objetos
    string restaurant_name = "";
    int numOrders = 0;
    float revenue = 0;
    Node<string> *aux = datos.getFirst();

    // Pasa por cada orden y agrega el restaurante a los heaps
    for(int j = 0; j < i; j++){
        // Aumenta el numero de ordenes del restaurante
        numOrders++;

        // Aumenta las ganancias del restaurante
        revenue += get_revenue(aux->value);

        // Verifica si el restaurante del nodo actual no es igual al del nodo siguiente
        if(get_restaurant(aux->value) != get_restaurant(aux->next->value)){
            // Nombre del restaurante
            restaurant_name = get_restaurant(aux->value);

            // Crea un objeto de tipo Restaurant
            Restaurant restaurant(restaurant_name, numOrders, revenue);

            // Inserta el restaurante en los heaps
            heap_numOrders.push(restaurant);
            heap_revenue.push(restaurant);

            // Reinicia las variables
            numOrders = 0;
            revenue = 0;
        }

        aux = aux->next;
    }

    int num = 0;

    // Guarda el contenido de los heaps en los archivos de salida
    sorted_numOrders << "Lista de restaurantes por numero de ordenes" << endl;
    cout << "Restaurantes con mayor numero de ordenes" << endl;
    while(!heap_numOrders.isEmpty()){
        Restaurant restaurant = heap_numOrders.pop();
        num++;
        sorted_numOrders << num << "- " << restaurant.name << ": " << restaurant.numOrders << " ordenes, $" << restaurant.revenue << endl;

        // Imprime los primeros 10 restaurantes
        if(num <= 10){
            cout << num << "- " << restaurant.name << ": " << restaurant.numOrders << " ordenes, $" << restaurant.revenue << endl;
        }
    }

    num = 0;
    cout << endl;

    sorted_revenue << "Lista de restaurantes por ganancias" << endl;
    cout << "Restaurantes con mayores ganancias" << endl;
    while(!heap_revenue.isEmpty()){
        Restaurant restaurant = heap_revenue.pop();
        num++;
        sorted_revenue << num << "- " << restaurant.name << ": " << restaurant.numOrders << " ordenes, $" << restaurant.revenue << endl;

        // Imprime los primeros 10 restaurantes
        if(num <= 10){
            cout << num << "- " << restaurant.name << ": " << restaurant.numOrders << " ordenes, $" << restaurant.revenue << endl;
        }
    }

    // Cierra los archivos utilizados en el programa
    file.close();
    sorted_numOrders.close();
    sorted_revenue.close();

    // Libera la memoria utilizada por los heaps
    delete[] heap_numOrders.restaurants;
    delete[] heap_revenue.restaurants;

    return 0;
}
