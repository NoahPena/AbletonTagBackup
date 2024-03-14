#include "Main.h"
#include "MainFrame.h"

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello Everyone!", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~wxMAXIMIZE_BOX);
	// MyFrame *frame = new MyFrame("Hello Everyone!");
	// frame->SetMinSize(frame->GetSize());
	// frame->SetMaxSize(frame->GetSize());
	
    frame->Show(true);
    return true;
}
