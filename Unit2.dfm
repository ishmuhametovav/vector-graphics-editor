object Form2: TForm2
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
  ClientHeight = 100
  ClientWidth = 247
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object program_name_label: TLabel
    Left = 8
    Top = 8
    Width = 190
    Height = 15
    Caption = #1042#1077#1082#1090#1086#1088#1085#1099#1081' '#1075#1088#1072#1092#1080#1095#1077#1089#1082#1080#1081' '#1088#1077#1076#1072#1082#1090#1086#1088
  end
  object creator_name_label: TLabel
    Left = 8
    Top = 44
    Width = 176
    Height = 17
    Caption = #1055#1086#1076#1075#1086#1090#1086#1074#1080#1083': '#1048#1096#1084#1091#1093#1072#1084#1077#1090#1086#1074' '#1040'.'#1042'.'
  end
  object creator_group_label: TLabel
    Left = 8
    Top = 71
    Width = 35
    Height = 15
    Caption = #1045#1058'-312'
  end
  object close_button: TButton
    Left = 164
    Top = 67
    Width = 75
    Height = 25
    Caption = #1054#1082
    TabOrder = 0
    OnClick = close_buttonClick
  end
end
