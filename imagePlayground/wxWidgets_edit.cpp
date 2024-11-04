#include <wx/wx.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

private:
    void OnPaint(wxPaintEvent& event);

    wxBitmap m_bitmap;
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_PAINT(MyFrame::OnPaint)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    wxInitAllImageHandlers();

    MyFrame* frame = new MyFrame("Bitmap Editing Example");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 400)) {

    // Load a bitmap image
    wxImage image("frog.jpg");

    // Convert to wxImage for pixel editing
    //wxImage image = m_bitmap.ConvertToImage();

    // Modify the image (for example, invert colors)
    if (image.IsOk()) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            for (int y = 0; y < image.GetHeight(); ++y) {
                unsigned char r = image.GetRed(x, y);
                unsigned char g = image.GetGreen(x, y);
                unsigned char b = image.GetBlue(x, y);

                int average = (0.25 * r) + (0.75 * g) + (0.25 * b);

                // Invert colors
                image.SetRGB(x, y, average, average, average);
            }
        }

        // Convert the modified image back to bitmap
        m_bitmap = wxBitmap(image);
    }
}

void MyFrame::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);

    // Draw the modified bitmap on the window
    if (m_bitmap.IsOk()) {
        dc.DrawBitmap(m_bitmap, 0, 0, false);
    }
}