//---------------------------------------------------------------------------

#ifndef LiwH
#define LiwH

#include "TrubyLiw.h"

class CGeoPoint;
struct GeoSegmentInform // ��������� ������������� CGeoSegment
{
    CGeoPoint *PBeg; // ��������� �� ����� ������ �������
    CGeoPoint *PEnd; // ��������� �� ����� ����� �������
    double Len; // ����� �������
    double HBeg; // ��������� ����������� �����
    CSortamentItem *SortamentItem; // ������ ��������� �����������
    double Q; // �������������� ������ � ���������������
    AnsiString Name; // �������� �������
    int NSegment; // ����� �������
};
class CGeoSegment
{
    private:
        GeoSegmentInform Info;
        CGeoPoint * GetPBeg(void);
        CGeoPoint * GetPEnd(void);
    public:
        CGeoSegment(GeoSegmentInform Information);
        ~CGeoSegment();
        CTruba *Truba;
        void Calculation(void); // ���������� ������������� �������
        bool IsCalculated(void); // ���������� true ���� ������� ��� ��������.
        void CreateReport(TStrings *Strings); // �������� ������ �� �������.
        AnsiString CreateLineTable(void);
        void CreateSpecialReport(TStrings *Strings); // �������� ������ �� ���������� ������������ �� �������
        AnsiString CreateLineTableSmall(void);
        void CreateReportOtm(TStrings *Str); // �������� ������ ������� �� �������
        __property  CGeoPoint *PBeg={read=GetPBeg};
        __property  CGeoPoint *PEnd={read=GetPEnd};
};
class CGeoPoint
{
private:
    TList *SegmentBefore; // ������ ���� ��������� � ������ �����
public:
    CGeoPoint(
        double Z, // ������������� ������ �����
        double Q0 // ��������������� ������ �3/�
        );
    ~CGeoPoint();
    void AddBefore(CGeoSegment *Seg);
    void DeleteBefore(CGeoSegment *Seg);
    double z; // �������������� ������ �����
    double q; // ������ ���������� ����� ������ �����
    //double qliv; // �������� ������ ���������� ����� ������ �����.
    double Time; // ����� ���������� ����� ������ �����, ����������� �� ����� Calculation. 
    double q0;
    double qmax; // ������������ ������ � �������� ����������� � ������ ����� ��. Calculation
    double v; // ������������ �������� ������� �������� ���������� � �����
    double h; // ������������ ����������� ����, ���������� � �����.
    void Calculation(void); // ������ ���������� �������� � ���������� ������ � Q � V;
    CGeoSegment * Items(int i);
    int CountBefore(void);
    bool TheEndPoint;
    CTruba * GetTrubaOfMinHil(void); // ���������� ����� � ����������� �������� ������
    CTruba * GetTrubaOfMinLot(void); // ���������� ����� � ����������� �������� �����
};

extern double GetKnerawn(double q); // ���������� ����� ����������� ��������������� ��� ������� �������
//---------------------------------------------------------------------------
#endif
