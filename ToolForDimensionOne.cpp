#define Coefficient_Number 30

class Multipole{
public:
    double Center;
    double Coefficient[Coefficient_Number];
    Multipole(){}
    Multipole(double center){
        Center = center;
        for(int i=0;i<Coefficient_Number;i++){
            Coefficient[i] = 0;
        }
    }
    double Calculation(double y){
        double t = 1/(y-Center);
        double ans = 0;
        for(int i=0;i<Coefficient_Number;i++){
            ans += Coefficient[i]*t;
            t /= (y-Center);
        }
        return ans;
    }
    void Add(double x,double u){
        double t = u;
        for(int i=0;i<Coefficient_Number;i++){
            Coefficient[i] += t;
            t *= x-Center;
        }
    }
    void Add(Multipole M,double *A){
        for(int i=0;i<Coefficient_Number;i++){
            double t = 1;
            for(int j=i;j>=0;j--){
                Coefficient[i] += M.Coefficient[j]*A[i*2*Coefficient_Number+j]*t;
                t *= (M.Center-Center);
            }
        }
    }
};
class LocalExpansion{
public:
    double Center;
    double Coefficient[Coefficient_Number];
    LocalExpansion(){}
    LocalExpansion(double center){
        Center = center;
        for(int i=0;i<Coefficient_Number;i++){
            Coefficient[i] = 0;
        }
    }
    double Calculation(double y){
        double t = 1;
        double ans = 0;
        for(int i=0;i<Coefficient_Number;i++){
            ans += Coefficient[i]*t;
            t *= (y-Center);
        }
        return ans;
    }
    void Add(double x,double u){
        double t = -u/(x-Center);
        for(int i=0;i<Coefficient_Number;i++){
            Coefficient[i] += t;
            t /= (x-Center);
        }
    }
    void Add(LocalExpansion L,double *A){
        for(int i=0;i<Coefficient_Number;i++){
            double t = 1;
            for(int j=i;j<Coefficient_Number;j++){
                Coefficient[i] += L.Coefficient[j]*A[j*2*Coefficient_Number+i]*t;
                t *= (Center-L.Center);
            }
        }
    }
    void Add(Multipole M,double *A){
        double t1 = -1/(M.Center-Center);
        for(int i=0;i<Coefficient_Number;i++){
            double t2 = t1;
            for(int j=0;j<Coefficient_Number;j++){
                Coefficient[i] += M.Coefficient[j]*A[(i+j)*2*Coefficient_Number+j]*t2;
                t2 /= -1*(M.Center-Center);
            }
            t1 /= (M.Center-Center);
        }
    }
};