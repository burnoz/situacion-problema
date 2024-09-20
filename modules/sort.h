#include <vector>

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