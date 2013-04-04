// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitForm.h"
#include "UnitRC4.h"
#include "Hakkinda.h"
#include "UnitSifreUret.h"
// ---------------------------------------------------------------------------

// Author: Halil Kemal TA�KIN
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
	lblSayac->Caption = "�ifre Uzunlu�u: " + IntToStr(edtSifre->Text.Length());
	if (edtSifre->Text.Length() > 255) {
		edtSifre->Text = edtSifre->Text.SubString(0,255);
		ShowMessage("�ifre 255 karakterden uzun olamaz!");
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

	UnicodeString kucuk = u"abc�defg�h�ijklmno�prs�tu�vyzqwx";
	UnicodeString buyuk = u"ABC�DEFG�HI�JKLMNO�PRS�TU�VYZQWX";
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

	// �ifre kutusu bo�mu
	if (edtSifre->Text.Length() == 0) {
		ShowMessage("L�tfen bir �ifre yaz�n!");
		edtSifre->SetFocus();
		return;
	}
	// �ifreler e�it mi
	if (edtSifre->Text != edtSifreTekrar->Text) {
		ShowMessage("�ifreler uyu�muyor. L�tfen kontrol edin!");
		edtSifre->SetFocus();
		return;
	}

	// hedef dosya se�ili mi?
	if (lblHedefDosya->Caption == "") {
		ShowMessage("L�tfen �ifreli dosyan�n kaydedilece�i yeri se�in!");
		return;
	}
	ProgressBarEncrypt->Style = pbstMarquee;
	rc4->DosyaSifrele(AnsiString(lblDosyaAdi->Caption).c_str(),
		AnsiString(lblHedefDosya->Caption).c_str(),
		AnsiString(edtSifre->Text).c_str());
	ProgressBarEncrypt->Style = pbstNormal;
	lblIlerleme->Caption = "�ifreli dosya kaydedildi!";
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::btnEncKaydetClick(TObject *Sender) {
	SaveDialog1->DefaultExt = "hkt";
	SaveDialog1->FileName = "�ifreli Dosya";
	SaveDialog1->Filter = "�ifreli Dosyalar|*.hkt|B�t�n Dosyalar|*.*";
	if (SaveDialog1->Execute()) {
		lblHedefDosya->Caption = SaveDialog1->FileName;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::ifrelenmiDosyayz1Click(TObject *Sender) {
	OpenDialog1->Filter = "�ifreli Dosyalar|*.hkt";
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
	// ba�la
	if (edtDecryptSifre->Text.Length() == 0) {
		ShowMessage("L�tfen �ifreyi yaz�n!");
		edtDecryptSifre->SetFocus();
		return;
	}
	if (lblDecryptHedefDosya->Caption == "") {
		ShowMessage("L�tfen ��z�lm�� dosyan�n kaydedilece�i yeri se�in!");
		return;
	}
	ProgressBarDecrypt->Style = pbstMarquee;
	rc4->DosyaSifrele(AnsiString(lblDecryptDosya->Caption).c_str(),
		AnsiString(lblDecryptHedefDosya->Caption).c_str(),
		AnsiString(edtDecryptSifre->Text).c_str());
	ProgressBarDecrypt->Style = pbstNormal;
	lblIlerlemedecrypt->Caption = "Dosya ba�ar�yla ��z�ld�!";

}
// ---------------------------------------------------------------------------

void __fastcall TForm1::btnDecryptKaydetClick(TObject *Sender) {
	SaveDialog1->DefaultExt = "txt";
	SaveDialog1->FileName = "��z�lm�� Dosya" + OpenDialog1->FileName.SubString
		(OpenDialog1->FileName.Length() - 7, 4);
	SaveDialog1->Filter = "B�t�n Dosyalar|*.*";
	if (SaveDialog1->Execute()) {
		lblDecryptHedefDosya->Caption = SaveDialog1->FileName;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::ResimBMPifrele1Click(TObject *Sender) {
	OpenDialog1->Filter = "BMP Resim Dosyalar�|*.bmp";
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
	// ba�la
	if (edtResimSifre->Text.Length() == 0) {
		ShowMessage("L�tfen �ifre yaz�n!");
		edtResimSifre->SetFocus();
		return;
	}

	// kay�t yerini sor

	SaveDialog1->Filter = "BMP Resim Dosyalar�|*.bmp";
	SaveDialog1->DefaultExt = "bmp";
	SaveDialog1->FileName = lblResimDosya->Caption.SubString(0,
		lblResimDosya->Caption.Length() - 4) + " �ifreli.bmp";
	if (SaveDialog1->Execute()) {

		// resmi �ifrele
		rc4->BMPSifrele(AnsiString(lblResimDosya->Caption).c_str(),
			AnsiString(SaveDialog1->FileName).c_str(),
			AnsiString(edtResimSifre->Text).c_str());

		// �ifreli resmi y�kle
		Image2->Picture->LoadFromFile(SaveDialog1->FileName);
	}

	SaveDialog1->Filter = "";
	SaveDialog1->DefaultExt = "";
	SaveDialog1->FileName = "";

}
// ---------------------------------------------------------------------------

void __fastcall TForm1::btnResimCozClick(TObject *Sender) {
	// ba�la
	if (edtResimCozSifre->Text.Length() == 0) {
		ShowMessage("L�tfen �ifre yaz�n!");
		edtResimCozSifre->SetFocus();
		return;
	}

	// kay�t yerini sor

	SaveDialog1->Filter = "BMP Resim Dosyalar�|*.bmp";
	SaveDialog1->DefaultExt = "bmp";
	SaveDialog1->FileName = lblResimCozDosya->Caption.SubString(0,
		lblResimCozDosya->Caption.Length() - 12) + ".bmp";
	if (SaveDialog1->Execute()) {

		// resmi �ifrele
		rc4->BMPSifrele(AnsiString(lblResimCozDosya->Caption).c_str(),
			AnsiString(SaveDialog1->FileName).c_str(),
			AnsiString(edtResimCozSifre->Text).c_str());

		// �ifreli resmi y�kle
		Image4->Picture->LoadFromFile(SaveDialog1->FileName);
	}

	SaveDialog1->Filter = "";
	SaveDialog1->DefaultExt = "";
	SaveDialog1->FileName = "";
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::ifrelenmiResmiBMPz1Click(TObject *Sender) {
	OpenDialog1->Filter = "BMP Resim Dosyalar�|*.bmp";
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

