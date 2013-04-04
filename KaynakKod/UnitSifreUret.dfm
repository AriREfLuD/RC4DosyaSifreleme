object Form2: TForm2
  Left = 0
  Top = 0
  AutoSize = True
  Caption = #350'ifre Se'#231'me Yard'#305'mc'#305's'#305
  ClientHeight = 192
  ClientWidth = 535
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 0
    Top = 0
    Width = 530
    Height = 25
    Caption = 'Bu form size g'#252'venli '#351'ifre se'#231'menizde yard'#305'mc'#305' olacakt'#305'r.'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 0
    Top = 56
    Width = 267
    Height = 25
    Caption = 'Tercih Edilen '#350'ifre Uzunlu'#287'u'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 0
    Top = 162
    Width = 123
    Height = 25
    Caption = #220'retilen '#350'ifre'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object cmbSifre: TComboBox
    Left = 283
    Top = 53
    Width = 110
    Height = 33
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
  end
  object edtSifre: TEdit
    Left = 144
    Top = 159
    Width = 391
    Height = 33
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
  end
  object btnUret: TButton
    Left = 16
    Top = 100
    Width = 497
    Height = 37
    Caption = 'Rastgele '#350'ifre '#220'ret'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnClick = btnUretClick
  end
end
