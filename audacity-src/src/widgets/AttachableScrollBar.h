/**********************************************************************

  Audacity: A Digital Audio Editor

  AttachableScrollBar.h

  James Crook
 
  A scroll bar that can be attached to multiple items and so control 
  their scrolling.

  Audacity is free software.
  This file is licensed under the wxWindows license, see License.txt

**********************************************************************/


#pragma once
#include <wx/scrolbar.h>

struct ViewInfo;

class AttachableScrollBar :
	public wxScrollBar
{
public:
	AttachableScrollBar(
	wxWindow* parent, 
	wxWindowID id, 
	const wxPoint& pos = wxDefaultPosition, 
	const wxSize& size = wxDefaultSize, 
	long style = wxSB_HORIZONTAL);
public:
	~AttachableScrollBar(void);
	void OnScroll(wxScrollEvent & event);
	void SetViewInfo( ViewInfo * view );

   void SetScrollBarFromViewInfo();
   void SetViewInfoFromScrollBar();

	ViewInfo * mpViewInfo;
   DECLARE_EVENT_TABLE();
};
