/*AIM- To implement Heap Sort using the Max-Heap data structure in C/C++, demonstrate Build-Max-Heap and Heapify
operations, and analyze the time and space complexity of the algorithm.*/
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

void heapify(int arr[], int n, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && arr[left] > arr[largest]){
        largest = left;
    }

    if(right < n && arr[right] > arr[largest]){
        largest = right;
    }

    if(largest != i){
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void buildMaxHeap(int arr[], int n){
    for(int i = n / 2 - 1; i >= 0; i--){
        heapify(arr, n, i);
    }
}

void heapSort(int arr[], int n){
    buildMaxHeap(arr, n);

    for(int i = n - 1; i > 0; i--){
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
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

    heapSort(arr, size);

    cout << "Sorted Array : ";
    displayArray(arr, size);

    return 0;
}