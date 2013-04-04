//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Hakkinda.h"
//--------------------------------------------------------------------- 

// Author: Halil Kemal TAÞKIN
// Web: http://hkt.me

#pragma resource "*.dfm"
TAboutBox *AboutBox;
//--------------------------------------------------------------------- 
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TAboutBox::OKButtonClick(TObject *Sender)
{
this->Hide();
}
//---------------------------------------------------------------------------

