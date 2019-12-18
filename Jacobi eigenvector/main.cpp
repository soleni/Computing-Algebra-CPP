#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

const int n = 6;
double k = 0;
const double Eps = 5e-7;

int main() {
    ifstream getData("data.txt");
    //ofstream cout("output.txt");
    if(!getData.is_open()) return 1;

    vector<double> temp;
    temp.resize(n,0);

    vector<vector<double>> B;
    B.resize(n,temp);
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n ; j++){
            getData >> B[i][j];
        }
    }

    vector<vector<double>> C;
    C.resize(n,temp);
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n ; j++){
            getData >> C[i][j];
        }
    }

    getData >> k;
    getData.close();

    vector<vector<double>> A;
    A.resize(n,temp);
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n ; j++){
            A[i][j] = B[i][j] + C[i][j]*k;
        }
    }
    cout << "MATRIX :\n\n";
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n ; j++){
            cout << setprecision(4) << setw(9) << A[i][j] << " ";
        }
        cout << "\n";
    }
    cout <<"\n";

    vector<double> squares;
    squares.resize(n,0);
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n ; j++){
            if(i != j)
            squares[i] += A[i][j]*A[i][j];
        }
    }

    int count = 0;
    while(true){
        int l = 0, k = 0;
        double maxtemp = 0;
        double angle;


        for(int i =0 ;i < n ;i++){
            for(int j =0;j <n;j++){
                if(i != j && maxtemp < abs(A[i][j])){
                    maxtemp = abs(A[i][j]);
                    k = i;
                    l = j;
                }
            }
        }


        //FIND MAX
        for(int i = 0 ; i < n; i++){
            if(maxtemp < abs(squares[i])){
                maxtemp = abs(squares[i]);
                k = i;
            }
        }
        maxtemp = 0;
        for(int i = 0 ; i < n; i++){
            if(maxtemp < abs(A[k][i]) && k!=i){
                maxtemp = abs(A[k][i]);
                l = i;
            }
        }

        if(abs(A[k][l]) < Eps) break;
        count ++;

        //CHANGE SQUARES BEFORE ITERATION
        squares[k]-= A[k][k]*A[k][k]  + A[k][l]*A[k][l];
        squares[l]+= squares[k];

        //GET ANGLE
        angle = atan(2*A[k][l]/(A[k][k]-A[l][l]))/2;

        //A*T = B
        for(int i =0;i < n;i++){
            double bk,bl;
            bk = A[i][k]*cos(angle) + A[i][l]*sin(angle);
            bl = -1*A[i][k]*sin(angle) + A[i][l]*cos(angle);
            A[i][k] = bk;
            A[i][l] = bl;
        }

        //T(t)*B = C
        for(int i =0;i < n;i++){
            double ck,cl;
            ck = A[k][i]*cos(angle) + A[l][i]*sin(angle);
            cl = -1*A[k][i]*sin(angle) + A[l][i]*cos(angle);
            A[k][i] = ck;
            A[l][i] = cl;
        }

        //CHANGE SQUARES AFTER ITERATION
        squares[k]+= A[k][k]*A[k][k];
        squares[l]-= squares[k];
    }

    cout << count <<"\n\n";
    cout << "MATRIX :\n\n";
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n ; j++){
            cout << setprecision(4) << setw(9) << A[i][j] << " ";
        }
        cout << "\n";
    }
    cout <<"\n";
}