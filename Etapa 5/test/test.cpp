#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

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

		void show();				// Ver toda la tabla
		void show2();				// Ver espacio ocupados en la tabla
		void insert(string, T);		// Agregar un elemento nuevo, recibe key y value
		void remove(string);		// Remover uno por su key
        void update(string, T);     // Cambia el valor de una llave
		int find(string);			// Encontrar el indice de una key
};


template<class T> 
void Hash<T>::show(){	
    int j;

	// Muestra toda la tabla, su indice, char_key, int_key, int_key real y valor almacenado
	for(j =0; j < maxSize; j++){	
        cout << j << " " << table[j]->str_key << " " << table[j]->int_key << " " << table[j]->h_key << " " << table[j]->item << endl; 	
    }
	
    cout << endl << endl;
}

// Muestra los espacios ocupados en la tabla
// Complejidad: O(n)
template<class T> 
void Hash<T>::show2(){	
    int j;

	// Muestra toda la tabla, su indice, char_key, int_key, int_key real y valor almacenado
	for(j = 0; j < maxSize; j++){	
        if(table[j]->free == false)
            cout << table[j]->str_key << " " << table[j]->item << endl;
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

        // Verifica si el espacio esta libre (no hay colisiones)
        if(table[h_key]->str_key == str_key){
            return h_key;
        }

        i++;
        alternate++;
    }

    return -1;
}


int main(){
    string menus[] = {
        "R:La Terraza del Mar O:Falafel con Hummus(284)", 
        "R:El Barzon O:ensalada Griega(140)", 
        "R:El Cafe de la Plaza O:Curry de Pollo(273)", 
        "R:The Rustic Spoon O:Tiradito de Pescado(279)", 
        "R:El Pueblo O:Fideua(276)", 
        "R:El Cafe de Lola O:Hummus con Pita(151)", 
        "R:La Abuela O:Fettuccine Alfredo(282)", 
        "R:Cocina Miguel O:Arroz con Pollo(274)", 
        "R:La Brasserie Parisienne O:Sopa de Cebolla(135)"
    };

    Hash<Hash<int>*> hash(11);

    for(int i = 0; i < 9; i++){
        string restaurant = get_restaurant(menus[i]);
        string dish = get_dish(menus[i]);
        int revenue = get_revenue(menus[i]);

        int index = hash.find(restaurant);
        // cout << "index: " << index << endl;

        if(index == -1){
            Hash<int> *inner_hash = new Hash<int>(11);
            inner_hash->insert(dish, revenue);
            hash.insert(restaurant, inner_hash);
        }

        else{
            hash.table[index]->item->insert(dish, revenue);
        }
    }

    // Muestra el hash de cada restaurante
    for(int i = 0; i < 11; i++){
        if(hash.table[i]->free == false){
            cout << hash.table[i]->str_key << endl;
            hash.table[i]->item->show2();
        }
    }
}