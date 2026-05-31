/*AIM- To implement multiplication (X*Y), exponentiation (X^Y), and division (X/Y) 
using the Divide and Conquer approach in C++, and analyze their time and 
space complexities.*/
//PROGRAMMER NAME = {NAME}

#include<iostream>
using namespace std;

int multiply(int x, int y){
    if(x == 0 || y == 0){
        return 0;
    }

    if(x == 1){
        return y;
    }

    int temp = 2 * multiply(x / 2, y);

    if(x % 2 != 0){
        temp = temp + y;
    }

    return temp;
}

long long power(long long x, int y){
    if(y == 0){
        return 1;
    }

    if(y == 1){
        return x;
    }

    if(y % 2 == 0){
        return power(x * x, y / 2);
    }

    return power(x * x, (y - 1) / 2) * x;
}

double divide(double x, double y){
    return x / y;
}

int main(){
    int x, y;

    cout << "Enter Value of X : ";
    cin >> x;

    cout << "Enter Value of Y : ";
    cin >> y;

    cout << "X * Y = " << multiply(x, y) << endl;

    cout << "X ^ Y = " << power(x, y) << endl;

    if(y == 0){
        cout << "Division by Zero Not Allowed" << endl;
    }
    else{
        cout << "X / Y = " << divide(x, y) << endl;
    }

    return 0;
}