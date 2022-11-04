//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UMain.cpp", fmMain);
USEFORM("USettings.cpp", fmSettings);
USEFORM("USpectrum.cpp", fmSpectrum);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->Title = "SmartStim";
		Application->CreateForm(__classid(TfmMain), &fmMain);
     Application->CreateForm(__classid(TfmSettings), &fmSettings);
     Application->CreateForm(__classid(TfmSpectrum), &fmSpectrum);
     Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
