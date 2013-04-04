// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitForm.h"
#include "UnitRC4.h"
#include "Hakkinda.h"
#include "UnitSifreUret.h"
// ---------------------------------------------------------------------------

// Author: Halil Kemal TAÞKIN
// Web: http://hkt.me

#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
RC4 *rc4;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {

}
// ---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender) {
	edtSifre->Text = "";
	edtSifre->PasswordChar = '*';
	edtDecryptSifre->PasswordChar = '*';
	edtSifreTekrar->Text = "";
	edtSifreTekrar->PasswordChar = '*';
	edtResimSifre->PasswordChar = '*';
	edtResimCozSifre->PasswordChar = '*';
	lblSayac->Caption = "";
	btnEncKaydet->Visible = false;
	btnDecryptKaydet->Visible = false;

	lblIlerleme->Caption = "";
	lblIlerlemedecrypt->Caption = "";

	PageControl1->ActivePageIndex = 0;

	btnSifrele->Enabled = false;
	btnSifreCoz->Enabled = false;
	btnResimSifrele->Enabled = false;
	btnResimCoz->Enabled = false;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Hakknda1Click(TObject *Sender) {
	AboutBox->Show();
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Dosyaifrele1Click(TObject *Sender) {
	if (OpenDialog1->Execute()) {
		lblDosyaAdi->Caption = OpenDialog1->FileName;
		if (rdbOtomatikDosya->Checked) {
			lblHedefDosya->Caption = OpenDialog1->FileName + ".hkt";
		}
		btnSifrele->Enabled = true;
		PageControl1->ActivePageIndex = 1;
	}

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::edtSifreChange(TObject *Sender) {
	lblSayac->Caption = "Þifre Uzunluðu: " + IntToStr(edtSifre->Text.Length());
	if (edtSifre->Text.Length() > 255) {
		edtSifre->Text = edtSifre->Text.SubString(0,255);
		ShowMessage("Þifre 255 karakterden uzun olamaz!");
		return;
	}
	ProgressBar1->Position = Zorluk(edtSifre->Text);

}
// ---------------------------------------------------------------------------

int TForm1::Zorluk(UnicodeString str) {
	if (str.Length() == 0)
		return 0;

	if (str.Length() < 6)
		return 10;

	if (str.Length() < 9)
		return 25;

	UnicodeString kucuk = u"abcçdefgðhýijklmnoöprsþtuüvyzqwx";
	UnicodeString buyuk = u"ABCÇDEFGÐHIÝJKLMNOÖPRSÞTUÜVYZQWX";
	UnicodeString rakam = u"0123456789";
	UnicodeString ozel = u"!'^+%&/()=?_-|}][{$#><";

	if (VarMi(str, kucuk) && VarMi(str, buyuk) && VarMi(str,
		rakam) && VarMi(str, ozel)) {
		return 100;
	}
	else if (VarMi(str, kucuk) && VarMi(str, buyuk) && VarMi(str, rakam)) {
		return 90;
	}
	else if (VarMi(str, kucuk) && VarMi(str, buyuk)) {
		return 80;
	}
	else if (VarMi(str, kucuk) || VarMi(str, buyuk) || VarMi(str, ozel) ||
		VarMi(str, rakam)) {
		return 70;
	}

	if (str.Length() > 20) {
		return 95;
	}

	return 0;

}

bool TForm1::VarMi(UnicodeString bunda1, UnicodeString bundan1) {

	char* bunda = AnsiString(bunda1).c_str();
	char* bundan = AnsiString(bundan1).c_str();

	for (int i = 0; i < bunda1.Length(); i++) {

		for (int j = 0; j < bundan1.Length(); j++) {
			if (bunda[i] == bundan[j])
				return true;
		}
	}
	return false;
}

// ---------------------------------------------------------------------------

void __fastcall TForm1::rdbOtomatikDosyaClick(TObject *Sender) {
	if (rdbOtomatikDosya->Checked) {
		btnEncKaydet->Visible = false;
		if (lblDosyaAdi->Caption.Length() > 0) {
			lblHedefDosya->Caption = OpenDialog1->FileName + ".hkt";
		}
		else {
			lblHedefDosya->Caption = "";
		}

	}

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::rdbSifreliDosyaSecClick(TObject *Sender) {
	if (rdbSifreliDosyaSec->Checked) {
		lblHedefDosya->Caption = "";
		lblHedefDosya->Caption = "";
		btnEncKaydet->Visible = true;
	}

}
// ---------------------------------------------------------------------------

void __fastcall TForm1::btnSifreSecClick(TObject *Sender) {
	Form2->Show();
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::btnSifreleClick(TObject *Sender) {

	// þifre kutusu boþmu
	if (edtSifre->Text.Length() == 0) {
		ShowMessage("Lütfen bir þifre yazýn!");
		edtSifre->SetFocus();
		return;
	}
	// þifreler eþit mi
	if (edtSifre->Text != edtSifreTekrar->Text) {
		ShowMessage("Þifreler uyuþmuyor. Lütfen kontrol edin!");
		edtSifre->SetFocus();
		return;
	}

	// hedef dosya seçili mi?
	if (lblHedefDosya->Caption == "") {
		ShowMessage("Lütfen þifreli dosyanýn kaydedileceði yeri seçin!");
		return;
	}
	ProgressBarEncrypt->Style = pbstMarquee;
	rc4->DosyaSifrele(AnsiString(lblDosyaAdi->Caption).c_str(),
		AnsiString(lblHedefDosya->Caption).c_str(),
		AnsiString(edtSifre->Text).c_str());
	ProgressBarEncrypt->Style = pbstNormal;
	lblIlerleme->Caption = "Þifreli dosya kaydedildi!";
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::btnEncKaydetClick(TObject *Sender) {
	SaveDialog1->DefaultExt = "hkt";
	SaveDialog1->FileName = "Þifreli Dosya";
	SaveDialog1->Filter = "Þifreli Dosyalar|*.hkt|Bütün Dosyalar|*.*";
	if (SaveDialog1->Execute()) {
		lblHedefDosya->Caption = SaveDialog1->FileName;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::ifrelenmiDosyayz1Click(TObject *Sender) {
	OpenDialog1->Filter = "Þifreli Dosyalar|*.hkt";
	if (OpenDialog1->Execute()) {
		lblDecryptDosya->Caption = OpenDialog1->FileName;
		if (rdbDecryptOto->Checked) {
			lblDecryptHedefDosya->Caption =
				OpenDialog1->FileName.SubString(0,
				OpenDialog1->FileName.Length() - 4);
		}
		btnSifreCoz->Enabled = true;
		PageControl1->ActivePageIndex = 2;
	}
	OpenDialog1->Filter = "";
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::rdbDecryptOtoClick(TObject *Sender) {
	if (rdbDecryptOto->Checked) {
		btnDecryptKaydet->Visible = false;
		if (lblDecryptDosya->Caption.Length() > 0) {
			lblDecryptHedefDosya->Caption =
				OpenDialog1->FileName.SubString(0,
				OpenDialog1->FileName.Length() - 4);
		}
		else {
			lblDecryptHedefDosya->Caption = "";
		}

	}
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::rdbDecryptElleSecimClick(TObject *Sender) {
	if (rdbDecryptElleSecim->Checked) {
		lblDecryptHedefDosya->Caption = "";
		lblDecryptHedefDosya->Caption = "";
		btnDecryptKaydet->Visible = true;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::btnSifreCozClick(TObject *Sender) {
	// baþla
	if (edtDecryptSifre->Text.Length() == 0) {
		ShowMessage("Lütfen þifreyi yazýn!");
		edtDecryptSifre->SetFocus();
		return;
	}
	if (lblDecryptHedefDosya->Caption == "") {
		ShowMessage("Lütfen çözülmüþ dosyanýn kaydedileceði yeri seçin!");
		return;
	}
	ProgressBarDecrypt->Style = pbstMarquee;
	rc4->DosyaSifrele(AnsiString(lblDecryptDosya->Caption).c_str(),
		AnsiString(lblDecryptHedefDosya->Caption).c_str(),
		AnsiString(edtDecryptSifre->Text).c_str());
	ProgressBarDecrypt->Style = pbstNormal;
	lblIlerlemedecrypt->Caption = "Dosya baþarýyla çözüldü!";

}
// ---------------------------------------------------------------------------

void __fastcall TForm1::btnDecryptKaydetClick(TObject *Sender) {
	SaveDialog1->DefaultExt = "txt";
	SaveDialog1->FileName = "Çözülmüþ Dosya" + OpenDialog1->FileName.SubString
		(OpenDialog1->FileName.Length() - 7, 4);
	SaveDialog1->Filter = "Bütün Dosyalar|*.*";
	if (SaveDialog1->Execute()) {
		lblDecryptHedefDosya->Caption = SaveDialog1->FileName;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::ResimBMPifrele1Click(TObject *Sender) {
	OpenDialog1->Filter = "BMP Resim Dosyalarý|*.bmp";
	if (OpenDialog1->Execute()) {
		lblResimDosya->Caption = OpenDialog1->FileName;
		Image1->Picture->LoadFromFile(OpenDialog1->FileName);
		btnResimSifrele->Enabled = true;
		PageControl1->ActivePageIndex = 3;
	}
	OpenDialog1->Filter = "";
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::btnResimSifreleClick(TObject *Sender) {
	// baþla
	if (edtResimSifre->Text.Length() == 0) {
		ShowMessage("Lütfen þifre yazýn!");
		edtResimSifre->SetFocus();
		return;
	}

	// kayýt yerini sor

	SaveDialog1->Filter = "BMP Resim Dosyalarý|*.bmp";
	SaveDialog1->DefaultExt = "bmp";
	SaveDialog1->FileName = lblResimDosya->Caption.SubString(0,
		lblResimDosya->Caption.Length() - 4) + " Þifreli.bmp";
	if (SaveDialog1->Execute()) {

		// resmi þifrele
		rc4->BMPSifrele(AnsiString(lblResimDosya->Caption).c_str(),
			AnsiString(SaveDialog1->FileName).c_str(),
			AnsiString(edtResimSifre->Text).c_str());

		// þifreli resmi yükle
		Image2->Picture->LoadFromFile(SaveDialog1->FileName);
	}

	SaveDialog1->Filter = "";
	SaveDialog1->DefaultExt = "";
	SaveDialog1->FileName = "";

}
// ---------------------------------------------------------------------------

void __fastcall TForm1::btnResimCozClick(TObject *Sender) {
	// baþla
	if (edtResimCozSifre->Text.Length() == 0) {
		ShowMessage("Lütfen þifre yazýn!");
		edtResimCozSifre->SetFocus();
		return;
	}

	// kayýt yerini sor

	SaveDialog1->Filter = "BMP Resim Dosyalarý|*.bmp";
	SaveDialog1->DefaultExt = "bmp";
	SaveDialog1->FileName = lblResimCozDosya->Caption.SubString(0,
		lblResimCozDosya->Caption.Length() - 12) + ".bmp";
	if (SaveDialog1->Execute()) {

		// resmi þifrele
		rc4->BMPSifrele(AnsiString(lblResimCozDosya->Caption).c_str(),
			AnsiString(SaveDialog1->FileName).c_str(),
			AnsiString(edtResimCozSifre->Text).c_str());

		// þifreli resmi yükle
		Image4->Picture->LoadFromFile(SaveDialog1->FileName);
	}

	SaveDialog1->Filter = "";
	SaveDialog1->DefaultExt = "";
	SaveDialog1->FileName = "";
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::ifrelenmiResmiBMPz1Click(TObject *Sender) {
	OpenDialog1->Filter = "BMP Resim Dosyalarý|*.bmp";
	if (OpenDialog1->Execute()) {
		lblResimCozDosya->Caption = OpenDialog1->FileName;
		Image3->Picture->LoadFromFile(OpenDialog1->FileName);
		btnResimCoz->Enabled = true;
		PageControl1->ActivePageIndex = 4;
	}
	OpenDialog1->Filter = "";
}
// ---------------------------------------------------------------------------
void __fastcall TForm1::k1Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

