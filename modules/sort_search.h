#include <vector>
#include <iostream>
#include <fstream>

#include "get_value.h"

// Ordenamiento por fusion (merge)
// Complejidad promedio: O(nlog(n))
void merge(vector<string>& A, int l, int m, int r) {
    int i, j, k, s1, s2;

    // Tamanos para los subarreglos 
    s1 = m - l + 1;
    s2 = r - m;

    // Creación de subarreglos (los vectores tienen tamaño dinamico)
    vector<string> L(s1), R(s2);

    // Copia los elementos al subarreglo de la izquierda
    for(i = 0; i < s1; i++){
        L[i] = A[l + i];
    }

    // Copia los elementos al subarreglo de la derecha
    for (j = 0; j < s2; j++){
        R[j] = A[m + 1 + j];
    }
        
    i = 0;
    j = 0;
    k = l;

    // Combina los subarreglos
    while(i < s1 && j < s2){
        // Compara los elementos (convierte el string con la fecha a un int) de los subarreglos e inserta el menor
        if(get_value(L[i]) <= get_value(R[j])){
            A[k] = L[i];
            i++;
        } 
        
        else{
            A[k] = R[j];
            j++;
        }

        k++;
    }

    // Inserta los elementos restantes
    while(i < s1){
        A[k] = L[i];
        i++;
        k++;
    }

    while(j < s2){
        A[k] = R[j];
        j++;
        k++;
    }
}


void mergeSort(vector<string>& A, int l, int r) {
    int m;

    if (l < r) {
        // Encuentra el punto medio
        m = l + (r - l) / 2;

        mergeSort(A, l, m);
        mergeSort(A, m + 1, r);
        merge(A, l, m, r);
    }
}


void single_search(string date, int date_value, vector<string> orders, int n){
    ofstream search_results("outputs/search_results.txt");

    vector<string> results;
    int i, j;

    for(i = 0; i < n; i++){
        if(get_value(orders[i]) == date_value){
            results.push_back(orders[i]);
        }
    }

    cout << "Resultados de la busqueda:" << endl;
    search_results << "Resultados de la busqueda \"" << date << "\"" << endl;

    if(results.size() == 0){
        cout << "No hay resultados para esta fecha";
    }

    else{
        for(j = 0; j < results.size(); j++){
            cout << j + 1 << "- " << results[j] << endl;
            search_results << j + 1 << "- " << results[j] << endl;
        }
    }

    search_results.close();
}


void range_search(string lower_date, string upper_date, int lower_date_value, int upper_date_value, vector<string> orders, int n){
    ofstream search_results("outputs/search_results.txt");

    vector<string> results;
    int i, j;

    for(i = 0; i < n; i++){
        if(get_value(orders[i]) >= lower_date_value && get_value(orders[i]) <= upper_date_value){
            results.push_back(orders[i]);
        }
    }

    cout << "Resultados de la busqueda:" << endl;
    search_results << "Resultados de la busqueda \"" << lower_date << " - " << upper_date << "\"" << endl;

    if(results.size() == 0){
        cout << "No hay resultados para esta fecha";
    }

    else{
        for(j = 0; j < results.size(); j++){
            cout << j + 1 << "- " << results[j] << endl;
            search_results << j + 1 << "- " << results[j] << endl;
        }
    }

    search_results.close();
}