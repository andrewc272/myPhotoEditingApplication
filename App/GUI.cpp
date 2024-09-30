/*
GUI.cpp
*/

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <iostream>

std::string app_name = "Photo Editing Software";
std::string image_folder = "/Users/andrewcarlson/Documents/School/Graphics/graphicsProject/Images/";
std::string image = "frog.png";
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
    void OnSlidersChange(wxCommandEvent& event)
    {
        int value = slider1->GetValue();
        if( value != slider1_value ){
            message_box->SetLabel(wxString::Format("Slider1 Value: %d", value));
        }
        value = slider2->GetValue();
        if( value != slider2_value ){
            message_box->SetLabel(wxString::Format("Slider2 Value: %d", value));
        }
        value = slider3->GetValue();
        if( value != slider3_value ){
            message_box->SetLabel(wxString::Format("Slider3 Value: %d", value));
        }
    }

    wxSlider* slider1;
    int slider1_value = 50;
    wxSlider* slider2;
    int slider2_value = 50;
    wxSlider* slider3;
    int slider3_value = 50;
    wxStaticText* message_box;
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

    wxImage image(image_path, wxBITMAP_TYPE_ANY);
    wxStaticBitmap* bitmap = new wxStaticBitmap(picture_panel, wxID_ANY, 
                                        wxBitmap(image), wxPoint(10, 10));

    wxBoxSizer* vSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* slider1_label = new wxStaticText(slider_panel, wxID_ANY, "Red");
    slider1 = new wxSlider(slider_panel, wxID_ANY, slider1_value, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);
    wxStaticText* slider2_label = new wxStaticText(slider_panel, wxID_ANY, "Green");
    slider2 = new wxSlider(slider_panel, wxID_ANY, slider2_value, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);  
    wxStaticText* slider3_label = new wxStaticText(slider_panel, wxID_ANY, "Blue");
    slider3 = new wxSlider(slider_panel, wxID_ANY, slider3_value, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);
    message_box = new wxStaticText(slider_panel, wxID_ANY, "No Change");

    vSizer->Add(slider1_label, 1, wxALL | wxEXPAND, 5);
    vSizer->Add(slider1, 1, wxALL | wxEXPAND, 1);
    vSizer->Add(slider2_label, 1, wxALL | wxEXPAND, 5);
    vSizer->Add(slider2, 1, wxALL | wxEXPAND, 1);
    vSizer->Add(slider3_label, 1, wxALL | wxEXPAND, 5);
    vSizer->Add(slider3, 1, wxALL | wxEXPAND, 1);
    vSizer->Add(message_box, 1, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);


    slider_panel->SetSizer(vSizer);

    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

    hbox->Add(picture_panel, 3, wxEXPAND | wxALL, 10);
    hbox->Add(slider_panel, 1, wxEXPAND | wxALL, 10);

    this->SetSizer(hbox);

    slider1->Bind(wxEVT_SLIDER, &MyFrame::OnSlidersChange, this);
    slider2->Bind(wxEVT_SLIDER, &MyFrame::OnSlidersChange, this);
    slider3->Bind(wxEVT_SLIDER, &MyFrame::OnSlidersChange, this);
}
