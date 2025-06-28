#include "MainFrame.h"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_PAINT(MainFrame::DrawBoard)
EVT_LEFT_DOWN(MainFrame::OnGridClick)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title), currentPlayer(Player::Red), gameOver(false)
{
    panel = new wxPanel(this, wxID_ANY);
    panel->SetBackgroundColour(wxColour(30, 30, 60));

    wxButton* resetButton = new wxButton(panel, wxID_ANY, "New Game", wxPoint(10, 10), wxSize(100, 30));
    resetButton->Bind(wxEVT_BUTTON, &MainFrame::ResetGame, this);

    statusText = new wxStaticText(panel, wxID_ANY, "", wxPoint(120, 15));
    statusText->SetForegroundColour(*wxWHITE);
    statusText->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    InitializeBoard();
    UpdateStatus();

    panel->Bind(wxEVT_PAINT, &MainFrame::DrawBoard, this);
    panel->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnGridClick, this);
}

void MainFrame::InitializeBoard()
{
    board.clear();
    board.resize(6, std::vector<Player>(7, Player::None));
    currentPlayer = Player::Red;
    gameOver = false;
}

void MainFrame::DrawBoard(wxPaintEvent& evt)
{
    wxPaintDC dc(panel);
    dc.SetPen(*wxWHITE_PEN);

    // Draw board background
    dc.SetBrush(wxBrush(wxColour(0, 0, 139))); // Dark blue
    dc.DrawRectangle(50, 100, 600, 500);

    // Draw grid
    for (int row = 0; row < 6; ++row)
    {
        for (int col = 0; col < 7; ++col)
        {
            wxColour circleColor;
            switch (board[row][col])
            {
            case Player::Red: circleColor = wxColour(255, 0, 0); break;
            case Player::Yellow: circleColor = wxColour(255, 255, 0); break;
            default: circleColor = wxColour(200, 200, 200); // Light gray for empty
            }

            dc.SetBrush(wxBrush(circleColor));
            dc.DrawCircle(100 + col * 80, 150 + row * 80, 30);
        }
    }
}

void MainFrame::OnGridClick(wxMouseEvent& evt)
{
    if (gameOver) return;

    wxPoint pos = evt.GetPosition();
    if (pos.y < 100 || pos.y > 580 || pos.x < 50 || pos.x > 650) return;

    int col = (pos.x - 50) / 80;
    if (col < 0 || col >= 7) return;

    // Find the first empty row in the selected column
    for (int row = 5; row >= 0; --row)
    {
        if (board[row][col] == Player::None)
        {
            board[row][col] = currentPlayer;

            if (CheckWin(row, col))
            {
                gameOver = true;
                UpdateStatus();
                panel->Refresh();
                return;
            }

            // Check for draw
            bool isDraw = true;
            for (int r = 0; r < 6 && isDraw; ++r)
            {
                for (int c = 0; c < 7 && isDraw; ++c)
                {
                    if (board[r][c] == Player::None)
                    {
                        isDraw = false;
                    }
                }
            }

            if (isDraw)
            {
                gameOver = true;
                UpdateStatus();
                panel->Refresh();
                return;
            }

            currentPlayer = (currentPlayer == Player::Red) ? Player::Yellow : Player::Red;
            UpdateStatus();
            panel->Refresh();
            return;
        }
    }
}

void MainFrame::ResetGame(wxCommandEvent& evt)
{
    InitializeBoard();
    UpdateStatus();
    panel->Refresh();
}

void MainFrame::UpdateStatus()
{
    if (gameOver)
    {
        bool isDraw = true;
        for (const auto& row : board)
        {
            for (const auto& cell : row)
            {
                if (cell == Player::None)
                {
                    isDraw = false;
                    break;
                }
            }
            if (!isDraw) break;
        }

        if (isDraw)
        {
            statusText->SetLabel("Game Over: It's a draw!");
        }
        else
        {
            wxString winner = (currentPlayer == Player::Red) ? "Red" : "Yellow";
            statusText->SetLabel(wxString::Format("Game Over: %s wins!", winner));
        }
    }
    else
    {
        wxString player = (currentPlayer == Player::Red) ? "Red" : "Yellow";
        statusText->SetLabel(wxString::Format("Current Player: %s", player));
    }
}

bool MainFrame::CheckWin(int row, int col)
{
    // Check all possible directions
    return CheckDirection(row, col, 0, 1) ||  // Horizontal
        CheckDirection(row, col, 1, 0) ||  // Vertical
        CheckDirection(row, col, 1, 1) ||  // Diagonal down-right
        CheckDirection(row, col, -1, 1);   // Diagonal up-right
}

bool MainFrame::CheckDirection(int row, int col, int rowDir, int colDir)
{
    Player player = board[row][col];
    int count = 1;

    // Check in positive direction
    for (int i = 1; i < 4; ++i)
    {
        int r = row + i * rowDir;
        int c = col + i * colDir;
        if (r < 0 || r >= 6 || c < 0 || c >= 7 || board[r][c] != player)
            break;
        count++;
    }

    // Check in negative direction
    for (int i = 1; i < 4; ++i)
    {
        int r = row - i * rowDir;
        int c = col - i * colDir;
        if (r < 0 || r >= 6 || c < 0 || c >= 7 || board[r][c] != player)
            break;
        count++;
    }

    return count >= 4;
}
