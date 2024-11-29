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
int get_revenue(string order){
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

// Clase para un elemento de la tabla
template<class T>
class Element{
	public:
		string str_key;		// Llave string, como "Ana"
		int int_key;		// Llave entera, resultante de la llave string
		int h_key;		    // Indice real asignado con base en int_key
		T item;		        // El objeto asociado con la llave
		bool free;		    // Una bandera para saber si este elemento de la tabla esta libre o no

		//	Constructor
		Element<T>(){	
            str_key = "";
            int_key = -1;
            h_key = -1;
            // item = -1;
            free = true;
		}
};

// Clase para la tabla hash
template<class T>
class Hash{	
    public:
		int maxSize;	    // Tamaño maximo
        int currentSize;    // Tamaño actual	
        int i;              // Contador de colisiones
		Element<T> **table;	// Puntero a arreglo de los elementos
		
		Hash(int size){
            int j;
			maxSize = size;
            currentSize = 0;
            i = 0;
            table = new Element<T>*[maxSize];

            for(j = 0; j < maxSize; j++){
                table[j] = new Element<T>();
            }
		}

        void show();               // Ver los espacios ocupados
		void insert(string, T);		// Agregar un elemento nuevo, recibe key y value
		void remove(string);		// Remover uno por su key
        void update(string, T);     // Cambia el valor de una llave
		int find(string);			// Encontrar el indice de una key
};

// Muestra los espacios ocupados en la tabla
// Complejidad: O(n)
template<class T> 
void Hash<T>::show(){	
    int j;
    int k = 1;

	// Muestra toda la tabla, su indice, char_key, int_key, int_key real y valor almacenado
	for(j = 0; j < maxSize; j++){	
        if(table[j]->free == false){
            cout << k << ". " << table[j]->str_key << " (Precio: $" << table[j]->item << ")" << endl;
            k++;
        }
    }
	
    cout << endl << endl;
}

// Inserta un elemento en la tabla
// Complejidad: O(1)
template<class T> 
void Hash<T>::insert(string str_key, T value){  // Recibe algo como insert("Annie", 23)
    int key = 0;
    int h_key;
    int flag;
    int k;
    int alternate;
    
    if(currentSize < maxSize && find(str_key) == -1){
        // Calcula el valor numerico de la llave
        for(k = 0; k < size(str_key); k++){
            key += int(str_key[k]);
        }
        
        i = 0; // Contador de colisiones
        alternate = 1; // Variable para alternar el signo al calcular h_key
        flag = 0;

        while(flag == 0){
            // Quadratic probing
            if(alternate % 2 != 0){
                h_key = (key + (i * i)) % maxSize;                
            }

            else{
                h_key = (key - (i * i)) % maxSize;
            }

            // Verifica si el espacio esta libre (no hay colisiones)
            if(table[h_key]->free == true){
                // Indica que el espacio ya no esta libre
                table[h_key]->free = false;

                // Guarda el elemento en el espacio
                table[h_key]->str_key = str_key;
                table[h_key]->int_key = key;
                table[h_key]->h_key = h_key;
                table[h_key]->item = value;

                // Aumenta el numero de elementos
                currentSize++;

                // Sale del ciclo
                flag = 1;
            }

            // El espacio esta ocupado (hay una colision)
            else{
                // Suma una colision
                i++;
            }

            alternate++;
        }
    }

    else{
        cout << "Tabla llena" << endl;
    }
}

// Elimina un elemento de la tabla
// Complejidad: O(1 + a) por el uso de find
template<class T> 
void Hash<T>::remove(string str_key){  // Recibe una key como "Annie"
    int index = find(str_key);

    if(index != -1){
        // Indica que el espacio ahora esta libre
        table[index]->free = true;

        // Elimina el elemento (regresa a los valores por defecto)
        table[index]->str_key = "";
        table[index]->int_key = -1;
        table[index]->h_key = -1;
        table[index]->item = -1;

        // Disminuye el numero de elementos
        currentSize--;
    }

    else{
        cout << "La llave no existe en la tabla" << endl;
    }
}

// Inserta un elemento en la tabla
// Complejidad: O(1 + a) por el uso de find
template<class T> 
void Hash<T>::update(string str_key, T newValue){  // Recibe algo como update("Annie", 23)
    int index = find(str_key);
    int key = 0;
    int k;

    if(index != -1){
        // Actualiza el valor de la llave
        table[index]->item = newValue;

        // Disminuye el numero de elementos
        currentSize--;
    }

    else{
        cout << "La llave no existe en la tabla" << endl;
    }
}

// Encuentra un elemento en la tabla
// Complejidad: O(1 + a)
template<class T>
int Hash<T>::find(string str_key) {
    int key = 0;
    int h_key;
    int i = 0;
    int alternate = 1;

    // Calcula el valor numerico de la llave
    for(int k = 0; k < size(str_key); k++){
        key += int(str_key[k]);
    }

    while(i < maxSize){
        // Quadratic probing
        if(alternate % 2 != 0){
            h_key = (key + (i * i)) % maxSize;
        }

        else{
            h_key = (key - (i * i)) % maxSize;
        }

        // Verifica si la llave del espacio es igual a la llave buscada
        if(h_key >= 0 && table[h_key]->str_key == str_key){
            return h_key;
        }

        i++;
        alternate++;
    }

    return -1;
}

// Algoritmo de Dijkstra para encontrar el camino mas corto entre dos nodos
// Complejidad O((V + E) log V)
List<string> dijkstra(int **matrix, List<string> posiciones, string start, Hash<string> res_positions, int N){
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

    // Indice de las posicion de inicio
    int start_index = posiciones.find(start);

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

    // Lista de restaurantes mas cercanos
    List<string> closest;

    string min1 = "";
    string min2 = "";
    string min3 = "";

    int min1_index = -1;
    int min2_index = -1;
    int min3_index = -1;

    // Encuentra los 3 restaurantes mas cercanos
    for(int i = 0; i < res_positions.maxSize; i++){
        if(res_positions.table[i]->free == false){
            string coordinates = res_positions.table[i]->item;
            int index = posiciones.find(coordinates);

            if(dist[index] < dist[min1_index] || min1_index == -1){
                min3 = min2;
                min3_index = min2_index;

                min2 = min1;
                min2_index = min1_index;

                min1 = res_positions.table[i]->str_key;
                min1_index = index;
            }

            else if(dist[index] < dist[min2_index] || min2_index == -1){
                min3 = min2;
                min3_index = min2_index;

                min2 = res_positions.table[i]->str_key;
                min2_index = index;
            }

            else if(dist[index] < dist[min3_index] || min3_index == -1){
                min3 = res_positions.table[i]->str_key;
                min3_index = index;
            }
        }
    }

    cout << "Restaurantes mas cercanos a la posicion " << start << endl;
    cout << "1. " << min1 << " a " << dist[min1_index] << " metros" << endl;
    cout << "2. " << min2 << " a " << dist[min2_index] << " metros" << endl;
    cout << "3. " << min3 << " a " << dist[min3_index] << " metros" << endl;
    
    closest.insertLast(min1);
    closest.insertLast(min2);
    closest.insertLast(min3);

    return closest;   
}


int main(int argc, char* argv[]){
    // Archivos de entrada
    ifstream menus("menus.txt");
    ifstream city30x30("city30x30.txt");
    ifstream restaPlaces("restaPlaces.txt");

    // Hash que guarda un hash de platos y su precio para cada restaurante
    Hash<Hash<int>*> restaurants(239);

    // Hash que guarda un hash de restaurantes y su precio para cada plato
    Hash<Hash<int>*> dishes(3911);

    // Variables para leer los archivos
    string line;
    string restaurant;
    string dish;
    int price;
    int index;
    int k = 0;

    // Lee el archivo de menus
    if(menus.is_open()){
        while(getline(menus, line)){
            if(k == 0){
                k++;
            }

            else{
                // Obtiene el restaurante, platillo y precio
                restaurant = get_restaurant(line);
                dish = get_dish(line);
                price = get_revenue(line);

                index = restaurants.find(restaurant);

                if(index == -1){
                    // cout << "Insertando restaurante: " << restaurant << endl;

                    Hash<int> *inner_hash = new Hash<int>(9973);
                    inner_hash->insert(dish, price);
                    restaurants.insert(restaurant, inner_hash);
                }

                else{
                    // cout << "Insertando platillo: " << dish << " en " << restaurant << endl;
                    restaurants.table[index]->item->insert(dish, price);
                }

                index = dishes.find(dish);

                if(index == -1){
                    // cout << "Insertando platillo: " << dish << endl;

                    Hash<int> *inner_hash = new Hash<int>(3643);
                    inner_hash->insert(restaurant, price);
                    dishes.insert(dish, inner_hash);
                }

                else{
                    // cout << "Insertando restaurante: " << restaurant << " en " << dish << endl;
                    dishes.table[index]->item->insert(restaurant, price);
                }
            }
        }
    }

    cout << "Opciones" << endl;
    cout << "1- Busqueda del menu de un restaurante en especifico" << endl;
    cout << "2- Busqueda de restaurantes que ofrecen un plato en especifico" << endl;
    cout << "3- Continuar" << endl;
    cout << "> ";
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
            index = restaurants.find(restaurant);

            cout << "---------------------------------" << endl;
            cout << "Menu de " << restaurant << endl;
            cout << "---------------------------------" << endl;
            cout << endl;

            // Muestra los platos que ofrece el restaurante
            restaurants.table[index]->item->show();

            break;

        case 2:
            cout << "Restaurantes que ofrecen un plato en especifico" << endl;
            cout << "Seleccione un plato: ";
            getline(cin >> ws, dish);
            cout << endl;
            
            // Obtiene el indice del plato en la lista de datos
            index = dishes.find(dish);

            cout << "-----------------------------------------------" << endl;
            cout << "Restaurantes que ofrecen " << dish << endl;
            cout << "-----------------------------------------------" << endl;
            cout << endl;

            // Muestra los restaurantes que ofrecen el plato
            dishes.table[index]->item->show();

            break;

        case 3:
            break;

        default:
            cout << "Opcion invalida" << endl;
            break;
    }

    // Lista de posiciones de la ciudad
    List<string> city_positions;

    // Variables para la matriz de adyacencia de la ciudad
    string coord;
    string aux;
    int i = 0;
    int **city_matrix;
    int j;
    int a;
    int b;
    int N = 900; // max: (29, 29)

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
    // for(k = 0; k < 10; k++){
    //     for(j = 0; j < 10; j++){
    //         cout << city_matrix[k][j] << " ";
    //     }
    //     cout << endl;
    // }

    // Hash de restaurantes y sus coordenadas
    Hash<string> restaurant_coordinates(239);

    // Lee el archivo de restaurantes y sus coordenadas
    if(restaPlaces.is_open()){
        while(getline(restaPlaces, coord)){
            // Obtiene el nombre del restaurante y sus coordenadas
            index = coord.find(" (");
            restaurant = coord.substr(0, index);
            string coordinates = get_coordinates(coord);

            // Inserta el restaurante y sus coordenadas en el hash
            restaurant_coordinates.insert(restaurant, coordinates);
        }
    }

    restaPlaces.close();

    // Busqueda de restaurantes cercanos
    string start_position;
    List<string> closest;

    cout << "Busqueda de restaurantes cercanos" << endl;
    cout << "Seleccione una posicion de inicio (formato: (0, 0)): ";
    getline(cin >> ws, start_position);
    cout << endl;

    closest = dijkstra(city_matrix, city_positions, start_position, restaurant_coordinates, N);

    cout << endl;
    cout << "Consultar menu de los restaurantes" << endl;
    cout << "1. Si" << endl;
    cout << "2. No" << endl;
    cout << "> "; 
    cin >> option;

    switch(option){
        case 1:
            cout << "Seleccione un restaurante de los encontrados: ";
            cin >> option;
            cout << endl;

            // Obtiene el nombre del restaurante
            restaurant = closest.get(option - 1);

            cout << "---------------------------------" << endl;
            cout << "Menu de " << restaurant << endl;
            cout << "---------------------------------" << endl;
            cout << endl;
            
            // Muestra el menu del restaurante
            restaurants.table[restaurants.find(restaurant)]->item->show();

            break;

        case 2:
            break;

        default:
            cout << "Opcion invalida" << endl;
            break;
    }
}