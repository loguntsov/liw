//---------------------------------------------------------------------------

#ifndef DiskSystemH
#define DiskSystemH

class DiskStream
{
private:
    TStream *S;
public:
    DiskStream(TStream *Stream);
    // Методы записис в поток
    void Write(long x);
    void Write(int x);
    void Write(double x);
    void Write(float x);
    void Write(AnsiString x);
    void Write(char * x);
    void Write(char x);
    // Методы чтения из потока
    long ReadLong(void);
    int ReadInt(void);
    double ReadDouble(void);
    float ReadFloat(void);
    AnsiString ReadAnsiString(void);
    void ReadString(char *Buf,int SizeBuf);
    char ReadChar(void);
};
//---------------------------------------------------------------------------
#endif
