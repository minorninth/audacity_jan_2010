/**********************************************************************

  Audacity: A Digital Audio Editor

  FileDialog.h

  Leland Lucius

*******************************************************************//**

\class FileDialog
\brief Dialog used to present platform specific "Save As" dialog with
custom controls.

*//*******************************************************************/

#ifndef _FILE_DIALOG_H_
#define _FILE_DIALOG_H_

#include "wx/defs.h"
#include "wx/filedlg.h"

typedef void (*fdCallback)(void *, int);

#if defined(__WXMAC__)
#include "mac/FileDialog.h"
#elif defined(__WXMSW__)
#include "win/FileDialog.h"
#elif defined(__FORCE_WXGTK__)
#include "gtk/FileDialog.h"
#else
#include "generic/FileDialog.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// Name:        filedlg.h
// Purpose:     wxFileDialog base header
// Author:      Robert Roebling
// Modified by: Leland Lucius
// Created:     8/17/99
// Copyright:   (c) Robert Roebling
// RCS-ID:      $Id: filedlg.h,v 1.39 2005/03/16 16:18:18 ABX Exp $
// Licence:     wxWindows licence
//
// Modified for Audacity to support an additional button on Save dialogs
//
/////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// wxFileDialog convenience functions
//----------------------------------------------------------------------------

// File selector - backward compatibility
WXDLLEXPORT wxString
FileSelector(const wxChar *message = wxFileSelectorPromptStr,
             const wxChar *default_path = NULL,
             const wxChar *default_filename = NULL,
             const wxChar *default_extension = NULL,
             const wxChar *wildcard = wxFileSelectorDefaultWildcardStr,
             int flags = 0,
             wxWindow *parent = NULL,
             wxString label = wxEmptyString,
             fdCallback cb = NULL,
             void *cbdata = NULL);

#endif
