#include <cstdlib>
#include <iostream>
using namespace std;

int fib (int x);
int fib2 (int x);
int fibaux (int y, int a1 , int a2 , int x);
int fibaux_iterativo (int y, int a1, int a2, int x);

int main () {
    int result = fib (4);
    cout<<"resultado"<<endl;
    cout << result << endl;

     int result2 = fib2 (7);
    cout<<"resultado"<<endl;
    cout << result2 << endl;
    return 0;
}

int fib (int x){
    if(x< 3){
        return 1;
    }
    else {
        return fib (x-1) + fib (x -2);
    }
}

int fibaux (int y, int a1 , int a2 , int x){
    if(y==x){
        return a1 + a2;
    } else {
        return fibaux (y+1, a1+a2 , a1 , x);
    }
}

int fib2 (int x){
    if (x <3){
        return 1;
    } else {
        return fibaux_iterativo (3, 1, 1, x);
    }
}

int fibaux_iterativo (int y, int a1, int a2, int x){
    while (y!=x){
        int temp = a2;
        a2 = a1;
        a1 = temp + a1;
        y++;
    }
    return a1 + a2;
}


