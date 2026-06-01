/*AIM- To implement the Binary Search algorithm using a recursive approach and 
to analyze its time and space complexity using recurrence relations.*/
//{NAME}

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


    if(first > last){
        return -1;
    }

    int mid = first + (last - first) / 2;
    if(arr[mid] == key){
        return mid;
    }

    if(key < arr[mid]){
        return binarySearch(arr, first, mid - 1, key);
    }
    return binarySearch(arr, mid + 1, last, key);
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