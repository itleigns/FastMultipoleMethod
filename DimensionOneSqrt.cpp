#include <vector>
#include <cmath>
#include "ToolForDimensionOne.cpp"
using namespace std;
namespace DimensionOneSqrt{
    class Section{
        Multipole mult;
        vector<double> X;
        vector<double> U;
    public:
        Section(double center,double size)
            : mult(center,size){}
        void Add(double x,double u){
            mult.Add(x,u);
            X.push_back(x);
            U.push_back(u);
        }
        double CalcNormal(double y){
            double ans = 0;
            for(int i=0;i<X.size();i++){
                ans += U[i]/(y-X[i]);
            }
            return ans;
        }
        double CalcFast(double y){
            return mult.Calculation(y);
        }
    };
    void Calculate(double *X,double *U,double *Y,int N,int M,double *ans){
        int Block = max((int)(sqrt(3*N/Coefficient_Number)),1);
        vector<Section> Sec;
        double BlockSize = 1.0/Block;
        for(int i=0;i<Block;i++){
            Sec.push_back(Section((i+0.5)/Block,BlockSize));
        }
        for(int i=0;i<N;i++){
            int p = (int)(X[i]*Block);
            Sec[p].Add(X[i],U[i]);
        }
        for(int i=0;i<M;i++){
            int p = (int)(Y[i]*Block);
            for(int j=0;j<Block;j++){
                if(p-1 <= j && j <= p+1){
                    ans[i] += Sec[j].CalcNormal(Y[i]);
                }
                else{
                    ans[i] += Sec[j].CalcFast(Y[i]);
                }
            }
        }
    }
}
void CalculateInSqrt(double *X,double *U,double *Y,int N,int M,double *ans){
    DimensionOneSqrt::Calculate(X,U,Y,N,M,ans);
}