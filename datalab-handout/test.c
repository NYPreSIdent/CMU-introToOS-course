#include<stdio.h>
int fib(int n) {
    if (n <= 2) {
        return n;
    }
    return fib(n-1) + fib(n-2);
}
int fib(int n) {
    int[] arry1 = int[100];
    arry[0] = 1;
    arry[1] = 1;
    for (int i = 2; i < 100; i++) {
        arry[i] = arry[i-1] + arry[i-2];
    }
    return arry[n]; 
}
int main() {
    int result = 0;
    for (int i = 1; i <= 100; i += 1) {
        result += 1;
    }
}
