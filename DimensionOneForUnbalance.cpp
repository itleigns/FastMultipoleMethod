#include <vector>
#include <cmath>
#include "ToolForDimensionOne.cpp"
#define OneSectionMax 30

using namespace std;
namespace DimensionOneForUnbalance{
    class Section{
    public:
        vector<double> X;
        vector<double> U;
        vector<double> Y;
        vector<int> O;
        Multipole mult;
        LocalExpansion loc;
        Section* left;
        Section* right;
        Section* parent;
        int depthplace;
        int Depth;
        long long Place;
        double Length;
        double Center;
        Section(){}
        Section(double center,double length,int depth,Section* pare,long long place)
            : mult(center,length),loc(center,length),Center(center),Length(length),Depth(depth),
            left(nullptr),right(nullptr),parent(pare),Place(place){}
        void Add(double x,double u){
            X.push_back(x);
            U.push_back(u);
        }
        void AddQuerry(double y,int o){
            Y.push_back(y);
            O.push_back(o);
        }
        void Divide(vector<Section*>& child,vector<vector<Section*> >& sectionbydepth){
            if(Depth == sectionbydepth.size()){
                vector<Section*> newsec;
                sectionbydepth.push_back(newsec);
            }
            if(X.size()+Y.size() >= OneSectionMax){
                left = new Section(Center-Length/4,Length/2,Depth+1,this,Place*2);
                right = new Section(Center+Length/4,Length/2,Depth+1,this,Place*2+1);
                for(int i=0;i<X.size();i++){
                    if(X[i] < Center){
                        left->Add(X[i],U[i]);
                    }
                    else{
                        right->Add(X[i],U[i]);
                    }
                }
                for(int i=0;i<Y.size();i++){
                    if(Y[i] < Center){
                        left->AddQuerry(Y[i],O[i]);
                    }
                    else{
                        right->AddQuerry(Y[i],O[i]);
                    }
                }
                left->Divide(child,sectionbydepth);
                right->Divide(child,sectionbydepth);
                depthplace = sectionbydepth[Depth].size();
                sectionbydepth[Depth].push_back(this);
            }
            else{
                depthplace = sectionbydepth[Depth].size();
                sectionbydepth[Depth].push_back(this);
                child.push_back(this);
            }
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
        vector<Section*> child;
        vector<vector<Section*> > sectionbydepth;
        Section Top(0.5,1,0,NULL,0);
        for(int i=0;i<N;i++){
            Top.Add(X[i],U[i]);
        }
        for(int i=0;i<M;i++){
            Top.AddQuerry(Y[i],i);
        }
        Top.Divide(child,sectionbydepth);
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
        for(int i=1;i<child.size()-1;i++){
            for(int j=0;j<child[i]->O.size();j++){
                ans[child[i]->O[j]] += child[i]->CalcNormal(child[i]->Y[j]);
                ans[child[i]->O[j]] += child[i-1]->CalcNormal(child[i]->Y[j]);
                ans[child[i]->O[j]] += child[i+1]->CalcNormal(child[i]->Y[j]);
            }
        }
        if(child.size() != 1){
            for(int j=0;j<child[0]->O.size();j++){
                ans[child[0]->O[j]] += child[0]->CalcNormal(child[0]->Y[j]);
                ans[child[0]->O[j]] += child[1]->CalcNormal(child[0]->Y[j]);
            }
            for(int j=0;j<child[child.size()-1]->O.size();j++){
                ans[child[child.size()-1]->O[j]] += child[child.size()-1]->CalcNormal(child[child.size()-1]->Y[j]);
                ans[child[child.size()-1]->O[j]] += child[child.size()-2]->CalcNormal(child[child.size()-1]->Y[j]);
            }
        }
        else{
            for(int j=0;j<child[0]->O.size();j++){
                ans[child[0]->O[j]] += child[0]->CalcNormal(child[0]->Y[j]);
            }
        }
        for(int i=0;i<child.size();i++){
            for(int j=0;j<child[i]->X.size();j++){
                child[i]->mult.Add(child[i]->X[j],child[i]->U[j]);
            }
        }
        for(int i=sectionbydepth.size()-1;i>0;i--){
            for(int j=0;j<sectionbydepth[i].size();j++){
                sectionbydepth[i][j]->parent->mult.Add(sectionbydepth[i][j]->mult,Conv);
            }
        }
        for(int i=sectionbydepth.size()-2;i>0;i--){
            for(int j=0;j<sectionbydepth[i].size()-1;j++){
                if(sectionbydepth[i][j]->Place+1 == sectionbydepth[i][j+1]->Place){
                    if(sectionbydepth[i][j]->left != NULL && sectionbydepth[i][j+1]->left != NULL){
                        sectionbydepth[i][j]->left->loc.Add(sectionbydepth[i][j+1]->left->mult,Conv);
                        sectionbydepth[i][j]->left->loc.Add(sectionbydepth[i][j+1]->right->mult,Conv);
                        sectionbydepth[i][j]->right->loc.Add(sectionbydepth[i][j+1]->right->mult,Conv);
                        sectionbydepth[i][j+1]->right->loc.Add(sectionbydepth[i][j]->right->mult,Conv);
                        sectionbydepth[i][j+1]->right->loc.Add(sectionbydepth[i][j]->left->mult,Conv);
                        sectionbydepth[i][j+1]->left->loc.Add(sectionbydepth[i][j]->left->mult,Conv);
                    }
                }
            }
        }
        for(int i=0;i<child.size();i++){
            int d = child[i]->Depth;
            int p = child[i]->depthplace;
            if(p != 0 && sectionbydepth[d][p-1]->Place+1 == sectionbydepth[d][p]->Place){
                Section s = *(sectionbydepth[d][p-1]);
                while(s.left != NULL){
                    for(int j=0;j<child[i]->X.size();j++){
                        s.left->loc.Add(child[i]->X[j],child[i]->U[j]);
                    }
                    for(int j=0;j<child[i]->O.size();j++){
                        ans[child[i]->O[j]] += s.left->mult.Calculation(child[i]->Y[j]);
                    }
                    s = *(s.right);
                }
            }
            if(p != sectionbydepth[d].size()-1 && sectionbydepth[d][p]->Place+1 == sectionbydepth[d][p+1]->Place){
                Section s = *(sectionbydepth[d][p+1]);
                while(s.right != NULL){
                    for(int j=0;j<child[i]->X.size();j++){
                        s.right->loc.Add(child[i]->X[j],child[i]->U[j]);
                    }
                    for(int j=0;j<child[i]->O.size();j++){
                        ans[child[i]->O[j]] += s.right->mult.Calculation(child[i]->Y[j]);
                    }
                    s = *(s.left);
                }
            }
        }
        for(int i=1;i<sectionbydepth.size();i++){
            for(int j=0;j<sectionbydepth[i].size();j++){
                sectionbydepth[i][j]->loc.Add(sectionbydepth[i][j]->parent->loc,Conv);
            }
        }
        for(int i=0;i<child.size();i++){
            for(int j=0;j<child[i]->O.size();j++){
                ans[child[i]->O[j]] += child[i]->CalcFast(child[i]->Y[j]);
            }
        }
    }
}
void CalculateForUnbalance(double *X,double *U,double *Y,int N,int M,double *ans){
    DimensionOneForUnbalance::Calculate(X,U,Y,N,M,ans);
}