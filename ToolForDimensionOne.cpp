#define Coefficient_Number 30

class Multipole{
public:
    double Center;
    double SectionSize;
    double Coefficient[Coefficient_Number];
    Multipole(){}
    Multipole(double center,double size){
        Center = center;
        SectionSize = size;
        for(int i=0;i<Coefficient_Number;i++){
            Coefficient[i] = 0;
        }
    }
    double Calculation(double y){
        double di = SectionSize/(y-Center);
        double t = 1/(y-Center);
        double ans = 0;
        for(int i=0;i<Coefficient_Number;i++){
            ans += Coefficient[i]*t;
            t *= di;
        }
        return ans;
    }
    void Add(double x,double u){
        double t = u;
        double d = (x-Center)/SectionSize;
        for(int i=0;i<Coefficient_Number;i++){
            Coefficient[i] += t;
            t *= d;
        }
    }
    void Add(Multipole M,double *A){
        double t = 1;
        double d = (M.Center-Center)/SectionSize;
        double md = M.SectionSize/(M.Center-Center);
        for(int i=0;i<Coefficient_Number;i++){
            double ti = t;
            for(int j=0;j<=i;j++){
                Coefficient[i] += M.Coefficient[j]*A[i*2*Coefficient_Number+j]*ti;
                ti *= md;
            }
            t *= d;
        }
    }
};
class LocalExpansion{
public:
    double Center;
    double SectionSize;
    double Coefficient[Coefficient_Number];
    LocalExpansion(){}
    LocalExpansion(double center,double size){
        Center = center;
        SectionSize = size;
        for(int i=0;i<Coefficient_Number;i++){
            Coefficient[i] = 0;
        }
    }
    double Calculation(double y){
        double t = 1;
        double ans = 0;
        double d = (y-Center)/SectionSize;
        for(int i=0;i<Coefficient_Number;i++){
            ans += Coefficient[i]*t;
            t *= d;
        }
        return ans;
    }
    void Add(double x,double u){
        double di = SectionSize/(x-Center);
        double t = -u/(x-Center);
        for(int i=0;i<Coefficient_Number;i++){
            Coefficient[i] += t;
            t *= di;
        }
    }
    void Add(LocalExpansion L,double *A){
        double t = 1;
        double d = SectionSize/L.SectionSize;
        double ld = (Center-L.Center)/L.SectionSize;
        for(int i=0;i<Coefficient_Number;i++){
            double ti = t;
            for(int j=i;j<Coefficient_Number;j++){
                Coefficient[i] += L.Coefficient[j]*A[j*2*Coefficient_Number+i]*ti;
                ti *= ld;
            }
            t *= d;
        }
    }
    void Add(Multipole M,double *A){
        double d = SectionSize/(M.Center-Center);
        double md = -M.SectionSize/(M.Center-Center);
        double t = -1/(M.Center-Center);
        for(int i=0;i<Coefficient_Number;i++){
            double ti = t;
            for(int j=0;j<Coefficient_Number;j++){
                Coefficient[i] += M.Coefficient[j]*A[(i+j)*2*Coefficient_Number+j]*ti;
                ti *= md;
            }
            t *= d;
        }
    }
};