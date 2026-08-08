[Setup]
AppName=SAPI-SAM
AppVersion=1.0
DefaultDirName=C:\SAM
DefaultGroupName=SAPI-SAM
OutputDir=.
OutputBaseFilename=SAPI-SAM
Compression=lzma
SolidCompression=yes
PrivilegesRequired=admin

[Files]
Source: "sam.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "SamSapi32.dll"; DestDir: "{app}"; Flags: ignoreversion

Source: "SamSapi64.dll"; DestDir: "{app}"; Check: IsX64; Flags: ignoreversion

[Registry]--
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Speech\Voices\Tokens\Software Automatic Mouth"; ValueType: string; ValueName: ""; ValueData: "Software Automatic Mouth (SAM)"; Check: IsX64
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Speech\Voices\Tokens\Software Automatic Mouth"; ValueType: string; ValueName: "CLSID"; ValueData: "{{A9234856-7812-4ABC-9123-ABCDEF123456}}"; Check: IsX64

Root: HKLM; Subkey: "SOFTWARE\Microsoft\Speech\Voices\Tokens\Software Automatic Mouth\Attributes"; ValueType: string; ValueName: "Name"; ValueData: "Software Automatic Mouth"; Check: IsX64
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Speech\Voices\Tokens\Software Automatic Mouth\Attributes"; ValueType: string; ValueName: "Language"; ValueData: "409"; Check: IsX64
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Speech\Voices\Tokens\Software Automatic Mouth\Attributes"; ValueType: string; ValueName: "Gender"; ValueData: "Male"; Check: IsX64
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Speech\Voices\Tokens\Software Automatic Mouth\Attributes"; ValueType: string; ValueName: "Age"; ValueData: "Adult"; Check: IsX64
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Speech\Voices\Tokens\Software Automatic Mouth\Attributes"; ValueType: string; ValueName: "Vendor"; ValueData: "Commodor"; Check: IsX64

Root: HKLM; Subkey: "SOFTWARE\WOW6432Node\Microsoft\SPEECH\Voices\Tokens\Software Automatic Mouth"; ValueType: string; ValueName: ""; ValueData: "Software Automatic Mouth (SAM)"; Check: IsX64
Root: HKLM; Subkey: "SOFTWARE\WOW6432Node\Microsoft\SPEECH\Voices\Tokens\Software Automatic Mouth"; ValueType: string; ValueName: "CLSID"; ValueData: "{{A9234856-7812-4ABC-9123-ABCDEF123456}}"; Check: IsX64

Root: HKLM; Subkey: "SOFTWARE\WOW6432Node\Microsoft\SPEECH\Voices\Tokens\Software Automatic Mouth\Attributes"; ValueType: string; ValueName: "Name"; ValueData: "Software Automatic Mouth"; Check: IsX64
Root: HKLM; Subkey: "SOFTWARE\WOW6432Node\Microsoft\SPEECH\Voices\Tokens\Software Automatic Mouth\Attributes"; ValueType: string; ValueName: "Language"; ValueData: "409"; Check: IsX64
Root: HKLM; Subkey: "SOFTWARE\WOW6432Node\Microsoft\SPEECH\Voices\Tokens\Software Automatic Mouth\Attributes"; ValueType: string; ValueName: "Gender"; ValueData: "Male"; Check: IsX64
Root: HKLM; Subkey: "SOFTWARE\WOW6432Node\Microsoft\SPEECH\Voices\Tokens\Software Automatic Mouth\Attributes"; ValueType: string; ValueName: "Age"; ValueData: "Adult"; Check: IsX64
Root: HKLM; Subkey: "SOFTWARE\WOW6432Node\Microsoft\Speech\Voices\Tokens\Software Automatic Mouth\Attributes"; ValueType: string; ValueName: "Vendor"; ValueData: "Commodor"; Check: IsX64
-
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Speech\Voices\Tokens\Software Automatic Mouth"; ValueType: string; ValueName: ""; ValueData: "Software Automatic Mouth (SAM)"; Check: not IsX64
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Speech\Voices\Tokens\Software Automatic Mouth"; ValueType: string; ValueName: "CLSID"; ValueData: "{{A9234856-7812-4ABC-9123-ABCDEF123456}}"; Check: not IsX64

Root: HKLM; Subkey: "SOFTWARE\Microsoft\Speech\Voices\Tokens\Software Automatic Mouth\Attributes"; ValueType: string; ValueName: "Name"; ValueData: "Software Automatic Mouth"; Check: not IsX64
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Speech\Voices\Tokens\Software Automatic Mouth\Attributes"; ValueType: string; ValueName: "Language"; ValueData: "409"; Check: not IsX64
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Speech\Voices\Tokens\Software Automatic Mouth\Attributes"; ValueType: string; ValueName: "Gender"; ValueData: "Male"; Check: not IsX64
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Speech\Voices\Tokens\Software Automatic Mouth\Attributes"; ValueType: string; ValueName: "Age"; ValueData: "Adult"; Check: not IsX64
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Speech\Voices\Tokens\Software Automatic Mouth\Attributes"; ValueType: string; ValueName: "Vendor"; ValueData: "Commodor"; Check: not IsX64

Root: HKCR; Subkey: "CLSID\{{A9234856-7812-4ABC-9123-ABCDEF123456}}"; ValueType: string; ValueName: ""; ValueData: "SamTTSEngine Class"

Root: HKCR; Subkey: "CLSID\{{A9234856-7812-4ABC-9123-ABCDEF123456}}\InprocServer32"; ValueType: string; ValueName: ""; ValueData: "{{app}}\SamSapi64.dll"; Check: IsX64
Root: HKCR; Subkey: "CLSID\{{A9234856-7812-4ABC-9123-ABCDEF123456}}\InprocServer32"; ValueType: string; ValueName: "ThreadingModel"; ValueData: "Both"; Check: IsX64

Root: HKLM; Subkey: "SOFTWARE\WOW6432Node\Classes\CLSID\{{A9234856-7812-4ABC-9123-ABCDEF123456}}"; ValueType: string; ValueName: ""; ValueData: "SamTTSEngine Class"; Check: IsX64
Root: HKLM; Subkey: "SOFTWARE\WOW6432Node\Classes\CLSID\{{A9234856-7812-4ABC-9123-ABCDEF123456}}\InprocServer32"; ValueType: string; ValueName: ""; ValueData: "{{app}}\SamSapi32.dll"; Check: IsX64
Root: HKLM; Subkey: "SOFTWARE\WOW6432Node\Classes\CLSID\{{A9234856-7812-4ABC-9123-ABCDEF123456}}\InprocServer32"; ValueType: string; ValueName: "ThreadingModel"; ValueData: "Both"; Check: IsX64

Root: HKCR; Subkey: "CLSID\{{A9234856-7812-4ABC-9123-ABCDEF123456}}\InprocServer32"; ValueType: string; ValueName: ""; ValueData: "{{app}}\SamSapi32.dll"; Check: not IsX64
Root: HKCR; Subkey: "CLSID\{{A9234856-7812-4ABC-9123-ABCDEF123456}}\InprocServer32"; ValueType: string; ValueName: "ThreadingModel"; ValueData: "Both"; Check: not IsX64

Root: HKLM; Subkey: "SOFTWARE\Microsoft\Speech\Voices"; ValueType: string; ValueName: "DefaultToken"; ValueData: "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Speech\Voices\Tokens\Software Automatic Mouth"; Check: IsX64 and MakeDefaultChecked; Flags: uninsdeletevalue
Root: HKLM; Subkey: "SOFTWARE\WOW6432Node\Microsoft\Speech\Voices"; ValueType: string; ValueName: "DefaultToken"; ValueData: "HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\Microsoft\Speech\Voices\Tokens\Software Automatic Mouth"; Check: IsX64 and MakeDefaultChecked; Flags: uninsdeletevalue
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Speech\Voices"; ValueType: string; ValueName: "DefaultToken"; ValueData: "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Speech\Voices\Tokens\Software Automatic Mouth"; Check: not IsX64 and MakeDefaultChecked; Flags: uninsdeletevalue

[Code]
var
  DefaultVoicePage: TInputOptionWizardPage;
  DefaultCheckbox: TNewCheckBox;

procedure InitializeWizard;
begin
  DefaultVoicePage := CreateInputOptionPage(wpSelectDir,
    'Configure Default Voice', 'Would you like to set SAM as your default system voice?',
    'Please choose whether you want SAM to be your primary text-to-speech voice.',
    True, False);

  DefaultVoicePage.Add('Make SAM the default system speech voice');
  DefaultVoicePage.Values[0] := False;
end;

function NextButtonClick(CurPageID: Integer): Boolean;
begin
  Result := True;
  
  if CurPageID = DefaultVoicePage.ID then
  begin
    if not DefaultVoicePage.Values[0] then
    begin
      MsgBox('Warning: You chose not to set SAM as the default voice. It cannot be selected as default in another way automatically later without manual registry edits.', mbInformation, MB_OK);
    end;
  end;
end;

function MakeDefaultChecked: Boolean;
begin
  Result := DefaultVoicePage.Values[0];
end;