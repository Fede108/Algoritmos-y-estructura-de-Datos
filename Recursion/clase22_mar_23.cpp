#include <iostream>
#include <sstream>

#include <stdlib.h>

using namespace std;


int fib(int n){
    if(n<3) {
       return 1;
    } else {
       return fib(n-1)+fib(n-2);
    }
}

int fAux(int n, int p, int a1, int a2){
	if(n==p) {
		return a1+a2;
	} else {
		return fAux(n,p+1,a1+a2,a1);
	}
}

int fibSimple(int n){
	if(n<3) {
	 return 1;
	} else {
	  return fAux(n,3,1,1);	
	}

}

int main(int argc, char** argv)
{
    int n;
    cout<<"Entre el fibonacci"<<endl;
    cin>>n;
    cout << fibSimple(n) << endl;
    cout << fib(n) << endl;
    return 0;
}