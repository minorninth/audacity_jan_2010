/**********************************************************************

  Audacity: A Digital Audio Editor

  TimeTextCtrl.h

  Dominic Mazzoni

  See TimeTextCtrl.cpp for documentation on how to use the
  format string to specify how a TimeTextCtrl's fields are
  laid out.

**********************************************************************/

#ifndef __AUDACITY_TIME_TEXT_CTRL__
#define __AUDACITY_TIME_TEXT_CTRL__

#include <wx/defs.h>
#include <wx/event.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/string.h>
#include <wx/textctrl.h>

#if wxUSE_ACCESSIBILITY
#if defined(__WXMSW__)
#include <oleacc.h>
#endif
#include <wx/access.h>
#endif

DECLARE_EVENT_TYPE(EVT_TIMETEXTCTRL_UPDATED, -1);

class TimeField;
WX_DECLARE_OBJARRAY(TimeField, TimeFieldArray);

class DigitInfo;
WX_DECLARE_OBJARRAY(DigitInfo, DigitInfoArray);

class TimeTextCtrl: public wxControl
{
   friend class TimeTextCtrlAx;

 public:
   DECLARE_DYNAMIC_CLASS(TimeTextCtrl);

   TimeTextCtrl(wxWindow *parent,
                wxWindowID id,
                wxString formatString = wxT(""),
                double timeValue = 0.0,
                double sampleRate = 44100,
                const wxPoint &pos = wxDefaultPosition,
                const wxSize &size = wxDefaultSize,
                bool autoPos = false);

   virtual ~TimeTextCtrl();

   virtual bool Layout();
   virtual void Fit();

   void SetFormatString(wxString formatString);
   void SetSampleRate(double sampleRate);
   void SetTimeValue(double newTime);
   const double GetTimeValue();

   wxString GetTimeString();

   static int GetNumBuiltins();
   static wxString GetBuiltinName(int index);
   static wxString GetBuiltinFormat(int index);
   static wxString GetBuiltinFormat(const wxString &name);

   void EnableMenu(bool enable = true);

private:

   void OnCaptureKey(wxCommandEvent &event);
   void OnKeyDown(wxKeyEvent &event);
   void OnMouse(wxMouseEvent &event);
   void OnPaint(wxPaintEvent &event);
   void OnFocus(wxFocusEvent &event);
   void OnContext(wxContextMenuEvent &event);
   void OnMenu(wxCommandEvent &event);

   void ParseFormatString();

   void ValueToControls();
   void ControlsToValue();

   void PrintDebugInfo();

   void SetFieldFocus(int digit);
   void Updated();
   void Increase(int steps);
   void Decrease(int steps);

   double         mTimeValue;
   double         mSampleRate;
   wxString       mFormatString;
   wxString       mValueString;
   wxString       mValueTemplate;
   wxString       mValueMask;

   bool           mMenuEnabled;

   wxString       mPrefix;

   wxBitmap      *mBackgroundBitmap;

   wxFont        *mDigitFont;
   wxFont        *mLabelFont;
   int            mDigitBoxW;
   int            mDigitBoxH;
   int            mDigitW;
   int            mDigitH;
   int            mBorderLeft;
   int            mBorderTop;
   int            mBorderRight;
   int            mBorderBottom;
   int            mWidth;
   int            mHeight;
   int            mButtonWidth;

   int            mFocusedDigit;
   int            mLastField;

   DigitInfoArray mDigits;

   TimeFieldArray mFields;
   double         mScalingFactor;
   bool           mNtscDrop;

   DECLARE_EVENT_TABLE()
};

#if wxUSE_ACCESSIBILITY

class TimeTextCtrlAx: public wxWindowAccessible
{
public:
   TimeTextCtrlAx(wxWindow * window);

   virtual ~ TimeTextCtrlAx();

   // Performs the default action. childId is 0 (the action for this object)
   // or > 0 (the action for a child).
   // Return wxACC_NOT_SUPPORTED if there is no default action for this
   // window (e.g. an edit control).
   virtual wxAccStatus DoDefaultAction(int childId);

   // Retrieves the address of an IDispatch interface for the specified child.
   // All objects must support this property.
   virtual wxAccStatus GetChild( int childId, wxAccessible** child );

   // Gets the number of children.
   virtual wxAccStatus GetChildCount(int* childCount);

   // Gets the default action for this object (0) or > 0 (the action for a child).
   // Return wxACC_OK even if there is no action. actionName is the action, or the empty
   // string if there is no action.
   // The retrieved string describes the action that is performed on an object,
   // not what the object does as a result. For example, a toolbar button that prints
   // a document has a default action of "Press" rather than "Prints the current document."
   virtual wxAccStatus GetDefaultAction( int childId, wxString *actionName );

   // Returns the description for this object or a child.
   virtual wxAccStatus GetDescription( int childId, wxString *description );

   // Gets the window with the keyboard focus.
   // If childId is 0 and child is NULL, no object in
   // this subhierarchy has the focus.
   // If this object has the focus, child should be 'this'.
   virtual wxAccStatus GetFocus( int *childId, wxAccessible **child );

   // Returns help text for this object or a child, similar to tooltip text.
   virtual wxAccStatus GetHelpText( int childId, wxString *helpText );

   // Returns the keyboard shortcut for this object or child.
   // Return e.g. ALT+K
   virtual wxAccStatus GetKeyboardShortcut( int childId, wxString *shortcut );

   // Returns the rectangle for this object (id = 0) or a child element (id > 0).
   // rect is in screen coordinates.
   virtual wxAccStatus GetLocation( wxRect& rect, int elementId );

   // Gets the name of the specified object.
   virtual wxAccStatus GetName( int childId, wxString *name );

   // Returns a role constant.
   virtual wxAccStatus GetRole( int childId, wxAccRole *role );

   // Gets a variant representing the selected children
   // of this object.
   // Acceptable values:
   // - a null variant (IsNull() returns TRUE)
   // - a list variant (GetType() == wxT("list"))
   // - an integer representing the selected child element,
   //   or 0 if this object is selected (GetType() == wxT("long"))
   // - a "void*" pointer to a wxAccessible child object
   virtual wxAccStatus GetSelections( wxVariant *selections );

   // Returns a state constant.
   virtual wxAccStatus GetState(int childId, long* state);

   // Returns a localized string representing the value for the object
   // or child.
   virtual wxAccStatus GetValue(int childId, wxString* strValue);

private:
   TimeTextCtrl *mCtrl;
};

#endif // wxUSE_ACCESSIBILITY

#endif // __AUDACITY_TIME_TEXT_CTRL__

// Indentation settings for Vim and Emacs.
// Please do not modify past this point.
//
// Local Variables:
// c-basic-offset: 3
// indent-tabs-mode: nil
// End:
//
// vim: et sts=3 sw=3
// 

