//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MathMethod.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//
// LinIntr
//
double GetYPoint(double x,double y,double x0,double y0,double x1);
LinIntr::LinIntr(double *x,double *y,int n)
{
    N=n;
    X=x;
    Y=y;
}
double LinIntr::GetY(double x)
{
    if (x<X[0])
    {
        return GetYPoint(X[0],Y[0],X[1],Y[1],x);
    }
    if (x>X[N-1])
    {
        return GetYPoint(X[N-1],Y[N-1],X[N-2],Y[N-2],x);
    }
    for(int i=1;i<N;i++)
    {
        if (X[i]>=x)
        {
            return GetYPoint(X[i],Y[i],X[i-1],Y[i-1],x);
        }
    }
    throw("jsdhkajsdh");
    Abort();
    return 0;
}
double GetYPoint(double x,double y,double x0,double y0,double x1)
{
    double k=(y-y0)/(x-x0);
    double b=y-k*x;
    return x1*k+b;
}
double LinIntr::GetX(double y)
{
    double *C=X;
    X=Y;Y=C;
    double x=GetY(y);
    C=X;X=Y;Y=C;
    return x;
}

