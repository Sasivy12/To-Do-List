#include "MainFrame.h"
#include "Task.h"
#include <wx/wx.h>
#include <vector>
#include <string>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	Controls();
	BindEVTs();
}

void MainFrame::Controls()
{
	wxFont head_font(wxFontInfo(wxSize(0, 36)).Bold());
	wxFont mainfont(wxFontInfo(wxSize(0, 20)));

	panel = new wxPanel(this);
	panel->SetFont(mainfont);

	head_text = new wxStaticText(panel, wxID_ANY, "TO-DO List", wxPoint(0, 25), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	head_text->SetFont(head_font);

	input_task = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(80, 90), wxSize(500, 35));

	task_button = new wxButton(panel, wxID_ANY, "Add Task", wxPoint(600, 90), wxSize(100, 35));

	task_box = new wxCheckListBox(panel, wxID_ANY, wxPoint(80, 150), wxSize(620, 350));

	clear_button = new wxButton(panel, wxID_ANY, "Clear", wxPoint(80, 520), wxSize(100, 35));

}

void MainFrame::BindEVTs()
{
	task_button->Bind(wxEVT_BUTTON, &MainFrame::OnAddButtonClicked, this);
	clear_button->Bind(wxEVT_BUTTON, &MainFrame::OnClearButtonClicked, this);
	task_box->Bind(wxEVT_KEY_DOWN, &MainFrame::CheckButtons, this);
}

void MainFrame::OnAddButtonClicked(wxCommandEvent& evt)
{
	AddTask();
}

void MainFrame::AddTask()
{
	wxString descript = input_task->GetValue();
	
	if (!descript.IsEmpty())
	{
		task_box->Insert(descript, task_box->GetCount());
		input_task->Clear();
	}
	input_task->SetFocus();
}

void MainFrame::CheckButtons(wxKeyEvent& evt)
{
	int key = evt.GetKeyCode();
	switch (key)
	{
	case WXK_DELETE:
		DeleteTask();
		break;

	case WXK_UP:
		MoveTask(-1);
		break;
	

	case WXK_DOWN:
		MoveTask(1);
		break;
	}
}


void MainFrame::MoveTask(int pos)

{	int selectedTask = task_box->GetSelection();

	int newPos = selectedTask + pos;

	if (newPos >= 0 && newPos < task_box->GetCount())
	{
			SwapTask(selectedTask, newPos);
			task_box->SetSelection(newPos, true);
	}
}

void MainFrame::SwapTask(int i, int j)
{
	Task taskI{ task_box->GetString(i).ToStdString(), task_box->IsChecked(i) };
	Task taskJ{ task_box->GetString(j).ToStdString(), task_box->IsChecked(j) };

	task_box->SetString(i, taskJ.descr);
	task_box->Check(i, taskJ.done);
	task_box->SetString(j, taskI.descr);
	task_box->Check(j, taskI.done);
}

void MainFrame::DeleteTask()
{
	if (task_box->GetSelection() != wxNOT_FOUND)
	{
		task_box->Delete(task_box->GetSelection());
	}
	else
	{
		return;
	}
}

void MainFrame::OnClearButtonClicked(wxCommandEvent& evt)
{
	task_box->Clear();
}
