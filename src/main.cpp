#include "Main.h"
#include "MainFrame.h"

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello Everyone!", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}
