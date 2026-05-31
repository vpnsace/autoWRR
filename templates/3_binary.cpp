/*AIM- To implement the Binary Search algorithm using an iterative approach 
(using loops) and to analyze its time andspace complexity.*/
//PROGRAMMER NAME = {NAME}

#include<iostream>
using namespace std;

void fillArray(int arr[], int size){
    for(int i = 0; i < size; i++){
        cout << "Enter " << i << " Element : ";
        cin >> arr[i];

        if(i > 0 && arr[i] < arr[i - 1]){
            cout << "Data is Unsorted. Enter a value greater than or equal to "
                 << arr[i - 1] << endl;
            i--;
        }
    }
}

void displayArray(int arr[], int size){
    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
}

int binarySearch(int arr[], int first, int last, int key){
    while(first <= last){
        int mid = first + (last - first) / 2;

        if(arr[mid] == key){
            return mid;
        }
        else if(key < arr[mid]){
            last = mid - 1;
        }
        else{
            first = mid + 1;
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

    int result = binarySearch(arr, 0, size - 1, key);

    if(result != -1){
        cout << "Key Found at pos : " << result+1;
    }
    else{
        cout << "Key Not Found";
    }

    return 0;
}