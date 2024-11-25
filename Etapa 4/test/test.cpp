#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;

// Clase para heap
template <class T>
class Heap{
    public:
        T *data;
        int maxSize;
        int currentSize;

        // Constructor
        Heap(int n){
            maxSize = n;
            currentSize = 0;
            data = new T(maxSize);
        }

        // Destructor
        ~Heap(){
            delete[] data;
            maxSize = 0;
            currentSize = 0;
        }

        // Funciones
        bool isEmpty();
        bool isFull();

        T getTop();
        int parent(int);
        int left(int);
        int right(int);

        void push(T);
        T pop();
        void heapify(int);
        void swap(int, int);
        void show();
};

// Verifica si el heap esta vacio
// Complejidad O(1)
template <class T>
bool Heap<T>::isEmpty(){
    return currentSize == 0;
}

// Verifica si el heap esta lleno
// Complejidad O(1)
template <class T>
bool Heap<T>::isFull(){
    return currentSize == maxSize;
}

// Obtiene el valor superior del heap
// Complejidad O(1)
template <class T>
T Heap<T>::getTop(){
    return data[0];
}

// Obtiene el indice del padre
// Complejidad O(1)
template <class T>
int Heap<T>::parent(int i){
    return (i - 1) / 2;
}

// Obtiene el indice del hijo izquierdo
// Complejidad O(1)
template <class T>
int Heap<T>::left(int i){
    return 2 * i + 1;
}

// Obtiene el indice del hijo derecho
// Complejidad O(1)
template <class T>
int Heap<T>::right(int i){
    return 2 * i + 2;
}

// Inserta un valor
// Complejidad O(nlog(n))
template <class T>
void Heap<T>::push(T value){
    if(!isFull()){
        int i = currentSize;
        int p = parent(i);

        while(i > 0 && value < data[p]){
            data[i] = data[p];
            i = p;
            p = parent(p);
        }

        data[i] = value;
        currentSize++;
    }

    else{
        cout << "Heap lleno" << endl;
    }
}

// Regresa el valor superior y lo elimina
// O(log(n))
template <class T>
T Heap<T>::pop(){
    if(!isEmpty()){
        T value = data[0];
        data[0] = data[currentSize - 1];
        currentSize--;
        heapify(0);
        return value;
    }

    else{
        cout << "Heap vacio" << endl;
        return -1;
    }
}

// Reordena el heap
// Complejidad O(log(n))
template <class T>
void Heap<T>::heapify(int index){
    int l = left(index);
    int r = right(index);
    int i = index;

    if(l < currentSize && data[l] < data[i]){
        i = l;
    }

    if(r < currentSize && data[r] < data[i]){
        i = r;
    }

    if(i != index){
        swap(index, i);
        heapify(i);
    }
}

// Intercambia dos valores
// Complejidad O(1)
template <class T>
void Heap<T>::swap(int i, int j){
    T aux = data[i];
    data[i] = data[j];
    data[j] = aux;
}

// Muestra el heap
// Complejidad O(n)
template <class T>
void Heap<T>::show( ){	
    int i;
	int level = 0;
	cout << "Size: " << currentSize << endl ;

	i = pow(2, level);

	while(i-1 < currentSize){	
        cout << "\t" << data[i-1] << "(" << level << ")" ;	
		i++;

		if ((i) == pow(2, level+1)){	
            cout << endl;
			level++;
		}
	}
	cout << endl ;
}

// Clase para stack
class Stack{
	private:
		int *data;
		int top;
		int maxSize;

	public:
		Stack(int maxSize){	
			this->maxSize = maxSize;
			this->data = (int *) malloc( this->maxSize * sizeof(int));
			this->top = -1;
		}

		~Stack(){	
			//free(this->data);	
			delete[] this->data;
		}

		void push(int Valor);
		int getTop();
		int pop();
		bool isEmpty();  
		bool isFull();
};

//	solo consulta el dato en top
int Stack::getTop(){	
	int value = this->data[top];
	return value;
}

//	extrae el dato en top
int Stack::pop(){	
	int value = this->data[top];
	this->top--;
	return value;
}

// 	agrega elemento
void Stack::push(int value){	
	this->top++;
	this->data[this->top] = value;
}

//	revisa si la pila esta llena
bool Stack::isFull(){	
	return this->top == (this->maxSize - 1);	
}

//	 revisa si la pila esta vacia
bool Stack::isEmpty(){	
	return this->top == -1;	
}

// Clase para queue
class Queue{
	private:
		int *data;
		int front;
		int end;
		int maxSize;

	public:
		Queue(int maxSize){   
			this->maxSize = maxSize;
			this->data = (int *) malloc( this->maxSize * sizeof(int));
			this->front = -1;
			this->end = -1;
		}

		~Queue(){	
			free(this->data);	
			//	delete[] this->data;
		}

	void enqueue(int Valor);
	int dequeue();
	int getFront();
	bool isEmpty();  
	bool isFull();

};

//	muestra el valor al frente
int Queue::getFront(){	
	return this->data[this->front];  
}

//	extrae elemento del frente
int Queue::dequeue(){	
	int value = this->data[this->front];
	
	if (this->front == this->end){	
		this->front = -1;
		this->end = -1 ;	
	}
	
	else{	
		this->front = (this->front + 1) % this->maxSize;	
	}

	return value;
}

//	agrega elemento
void Queue::enqueue(int value){	
	this->end = (this->end + 1) % this->maxSize;
	this->data[end] = value;

	if (this->front == -1 ){	
		this->front++;
	}
}

//	si esta llena
bool Queue::isFull(){	
	return (end+1) % this->maxSize == front;	
}

//	si esta vacia
bool Queue::isEmpty(){	
	return front == -1;	 
}

//	Usa una stack para procesar los nodos
void recDFS(int N, int **matrix, Queue *topo, int *visitados_topo){	
	Stack *stack = new Stack(N);

	int i;
	int origen = 0;

	int *visitados = (int *) calloc(N, sizeof(int));
	int *predecesores = (int *) calloc(N, sizeof(int));

	// for(i = 0; i < N, i++){
	// 	cout << visitados[i] << " ";
	// }

	// cout << endl;

	stack->push(origen); // El nodo origen entra a la stack
	visitados[origen] = 1; // se marca como visitado
	predecesores[origen] = -1; // no tiene predecesor

	int u;

	while(!stack->isEmpty()){
		u = stack->pop(); // sale el nodo de la stack
		topo->enqueue(u); // se guarda en la stack
		// cout << "Sale nodo: " << u << endl;

		for(i = 0; i < N; i++){
			// Se buscan los vecinos
			if(matrix[u][i] == 1){
				// cout << "Vecinos-> u: " << u << " i: " << i << endl;

				if(visitados[i] == 0){
					stack->push(i);
					visitados[i] = 1;
					visitados_topo[i] = 1;
					predecesores[i] = u;
				}
			}
		}
	}

	cout << endl;

	// for(i = 0; i < N; i++){
	// 	cout << predecesores[i] << "\t";
	// }

	// cout << endl;

	// for(i = 0; i < N; i++){
	// 	cout << i << "\t";
	// }

	// cout << endl;
}

// Topological sort
// Entrada: N = numero de nodos, matrix = matriz de adyacencia
// Salida: orden topologico
void topoSort(int N, int** matrix){
	Queue *queue = new Queue(N);

	int *visitados = (int *) calloc(N, sizeof(int));

	for(int i = 0; i < N; i++){
		if(visitados[i] == 0){
			recDFS(N, matrix, queue, visitados);
		}
	}

	cout << "Orden topologico:" << endl;

	while(!queue->isEmpty()){
		cout << queue->dequeue() << " ";
	}

	cout << endl;
}

// Djikstra
// Entrada: N = numero de nodos, matrix = matriz de adyacencia
// Salida: Lista de caminos mas cortos desde un nodo origen
int Djikstra(int N, int** matrix, int origen){
	Queue *queue = new Queue(N);

	int distance;

	int *visitados = (int *) calloc(N, sizeof(int));
	int *distancias = (int *) calloc(N, sizeof(int));

	for(int i = 0; i < N; i++){
		distancias[i] = 9999;
	}

	distancias[origen] = 0;

	queue->enqueue(origen);

	int u;

	while(!queue->isEmpty()){
		u = queue->dequeue();

		for(int i = 0; i < N; i++){
			if(matrix[u][i] != 0){
				if(distancias[i] > distancias[u] + matrix[u][i]){
					distancias[i] = distancias[u] + matrix[u][i];
					queue->enqueue(i);
				}
			}
		}
	}

	cout << "Distancias mas cortas desde el nodo " << origen << endl;

	for(int i = 0; i < N; i++){
		cout << "Distancia a " << i << ": " << distancias[i] << endl;
	}

	return 0;
}

// Prim
// Entrada: N = numero de nodos, matrix = matriz de adyacencia
// Salida: Aristas para el arbol de expansion minima y costo total
int Prim(int N, int** matrix){
	Queue *queue = new Queue(N);

	int distance;
	int costo = 0;

	int *visitados = (int *) calloc(N, sizeof(int));
	int *distancias = (int *) calloc(N, sizeof(int));
	int *desde = (int *) calloc(N, sizeof(int));

	for(int i = 0; i < N; i++){
		distancias[i] = 9999;
	}

	distancias[0] = 0;
	desde[0] = -1;

	queue->enqueue(0);

	int u;

	while(!queue->isEmpty()){
		u = queue->dequeue();
		visitados[u] = 1; 

		// Por cada vecino de u
		for(int i = 0; i < N; i++){
			distance = matrix[u][i];

			if(distance != 0 && distance < distancias[i] && visitados[i] == 0){
				distancias[i] = distance;
				desde[i] = u;
				queue->enqueue(i);
			}
		}
	}

	cout << "Aristas para el arbol de expansion minima" << endl;

	for(int i = 0; i < N; i++){
		cout << "Distancia a " << i << ": " << distancias[i] << " desde " << desde[i] << endl;
	}

	for(int i = 0; i < N; i++){
		costo += distancias[i];
	}

	cout << "Costo total: " << costo << endl;

	return 0;
}

// Kruskal
// Entrada: N = numero de nodos, matrix = matriz de adyacencia
// Salida: Aristas para el arbol de expansion minima y costo total
void kruskal(int N, int **matrix){
	Heap<int> *heap = new Heap<int>(N);

	int costo = 0;

	int *visitados = (int *) calloc(N, sizeof(int));
	int *distancias = (int *) calloc(N, sizeof(int));
	int *desde = (int *) calloc(N, sizeof(int));

	for(int i = 0; i < N; i++){
		distancias[i] = 9999;
	}

	distancias[0] = 0;
	desde[0] = -1;

	heap->push(0);

	int u;

	while(!heap->isEmpty()){
		u = heap->pop();
		visitados[u] = 1;

		for(int i = 0; i < N; i++){
			if(matrix[u][i] != 0 && visitados[i] == 0){
				if(matrix[u][i] < distancias[i]){
					distancias[i] = matrix[u][i];
					desde[i] = u;
					heap->push(i);
				}
			}
		}
	}

	cout << "Aristas para el arbol de expansion minima" << endl;

	for(int i = 0; i < N; i++){
		cout << "Distancia a " << i << ": " << distancias[i] << " desde " << desde[i] << endl;
	}

	for(int i = 0; i < N; i++){
		costo += distancias[i];
	}

	cout << "Costo total: " << costo << endl;
}


int main(int argc, char* argv[]){    
	string sline, line, aux;
	int index;
	int a, b, current = -1;

	int **directed;
	int **weighted;

	int *start, *end; 

	ifstream inFile("grafo.txt");         //  input file stream
	
	//    Verifica que los archivos se hayan abierto correctamente
	int i = 0;
	int j;
	int N;
	int E;

	// Grafo dirigido
	if(inFile.is_open()){    
		//    Lee linea a linea
		while(getline(inFile, sline)){    
			if(i == 1){   
				//cout << sline << endl;
				line = sline;
				index = line.find(" "); 
				aux = line.substr(0, index);
				N = stoi(aux);//lee cuantos nodos son

				line = line.substr(index+1);
				index = line.find(" ");

				line = line.substr(index+1);
				index = line.find(" ");
				aux = line.substr(0, index);
				E = stoi(aux);

				// cout << "N: "<< N << endl;
				// cout << "E: "<< E << endl;

				directed = (int **) malloc ( N * sizeof(int*) );

				for (j = 0; j < N; j++){     
					directed[j] = (int *) malloc(N * sizeof(int));    
				}

				for (int x = 0; x < N; x++) {
					for (int y = 0; y < N; y++) {
						directed[x][y] = 0;
					}
				}
			}

			else if(i > 1){    
				//cout << sline << endl;

				line = sline;
				index = line.find(" "); 
				aux = line.substr(0, index);
				a = stoi(aux);

				line = line.substr(index+1);
				index = line.find(" "); 
				aux = line.substr(0, index);
				b = stoi(aux);

				// cout << "a y b: "<< a << " " << b << endl;

				//    asignar valores a la matriz
				//    indicando que a es adyacente a b
				directed[a][b] = 1;
			}
			
			i++;
		}
	}

	inFile.close();

	// Grafo ponderado

	ifstream inFile2("grafo_ponderado.txt");

	i = 0;

	if(inFile2.is_open()){    
		// Formato de linea: 1 2 3 (nodo1, nodo2, peso)

		while(getline(inFile2, sline)){    
			if(i == 1){   
				//cout << sline << endl;
				line = sline;
				index = line.find(" "); 
				aux = line.substr(0, index);
				N = stoi(aux);//lee cuantos nodos son

				line = line.substr(index+1);
				index = line.find(" ");

				line = line.substr(index+1);
				index = line.find(" ");
				aux = line.substr(0, index);
				E = stoi(aux);

				cout << "N: "<< N << endl;
				cout << "E: "<< E << endl;

				weighted = (int **) malloc ( N * sizeof(int*) );

				for (j = 0; j < N; j++){     
					weighted[j] = (int *) malloc(N * sizeof(int));    
				}

				for (int x = 0; x < N; x++) {
					for (int y = 0; y < N; y++) {
						weighted[x][y] = 0;
					}
				}
			}

			else if(i > 1){    
				//cout << sline << endl;

				line = sline;
				index = line.find(" "); 
				aux = line.substr(0, index);
				a = stoi(aux);

				line = line.substr(index+1);
				index = line.find(" "); 
				aux = line.substr(0, index);
				b = stoi(aux);

				line = line.substr(index+1);
				index = line.find(" "); 
				aux = line.substr(0, index);
				int w = stoi(aux);

				// cout << "a y b: "<< a << " " << b << " " << w << endl;

				//    asignar valores a la matriz
				//    indicando que a es adyacente a b
				weighted[a][b] = w;
				weighted[b][a] = w;
			}
			
			i++;
		}
	}

	inFile2.close();

	cout << "Matriz del grafo dirigido:" << endl;

	for(i = 0; i < N; i++){	
		for(j = 0; j < N; j++){	
			cout << "["<< i <<","<< j <<"] " << directed[i][j] << "\t\t"; 
		}
		
		cout << endl;
	}
	
	cout << endl;

	cout << "Matriz del grafo ponderado:" << endl;

	for(i = 0; i < N; i++){	
		for(j = 0; j < N; j++){	
			cout << "["<< i <<","<< j <<"] " << weighted[i][j] << "\t\t"; 
		}
		
		cout << endl;
	}
	
	cout << endl;

	topoSort(N, directed);
	cout << endl;

	cout << "Djikstra" << endl;
	Djikstra(N, weighted, 0);
	cout << endl;

	cout << "Prim" << endl;
	Prim(N, weighted);
	cout << endl;

	cout << "Kruskal" << endl;
	kruskal(N, weighted);
}