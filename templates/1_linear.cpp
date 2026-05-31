/*AIM- To implement Linear Search using a function that returns the position (index) of the key element in the array, and
to analyze its time and space complexity.*/
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
}

int linearSearch(int arr[], int size, int key){
    for(int i = 0; i < size; i++){
        if(arr[i] == key){
            return i;
        }
    }
    return -1;
}

int main(){
    int size, key;

    cout << "Enter Size of Array : ";
    cin >> size;

    int arr[size];

    fillArray(arr, size);

    cout << "Array Elements : ";
    displayArray(arr, size);
    cout << endl;

    cout << "Enter Key Element : ";
    cin >> key;

    int result = linearSearch(arr, size, key);

    if(result != -1){
        cout << "Key Found at pos : " << result+1;
    }
    else{
        cout << "Key Not Found";
    }

    return 0;
}