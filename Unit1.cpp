//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

void TForm1::update_status_bar(const int X, const int Y)
{
	double x = coord_system->to_coordx(X);
	double y = coord_system->to_coordy(Y);
	status_bar->Panels->Items[0]->Text = String().sprintf(L"   scale: %.1f%", coord_system->get_scale() * 100);
	status_bar->Panels->Items[1]->Text = String().sprintf(L"%.1f : %.1f     ", x, y);
}

void TForm1::draw_shapes()
{
	for(auto& i : shapes)
		i->draw(Canvas, coord_system.get());
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner), coord_system(std::make_unique<coordinate_system>()), shape_drawing(false)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)

{
	update_status_bar(X, Y);

	if(shape_drawing)
	{
		double x = coord_system->to_coordx(X);
		double y = coord_system->to_coordy(Y);
		shapes.back()->update_on_drag(x, y);
		Invalidate();
	}
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormMouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
		  bool &Handled)
{
	coord_system->set_scale(coord_system->get_scale() - 0.1);
	TPoint localPos = ScreenToClient(MousePos);
	update_status_bar(localPos.X, localPos.Y);
	Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
		  bool &Handled)
{
	coord_system->set_scale(coord_system->get_scale() + 0.1);
	TPoint localPos = ScreenToClient(MousePos);
	update_status_bar(localPos.X, localPos.Y);
    Invalidate();
}
//---------------------------------------------------------------------------




void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	double x = coord_system->to_coordx(X);
	double y = coord_system->to_coordy(Y);
	shapes.push_back(new pencil(x, y, x, y));
	shape_drawing = true;

}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormPaint(TObject *Sender)
{
	draw_shapes();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	shape_drawing = false;
}
//---------------------------------------------------------------------------

