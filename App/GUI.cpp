/*
GUI.cpp
*/

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <chrono>

std::string app_name = "Photo Editing Software";
std::string image_folder = "/Users/andrewcarlson/Files/[1] School/[1] Fall 2024/[2] Graphics/[1] Homework/graphicsProject/Images/";
std::string input_image = "input.png";
std::string input_path = image_folder + input_image;
std::string output_image = "output.ppm";
std::string output_path = image_folder + output_image;

class image_processor
{
public:
    image_processor(){
        image = cv::imread(input_path, cv::IMREAD_COLOR);

        if (image.empty()){
            std::cerr << "ERROR: Could not open or find the image!" << std::endl;
        }

        rows = image.rows;
        cols = image.cols;
    }
    void black_white(){
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // Access the pixel at (i, j)
                cv::Vec3b pixel = image.at<cv::Vec3b>(i, j); // Vec3b stores BGR values

                int average = (pixel[0] * 0.0722) + (pixel[1] * 0.7152) + (pixel[2] * 0.2126);

                //pixel[0] = average; 
                //pixel[1] = average; 
                //pixel[2] = average; 

                image.at<cv::Vec3b>(i, j) = pixel;

                // Print out the BGR values
                std::cout << "Pixel at (" << i << ", " << j << ") - "
                        << "B: " << static_cast<int>(pixel[0]) << ", "
                        << "G: " << static_cast<int>(pixel[1]) << ", "
                        << "R: " << static_cast<int>(pixel[2]) << std::endl;
            }
        }
        !cv::imwrite(output_path, image);
    }
private:
    int rows;
    int cols;
    cv::Mat image;
};

class MyApp : public wxApp
{
public:
    bool OnInit() override;

};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
public:
    image_processor processor;
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
        processor.black_white();
        //wxImage image(output_path, wxBITMAP_TYPE_ANY);
        //bitmap = new wxStaticBitmap(picture_panel, wxID_ANY, wxBitmap(image), wxPoint(10, 10));
        hbox = new wxBoxSizer(wxHORIZONTAL);
        hbox->Add(picture_panel, 3, wxEXPAND | wxALL, 10);
        hbox->Add(slider_panel, 1, wxEXPAND | wxALL, 10);
        
    }

    wxSlider* slider1;
    int slider1_value = 50;
    wxSlider* slider2;
    int slider2_value = 50;
    wxSlider* slider3;
    int slider3_value = 50;
    wxStaticText* message_box;
    wxStaticBitmap* bitmap;
    wxPanel* picture_panel;
    wxPanel* slider_panel;
    wxBoxSizer* hbox;
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
    picture_panel = new wxPanel(this, wxID_ANY);
    slider_panel = new wxPanel(this, wxID_ANY);

    wxImage image(input_path, wxBITMAP_TYPE_ANY);
    bitmap = new wxStaticBitmap(picture_panel, wxID_ANY, 
                                        wxBitmap(image), wxPoint(10, 10));

    wxBoxSizer* vSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* slider1_label = new wxStaticText(slider_panel, wxID_ANY, "Slider1");
    slider1 = new wxSlider(slider_panel, wxID_ANY, slider1_value, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);
    wxStaticText* slider2_label = new wxStaticText(slider_panel, wxID_ANY, "Slider2");
    slider2 = new wxSlider(slider_panel, wxID_ANY, slider2_value, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);  
    wxStaticText* slider3_label = new wxStaticText(slider_panel, wxID_ANY, "Slider3");
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

    hbox = new wxBoxSizer(wxHORIZONTAL);

    hbox->Add(picture_panel, 3, wxEXPAND | wxALL, 10);
    hbox->Add(slider_panel, 1, wxEXPAND | wxALL, 10);

    this->SetSizer(hbox);

    slider1->Bind(wxEVT_SLIDER, &MyFrame::OnSlidersChange, this);
    slider2->Bind(wxEVT_SLIDER, &MyFrame::OnSlidersChange, this);
    slider3->Bind(wxEVT_SLIDER, &MyFrame::OnSlidersChange, this);
}
