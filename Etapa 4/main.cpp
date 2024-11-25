#include <string>
// #include <vector>
#include <iostream>
#include <fstream>

using namespace std;

// Class node: un valor y un puntero a otro nodo
template <class T>
class Node{	
    public:
		T value;    // Valor almacenado

		Node<T> *prev;  // Dir del nodo anterior
		Node<T> *next;	// Dir del nodo siguiente
		 
		Node(T valor){	
			this->value = valor;
			this->prev = NULL;
			this->next = NULL;
		}
};

//  Clase lista enlazada doble: 
template <class T>
class List{	
	Node<T> *first;	//	Puntero al primer nodo
	Node<T> *last; 	//	Puntero al ultimo nodo	
	int size;		//	Numero de elementos que tiene la lista

	public:
		List(){	
            this->first = NULL; 
			this->last = NULL; 
			this->size = 0;
		}
		
		//	Funciones similares a las de la lista simple
		void insertLast(T);	// Inserta al final
		int find(T);		// Encontrar el indice de un valor
        T get(int);			// Obtener un valor
};

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
    this->first->prev = last;
	// El siguiente de last es first
    this->last->next = first;
	
	//	Finalmente actualizar el numero de elementos
	this->size++;
}

// Funcion para obtener la fecha de una orden
// Complejidad: O(1)
string get_date(string order){
    string date;

    // Encuentra el indice en el que termina la fecha
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
    // Arreglo para guardar la distancia mas corta
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
    cout << "Camino: " << posiciones.get(end_index) << " ";
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

    // Lista de datos
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
    N = 961; // 31 ^ 31

    // Matriz de adyacencia para representar la ciudad
    if(city30x30.is_open()){
        // Crea la matriz de adyacencia
        city_matrix = (int **) calloc (N, sizeof(int*));

        for(j = 0; j < N; j++){
            city_matrix[j] = (int *) calloc(N, sizeof(int));
        }

        // Lee cada linea del archivo de la ciudad
        // Formato de linea (0, 0) (1, 0) 50
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

            // Agrega el peso entre los nodos a la matriz
            city_matrix[a][b] = w;
            // Grafo no dirigido
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

    restaPlaces.close();

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
        cout << "----------------" << endl;
        cout << "Orden: " << dish << endl;
        cout << "Fecha: " << date << endl;
        cout << "Restaurante de entrega: " << restaurant << " " << position << endl;
        cout << "Lugar de entrega: " << end_position << endl;

        // Obtiene el camino mas corto entre el restaurante y el lugar de entrega
        dijkstra(city_matrix, city_positions, position, end_position, N);

        cout << endl;

        i++;
    }

    orders.close();
}