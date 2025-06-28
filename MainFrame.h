#ifndef CONNECTFOUR_MAINFRAME_H
#define CONNECTFOUR_MAINFRAME_H

#include <wx/wx.h>
#include <vector>

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);

private:
    enum class Player { None, Red, Yellow };

    wxPanel* panel;
    wxStaticText* statusText;
    std::vector<std::vector<Player>> board;
    Player currentPlayer;
    bool gameOver;

    void InitializeBoard();
    void DrawBoard(wxPaintEvent& evt);
    void OnGridClick(wxMouseEvent& evt);
    void ResetGame(wxCommandEvent& evt);
    void UpdateStatus();
    bool CheckWin(int row, int col);
    bool CheckDirection(int row, int col, int rowDir, int colDir);

    wxDECLARE_EVENT_TABLE();
};

#endif // CONNECTFOUR_MAINFRAME_H
