/*
GUI.cpp
*/

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <wx/image.h>
#include <iostream>

std::string app_name = "Photo Editing Software";
std::string image_folder = "/Users/andrewcarlson/Documents/School/Graphics/graphicsProject/Images/";
std::string image = "frog.jpg";
std::string image_path = image_folder + image;

class MyApp : public wxApp
{
public:
    bool OnInit() override;

};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
public:
    MyFrame();
private:

};

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();

    MyFrame *frame = new MyFrame();
    frame->Show();
    return true;

}

MyFrame::MyFrame()
    :wxFrame(nullptr, wxID_ANY, app_name)
{
    wxPanel* parent_panel = new wxPanel(this, wxID_ANY);

    wxPanel* picture_panel = new wxPanel(parent_panel, wxID_ANY);
    wxImage image(wxT(image_path), wxBITMAP_TYPE_PNG);
    if (!image.IsOk())
    {
    wxMessageBox("Failded to load image!", "Error", wxICON_ERROR);
    }
    
    wxBitmap bitmap(image);
    if (!bitmap.IsOk())
    {
    wxMessageBox("Failed to load image!", "Error", wxICON_ERROR);
    }

    wxStaticBitmap* imageDisplay = new wxStaticBitmap(picture_panel, wxID_ANY, bitmap);
    wxBoxSizer* photo_sizer = new wxBoxSizer(wxVERTICAL);
    photo_sizer->Add(imageDisplay, 1, wxCENTER | wxALL, 10);
    picture_panel->SetSizer(photo_sizer);
    parent_panel->Fit();

    wxPanel* slider_panel = new wxPanel(parent_panel, wxID_ANY);

    wxStaticText* slider_text = 
        new wxStaticText(slider_panel, wxID_ANY, "slider_panel");

    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

    hbox->Add(picture_panel, 1, wxEXPAND | wxALL, 10);
    hbox->Add(slider_panel, 1, wxEXPAND | wxALL, 10);

    parent_panel->SetSizer(hbox);
}