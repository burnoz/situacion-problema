#include <string>
// #include <vector>
#include <iostream>
#include <fstream>

using namespace std;

// class node: un valor y un puntero a otro nodo
template <class T>		//	Esta linea permite que podamos crear listas de cualquier tipo de dato
class Node{	
    public:
		//	Atributos del nodo

		//int value;		// En lugar de que el nodo guarde un entero, guarda algo de tipo T
		T value; 			// valor almacenado

		Node<T> *prev; 	 	//	dir del nodo anterior
		Node<T> *next;		//	dir del nodo siguiente
		
		//	Que deberia recibir el contructor de la clase? 
		//		un valor para guardar en el nodo
		//	Que valores por default deberian tener prev y next? 
		Node(T valor){	
			this->value = valor;
			this->prev = NULL;
			this->next = NULL;
		}
};

//  Clase lista enlazada doble: 
template <class T>
class List{	
    //	Que atributos necesita??

	Node<T> *first;		//	puntero al primer nodo
	Node<T> *last; 	//	puntero al ultimo nodo	
	int size;			//	numero de elementos que tiene la lista

	public:
		//	Que valores deberia tener la lista por default??
		List(){	
            this->first = NULL; 
			this->last = NULL; 
			this->size = 0;
		}
		
		//	Funciones similares a las de la lista simple

		int getSize(){ return size; }	//	Funcion para obtener el numero de elementos
		void showList();				//	Funcion para mostrar la lista
		void showListReverse();			//	Funcion para mostrar la lista en reversa
		
		//	Funciones para insertar elementos
		void insertFirst(T);				//	al principio
		void insertLast(T);					//	al final
		bool insertAtIndex(int, T); 		//	en un indice

		//	Funciones para eliminar elementos
		void deleteFirst();					//	al principio
		void deleteLast();					//	al final				
		void deleteAtIndex(int); 			//	en un indice		

		int find(T);			//	Encontrar un valor
        T get(int);			//	Obtener un valor
};

// Inserta en un indice especifico
// Complejidad O(n)
template<class T>
bool List<T>::insertAtIndex(int index, T newValue){	
    Node<T> *node = new Node<T> (newValue);  
	
	//	Insertar al inicio 
	if (index == 0){	
        this->insertFirst(newValue); 
		return true;
	}

	// Insertar al final
	if (index == this->size){
        this->insertLast(newValue); 
		return true;
	}

	if(index < size/2){		//	Cuando es mas barato insertar desde el inicio	
        Node<T> *aux = first;
		int i = 0; 

		// Recorre la lista
		while(i < size/2){
			// Verifica si se llego a la posicion anterior al indice dado
            if(i == index - 1){
				// Enlaza el nodo nuevo con la lista
                node->prev = aux;
				node->next = aux->next; 

				node->next->prev = node; 
				aux->next = node;

				// Actualiza el numero de elementos
				this->size++;
				return true;
			}

			// Avanza en la lista
			aux = aux->next;
			i++;
		}
	}

	else{  	//	Cuando es mas barato insertar desde el final 
		Node<T> *aux = last;
		int i = this->size - 1;

		// Recorre la lista (en reversa)
		while(i > size/2){
			// Verifica si se llego al indice
			if(i == index){
				// Enlaza el nodo nuevo con la lista
				node->next = aux;
				node->prev = aux->prev;

				node->prev->next = node;
				aux->prev = node;

				// Actualiza el numero de elementos
				this->size++;
				return true;
			}

			// Retrocede en la lista
			aux = aux->prev;
			i--;
		}
	}

	return false;
}

// Encontrar un valor en la lista
// Complejidad O(n)
template<class T>
int List<T>::find(T value){	
    Node<T> *aux = first;
    int i = 0;

    // Recorre la lista
    while(i < this->size){
        // Si encuentra el valor, regresa el indice
        if(aux->value == value){
            return i;
        }

        // Avanza en la lista
        aux = aux->next;
        i++;
    }

    // Si no encuentra el valor, regresa -1
    return -1;
}

// Obtiene un valor en un indice especifico
// Complejidad O(n)
template<class T>
T List<T>::get(int index){	
    Node<T> *aux = first;
    int i = 0;

    // Recorre la lista
    while(i < this->size){
        // Si encuentra el indice, regresa el valor
        if(i == index){
            return aux->value;
        }

        // Avanza en la lista
        aux = aux->next;
        i++;
    }

    // Si no encuentra el indice, regresa -1
    return NULL;
}

// Elimina un elemento en un indice especifico
// Complejidad O(n)
template<class T>
void List<T>::deleteAtIndex(int index){
    // Elimina el primer elemento
    if(index == 0){
        deleteFirst();
        return;
    }

    // Elimina el ultimo elemento
    if (index == this->size - 1){
        deleteLast();
        return;
    }

    Node<T> *aux;	// Nodo auxiliar

    // Cuando es mas barato eliminar desde el inicio
    if (index < size/2){
		// Inicia auxiliar en first
        aux = first;

		// Recorre la lista
        int i = 0;
        while (i < index){
            aux = aux->next;
            i++;
        }
    }

    // Cuando es mas barato eliminar desde el final
    else{
		// Inicia auxiliar en last
        aux = last;

		// Recorre la lista (en reversa)
        int i = size - 1;
        while (i > index){
            aux = aux->prev;
            i--;
        }
    }

    // Conecta los elementos a los lados del nodo a eliminar
    aux->prev->next = aux->next;
    aux->next->prev = aux->prev;

    // Elimina el nodo
    delete aux;

    // Actualiza el numero de elementos
    this->size--;
}

// Elimina el primer elemento
// Complejidad O(1)
template<class T>
void List<T>::deleteFirst(){	
    //  Crear un  auxiliar que guarde la direccion de first
	Node<T> *aux = first;
	
	//	Crear una puntero, llamado segundo, que tome la direccion del nodo siguiente de first
	Node<T> *second = aux->next;
	//  Asigna que el anterior a segundo ahora es last
	second->prev = last; 

	//  Y que el siguiente de last es segundo
	last->next = second;

	// Elimina aux con un delete
	delete aux;	
	
	// Ahora first es segundo
	this->first = second;

	// Disminuye el numero de elementos
	this->size--;	
}

// Elimina el ultimo elemento
// Complejidad O(1)
template<class T>
void List<T>::deleteLast(){	
	// Nodo auxiliar que guarda la direccion de last
	Node<T> *aux = this->last;

	// El penultimo elemento se vuelve el ultimo y lo enlaza con el primero
	this->last = aux->prev;
	this->last->next = first;

	// Elimina el nodo
	delete aux;

	// Actualiza el numero de elementos
	this->size--;
}

// inserta al inicio
// Complejidad O(1)
template<class T>
void List<T>::insertFirst(T newValue){	
    // Crear un nodo nuevo
	// Sintaxis: 
	// Clase<plantilla> *nombre = new Clase<plantilla>(parametros)
	Node<T> *node = new Node(newValue);

	// Crear un puntero auxiliar que guarde la direccion de first
	Node<T> *aux = first;

	// Hacer que el siguiente del nodo nuevo sea el auxiliar
	node->next = aux;
	// Y que el first ahora sea el nodo nuevo
	this->first = node;


	// Si la lista esta vacia
	if(this->size == 0){
		//	el ultimo es tambien el nodo nuevo
		this->last = node;
	}

	// Si no, 
	else{
		// el anterior a aux (viejo first) es ahora el nodo nuevo
		aux->prev = node; 
	}	

	// Para asegurar que la lista es circular
	// El anterior a first es last
	// El siguiente de last es first

	//	Finalmente actualizar el numero de elementos
	this->size++;
}

// inserta al final
// Complejidad O(1)
template<class T>
void List<T>::insertLast(T newValue){	
    // Crear un nodo nuevo
	// Sintaxis: 
	// Clase<plantilla> *nombre = new Clase<plantilla>(parametros)
	Node<T> *node = new Node<T>(newValue);

	// Crear un puntero auxiliar que guarde la direccion de last
	Node<T> *aux = this->last;

	// Hacer que el anterior del nodo nuevo sea el auxiliar (viejo last)
	node->prev = aux;
	// Y que el nuevo last ahora sea el nodo nuevo
	this->last = node;
	

	// Si la lista esta vacia
	if(this->size == 0){
		//	el first es tambien el nodo nuevo
		this->first = node;
	}

	// Si no, 
	else{
		// el siguiente a aux (viejo last) es ahora el nodo nuevo
		aux->next = node; 
	}
	
	// Para asegurar que la lista es circular
	// El anterior a first es last
	// El siguiente de last es first
	
	//	Finalmente actualizar el numero de elementos
	this->size++;
}

// Muestra la lista
// Complejidad O(n)
template<class T>
void List<T>::showList(){	
    // Crea un nodo auxiliar para iterar en la lista
	// auxiliar inicia en first
	Node<T> *aux = this->first;

	// Declara un contador i que inicie en 0
	int i = 0;

	// Imprime el numero de elementos
	cout << this->size << " elementos" << endl;

	// Mientras i sea menor que el numero de elementos
	while(i < this->size){	
        // Imprime el nodo
		cout << "El [" << i << "] elemento es:\t" << aux->value << endl;
		
		// aux avanza a aux->next
		aux = aux->next;

		// i incrementa
		i++;
	}

	cout << endl;
}

// Muestra la lista en reversa
// Complejidad O(n)
template<class T>
void List<T>::showListReverse(){
	// Crea un nodo auxiliar para iterar en la lista
	// auxiliar inicia al final de la lista
	Node<T> *aux = last;

	// Declara un contador i con el numero de elementos en la lista
	int i = this->size - 1;

	while(i >= 0){
		// Imprime el nodo
		cout << "El [" << i << "] elemento es:\t" << aux->value << endl;
		
		// aux retrocede a aux->prev
		aux = aux->prev;

		// i disminuye
		i--;
	}

	cout << endl;
}

// Funcion para obtener la fecha de una orden
// Complejidad: O(1)
string get_date(string order){
    string date;

    // Encuentra los indices en los que inicia y termina la fecha
    int date_end_index = order.find(" R:");

    // Extrae la fecha
    date = order.substr(0, date_end_index);

    return date;
}

// Funcion para obtener las coordenadas de un restaurante o lugar de entrega
// Complejidad: O(1)
string get_coordinates(string place){
    string coordinates;

    // Encuentra los indices en los que inicia y termina las coordenadas
    int coordinates_start_index = place.rfind(" (");
    int coordinates_end_index = place.rfind(")");

    // Extrae las coordenadas
    coordinates = place.substr(coordinates_start_index + 1, coordinates_end_index - coordinates_start_index + 1);

    return coordinates;
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

// Funcion para obtener el nombre del plato de una orden
// Complejidad: O(1)
string get_dish(string order){
    string dish;

    // Encuentra los indices en los que inicia y termina el nombre del plato
    int dish_start_index = order.find("O:");
    int dish_end_index = order.find("(");

    // Extrae el nombre del plato
    dish = order.substr(dish_start_index + 2, dish_end_index - dish_start_index - 2);

    return dish;
}

// Algoritmo de Dijkstra para encontrar el camino mas corto entre dos nodos
// Complejidad O((V + E) log V)
void dijkstra(int **matrix, List<string> posiciones, string start, string end, int N){
    // Arreglo para guardar la distancia mas corta entre el nodo de inicio y los demas nodos
    int *dist = (int *) calloc(N, sizeof(int));

    // Arreglo para guardar si el nodo ya fue visitado
    bool *visited = (bool *) calloc(N, sizeof(bool));

    // Arreglo para guardar predescesores
    int *pred = (int *) calloc(N, sizeof(int));

    // Inicia las distancias en infinito y los nodos como no visitados
    for(int i = 0; i < N; i++){
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    // Indices de las posiciones de inicio y fin
    int start_index = posiciones.find(start);
    int end_index = posiciones.find(end);

    // La distancia del nodo de inicio a si mismo es 0
    dist[start_index] = 0;

    // Encuentra el camino mas corto
    for(int i = 0; i < N - 1; i++){
        // Encuentra el nodo con la distancia mas corta
        int min = INT_MAX;
        int min_index;

        for(int j = 0; j < N; j++){
            if(visited[j] == false && dist[j] <= min){
                min = dist[j];
                min_index = j;
            }
        }

        // Marca el nodo como visitado
        visited[min_index] = true;

        // Actualiza la distancia de los nodos adyacentes
        for(int j = 0; j < N; j++){
            if(!visited[j] && matrix[min_index][j] && dist[min_index] != INT_MAX && dist[min_index] + matrix[min_index][j] < dist[j]){
                dist[j] = dist[min_index] + matrix[min_index][j];
                pred[j] = min_index;
            }
        }
    }

    // Muestra la distancia mas corta
    cout << "La distancia mas corta entre " << posiciones.get(start_index) << " y " << posiciones.get(end_index) << " es: " << dist[end_index] << endl;

    // Muestra el camino mas corto
    cout << "Camino mas corto: " << posiciones.get(end_index) << " ";
    int j = end_index;
    int num_aristas = 0;
    while(j != start_index){
        cout << posiciones.get(pred[j]) << " ";
        j = pred[j];
        num_aristas++;
    }

    cout << endl << "Numero de aristas: " << num_aristas << endl;
}


int main(int argc, char* argv[]){
    // Archivos de entrada
    ifstream menus("menus.txt");
    ifstream city30x30("city30x30.txt");
    ifstream restaPlaces("restaPlaces.txt");
    ifstream orders("orders-city30x30.txt");

    // Listas
    List<string> datos;

    // Variables para la matriz de adyacencia
    string rest;
    string aux;
    int i = 0;
    int **menus_matrix;
    int j;
    int a;
    int b;
    int num_restaurants;
    int num_dishes;
    int N;

    // Numero de nodos: 163 + 3638
    // int N = 3801;

    // Matriz de adyacencia para representar menus
    if(menus.is_open()){
        // Lee cada linea del archivo de menus
        while(getline(menus, rest)){
            if(i == 0){
                // cout << "Informacion: " << rest << endl;
                // Obtiene el numero de restaurantes y platos
                int index = rest.find(" ");
                aux = rest.substr(0, index);
                num_restaurants = stoi(aux);

                rest = rest.substr(index + 1);
                index = rest.find(" ");
                aux = rest.substr(0, index);
                num_dishes = stoi(aux);

                // Crea la matriz de adyacencia
                N = num_restaurants + num_dishes;

                menus_matrix = (int **) calloc (N, sizeof(int*));

                for(j = 0; j < N; j++){
                    menus_matrix[j] = (int *) calloc(N, sizeof(int));
                }

                i++;
            }

            else{
                // Obtiene los restaurantes y sus platos
                string restaurant = get_restaurant(rest);
                string dish = get_dish(rest);
                float revenue = get_revenue(rest);

                // Agrega el restaurante y el plato a la lista de datos si no estan ya en ella
                if(datos.find(restaurant) == -1){
                    datos.insertLast(restaurant);
                }

                if(datos.find(dish) == -1){
                    datos.insertLast(dish);
                }

                a = datos.find(restaurant);
                b = datos.find(dish);

                // cout << "a: " << a << " b: " << b << endl;

                // Agrega la relacion entre restaurantes y platos a la matriz de adyacencia
                // Agrega el precio del plato
                menus_matrix[a][b] = revenue;
                // Agrega la existencia del plato en el restaurante
                menus_matrix[b][a] = 1;
            }
        }
    }

    menus.close();

    // Matriz de adyacencia de los menus, cambiar N para ver una parte de la matriz
    // cout << "Matriz de adyacencia de los menus" << endl;
    // for(i = 0; i < N; i++){
    //     for(j = 0; j < N; j++){
    //         cout << menus_matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    cout << "Menus" << endl;
    cout << "1- Busqueda del menu de un restaurante en especifico" << endl;
    cout << "2- Busqueda de restaurantes que ofrecen un plato en especifico" << endl;
    cout << "> ";

    string restaurant;
    string dish;
    int restaurant_index;
    int dish_index;
    int option;
    cin >> option;
    cout << endl;

    switch(option){
        case 1:
            cout << "Menu de un restaurante en especifico" << endl;
            cout << "Seleccione un restaurante: ";
            getline(cin >> ws, restaurant);
            cout << endl;

            // Obtiene el indice del restaurante en la lista de datos
            restaurant_index = datos.find(restaurant);

            cout << "---------------------------------" << endl;
            cout << "Menu de " << restaurant << endl;
            cout << "---------------------------------" << endl;
            cout << endl;

            // Muestra los platos que ofrece el restaurante (espacios donde hay un precio)
            for(i = 0; i < N; i++){
                if(menus_matrix[restaurant_index][i] != 0){
                    cout << "Plato: " << datos.get(i) << " (Precio: " << menus_matrix[restaurant_index][i] << ")" << endl;
                }
            }

            break;

        case 2:
            cout << "Restaurantes que ofrecen un plato en especifico" << endl;
            cout << "Seleccione un plato: ";
            getline(cin >> ws, dish);
            cout << endl;
            
            // Obtiene el indice del plato en la lista de datos
            dish_index = datos.find(dish);

            cout << "-----------------------------------------------" << endl;
            cout << "Restaurantes que ofrecen " << dish << endl;
            cout << "-----------------------------------------------" << endl;
            cout << endl;

            // Muestra los restaurantes que ofrecen el plato (espacios donde haya un 1)
            for(i = 0; i < N; i++){
                if(menus_matrix[dish_index][i] == 1){
                    cout << "Restaurante: " << datos.get(i) << " (Precio: " << menus_matrix[i][dish_index] << ")" << endl;
                }
            }

            break;

        default:
            cout << "Opcion invalida" << endl;
            break;
    }

    // Lista de posiciones de la ciudad
    List<string> city_positions;

    // Variables para la matriz de adyacencia de la ciudad
    string coord;
    int **city_matrix;
    N = 961;

    // Matriz de adyacencia para representar la ciudad
    if(city30x30.is_open()){
        // Crea la matriz de adyacencia
        city_matrix = (int **) calloc (N, sizeof(int*));

        for(j = 0; j < N; j++){
            city_matrix[j] = (int *) calloc(N, sizeof(int));
        }

        // Lee cada linea del archivo de la ciudad
        // Formato de linea (0, 0) (1, 0) 50 (nodo1, nodo2, peso)
        while(getline(city30x30, coord)){
            // Obtiene los nodos y el peso
            int index = coord.find(")");
            aux = coord.substr(0, index + 1);
            // cout << "aux: " << aux << endl;
            
            coord = coord.substr(index + 1);
            index = coord.find(")");
            string aux2 = coord.substr(1, index);
            // cout << "aux2: " << aux2 << endl;

            coord = coord.substr(index + 2);
            int w = stoi(coord);
            // cout << "w: " << w << endl;

            // Agrega los nodos a la lista de posiciones si no estan ya en ella
            if(city_positions.find(aux) == -1){
                city_positions.insertLast(aux);
            }

            if(city_positions.find(aux2) == -1){
                city_positions.insertLast(aux2);
            }

            a = city_positions.find(aux);
            b = city_positions.find(aux2);

            // Agrega la relacion entre nodos a la matriz de adyacencia
            city_matrix[a][b] = w;
            city_matrix[b][a] = w;
        }
    }

    city30x30.close();

    // Matriz de adyacencia de la ciudad, cambiar N para ver una parte de la matriz
    // cout << "City30x30" << endl;
    // for(i = 0; i < 10; i++){
    //     for(j = 0; j < 10; j++){
    //         cout << city_matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    cout << endl << "Rutas" << endl;

    // Listas para almacenar los restaurantes y sus posiciones
    List<string> restaurants;
    List<string> restaurant_positions;
    int index;

    // Lee cada linea del archivo de los restaurantes
    while(getline(restaPlaces, rest)){
        index = rest.find(" (");
        restaurant = rest.substr(0, index);

        // Agrega los restaurantes y sus posiciones a las listas
        restaurants.insertLast(restaurant);
        restaurant_positions.insertLast(get_coordinates(rest));
    }

    // Variables para los casos de prueba
    i = 1;
    string position;
    string end_position;
    string date;

    // Lee cada linea del archivo de las ordenes
    while(getline(orders, rest)){
        // Extrae la informacion de la orden
        restaurant = get_restaurant(rest);
        end_position = get_coordinates(rest);
        dish = get_dish(rest);
        date = get_date(rest);

        // Obtiene el indice del restaurante en la lista de restaurantes
        index = restaurants.find(restaurant);

        // Obtiene la posicion del restaurante
        position = restaurant_positions.get(index);

        cout << "Caso de prueba " << i << endl;
        cout << "---------------" << endl;
        cout << "Orden: " << dish << endl;
        cout << "Fecha: " << date << endl;
        cout << "Restaurante de entrega: " << restaurant << " " << position << endl;
        cout << "Lugar de entrega: " << end_position << endl;

        // Obtiene el camino mas corto entre el restaurante y el lugar de entrega
        dijkstra(city_matrix, city_positions, position, end_position, N);

        cout << endl;

        i++;
    }
}