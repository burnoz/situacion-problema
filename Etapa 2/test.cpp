//g++ listaEnlazadaEj.cpp -o listaEnlazadaDoble; ./listaEnlazadaDoble

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;


// class node: un valor y un puntero a otro nodo
template <class T>
class Node
{	public:

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

	if (size == 0)
	{	last = node;   }	//	Si la lista esta vacia, el nodo nuevo es tambien el ultimo
	else
	{	aux->prev = node; 	// first; Si no, el anterior al viejo first (aux) es el nuevo
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
	{	cout << aux->value << "\t" ;
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
Node<T>* partition( List<T> datos, Node<T> *L, Node<T> *R )
{	Node<T> *j = L; 	
	Node<T> *i = NULL; 
	Node<T> *pivot = R; 
	
	T aux = 0; 			 
	
	//	Compara con pivot e intercambios
	while ( j != R)
	{	//cout << "\tComaparo " <<  j->value << " y " << pivot->value << endl;  		
		
		if ( j->value < pivot->value )
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
void quickSort( List<T> datos )
{	Stack< Node<int>* > stack;

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
	while ( stack.isEmpty() == false )
	{	R = stack.pop();
		L = stack.pop();

		pivot = partition(datos, L, R);

		if (pivot != L && pivot->next != L)
		{	stack.push( L );
			stack.push( pivot->prev );
		}

		if (pivot != R && pivot->prev != R)
		{	stack.push( pivot->next );
			stack.push( R );
		}

		datos.showList();   // <---- Descomenta para ver el paso a paso
	}

	
}



int main(int argc, char* argv[]) 
{	List<int> datos;

	datos.insertLast(6); 	//dList.showList(); 	
	datos.insertLast(5); 	//dList.showList(); 	
	datos.insertLast(3); 	//dList.showList(); 	
	datos.insertLast(1); 	//dList.showList(); 	
	datos.insertLast(8); 	//dList.showList(); 	
	datos.insertLast(7); 	//dList.showList(); 	
	datos.insertLast(2); 	//dList.showList(); 	
	datos.insertLast(4); 	datos.showList(); 	

	cout << "Antes de ordenar " << endl;
	datos.showList();

	quickSort(datos);

	cout << "Tras ordenar " << endl;
	datos.showList();
}