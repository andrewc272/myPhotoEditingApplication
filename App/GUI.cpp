/*
GUI.cpp
*/

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>
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

    wxImage image("/Users/andrewcarlson/Documents/School/Graphics/graphicsProject/Images/frog.jpg", wxBITMAP_TYPE_ANY);
    wxStaticBitmap* bitmap = new wxStaticBitmap(picture_panel, wxID_ANY, 
                                        wxBitmap(image), wxPoint(10, 10));

    wxBoxSizer* vSizer = new wxBoxSizer(wxVERTICAL);

    wxSlider* slider1 = new wxSlider(slider_panel, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);
    wxSlider* slider2 = new wxSlider(slider_panel, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);  
    wxSlider* slider3 = new wxSlider(slider_panel, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);

    vSizer->Add(slider1, 1, wxALL | wxEXPAND, 5);
    vSizer->Add(slider2, 1, wxALL | wxEXPAND, 5);
    vSizer->Add(slider3, 1, wxALL | wxEXPAND, 5);

    slider_panel->SetSizer(vSizer);

    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

    hbox->Add(picture_panel, 3, wxEXPAND | wxALL, 10);
    hbox->Add(slider_panel, 1, wxEXPAND | wxALL, 10);

    this->SetSizer(hbox);
}
