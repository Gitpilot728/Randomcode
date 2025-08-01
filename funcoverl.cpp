#include <iostream>
using namespace std;
int sum(int num1, int num2) {
    return num1 + num2;
}
double sum(double num1, double num2) {
    return num1 + num2;
}
int sum(int num1, int num2, int num3) {
    return num1 + num2 + num3;
}
int main() {
    cout << "Sum 1 = " << sum(5, 6) << endl;
    cout << "Sum 2 = " << sum(5.5, 6.6) << endl;
    cout << "Sum 3 = " << sum(5, 6, 7) << endl;
    return 0;
}
