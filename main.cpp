#include "modules/sort_search.h"

int main(int argc, char* argv[]){
    // Lee la ruta del archivo desde la terminal
    ifstream file(argv[1]);

    // Crea (o escribe sobre) los archivos de salida
    ofstream sorted_orders("outputs/sorted_orders.txt");

    int option;
    int i = 0;

    string start_date;
    string end_date;
    int start_date_value;
    int end_date_value;

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

    // Busqueda de ordenes por fecha
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

        single_search(start_date, start_date_value, orders, i);

        break;
    
    case 2:
        cout << endl << "Ingrese las fechas y horas (ej. \"Jun 12 06:51:16\"):" << endl;
        
        cout << "Limite inferior: ";
        getline(cin >> ws, start_date);
        start_date_value = get_value(start_date);

        cout << "Limite inferior: ";
        getline(cin >> ws, end_date);
        end_date_value = get_value(end_date);

        range_search(start_date, end_date, start_date_value, end_date_value, orders, i);

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