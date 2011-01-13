#ifndef BASE_H
#define BASE_H

#include <vector>
#include <wx/string.h>
#include <wx/choice.h>
#include <wx/cmndata.h>
#include <wx/listbox.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/app.h>
#include <wx/frame.h>

class wxSocketEvent;
class wxTaskBarIcon;
class wxFileConfig;
class wxSocketClient;

struct version {
    int ID;
    wxString Name;
};

class MoosApp: public wxApp {
public:
    virtual bool OnInit();
};

class MainFrame: public wxFrame {
public:
    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    ~MainFrame();
//base.cpp - Common
    void OnSelectChannel(wxCommandEvent &event);
    void OnSelectUser(wxCommandEvent& event);
    void OnWhisperClick(wxCommandEvent& event);
    void OnSendMessage(wxCommandEvent& WXUNUSED(event));
    void OnText(wxCommandEvent& event);
    wxString AutoComplete(wxString Beginning, wxString Ending=L"", int Ignored=0);
    void Message(wxString Text, wxString Input0=L"", wxString Input1=L"", wxString Input2=L"", wxString Input3=L"");
    void AddChannel(wxString Channel);
    void SetChannel(wxString Channel);
    void RemoveChannel(wxString Channel);
    void RemoveAllChannelsAndUsers();
    void RefreshAutocomplete(wxString User, bool Event=true);
//connection.cpp - Socket
    void OnSocketEvent(wxSocketEvent& event);
    void OnConnectionLost();
    void OnConnect();
    void OnIncomingData();
    void ParseProcessCommand(wxString strData);
    wxString GetVersion(wxString ID);
    std::string EncodeMessage(const std::string Message);
    std::string GetInvertedLength(const unsigned int &Length);
    std::string GenerateLoginMessage(wxString User, wxString Password);
    void Write(wxString Data);
    void LoginAs(wxString User, wxString Password, wxString Server=L"", wxString Port=L"");
//moosmenu.cpp - Moos Menu
    void OnLoginAs(wxCommandEvent &event);
    void OnLogout(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
//usermenu.cpp - User Menu
    void OnWhoisUser(wxCommandEvent &event);
    void OnSlapUser(wxCommandEvent &event);
    void OnIgnoreUser(wxCommandEvent &event);
    void OnIgnoreList(wxCommandEvent & WXUNUSED(event));
    void AddUser(wxString Username);
    void IgnoreUser(wxString User);
    void UnignoreUser(wxString User);
    bool IsIgnored(wxString User);
    void RemoveUser(wxString User);
    void RemoveAllUsers();
//viewmenu.cpp - Ansicht Menu
    void OnSaveChat(wxCommandEvent &event);
    void OnFreezeChat(wxCommandEvent & WXUNUSED(event));
    void OnDeleteChat(wxCommandEvent &event);
    void OnColorSelect(wxCommandEvent & WXUNUSED(event));
    void OnManualColorCode(wxCommandEvent & WXUNUSED(event));
//settingsmenu.cpp - Settings Menu
    void OnAutoLoginAccount(wxCommandEvent& event);
    void OnBeepSound(wxCommandEvent& event);
    void OnDisableSlaps(wxCommandEvent& event);
    void OnChangeFont(wxCommandEvent & WXUNUSED(event));
    void OnSelectLanguage(wxCommandEvent & WXUNUSED(event));
//helpmenu.cpp - Help Menu
    void OnOnlineReadme(wxCommandEvent &event);
    void OnMailBugs(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
private:
//Variablen
    wxBoxSizer *MainSizer;
    wxBoxSizer *ListSizer;
    wxBoxSizer *ChatSizer;
    wxBoxSizer *InputSizer;
    wxString ChatHistory, LastInput;
    wxArrayString ChatBuffer, SeenUsers;
    wxListBox *UserList, *IgnoredUserList;
    wxFontData Font;
    wxChoice *ChannelSwitcher;
    wxTextCtrl *ChatView, *ChatInput;
    wxCheckBox *WhisperCheckbox;
    wxMenu *MoosMenu, *UserMenu, *ViewMenu, *SettingsMenu, *HelpMenu;
    wxTaskBarIcon *MoosIcon;
    wxMenuBar *MenuBar;
    wxFileConfig *MoosIni, *LangIni;
    wxSocketClient *Socket;
    bool DisableOnText;
    wxString LoginName, LoginPassword;
    std::vector<version> GameVersion;

    DECLARE_EVENT_TABLE()
};

#endif