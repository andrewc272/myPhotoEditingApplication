#include <wx/wx.h>
#include <wx/filedlg.h>  // For file dialogs
#include <wx/image.h>    // For handling images
#include <wx/toolbar.h>  // For toolbar

// Define the application class
class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

// Define the frame (window) class
class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    // Event handlers for menu and toolbar actions
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnUndo(wxCommandEvent& event);
    void OnRedo(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);

    wxImage image;  // Image to be edited
    wxStaticBitmap* imageDisplay;  // Widget for displaying the image

    wxDECLARE_EVENT_TABLE();
};

// Define event table for connecting events to handlers
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_OPEN, MyFrame::OnOpen)
    EVT_MENU(wxID_SAVE, MyFrame::OnSave)
    EVT_MENU(wxID_UNDO, MyFrame::OnUndo)
    EVT_MENU(wxID_REDO, MyFrame::OnRedo)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
    EVT_MENU(wxID_EXIT, MyFrame::OnExit)
wxEND_EVENT_TABLE()

// Implement the application class
wxIMPLEMENT_APP(MyApp);

// OnInit for the application
bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("Photo Editor", wxPoint(50, 50), wxSize(800, 600));
    frame->Show(true);
    return true;
}

// Frame constructor
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size) {

    // Create menu bar
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(wxID_OPEN, "&Open\tCtrl-O");
    menuFile->Append(wxID_SAVE, "&Save\tCtrl-S");
    menuFile->Append(wxID_EXIT, "&Exit\tCtrl-Q");

    wxMenu* menuEdit = new wxMenu;
    menuEdit->Append(wxID_UNDO, "&Undo\tCtrl-Z");
    menuEdit->Append(wxID_REDO, "&Redo\tCtrl-Y");

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT, "&About");

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuEdit, "&Edit");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);

    // Create toolbar
    wxToolBar* toolbar = CreateToolBar();
    toolbar->AddTool(wxID_OPEN, "Open", wxBitmap("open.png"), "Open Image");
    toolbar->AddTool(wxID_SAVE, "Save", wxBitmap("save.png"), "Save Image");
    toolbar->AddTool(wxID_UNDO, "Undo", wxBitmap("undo.png"), "Undo Action");
    toolbar->AddTool(wxID_REDO, "Redo", wxBitmap("redo.png"), "Redo Action");
    toolbar->Realize();  // Finalize toolbar

    // Create image display area
    imageDisplay = new wxStaticBitmap(this, wxID_ANY, wxBitmap());

    // Create status bar
    CreateStatusBar();
    SetStatusText("Welcome to Photo Editor!");
}

// Event handler for opening an image
void MyFrame::OnOpen(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, "Open Image file", "", "",
                                "Image files (*.png;*.jpg;*.bmp)|*.png;*.jpg;*.bmp",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;  // The user canceled the operation
    }

    wxString filePath = openFileDialog.GetPath();
    if (!image.LoadFile(filePath)) {
        wxLogError("Cannot open file '%s'.", filePath);
        return;
    }

    imageDisplay->SetBitmap(wxBitmap(image));  // Display the image
    SetStatusText("Image loaded successfully.");
}

// Event handler for saving an image
void MyFrame::OnSave(wxCommandEvent& event) {
    wxFileDialog saveFileDialog(this, "Save Image file", "", "",
                                "PNG files (*.png)|*.png|JPEG files (*.jpg)|*.jpg|BMP files (*.bmp)|*.bmp",
                                wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;  // The user canceled the operation
    }

    wxString filePath = saveFileDialog.GetPath();
    if (!image.SaveFile(filePath)) {
        wxLogError("Cannot save file '%s'.", filePath);
        return;
    }

    SetStatusText("Image saved successfully.");
}

// Event handler for undo action (placeholder)
void MyFrame::OnUndo(wxCommandEvent& event) {
    wxMessageBox("Undo action not implemented yet.", "Info", wxOK | wxICON_INFORMATION);
}

// Event handler for redo action (placeholder)
void MyFrame::OnRedo(wxCommandEvent& event) {
    wxMessageBox("Redo action not implemented yet.", "Info", wxOK | wxICON_INFORMATION);
}

// Event handler for showing the About dialog
void MyFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is a basic photo editor built with wxWidgets.",
                 "About Photo Editor", wxOK | wxICON_INFORMATION);
}

// Event handler for exiting the application
void MyFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}
