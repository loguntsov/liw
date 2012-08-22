//---------------------------------------------------------------------------

#ifndef TrubyLiwH
#define TrubyLiwH
extern double Hmin; // Минимальное заглубление
extern double Hmax; // Максимальное заглубление
extern double H0max; // Максимальное заглубление для насосной станции
extern double hPer; // Максимальная глубина перепадного колодца
extern double Md; // Максимальное суточное количество осадков по СНиП 2.01.01-82
extern double MinDim; // Минимальный диаметр в сети  
extern double Tk; // Время поверхностной концентрации
extern double Tl; // Время пробега по лотку
extern double N; // Климатич коэф.
class CMaterial
{
    public:
    CMaterial(
        char *NamE, // наименование материала
        char *Gost, // гост на материал
        double N, // коэффициент шероховатости
        double VMAX // Максимальная скорость для данного материала
        );
    AnsiString Name; // Название материала;
// Характеристики материала
    double n; // Коэффициент шероховатости
    double Vmax; // Максимальная скорость
    AnsiString GOST;
};
class CDiametr
{
public:
    CDiametr(int Usl,double Fakt);
    CDiametr();
    int UslDiametr; // Условный диаметр.
    double FaktDiametr; // Фактический диаметр.
    double GetMaxNapoln(void); // Возвращает максимальное наполнение для данного диаметра
    double GetVtoNap100(double Q); // Возвращает скорость идеальной жидкости при 100% наполнении
};
class CSortament
{
private:
    double GetAlfa(void); // Возвращает угол
    double GetR(void); // Возвращает гидравлический радиус
public:
    CSortament(CDiametr Diam,CMaterial *Mat);
    CDiametr Diametr;
    CMaterial *Material;
    double GetVmin(void); // Возвращает минимальную скорость для данного сортамента
    double GetQmin(void); // Возвращает минимальный расход
    double Geti1000min(void); // Возвращает минимальный уклон
    double Geti1000(double Q); // Возвращает уклон трубы для данного диаметра при расходе Q и максимальном наполнении
    double GetW(void); // Возвращает площадь живого сечения трубы    
};
class CSortamentItem
{
public:
    AnsiString Name;
    CSortament **Sortament;
    CSortamentItem(AnsiString Name,CSortament **Sortament);
    int GetNumSortament(double Diam); // Возвращает номер наиболее близкого сортамента к диаметру Diam
};

class CTruba;
struct TrubaInform // Структура для инициализации класса CTruba
{
        CSortamentItem *SortamentItem; // Ссылка на сортамент труб
        double Len; // Длина трубы
        double ZBeg; // Начальная отметка земли
        double ZEnd; // Конечная отметка земли
        double HLBeg; // Минимальное начальное заглубление лотка трубы в начале
        double Q; // Средний расход на данном участке.
        double Qdop; // Дополнительный постоянный расход .
        double VVH; // Скорость входа жидкости в трубу.
        double Time; // Время прохождения воды с предыдущих участков
        double Qmax; // Максимальный расход с предыдущих участков
        CTruba *TROFHIL; // Труба примыкающая к началу данной с минимальной отметкой шелыги
        CTruba *TROFLOT; // Труба примыкающая к началу данной с минимальной отметкой лотка
        int NSegment; // Номер сегмента, для отладки
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
    bool IsDiametrGood(void); // Возвращает true если текущий диаметр удовлетворяет условиям выбора диаметров
    // выбирая при этом начальное заглубление лотка трубы (выравнивание по лотку или шелыги)
    CPerepadWells * PerepadWells;
    bool FindDiametrAndi1000( // ищет подходящий уклон для текущего диаметра трубы, результаты записывает в NSortament и i1000
        double Hmin, // Минимальное заглубление
        double Hmax, // Максимальное заглубление
        bool f // если true - то ищем по минимальному заглублению, иначе по максимальному);
        );// возвращает true если все хорошо
public:
    CTruba(TrubaInform Information);
    ~CTruba();
    __property CSortament * Sortament={read=GetSortament}; // Сортамент (диаметр и материал) трубы
    __property double HEnd={read=GetHEnd,write=SetHEnd}; // Заглубление шелыги трубы в конце
    __property double V={read=GetV}; // Скорость в трубе.
    __property double ZLBeg={read=GetZLBeg}; // Отметка лотка в начале
    __property double ZLEnd={read=GetZLEnd}; // Отметка лотка в конце
    __property double ZHBeg={read=GetZHBeg}; // Отметка шилыги в начале
    __property double ZHEnd={read=GetZHEnd}; // Отметка шилыги в конце
    __property double i1000={read=Geti1000,write=Seti1000}; // Уклон под которым уложена труба.
    __property double HHEnd={read=GetHHEnd}; // Заглубление шелыги
    __property double Len={read=GetLen};// Длина участка
    __property double ZBeg={read=GetZBeg}; // Отметка зкмли в начале
    __property double ZEnd={read=GetZEnd}; // Отметка земли в конце
    __property double HBeg={read=GetHBeg,write=SetHBeg}; // Заглубление трубы в начале
    int NSortament;
    TrubaInform Info;
    double hd; // Наполнение трубы
    double Q;
    double Time;
    double DH; // Приращение конечного заглубления для учета насосной станции и перепадных колодцев
     // DH>0 - насосная станция
     // DH=0 - обычный участок
     // DH<0 - перепадные колодцы
    double Qliv; // Дополнительный инфильтрационный расход с предыдущих участков + на текущем
    void ToMaxSortament(void); // Вычисление диаметра трубы, без учета рельефа
    void ToNapolnenie(void); // Расчет наполнения трубы, при заданных параметрах.
    void ToGetSortament(void); // Вычисление диаметра трубы с учетом рельефа.
    double GetVmin(void);
    bool Rash; // Признак не расчетного участка
    void CreateReport(TStrings *Strings); // Создание отчета по трубе
    void SetPumpStation(double H); // Установка насной станции подкачки с высотой поднятия до H м
    void SetWells(double H); // Установка перепадных колодцев с падением заглубления по лотку до H м
    void SetNapWodowod(void); // Установка напорных водоводов.
    int GetNumSortamentFrom(double Diam); // Возвращает число сортаментов находящихся между диаметром данной трубы и Diam (фактический диаметр,мм)
    double GetDiametr(void); // Возвращает диаметр в метрах
    double Geti1000mest(void); // Возвращает уклон местности
    double GetNapolnenieToQPlusQliv(void);
    bool GS; // Применение гасител скорости.
    double Geti1000ToHmin(void); // Возвращает уклон трубы, чтобы она вышла на минимальное заглубление
    double Geti1000ToHmax(void); // Возвращвет уклон трубы, чтобы она вышла на максимальное заглубление
    double Geti1000ToHminimum(void); // Возвращает минимальное заглубление с учетом наличия перепадного колодца    
    double GetZmest(double Len); // Возвращает отметку земли на расстоянии Len от начала участка
    double GetQmax();// Возвращает максимальный расход, которвй может пропустить труба при данном диаметре (NSortament) и уклоне (i1000).
    AnsiString CreateLineTable(void); // Создание отчета в виде строки таблицы
    void CreateSpecialReport(TStrings *Str); // Создание отчета об инженерных конструкциях на трубе
    AnsiString CreateLineTableSmall(void); // Создание отчета об параметрах трубопровода без отметок
    AnsiString CreateOtm(void); // Создание строки таблицы отметок
    void CreateOtmSoor(TStrings *Str); // Создание отметок земли технических сооружений
    double GetQfromHD(double hd); // Возвращает расход при наполнении HD.
};

//---------------------------------------------------------------------------

// Допустимые материалы труб.

extern CMaterial MAsbest1;//("асбестоцементные безнапорные","ГОСТ 1839");
extern CMaterial MAsbest2;//("асбестоцементные напорные","ГОСТ 539");
extern CMaterial MKeramika;//("керамические","ГОСТ 286");
extern CMaterial MBeton;//("железобетонные безнапорные","ГОСТ 6482");
extern CMaterial MStal; // ("стальные электросварные","ГОСТ 8696",0.012,8);
extern CMaterial MChug;// ("чугунные","ГОСТ 9583",0.012,10);
// Список всех сортаментов

extern CSortamentItem *SortamentName[];

// Допустимые сортаменты труб

extern CSortament *SAsbest[]; // Асбестоцементные трубы
extern CSortament *SKeramika[]; // Керамические трубы
extern CSortament *SBeton[]; // Железобетонные трубы
extern CSortament *SKeramikaBeton[]; // Керамика + Бетон
extern CSortament *SStal[]; // Стальные электросварные

// Перепадной колодец.

class CPerepadWells
{
private:
    CTruba *Truba;
public:
    PerepadWells(CTruba *TRUBA);
};

// Данные о максимальном колличестве осадков на территории России

extern AnsiString NameMest[];
extern double MD[];


// Функции

extern double MaxNapoln(
    double Diam // Условный диаметр трубы
); // Возвращает наполнение для конкретного диаметра трубы.
extern double sqr(double X); // Возвращает x^2
extern CSortamentItem * GetSortamentItem(
    CSortamentItem *SortArray[], // Указатель на массив сортаментов
    CSortament *Sortament[] // Указатель на нужный сортамент
    );
// Возвращает указатель на список сортаментов
//extern AnsiString Fmt(double X); // Форматирует X как "  00.00"

#endif   
