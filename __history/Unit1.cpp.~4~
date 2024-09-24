//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

void TForm1::update_coordinates_label(const int X, const int Y)
{
	double x = coord_system->to_coordx(X);
	double y = coord_system->to_coordy(Y);
	coordinates_label->Caption = String(x) + " : " + String(y);
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner), coord_system(std::make_unique<coordinate_system>())
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)

{
	update_coordinates_label(X, Y);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormResize(TObject *Sender)
{
	coordinates_label->Left = ClientWidth - coordinates_label->Width - 30;
	coordinates_label->Top = ClientHeight - coordinates_label->Height - 10;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormMouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
		  bool &Handled)
{
	coord_system->set_scale(coord_system->get_scale() - 0.1);
	TPoint localPos = ScreenToClient(MousePos);
	update_coordinates_label(localPos.X, localPos.Y);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
		  bool &Handled)
{
	coord_system->set_scale(coord_system->get_scale() + 0.1);
	TPoint localPos = ScreenToClient(MousePos);
	update_coordinates_label(localPos.X, localPos.Y);
}
//---------------------------------------------------------------------------

