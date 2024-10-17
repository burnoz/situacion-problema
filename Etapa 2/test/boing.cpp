#include <iostream>
#include <string>
#include <vector>

using namespace std;

string get_restaurant(string order){
    string restaurant;
    int restaurant_start_index = order.find("R:");
    int restaurant_end_index = order.find(" O:");

    restaurant = order.substr(restaurant_start_index + 2, restaurant_end_index - restaurant_start_index - 2);
    
    return restaurant;
}

int get_value(string order){
    string months[12] = {"ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"};
    string aux;

    int month_end_index = order.find(" ");
    string month = order.substr(0, month_end_index);

    aux = order.substr(month_end_index + 1);

    int day_end_index = aux.find(" ");
    string day = aux.substr(0, day_end_index);

    aux = aux.substr(day_end_index + 1);
    
    int time_end_index = aux.find(" ");
    string time = aux.substr(0, time_end_index);

    int value = 0;

	// Pasa por todos los elementos del arreglo
	for(int i = 0; i < 12; i++){
		if(month == months[i]){
			// Indice del elemento encontrado
			value += (i + 1) * 100000000;
            break;
		}
	}

    value += stoi(day) * 1000000;

    int hour_end_index = aux.find(":");
    string hour = time.substr(0, hour_end_index);

    aux = time.substr(hour_end_index + 1);

    int minute_end_index = aux.find(":");
    string minute = aux.substr(0, minute_end_index);

    aux = aux.substr(minute_end_index + 1);

    int second_end_index = aux.find(" ");
    string second = aux.substr(0, second_end_index);

    value += stoi(hour) * 10000;
    value += stoi(minute) * 100;
    value += stoi(second);

    return value;
}

// Merges two subarrays of vec.
// First subarray is vec[left..mid]
// Second subarray is vec[mid+1..right]
void merge(vector<string>& vec, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary vectors
    vector<string> leftVec(n1), rightVec(n2);

    // Copy data to temporary vectors
    for (i = 0; i < n1; i++)
        leftVec[i] = vec[left + i];
    for (j = 0; j < n2; j++)
        rightVec[j] = vec[mid + 1 + j];

    // Merge the temporary vectors back into vec[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if ((leftVec[i]) <= (rightVec[j])) {
            vec[k] = leftVec[i];
            i++;
        } else {
            vec[k] = rightVec[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftVec[], if any
    while (i < n1) {
        vec[k] = leftVec[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightVec[], if any
    while (j < n2) {
        vec[k] = rightVec[j];
        j++;
        k++;
    }
}

// The subarray to be sorted is in the index range [left..right]
void mergeSort(vector<string>& vec, int left, int right) {
    if (left < right) {
      
        // Calculate the midpoint
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);

        // Merge the sorted halves
        merge(vec, left, mid, right);
    }
}


int main(){
    vector<string> orders = {
        "Jun 24 19:39:45 R:La Terraza del Mar O:Falafel con Hummus(284)",
        "Feb 13 19:25:24 R:El Barzon O:ensalada Griega(140)", 
        "Feb 7 17:8:30 R:El Cafe de la Plaza O:Curry de Pollo(273)",
        "Dic 24 14:50:39 R:The Rustic Spoon O:Tiradito de Pescado(279)",
        "Ago 4 13:25:11 R:El Pueblo O:Fideua(276)",
        "ene 4 17:51:54 R:El Rinconcito Tropical O:Fettuccine Alfredo(299)",
        "Nov 2 13:5:23 R:Aere and Now O:Carne de Res en Salsa(292) " };

    vector<int> values(7);
    vector<string> restaurants(7);

    string orden = "Ago 12 15:20:30";

    string test;

    getline(cin, test);

    cout << test << endl;

    cout << get_value(orden) << endl;

    for(int i = 0; i < 7; i++){
        values[i] = get_value(orders[i]);
        restaurants[i] = get_restaurant(orders[i]);

        cout << restaurants[i] << endl;
        cout << values[i] << endl;
    }

    mergeSort(restaurants, 0, 6);
    
    for(int i = 0; i < 7; i++){
        cout << restaurants[i] << endl;
    }
}