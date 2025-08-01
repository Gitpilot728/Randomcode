// Cpp program for Pascal’s Triangle Using Dynamic Programming 
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> printPascal(int n) {
    vector<vector<int>> mat;
    for (int row = 0; row < n; row++) {
      	vector<int>arr;
        for (int i = 0; i <= row; i++) {
        if (row == i || i == 0)
            arr.push_back(1);
        else
            arr.push_back(mat[row - 1][i - 1] + mat[row - 1][i]);
        }
        mat.push_back(arr);
    }
  return mat;
}
int main() {
    int n = 5;
    vector<vector<int>> mat = printPascal(n);
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            	cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
