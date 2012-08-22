//---------------------------------------------------------------------------

#ifndef LiwH
#define LiwH

#include "TrubyLiw.h"

class CGeoPoint;
struct GeoSegmentInform // Структыра инициализации CGeoSegment
{
    CGeoPoint *PBeg; // Указатель на точку начала участка
    CGeoPoint *PEnd; // Указатель на точку конца участка
    double Len; // Длина участка
    double HBeg; // Начальное заглубление трубы
    CSortamentItem *SortamentItem; // Список возможных сортаментов
    double Q; // Дополнительный расход с дождеприемников
    AnsiString Name; // Название участка
    int NSegment; // Номер участка
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
        void Calculation(void); // Вычисление характеристик участка
        bool IsCalculated(void); // Возвращает true если участок был расчитан.
        void CreateReport(TStrings *Strings); // Создание отчета по участку.
        AnsiString CreateLineTable(void);
        void CreateSpecialReport(TStrings *Strings); // Создание отчета об инженерных конструкциях на участке
        AnsiString CreateLineTableSmall(void);
        void CreateReportOtm(TStrings *Str); // Создание отчета отметок об участке
        __property  CGeoPoint *PBeg={read=GetPBeg};
        __property  CGeoPoint *PEnd={read=GetPEnd};
};
class CGeoPoint
{
private:
    TList *SegmentBefore; // Список труб втекающих в данную точку
public:
    CGeoPoint(
        double Z, // Геометричекая высота точки
        double Q0 // Сосредоточенный расход м3/ч
        );
    ~CGeoPoint();
    void AddBefore(CGeoSegment *Seg);
    void DeleteBefore(CGeoSegment *Seg);
    double z; // Геометрическая высота точки
    double q; // Расход проходящий через данную точку
    //double qliv; // Ливневой расход проходящий через данную точку.
    double Time; // Время проходящее через данную точку, вычисляется во время Calculation. 
    double q0;
    double qmax; // Максимальный расход с участков примыкающих к данной точке см. Calculation
    double v; // Максимальная скорость течения жидкости приходящей в точку
    double h; // Максимальное заглубление труб, приходящих в точку.
    void Calculation(void); // Расчет предыдущих участков и подведение итогов в Q и V;
    CGeoSegment * Items(int i);
    int CountBefore(void);
    bool TheEndPoint;
    CTruba * GetTrubaOfMinHil(void); // Возвращает трубу с минимальной отметкой шелыги
    CTruba * GetTrubaOfMinLot(void); // Возвращает трубу с минимальной отметкой лотка
};

extern double GetKnerawn(double q); // Возвращает общий коэффициент неравномерности для данного расхода
//---------------------------------------------------------------------------
#endif
