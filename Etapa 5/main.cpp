#include <string>
// #include <vector>
#include <iostream>
#include <fstream>

using namespace std;

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
            item = -1;
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
		void insert(string, T);		// Agregar un elemento nuevo, recibe key y value
		void remove(string);		// Remover uno por su key
        void update(string, T);     // Cambia el valor de una llave
		int find(string);			// Encontrar el indice de una key
};


template<class T> 
void Hash<T>::show(){	
    int j;

	// Muestra toda la tabla, su indice, char_key, int_key, int_key real y valor almacenado
	for (j =0; j < maxSize; j++){	
        cout << j << " " << table[j]->str_key << " " << table[j]->int_key << " " << table[j]->h_key << " " << table[j]->item << endl; 	
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


int main(int argc, char* argv[]){

}