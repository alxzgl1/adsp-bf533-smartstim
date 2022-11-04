//---------------------------------------------------------------------------
#ifndef UConnectionH
#define UConnectionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TConnection : public TThread
{            
private:
protected:
	void __fastcall Execute();
public:
	__fastcall TConnection(bool CreateSuspended);
  void __fastcall SynchronizeDrawPlot();
  void __fastcall SynchronizeClearPlot();
  void __fastcall SynchronizeOnlineData();
  void __fastcall SynchronizeControlItems();
  void __fastcall SynchronizeTrainingTime();
  void __fastcall SynchronizeModeDependentValue();
  bool __fastcall OpenSerialPort();
  void __fastcall ClearSerialPort();
  HANDLE m_hCOM;
  // FILE for online mode
  FILE *m_pOnlineProcessingStream;
  FILE *m_pOfflineProcessingStream;

  // Test
  int m_nMyVar;
  void __fastcall MyTextOut(void);
};
//---------------------------------------------------------------------------
#endif
