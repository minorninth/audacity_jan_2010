/**********************************************************************

  Audacity: A Digital Audio Editor

  LinkingHtmlWindow.cpp

  Vaughan Johnson
  Dominic Mazzoni

  utility fn and 
  descendant of wxHtmlWindow that opens links in the user's 
  default browser
  
**********************************************************************/

#include "LinkingHtmlWindow.h"
#include <wx/mimetype.h>
#include "../HelpText.h"

void OpenInDefaultBrowser(const wxHtmlLinkInfo& link)
{
   #ifdef __WXMAC__
      wxString openCmd = wxT("open ") + link.GetHref();
      ::wxExecute(openCmd);
   #else
      #ifdef __WXMSW__
         wxFileType* pFileType = wxTheMimeTypesManager->GetFileTypeFromExtension(wxT(".htm"));
         if (pFileType == NULL) 
            return;
         wxString openCmd = pFileType->GetOpenCommand(link.GetHref());
         if (openCmd.Contains(wxT("iexplore.exe")))
            // GetOpenCommand is not quite right for Internet Explorer.
            openCmd.Replace(wxT("WWW_OpenURL#\"file://"), wxT("WWW_OpenURL#\""));
         ::wxExecute(openCmd);
         delete pFileType;
      #else
         wxLaunchDefaultBrowser(Url);
      #endif
   #endif
};

LinkingHtmlWindow::LinkingHtmlWindow(wxWindow *parent, wxWindowID id /*= -1*/, 
                                       const wxPoint& pos /*= wxDefaultPosition*/, 
                                       const wxSize& size /*= wxDefaultSize*/, 
                                       long style /*= wxHW_SCROLLBAR_AUTO*/) :
   wxHtmlWindow(parent, id, pos, size, style)
{
}

void LinkingHtmlWindow::OnLinkClicked(const wxHtmlLinkInfo& link)
{
   wxString href = link.GetHref();
   if( href.StartsWith(wxT("innerlink:")) )
   {
      this->SetPage( HelpText( href.Mid( 10 )));
      this->GetParent()->SetLabel( TitleText( href.Mid( 10 )));
      return;
   }
   OpenInDefaultBrowser(link);
}
