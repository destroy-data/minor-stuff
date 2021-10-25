#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <string>
#include <fstream>
#include <wx/valnum.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
private:
	struct Question
    {
        wxString question_s;
        std::vector<wxString> answer_s;
        std::vector<unsigned char> if_correct_answer;
    };
    std::vector<Question> question;

	bool is_bazunia_loaded;
	bool is_question_answered;
	short question_number; //numer aktualnego pytania, liczone od 1
	wxIntegerValidator<int> *number_v;
	
	MyFrame* frame;
	wxMenu* menuFile;
	wxMenu* menuHelp;
	wxMenuBar* menuBar;
	wxStaticText *max_number_t;
	wxTextCtrl* number_t;
	wxTextCtrl* question_t;
	std::vector<wxTextCtrl*>  answer_t;
	std::vector<wxRadioButton*> rbutton;
	wxRadioButton* fake_rbutton; //taki myk, żeby móc odznaczyć wszystkie pozostałe radio-guziki
	wxButton* back_b;
	wxButton* check_b;
	wxButton* forward_b;
	wxPanel* panel;
		
    void onExit(wxCommandEvent& event);
    void onAboutShortcuts(wxCommandEvent& event);
    void onLicense(wxCommandEvent& event);
	void onOpen(wxCommandEvent& event);
	void onOpenAdditionaly(wxCommandEvent& event);
	void onBack(wxCommandEvent& event);
	void onCheck(wxCommandEvent& event);
	void onForward(wxCommandEvent& event);
	void onNumberChange(wxCommandEvent& event);
	void onKeyDown(wxKeyEvent& event);
	void onChildFocus(wxCommandEvent& event);
	
	void updateText(bool incriment);
	void setAnswerBoxes(int how_many=5);
	bool Open();
	int load_bazunia(wxString path_s);
};

enum
{
    ID_Open = 1,
	ID_OpenAdditionaly,
	ID_Exit,
	ID_AboutShortcuts,
	ID_License,
	ID_Back,
	ID_Check,
	ID_Forward,
	ID_Number,
};

