//---------------------------------------------------------------------------

#ifndef UnitSifreUretH
#define UnitSifreUretH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------

// Author: Halil Kemal TAÞKIN
// Web: http://hkt.me

class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TComboBox *cmbSifre;
	TLabel *Label3;
	TEdit *edtSifre;
	TButton *btnUret;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnUretClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
