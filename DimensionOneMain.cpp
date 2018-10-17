#include <iostream>
using namespace std;
void CalculateInSquare(double *X,double *U,double *Y,int N,int M,double* ans);
void CalculateInSqrt(double *X,double *U,double *Y,int N,int M,double* ans);
void CalculateInLog(double *X,double *U,double *Y,int N,int M,double* ans);
void CalculateInLinear(double *X,double *U,double *Y,int N,int M,double* ans);
void CalculateForUnbalance(double *X,double *U,double *Y,int N,int M,double *ans);
int main(int argc, char *argv[]){
    int N,M;
    cin >> N >> M;
    double X[N];
    double U[N];
    double Y[M];
    for(int i=0;i<N;i++){
        cin >> X[i] >> U[i];
    }
    for(int i=0;i<M;i++){
        cin >> Y[i];
    }
    double ans[M];
    for(int i=0;i<M;i++){
        ans[i] = 0;
    }
    string str = string(argv[1]);
    if(str == "Normal"){
        CalculateInSquare(X,U,Y,N,M,ans);    
    }
    else if(str == "Sqrt"){
        CalculateInSqrt(X,U,Y,N,M,ans);    
    }
    else if(str == "Log"){
        CalculateInLog(X,U,Y,N,M,ans);    
    }
    else if(str == "Linear"){
        CalculateInLinear(X,U,Y,N,M,ans);    
    }
    else if(str == "Unbalance"){
        CalculateForUnbalance(X,U,Y,N,M,ans);
    }
    for(int i=0;i<M;i++){
        cout << ans[i] << endl;
    }
}