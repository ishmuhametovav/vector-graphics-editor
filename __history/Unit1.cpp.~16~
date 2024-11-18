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
	: TForm(Owner), coord_system(std::make_unique<coordinate_system>()), shape_drawing(false),
		colors{clWhite, clYellow, clGreen, clMaroon, clRed, clFuchsia, clGray, clBlue, clPurple, clBlack}
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

	if(tool_group->ItemIndex == -1) return;
	double x = coord_system->to_coordx(X);
	double y = coord_system->to_coordy(Y);

	int width = width_track_bar->Position;
	TColor pen_color = colors[selected_colors_group->Items->Items[0]->ImageIndex];
	TColor brush_color = colors[selected_colors_group->Items->Items[1]->ImageIndex];

	if(tool_group->ItemIndex == 0) shapes.push_back(new pencil(x, y, x, y, width, pen_color));
	if(tool_group->ItemIndex == 1) shapes.push_back(new line(x, y, x, y, width, pen_color));
	if(tool_group->ItemIndex == 2) shapes.push_back(new ellipse(x, y, 1, 1, width, pen_color, brush_color));
	if(tool_group->ItemIndex == 3) shapes.push_back(new rectangle(x, y, x, y, width, pen_color, brush_color));
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




void __fastcall TForm1::FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight,
          bool &Resize)
{
	panel->Top = (NewHeight - panel->Height) / 2 - 30;
	panel->Left = 8;
}
//---------------------------------------------------------------------------




void __fastcall TForm1::color_groupButtonClicked(TObject *Sender, int Index)
{
	int selected_index = selected_colors_group->ItemIndex;
	selected_colors_group->Items->Items[selected_index]->ImageIndex = Index;
}
//---------------------------------------------------------------------------

