/*AIM- To implement arithmetic operations — Multiplication (X×Y), Exponentiation (X^Y), and Integer Division (X÷Y) — using
Recursion in C/C++, understand the concept of base case and recursive case, and analyze the time and space complexity of
each recursive function.*/
//PROGRAMMER NAME = {NAME}

#include<iostream>
using namespace std;

int multiply(int x, int y){
    if(y == 0){
        return 0;
    }

    if(y < 0){
        return -multiply(x, -y);
    }

    return x + multiply(x, y - 1);
}

double power(double x, int y){
    if(y == 0){
        return 1;
    }

    if(y < 0){
        return 1 / power(x, -y);
    }

    return x * power(x, y - 1);
}

int divide(int x, int y){
    if(x < y){
        return 0;
    }

    return 1 + divide(x - y, y);
}

int main(){
    int x, y;

    cout << "Enter Value of X : ";
    cin >> x;

    cout << "Enter Value of Y : ";
    cin >> y;

    int result_mul = multiply(x, y);
    cout << "X * Y = " << result_mul << endl;

    double result_pow = power(x, y);
    cout << "X ^ Y = " << result_pow << endl;

    if(y == 0){
        cout << "Division by Zero Not Allowed" << endl;
    }
    else{
        int result_div = divide(x, y);
        cout << "X / Y = " << result_div << endl;
    }

    return 0;
}