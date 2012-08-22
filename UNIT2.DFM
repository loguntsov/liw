object Form2: TForm2
  Left = 195
  Top = 105
  Width = 389
  Height = 415
  Caption = 'Form2'
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
    Left = 8
    Top = 16
    Width = 126
    Height = 13
    Caption = 'Отметка земли в начале'
  end
  object Label2: TLabel
    Left = 8
    Top = 48
    Width = 121
    Height = 13
    Caption = 'Отметка земли в конце'
  end
  object Label3: TLabel
    Left = 8
    Top = 72
    Width = 122
    Height = 13
    Caption = 'Начальное заглубление'
  end
  object Label4: TLabel
    Left = 8
    Top = 96
    Width = 36
    Height = 13
    Caption = 'Расход'
  end
  object Label5: TLabel
    Left = 8
    Top = 120
    Width = 33
    Height = 13
    Caption = 'Длина'
  end
  object Label6: TLabel
    Left = 8
    Top = 152
    Width = 46
    Height = 13
    Caption = 'Диаметр'
  end
  object Label7: TLabel
    Left = 64
    Top = 152
    Width = 32
    Height = 13
    Caption = 'Label7'
  end
  object Label8: TLabel
    Left = 160
    Top = 152
    Width = 32
    Height = 13
    Caption = 'Уклон'
  end
  object Label9: TLabel
    Left = 200
    Top = 152
    Width = 32
    Height = 13
    Caption = 'Label9'
  end
  object Label10: TLabel
    Left = 8
    Top = 176
    Width = 62
    Height = 13
    Caption = 'Наполнение'
  end
  object Label11: TLabel
    Left = 72
    Top = 176
    Width = 38
    Height = 13
    Caption = 'Label11'
  end
  object Label12: TLabel
    Left = 152
    Top = 176
    Width = 107
    Height = 13
    Caption = 'Заглубление в конце'
  end
  object Label13: TLabel
    Left = 264
    Top = 176
    Width = 38
    Height = 13
    Caption = 'Label13'
  end
  object Label14: TLabel
    Left = 8
    Top = 200
    Width = 48
    Height = 13
    Caption = 'Скорость'
  end
  object Label15: TLabel
    Left = 64
    Top = 200
    Width = 38
    Height = 13
    Caption = 'Label15'
  end
  object Label16: TLabel
    Left = 16
    Top = 264
    Width = 80
    Height = 13
    Caption = 'Скорость входа'
  end
  object Label17: TLabel
    Left = 128
    Top = 328
    Width = 233
    Height = 33
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Edit1: TEdit
    Left = 144
    Top = 16
    Width = 153
    Height = 21
    TabOrder = 0
    Text = '100'
  end
  object Edit2: TEdit
    Left = 144
    Top = 40
    Width = 153
    Height = 21
    TabOrder = 1
  end
  object Edit3: TEdit
    Left = 144
    Top = 64
    Width = 153
    Height = 21
    TabOrder = 2
    Text = '2'
  end
  object Edit4: TEdit
    Left = 144
    Top = 88
    Width = 153
    Height = 21
    TabOrder = 3
  end
  object Edit5: TEdit
    Left = 144
    Top = 112
    Width = 153
    Height = 21
    TabOrder = 4
    Text = '100'
  end
  object ComboBox1: TComboBox
    Left = 16
    Top = 296
    Width = 361
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 5
  end
  object Button1: TButton
    Left = 16
    Top = 328
    Width = 105
    Height = 33
    Caption = 'Button1'
    TabOrder = 6
    OnClick = Button1Click
  end
  object Edit6: TEdit
    Left = 104
    Top = 264
    Width = 105
    Height = 21
    TabOrder = 7
    Text = '0'
  end
end
