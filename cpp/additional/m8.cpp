#include <iostream>
#include <fstream>
using namespace std;


int** iter(int** a, int** b, int n)
{
  int** res = new int* [n];

  for (int i = 0; i < n; i++) {
    res[i]=new int[n];
    for (int j=0;j<n;j++)
      res[i][j] = 0;
  }

  for (int row = 0; row < n; row++)
    for (int col = 0; col < n; col++)
      for (int inner = 0; inner < n; inner++)
        res[row][col] += a[row][inner] * b[inner][col];

  return res;
}


void power(int** a, int** b, int n, int current, int s)
{
  if (current == s) {
    return;
  }
  else
  {    
    current++;
    power(iter(a, b, n), b, n, current, s);
  }
}


int main (void)
{

  ifstream in ("input.txt");
  ofstream out ("output.txt");
  
  int n;
  in >> n;
  
  int** a = new int *[n];
  int** b = new int *[n];
  for (int i = 0; i < n; i++) {
    a[i]=new int[n];
    b[i]=new int[n];    
  }
  
  int s;
  in >> s;
  for ( int i = 0; i < n; i++)
    for ( int j = 0; j < n; j++)
      {
        in >> a[i][j];
        b[i][j] = a[i][j];
      }
  
  power(a, b, n, 1, s);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      cout << a[i][j] << " ";
    cout << endl;
  }
}