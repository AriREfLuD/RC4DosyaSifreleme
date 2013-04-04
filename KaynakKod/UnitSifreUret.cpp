// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitSifreUret.h"
#include "UnitForm.h"
// ---------------------------------------------------------------------------

// Author: Halil Kemal TAÞKIN
// Web: http://hkt.me

#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

// ---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner) : TForm(Owner) {
}
// ---------------------------------------------------------------------------

void __fastcall TForm2::FormCreate(TObject *Sender) {
	for (int i = 8; i < 256; i++) {
		cmbSifre->Items->Add(i);
	}
	cmbSifre->ItemIndex = 2;
	Randomize();
}
// ---------------------------------------------------------------------------

void __fastcall TForm2::btnUretClick(TObject *Sender) {

	char* alfabe =
		"abcdefghijklmnoprstuvyzqwxABCDEFGHIJKLMNOPRSTUVYZQWX0123456789!'^+%&/()=?_-|}][{$#><";
	int len = strlen(alfabe);
	int uzunluk = StrToInt(cmbSifre->Items->Strings[cmbSifre->ItemIndex]);
	edtSifre->Text = "";
	for (int i = 0; i < uzunluk; i++) {
		edtSifre->Text = edtSifre->Text + alfabe[Random(len)];
	}
}
// ---------------------------------------------------------------------------
