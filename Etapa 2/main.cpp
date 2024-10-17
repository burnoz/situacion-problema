#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

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

// Class node: un valor y un puntero a otro nodo
template <class T>
class Node{	
	public:
		//	Valor almacenado
		T value; 			// Tipo de dato generico

		Node<T> *prev; 		//	Puntero al nodo anterior
		Node<T> *next;		//	Puntero al nodo siguiente
		
		Node(T value){	
            this->value = value;
			this->prev = NULL;
			this->next = NULL;
		}
};

//  Clase lista enlazada simple: puntero al primer y ultimo nodo
template <class T>
class List{	
    Node<T> *first;	// Puntero al primer nodo
	Node<T> *last; 	// Puntero al ultimo nodo	
	int size;       // Numero de elementos

	public:
		List(){	
            this->first = NULL; 
			this->last = NULL; 
			this->size = 0;
		}
		
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
Node<T>* List<T>::getFirst( ){	
	return first;
}

// Devuelve el ultimo nodo de la lista
// Complejidad: O(1)
template<class T>
Node<T>* List<T>::getLast( ){	
	return last;
}

// Elimina el primer nodo de la lista
// Complejidad: O(1)
template<class T>
void List<T>::deleteFirst(){	
    Node<T> *aux = first;

	Node<T> *second = first->next;	//	El nodo siguinte del que se va
	second->prev = last; 			//	El nuevo primero enlazara al ultimo

	last->next = second;
	delete aux;

	first = second;
	size--;
}

// Inserta al inicio
// Complejidad: O(1)
template<class T>
void List<T>::insertFirst(T newValue){	
    Node<T> *node = new Node<T>(newValue);  // Creamos un nodo nuevo

	Node<T> *aux = first;	//	El nodo que solia ser el primero se convertira en 2do

	node->next = aux; 		//	El siguiente del nodo nuevo sera
	first = node;			//	El primero ahora sera el nuevo nodo

	if (size == 0){	
		last = node;		//	Si la lista esta vacia, el nodo nuevo es tambien el ultimo   
	}

	else{	
		aux->prev = node; 	// first; Si no, el anterior al viejo first (aux) es el nuevo
	}

	//	Mantener la lista circular
	first->prev = last;
	last->next = first;
	size++;	
}

// Inserta al final
// Complejidad: O(1)
template<class T>
void List<T>::insertLast(T newValue){	
    Node<T> *node = new Node<T>(newValue); //	nodo nuevo

	Node<T> *secondLast = last;			//	El nodo que solia ser last

	node->prev = secondLast;			//	El siguiente del nuevo aora es second last
	last = node;						//	El nuevo es ahora el ultimo

	if (size == 0){						//	Si la lista estaba vacia el nuevo es tambien el primero
        first = node; 
    }	

	else{								//	Si no, el siguiente del penultimo es el nodo nuevo
        secondLast->next = node; 
    }

	//	Mantener la lista circular
	first->prev = last;
	last->next = first;
	size++;
}

//	Muestra la lista
//	Complejidad: O(n)
template<class T>
void List<T>::showList( )
{	Node<T> *aux = first;
	int i = 0; 

	cout << "Size: " << size << endl;

	while(i < size){	
        cout << aux->value << endl ;
		aux = aux->next;
		i++;
	}
	cout << endl << endl;
}

//	Devuelve el nodo en la posicion index
//	Complejidad: O(n)
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

//	Una clase stack, con una lista enlazada doble dentro
template <class T>
class Stack{	
    public:

		List<T> lista;	// Tiene una lista dentro, que guarda cosas de tipo T
		int size = 0;
		
		Stack(){			// Un constructor que no hace nada
        }

		void show();		
		bool isEmpty();
		void push(T);
		T pop();
};

// Mostrar es solo llamar a la funcion show de la lista
template<class T>
void Stack<T>::show(){	
	this->lista.showList();
}

// Evalua si la lista tiene 0 elementos
// Complejidad: O(1)
template<class T>
bool Stack<T>::isEmpty(){	
    return lista.getSize() == 0; 
}


// Agrega un elemento en el top de la stack (inicio de la lista) 
template<class T>
void Stack<T>::push( T  item){	
    this->lista.insertFirst(item);
	this->size = this->lista.getSize();
}

//	Consulta y guarda el primer elemento de la lista
//	Elimina el top de la lista y devuelve el valor guardado
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
	
	//	Compara con pivot e intercambios
	while (j != R){	
		// cout << "\tComaparo " <<  j->value << " y " << pivot->value << endl;  		
		
		if (get_restaurant(j->value) < get_restaurant(pivot->value))
		{	if (i == NULL)
			{	i = L; }
			else
			{	i = i->next; }

			aux = j->value;
			j->value = i->value;
			i->value = aux; 
		}

		j = j->next;
	}

	//	Coloca el valor pivote en su sitio
	if (i == NULL)
	{	i = L; }
	else
	{	i = i->next; }
	
	aux = i->value;
	i->value = pivot->value;
	pivot->value = aux; 

	return i;	//	Devuelve la direccion de donde quedo el valor pivote
}

//	quicksort
//	Ordena por restaurantes
// Complejidad: O(nlog(n))
template<class T>
void quickSortR(List<T> datos){	
	Stack<Node<string>*> stack;

	Node<T> *L =   datos.getFirst();
	Node<T> *R =   datos.getLast();
	Node<T> *pivot = NULL;

	//	El primer par de L y R entran en la stack
	//	Esta particion inicial son el inicio y fin de la lista de datos
	stack.push(L);
    stack.push(R);

	//	En cada iteracion un par L y R salen de la stak
	// 	La particion de L a R es reordenada 
	//	Y segun donde quede el pivote, agrega nuevos pares de L y R a la stack
	while (stack.isEmpty() == false){	
		R = stack.pop();
		L = stack.pop();

		pivot = partitionR(datos, L, R);

		if (pivot != L && pivot->next != L){	
			stack.push(L);
			stack.push(pivot->prev);
		}

		if (pivot != R && pivot->prev != R){	
			stack.push( pivot->next );
			stack.push( R );
		}

		// datos.showList();   // <---- Descomenta para ver el paso a paso
	}
}

//    Funcion para particionar la lista de ordenes (ordenar por fechas)
template<class T>
Node<T>* partition( List<T> datos, Node<T> *L, Node<T> *R ){	
	Node<T> *j = L; 	
	Node<T> *i = NULL; 
	Node<T> *pivot = R; 
	
	T aux = "";
	
	//	Compara con pivot e intercambios
	while (j != R){	
		// cout << "\tComaparo " <<  j->value << " y " << pivot->value << endl;  		
		
		if (get_value(j->value) < get_value(pivot->value))
		{	if (i == NULL)
			{	i = L; }
			else
			{	i = i->next; }

			aux = j->value;
			j->value = i->value;
			i->value = aux; 
		}

		j = j->next;
	}

	//	Coloca el valor pivote en su sitio
	if (i == NULL)
	{	i = L; }
	else
	{	i = i->next; }
	
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

	Node<T> *L =   datos.getFirst();
	Node<T> *R =   datos.getLast();
	Node<T> *pivot = NULL;
	
	//	El primer par de L y R entran en la stack
	//	Esta particion inicial son el inicio y fin de la lista de datos
	stack.push(L);
    stack.push(R);

	//	En cada iteracion un par L y R salen de la stak
	// 	La particion de L a R es reordenada 
	//	Y segun donde quede el pivote, agrega nuevos pares de L y R a la stack
	while (stack.isEmpty() == false){	
		R = stack.pop();
		L = stack.pop();

		pivot = partition(datos, L, R);

		if (pivot != L && pivot->next != L){	
			stack.push(L);
			stack.push(pivot->prev);
		}

		if (pivot != R && pivot->prev != R){	
			stack.push( pivot->next );
			stack.push( R );
		}

		// datos.showList();   // <---- Descomenta para ver el paso a paso
	}
}

// Funcion para buscar ordenes por fecha y hora
// Complejidad: O(n)
void single_search(string date, int date_value, List<string> orders, int n){
    // Archivo en el que se almacenan los resultados de busqueda
    ofstream search_results("outputs/search_results.txt");

    List<string> results;
    int i, j;

    // Pasa por todos los elementos de la lista de ordenes
    for(i = 0; i < n; i++){
        // Busca coincidencias exactas con la fecha dada
        if(get_value(orders.getIndex(i)->value) == date_value){
            // Guarda las coincidencias en la lista de resultados
            results.insertLast(orders.getIndex(i)->value);
        }
    }

    // Imprime los resultados de la busqueda y los escribe en el archivo de salida
    cout << "Resultados de la busqueda (" << results.getSize() << " coincidencias):" << endl;
    search_results << "Resultados de la busqueda \"" << date << "\" (" << results.getSize() << " coincidencias):" << endl;

    if(results.getSize() == 0){
        cout << "No hay resultados para esta fecha";
    }

    else{
        for(j = 0; j < results.getSize(); j++){
            cout << j + 1 << "- " << results.getIndex(j)->value << endl;
            search_results << j + 1 << "- " << results.getIndex(j)->value << endl;
        }
    }

    search_results.close();
}

// Funcion para buscar ordenes por rango de fechas y horas
// Complejidad: O(n)
void range_search(string lower_date, string upper_date, int lower_date_value, int upper_date_value, List<string> orders, int n){
    // Archivo en el que se almacenan los resultados de busqueda
    ofstream search_results("outputs/search_results.txt");

    List<string> results;
    int i, j;

    // Pasa por todos los elementos de la lista de ordenes
    for(i = 0; i < n; i++){
        // Busca coincidencias exactas con las fechas dadas
        if(get_value(orders.getIndex(i)->value) >= lower_date_value && get_value(orders.getIndex(i)->value) <= upper_date_value){
            // Guarda las coincidencias en la lista de resultados
            results.insertLast(orders.getIndex(i)->value);
        }
    }

    // Imprime los resultados de la busqueda y los escribe en el archivo de salida
    cout << "Resultados de la busqueda (" << results.getSize() << " coincidencias):" << endl;
    search_results << "Resultados de la busqueda entre \"" << lower_date << "\" y \"" << upper_date << "\" (" << results.getSize() << " coincidencias):" << endl;

    if(results.getSize() == 0){
        cout << "No hay resultados para este rango de fechas";
    }

    else{
        for(j = 0; j < results.getSize(); j++){
            cout << j + 1 << "- " << results.getIndex(j)->value << endl;
            search_results << j + 1 << "- " << results.getIndex(j)->value << endl;
        }
    }

    search_results.close();
}

// Funcion para buscar ordenes por restaurante
// Complejidad: O(n)
void search_restaurant(string restaurant, List<string> orders, int n){
    // Archivo en el que se almacenan los resultados de busqueda
    ofstream search_results("outputs/search_results.txt");

    List<string> results;
    int i, j;

    // Pasa por todos los elementos de la lista de ordenes
    for(i = 0; i < n; i++){
        // Busca coincidencias exactas con el nombre del restaurante
        if(get_restaurant(orders.getIndex(i)->value) == restaurant){
            // Guarda las coincidencias en la lista de resultados
            results.insertLast(orders.getIndex(i)->value);
        }
    }

    // Imprime los resultados de la busqueda y los escribe en el archivo de salida
    cout << "Resultados de la busqueda (" << results.getSize() << " coincidencias):" << endl;
    search_results << "Resultados de la busqueda \"" << restaurant << "\" (" << results.getSize() << " coincidencias):" << endl;

    if(results.getSize() == 0){
        cout << "No hay resultados para este restaurante";
    }

    else{
        quickSort(results);

        for(j = 0; j < results.getSize(); j++){
            cout << j + 1 << "- " << results.getIndex(j)->value << endl;
            search_results << j + 1 << "- " << results.getIndex(j)->value << endl;
        }
    }

    search_results.close();
}



int main(int argc, char* argv[]){
    // Lee la ruta del archivo desde la terminal
    ifstream file(argv[1]);

    // Crea (o escribe sobre) los archivos de salida
    ofstream sorted_orders("outputs/sorted_orders.txt");

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

    // Imprime las primeras 10 ordenes en la terminal
    cout << "Primeras 10 ordenes" << endl;
    for(int j = 0; j < 10; j++){
        cout << datos.getIndex(j)->value << endl;
    }

    // Copia la lista ordenada al archivo de salida correspondiente
    for(int k = 0; k < i; k++){
        sorted_orders << datos.getIndex(k)->value << endl;
    }

    cout << endl << endl;

    cout << "------------------------------------" << endl;
    cout << "Busqueda de ordenes" << endl;
    cout << "------------------------------------" << endl;
    cout << "Seleccione una opcion: " << endl;
    cout << "1- Busqueda por fecha" << endl << "2- Busqueda por restaurante" << endl;
    cout << "> ";

    cin >> busqueda;

    switch(busqueda){
        case 1:
            // Busqueda de ordenes por fecha
            cout << endl << endl;
            cout << "------------------------------------" << endl;
            cout << "Busqueda de ordenes por fecha y hora" << endl;
            cout << "------------------------------------" << endl;
            cout << "Seleccione una opcion: " << endl;
            cout << "1- Busqueda individual" << endl << "2- Busqueda por rango" << endl;
            cout << "> ";

            cin >> option;

            switch(option){
                case 1:
                    cout << endl << "Ingrese la fecha y hora a buscar (ej. \"Jun 12 06:51:16\"):" << endl;
                    
                    cout << "> ";
                    getline(cin >> ws, start_date);
                    start_date_value = get_value(start_date);

                    cout << endl;

                    single_search(start_date, start_date_value, datos, i);

                    break;
                
                case 2:
                    cout << endl << "Ingrese las fechas y horas (ej. \"Jun 12 06:51:16\"):" << endl;
                    
                    cout << "Limite inferior: ";
                    getline(cin >> ws, start_date);
                    start_date_value = get_value(start_date);

                    cout << "Limite superior: ";
                    getline(cin >> ws, end_date);
                    end_date_value = get_value(end_date);

                    cout << endl;

                    range_search(start_date, end_date, start_date_value, end_date_value, datos, i);

                    break;

            default:
                cout << "Opcion invalida" << endl;
                break;

            }

            break;

        case 2:
            cout << endl << endl;
            cout << "------------------------------------" << endl;
            cout << "Busqueda de ordenes por restaurante" << endl;
            cout << "------------------------------------" << endl;
            cout << "Ingrese el nombre del restaurante tomando en cuenta mayusculas (ej. \"The Bee\"): " << endl;
            cout << "> ";

            getline(cin >> ws, restaurant);

            cout << endl;
            
            search_restaurant(restaurant, datos, i);
            break;

        default:
            cout << "Opcion invalida" << endl;
            break;
    }

    // Cierra los archivos utilizados en el programa
    file.close();
    sorted_orders.close();

    return 0;
}
