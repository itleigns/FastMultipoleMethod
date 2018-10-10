#include <vector>
#include <cmath>
#include "ToolForDimensionOne.cpp"
using namespace std;
namespace DimensionOneLinear{
    class Section{
        vector<double> X;
        vector<double> U;
    public:
        Multipole mult;
        LocalExpansion loc;
        Section(){}
        Section(double center)
            : mult(center),loc(center){}
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
            return loc.Calculation(y);
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
        double Conv[4*Coefficient_Number*Coefficient_Number];
        {
            Conv[0] = 1;
            for(int i=1;i<2*Coefficient_Number;i++){
                Conv[i*2*Coefficient_Number] = 1;
                for(int j=1;j<i;j++){
                    Conv[i*2*Coefficient_Number+j] = Conv[(i-1)*2*Coefficient_Number+j-1]+Conv[(i-1)*2*Coefficient_Number+j];
                }
                Conv[i*2*Coefficient_Number+i] = 1;
            }
        }
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
        }
        for(int i=Block-2;i>=3;i--){
            Sec[i].mult.Add(Sec[i*2+1].mult,Conv);
            Sec[i].mult.Add(Sec[i*2+2].mult,Conv);
        }
        Sec[3].loc.Add(Sec[5].mult,Conv);
        Sec[3].loc.Add(Sec[6].mult,Conv);
        Sec[4].loc.Add(Sec[6].mult,Conv);
        Sec[5].loc.Add(Sec[3].mult,Conv);
        Sec[6].loc.Add(Sec[3].mult,Conv);
        Sec[6].loc.Add(Sec[4].mult,Conv);
        for(int i=7;i<2*Block-1;i++){
            Sec[i].loc.Add(Sec[(i-1)/2].loc,Conv);
            if(i % 2 == 1){
                if((i & (i+1)) != 0){
                    Sec[i].loc.Add(Sec[i-2].mult,Conv);
                }
                if(((i+2) & (i+3)) != 0){
                    Sec[i].loc.Add(Sec[i+2].mult,Conv);
                    Sec[i].loc.Add(Sec[i+3].mult,Conv);
                }
            }
            else{
                if(((i-1) & i) != 0){
                    Sec[i].loc.Add(Sec[i-2].mult,Conv);
                    Sec[i].loc.Add(Sec[i-3].mult,Conv);
                }
                if(((i+1) & (i+2)) != 0){
                    Sec[i].loc.Add(Sec[i+2].mult,Conv);
                }
            }
        }
        for(int i=0;i<M;i++){
            int p = (int)(Y[i]*Block) + Block - 1;
            if((p & (p+1)) != 0){
                ans[i] += Sec[p-1].CalcNormal(Y[i]);
            }
            ans[i] += Sec[p].CalcNormal(Y[i]);
            if(((p+1) & (p+2)) != 0){
                ans[i] += Sec[p+1].CalcNormal(Y[i]);
            }
            ans[i] += Sec[p].CalcFast(Y[i]);
        }
    }
}
void CalculateInLinear(double *X,double *U,double *Y,int N,int M,double *ans){
    DimensionOneLinear::Calculate(X,U,Y,N,M,ans);
}