#include "ToolForDimensionOne.cpp"
namespace DimensionOneNormal{
    void Calculate(double *X,double *U,double *Y,int N,int M,double *ans){
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                ans[j] += U[i]/(Y[j]-X[i]);
            }
        }
    }
}
void CalculateInSquare(double *X,double *U,double *Y,int N,int M,double *ans){
    DimensionOneNormal::Calculate(X,U,Y,N,M,ans);
}