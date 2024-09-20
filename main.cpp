#include <fstream> 
#include <iostream>

#include "modules/sort.h"

int main(int argc, char* argv[]){
    // Lee la ruta del archivo desde la terminal
    ifstream file(argv[1]);

    // Crea (o escribe sobre) los archivos de salida
    ofstream search_results("outputs/search_results.txt");
    ofstream sorted_orders("outputs/sorted_orders.txt");

    int i = 0;

    // Variable auxiliar para leer cada linea del archivo
    string line;

    // Vector para almacenar las ordenes
    vector<string> orders(10000);
    
    // Pasa por cada linea del archivo
    while(getline(file, line)){
        // Copia la linea al vector de ordenes
        orders[i] = line;
        i++;
    }

    // Ordena los elementos de acuerdo a su fecha
    mergeSort(orders, 0, i - 1);

    // Imprime las primeras 10 ordenes en la terminal
    for(int j = 0; j < 10; j++){
        cout << orders[j] << endl;
    }

    // Copia la lista ordenada al archivo de salida correspondiente
    for(int k = 0; k < i; k++){
        sorted_orders << orders[k] << endl;
    }

    cout << endl << endl;

    cout << "-----------------------------" << endl;
    cout << "Busqueda de ordenes por fecha" << endl;
    cout << "-----------------------------" << endl;
    cout << "Ingrese el limite menor: " << endl;
    cout << ">";

    // Cierra los archivos utilizados en el programa
    file.close();
    search_results.close();
    sorted_orders.close();

    return 0;
}