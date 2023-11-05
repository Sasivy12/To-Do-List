#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);

private:
	void Controls();
	void BindEVTs();

	void OnAddButtonClicked(wxCommandEvent& evt);
	void AddTask();

	void CheckButtons(wxKeyEvent& evt);
	void MoveTask(int pos);
	void SwapTask(int i, int j);
	void DeleteTask();

	void OnClearButtonClicked(wxCommandEvent& evt);
	void ClearTasks();

	wxPanel* panel;
	wxStaticText* head_text;
	wxTextCtrl* input_task;
	wxButton* task_button;
	wxCheckListBox* task_box;
	wxButton* clear_button;
};
