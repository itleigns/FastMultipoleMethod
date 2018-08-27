#include <iostream>
#include <chrono>
using namespace std;
void CalculateInSquare(double *X,double *U,double *Y,int N,int M,double* ans);
void CalculateInSqrt(double *X,double *U,double *Y,int N,int M,double* ans);
void CalculateInLog(double *X,double *U,double *Y,int N,int M,double* ans);
void CalculateInLinear(double *X,double *U,double *Y,int N,int M,double* ans);
int main(){
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
    chrono::system_clock::time_point  start = chrono::system_clock::now();
    CalculateInSquare(X,U,Y,N,M,ans);
    chrono::system_clock::time_point  end = chrono::system_clock::now();
    double elapsed = chrono::duration_cast<chrono::milliseconds>(end-start).count();
    #ifdef PLOT
        cout << N << " " << elapsed/1000 << " ";
    #else
        cout << "duration = " << elapsed/1000 << "sec.\n";
    #endif
    for(int i=0;i<M;i++){
        ans[i] = 0;
    }
    start = chrono::system_clock::now();
    CalculateInSqrt(X,U,Y,N,M,ans);
    end = chrono::system_clock::now();
    elapsed = chrono::duration_cast<chrono::milliseconds>(end-start).count();
    #ifdef PLOT
        cout << elapsed/1000 << " ";
    #else
        cout << "duration = " << elapsed/1000 << "sec.\n";
    #endif
    for(int i=0;i<M;i++){
        ans[i] = 0;
    }
    start = chrono::system_clock::now();
    CalculateInLog(X,U,Y,N,M,ans);
    end = chrono::system_clock::now();
    elapsed = chrono::duration_cast<chrono::milliseconds>(end-start).count();
    #ifdef PLOT
        cout << elapsed/1000 << " ";
    #else
        cout << "duration = " << elapsed/1000 << "sec.\n";
    #endif
    for(int i=0;i<M;i++){
        ans[i] = 0;
    }
    start = chrono::system_clock::now();
    CalculateInLinear(X,U,Y,N,M,ans);
    end = chrono::system_clock::now();
    elapsed = chrono::duration_cast<chrono::milliseconds>(end-start).count();
    #ifdef PLOT
        cout << elapsed/1000 << "\n";
    #else
        cout << "duration = " << elapsed/1000 << "sec.\n";
    #endif
}