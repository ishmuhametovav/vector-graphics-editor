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
#include <Vcl.Menus.hpp>
#include <Vcl.Dialogs.hpp>
#include<forward_list>
#include<vector>
#include<array>
#include"tinyxml2.h"
#include"coordinate_system.h"
#include"Rectangle.h"
#include"Ellipse.h"
#include"Line.h"
#include"Pencil.h"
#include"Unit2.h"
#include"Unit3.h"
#include"SvgIO.h"
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
	TScrollBar *vert_scrollbar;
	TScrollBar *horiz_scrollbar;
	TMainMenu *main_menu;
	TMenuItem *file_button;
	TMenuItem *settings_button;
	TMenuItem *create_button;
	TMenuItem *open_button;
	TMenuItem *save_button;
	TMenuItem *save_as_button;
	TMenuItem *image_settings_button;
	TMenuItem *about_program_button;
	TSaveDialog *save_dialog;
	TOpenDialog *open_dialog;
	void __fastcall FormMouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall FormMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
		  bool &Handled);
	void __fastcall FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight, bool &Resize);
	void __fastcall color_groupButtonClicked(TObject *Sender, int Index);
	void __fastcall paint_boxPaint(TObject *Sender);
	void __fastcall paint_boxMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall paint_boxMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall paint_boxMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall selected_colors_groupMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall horiz_scrollbarChange(TObject *Sender);
	void __fastcall vert_scrollbarChange(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall width_track_barChange(TObject *Sender);
	void __fastcall about_program_buttonClick(TObject *Sender);
	void __fastcall image_settings_buttonClick(TObject *Sender);
	void __fastcall save_buttonClick(TObject *Sender);
	void __fastcall open_buttonClick(TObject *Sender);
	void __fastcall create_buttonClick(TObject *Sender);
	void __fastcall save_as_buttonClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);





private:	// User declarations
	int original_width, original_height;
	std::array<TColor, 10> colors;
	svg_io* file_io;
	coordinate_system* coord_system;
	std::forward_list<shape*> shapes;
	shape* selected_shape;
	bool shape_drawing;
	bool shape_translation;
    bool shape_resizing;
	bool paint_box_resizing;
	bool file_modified;
    std::string filename;
	void update_status_bar(const int X, const int Y);
	void draw_shapes();
	void remove_shape(const double x, const double y);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
    void update_scrollbars();
	coordinate_system* get_coord_system(){ return coord_system; }
	int get_original_width() const { return original_width; }
	int get_original_height() const { return original_height; }
	void set_original_width( int original_width ) { this->original_width = original_width; }
	void set_original_height( int original_height ) { this->original_height = original_height; }
    std::string get_filename() const { return filename; }
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
