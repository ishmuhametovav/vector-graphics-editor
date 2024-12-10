object Form3: TForm3
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1057#1074#1086#1081#1089#1090#1074#1072
  ClientHeight = 205
  ClientWidth = 225
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnShow = FormShow
  TextHeight = 15
  object save_data_label: TLabel
    Left = 8
    Top = 24
    Width = 99
    Height = 15
    Caption = #1044#1072#1090#1072' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103': '
  end
  object data_size_label: TLabel
    Left = 8
    Top = 61
    Width = 96
    Height = 15
    Caption = #1056#1072#1079#1084#1077#1088' '#1085#1072' '#1076#1080#1089#1082#1077': '
  end
  object width_label: TLabel
    Left = 8
    Top = 96
    Width = 51
    Height = 15
    Caption = #1064#1080#1088#1080#1085#1072': '
  end
  object height_label: TLabel
    Left = 8
    Top = 136
    Width = 46
    Height = 15
    Caption = #1042#1099#1089#1086#1090#1072': '
  end
  object apply_button: TButton
    Left = 8
    Top = 172
    Width = 75
    Height = 25
    Caption = 'Ok'
    TabOrder = 0
    OnClick = apply_buttonClick
  end
  object cancel_button: TButton
    Left = 135
    Top = 172
    Width = 75
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 1
    OnClick = cancel_buttonClick
  end
  object width_edit: TEdit
    Left = 96
    Top = 93
    Width = 121
    Height = 23
    NumbersOnly = True
    TabOrder = 2
  end
  object height_edit: TEdit
    Left = 96
    Top = 133
    Width = 121
    Height = 23
    NumbersOnly = True
    TabOrder = 3
  end
end
