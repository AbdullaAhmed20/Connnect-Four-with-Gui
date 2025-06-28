/*#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <vector>

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);

private:
    void CreateStartPanel();
    void CreateGamePanel();
    void CreateNameDialog();
    void ShowStartPanel();
    void ShowGamePanel();
    void ResetGame();
    void ComputerMove();
    void CheckWinner();
    void AnnounceWinner(int player);

    void OnVsComputerClicked(wxCommandEvent& event);
    void OnVsPlayerClicked(wxCommandEvent& event);
    void OnStartButtonClicked(wxCommandEvent& event);
    void OnGameButtonClicked(wxCommandEvent& event);
    void OnResetButtonClicked(wxCommandEvent& event);

    wxPanel* startPanel;
    wxPanel* gamePanel;
    wxButton* vsComputerButton;
    wxButton* vsPlayerButton;
    wxButton* buttons[9];
    wxButton* startButton;
    wxButton* resetButton;
    wxStaticText* statusText;

    int board[9];
    bool currentPlayer;
    bool gameEnded;
    bool gameAgainstComputer;

    wxString player1Name;
    wxString player2Name;

    wxDECLARE_EVENT_TABLE();
};

#endif*/

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