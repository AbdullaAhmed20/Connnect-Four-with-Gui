#include "App.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(ConnectFourApp);

bool ConnectFourApp::OnInit()
{
    MainFrame* mainFrame = new MainFrame("Connect Four");
    mainFrame->SetClientSize(700, 600);
    mainFrame->Center();
    mainFrame->Show();
    return true;
}
