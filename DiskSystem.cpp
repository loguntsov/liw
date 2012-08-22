//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DiskSystem.h"
#include "String.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
DiskStream::DiskStream(TStream *Stream)
{
    S=Stream;
}
// Методы записис в поток
void DiskStream::Write(long x)
{
    S->WriteBuffer(&x,sizeof(x));
}
void DiskStream::Write(int x)
{
    S->WriteBuffer(&x,sizeof(x));
}
void DiskStream::Write(double x)
{
    S->WriteBuffer(&x,sizeof(x));
}
void DiskStream::Write(float x)
{
    S->WriteBuffer(&x,sizeof(x));
}
void DiskStream::Write(AnsiString x)
{
    int n=strlen(x.c_str())+1;
    S->WriteBuffer(x.c_str(),n);
}
void DiskStream::Write(char * x)
{
    int n=strlen(x)+1;
    S->WriteBuffer(x,n);
}
void DiskStream::Write(char x)
{
    S->WriteBuffer(&x,sizeof(x));
}
// Методы чтения из потока

long DiskStream::ReadLong(void)
{
    long x;
    S->ReadBuffer(&x,sizeof(x));
    return x;
}
int DiskStream::ReadInt(void)
{
    int x;
    S->ReadBuffer(&x,sizeof(x));
    return x;
}
double DiskStream::ReadDouble(void)
{
    double x;
    S->ReadBuffer(&x,sizeof(x));
    return x;
}
float DiskStream::ReadFloat(void)
{
    float x;
    S->ReadBuffer(&x,sizeof(x));
    return x;
}
AnsiString DiskStream::ReadAnsiString(void)
{
    AnsiString x="";
    while(true)
    {
        char c=ReadChar();
        if (c!=0) x=x+c; else break;
    }
    return x;
}
void DiskStream::ReadString(char *Buf,int SizeBuf)
{
    int i=0;
    while(i<SizeBuf)
    {
        *Buf=ReadChar();
        if (*Buf==0) break;
        i++;Buf++;
    }
}
char DiskStream::ReadChar(void)
{
    char x;
    S->ReadBuffer(&x,sizeof(x));
    return x;
}
