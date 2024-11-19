//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ButtonGroup.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include<memory>
#include<vector>
#include<array>
#include"coordinate_system.h"
#include"Rectangle.h"
#include"Ellipse.h"
#include"Line.h"
#include"Pencil.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TStatusBar *status_bar;
	TPanel *panel;
	TTrackBar *width_track_bar;
	TButtonGroup *color_group;
	TButtonGroup *tool_group;
	TImageList *color_image_list;
	TImageList *tools_image_list;
	TButtonGroup *selected_colors_group;
	TPaintBox *paint_box;
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FormMouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall FormMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
		  bool &Handled);
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight, bool &Resize);
	void __fastcall color_groupButtonClicked(TObject *Sender, int Index);
	void __fastcall paint_boxPaint(TObject *Sender);
	void __fastcall paint_boxMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall paint_boxMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall paint_boxMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);





private:	// User declarations
	std::array<TColor, 10> colors;
	std::unique_ptr<coordinate_system> coord_system;
	std::vector<shape*> shapes;
	bool shape_drawing;
    bool paint_box_resizing;
	void update_status_bar(const int X, const int Y);
	void draw_shapes();
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
