/*AIM- To implement Linear Search using a void function that prints the result directly 
(instead of returning a value), and to understand the difference between void and 
non-void functions.*/
//{NAME}

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

// Linear Search using Void Function
void linearSearch(int arr[], int size, int key){
    for(int i = 0; i < size; i++){
        if(arr[i] == key){
            cout << "Key Found at Position : " << i + 1;
            return;
        }
    }

    cout << "Key Not Found";
}

int main(){
    int size, key;

    cout << "Enter Size of Array : ";
    cin >> size;

    int arr[size];

    cout << "Enter Array Elements : " << endl;
    fillArray(arr, size);

    cout << "Array Elements are : ";
    displayArray(arr, size);
    cout << endl;

    cout << "Enter Key Element : ";
    cin >> key;

    linearSearch(arr, size, key);

    return 0;
}