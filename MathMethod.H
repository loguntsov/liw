//---------------------------------------------------------------------------

#ifndef MathMetodH
#define MathMetodH
// �������� ������������
class LinIntr
{
private:
    int N;
    double *X;
    double *Y;
public:
    LinIntr(double *x,double *y,int n); // x � y - ��������� �� ������ ������
    double GetY(double x); // ���������� �������� y �� ��������� x
    double GetX(double y); // ���������� �������� x �� ��������� y
};

//---------------------------------------------------------------------------
#endif
