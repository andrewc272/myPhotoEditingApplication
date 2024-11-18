#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/image.h>
#include <wx/statbmp.h>
#include <wx/slider.h>

class ImageRenderer{
public:
    ImageRenderer(wxImage origninalImage);
    wxImage update_hsv(float h, float s, float v);
private:
    wxImage Image;
};

ImageRenderer::ImageRenderer(wxImage originalImage){
    Image = originalImage.Copy();
}

wxImage ImageRenderer::update_hsv( float h, float s, float v ){
    for (int x = 0; x < Image.GetWidth(); x++){
    for (int y = 0; y < Image.GetHeight(); y++){

        // get rgb values
        unsigned char r = Image.GetRed(x, y);
        unsigned char g = Image.GetGreen(x, y);
        unsigned char b = Image.GetBlue(x, y);

        //convert to hsv
        // get max
        float max = r;
        if ( g > max ) max = g;
        if ( b > max ) max = b;

        //get min
        float min = r;
        if ( g < min ) min = g;
        if ( b < min ) min = b;
    }
    }
}

class ImageEditorFrame : public wxFrame
{
public:
    ImageEditorFrame(const wxString& title);

    

private:
    void OnHSVChanged(wxCommandEvent& event);

    void UpdateImage();

    wxStaticBitmap* imageDisplay;
    wxSlider* hueSlider;
    wxSlider* saturationSlider;
    wxSlider* brightnessSlider;

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

    // Load an image (placeholder, replace "image.jpg" with your image path)
    originalImage.LoadFile("frog.jpg");
    ImageRenderer* imgRen = new ImageRenderer(originalImage);
    adjustedImage = originalImage.Copy();
    imageDisplay = new wxStaticBitmap(leftPanel, wxID_ANY, wxBitmap(adjustedImage));
    
    leftSizer->Add(imageDisplay, 1, wxEXPAND | wxALL, 10);
    leftPanel->SetSizer(leftSizer);

    // ** Right Panel - Controls **
    wxPanel* rightPanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);

    // Add sliders (placeholder without functionality)
    wxStaticText* hueLabel = new wxStaticText(rightPanel, wxID_ANY, "HUE");
    wxSlider* hueSlider = new wxSlider(rightPanel, wxID_ANY, 50, 0, 100);
    rightSizer->Add(hueLabel, 0, wxTOP | wxLEFT | wxRIGHT, 10);
    rightSizer->Add(hueSlider, 0, wxEXPAND | wxALL, 10);

    hueSlider->Bind(wxEVT_SLIDER, &ImageEditorFrame::OnHSVChanged, this);

    wxStaticText* saturationLabel = new wxStaticText(rightPanel, wxID_ANY, "SATURATION");
    wxSlider* saturationSlider = new wxSlider(rightPanel, wxID_ANY, 50, 0, 100);
    rightSizer->Add(saturationLabel, 0, wxTOP | wxLEFT | wxRIGHT, 10);
    rightSizer->Add(saturationSlider, 0, wxEXPAND | wxALL, 10);

    saturationSlider->Bind(wxEVT_SLIDER, &ImageEditorFrame::OnHSVChanged, this);

    wxStaticText* brightnessLabel = new wxStaticText(rightPanel, wxID_ANY, "BRIGHTNESS");
    wxSlider* brightnessSlider = new wxSlider(rightPanel, wxID_ANY, 50, 0, 100);
    rightSizer->Add(brightnessLabel, 0, wxTOP | wxLEFT | wxRIGHT, 10);
    rightSizer->Add(brightnessSlider, 0, wxEXPAND | wxALL, 10);

    brightnessSlider->Bind(wxEVT_SLIDER, &ImageEditorFrame::OnHSVChanged, this);

    rightPanel->SetSizer(rightSizer);

    // Add both panels to the main sizer
    mainSizer->Add(leftPanel, 1, wxEXPAND | wxALL, 10); // Left panel takes more space
    mainSizer->Add(rightPanel, 0, wxEXPAND | wxALL, 10); // Right panel with sliders

    SetSizer(mainSizer);
    Centre();
}

void ImageEditorFrame::OnHSVChanged(wxCommandEvent& event)
{
    UpdateImage();
}

void ImageEditorFrame::UpdateImage()
{
    // Copy the original image to avoid modifying it directly
    adjustedImage = originalImage.Copy();

    // Get slider values
    int hue = hueSlider->GetValue();
    int saturation = saturationSlider->GetValue();
    int contrast = saturationSlider->GetValue();

    // Adjust brightness (example: simple additive brightness)
    // unsigned char* data = adjustedImage.GetData();
    // int numPixels = adjustedImage.GetWidth() * adjustedImage.GetHeight();
    // for (int i = 0; i < numPixels * 3; i++) {
    //     int value = data[i] + (brightness - 50) * 2; // Simple brightness adjustment
    //     data[i] = std::clamp(value, 0, 255); // Clamp to valid RGB range
    // }

    // (Additional processing for contrast and saturation would go here)

    // Update the displayed image
    imageDisplay->SetBitmap(wxBitmap(adjustedImage));
    Refresh(); // Redraw the frame
}
