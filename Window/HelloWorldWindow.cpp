//
// Created by Руслан Москвитин on 15.09.2024.
//

#include "HelloWorldWindow.h"

#define SEEKSLIDER_MAXVALUE 20000


static gboolean link_elements_with_filter(GstElement* element1, GstElement* element2)
{
	gboolean link_ok;
	GstCaps* caps;

	caps = gst_caps_from_string("video/x-raw,width=1920,height=1080,framerate=25/1");

	link_ok = gst_element_link_filtered(element1, element2, caps);
	gst_caps_unref(caps);

	if (!link_ok) {
		g_warning("Failed to link element1 and element2!");
	}

	return link_ok;
}

/* playbin flags */
typedef enum {
	GST_PLAY_FLAG_VIDEO = (1 << 0), /* We want video output */
	GST_PLAY_FLAG_AUDIO = (1 << 1), /* We want audio output */
	GST_PLAY_FLAG_TEXT = (1 << 2)  /* We want subtitle output */
} GstPlayFlags;


HelloWorldWindow::HelloWorldWindow(wxWindow* parent)
	: wxFrame(parent, wxID_ANY, wxT("Hello wxDC"), wxPoint(50, 50), wxSize(1285, 850))
{



	wxStatusBar* stb = new wxStatusBar(this, wxID_ANY, wxSTB_SIZEGRIP);
	int widths[] = { -1, 80, 124 }; // {elastic width, 100 pixels, 100 pixels}
	int styles[] = { wxSB_SUNKEN,wxSB_SUNKEN, wxSB_SUNKEN };
	stb->SetFieldsCount(3, widths); // Replace the above two commands
	stb->SetStatusStyles(3, styles);
	// ----- Initialize Text for Status Bar -----
	stb->SetStatusText("Field 1", 0);
	stb->SetStatusText("Field 2", 1);
	stb->SetStatusText("Field 3", 2);
	// Assign the status bar to the frame
	SetStatusBar(stb); // Uncomment this line to set stb as status bar of the frame



	wxMenuBar* mnuBar = new wxMenuBar();
	wxMenu* mnuFile = new wxMenu();
	wxMenu* mnuHelp = new wxMenu();
	wxMenuItem* mnuOpen = new wxMenuItem(mnuFile, wxID_OPEN, "&Открыть",
		"Открыть файл из локального хранилища");
	wxMenuItem* mnuExit = new wxMenuItem(mnuFile, wxID_EXIT,
		"Выход\tAlt+X", "Выйти из программы");
	wxMenuItem* mnuAbout = new wxMenuItem(mnuHelp, wxID_ABOUT, "О программе\tF1",
		"Инфа о программе");
	// Add wxMenuItem to wxMenu
	mnuFile->Append(mnuOpen);
	mnuFile->AppendSeparator();
	mnuFile->Append(mnuExit);
	mnuHelp->Append(mnuAbout);
	// Add wxMenu to wxMenuBar
	mnuBar->Append(mnuFile, "&File");
	mnuBar->Append(mnuHelp, "&Help");
	// Assign the menu bar to the frame
	SetMenuBar(mnuBar);



	wxPanel* bg = new wxPanel(this, wxID_ANY);
	m_renderWindow = new wxWindow(bg, wxID_ANY, wxPoint(50, 50), wxSize(285, 50));
	bg->SetBackgroundColour(*wxWHITE);
	m_renderWindow->SetBackgroundColour(*wxBLACK);


	wxBoxSizer* szr1 = new wxBoxSizer(wxVERTICAL);
	szr1->Add(m_renderWindow, wxSizerFlags(1).Expand().Border(wxBOTTOM));
	bg->SetSizer(szr1);

	Layout();
	Center();

	Bind(wxEVT_MENU, &HelloWorldWindow::OnmnuAbout, this, wxID_ABOUT);

	m_xid = 0;
	m_pipeline = NULL;


	//GstElement* source = gst_element_factory_make("videotestsrc", "source");
	//g_object_set(source, "pattern", 25, NULL);

	GstElement* source = gst_element_factory_make("playbin", "source");

	g_object_set(source, "uri", "https://gstreamer.freedesktop.org/data/media/sintel_trailer-480p.webm", NULL);
	//g_object_set(source, "uri", "file:////dir/file_1080p.mkv", NULL);

	GstElement* customoutput = gst_bin_new("customoutput");
	GstElement* convert = gst_element_factory_make("videoconvert", "vconv");


#ifdef __WXGTK__
	GstElement* sink = gst_element_factory_make("xvimagesink", "sink");
#elif defined __WXMSW__
	GstElement* sink = gst_element_factory_make("d3dvideosink", "sink");
#elif defined __WXMAC__
	GstElement* sink = gst_element_factory_make("osxvideosink", "sink");
#endif
	WXWidget hwnd = m_renderWindow->GetHandle();
	gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(sink),
		reinterpret_cast<guintptr>(hwnd));

	m_pipeline = gst_pipeline_new("test-pipeline");

	if (!m_pipeline || !source || !sink || !convert || !customoutput)
	{
		wxLogError("Not all elements could be created.");
		return;
	}


	// Build the pipeline
	//gst_bin_add_many(GST_BIN(m_pipeline), source, convert, sink, NULL);
	gst_bin_add_many(GST_BIN(customoutput), convert, sink, NULL);

	if (gst_element_link(convert, sink) != TRUE)
	{
		wxLogWarning("Elements convert, sink could not be linked.");
		gst_object_unref(m_pipeline);
		m_pipeline = NULL;
		return;
	}

	//if (link_elements_with_filter(source, convert) != TRUE)
	//{
	//	wxLogWarning("Elements source, convert could not be linked.");
	//	gst_object_unref(m_pipeline);
	//	m_pipeline = NULL;
	//	return;
	//}


	GstPad* sinkpad, * ghost_sinkpad;
	sinkpad = gst_element_get_static_pad(convert, "sink");
	ghost_sinkpad = gst_ghost_pad_new("sink", sinkpad);
	gst_pad_set_active(ghost_sinkpad, TRUE);
	gst_element_add_pad(customoutput, ghost_sinkpad);
	g_object_set(source, "video-sink", customoutput, NULL);


	gst_bin_add_many(GST_BIN(m_pipeline), source, NULL);



	GstStateChangeReturn  ret =
		gst_element_set_state(m_pipeline, GST_STATE_PLAYING);

	//if (ret == GST_STATE_CHANGE_FAILURE)
	//{
	//	wxLogWarning(" GST_STATE_CHANGE_FAILURE");
	//	gst_object_unref(m_pipeline);
	//	m_pipeline = NULL;
	//}

}


HelloWorldWindow::~HelloWorldWindow()
{

}

void HelloWorldWindow::OnmnuAbout(wxCommandEvent& event)
{
	const gchar* nano_str;
	guint major, minor, micro, nano, wxmajor, wxminor, wxmicro;
	gst_version(&major, &minor, &micro, &nano);

	if (nano == 1)
		nano_str = "(CVS)";
	else if (nano == 2)
		nano_str = "(Prerelease)";
	else
		nano_str = "";
	char msg2buf[100];

	wxmajor = wxGetLibraryVersionInfo().GetMajor();
	wxminor = wxGetLibraryVersionInfo().GetMinor();
	wxmicro = wxGetLibraryVersionInfo().GetMicro();

	sprintf(msg2buf, "WxWigets %d.%d.%d\nGStreamer %d.%d.%d %s\n",
		wxmajor, wxminor, wxmicro,major, minor, micro, nano_str);

	wxMessageBox(msg2buf,
		"Информация о сборочке", wxICON_INFORMATION);
}