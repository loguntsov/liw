object MDIReport: TMDIReport
  Tag = 2
  Left = 271
  Top = 170
  BorderStyle = bsNone
  Caption = 'MDIReport'
  ClientHeight = 299
  ClientWidth = 325
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  WindowState = wsMaximized
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object RichBox: TRichEdit
    Left = 0
    Top = 0
    Width = 325
    Height = 299
    Align = alClient
    BorderStyle = bsNone
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    PlainText = True
    ScrollBars = ssBoth
    TabOrder = 0
    WantTabs = True
  end
  object SaveDialog: TSaveDialog
    DefaultExt = 'txt'
    Filter = 'Текст в формате RTF|*.rtf|Текстовый файл *.TXT|*.txt'
    FilterIndex = 2
    Title = 'Сохранение отчета'
    Left = 216
    Top = 32
  end
end
