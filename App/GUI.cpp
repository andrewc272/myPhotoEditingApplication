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
    :wxFrame(nullptr, wxID_ANY, app_name, wxDefaultPosition, wxSize(600, 400))
{
    wxPanel* picture_panel = new wxPanel(this, wxID_ANY);
    wxPanel* slider_panel = new wxPanel(this, wxID_ANY);

    picture_panel->SetBackgroundColour(wxColour(0, 255, 0));
    slider_panel->SetBackgroundColour(wxColour(0, 0, 255));

    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

    hbox->Add(picture_panel, 3, wxEXPAND | wxALL, 10);
    hbox->Add(slider_panel, 1, wxEXPAND | wxALL, 10);

    this->SetSizer(hbox);
}
