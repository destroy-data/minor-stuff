#include "ui.hpp"

void MyFrame::updateText(bool incriment)
{
    if(incriment && (question_number < question.size()))
        question_number++;
    else if (!incriment && question_number>1 && question_number <= int(question.size()))
        question_number--;
    else return;
	
	fake_rbutton->SetValue(true);
	for(int i=0;i<answer_t.size();i++)
    {
		answer_t[i]->SetBackgroundColour(wxNullColour);
		answer_t[i]->SetDefaultStyle(wxTextAttr(wxNullColour,wxNullColour));
		answer_t[i]->Refresh();
	}
	
    question_t->ChangeValue(question[question_number-1].question_s);
	int j=question[question_number-1].answer_s.size();

    for(int i=0; i<j;i++)
        answer_t[i]->ChangeValue(question[question_number-1].answer_s[i]);

	for(int i=answer_t.size();i>j;i--)
		answer_t[i-1]->ChangeValue(wxEmptyString);
	
	wxString tmp;
	tmp << question_number;
	number_t->ChangeValue(tmp);
	
	forward_b->SetPosition(wxPoint(230, 160+55*answer_t.size()));
	check_b->Show();
	is_question_answered=false;
}

void MyFrame::setAnswerBoxes(int how_many)
{
	if(how_many>answer_t.size())
	{
		rbutton.resize(how_many);
		for(int i=answer_t.size();answer_t.size()<how_many;i++)
		{
			answer_t.push_back(new wxTextCtrl(this, wxID_ANY, "", wxPoint(25,160+55*i), wxSize(600,45), wxTE_MULTILINE | wxTE_READONLY));
			rbutton[i]=new wxRadioButton(this, wxID_ANY,"",wxPoint(3,160+12+55*i));
		}	
	} else if(how_many<answer_t.size())
	{
		for(int i=how_many;i<answer_t.size();i++)
		{
			answer_t[i]->Destroy();
			rbutton[i]->Destroy();
		}
		answer_t.resize(how_many);
		rbutton.resize(how_many);
	}
	this->SetSize(640,250+answer_t.size()*55);
	
	back_b->SetPosition(wxPoint(10,160+55*answer_t.size()));
	check_b->SetPosition(wxPoint(120, 160+55*answer_t.size()));
	forward_b->SetPosition(wxPoint(230, 160+55*answer_t.size()));
	
	//Czemu zabawa z usuwaniem i tworzeniem obiektu? Bo gówno dziwnie się zachowywało przy samej zmianie pozycji
	number_t->Destroy();
	wxIntegerValidator<short> number_v(&question_number);
	number_v.SetRange(1,9999);
	number_t = new wxTextCtrl(this, ID_Number,"", wxPoint(520,165+55*answer_t.size()), wxSize(50,20), wxTE_RIGHT ,number_v);
	
	max_number_t->SetPosition(wxPoint(580,165+55*answer_t.size()));
}

void MyFrame::onNumberChange(wxCommandEvent& event)
{
	long tmp;
	number_t->GetValue().ToLong(&tmp);
	
	if( tmp <= question.size())
	{
		question_number=tmp-1;
		updateText(true);
	}
}

int MyFrame::load_bazunia(wxString filepath)
{
    std::ifstream file;
    file.open(filepath.ToUTF8());
    if(file.good())
    {
		int how_many_answers=answer_t.size();
        std::string line;
        getline(file,line,'#');//do '#' jest komentarz
        while(std::getline(file, line))//ładowanie pytań jako całości (z odpowiedziami)
        {
            bool if_still_question=true;
            Question question_temp;
			if(line!="")
				question_temp.question_s.append(wxString::FromUTF8(line));//pierwsza niepusta linia jest zawsze treścią pytania
			else continue;
			
            while(std::getline(file, line))//obsługa kolejnych linii aż do pustej (czyli przerwy między pytaniami)
            {
				//Szukanie oznak, że to już (kolejna) odpowiedź, a nie kolejna linia pytania albo obecnie wczytywanej odpowiedzi
                int where1=line.find('.');
                int where2=line.find(')');
                if(where1 ==1 || where2==1 || line[0]=='*')
                {
                    if_still_question=false;
                    if(line[0]=='*')//prawidłowa odpowiedź
                    {
                        line.erase(0,1);
                        question_temp.if_correct_answer.push_back(1);
                    } else
                        question_temp.if_correct_answer.push_back(0);
                    line.erase(0,2);
                    question_temp.answer_s.push_back(wxString::FromUTF8(line));
                } else if(line=="")
                            break;
                else if(if_still_question)
				{
					//question_temp.question_s.append(" ");
					question_temp.question_s.append(wxString::FromUTF8(line));
				}
                else
                {
                     //question_temp.answer_s.back().append(" ");
                     question_temp.answer_s.back().append(wxString::FromUTF8(line));
                }
            }
			if(how_many_answers<question_temp.if_correct_answer.size())
				how_many_answers=question_temp.if_correct_answer.size();
            question.push_back(question_temp);
        }
		setAnswerBoxes(how_many_answers);
	}
    else
    {
        wxLogError(L"Nie można załadować pliku.");
        return 1;
    }
    file.close();
    return 0;
}

//Do zrobienia: o programie, licencja, wersja Win, obrazki