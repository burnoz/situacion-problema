//g++ listaEnlazadaEj.cpp -o listaEnlazadaDoble; ./listaEnlazadaDoble

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

// Funcion para obtener el nombre del restaurante de una orden
string get_restaurant(string order){
    string restaurant;
    int restaurant_start_index = order.find("R:");
    int restaurant_end_index = order.find(" O:");

    restaurant = order.substr(restaurant_start_index + 2, restaurant_end_index - restaurant_start_index - 2);
    
    return restaurant;
}

// Funcion para asignar un valor a cada orden de acuerdo a su fecha y hora
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

	// Pasa por todos los elementos del arreglo
	for(int i = 0; i < 12; i++){
		if(month == months[i]){
			// Indice del elemento encontrado
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

// class node: un valor y un puntero a otro nodo
template <class T>
class Node{	
	public:
		//	valor almacenado
		T value; 			// <--- Nota que es de tipo T

		Node<T> *prev; 		//	dir del nodo anterior
		Node<T> *next;		//	dir del nodo siguiente
		
		Node(T value)
		{	this->value = value;
			this->prev = NULL;
			this->next = NULL;
		}
};

//  Clase lista enlazada simple: 
//	puntero al primer nodo y tamaño total
template <class T>
class List
{	Node<T> *first;	// puntero al primer nodo
	Node<T> *last; 	//	puntero al ultimo nodo	
	int size;	

	public:
		List() 
		{	this->first = NULL; 
			this->last = NULL; 
			this->size = 0;
		}
		
		int getSize(){ return size; }
		void showList();
		void showListReverse();
		
		void insertFirst(T);		
		void insertLast(T);
		bool insertAtIndex(int, T); 	

		void deleteFirst();
		void deleteLast();				
		void deleteAtIndex(int);		

		Node<T>* find(T, int*);			

		Node<T>* getFirst();
		Node<T>* getLast();
		void update(int, T);			
};





template<class T>
Node<T>* List<T>::getFirst( )
{	
	return first;
}


template<class T>
Node<T>* List<T>::getLast( )
{	
	return last;
}


// inserta al inicio
template<class T>
void List<T>::deleteFirst()
{	Node<T> *aux = first;

	Node<T> *second = first->next;	//	El nodo siguinte del que se va
	second->prev = last; 			//	El nuevo primero enlazara al ultimo

	last->next = second;
	delete aux;

	first = second;
	size--;

}

// inserta al inicio
template<class T>
void List<T>::insertFirst(T newValue)
{	Node<T> *node = new Node<T>(newValue);  // Creamos un nodo nuevo

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


// inserta al final
template<class T>
void List<T>::insertLast(T newValue)
{	Node<T> *node = new Node<T>(newValue); //	nodo nuevo

	Node<T> *secondLast = last;			//	El nodo que solia ser last

	node->prev = secondLast;			//	El siguiente del nuevo aora es second last
	last = node;						//	El nuevo es ahora el ultimo

	if (size == 0)						//	Si la lista estaba vacia el nuevo es tambien el primero
	{	first = node; }	
	else								//	Si no, el siguiente del penultimo es el nodo nuevo
	{	secondLast->next = node; }

	//	Mantener la lista circular
	first->prev = last;
	last->next = first;

	size++;
}

template<class T>
void List<T>::showList( )
{	Node<T> *aux = first;
	int i = 0; 

	cout << "Size: " << size << endl;

	while( i < size )
	{	cout << aux->value << endl ;
		aux = aux->next;
		i++;
	}
	cout << endl << endl;
}

template<class T>
void List<T>::showListReverse( )
{	Node<T> *aux = last;
	int i = 0;  // i = size-1

	cout << "Reverse. Size: " << size << endl;
	
	while (i < size) //i >= 0
	{	cout << aux->value << "\t" ;
		aux = aux->prev;
		i++; // i--
	}	
	cout << endl << endl;
}




//	Una clase stack, con una lista enlazada doble dentro 
template <class T>
class Stack
{	public:

		List< T > lista;	// Tiene una lista dentro, que guarda cosas de tipo T
		int size = 0;
		
		Stack( )			// Un constructor que no hace nada
		{	}

		void show();		
		bool isEmpty();
		void push( T );
		T pop();
};

//	Mostrar es solo llamar a la funcion show de la lista
template<class T>
void Stack<T>::show( )	
{	
	this->lista.showList();
}

//	isEmpty evalua si la lista tiene 0 elementos
template<class T>
bool Stack<T>::isEmpty( )
{	return lista.getSize() == 0;  }


// push: agrega un elemento en el top de la stack, 
// aka, el inicio de la lista
template<class T>
void Stack<T>::push( T  item)
{	this->lista.insertFirst(item);
	this->size = this->lista.getSize();
}

//	pop: consulta y guarda el primer elemento de la lista
//	elimina el top de la lista y devuelve el valor guardado
template<class T>
T Stack<T>::pop( )
{	T topValue = lista.getFirst()->value;
	lista.deleteFirst();

	return topValue;
}


//	compara elementos en la particion de L a R 
//	reorganizandolos de acuerdo a las comparaciones con pivot
//	pivot es el ultimo de la particion
//	en este ejemplo, aux es un int, porque T es int
template<class T>
Node<T>* partitionR( List<T> datos, Node<T> *L, Node<T> *R ){	
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
//	Reordena por particiones iterativamente
template<class T>
void quickSortR(List<T> datos){	
	Stack<Node<string>*> stack;

	Node<T> *L =   datos.getFirst();
	Node<T> *R =   datos.getLast();
	Node<T> *pivot = NULL;
	
	cout << "L" << L << " es dir: "<< L->value << endl; 
	cout << "R" << R << " es dir: "<< R->value << endl; 

	//	El primer par de L y R entran en la stack
	//	Esta particion inicial son el inicio y fin de la lista de datos
	stack.push(L);
    stack.push(R);
	stack.show();

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
//	Reordena por particiones iterativamente
template<class T>
void quickSort(List<T> datos){	
	Stack<Node<string>*> stack;

	Node<T> *L =   datos.getFirst();
	Node<T> *R =   datos.getLast();
	Node<T> *pivot = NULL;
	
	cout << "L" << L << " es dir: "<< L->value << endl; 
	cout << "R" << R << " es dir: "<< R->value << endl; 

	//	El primer par de L y R entran en la stack
	//	Esta particion inicial son el inicio y fin de la lista de datos
	stack.push(L);
    stack.push(R);
	stack.show();

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


int main(int argc, char* argv[]) 
{	List<string> datos;

	datos.insertLast("Jun 24 19:39:45 R:La Terraza del Mar O:Falafel con Hummus(284)");
    datos.insertLast("Feb 13 19:25:24 R:El Barzon O:ensalada Griega(140)");
    datos.insertLast("Feb 7 17:8:30 R:El Cafe de la Plaza O:Curry de Pollo(273)");

	cout << "Antes de ordenar " << endl;
	datos.showList();

    quickSort(datos);
	quickSortR(datos);

	cout << "Tras ordenar " << endl;
	datos.showList();
}