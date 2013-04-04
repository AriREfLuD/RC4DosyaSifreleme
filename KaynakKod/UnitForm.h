//---------------------------------------------------------------------------

#ifndef UnitFormH
#define UnitFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------

// Author: Halil Kemal TAÞKIN
// Web: http://hkt.me

class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TOpenPictureDialog *OpenPictureDialog1;
	TOpenDialog *OpenDialog1;
	TMainMenu *MainMenu1;
	TMenuItem *Dosya1;
	TMenuItem *Dosyaifrele1;
	TMenuItem *ifrelenmiDosyayz1;
	TMenuItem *ResimBMPifrele1;
	TMenuItem *ifrelenmiResmiBMPz1;
	TMenuItem *N1;
	TMenuItem *k1;
	TMenuItem *Yardm1;
	TMenuItem *Hakknda1;
	TLabel *lblDosyaAdi;
	TLabel *Label5;
	TLabel *lblZorlukSeviyesi;
	TLabel *lblSayac;
	TLabel *Label3;
	TLabel *Label2;
	TLabel *Label1;
	TButton *btnSifrele;
	TButton *btnEncKaydet;
	TRadioButton *rdbSifreliDosyaSec;
	TRadioButton *rdbOtomatikDosya;
	TProgressBar *ProgressBar1;
	TButton *btnSifreSec;
	TEdit *edtSifreTekrar;
	TEdit *edtSifre;
	TLabel *lblHedefDosya;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TTabSheet *TabSheet4;
	TTabSheet *TabSheet5;
	TProgressBar *ProgressBarEncrypt;
	TLabel *lblIlerleme;
	TLabel *lblDecryptDosya;
	TLabel *Label7;
	TLabel *Label8;
	TEdit *edtDecryptSifre;
	TLabel *Label6;
	TButton *btnSifreCoz;
	TButton *btnDecryptKaydet;
	TRadioButton *rdbDecryptElleSecim;
	TRadioButton *rdbDecryptOto;
	TLabel *lblDecryptHedefDosya;
	TProgressBar *ProgressBarDecrypt;
	TLabel *lblIlerlemedecrypt;
	TSaveDialog *SaveDialog1;
	TLabel *lblResimDosya;
	TLabel *Label10;
	TLabel *Label11;
	TEdit *edtResimSifre;
	TImage *Image1;
	TButton *btnResimSifrele;
	TImage *Image2;
	TLabel *Label4;
	TLabel *Label9;
	TImage *Image4;
	TLabel *Label12;
	TLabel *Label13;
	TButton *btnResimCoz;
	TImage *Image3;
	TEdit *edtResimCozSifre;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *lblResimCozDosya;
	TImage *Image5;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	void __fastcall Hakknda1Click(TObject *Sender);
	void __fastcall Dosyaifrele1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall edtSifreChange(TObject *Sender);
	void __fastcall rdbOtomatikDosyaClick(TObject *Sender);
	void __fastcall rdbSifreliDosyaSecClick(TObject *Sender);
	void __fastcall btnSifreSecClick(TObject *Sender);
	void __fastcall btnSifreleClick(TObject *Sender);
	void __fastcall btnEncKaydetClick(TObject *Sender);
	void __fastcall ifrelenmiDosyayz1Click(TObject *Sender);
	void __fastcall rdbDecryptOtoClick(TObject *Sender);
	void __fastcall rdbDecryptElleSecimClick(TObject *Sender);
	void __fastcall btnSifreCozClick(TObject *Sender);
	void __fastcall btnDecryptKaydetClick(TObject *Sender);
	void __fastcall ResimBMPifrele1Click(TObject *Sender);
	void __fastcall btnResimSifreleClick(TObject *Sender);
	void __fastcall btnResimCozClick(TObject *Sender);
	void __fastcall ifrelenmiResmiBMPz1Click(TObject *Sender);
	void __fastcall k1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	int Zorluk(UnicodeString str);
	bool VarMi(UnicodeString bunda,UnicodeString bundan);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
