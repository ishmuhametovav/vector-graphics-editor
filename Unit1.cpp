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
		i->draw(paint_box->Canvas, coord_system);

	if(selected_shape) selected_shape->draw_selection_box(paint_box->Canvas, coord_system);
}

void TForm1::remove_shape(const double x, const double y)
{
	shapes.remove_if([x, y](shape* s){return s->is_clicked(x,y);});
}

void TForm1::update_scrollbars()
{
	vert_scrollbar->Min = std::min(paint_box->Top, -paint_box->Top);
	//vert_scrollbar->Max = std::max(0, paint_box->ClientHeight - ClientHeight);
	vert_scrollbar->Max = vert_scrollbar->Min + paint_box->ClientHeight;
	vert_scrollbar->PageSize = paint_box->ClientHeight;

	horiz_scrollbar->Min = std::min(paint_box->Left, -paint_box->Left);
	//horiz_scrollbar->Max = std::max(0, paint_box->ClientWidth - ClientWidth);
    horiz_scrollbar->Max = horiz_scrollbar->Min + paint_box->ClientWidth;
	horiz_scrollbar->PageSize = paint_box->ClientWidth;

	if (vert_scrollbar->Position > vert_scrollbar->Max ||
		vert_scrollbar->Position < vert_scrollbar->Min) vert_scrollbar->Position = vert_scrollbar->Min;

	if (horiz_scrollbar->Position > horiz_scrollbar->Max ||
		horiz_scrollbar->Position < horiz_scrollbar->Min) horiz_scrollbar->Position = horiz_scrollbar->Min;
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner), coord_system(new coordinate_system()), original_width(361), original_height(321), selected_shape(nullptr), shape_drawing(false), shape_translation(false),
		shape_resizing(false), paint_box_resizing(false), file_modified(false), filename(""), colors{clWhite, clYellow, clGreen, clMaroon, clRed, clFuchsia, clGray, clBlue, clPurple, clBlack}
{
	file_io = new svg_io(coord_system, &shapes);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormMouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
		  bool &Handled)
{
	double old_scale = coord_system->get_scale();
	coord_system->set_scale(old_scale - 0.1);
	TPoint localPos = paint_box->ScreenToClient(MousePos);

	paint_box->Width *= (coord_system->get_scale() / old_scale);
	paint_box->Height *= (coord_system->get_scale() / old_scale);
	paint_box->Left += localPos.X * (1 - (coord_system->get_scale() / old_scale));
	paint_box->Top += localPos.Y * (1 - (coord_system->get_scale() / old_scale));

	update_status_bar(localPos.X, localPos.Y);
	update_scrollbars();
	paint_box->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
		  bool &Handled)
{
	double old_scale = coord_system->get_scale();
	coord_system->set_scale(old_scale + 0.1);

	TPoint localPos = paint_box->ScreenToClient(MousePos);
	paint_box->Width *= (coord_system->get_scale() / old_scale);
	paint_box->Height *= (coord_system->get_scale() / old_scale);
	paint_box->Left += localPos.X * (1 - (coord_system->get_scale() / old_scale));
	paint_box->Top += localPos.Y * ((1 - coord_system->get_scale() / old_scale));

	update_status_bar(localPos.X, localPos.Y);
	update_scrollbars();
	paint_box->Invalidate();
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

	if(selected_shape)
	{
		TColor pen_color = colors[selected_colors_group->Items->Items[0]->ImageIndex];
		TColor brush_color = colors[selected_colors_group->Items->Items[1]->ImageIndex];
		selected_shape->set_pen_color(pen_color);
		selected_shape->set_brush_color(brush_color);
		paint_box->Invalidate();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::paint_boxPaint(TObject *Sender)
{
	paint_box->Canvas->Brush->Color = clWhite;
	paint_box->Canvas->FillRect(paint_box->ClientRect);

	draw_shapes();
	paint_box->Canvas->Pen->Width = 1;
	paint_box->Canvas->Pen->Color = clBlack;
	paint_box->Canvas->Pen->Style = psSolid;
	paint_box->Canvas->Brush->Style = bsClear;
	paint_box->Canvas->Rectangle(0, 0, paint_box->Width, paint_box->Height);
}
//---------------------------------------------------------------------------




void __fastcall TForm1::paint_boxMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if(Button == mbLeft && X >= paint_box->Width - 5 && Y >= paint_box->Height - 5)
		paint_box_resizing = true;
	else
	{
		double x = coord_system->to_coordx(X);
		double y = coord_system->to_coordy(Y);

		selected_shape = nullptr;

		if(tool_group->ItemIndex == 5)
			remove_shape(x,y);
		else
		{
			for(auto& i : shapes)
			{
				if(i->is_clicked(x, y) || i->is_border_clicked(x, y))
				{
					if(i->is_border_clicked(x, y)) shape_resizing = true;
					else shape_translation = true;
					selected_shape = i;
				}
			}

			if(!selected_shape)
			{
				if(tool_group->ItemIndex == -1) return;

				int width = width_track_bar->Position;
				TColor pen_color = colors[selected_colors_group->Items->Items[0]->ImageIndex];
				TColor brush_color = colors[selected_colors_group->Items->Items[1]->ImageIndex];

				if(tool_group->ItemIndex == 0) shapes.push_front(new pencil(x, y, x, y, width, pen_color));
				if(tool_group->ItemIndex == 1) shapes.push_front(new line(x, y, x, y, width, pen_color));
				if(tool_group->ItemIndex == 2) shapes.push_front(new ellipse(x, y, 1, 1, width, pen_color, brush_color));
				if(tool_group->ItemIndex == 3) shapes.push_front(new rectangle(x, y, x, y, width, pen_color, brush_color));
				shape_drawing = true;
			}
		}
        paint_box->Invalidate();
	}
	file_modified = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::paint_boxMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{

	update_status_bar(X, Y);

	double x = coord_system->to_coordx(X);
	double y = coord_system->to_coordy(Y);

	if(shape_drawing)
	{
		shapes.front()->update_on_drag(x, y);
		Invalidate();
	}
	else
	{
		if((X >= paint_box->Width - 5 && Y >= paint_box->Height - 5) ||
			 (selected_shape && selected_shape->is_border_clicked(x, y)))
			paint_box->Cursor = crSizeNWSE;

		else paint_box->Cursor = crDefault;

		if(shape_translation)
		{//возможно стоит вынести в отдельную функцию
			static double last_x = coord_system->to_coordx(X), last_y = coord_system->to_coordy(Y);
			static shape* last_shape = selected_shape;

			if(last_shape != selected_shape)
			{
				last_shape = selected_shape;
				last_x = x; last_y = y;
			}

			selected_shape->translate(x - last_x, y - last_y);
			last_x = x, last_y = y;
			Invalidate();
		}

		else if(shape_resizing)
		{
			selected_shape->scale(x, y);
			Invalidate();
		}

		else if(paint_box_resizing)
		{
			static TPoint last_point{ X, Y };

			int deltax = X - last_point.X;
			int deltay = Y - last_point.Y;

			paint_box->Width += deltax;
			paint_box->Height += deltay;

			original_width += deltax;
			original_height += deltay;

			last_point = { X, Y };
		}
	}
	update_scrollbars();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::paint_boxMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	shape_drawing = false;
	shape_translation = false;
	shape_resizing = false;
	if(Button == mbLeft)
		paint_box_resizing = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::selected_colors_groupMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    color_group->ItemIndex = -1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::horiz_scrollbarChange(TObject *Sender)
{
	paint_box->Left = -horiz_scrollbar->Position;
	paint_box->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::vert_scrollbarChange(TObject *Sender)
{
	paint_box->Top = -vert_scrollbar->Position;
	paint_box->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormResize(TObject *Sender)
{
	update_scrollbars();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::width_track_barChange(TObject *Sender)
{
	if(selected_shape) selected_shape->set_width(width_track_bar->Position);
	paint_box->Invalidate();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::about_program_buttonClick(TObject *Sender)
{
    Form2->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::image_settings_buttonClick(TObject *Sender)
{
    Form3->Show();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::save_buttonClick(TObject *Sender)
{
	if(filename == "") save_as_buttonClick(Sender);
	else
	{
		file_io->save_to_file(filename, original_width, original_height);
		file_modified = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::open_buttonClick(TObject *Sender)
{
	try
	{
		int rc = IDYES;
		if(file_modified)
			rc = Application->MessageBox(L"Файл не сохранен. Открыть новый файл?", L"Открытие файла", MB_YESNOCANCEL);
		if(rc == IDCANCEL || rc == IDNO) return;

		if(open_dialog->Execute())
		{
			std::wstring wstr(open_dialog->FileName.c_str());
			int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
			filename.resize(len);
			WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &filename[0], len, NULL, NULL);

			shapes.clear();
			selected_shape = nullptr;

			file_io->load_from_file(filename, original_width, original_height);
			paint_box->Width = original_width;
			paint_box->Height = original_height;
			file_modified = false;
			paint_box->Invalidate();
		}
	}
	catch(const std::exception& e){MessageBoxA(nullptr, filename.c_str(), "Error", MB_OK);}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::create_buttonClick(TObject *Sender)
{
	int rc = IDYES;
		if(file_modified)
			rc = Application->MessageBox(L"Файл не сохранен. Создать новый файл?", L"Создание файла", MB_YESNOCANCEL);
	if(rc == IDCANCEL || rc == IDNO) return;

	shapes.clear();
	selected_shape = nullptr;

	filename = "";
    file_modified = false;
	paint_box->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::save_as_buttonClick(TObject *Sender)
{
	save_dialog->FileName = std::wstring(filename.begin(), filename.end()).c_str();

	if(save_dialog->Execute())
	{
		std::wstring wstr(save_dialog->FileName.c_str());
		int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
		filename.resize(len);
		WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &filename[0], len, NULL, NULL);

		file_io->save_to_file(filename, original_width, original_height);
		file_modified = false;
	}
}
//---------------------------------------------------------------------------

