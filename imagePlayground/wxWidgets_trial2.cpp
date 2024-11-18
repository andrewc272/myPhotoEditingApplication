#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/image.h>
#include <wx/statbmp.h>
#include <wx/slider.h>
#include <iostream>

class ImageEditorFrame : public wxFrame
{
public:
    ImageEditorFrame(const wxString& title);

private:
    // Event handler functions
    void OnHueChanged(wxCommandEvent& event);
    void OnSaturationChanged(wxCommandEvent& event);
    void OnValueChanged(wxCommandEvent& event);

    // Helper function to update the displayed image based on slider values
    void UpdateImage();

    // UI components
    wxStaticBitmap* imageDisplay;
    wxSlider* hueSlider;
    wxSlider* saturationSlider;
    wxSlider* valueSlider;

    // Original and adjusted images
    wxImage originalImage;
    wxImage adjustedImage;
};

class ImageEditorApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(ImageEditorApp);

bool ImageEditorApp::OnInit()
{
    wxInitAllImageHandlers();

    ImageEditorFrame* frame = new ImageEditorFrame("Image Editor");
    frame->Show(true);
    return true;
}

ImageEditorFrame::ImageEditorFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
    // Create a horizontal sizer for layout
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    // ** Left Panel - Image Display **
    wxPanel* leftPanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);

    // Load an image (replace "image.jpg" with your image path)
    originalImage.LoadFile("images/frog.jpg");
    adjustedImage = originalImage.Copy(); // Make a copy for editing
    imageDisplay = new wxStaticBitmap(leftPanel, wxID_ANY, wxBitmap(adjustedImage));

    leftSizer->Add(imageDisplay, 1, wxEXPAND | wxALL, 10);
    leftPanel->SetSizer(leftSizer);

    // ** Right Panel - Controls **
    wxPanel* rightPanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);

    // Hue slider
    wxStaticText* hueLabel = new wxStaticText(rightPanel, wxID_ANY, "Hue");
    hueSlider = new wxSlider(rightPanel, wxID_ANY, 50, 0, 100);
    rightSizer->Add(hueLabel, 0, wxTOP | wxLEFT | wxRIGHT, 10);
    rightSizer->Add(hueSlider, 0, wxEXPAND | wxALL, 10);

    // Bind event handler for hue slider
    hueSlider->Bind(wxEVT_SLIDER, &ImageEditorFrame::OnHueChanged, this);

    // saturation slider
    wxStaticText* saturationLabel = new wxStaticText(rightPanel, wxID_ANY, "Saturation");
    saturationSlider = new wxSlider(rightPanel, wxID_ANY, 50, 0, 100);
    rightSizer->Add(saturationLabel, 0, wxTOP | wxLEFT | wxRIGHT, 10);
    rightSizer->Add(saturationSlider, 0, wxEXPAND | wxALL, 10);

    // Bind event handler for saturation slider
    saturationSlider->Bind(wxEVT_SLIDER, &ImageEditorFrame::OnSaturationChanged, this);

    // Value slider
    wxStaticText* valueLabel = new wxStaticText(rightPanel, wxID_ANY, "Value");
    valueSlider = new wxSlider(rightPanel, wxID_ANY, 50, 0, 100);
    rightSizer->Add(valueLabel, 0, wxTOP | wxLEFT | wxRIGHT, 10);
    rightSizer->Add(valueSlider, 0, wxEXPAND | wxALL, 10);

    // Bind event handler for value slider
    valueSlider->Bind(wxEVT_SLIDER, &ImageEditorFrame::OnValueChanged, this);

    rightPanel->SetSizer(rightSizer);

    // Add both panels to the main sizer
    mainSizer->Add(leftPanel, 1, wxEXPAND | wxALL, 10);
    mainSizer->Add(rightPanel, 0, wxEXPAND | wxALL, 10);

    SetSizer(mainSizer);
    Centre();
}

void ImageEditorFrame::OnHueChanged(wxCommandEvent& event)
{
    UpdateImage();
}

void ImageEditorFrame::OnSaturationChanged(wxCommandEvent& event)
{
    UpdateImage();
}

void ImageEditorFrame::OnValueChanged(wxCommandEvent& event)
{
    UpdateImage();
}

void ImageEditorFrame::UpdateImage()
{
    // Copy the original image to avoid modifying it directly
    adjustedImage = originalImage.Copy();

    // Get slider values
    float hue = hueSlider->GetValue() / 100.0;
    float saturation = (saturationSlider->GetValue() / 50.0) - 1;
    saturation = saturation*saturation*saturation;
    float value = (valueSlider->GetValue() / 50.0) - 1;
    value = value * value * value;

    std::cout << "Hue: " << static_cast<float>(hue) << ", "
                      << "Saturation: " << static_cast<float>(saturation) << ", "
                      << "Value: " << static_cast<float>(value) << std::endl;
        std::cout << "\n";

    for (int x = 0; x < adjustedImage.GetWidth(); x++){
    for (int y = 0; y < adjustedImage.GetHeight(); y++){

        // get rgb values
        float r = (float)adjustedImage.GetRed(x, y);
        float g = (float)adjustedImage.GetGreen(x, y);
        float b = (float)adjustedImage.GetBlue(x, y);

        //convert to hsv
        // get max
        float max = r;
        if ( g > max ) max = g;
        if ( b > max ) max = b;

        //get min
        float min = r;
        if ( g < min ) min = g;
        if ( b < min ) min = b;

        //get diff
        float diff = max - min;

        float v = max/255;

        float s = diff/max;

        float hue_360;
        if (diff == 0){
            hue_360 = 0;
        }
        else{
            if ( r == max ){
                hue_360 = 0 + 60*(g-b) / diff;
            }
            else if ( g == max ){
                hue_360 = 120 + 60*(b-r) / diff;
            }
            else{ // b == max
                hue_360 = 240 + 60*(r-g) / diff;
            }
        }
        if (hue_360 < 0){
            hue_360 = hue_360 + 360;
        }

        float h = hue_360/360;

        if (max == 0) {
            h = 0;
            s = 0;
            v = 0;
        }

        //hsv manipulation
        // h = hue;

        // saturation
        if ( saturation > 0.0 && saturation <= 1.0 ){
            float saturation_addition = saturation * ( 1 - s );
            s = s + saturation_addition;
        }
        else if ( saturation >= -1.0 && saturation < 0.0 ) {
            float saturation_addition = saturation * s;
            s = s + saturation_addition;
        }

        // v = value;
        if ( value > 0.0 && value <= 1.0 ){
            float value_addition = value * ( 1 - v );
            v = v + value_addition;
        }
        else if ( value >= -1.0 && value < 0.0 ) {
            float value_addition = value * v;
            v = v + value_addition;
        }
        


        //hsv to rgb
        max = v;
        min = v - s * v;

        diff = max - min;

        float sixth = 1.0/6.0;

        int base_angle = 0;
        if (1.0/6.0 < h && h <= 3.0/6.0){
            base_angle = 120;
        }
        if ((3.0/6.0 < h) && (h <= 5.0/6.0)){
            base_angle = 240;
        }

        float mid = min;

        bool roatate_positive = false;
        if ((0 < h && h <= 1.0/6.0) || (2.0/6.0 < h && h <= 3.0/6.0) || (4.0/6.0 < h && h <= 5.0/6.0)){
            roatate_positive = true;
        }

        if (roatate_positive){
            mid = (h*360 - base_angle)*diff/60+min;
        }
        else{
            mid = (base_angle - h*360)*diff/60+min;
        }

        if (mid < min){
            mid = (base_angle - 360*(h-1))*diff/60+min;
        }

        min = min * 255;
        mid = mid * 255;
        max = max * 255;

        if (base_angle == 0){
            if (roatate_positive){
                r = max;
                g = mid;
                b = min;
            }
            else{
                r = max;
                g = min;
                b = mid;
            }
        }
        if (base_angle == 120){
            if (roatate_positive){
                r = min;
                g = max;
                b = mid;
            }
            else{
                r = mid;
                g = max;
                b = min;
            }
        }
        if (base_angle == 240){
            if (roatate_positive){
                r = mid;
                g = min;
                b = max;
            }
            else{
                r = min;
                g = mid;
                b = max;
            }
        }

        adjustedImage.SetRGB(x, y, r, g, b);
    }
    }

    // Update the displayed image
    imageDisplay->SetBitmap(wxBitmap(adjustedImage));
    Refresh(); // Redraw the frame
}
