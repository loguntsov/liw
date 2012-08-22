//---------------------------------------------------------------------------

#ifndef MathMetodH
#define MathMetodH
// Линейная интерполяция
class LinIntr
{
private:
    int N;
    double *X;
    double *Y;
public:
    LinIntr(double *x,double *y,int n); // x и y - указатель на массив данных
    double GetY(double x); // Возвращает значение y по заданному x
    double GetX(double y); // Возвращает значение x по заданному y
};

//---------------------------------------------------------------------------
#endif
