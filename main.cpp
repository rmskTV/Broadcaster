#include "main.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(MyApp);

MyApp::MyApp()
{
}

MyApp::~MyApp()
{
}

bool MyApp::OnInit()
{
    ::wxInitAllImageHandlers();
    putenv("GST_DEBUG_DUMP_DOT_DIR=/Users/ruslanmoskvitin/REPOSITORY/Broadcaster/gstDebug");
    putenv("GST_DEBUG_FILE=/Users/ruslanmoskvitin/REPOSITORY/Broadcaster/gstDebug/log.txt");
    putenv("GST_DEBUG=3");

    gst_init(NULL, NULL);


    MainWindow* mw = NULL;
    mw = new MainWindow(NULL);
    if (mw) // If Instantiated object exists...
    {

        mw->Show(true);
        SetTopWindow(mw); // Set the window on top of others on your screen

        //std::async(std::launch::async, DiscovererInfo::DSConMonitoring, mw->fileList);

        return true; // Return back to wxWidget system loop
    }
    else // If Instantiated object does not exist...
    {
        wxMessageBox("Window was not created!\n"
            "This application will be terminated now!",
            "Error", wxICON_ERROR);
        return false;
    }


}
