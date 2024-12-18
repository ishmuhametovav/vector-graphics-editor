//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::cancel_buttonClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::apply_buttonClick(TObject *Sender)
{
	Form1->get_coord_system()->set_scale(1.0);
	Form1->set_original_width(StrToInt(width_edit->Text));
	Form1->set_original_height(StrToInt(height_edit->Text));

	Form1->paint_box->Width = Form1->get_original_width();
	Form1->paint_box->Height = Form1->get_original_height();

    Form1->update_scrollbars();

    Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormShow(TObject *Sender)
{
	width_edit->Text = Form1->get_original_width();
	height_edit->Text = Form1->get_original_height();

	update_file_labels();
}
//---------------------------------------------------------------------------

bool get_file_info(const std::string& filePath, LARGE_INTEGER& fileSize, SYSTEMTIME& lastWriteTime)
{
	HANDLE hFile = CreateFileA(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
        return false;

    FILE_STANDARD_INFO fileInfo;
    if (!GetFileInformationByHandleEx(hFile, FileStandardInfo, &fileInfo, sizeof(fileInfo)))
    {
        CloseHandle(hFile);
        return false;
    }
    fileSize = fileInfo.EndOfFile;

    FILETIME ftWrite;
    if (!GetFileTime(hFile, NULL, NULL, &ftWrite))
    {
        CloseHandle(hFile);
        return false;
    }

    FileTimeToSystemTime(&ftWrite, &lastWriteTime);

    CloseHandle(hFile);
    return true;
}

void TForm3::update_file_labels()
{
	std::string filePath = Form1->get_filename();
	if (filePath.empty())
		return;

    LARGE_INTEGER fileSize;
    SYSTEMTIME lastWriteTime;

	if (get_file_info(filePath, fileSize, lastWriteTime))
	{
        UnicodeString dateStr = UnicodeString().sprintf(
            L"%02d/%02d/%04d %02d:%02d:%02d",
            lastWriteTime.wDay,
            lastWriteTime.wMonth,
            lastWriteTime.wYear,
            lastWriteTime.wHour,
            lastWriteTime.wMinute,
            lastWriteTime.wSecond
        );

        save_data_label->Caption = L"Дата сохранения: " + dateStr;
        data_size_label->Caption = L"Размер на диске: " + UnicodeString(fileSize.QuadPart) + L" байт";
    }
	else ShowMessage(L"Не удалось получить информацию о файле.");
}

