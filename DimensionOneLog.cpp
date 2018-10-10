#include <vector>
#include <cmath>
#include "ToolForDimensionOne.cpp"
using namespace std;
namespace DimensionOneLog{
    class Section{
        Multipole mult;
        vector<double> X;
        vector<double> U;
    public:
        Section(){}
        Section(double center)
            : mult(center){}
        void Add(double x,double u){
            mult.Add(x,u);
            X.push_back(x);
            U.push_back(u);
        }
        void Add2(double x,double u){
            mult.Add(x,u);
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
    int BiggestBit(int N){
        int ans = 1;
        while(ans < N){
            ans *= 2;
        }
        return ans;
    }
    void Calculate(double *X,double *U,double *Y,int N,int M,double *ans){
        int Block = BiggestBit((max(N,M)));
        vector<Section> Sec;
        {
            Sec.push_back(Section());
            Sec.push_back(Section());
            Sec.push_back(Section());
            int b = 4;
            while(b <= Block){
                for(int i=0;i<b;i++){
                    Sec.push_back(Section((i+0.5)/b));
                }
                b *= 2;
            }
        }
        for(int i=0;i<N;i++){
            int p = (int)(X[i]*Block) + Block - 1;
            Sec[p].Add(X[i],U[i]);
            p = (p-1)/2;
            while(p >= 3){
                Sec[p].Add2(X[i],U[i]);
                p = (p-1)/2;
            }
        }
        for(int i=0;i<M;i++){
            int p = (int)(Y[i]*Block) + Block - 1;
            int f = p;
            int t = p;
            if((p & (p+1)) != 0){
                ans[i] += Sec[p-1].CalcNormal(Y[i]);
                f = p-1;
            }
            ans[i] += Sec[p].CalcNormal(Y[i]);
            if(((p+1) & (p+2)) != 0){
                ans[i] += Sec[p+1].CalcNormal(Y[i]);
                t = p+1;
            }
            while(f >= 3){
                if((f ^ (f-1)) == 1){
                    if((f & (f+1)) != 0){
                        ans[i] += Sec[f-1].CalcFast(Y[i]);
                        ans[i] += Sec[f-2].CalcFast(Y[i]);
                        f -= 2;
                    }
                }
                else{
                    ans[i] += Sec[f-1].CalcFast(Y[i]);
                    f--;
                }
                if((t ^ (t-1)) == 1){
                    ans[i] += Sec[t+1].CalcFast(Y[i]);
                    t++;
                }
                else{
                    if(((t+1) & (t+2)) != 0){
                        ans[i] += Sec[t+1].CalcFast(Y[i]);
                        ans[i] += Sec[t+2].CalcFast(Y[i]);
                        t += 2;
                    }
                }
                f = (f-1)/2;
                t = (t-1)/2;
            }
        }
    }
}
void CalculateInLog(double *X,double *U,double *Y,int N,int M,double *ans){
    DimensionOneLog::Calculate(X,U,Y,N,M,ans);
}