//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include<memory>
#include"coordinate_system.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *coordinates_label;
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormMouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall FormMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);

private:	// User declarations
	std::unique_ptr<coordinate_system> coord_system;
	void update_coordinates_label(const int X, const int Y);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
