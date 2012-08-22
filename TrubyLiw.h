//---------------------------------------------------------------------------

#ifndef TrubyLiwH
#define TrubyLiwH
extern double Hmin; // ����������� �����������
extern double Hmax; // ������������ �����������
extern double H0max; // ������������ ����������� ��� �������� �������
extern double hPer; // ������������ ������� ����������� �������
extern double Md; // ������������ �������� ���������� ������� �� ���� 2.01.01-82
extern double MinDim; // ����������� ������� � ����  
extern double Tk; // ����� ������������� ������������
extern double Tl; // ����� ������� �� �����
extern double N; // �������� ����.
class CMaterial
{
    public:
    CMaterial(
        char *NamE, // ������������ ���������
        char *Gost, // ���� �� ��������
        double N, // ����������� �������������
        double VMAX // ������������ �������� ��� ������� ���������
        );
    AnsiString Name; // �������� ���������;
// �������������� ���������
    double n; // ����������� �������������
    double Vmax; // ������������ ��������
    AnsiString GOST;
};
class CDiametr
{
public:
    CDiametr(int Usl,double Fakt);
    CDiametr();
    int UslDiametr; // �������� �������.
    double FaktDiametr; // ����������� �������.
    double GetMaxNapoln(void); // ���������� ������������ ���������� ��� ������� ��������
    double GetVtoNap100(double Q); // ���������� �������� ��������� �������� ��� 100% ����������
};
class CSortament
{
private:
    double GetAlfa(void); // ���������� ����
    double GetR(void); // ���������� �������������� ������
public:
    CSortament(CDiametr Diam,CMaterial *Mat);
    CDiametr Diametr;
    CMaterial *Material;
    double GetVmin(void); // ���������� ����������� �������� ��� ������� ����������
    double GetQmin(void); // ���������� ����������� ������
    double Geti1000min(void); // ���������� ����������� �����
    double Geti1000(double Q); // ���������� ����� ����� ��� ������� �������� ��� ������� Q � ������������ ����������
    double GetW(void); // ���������� ������� ������ ������� �����    
};
class CSortamentItem
{
public:
    AnsiString Name;
    CSortament **Sortament;
    CSortamentItem(AnsiString Name,CSortament **Sortament);
    int GetNumSortament(double Diam); // ���������� ����� �������� �������� ���������� � �������� Diam
};

class CTruba;
struct TrubaInform // ��������� ��� ������������� ������ CTruba
{
        CSortamentItem *SortamentItem; // ������ �� ��������� ����
        double Len; // ����� �����
        double ZBeg; // ��������� ������� �����
        double ZEnd; // �������� ������� �����
        double HLBeg; // ����������� ��������� ����������� ����� ����� � ������
        double Q; // ������� ������ �� ������ �������.
        double Qdop; // �������������� ���������� ������ .
        double VVH; // �������� ����� �������� � �����.
        double Time; // ����� ����������� ���� � ���������� ��������
        double Qmax; // ������������ ������ � ���������� ��������
        CTruba *TROFHIL; // ����� ����������� � ������ ������ � ����������� �������� ������
        CTruba *TROFLOT; // ����� ����������� � ������ ������ � ����������� �������� �����
        int NSegment; // ����� ��������, ��� �������
};
class CPerepadWells;
class CTruba
{
private:
    CSortament * GetSortament(void);
    double func(double hd);
    double GetHEnd(void);
    void SetHEnd(double HEND);
    double GetW(void);
    double GetW(double hd);
    double GetV(void);
    double GetZLBeg(void);
    double GetZLEnd(void);
    double GetZHBeg(void);
    double GetZHEnd(void);
    double GetLen(void);
    double GetZBeg(void);
    double GetZEnd(void);
    double GetHBeg(void);
    void SetHBeg(double X);
    double GetBeta(void);
    double fi1000;
    double fHBeg;
    double Geti1000(void);
    double Vvh;
    void Seti1000(double i1000);
    double GetHHEnd(void);
    //double HLBegMin;
    bool IsDiametrGood(void); // ���������� true ���� ������� ������� ������������� �������� ������ ���������
    // ������� ��� ���� ��������� ����������� ����� ����� (������������ �� ����� ��� ������)
    CPerepadWells * PerepadWells;
    bool FindDiametrAndi1000( // ���� ���������� ����� ��� �������� �������� �����, ���������� ���������� � NSortament � i1000
        double Hmin, // ����������� �����������
        double Hmax, // ������������ �����������
        bool f // ���� true - �� ���� �� ������������ �����������, ����� �� �������������);
        );// ���������� true ���� ��� ������
public:
    CTruba(TrubaInform Information);
    ~CTruba();
    __property CSortament * Sortament={read=GetSortament}; // ��������� (������� � ��������) �����
    __property double HEnd={read=GetHEnd,write=SetHEnd}; // ����������� ������ ����� � �����
    __property double V={read=GetV}; // �������� � �����.
    __property double ZLBeg={read=GetZLBeg}; // ������� ����� � ������
    __property double ZLEnd={read=GetZLEnd}; // ������� ����� � �����
    __property double ZHBeg={read=GetZHBeg}; // ������� ������ � ������
    __property double ZHEnd={read=GetZHEnd}; // ������� ������ � �����
    __property double i1000={read=Geti1000,write=Seti1000}; // ����� ��� ������� ������� �����.
    __property double HHEnd={read=GetHHEnd}; // ����������� ������
    __property double Len={read=GetLen};// ����� �������
    __property double ZBeg={read=GetZBeg}; // ������� ����� � ������
    __property double ZEnd={read=GetZEnd}; // ������� ����� � �����
    __property double HBeg={read=GetHBeg,write=SetHBeg}; // ����������� ����� � ������
    int NSortament;
    TrubaInform Info;
    double hd; // ���������� �����
    double Q;
    double Time;
    double DH; // ���������� ��������� ����������� ��� ����� �������� ������� � ���������� ��������
     // DH>0 - �������� �������
     // DH=0 - ������� �������
     // DH<0 - ���������� �������
    double Qliv; // �������������� ���������������� ������ � ���������� �������� + �� �������
    void ToMaxSortament(void); // ���������� �������� �����, ��� ����� �������
    void ToNapolnenie(void); // ������ ���������� �����, ��� �������� ����������.
    void ToGetSortament(void); // ���������� �������� ����� � ������ �������.
    double GetVmin(void);
    bool Rash; // ������� �� ���������� �������
    void CreateReport(TStrings *Strings); // �������� ������ �� �����
    void SetPumpStation(double H); // ��������� ������ ������� �������� � ������� �������� �� H �
    void SetWells(double H); // ��������� ���������� �������� � �������� ����������� �� ����� �� H �
    void SetNapWodowod(void); // ��������� �������� ���������.
    int GetNumSortamentFrom(double Diam); // ���������� ����� ����������� ����������� ����� ��������� ������ ����� � Diam (����������� �������,��)
    double GetDiametr(void); // ���������� ������� � ������
    double Geti1000mest(void); // ���������� ����� ���������
    double GetNapolnenieToQPlusQliv(void);
    bool GS; // ���������� ������� ��������.
    double Geti1000ToHmin(void); // ���������� ����� �����, ����� ��� ����� �� ����������� �����������
    double Geti1000ToHmax(void); // ���������� ����� �����, ����� ��� ����� �� ������������ �����������
    double Geti1000ToHminimum(void); // ���������� ����������� ����������� � ������ ������� ����������� �������    
    double GetZmest(double Len); // ���������� ������� ����� �� ���������� Len �� ������ �������
    double GetQmax();// ���������� ������������ ������, ������� ����� ���������� ����� ��� ������ �������� (NSortament) � ������ (i1000).
    AnsiString CreateLineTable(void); // �������� ������ � ���� ������ �������
    void CreateSpecialReport(TStrings *Str); // �������� ������ �� ���������� ������������ �� �����
    AnsiString CreateLineTableSmall(void); // �������� ������ �� ���������� ������������ ��� �������
    AnsiString CreateOtm(void); // �������� ������ ������� �������
    void CreateOtmSoor(TStrings *Str); // �������� ������� ����� ����������� ����������
    double GetQfromHD(double hd); // ���������� ������ ��� ���������� HD.
};

//---------------------------------------------------------------------------

// ���������� ��������� ����.

extern CMaterial MAsbest1;//("���������������� �����������","���� 1839");
extern CMaterial MAsbest2;//("���������������� ��������","���� 539");
extern CMaterial MKeramika;//("������������","���� 286");
extern CMaterial MBeton;//("�������������� �����������","���� 6482");
extern CMaterial MStal; // ("�������� ��������������","���� 8696",0.012,8);
extern CMaterial MChug;// ("��������","���� 9583",0.012,10);
// ������ ���� �����������

extern CSortamentItem *SortamentName[];

// ���������� ���������� ����

extern CSortament *SAsbest[]; // ���������������� �����
extern CSortament *SKeramika[]; // ������������ �����
extern CSortament *SBeton[]; // �������������� �����
extern CSortament *SKeramikaBeton[]; // �������� + �����
extern CSortament *SStal[]; // �������� ��������������

// ���������� �������.

class CPerepadWells
{
private:
    CTruba *Truba;
public:
    PerepadWells(CTruba *TRUBA);
};

// ������ � ������������ ����������� ������� �� ���������� ������

extern AnsiString NameMest[];
extern double MD[];


// �������

extern double MaxNapoln(
    double Diam // �������� ������� �����
); // ���������� ���������� ��� ����������� �������� �����.
extern double sqr(double X); // ���������� x^2
extern CSortamentItem * GetSortamentItem(
    CSortamentItem *SortArray[], // ��������� �� ������ �����������
    CSortament *Sortament[] // ��������� �� ������ ���������
    );
// ���������� ��������� �� ������ �����������
//extern AnsiString Fmt(double X); // ����������� X ��� "  00.00"

#endif   
