object fmMain: TfmMain
  Left = 234
  Top = 113
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'SmartStim'
  ClientHeight = 446
  ClientWidth = 705
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001001010100000000000280100001600000028000000100000002000
    00000100040000000000C0000000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFF
    FFFFFFFFFFFFFFFF0FFFFFDF0FFFFFF0F0FFFFD0F0FFFFF0F0FFFFD0F0FFFFF0
    F0FFFFD0F0FFF80888088808880FFF0FFF0FFF0FFF0FFFFFFF0FFF0FFFFFFFFF
    FF0FFF0FFFFFFFFFFFF0F0DFFFFFF00DDFF0F0DFFFFFFFF0FDF0F0DFFFFFFF0F
    DFFF0FDFFFFFF0FDFFFFFFDFFFFFFF00DDFFFFDFFFFFFFFFFFFFFFFFFFFF0000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  PopupMenu = pmSmartStimAnalysis
  Position = poDesktopCenter
  Scaled = False
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  OnPaint = FormPaint
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object blPlot: TBevel
    Left = 4
    Top = 28
    Width = 643
    Height = 394
    Shape = bsFrame
  end
  object sbOnlineCorrectionMode10Release: TSpeedButton
    Left = 684
    Top = 104
    Width = 17
    Height = 17
    Visible = False
    OnClick = sbOnlineCorrectionMode10ReleaseClick
  end
  object sbOnlineCorrectionMode10Cancel: TSpeedButton
    Left = 668
    Top = 104
    Width = 17
    Height = 17
    Visible = False
    OnClick = sbOnlineCorrectionMode10CancelClick
  end
  object sbPlotXScroll: TScrollBar
    Left = 5
    Top = 424
    Width = 641
    Height = 17
    Enabled = False
    PageSize = 0
    TabOrder = 0
    TabStop = False
    OnChange = sbPlotXScrollChange
  end
  object bnSettings: TButton
    Left = 128
    Top = 4
    Width = 65
    Height = 21
    Caption = 'Settings'
    TabOrder = 1
    OnClick = bnSettingsClick
  end
  object bnStart: TButton
    Left = 204
    Top = 4
    Width = 65
    Height = 21
    Caption = 'Start'
    TabOrder = 2
    OnClick = bnStartClick
  end
  object bnStop: TButton
    Left = 272
    Top = 4
    Width = 65
    Height = 21
    Caption = 'Stop'
    TabOrder = 3
    OnClick = bnStopClick
  end
  object cbOperatingMode: TComboBox
    Left = 4
    Top = 4
    Width = 121
    Height = 21
    ItemHeight = 13
    TabOrder = 4
    Text = 'Online Processing'
    OnChange = cbOperatingModeChange
    Items.Strings = (
      'Online Processing'
      'Offline Processing'
      'Offline Viewing')
  end
  object cbAVStimulation: TCheckBox
    Left = 344
    Top = 9
    Width = 88
    Height = 17
    Alignment = taLeftJustify
    Caption = 'AV stimulation'
    Enabled = False
    TabOrder = 5
  end
  object stModeDependentInfo: TStaticText
    Left = 509
    Top = 10
    Width = 22
    Height = 17
    AutoSize = False
    Caption = 'Info'
    TabOrder = 6
    Visible = False
  end
  object stTrainingModeCaption: TStaticText
    Left = 440
    Top = 10
    Width = 29
    Height = 17
    AutoSize = False
    Caption = 'Mode'
    TabOrder = 7
    Visible = False
  end
  object stTrainingTimeCaption: TStaticText
    Left = 584
    Top = 10
    Width = 25
    Height = 17
    AutoSize = False
    Caption = 'Time'
    TabOrder = 8
    Visible = False
  end
  object stMarkerR4x4: TStaticText
    Left = 650
    Top = 24
    Width = 25
    Height = 13
    AutoSize = False
    Caption = '64'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 9
    Visible = False
  end
  object stMarkerR0x4: TStaticText
    Left = 650
    Top = 88
    Width = 25
    Height = 13
    AutoSize = False
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 10
    Visible = False
  end
  object stMarkerR3x4: TStaticText
    Left = 650
    Top = 40
    Width = 25
    Height = 13
    AutoSize = False
    Caption = '48'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 11
    Visible = False
  end
  object stMarkerR2x4: TStaticText
    Left = 650
    Top = 56
    Width = 25
    Height = 13
    AutoSize = False
    Caption = '32'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 12
    Visible = False
  end
  object stMarkerR1x4: TStaticText
    Left = 650
    Top = 72
    Width = 25
    Height = 13
    AutoSize = False
    Caption = '16'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 13
    Visible = False
  end
  object stMarkerF4x4: TStaticText
    Left = 650
    Top = 160
    Width = 25
    Height = 13
    AutoSize = False
    Caption = '64'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 14
    Visible = False
  end
  object stMarkerF0x4: TStaticText
    Left = 650
    Top = 224
    Width = 25
    Height = 13
    AutoSize = False
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 15
    Visible = False
  end
  object stMarkerF3x4: TStaticText
    Left = 650
    Top = 176
    Width = 25
    Height = 13
    AutoSize = False
    Caption = '48'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 16
    Visible = False
  end
  object stMarkerF2x4: TStaticText
    Left = 650
    Top = 192
    Width = 25
    Height = 13
    AutoSize = False
    Caption = '32'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 17
    Visible = False
  end
  object stMarkerF1x4: TStaticText
    Left = 650
    Top = 208
    Width = 25
    Height = 13
    AutoSize = False
    Caption = '16'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 18
    Visible = False
  end
  object stMarkerP4x4: TStaticText
    Left = 654
    Top = 296
    Width = 25
    Height = 13
    AutoSize = False
    Caption = '64'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 19
    Visible = False
  end
  object stMarkerP0x4: TStaticText
    Left = 654
    Top = 356
    Width = 25
    Height = 13
    AutoSize = False
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 20
    Visible = False
  end
  object stMarkerP3x4: TStaticText
    Left = 654
    Top = 308
    Width = 25
    Height = 13
    AutoSize = False
    Caption = '48'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 21
    Visible = False
  end
  object stMarkerP2x4: TStaticText
    Left = 654
    Top = 324
    Width = 25
    Height = 13
    AutoSize = False
    Caption = '32'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 22
    Visible = False
  end
  object stMarkerP1x4: TStaticText
    Left = 654
    Top = 340
    Width = 25
    Height = 13
    AutoSize = False
    Caption = '16'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 23
    Visible = False
  end
  object udOnlineThresholdLevelValue: TUpDown
    Left = 676
    Top = 234
    Width = 25
    Height = 17
    Min = 0
    Max = 504
    Increment = 4
    Orientation = udHorizontal
    Position = 0
    TabOrder = 24
    Visible = False
    Wrap = False
    OnClick = udOnlineThresholdLevelValueClick
  end
  object stTrainingModeValue: TStaticText
    Left = 474
    Top = 8
    Width = 27
    Height = 18
    Alignment = taCenter
    AutoSize = False
    BevelKind = bkTile
    Caption = '10'
    TabOrder = 25
    Visible = False
  end
  object stModeDependentValue: TStaticText
    Left = 534
    Top = 8
    Width = 25
    Height = 18
    Alignment = taCenter
    AutoSize = False
    BevelKind = bkTile
    Caption = '140'
    TabOrder = 26
    Visible = False
  end
  object stTrainingTimeValue: TStaticText
    Left = 614
    Top = 8
    Width = 33
    Height = 18
    AutoSize = False
    BevelKind = bkTile
    Caption = '00:00'
    TabOrder = 27
    Visible = False
  end
  object stOnlineThresholdLevelValue: TStaticText
    Left = 650
    Top = 234
    Width = 25
    Height = 18
    Alignment = taCenter
    AutoSize = False
    BevelKind = bkTile
    Caption = '508'
    TabOrder = 28
    Visible = False
  end
  object stOnlinePatternPeakParamValue: TStaticText
    Left = 650
    Top = 366
    Width = 25
    Height = 18
    Alignment = taCenter
    AutoSize = False
    BevelKind = bkTile
    Caption = '12'
    TabOrder = 29
    Visible = False
  end
  object udOnlinePatternPeakParamValue: TUpDown
    Left = 676
    Top = 366
    Width = 25
    Height = 17
    Min = 2
    Max = 40
    Orientation = udHorizontal
    Position = 2
    TabOrder = 30
    Visible = False
    Wrap = False
    OnClick = udOnlinePatternPeakParamValueClick
  end
  object udOnlinePatternPeakParamIndex: TUpDown
    Left = 676
    Top = 385
    Width = 25
    Height = 17
    Min = 0
    Max = 2
    Orientation = udHorizontal
    Position = 0
    TabOrder = 31
    Visible = False
    Wrap = False
    OnClick = udOnlinePatternPeakParamIndexClick
  end
  object stOnlinePatternPeakParamIndex: TStaticText
    Left = 650
    Top = 385
    Width = 25
    Height = 18
    Alignment = taCenter
    AutoSize = False
    BevelKind = bkTile
    BiDiMode = bdLeftToRight
    Caption = 'min'
    ParentBiDiMode = False
    TabOrder = 32
    Visible = False
  end
  object stModeDependentFlag: TStaticText
    Left = 560
    Top = 8
    Width = 17
    Height = 17
    AutoSize = False
    Color = clBtnFace
    ParentColor = False
    TabOrder = 33
  end
  object udOnlineThresholdLevelIndex: TUpDown
    Left = 676
    Top = 253
    Width = 25
    Height = 17
    Min = 0
    Max = 4
    Orientation = udHorizontal
    Position = 0
    TabOrder = 34
    Visible = False
    Wrap = False
    OnClick = udOnlineThresholdLevelIndexClick
  end
  object stOnlineThresholdLevelIndex: TStaticText
    Left = 650
    Top = 253
    Width = 25
    Height = 18
    Alignment = taCenter
    AutoSize = False
    BevelKind = bkTile
    Caption = 'low'
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 35
    Visible = False
  end
  object stOnlineCorrectionMode10: TStaticText
    Left = 650
    Top = 104
    Width = 17
    Height = 17
    AutoSize = False
    Color = clGreen
    ParentColor = False
    TabOrder = 36
    Visible = False
  end
  object pmSmartStimAnalysis: TPopupMenu
    Left = 648
    Top = 412
    object NAnalysisFFT: TMenuItem
      Caption = 'FFT'
      OnClick = NAnalysisFFTClick
    end
  end
end
