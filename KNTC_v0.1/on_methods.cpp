#include "ui.hpp"

void MyFrame::onExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::onAboutShortcuts(wxCommandEvent& event)
{
    wxMessageBox(L"Ctrl+O – Otwórz nowy plik i zamknij stary\n"
				 "Ctrl+P – Otwórz nowy plik i dodaj pytania\n"
				 "Ctrl+Q – Zamknij program\n"
				 "j, Num0, ← – poprzednie pytanie\n"
				 "k, Num(,), → – następne pytanie\n"
				 "(1-9)-zaznaczanie odpowiedzi\n"
				 "Enter – zatwierdzenie odpowiedzi",
                 L"Skróty klawiszowe", wxOK | wxICON_INFORMATION);
}

void MyFrame::onLicense(wxCommandEvent& event)
{
    wxMessageBox(L"Program jest udostępniony na licencji GPL 3. Do budowy programu została "
				 L"użyta biblioteka wxWidgets na licencji wxWindows Library Licence w wersji 3.1.",
                 "Licencja", wxOK | wxICON_INFORMATION);
}

void MyFrame::onOpen(wxCommandEvent& event)
{
	if(is_bazunia_loaded)
	{
		question.resize(0);
		setAnswerBoxes();
	}
	
	if(Open())
	{
		menuFile->Enable(ID_OpenAdditionaly, true);
		for(int i=0;i<5;i++)
			rbutton[i]->Enable();
	}
	
}

void MyFrame::onOpenAdditionaly(wxCommandEvent& event)
{
	Open();
}

bool MyFrame::Open()
{
	wxFileDialog fileDialog(this, L"Wybierz plik z bazunią", "", "", "(*.txt)|*.txt", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	if (fileDialog.ShowModal() == wxID_CANCEL)
        return false;
	
	if(load_bazunia(fileDialog.GetPath()))
		return false;
		
	is_bazunia_loaded=true;
	wxString tmp = "/";
	tmp << question.size();
	max_number_t->SetLabel(tmp);
	question_number=0;
	updateText(true);
	return true;
}

void MyFrame::onBack(wxCommandEvent& event)
{
    if(is_bazunia_loaded)
		updateText(false);
}

void MyFrame::onForward(wxCommandEvent& event)
{
    if(is_bazunia_loaded)
		updateText(true);
}

void MyFrame::onCheck(wxCommandEvent& event)
{
	if(is_question_answered)
	{
		if(is_bazunia_loaded)
			updateText(true);
		return;
	}
	
	if(is_bazunia_loaded)
	{
		for(int i=0;i<question[question_number-1].answer_s.size(); i++)
		{
			if(question[question_number-1].if_correct_answer[i])
			{
				answer_t[i]->SetBackgroundColour(*wxGREEN);
				answer_t[i]->Refresh();
				
			} else if(rbutton[i]->GetValue())
			{
				answer_t[i]->SetBackgroundColour(*wxRED);
				answer_t[i]->Refresh();
			}
		}
		check_b->Hide();
		forward_b->SetPosition(wxPoint(120, 160+55*answer_t.size()));
		is_question_answered=true;
	}
}

void MyFrame::onKeyDown(wxKeyEvent& event)
{
	//wxLogError(wxString::Format("KeyDown: %i\n", event.GetKeyCode()));
	if(event.GetKeyCode()>48 && event.GetKeyCode()<58 && event.GetKeyCode()-49<answer_t.size())
		rbutton[event.GetKeyCode()-49]->SetValue(true);
	
	if(event.GetKeyCode()>324 && event.GetKeyCode()<334 && event.GetKeyCode()-325<answer_t.size())
		rbutton[event.GetKeyCode()-325]->SetValue(true);
	event.Skip();
}

void MyFrame::onChildFocus(wxCommandEvent& event)
{
	if(!number_t->HasFocus())
		panel->SetFocus();
}