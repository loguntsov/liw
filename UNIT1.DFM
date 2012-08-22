object Form1: TForm1
  Left = 177
  Top = 154
  Width = 559
  Height = 396
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 16
    Width = 83
    Height = 13
    Caption = 'Сортамент труб:'
  end
  object SortamentComboBox: TComboBox
    Left = 104
    Top = 16
    Width = 401
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 0
    OnClick = SortamentComboBoxClick
  end
  object StringGrid1: TStringGrid
    Left = 8
    Top = 56
    Width = 529
    Height = 297
    TabOrder = 1
  end
end
