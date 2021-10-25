#include "ui.hpp"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "KNTC 0.9", wxDefaultPosition, wxSize(640,530), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    menuFile = new wxMenu;
    menuFile->Append(ID_Open, L"&Otwórz\tCtrl-O");
	menuFile->Append(ID_OpenAdditionaly, L"&Dodaj\tCtrl-P");
	menuFile->Enable(ID_OpenAdditionaly, false);
	menuFile->AppendSeparator();
    menuFile->Append(ID_Exit, L"Wyjście\tCtrl-Q");
    menuHelp = new wxMenu;
	menuHelp->Append(ID_AboutShortcuts, L"Skróty klawiszowe");
	menuHelp->Append(ID_License, "Licencja");
    menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "Plik");
    menuBar->Append(menuHelp, "Pomoc");
    SetMenuBar(menuBar);
    Bind(wxEVT_MENU, &MyFrame::onOpen, this, ID_Open);
	Bind(wxEVT_MENU, &MyFrame::onOpenAdditionaly, this, ID_OpenAdditionaly);
	Bind(wxEVT_MENU, &MyFrame::onAboutShortcuts, this, ID_AboutShortcuts);
	Bind(wxEVT_MENU, &MyFrame::onLicense, this, ID_License);
    Bind(wxEVT_MENU, &MyFrame::onExit, this, ID_Exit);
	
	panel = new wxPanel(this, wxID_ANY);
	rbutton = {new wxRadioButton(this, wxID_ANY,""),new wxRadioButton(this, wxID_ANY,""),new wxRadioButton(this, wxID_ANY,""),new wxRadioButton(this, wxID_ANY,""),new wxRadioButton(this, wxID_ANY,"")};
	
	question_t= new wxTextCtrl(this,wxID_ANY, L"Po co się uczyć, kiedy można iść na piwo?" , wxPoint(25,10), wxSize(600,140), wxTE_MULTILINE | wxTE_READONLY);
	for(int i=0;i<5;i++)
	{
		answer_t.push_back(new wxTextCtrl(this, wxID_ANY, "", wxPoint(25, 160+55*i), wxSize(600,45), wxTE_MULTILINE | wxTE_READONLY));
		rbutton[i]->SetPosition(wxPoint(3,160+12+55*i));
		rbutton[i]->Disable();
	}
	fake_rbutton = new wxRadioButton(this, wxID_ANY,"", wxPoint(666,0));
	fake_rbutton->SetValue(true);
	
	back_b = new wxButton(this, ID_Back, "Wstecz", wxPoint(10, 435),wxSize(100,30));
	check_b = new wxButton(this, ID_Check, L"Sprawdź", wxPoint(120, 435),wxSize(100,30));
	forward_b = new wxButton(this, ID_Forward, "Dalej", wxPoint(230, 435),wxSize(100,30));
	
	Bind(wxEVT_BUTTON, &MyFrame::onBack, this, ID_Back);
	Bind(wxEVT_BUTTON, &MyFrame::onCheck, this, ID_Check);
	Bind(wxEVT_BUTTON, &MyFrame::onForward, this, ID_Forward);
	
	number_t = new wxTextCtrl(this, ID_Number,"", wxPoint(520,165+55*answer_t.size()), wxSize(50,20), wxTE_RIGHT);
	number_t->Disable();
	max_number_t = new wxStaticText(this, wxID_ANY,"", wxPoint(580,440), wxSize(50,20));
	Bind(wxEVT_TEXT, &MyFrame::onNumberChange, this, ID_Number);
	
	wxAcceleratorEntry shortcut[8];
	shortcut[0].Set(0, int('j'), ID_Back);
	shortcut[1].Set(0, int('k'), ID_Forward);
	shortcut[2].Set(0, 13, ID_Check);
	shortcut[3].Set(0, 370, ID_Check);
	shortcut[4].Set(0, 324, ID_Back);
	shortcut[5].Set(0, 389, ID_Forward);
	shortcut[6].Set(0, WXK_LEFT, ID_Back);
	shortcut[7].Set(0, WXK_RIGHT, ID_Forward);
	
	wxAcceleratorTable shortcuts_table(8,shortcut);
	this->SetAcceleratorTable(shortcuts_table);
	
	panel->Bind(wxEVT_KEY_DOWN, &MyFrame::onKeyDown, this);
	this->Bind(wxEVT_CHILD_FOCUS, &MyFrame::onChildFocus, this);
}

