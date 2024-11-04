#include <wx/wx.h>
#include <wx/image.h>
#include <wx/sizer.h>

std::string app_name = "Photo Editing Software";
std::string image_folder = "/Users/andrewcarlson/Files/[1] School/[1] Fall 2024/[2] Graphics/[1] Homework/graphicsProject/Images/";
std::string input_image = "input.png";
std::string input_path = image_folder + input_image;
std::string output_image = "output.png";
std::string output_path = image_folder + output_image;

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);
private:
    void OnSliderUpdate(wxScrollEvent& event);
    void UpdateImage();

    wxImage m_originalImage;
    wxBitmap m_displayBitmap;
    wxStaticBitmap* m_imageControl;
    wxSlider* m_brightnessSlider;
    wxSlider* m_contrastSlider;

    int m_brightness;
    int m_contrast;

    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_SLIDER(wxID_ANY, MyFrame::OnSliderUpdate)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame(app_name);
    frame->Show(true);
    return true;
}


bool MyApp::OnInit()
{
    wxInitAllImageHandlers();

    MyFrame *frame = new MyFrame();
    frame->Show();
    return true;
}

wxIMPLEMENT_APP(MyApp);

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 600)),
      m_brightness(0), m_contrast(0) {

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Load the original image
    m_originalImage.LoadFile(input_image); // Replace "input.png" with your image file

    // Create a wxStaticBitmap to display the image
    m_displayBitmap = wxBitmap(m_originalImage);
    m_imageControl = new wxStaticBitmap(this, wxID_ANY, m_displayBitmap);

    // Create sliders for brightness and contrast
    m_brightnessSlider = new wxSlider(this, wxID_ANY, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);
    m_contrastSlider = new wxSlider(this, wxID_ANY, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);

    // Add controls to the sizer
    mainSizer->Add(m_imageControl, 1, wxEXPAND | wxALL, 10);
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Brightness"), 0, wxALIGN_CENTER | wxTOP, 10);
    mainSizer->Add(m_brightnessSlider, 0, wxEXPAND | wxLEFT | wxRIGHT, 20);
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Contrast"), 0, wxALIGN_CENTER | wxTOP, 10);
    mainSizer->Add(m_contrastSlider, 0, wxEXPAND | wxLEFT | wxRIGHT, 20);

    SetSizer(mainSizer);

    // Initialize the display with the original image
    UpdateImage();
}

void MyFrame::OnSliderUpdate(wxScrollEvent& event) {
    // Update brightness and contrast values from sliders
    m_brightness = m_brightnessSlider->GetValue();
    m_contrast = m_contrastSlider->GetValue();

    // Update the displayed image
    UpdateImage();
}

void MyFrame::UpdateImage() {
    // Make a copy of the original image to apply transformations
    wxImage modifiedImage = m_originalImage.Copy();

    // Apply brightness and contrast adjustments
    for (int x = 0; x < modifiedImage.GetWidth(); ++x) {
        for (int y = 0; y < modifiedImage.GetHeight(); ++y) {
            unsigned char r = modifiedImage.GetRed(x, y);
            unsigned char g = modifiedImage.GetGreen(x, y);
            unsigned char b = modifiedImage.GetBlue(x, y);

            // Adjust brightness
            r = std::clamp(static_cast<int>(r + m_brightness), 0, 255);
            g = std::clamp(static_cast<int>(g + m_brightness), 0, 255);
            b = std::clamp(static_cast<int>(b + m_brightness), 0, 255);

            // Adjust contrast (simplified)
            r = std::clamp(static_cast<int>((r - 128) * (1 + m_contrast / 100.0) + 128), 0, 255);
            g = std::clamp(static_cast<int>((g - 128) * (1 + m_contrast / 100.0) + 128), 0, 255);
            b = std::clamp(static_cast<int>((b - 128) * (1 + m_contrast / 100.0) + 128), 0, 255);

            modifiedImage.SetRGB(x, y, r, g, b);
        }
    }

    // Convert the modified image to a bitmap and display it
    m_displayBitmap = wxBitmap(modifiedImage);
    m_imageControl->SetBitmap(m_displayBitmap);
    Refresh(); // Refresh the frame to show the updated image
}

