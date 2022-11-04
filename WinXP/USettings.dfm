object fmSettings: TfmSettings
  Left = 325
  Top = 188
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Settings'
  ClientHeight = 460
  ClientWidth = 677
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
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000000
    0000000000000000B0000090B000000B0B00009B0B00000B0B00009B0B00000B
    0B00009B0B0008B888B888B888B000B000B000B000B0000000B000B000000000
    00B000B000000000000B0B9000000BB8800B0B900000000B080B0B90000000B0
    8000B09000000B0800000090000000BB88000090000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  Position = poMainFormCenter
  ShowHint = True
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object sbInputFileName: TSpeedButton
    Left = 428
    Top = 368
    Width = 21
    Height = 21
    Caption = '...'
    OnClick = sbInputFileNameClick
  end
  object sbOutputFileName: TSpeedButton
    Left = 204
    Top = 368
    Width = 21
    Height = 21
    Caption = '...'
    OnClick = sbOutputFileNameClick
  end
  object blOK: TBevel
    Left = 4
    Top = 396
    Width = 669
    Height = 9
    Shape = bsTopLine
  end
  object sbSoundFileName: TSpeedButton
    Left = 652
    Top = 368
    Width = 21
    Height = 21
    Caption = '...'
    OnClick = sbSoundFileNameClick
  end
  object sbSoundTest: TSpeedButton
    Left = 516
    Top = 368
    Width = 21
    Height = 21
    Caption = '>'
    OnClick = sbSoundTestClick
  end
  object gbStimulating: TGroupBox
    Left = 340
    Top = 148
    Width = 333
    Height = 193
    Caption = 'AV stimulation'
    TabOrder = 0
    object stStimulatingShift: TStaticText
      Left = 248
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Shift [ms]'
      TabOrder = 0
    end
    object stStimulatingIntensity: TStaticText
      Left = 168
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Intensity'
      TabOrder = 1
    end
    object cbStimulatingShift: TComboBox
      Left = 248
      Top = 40
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 2
      Text = '16'
      Items.Strings = (
        '0'
        '8'
        '16'
        '32'
        '64')
    end
    object cbStimulatingIntensity: TComboBox
      Left = 168
      Top = 40
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 3
      Text = '1'
      Items.Strings = (
        '1'
        '2'
        '3'
        '4'
        '5')
    end
    object stStimulatingType: TStaticText
      Left = 8
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Type'
      TabOrder = 4
    end
    object cbStimulatingType: TComboBox
      Left = 8
      Top = 40
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 5
      Text = 'Light'
      Items.Strings = (
        'None'
        'Light'
        'Sound'
        'Color'
        'Shock')
    end
    object pcStimulatingMode: TPageControl
      Left = 8
      Top = 68
      Width = 317
      Height = 93
      ActivePage = tsStimulatingMode6
      TabIndex = 5
      TabOrder = 6
      OnChange = pcStimulatingModeChange
      object tsStimulatingMode1: TTabSheet
        Caption = 'Mode 1'
        object stStimulatingMode1NoSpecialParams: TStaticText
          Left = 4
          Top = 8
          Width = 97
          Height = 19
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          Caption = 'No special params'
          TabOrder = 0
        end
      end
      object tsStimulatingMode2: TTabSheet
        Caption = 'Mode 2'
        ImageIndex = 1
        object stStimulatingMode2NoSpecialParams: TStaticText
          Left = 4
          Top = 8
          Width = 97
          Height = 19
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          Caption = 'No special params'
          TabOrder = 0
        end
      end
      object tsStimulatingMode3: TTabSheet
        Caption = 'Mode 3'
        ImageIndex = 2
        object stStimulatingMode3AlternativeIntensity: TStaticText
          Left = 4
          Top = 8
          Width = 97
          Height = 19
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          Caption = 'Alternate intensity'
          TabOrder = 0
        end
        object cbStimulatingMode3AlternativeIntensity: TComboBox
          Left = 4
          Top = 34
          Width = 97
          Height = 21
          ItemHeight = 13
          TabOrder = 1
          Text = '1'
          Items.Strings = (
            '1'
            '2'
            '3'
            '4'
            '5')
        end
      end
      object tsStimulatingMode4: TTabSheet
        Caption = 'Mode 4'
        ImageIndex = 3
        object stStimulatingMode4AlternativeShift: TStaticText
          Left = 4
          Top = 8
          Width = 97
          Height = 19
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          Caption = 'Alternate shift [ms]'
          TabOrder = 0
        end
        object cbStimulatingMode4AlternativeShift: TComboBox
          Left = 4
          Top = 34
          Width = 97
          Height = 21
          ItemHeight = 13
          TabOrder = 1
          Text = '0'
          Items.Strings = (
            '0'
            '8'
            '16'
            '32'
            '64')
        end
      end
      object tsStimulatingMode5: TTabSheet
        Caption = 'Mode 5'
        ImageIndex = 4
        object stStimulatingMode5StimulusPeriod: TStaticText
          Left = 4
          Top = 8
          Width = 97
          Height = 19
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          Caption = 'Stimuli period [ms]'
          TabOrder = 0
        end
        object cbStimulatingMode5StimulusPeriod: TComboBox
          Left = 4
          Top = 34
          Width = 97
          Height = 21
          ItemHeight = 13
          TabOrder = 1
          Text = '104'
          Items.Strings = (
            '8'
            '16'
            '24'
            '32'
            '40'
            '48'
            '56'
            '64'
            '72'
            '80'
            '88'
            '96'
            '104'
            '112'
            '120'
            '128'
            '136'
            '144'
            '152'
            '160'
            '168'
            '176'
            '184'
            '192'
            '200'
            '208'
            '216'
            '224'
            '232'
            '240'
            '248'
            '256')
        end
      end
      object tsStimulatingMode6: TTabSheet
        Caption = 'Mode 6'
        ImageIndex = 5
        object stStimulatingMode6NStimulationMask: TStaticText
          Left = 204
          Top = 8
          Width = 97
          Height = 19
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          Caption = 'Mask'
          TabOrder = 0
        end
        object cbStimulatingMode6NStimulationMask: TComboBox
          Left = 204
          Top = 32
          Width = 97
          Height = 21
          BevelOuter = bvNone
          ItemHeight = 13
          TabOrder = 1
          Text = 'Active RHY'
          Items.Strings = (
            'Active RHY'
            'Active INT'
            'Passive RHY')
        end
        object stStimulatingMode6NStimulusPeriod: TStaticText
          Left = 4
          Top = 8
          Width = 97
          Height = 19
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          Caption = 'Stimuli period [ms]'
          TabOrder = 2
        end
        object cbStimulatingMode6NStimulusPeriod: TComboBox
          Left = 4
          Top = 34
          Width = 97
          Height = 21
          ItemHeight = 13
          TabOrder = 3
          Text = '104'
          Items.Strings = (
            '8'
            '16'
            '24'
            '32'
            '40'
            '48'
            '56'
            '64'
            '72'
            '80'
            '88'
            '96'
            '104'
            '112'
            '120'
            '128'
            '136'
            '144'
            '152'
            '160'
            '168'
            '176'
            '184'
            '192'
            '200'
            '208'
            '216'
            '224'
            '232'
            '240'
            '248'
            '256')
        end
        object stStimulatingMode6NStimulationTime: TStaticText
          Left = 104
          Top = 8
          Width = 97
          Height = 19
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          Caption = 'Stimulation time [s]'
          TabOrder = 4
        end
        object cbStimulatingMode6NStimulationTime: TComboBox
          Left = 104
          Top = 34
          Width = 97
          Height = 21
          ItemHeight = 13
          TabOrder = 5
          Text = '4'
          Items.Strings = (
            '1'
            '2'
            '3'
            '4'
            '5'
            '6'
            '7'
            '8')
        end
      end
      object tsStimulatingMode7: TTabSheet
        Caption = 'Mode 7'
        ImageIndex = 6
        object stStimulatingMode7CycleTime: TStaticText
          Left = 4
          Top = 8
          Width = 97
          Height = 19
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          Caption = 'Cycle time [ms]'
          TabOrder = 0
        end
        object cbStimulatingMode7CycleTime: TComboBox
          Left = 4
          Top = 34
          Width = 97
          Height = 21
          ItemHeight = 13
          TabOrder = 1
          Text = '128'
          Items.Strings = (
            '128'
            '256'
            '512'
            '1024'
            '2048'
            '4096'
            '8192')
        end
        object stStimulatingMode7Modulation: TStaticText
          Left = 104
          Top = 8
          Width = 97
          Height = 19
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          Caption = 'Modulation'
          TabOrder = 2
        end
        object cbStimulatingMode7Modulation: TComboBox
          Left = 104
          Top = 34
          Width = 97
          Height = 21
          ItemHeight = 13
          TabOrder = 3
          Text = 'Symmetric'
          Items.Strings = (
            'Symmetric'
            'Asymmetric')
        end
      end
      object tsStimulatingMode8: TTabSheet
        Caption = 'Mode 8'
        ImageIndex = 7
        object stStimulatingMode8StimulusPeriod: TStaticText
          Left = 104
          Top = 8
          Width = 97
          Height = 19
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          Caption = 'Stimuli period [ms]'
          TabOrder = 0
        end
        object cbStimulatingMode8StimulusPeriod: TComboBox
          Left = 104
          Top = 34
          Width = 97
          Height = 21
          ItemHeight = 13
          TabOrder = 1
          Text = '104'
          Items.Strings = (
            '72'
            '80'
            '88'
            '96'
            '104'
            '112'
            '120'
            '128'
            '136'
            '144')
        end
        object stStimulatingMode8ParadigmType: TStaticText
          Left = 4
          Top = 8
          Width = 97
          Height = 19
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          Caption = 'Paradigm'
          TabOrder = 2
        end
        object cbStimulatingMode8ParadigmType: TComboBox
          Left = 4
          Top = 34
          Width = 97
          Height = 21
          ItemHeight = 13
          TabOrder = 3
          Text = 'Simple'
          Items.Strings = (
            'Simple'
            'Intensity'
            'Frequency'
            'Combine')
        end
      end
      object tsStimulatingMode9: TTabSheet
        Caption = 'Mode 9'
        ImageIndex = 8
        object stStimulatingMode9ParadigmType: TStaticText
          Left = 4
          Top = 8
          Width = 97
          Height = 19
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          Caption = 'Paradigm'
          TabOrder = 0
        end
        object cbStimulatingMode9ParadigmType: TComboBox
          Left = 4
          Top = 34
          Width = 97
          Height = 21
          ItemHeight = 13
          TabOrder = 1
          Text = 'Frequency'
          Items.Strings = (
            'Frequency'
            'Intensity')
        end
        object stStimulatingMode9StimulusNumber: TStaticText
          Left = 204
          Top = 8
          Width = 97
          Height = 19
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          Caption = 'Stimulus number'
          TabOrder = 2
        end
        object stStimulatingMode9StimulusPeriod: TStaticText
          Left = 104
          Top = 8
          Width = 97
          Height = 19
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          Caption = 'Stimuli period [ms]'
          TabOrder = 3
        end
        object cbStimulatingMode9StimulusNumber: TComboBox
          Left = 204
          Top = 34
          Width = 97
          Height = 21
          ItemHeight = 13
          TabOrder = 4
          Text = '8'
          Items.Strings = (
            '1'
            '2'
            '3'
            '4'
            '5'
            '6'
            '7'
            '8'
            '9'
            '10'
            '11'
            '12'
            '13'
            '14'
            '15'
            '16')
        end
        object cbStimulatingMode9StimulusPeriod: TComboBox
          Left = 104
          Top = 34
          Width = 97
          Height = 21
          ItemHeight = 13
          TabOrder = 5
          Text = '104'
          Items.Strings = (
            '72'
            '80'
            '88'
            '96'
            '104'
            '112'
            '120'
            '128'
            '136'
            '144')
        end
      end
      object tsStimulatingMode10: TTabSheet
        Caption = 'Mode 10'
        ImageIndex = 9
        object stStimulatingMode10ParadigmType: TStaticText
          Left = 4
          Top = 8
          Width = 97
          Height = 19
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          Caption = 'Paradigm'
          TabOrder = 0
        end
        object cbStimulatingMode10ParadigmType: TComboBox
          Left = 4
          Top = 34
          Width = 97
          Height = 21
          ItemHeight = 13
          TabOrder = 1
          Text = 'Only Shock'
          Items.Strings = (
            'Only Shock'
            'Relax < Shock '
            'Relax = Shock')
        end
        object stStimulatingMode10ShockType: TStaticText
          Left = 204
          Top = 8
          Width = 97
          Height = 19
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          Caption = 'Shock type'
          TabOrder = 2
        end
        object cbStimulatingMode10ShockType: TComboBox
          Left = 204
          Top = 34
          Width = 97
          Height = 21
          ItemHeight = 13
          TabOrder = 3
          Text = 'Electric shock'
          Items.Strings = (
            'Electric shock'
            'Sound shock')
        end
        object stStimulatingMode10AnalysisTime: TStaticText
          Left = 104
          Top = 8
          Width = 97
          Height = 19
          Alignment = taCenter
          AutoSize = False
          BevelKind = bkTile
          Caption = 'Analysis time [s]'
          TabOrder = 4
        end
        object cbStimulatingMode10AnalysisTime: TComboBox
          Left = 104
          Top = 34
          Width = 97
          Height = 21
          ItemHeight = 13
          TabOrder = 5
          Text = '5'
          Items.Strings = (
            '1'
            '2'
            '3'
            '4'
            '5'
            '6'
            '7'
            '8'
            '9'
            '10'
            '11'
            '12'
            '13'
            '14'
            '15'
            '16')
        end
      end
    end
    object stStimulatingDuration: TStaticText
      Left = 88
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Duration [ms]'
      TabOrder = 7
    end
    object cbStimulatingDuration: TComboBox
      Left = 88
      Top = 40
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 8
      Text = '16'
      Items.Strings = (
        '8'
        '16'
        '24'
        '32'
        '40'
        '48'
        '56'
        '64'
        '72'
        '80'
        '88'
        '96'
        '104'
        '112'
        '120'
        '128'
        '136'
        '144'
        '152'
        '160'
        '168'
        '176'
        '184'
        '192'
        '200'
        '208'
        '216'
        '224'
        '232'
        '240'
        '248'
        '256')
    end
    object stStimulatingVideoSet: TStaticText
      Left = 8
      Top = 168
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Video set'
      TabOrder = 9
    end
    object cbStimulatingVideoSet: TComboBox
      Left = 88
      Top = 166
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 10
      Text = '1'
      Items.Strings = (
        '1'
        '2'
        '3'
        '4')
    end
    object stStimulatingAudioSet: TStaticText
      Left = 168
      Top = 168
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Audio set'
      TabOrder = 11
    end
    object cbStimulatingAudioSet: TComboBox
      Left = 248
      Top = 166
      Width = 77
      Height = 21
      Hint = 'Modulation form index'
      ItemHeight = 13
      TabOrder = 12
      Text = '4'
      Items.Strings = (
        '2'
        '4'
        '8')
    end
  end
  object gbDigitizing: TGroupBox
    Left = 4
    Top = 4
    Width = 333
    Height = 69
    Caption = 'EEG acquisition'
    TabOrder = 1
    object stDigitizingSampleRate: TStaticText
      Left = 8
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Sample rate'
      TabOrder = 0
    end
    object stDigitizingLoFreq: TStaticText
      Left = 168
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Low freq [Hz]'
      TabOrder = 1
    end
    object stDigitizingHiFreq: TStaticText
      Left = 248
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'High freq [Hz]'
      TabOrder = 2
    end
    object cbDigitizingSampleRate: TComboBox
      Left = 8
      Top = 40
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 3
      Text = '128'
      Items.Strings = (
        '128')
    end
    object cbDigitizingLoFreq: TComboBox
      Left = 168
      Top = 40
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 4
      Text = '1'
      Items.Strings = (
        '1'
        '?'
        '?'
        '0.05'
        '0.5'
        '0.1'
        '?'
        '0.02')
    end
    object cbDigitizingHiFreq: TComboBox
      Left = 248
      Top = 40
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 5
      Text = '60'
      Items.Strings = (
        '30'
        '60'
        '150'
        '270')
    end
    object stDigitizingAmpGain: TStaticText
      Left = 88
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Amp gain'
      TabOrder = 6
    end
    object cbDigitizingAmpGain: TComboBox
      Left = 88
      Top = 40
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 7
      Text = '60000'
      Items.Strings = (
        '2000'
        '4000'
        '8000'
        '16000'
        '20000'
        '40000'
        '60000'
        '80000')
    end
  end
  object gbPlot: TGroupBox
    Left = 4
    Top = 272
    Width = 333
    Height = 69
    Caption = 'Plot'
    TabOrder = 2
    object stPlotWidth: TStaticText
      Left = 8
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Width'
      TabOrder = 0
    end
    object stPlotHeight: TStaticText
      Left = 88
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Height'
      TabOrder = 1
    end
    object stPlotXScale: TStaticText
      Left = 168
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'XScale'
      TabOrder = 2
    end
    object stPlotYScale: TStaticText
      Left = 248
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'YScale'
      TabOrder = 3
    end
    object cbPlotWidth: TComboBox
      Left = 8
      Top = 40
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 4
      Text = '640'
      Items.Strings = (
        '640'
        '768'
        '896'
        '1024'
        '1152')
    end
    object cbPlotHeight: TComboBox
      Left = 88
      Top = 40
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 5
      Text = '384'
      Items.Strings = (
        '384'
        '480'
        '576'
        '672'
        '768')
    end
    object cbPlotXScale: TComboBox
      Left = 168
      Top = 40
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 6
      Text = '2'
      Items.Strings = (
        '1'
        '2'
        '4')
    end
    object cbPlotYScale: TComboBox
      Left = 248
      Top = 40
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 7
      Text = '2'
      Items.Strings = (
        '1'
        '2'
        '3'
        '4'
        '5'
        '6'
        '7'
        '8'
        '9'
        '10'
        '11'
        '12'
        '13'
        '14'
        '15'
        '16')
    end
  end
  object stInputFileName: TStaticText
    Left = 228
    Top = 344
    Width = 221
    Height = 19
    Alignment = taCenter
    AutoSize = False
    BevelKind = bkTile
    Caption = 'Input file name'
    TabOrder = 3
  end
  object edInputFileName: TEdit
    Left = 228
    Top = 368
    Width = 197
    Height = 21
    ReadOnly = True
    TabOrder = 4
  end
  object stOutputFileName: TStaticText
    Left = 4
    Top = 344
    Width = 221
    Height = 19
    Alignment = taCenter
    AutoSize = False
    BevelKind = bkTile
    Caption = 'Output file name'
    TabOrder = 5
  end
  object edOutputFileName: TEdit
    Left = 4
    Top = 368
    Width = 197
    Height = 21
    ReadOnly = True
    TabOrder = 6
  end
  object cbPeaking: TGroupBox
    Left = 4
    Top = 76
    Width = 333
    Height = 121
    Caption = 'Peak detection'
    TabOrder = 7
    object stPeakingThresholdLevelNoise: TStaticText
      Left = 72
      Top = 16
      Width = 61
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Level noise'
      TabOrder = 0
    end
    object cbPeakingThresholdLevelNoise: TComboBox
      Left = 72
      Top = 40
      Width = 61
      Height = 21
      ItemHeight = 13
      TabOrder = 1
      Text = '0'
      Items.Strings = (
        '0'
        '4'
        '8'
        '12'
        '16'
        '20'
        '24'
        '28'
        '32'
        '36'
        '40'
        '44'
        '48'
        '52'
        '56'
        '60'
        '64'
        '68'
        '72'
        '76'
        '80'
        '84'
        '88'
        '92'
        '96'
        '100'
        '104'
        '108'
        '112'
        '116'
        '120'
        '124'
        '128'
        '132'
        '136'
        '140'
        '144'
        '148'
        '152'
        '156'
        '160'
        '164'
        '168'
        '172'
        '176'
        '180'
        '184'
        '188'
        '192'
        '196'
        '200'
        '204'
        '208'
        '212'
        '216'
        '220'
        '224'
        '228'
        '232'
        '236'
        '240'
        '244'
        '248'
        '252'
        '256'
        '260'
        '264'
        '268'
        '272'
        '276'
        '280'
        '284'
        '288'
        '292'
        '296'
        '300'
        '304'
        '308'
        '312'
        '316'
        '320'
        '324'
        '328'
        '332'
        '336'
        '340'
        '344'
        '348'
        '352'
        '356'
        '360'
        '364'
        '368'
        '372'
        '376'
        '380'
        '384'
        '388'
        '392'
        '396'
        '400'
        '404'
        '408'
        '412'
        '416'
        '420'
        '424'
        '428'
        '432'
        '436'
        '440'
        '444'
        '448'
        '452'
        '456'
        '460'
        '464'
        '468'
        '472'
        '476'
        '480'
        '484'
        '488'
        '492'
        '496'
        '500'
        '504'
        '508')
    end
    object stPeakingDeadTime: TStaticText
      Left = 8
      Top = 16
      Width = 61
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Dead time'
      TabOrder = 2
    end
    object cbPeakingDeadTime: TComboBox
      Left = 8
      Top = 40
      Width = 61
      Height = 21
      ItemHeight = 13
      TabOrder = 3
      Text = '40'
      Items.Strings = (
        '40'
        '48'
        '56'
        '64'
        '72'
        '80')
    end
    object stPeakingThresholdLevelFloat: TStaticText
      Left = 136
      Top = 68
      Width = 61
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Level float'
      Enabled = False
      TabOrder = 4
    end
    object cbPeakingThresholdLevelFloat: TComboBox
      Left = 136
      Top = 92
      Width = 61
      Height = 21
      Enabled = False
      ItemHeight = 13
      TabOrder = 5
      Text = '0'
      Items.Strings = (
        '0'
        '4'
        '8'
        '12'
        '16'
        '20'
        '24'
        '28'
        '32'
        '36'
        '40'
        '44'
        '48'
        '52'
        '56'
        '60'
        '64'
        '68'
        '72'
        '76'
        '80'
        '84'
        '88'
        '92'
        '96'
        '100'
        '104'
        '108'
        '112'
        '116'
        '120'
        '124'
        '128'
        '132'
        '136'
        '140'
        '144'
        '148'
        '152'
        '156'
        '160'
        '164'
        '168'
        '172'
        '176'
        '180'
        '184'
        '188'
        '192'
        '196'
        '200'
        '204'
        '208'
        '212'
        '216'
        '220'
        '224'
        '228'
        '232'
        '236'
        '240'
        '244'
        '248'
        '252'
        '256'
        '260'
        '264'
        '268'
        '272'
        '276'
        '280'
        '284'
        '288'
        '292'
        '296'
        '300'
        '304'
        '308'
        '312'
        '316'
        '320'
        '324'
        '328'
        '332'
        '336'
        '340'
        '344'
        '348'
        '352'
        '356'
        '360'
        '364'
        '368'
        '372'
        '376'
        '380'
        '384'
        '388'
        '392'
        '396'
        '400'
        '404'
        '408'
        '412'
        '416'
        '420'
        '424'
        '428'
        '432'
        '436'
        '440'
        '444'
        '448'
        '452'
        '456'
        '460'
        '464'
        '468'
        '472'
        '476'
        '480'
        '484'
        '488'
        '492'
        '496'
        '500'
        '504'
        '508')
    end
    object cbPeakingMeanShortWindowLength: TComboBox
      Left = 136
      Top = 40
      Width = 61
      Height = 21
      Enabled = False
      ItemHeight = 13
      TabOrder = 6
      Text = '512'
      Items.Strings = (
        '256'
        '384'
        '512'
        '640'
        '768'
        '896'
        '1024'
        '1152'
        '1280'
        '1408'
        '1536'
        '1664'
        '1792'
        '1920'
        '2048')
    end
    object stPeakingMeanShortWindowLength: TStaticText
      Left = 136
      Top = 16
      Width = 61
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Short wnd'
      Enabled = False
      TabOrder = 7
    end
    object stPeakingThresholdLevelFixed: TStaticText
      Left = 72
      Top = 68
      Width = 61
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Level fixed'
      TabOrder = 8
    end
    object cbPeakingThresholdLevelFixed: TComboBox
      Left = 72
      Top = 92
      Width = 61
      Height = 21
      ItemHeight = 13
      TabOrder = 9
      Text = '0'
      Items.Strings = (
        '0'
        '4'
        '8'
        '12'
        '16'
        '20'
        '24'
        '28'
        '32'
        '36'
        '40'
        '44'
        '48'
        '52'
        '56'
        '60'
        '64'
        '68'
        '72'
        '76'
        '80'
        '84'
        '88'
        '92'
        '96'
        '100'
        '104'
        '108'
        '112'
        '116'
        '120'
        '124'
        '128'
        '132'
        '136'
        '140'
        '144'
        '148'
        '152'
        '156'
        '160'
        '164'
        '168'
        '172'
        '176'
        '180'
        '184'
        '188'
        '192'
        '196'
        '200'
        '204'
        '208'
        '212'
        '216'
        '220'
        '224'
        '228'
        '232'
        '236'
        '240'
        '244'
        '248'
        '252'
        '256'
        '260'
        '264'
        '268'
        '272'
        '276'
        '280'
        '284'
        '288'
        '292'
        '296'
        '300'
        '304'
        '308'
        '312'
        '316'
        '320'
        '324'
        '328'
        '332'
        '336'
        '340'
        '344'
        '348'
        '352'
        '356'
        '360'
        '364'
        '368'
        '372'
        '376'
        '380'
        '384'
        '388'
        '392'
        '396'
        '400'
        '404'
        '408'
        '412'
        '416'
        '420'
        '424'
        '428'
        '432'
        '436'
        '440'
        '444'
        '448'
        '452'
        '456'
        '460'
        '464'
        '468'
        '472'
        '476'
        '480'
        '484'
        '488'
        '492'
        '496'
        '500'
        '504'
        '508')
    end
    object stPeakingThresholdLevelType: TStaticText
      Left = 8
      Top = 68
      Width = 61
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Level type'
      Enabled = False
      TabOrder = 10
    end
    object cbPeakingThresholdLevelType: TComboBox
      Left = 8
      Top = 92
      Width = 61
      Height = 21
      ItemHeight = 13
      TabOrder = 11
      Text = 'Float'
      OnChange = cbPeakingThresholdLevelTypeChange
      Items.Strings = (
        'Float'
        'Fixed')
    end
    object stPeakingMeanLongWindowLength: TStaticText
      Left = 200
      Top = 16
      Width = 61
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Long wnd'
      TabOrder = 12
    end
    object cbPeakingMeanLongWindowLength: TComboBox
      Left = 200
      Top = 40
      Width = 61
      Height = 21
      ItemHeight = 13
      TabOrder = 13
      Text = '4096'
      Items.Strings = (
        '2048'
        '3072'
        '4096'
        '5120'
        '6144'
        '7168'
        '8192'
        '9216'
        '10240'
        '11264'
        '12288'
        '13312'
        '14336'
        '15360'
        '16384')
    end
    object stPeakingCommandParameter: TStaticText
      Left = 264
      Top = 16
      Width = 61
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Cmd param'
      TabOrder = 14
    end
    object cbPeakingCommandParameter: TComboBox
      Left = 264
      Top = 40
      Width = 61
      Height = 21
      ItemHeight = 13
      TabOrder = 15
      Text = 'Peak'
      OnChange = cbPeakingCommandParameterChange
      Items.Strings = (
        'Peak'
        'Power')
    end
    object stPeakingThresholdLevelFloatMax: TStaticText
      Left = 264
      Top = 68
      Width = 61
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Level max'
      TabOrder = 16
    end
    object stPeakingThresholdLevelFloatMin: TStaticText
      Left = 200
      Top = 68
      Width = 61
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Level min'
      TabOrder = 17
    end
    object cbPeakingThresholdLevelFloatMax: TComboBox
      Left = 264
      Top = 92
      Width = 61
      Height = 21
      ItemHeight = 13
      TabOrder = 18
      Text = '0'
      Items.Strings = (
        '0'
        '4'
        '8'
        '12'
        '16'
        '20'
        '24'
        '28'
        '32'
        '36'
        '40'
        '44'
        '48'
        '52'
        '56'
        '60'
        '64'
        '68'
        '72'
        '76'
        '80'
        '84'
        '88'
        '92'
        '96'
        '100'
        '104'
        '108'
        '112'
        '116'
        '120'
        '124'
        '128'
        '132'
        '136'
        '140'
        '144'
        '148'
        '152'
        '156'
        '160'
        '164'
        '168'
        '172'
        '176'
        '180'
        '184'
        '188'
        '192'
        '196'
        '200'
        '204'
        '208'
        '212'
        '216'
        '220'
        '224'
        '228'
        '232'
        '236'
        '240'
        '244'
        '248'
        '252'
        '256'
        '260'
        '264'
        '268'
        '272'
        '276'
        '280'
        '284'
        '288'
        '292'
        '296'
        '300'
        '304'
        '308'
        '312'
        '316'
        '320'
        '324'
        '328'
        '332'
        '336'
        '340'
        '344'
        '348'
        '352'
        '356'
        '360'
        '364'
        '368'
        '372'
        '376'
        '380'
        '384'
        '388'
        '392'
        '396'
        '400'
        '404'
        '408'
        '412'
        '416'
        '420'
        '424'
        '428'
        '432'
        '436'
        '440'
        '444'
        '448'
        '452'
        '456'
        '460'
        '464'
        '468'
        '472'
        '476'
        '480'
        '484'
        '488'
        '492'
        '496'
        '500'
        '504'
        '508')
    end
    object cbPeakingThresholdLevelFloatMin: TComboBox
      Left = 200
      Top = 92
      Width = 61
      Height = 21
      ItemHeight = 13
      TabOrder = 19
      Text = '0'
      Items.Strings = (
        '0'
        '4'
        '8'
        '12'
        '16'
        '20'
        '24'
        '28'
        '32'
        '36'
        '40'
        '44'
        '48'
        '52'
        '56'
        '60'
        '64'
        '68'
        '72'
        '76'
        '80'
        '84'
        '88'
        '92'
        '96'
        '100'
        '104'
        '108'
        '112'
        '116'
        '120'
        '124'
        '128'
        '132'
        '136'
        '140'
        '144'
        '148'
        '152'
        '156'
        '160'
        '164'
        '168'
        '172'
        '176'
        '180'
        '184'
        '188'
        '192'
        '196'
        '200'
        '204'
        '208'
        '212'
        '216'
        '220'
        '224'
        '228'
        '232'
        '236'
        '240'
        '244'
        '248'
        '252'
        '256'
        '260'
        '264'
        '268'
        '272'
        '276'
        '280'
        '284'
        '288'
        '292'
        '296'
        '300'
        '304'
        '308'
        '312'
        '316'
        '320'
        '324'
        '328'
        '332'
        '336'
        '340'
        '344'
        '348'
        '352'
        '356'
        '360'
        '364'
        '368'
        '372'
        '376'
        '380'
        '384'
        '388'
        '392'
        '396'
        '400'
        '404'
        '408'
        '412'
        '416'
        '420'
        '424'
        '428'
        '432'
        '436'
        '440'
        '444'
        '448'
        '452'
        '456'
        '460'
        '464'
        '468'
        '472'
        '476'
        '480'
        '484'
        '488'
        '492'
        '496'
        '500'
        '504'
        '508')
    end
  end
  object gbTraining: TGroupBox
    Left = 340
    Top = 76
    Width = 333
    Height = 69
    Caption = 'Training'
    TabOrder = 8
    object stTrainingDuration: TStaticText
      Left = 8
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Duration [m]'
      TabOrder = 0
    end
    object stTrainingMode: TStaticText
      Left = 88
      Top = 16
      Width = 237
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Mode'
      TabOrder = 1
    end
    object cbTrainingDuration: TComboBox
      Left = 8
      Top = 40
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 2
      Text = '1'
      Items.Strings = (
        '1'
        '2'
        '3'
        '4'
        '5'
        '6'
        '7'
        '8'
        '9'
        '10'
        '11'
        '12'
        '13'
        '14'
        '15'
        '16'
        '17'
        '18'
        '19'
        '20'
        '21'
        '22'
        '23'
        '24'
        '25'
        '26'
        '27'
        '28'
        '29'
        '30')
    end
    object cbTrainingMode: TComboBox
      Left = 88
      Top = 40
      Width = 237
      Height = 21
      ItemHeight = 13
      TabOrder = 3
      Text = '1. Peak-wave stimulation'
      OnChange = cbTrainingModeChange
      Items.Strings = (
        '1. Peak-wave simple stimulation'
        '2. Peak-wave threshold stimulation'
        '3. Peak-wave power control stimulation'
        '4. Peak-wave shift control stimulation'
        '5. Rhythmic simple stimulation'
        '6. Rhythmic adaptive stimulation'
        '7. Rhythmic frequency control stimulation'
        '8. Rhythmic threshold stimulation'
        '9. Pattern simple paradigm stimulation'
        '10. Pattern shock paradigm stimulation')
    end
  end
  object bnApply: TButton
    Left = 260
    Top = 416
    Width = 75
    Height = 25
    Caption = 'Apply'
    TabOrder = 9
    OnClick = bnApplyClick
  end
  object bnCancel: TButton
    Left = 352
    Top = 416
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 10
    OnClick = bnCancelClick
  end
  object cbPatterning: TGroupBox
    Left = 4
    Top = 200
    Width = 333
    Height = 69
    Caption = 'Pattern detection'
    TabOrder = 11
    object stPatterningPeakParamMin: TStaticText
      Left = 88
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Range min'
      TabOrder = 0
    end
    object cbPatterningPeakParamMax: TComboBox
      Left = 168
      Top = 40
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 1
      Text = '10'
      Items.Strings = (
        '1'
        '2'
        '3'
        '4'
        '5'
        '6'
        '7'
        '8'
        '9'
        '10'
        '11'
        '12'
        '13'
        '14'
        '15'
        '16')
    end
    object stPatterningPeakType: TStaticText
      Left = 8
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Type'
      TabOrder = 2
    end
    object cbPatterningPeakType: TComboBox
      Left = 8
      Top = 40
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 3
      Text = 'TL above'
      Items.Strings = (
        'TL above'
        'TL below')
    end
    object cbPatterningPeakParamMin: TComboBox
      Left = 88
      Top = 40
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 4
      Text = '5'
      Items.Strings = (
        '1'
        '2'
        '3'
        '4'
        '5'
        '6'
        '7'
        '8'
        '9'
        '10'
        '11'
        '12'
        '13'
        '14'
        '15'
        '16')
    end
    object stPatterningPeakParamSpace: TStaticText
      Left = 248
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Space [ms]'
      TabOrder = 5
    end
    object stPatterningPeakParamMax: TStaticText
      Left = 168
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Range max'
      TabOrder = 6
    end
    object cbPatterningPeakParamSpace: TComboBox
      Left = 248
      Top = 40
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 7
      Text = '144'
      Items.Strings = (
        '72'
        '80'
        '88'
        '96'
        '104'
        '112'
        '120'
        '128'
        '136'
        '144'
        '152'
        '160')
    end
  end
  object gbMiscellaneous: TGroupBox
    Left = 340
    Top = 4
    Width = 333
    Height = 69
    Caption = 'Miscellaneous'
    TabOrder = 12
    object stMiscellaneousPort: TStaticText
      Left = 8
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Port'
      TabOrder = 0
    end
    object cbMiscellaneousPort: TComboBox
      Left = 8
      Top = 40
      Width = 77
      Height = 21
      ItemHeight = 13
      TabOrder = 1
      Text = 'COM3'
      OnChange = cbPortChange
      Items.Strings = (
        'COM1'
        'COM2'
        'COM3'
        'COM4'
        'COM5'
        'COM6'
        'COM7'
        'COM8'
        'COM9'
        'COM10'
        'COM11'
        'COM12'
        'COM13'
        'COM14'
        'COM15'
        'COM16'
        'COM17'
        'COM18'
        'COM19'
        'COM20'
        'COM21'
        'COM22'
        'COM23'
        'COM24'
        'COM25'
        'COM26'
        'COM27'
        'COM28'
        'COM29'
        'COM30'
        'COM31'
        'COM32')
    end
    object stMiscellaneousFilterType: TStaticText
      Left = 88
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Filter type'
      Enabled = False
      TabOrder = 2
    end
    object cbMiscellaneousFilterType: TComboBox
      Left = 88
      Top = 40
      Width = 77
      Height = 21
      Enabled = False
      ItemHeight = 13
      TabOrder = 3
      Text = 'FFT'
      Items.Strings = (
        'FFT')
    end
    object stMiscellaneousFilterFc1: TStaticText
      Left = 168
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Filter fc1 [Hz]'
      Enabled = False
      TabOrder = 4
    end
    object cbMiscellaneousFilterFc1: TComboBox
      Left = 168
      Top = 40
      Width = 77
      Height = 21
      Enabled = False
      ItemHeight = 13
      TabOrder = 5
      Text = '7'
      Items.Strings = (
        '1'
        '2'
        '3'
        '4'
        '5'
        '6'
        '7'
        '8'
        '9'
        '10'
        '11'
        '12'
        '13'
        '14'
        '15'
        '16'
        '17'
        '18'
        '19'
        '20'
        '21'
        '22'
        '23'
        '24'
        '25'
        '26'
        '27'
        '28'
        '29'
        '30'
        '31'
        '32'
        '33'
        '34'
        '35'
        '36'
        '37'
        '38'
        '39'
        '40'
        '41'
        '42'
        '43'
        '44'
        '45'
        '46'
        '47'
        '48'
        '49'
        '50')
    end
    object stMiscellaneousFilterFc2: TStaticText
      Left = 248
      Top = 16
      Width = 77
      Height = 19
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkTile
      Caption = 'Filter fc2 [Hz]'
      Enabled = False
      TabOrder = 6
    end
    object cbMiscellaneousFilterFc2: TComboBox
      Left = 248
      Top = 40
      Width = 77
      Height = 21
      Enabled = False
      ItemHeight = 13
      TabOrder = 7
      Text = '13'
      Items.Strings = (
        '1'
        '2'
        '3'
        '4'
        '5'
        '6'
        '7'
        '8'
        '9'
        '10'
        '11'
        '12'
        '13'
        '14'
        '15'
        '16'
        '17'
        '18'
        '19'
        '20'
        '21'
        '22'
        '23'
        '24'
        '25'
        '26'
        '27'
        '28'
        '29'
        '30'
        '31'
        '32'
        '33'
        '34'
        '35'
        '36'
        '37'
        '38'
        '39'
        '40'
        '41'
        '42'
        '43'
        '44'
        '45'
        '46'
        '47'
        '48'
        '49'
        '50')
    end
  end
  object cbSoundType: TComboBox
    Left = 452
    Top = 368
    Width = 61
    Height = 21
    ItemHeight = 13
    TabOrder = 13
    Text = 'Begin'
    OnChange = cbSoundTypeChange
    Items.Strings = (
      'Begin'
      'Relax'
      'Shock')
  end
  object edSoundFileName: TEdit
    Left = 540
    Top = 368
    Width = 109
    Height = 21
    TabOrder = 14
  end
  object stSoundFileName: TStaticText
    Left = 452
    Top = 344
    Width = 221
    Height = 19
    Alignment = taCenter
    AutoSize = False
    BevelKind = bkTile
    Caption = 'Sound file name'
    TabOrder = 15
  end
  object dlgOpenOutputFile: TOpenDialog
    Filter = 'SmartStim files (*.ss)|*.ss|All files (*.*)|*.*'
    Left = 4
    Top = 400
  end
  object dlgOpenInputFile: TOpenDialog
    Filter = 'SmartStim (*.ss)|*.ss|All files (*.*)|*.*'
    Left = 36
    Top = 400
  end
  object dlgOpenSoundFile: TOpenDialog
    Filter = 'Sound (*.wav)|*.wav'
    Left = 68
    Top = 400
  end
end
