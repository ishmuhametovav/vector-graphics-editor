//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include"Unit1.h"
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TButton *apply_button;
	TButton *cancel_button;
	TLabel *save_data_label;
	TLabel *data_size_label;
	TLabel *width_label;
	TLabel *height_label;
	TEdit *width_edit;
	TEdit *height_edit;
	void __fastcall cancel_buttonClick(TObject *Sender);
	void __fastcall apply_buttonClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
	void update_file_labels();
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
