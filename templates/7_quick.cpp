/* AIM- To implement Quick Sort using the Divide and Conquer approach with Lomuto 
partitioning and analyze its time and space complexity.*/
//PROGRAMMER NAME = {NAME}

#include<iostream>
using namespace std;

void fillArray(int arr[], int size){
    for(int i = 0; i < size; i++){
        cout << "Enter " << i << " Element : ";
        cin >> arr[i];
    }
}

void displayArray(int arr[], int size){
    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

int partition(int arr[], int low, int high){
    int pivot = arr[high];
    int i = low - 1;

    for(int j = low; j <= high - 1; j++){
        if(arr[j] <= pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);

    return i + 1;
}

void quickSort(int arr[], int low, int high){
    if(low < high){
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main(){
    int size;

    cout << "Enter Size of Array : ";
    cin >> size;

    int arr[size];

    fillArray(arr, size);

    cout << "Array Elements : ";
    displayArray(arr, size);

    quickSort(arr, 0, size - 1);

    cout << "Sorted Array : ";
    displayArray(arr, size);

    return 0;
}