/**********************************************************************

  Audacity: A Digital Audio Editor

  LabelTrack.cpp

  Dominic Mazzoni

**********************************************************************/

#include <wx/brush.h>
#include <wx/dc.h>
#include <wx/event.h>
#include <wx/pen.h>
#include <wx/string.h>
#include <wx/textfile.h>
#include <wx/intl.h>
#include <wx/icon.h>

#include <wx/log.h>

#include "LabelTrack.h"
#include "DirManager.h"
#include "Internat.h"

#include <iostream>
using std::cout;
using std::endl;

// static member variables.
bool LabelTrack::mbGlyphsReady=false;
// We have several variants of the icons (highlighting).
// The icons are draggable, and you can drag one boundary
// or all boundaries at the same timecode depending on whether you 
// click the centre (for all) or the arrow part (for one).
// Currently we have twelve variants but we're only using six.
wxIcon LabelTrack::mBoundaryGlyphs[ NUM_GLYPH_CONFIGS * NUM_GLYPH_HIGHLIGHTS ];
int LabelTrack::mIconHeight;
int LabelTrack::mIconWidth;
int LabelTrack::mTextHeight;


// TODO: Surely there is a header file which already defines max and min?
int max(int a,int b)
{
   return((a>b)?a:b);
}

int min(int a,int b)
{
   return((a<b)?a:b);
}

LabelTrack *TrackFactory::NewLabelTrack()
{
   return new LabelTrack(mDirManager);
}

LabelTrack::LabelTrack(DirManager * projDirManager):
   Track(projDirManager),
   mIsAdjustingLabel(false),
   mMouseOverLabelLeft(-1),
   mMouseOverLabelRight(-1)
{
   InitColours();
   SetName(_("Label Track"));

   // Label tracks are narrow
   // Default is to allow two rows so that new users get the
   // idea that labels can 'stack' when they would overlap.
   mHeight = 62;     
   CreateCustomGlyphs();
   mSelIndex = -1;
}

LabelTrack::LabelTrack(const LabelTrack &orig) :
   Track(orig),
   mIsAdjustingLabel(false),
   mMouseOverLabelLeft(-1),
   mMouseOverLabelRight(-1)
{
   InitColours();

   int len = orig.mLabels.Count();

   for (int i = 0; i < len; i++) {
      LabelStruct *l = new LabelStruct();
      l->t = orig.mLabels[i]->t;
      l->t1 = orig.mLabels[i]->t1;
      l->title = orig.mLabels[i]->title;
      mLabels.Add(l);
   }

   mSelIndex = orig.mSelIndex;
}

LabelTrack::~LabelTrack()
{
   int len = mLabels.Count();

   for (int i = 0; i < len; i++)
      delete mLabels[i];
}


/// ComputeTextPosition is 'smart' about where to display 
/// the label text.
///
/// The text must be displayed between its endpoints x and x1
/// We'd also like it centered between them, and we'd like it on
/// screen.  It isn't always possible to achieve all of this,
/// so we do the best we can.
///
/// This function has a number of tests and adjustments to the
/// text start position.  The tests later in the function will
/// take priority over the ones earlier, so because centering 
/// is the first thing we do, it's the first thing we lose if 
/// we can't do everything we want to.
void LabelTrack::ComputeTextPosition(wxRect & r, int index)
{
   // xExtra is extra space 
   // between the text and the endpoints.
   const int xExtra=mIconWidth;
   int x     = mLabels[index]->x;  // left endpoint
   int x1    = mLabels[index]->x1; // right endpoint.
   int width = mLabels[index]->width;

   int xText; // This is where the text will end up.

   // Will the text all fit at this zoom?
   bool bTooWideForScreen = width > (r.width-2*xExtra);
// bool bSimpleCentering = !bTooWideForScreen;
   bool bSimpleCentering = false;

   //TODO (possibly):
   // Add configurable options as to when to use simple 
   // and when complex centering.
   //
   // Simple centering does its best to keep the text  
   // centered between the label limits.
   //
   // Complex centering positions the text proportionally
   // to how far we are through the label.
   //
   // If we add preferences for this, we want to be able to
   // choose separately whether:
   //   a) Wide text labels centered simple/complex.
   //   b) Other text labels centered simple/complex.
   //

   if( bSimpleCentering )
   {
      // Center text between the two end points.
      xText = (x+x1-width)/2;
   }
   else
   {
      // Calculate xText position to make text line
      // scroll sideways evenly as r moves right.

      // xText is a linear function of r.x.
      // These variables are used to compute that function.
      int rx0,rx1,xText0,xText1;

      // Since we will be using a linear function,
      // we should blend smoothly between left and right 
      // aligned text as r, the 'viewport' moves.
      if( bTooWideForScreen )
      {
         rx0=x;           // when viewport at label start.
         xText0=x+xExtra; // text aligned left.
         rx1=x1-r.width;  // when viewport end at label end
         xText1=x1-(width+xExtra); // text aligned right.
      }
      else
      {
         // when label start + width + extra spacing at viewport end..
         rx0=x-r.width+width+2*xExtra; 
         // ..text aligned left.
         xText0=x+xExtra;  
         // when viewport start + width + extra spacing at label end..
         rx1=x1-(width+2*xExtra);
         // ..text aligned right.
         xText1=x1-(width+xExtra);
      }

      if( rx1 > rx0 ) // Avoid divide by zero case.
      {
         // Compute the blend between left and right aligned.

         // Don't use:
         //
         // xText = xText0 + ((xText1-xText0)*(r.x-rx0))/(rx1-rx0);
         //
         // The problem with the above is that it integer-oveflows at 
         // high zoom.

         // Instead use:
         xText = xText0 + (int)((xText1-xText0)*(((float)(r.x-rx0))/(rx1-rx0)));
      }
      else
      {
         // Avoid divide by zero by reverting to
         // simple centering.
         //
         // We could also fall into this case if x and x1
         // are swapped, in which case we'll end up
         // left aligned anyway because code later on
         // will catch that.
         xText = (x+x1-width)/2;
      }
   }

   // Is the text now appearing partly outside r? 
   bool bOffLeft = xText < r.x+xExtra;
   bool bOffRight = xText > r.x+r.width-width-xExtra;

   // IF any part of the text is offscreen
   // THEN we may bring it back.
   if( bOffLeft == bOffRight )
   {
      //IF both sides on screen, THEN nothing to do.
      //IF both sides off screen THEN don't do 
      //anything about it.
      //(because if we did, you'd never get to read
      //all the text by scrolling).
   }
   else if( bOffLeft != bTooWideForScreen)
   {
      // IF we're off on the left, OR we're
      // too wide for the screen and off on the right
      // (only) THEN align left.
      xText = r.x+xExtra;
   }
   else
   {
      // We're off on the right, OR we're
      // too wide and off on the left (only)
      // SO align right.
      xText =r.x+r.width-width-xExtra;
   }

   // But if we've taken the text out from its endpoints
   // we must move it back so that it's between the endpoints.
   
   // We test the left end point last because the
   // text might not even fit between the endpoints (at this
   // zoom factor), and in that case we'd like to position 
   // the text at the left end point.
   if( xText > (x1-width-xExtra))
      xText=(x1-width-xExtra);
   if( xText < x+xExtra )
      xText=x+xExtra;

   mLabels[index]->xText = xText;
}

/// ComputeLayout determines which row each label
/// should be placed on, and reserves space for it.
/// Function assumes that the labels are sorted.
void LabelTrack::ComputeLayout( wxRect & r, double h, double pps)
{
   int i;
   int iRow;
   // Rows are the 'same' height as icons or as the text,
   // whichever is taller.
   const int yRowHeight = max(mTextHeight,mIconHeight)+3;// pixels.
   // Extra space at end of rows.
   // We allow space for one half icon at the start and two
   // half icon widths for extra x for the text frame.
   // [we don't allow half a width space for the end icon since it is
   // allowed to be obscured by the text].
   const int xExtra= (3 * mIconWidth)/2;

   const int nRows = min((r.height / yRowHeight) + 1, MAX_NUM_ROWS);
   // Initially none of the rows have been used.
   // So set a value that is less than any valid value.
   const int xStart = r.x -(int)(h*pps) -100;
   for(i=0;i<MAX_NUM_ROWS;i++)
      xUsed[i]=xStart;
   int nRowsUsed=0;

   for (i = 0; i < (int)mLabels.Count(); i++) 
   {
      int x  = r.x + (int) ((mLabels[i]->t  - h) * pps);
      int x1 = r.x + (int) ((mLabels[i]->t1 - h) * pps);
      int y = r.y;

      mLabels[i]->x=x;
      mLabels[i]->x1=x1;
      mLabels[i]->y=-1;// -ve indicates nothing doing.
      iRow=0;
      // Our first preference is a row that ends where we start.
      // (This is to encourage merging of adjacent label boundaries).
      while( (iRow<nRowsUsed) && (xUsed[iRow] != x ))
         iRow++;
      // IF we didn't find one THEN 
      // find any row that can take a span starting at x.
      if( iRow >= nRowsUsed )
      {
         iRow=0;
         while( (iRow<nRows) && (xUsed[iRow] > x ))
            iRow++;
      }
      // IF we found such a row THEN record a valid position.
      if( iRow<nRows )
      {
         // Possibly update the number of rows actually used.
         if( iRow >= nRowsUsed )
            nRowsUsed=iRow+1;
         // Record the position for this label
         y= r.y + iRow * yRowHeight +(yRowHeight/2)+1;
         mLabels[i]->y=y;
         // On this row we have used up to max of end marker and width.
         // Plus also allow space to show the start icon and
         // some space for the text frame.
         xUsed[iRow]=x+mLabels[i]->width+xExtra;
         if( xUsed[iRow] < x1 ) xUsed[iRow]=x1;
         ComputeTextPosition( r, i );
      }
   }
}


/// Draw vertical lines that go exactly through the position
/// of the start or end of a label.
///   @param  dc the device context
///   @param  r  the LabelTrack rectangle.
void LabelStruct::DrawLines( wxDC & dc, wxRect & r)
{
   // How far out from the centre line should the vertical lines
   // start, i.e. what is the y position of the icon?
   // We addjust this slightly so that the line encroaches on 
   // the icon slightly (there is white space in the design).
   const int yIconStart = y - (LabelTrack::mIconHeight /2)+1;
   const int yIconEnd   = yIconStart + LabelTrack::mIconHeight-2;

   if (y<0) 
      return;
   // If y is positive then it is the center line for the 
   // Label.
   if((x  >= r.x) && (x  <= (r.x+r.width)))
   {
      // Draw line above and below left dragging widget.
      dc.DrawLine(x, r.y,  x, yIconStart);
      dc.DrawLine(x, yIconEnd, x, r.y + r.height);
   }
   if((x1 >= r.x) && (x1 <= (r.x+r.width)))
   {
      // Draw line above and below right dragging widget.
      dc.DrawLine(x1, r.y,  x1, yIconStart);
      dc.DrawLine(x1, yIconEnd, x1, r.y + r.height);
   }
}

/// DrawGlyphs draws the wxIcons at the start and end of a label.
///   @param  dc the device context
///   @param  r  the LabelTrack rectangle.
void LabelStruct::DrawGlyphs( wxDC & dc, wxRect & r, int GlyphLeft, int GlyphRight)
{
   if (y<0) 
      return;
   const int xHalfWidth=LabelTrack::mIconWidth/2;
   const int yStart=y-LabelTrack::mIconHeight/2;

   if((x  >= r.x) && (x  <= (r.x+r.width)))
      dc.DrawIcon( LabelTrack::mBoundaryGlyphs[GlyphLeft], x-xHalfWidth,yStart );
   // The extra test here suppresses right hand markers when they overlap
   // the left hand marker (e.g. zoomed out) or are to the left.
   if((x1 >= r.x) && (x1 <= (r.x+r.width)) && (x1>x+LabelTrack::mIconWidth))
      dc.DrawIcon( LabelTrack::mBoundaryGlyphs[GlyphRight], x1-xHalfWidth,yStart );
}

/// Draw the text of the label and also draw
/// a long thin rectangle for its full extent 
/// from x to x1 and a rectangular frame 
/// behind the text itself.
///   @param  dc the device context
///   @param  r  the LabelTrack rectangle.
void LabelStruct::DrawText( wxDC & dc, wxRect & r)
{
   if (y<0) 
      return;
   //If y is positive then it is the center line for the 
   //text we are about to draw.
   const int yBarHeight=3;
   const int yFrameHeight = LabelTrack::mTextHeight+3;
   const int xBarShorten  = LabelTrack::mIconWidth+4;


   // In drawing the bar and the frame, we compute the clipping
   // to the viewport ourselves.  Under Win98 the GDI does its 
   // calculations in 16 bit arithmetic, and so gets it completely 
   // wrong at higher zooms where the bar can easily be 
   // more than 65536 pixels wide.

   // Draw bar for label extent...
   // We don't quite draw from x to x1 because we allow 
   // half an icon width at each end.
   {
      const int xStart=max(r.x,x+xBarShorten/2);
      const int xEnd=min(r.x+r.width,x1-xBarShorten/2);
      const int xWidth = xEnd-xStart;

      if( (xStart < (r.x+r.width)) && (xEnd > r.x) && (xWidth>0))
      {
         wxRect bar( xStart,y-yBarHeight/2, 
            xWidth,yBarHeight);
         if( x1 > x+xBarShorten )
            dc.DrawRectangle(bar);
      }
   }
   // Draw frame for the text...
   // We draw it half an icon width left of the text itself.
   {
      const int xStart=max(r.x,xText-LabelTrack::mIconWidth/2);
      const int xEnd=min(r.x+r.width,xText+width+LabelTrack::mIconWidth/2);
      const int xWidth = xEnd-xStart;

      if( (xStart < (r.x+r.width)) && (xEnd > r.x) && (xWidth>0))
      {
         wxRect frame(
            xStart,y-yFrameHeight/2,
            xWidth,yFrameHeight );
         dc.DrawRectangle(frame);
         // Now draw the text itself.
         dc.DrawText(title, xText, y-LabelTrack::mTextHeight/2);
      }
   }
}

/// Draw calls other functions to draw the LabelTrack.
///   @param  dc the device context
///   @param  r  the LabelTrack rectangle.
void LabelTrack::Draw(wxDC & dc, wxRect & r, double h, double pps,
                      double sel0, double sel1)
{
   double right = h + r.width / pps;
   double dsel0 = sel0;
   if (dsel0 < h)
      dsel0 = h;
   if (dsel0 > right)
      dsel0 = right;
   double dsel1 = sel1;
   if (dsel1 < h)
      dsel1 = h;
   if (dsel1 > right)
      dsel1 = right;

   wxRect before = r;
   before.width = int ((dsel0 - h) * pps);
   dc.SetBrush(mUnselectedBrush);
   dc.SetPen(mUnselectedPen);
   dc.DrawRectangle(before);

   wxRect selr = r;
   selr.x += before.width;
   selr.width = int ((dsel1 - dsel0) * pps);
   dc.SetBrush(mSelectedBrush);
   dc.SetPen(mSelectedPen);
   dc.DrawRectangle(selr);

   wxRect after = r;
   after.x += (before.width + selr.width);
   after.width -= (before.width + selr.width);
   if (after.x < r.x) {
      after.width -= (r.x - after.x);
      after.x = r.x;
   }
   dc.SetBrush(mUnselectedBrush);
   dc.SetPen(mUnselectedPen);
   dc.DrawRectangle(after);

   int i;

#ifdef __WXMAC__
   long textWidth, textHeight;
#else
   int textWidth, textHeight;
#endif

   // Get the text widths.
   // TODO: Make more efficient by only re-computing when a
   // text label title changes.
   for (i = 0; i < (int)mLabels.Count(); i++) 
   {
         dc.GetTextExtent(mLabels[i]->title, &textWidth, &textHeight);
         mLabels[i]->width = textWidth;
   }

   // TODO: And this only needs to be done once, but we
   // do need the dc to do it.
   // We need to set mTextHeight to something sensible, 
   // guarding against the case where there are no
   // labels or all are empty strings, which for example
   // happens with a new label track.
   dc.GetTextExtent("Demo Text x^y", &textWidth, &textHeight);
   mTextHeight = (int)textHeight;   

   ComputeLayout( r, h , pps );

   dc.SetTextForeground(wxColour(0, 0, 0));
   dc.SetBackgroundMode(wxTRANSPARENT);
   dc.SetBrush(mTextNormalBrush);
   dc.SetPen(mLabelSurroundPen);

   const int nLabels = (int)mLabels.Count();
   int GlyphLeft;
   int GlyphRight;
   // Now we draw the various items in this order,
   // so that the correct things overpaint each other.
   for (i = 0; i < nLabels; i++) 
   {
      mLabels[i]->DrawLines( dc, r );
   }
   for (i = 0; i < nLabels; i++) 
   {
      GlyphLeft=0;
      GlyphRight=1;
      if( i==mMouseOverLabelLeft )
         GlyphLeft = mbHitCenter ? 6:9;
      if( i==mMouseOverLabelRight )
         GlyphRight = mbHitCenter ? 7:4;
      mLabels[i]->DrawGlyphs( dc, r, GlyphLeft, GlyphRight );
   }
   for (i = 0; i < nLabels; i++)
   {
      if( mSelIndex==i) dc.SetBrush(mTextEditBrush);
      mLabels[i]->DrawText( dc, r );
      if( mSelIndex==i) dc.SetBrush(mTextNormalBrush);
   }
}

double LabelTrack::GetStartTime()
{
   int len = mLabels.Count();
   
   if (len == 0)
      return 0.0;
   else
      return mLabels[0]->t;
}

double LabelTrack::GetEndTime()
{
   int len = mLabels.Count();

   if (len == 0)
      return 0.0;
   else
      return mLabels[len - 1]->t1;
}
 

/// OverGlyph returns 0 if not over a glyph,
/// 1 if over the left-hand glyph, and 
/// 2 if over the right-hand glyph on a label.
/// 3 if over both right and left.
///
/// It also sets up member variables:
///   mMouseLabelLeft - index of any left label hit
///   mMouseLabelRight - index of any right label hit
///   mbHitCenter     - if (x,y) 'hits the spot'.
///
/// TODO: Investigate what happens with large
/// numbers of labels, might need a binary search
/// rather than a linear one.
int LabelTrack::OverGlyph(int x, int y)
{
   //Determine the new selection.
   LabelStruct * pLabel;
   int result=0;
   const int d1=10; //distance in pixels.
   const int d2=5;  //distance in pixels.
   
   //If not over a label, reset it
   mMouseOverLabelLeft  = -1;
   mMouseOverLabelRight = -1;
   mbHitCenter = false;
   for (int i = 0; i < (int)mLabels.Count(); i++) 
   {
      pLabel = mLabels[i];
      
      //over left or right selection bound
      if(   abs(pLabel->y - y) < d1 &&
            abs(pLabel->x + d2 - x) < d1 )
      {
         mMouseOverLabelLeft = i;
         if(abs(pLabel->x - x) < d2 )
            mbHitCenter = true;
         result |= 1;
      }
      // use else-if so that we don't detect left and right 
      // of the same label.
      else if( abs(pLabel->y-y ) < d1 &&
               abs(pLabel->x1 - d2 -x) < d1)
      {
         mMouseOverLabelRight = i;
         if(abs(pLabel->x1 - x) < d2 )
            mbHitCenter = true;
         result |= 2;
      }
   }
   return result;
}

/// HandleMouse gets called with every mouse move or click.
/// 
void LabelTrack::HandleMouse(const wxMouseEvent & evt,
                             wxRect & r, double h, double pps,
                             double *newSel0, double *newSel1)
{
   if(evt.ButtonUp(1) )
   {
      mIsAdjustingLabel = false;
      mMouseOverLabelLeft  = -1;
      mMouseOverLabelRight = -1;
      return;
   }
   
   if(evt.Dragging())
   {
      
      //If we are currently adjusting a label, 
      //just reset its value and redraw.
      if(mIsAdjustingLabel )  // This guard is necessary but hides another bug.  && mSelIndex != -1)
      {
         //Adjust boundary and make sure that t < t1 on any dragged labels.
         //This code pushes both of them in one direction, instead of swapping
         //bounds like happens for the selection region.
         if(mMouseOverLabelLeft>=0)
         {
            mLabels[mMouseOverLabelLeft]->t  = h + (evt.m_x - r.x)/pps;
            if( mLabels[mMouseOverLabelLeft]->t > mLabels[mMouseOverLabelLeft]->t1)
            {
               mLabels[mMouseOverLabelLeft]->t1  = mLabels[mMouseOverLabelLeft]->t;
            }
         }
         if (mMouseOverLabelRight>=0)
         {
            mLabels[mMouseOverLabelRight]->t1 = h + (evt.m_x - r.x)/pps;
            
            if( mLabels[mMouseOverLabelRight]->t > mLabels[mMouseOverLabelRight]->t1)
            {
               mLabels[mMouseOverLabelRight]->t  = mLabels[mMouseOverLabelRight]->t1;
            }
         }

         if( mSelIndex >=0 )
         {
            //Set the selection region to be equal to
            //the new size of the label.
            *newSel0 = mLabels[mSelIndex]->t;
            *newSel1 = mLabels[mSelIndex]->t1;
         }
         SortLabels();
      }
      return;
   }
   
   if( evt.ButtonDown())
   {
      //OverGlyph sets mMouseOverLabel to be the chosen label.         
      mIsAdjustingLabel = OverGlyph(evt.m_x, evt.m_y) != 0;   
      
      if(mIsAdjustingLabel )
      {
         //The mouse was clicked on the label adjuster.
         if(mMouseOverLabelRight >=0)
         {
            mLabels[mMouseOverLabelRight]->t1 = h + (evt.m_x-r.x)/pps;
//          mSelIndex = mMouseOverLabelRight;
         }
         if(mMouseOverLabelLeft >=0)
         {
            mLabels[mMouseOverLabelLeft]->t = h + (evt.m_x-r.x)/pps;
//          mSelIndex = mMouseOverLabelLeft;
         }
         return;
      }
      
      LabelStruct * pLabel;

      //OK, they aren't dragging or clicking on an edge.
      //TODO: Move this into a function 'FindLabel' or some such.
      for (int i = 0; i < (int)mLabels.Count(); i++) {
         pLabel = mLabels[i];
         if( (pLabel->xText-(mIconWidth/2) < evt.m_x) && 
            (evt.m_x<pLabel->xText+pLabel->width+(mIconWidth/2)) &&
            (abs(pLabel->y-evt.m_y)<mIconHeight/2))
         {
            mSelIndex = i;
            *newSel0 = mLabels[i]->t;
            *newSel1 = mLabels[i]->t1;
            return;
         }
      }
   }
}


#ifdef __WXMAC__
 #if ((wxMAJOR_VERSION == 2) && (wxMINOR_VERSION <= 4))
  // HACK: Workaround wxMac <=2.4 bug
  bool gMacRepeat = false;
 #endif
#endif

/// KeyEvent is called for every keypress when over the label track.
/// TODO: Modify so that it can pass unused characters on to 
/// higher levels of the interface.
void LabelTrack::KeyEvent(double sel0, double sel1, wxKeyEvent & event)
{ 
#ifdef __WXMAC__
 #if ((wxMAJOR_VERSION == 2) && (wxMINOR_VERSION <= 4))
  // HACK: Workaround wxMac <=2.4 bug
   gMacRepeat = !gMacRepeat;
   if (gMacRepeat)
      return;
 #endif
#endif

   long keyCode = event.KeyCode();
   
   if (mSelIndex >= 0) {
      switch (keyCode) {
      case WXK_BACK:
         {
            int len = mLabels[mSelIndex]->title.Length();
            
            //If the label is not blank get rid of a letter
            if (len > 0)
            {
               mLabels[mSelIndex]->title = mLabels[mSelIndex]->title.Left(len - 1);
            }
            else
            {
               
               delete mLabels[mSelIndex];
               mLabels.RemoveAt(mSelIndex);
               mSelIndex = -1;
            }
         }
         break;
         
      case WXK_DELETE:
      case WXK_RETURN:
      case WXK_ESCAPE:
         if (mLabels[mSelIndex]->title == "") {
            delete mLabels[mSelIndex];
            mLabels.RemoveAt(mSelIndex);
         }
         
         mSelIndex = -1;
         break;
         
      case WXK_TAB:
         if (event.ShiftDown()) {
            if (mSelIndex > 0)
               mSelIndex--;
         } else {
            if (mSelIndex < (int)mLabels.Count() - 1)
               mSelIndex++;
         }
         break;
         
      default:
         if( IsGoodLabelCharacter( keyCode ))
            mLabels[mSelIndex]->title += keyCode;
         break;
      }
   } 
   else if( !IsGoodLabelFirstCharacter( keyCode ))
   {
      // Don't automatically start a label unless its one of the accepted 
      // characters.
      // We can always create the label and then type the forbidden character
      // as our first character.
      // TODO: (Possibly) pass the unused characters on to other keycode
      // handlers, 
   }
   else
   {
      // Create new label
      LabelStruct *l = new LabelStruct();
      l->t = sel0;
      l->t1 = sel1;
      l->title += wxChar(keyCode);
      
      int len = mLabels.Count();
      int pos = 0;
      
      while (pos < len && l->t > mLabels[pos]->t)
         pos++;
      
      mLabels.Insert(l, pos);
      
      mSelIndex = pos;
   }
}

void LabelTrack::Unselect()
{
   mSelIndex = -1;
}

bool LabelTrack::IsSelected() const
{
   return (mSelIndex >= 0 && mSelIndex < (int)mLabels.Count());
}

/// Export labels including label start and end-times.
void LabelTrack::Export(wxTextFile & f)
{
   for (int i = 0; i < (int)mLabels.Count(); i++) {
      f.AddLine(wxString::Format("%f\t%f\t%s",
                                 (double)mLabels[i]->t,
                                 (double)mLabels[i]->t1,
                                 (const char *) (mLabels[i]->title)));
   }
}

/// Import labels, handling files with or without end-times.
void LabelTrack::Import(wxTextFile & in)
{
   wxString currentLine;
   int i, i2,len;
   int index, lines;
   wxString s,s1;
   wxString title;
   double t,t1;
   
   lines = in.GetLineCount();
   
   mLabels.Clear();
   mLabels.Alloc(lines);
   
   //Currently, we expect a tag file to have two values and a label
   //on each line. If the second token is not a number, we treat
   //it as a single-value label.
   for (index = 0; index < lines; index++) {
      currentLine = in.GetLine(index);
      
      len = currentLine.Length();
      if (len == 0)
         return;
      
      //get the timepoint of the left edge of the label.
      i = 0;
      while (i < len && currentLine.GetChar(i) != ' '
         && currentLine.GetChar(i) != '\t')
      {
         i++;
      }
      s = currentLine.Left(i);
      
      if (!Internat::CompatibleToDouble(s, &t))
         return;
      
      //Increment one letter.
      i++;
      
      //Now, go until we find the start of the get the next token
      while (i < len
         && (currentLine.GetChar(i) == ' '
         || currentLine.GetChar(i) == '\t'))
      {
         i++;
      }
      //Keep track of the start of the second token
      i2=i;
      
      //Now, go to the end of the second token.
      while (i < len && currentLine.GetChar(i) != ' '
         && currentLine.GetChar(i) != '\t')
      {
         i++;
      }
      
      //We are at the end of the second token.      
      s1 = currentLine.Mid(i2,i-i2+1).Strip(wxString::stripType(0x3));
      if (!Internat::CompatibleToDouble(s1, &t1))
      {
         //s1 is not a number.
         t1 = t;  //This is a one-sided label; t1 == t.
         
         //Because s1 is not a number, the label should be
         //The rest of the line, starting at i2;
         title = currentLine.Right(len - i2).Strip(wxString::stripType(0x3));  //0x3 indicates both
      }
      else
      {
         //s1 is a number, and it is stored correctly in t1.
         //The title should be the remainder of the line, 
         //After we eat 
         
         //Get rid of spaces at either end 
         title = currentLine.Right(len - i).Strip(wxString::stripType(0x3)); //0x3 indicates both.
         
      }
      LabelStruct *l = new LabelStruct();
      l->t = t;
      l->t1 = t1;
      l->title = title;
      mLabels.Add(l);
   }
   SortLabels();
}

bool LabelTrack::HandleXMLTag(const char *tag, const char **attrs)
{
   if (!strcmp(tag, "label")) {

      LabelStruct *l = new LabelStruct();

      // loop through attrs, which is a null-terminated list of
      // attribute-value pairs
      bool has_t1 = false;
      while(*attrs) {
         const char *attr = *attrs++;
         const char *value = *attrs++;
         
         if (!value)
            break;
         
         if (!strcmp(attr, "t"))
            Internat::CompatibleToDouble(wxString(value), &l->t);
         else if (!strcmp(attr, "t1")) {
            has_t1 = true;
            Internat::CompatibleToDouble(wxString(value), &l->t1);
         }
         else if (!strcmp(attr, "title"))
            l->title = value;

      } // while

      // Handle files created by Audacity 1.1.   Labels in Audacity 1.1
      // did not have separate start- and end-times.
      if (!has_t1)
         l->t1 = l->t;

      mLabels.Add(l);

      return true;
   }
   else if (!strcmp(tag, "labeltrack")) {
      if (*attrs) {
         const char *attr = *attrs++;
         const char *value = *attrs++;
         
         if (!value)
            return true;

         if (!strcmp(attr, "name"))
            mName = value;
         else if (!strcmp(attr, "numlabels")) {
            int len = atoi(value);
            mLabels.Clear();
            mLabels.Alloc(len);
         }
      }

      return true;
   }

   return false;
}

XMLTagHandler *LabelTrack::HandleXMLChild(const char *tag)
{
   if (!strcmp(tag, "label"))
      return this;
   else
      return NULL;
}

void LabelTrack::WriteXML(int depth, FILE *fp)
{
   int len = mLabels.Count();
   int i, j;

   for(j=0; j<depth; j++)
      fprintf(fp, "\t");
   fprintf(fp, "<labeltrack ");
   fprintf(fp, "name=\"%s\" ", XMLEsc(mName).c_str());
   fprintf(fp, "numlabels=\"%d\">\n", len);

   for (i = 0; i < len; i++) {
      for(j=0; j<depth+1; j++)
         fprintf(fp, "\t");
      fprintf(fp, "<label t=\"%s\" t1=\"%s\" title=\"%s\"/>\n",
            Internat::ToString(mLabels[i]->t, 8).c_str(),
            Internat::ToString(mLabels[i]->t1, 8).c_str(),
            XMLEsc(mLabels[i]->title).c_str());
   }
   for(j=0; j<depth; j++)
      fprintf(fp, "\t");
   fprintf(fp, "</labeltrack>\n");
}

#if LEGACY_PROJECT_FILE_SUPPORT
bool LabelTrack::Load(wxTextFile * in, DirManager * dirManager)
{
   if (in->GetNextLine() != "NumMLabels")
      return false;

   unsigned long len;
   if (!(in->GetNextLine().ToULong(&len)))
      return false;

   unsigned int i;
   for (i = 0; i < mLabels.Count(); i++)
      delete mLabels[i];
   mLabels.Clear();
   mLabels.Alloc(len);

   for (i = 0; i < len; i++) {
      LabelStruct *l = new LabelStruct();
      if (!Internat::CompatibleToDouble(in->GetNextLine(), &l->t))
         return false;
      // Legacy file format does not include label end-times.
      l->t1 = l->t;
      l->title = in->GetNextLine();
      mLabels.Add(l);
   }

   if (in->GetNextLine() != "MLabelsEnd")
      return false;
   SortLabels();
   return true;
}

bool LabelTrack::Save(wxTextFile * out, bool overwrite)
{
   out->AddLine("NumMLabels");
   int len = mLabels.Count();
   out->AddLine(wxString::Format("%d", len));

   for (int i = 0; i < len; i++) {
      out->AddLine(wxString::Format("%lf", mLabels[i]->t));
      out->AddLine(mLabels[i]->title);
   }
   out->AddLine("MLabelsEnd");

   return true;
}
#endif

bool LabelTrack::Cut(double t0, double t1, Track ** dest)
{
   *dest = new LabelTrack(GetDirManager());
   int len = mLabels.Count();

   for (int i = 0; i < len; i++) {
      if (t0 <= mLabels[i]->t && mLabels[i]->t <= t1) {
         mLabels[i]->t -= t0;
         mLabels[i]->t1 -= t0;
         ((LabelTrack *) (*dest))->mLabels.Add(mLabels[i]);
         mLabels.RemoveAt(i);
         len--;
         i--;
      }
      else if (mLabels[i]->t > t1) {
         mLabels[i]->t -= (t1 - t0);
         mLabels[i]->t1 -= (t1 - t0);
      }
   }
   ((LabelTrack *) (*dest))->mClipLen = (t1 - t0);

   return true;
}

bool LabelTrack::Copy(double t0, double t1, Track ** dest)
{
   *dest = new LabelTrack(GetDirManager());
   int len = mLabels.Count();

   for (int i = 0; i < len; i++) {
      if (t0 <= mLabels[i]->t && mLabels[i]->t <= t1) {
         LabelStruct *l = new LabelStruct();
         l->t = mLabels[i]->t - t0;
         l->t1 = mLabels[i]->t1 - t0;
         l->title = mLabels[i]->title;
         ((LabelTrack *) (*dest))->mLabels.Add(l);
      }
   }
   ((LabelTrack *) (*dest))->mClipLen = (t1 - t0);

   return true;
}

bool LabelTrack::Paste(double t, const Track * src)
{
   if (src->GetKind() != Track::Label)
      return false;

   int len = mLabels.Count();
   int pos = 0;

   while (pos < len && mLabels[pos]->t < t)
      pos++;

   LabelTrack *sl = (LabelTrack *) src;
   for (unsigned int j = 0; j < sl->mLabels.Count(); j++) {
      LabelStruct *l = new LabelStruct();
      l->t = sl->mLabels[j]->t + t;
      l->t1 = sl->mLabels[j]->t1 + t;
      l->title = sl->mLabels[j]->title;
      mLabels.Insert(l, pos++);
      len++;
   }

   while (pos < len) {
      mLabels[pos]->t += sl->mClipLen;
      mLabels[pos]->t1 += sl->mClipLen;
      pos++;
   }

   return true;
}

bool LabelTrack::Clear(double t0, double t1)
{
   int len = mLabels.Count();

   for (int i = 0; i < len; i++) {
      if (t0 <= mLabels[i]->t && mLabels[i]->t <= t1) {
         mLabels.RemoveAt(i);
         len--;
         i--;
      }
      else if (mLabels[i]->t > t1) {
         mLabels[i]->t -= (t1 - t0);
         mLabels[i]->t1 -= (t1 - t0);
      }
   }

   return true;
}

bool LabelTrack::Silence(double t0, double t1)
{
   int len = mLabels.Count();

   for (int i = 0; i < len; i++) {
      if (t0 <= mLabels[i]->t && mLabels[i]->t <= t1) {
         mLabels.RemoveAt(i);
         len--;
         i--;
      }
   }

   return true;
}

bool LabelTrack::InsertSilence(double t, double len)
{
   int numLabels = mLabels.Count();

   for (int i = 0; i < numLabels; i++) {
      if (mLabels[i]->t >= t)
         mLabels[i]->t += len;

      if (mLabels[i]->t1 >= t)
         mLabels[i]->t1 += len;
   }

   return true;
}

int LabelTrack::GetNumLabels() const
{
   return mLabels.Count();
}

const LabelStruct *LabelTrack::GetLabel(int index) const
{
   return mLabels[index];
}

int LabelTrack::AddLabel(double t, double t1, const wxString &title)
{
   LabelStruct *l = new LabelStruct();
   l->t = t;
   l->t1 = t1;
   l->title = title;

   int len = mLabels.Count();
   int pos = 0;

   while (pos < len && mLabels[pos]->t < t)
      pos++;

   mLabels.Insert(l, pos);

   mSelIndex = pos;

   return pos;
}

// Private method called from the constructor
void LabelTrack::InitColours()
{
// JKC: Standard Audacity colours are grays and shades of blue.
// To keep interface 'unified' only use special colors
// where there is a good/established reason, e.g.
//   Red   - Record.
//   Green - Playback.
   mLabelSurroundPen.SetColour( 0, 0, 0);
   mTextEditBrush.SetColour( 255,255,255);
   mTextNormalBrush.SetColour( 190,190,240 );// #BEBEF0

   mUnselectedBrush.SetColour(192, 192, 192);
   mSelectedBrush.SetColour(148, 148, 170);

   mUnselectedPen.SetColour(192, 192, 192);
   mSelectedPen.SetColour(148, 148, 170);
}


// This one XPM spec is used to generate a number of
// different wxIcons.
/* XPM */
static char *GlyphXpmRegionSpec[] = {
/* columns rows colors chars-per-pixel */
"15 23 7 1",
/* Default colors, with first color transparent */
". c #C0C0C0",
"2 c black",
"3 c black",
"4 c black",
"5 c #BEBEF0",
"6 c #BEBEF0",
"7 c #BEBEF0",
/* pixels */
"...............",
"...............",
"...............",
"....333.444....",
"...3553.4774...",
"...3553.4774...",
"..35553.47774..",
"..35522222774..",
".3552666662774.",
".3526666666274.",
"355266666662774",
"355266666662774",
"355266666662774",
".3526666666274.",
".3552666662774.",
"..35522222774..",
"..35553.47774..",
"...3553.4774...",
"...3553.4774...",
"....333.444....",
"...............",
"...............",
"..............."
};

/// CreateCustomGlyphs() creates the mBoundaryGlyph array.
/// It's a bit like painting by numbers!
/// 
/// Schematically the glyphs we want will 'look like':
///   <O,  O>   and   <O>
/// for a left boundary to a label, a right boundary and both.
/// we're creating all three glyphs using the one Xpm Spec.
///
/// When we hover over a glyph we highlight the
/// inside of either the '<', the 'O' or the '>' or none,
/// giving 3 x 4 = 12 combinations.
///
/// Two of those combinations aren't used, but
/// treating them specially would make other code more 
/// complicated.
void LabelTrack::CreateCustomGlyphs()
{
   int iConfig;
   int iHighlight;
   int index;
   const int nSpecRows = 
      sizeof( GlyphXpmRegionSpec )/sizeof( GlyphXpmRegionSpec[0]);
   char *XmpBmp[nSpecRows];

   // The glyphs are declared static wxIcon; so we only need
   // to create them once, no matter how many LabelTracks.
   if( mbGlyphsReady )
      return;

// KLUDGE!  Color #C0C0C0 is transparent for icons in wxWindows 2.4.0
// Might not be that way in future, in which case we might need to
// explicitly create a mask for the bitmap dependent on the colors before
// creating the icon.

// We're about to tweak the basic color spec to get 12 variations.
   for( iConfig=0;iConfig<NUM_GLYPH_CONFIGS;iConfig++)
   {
      for( iHighlight=0;iHighlight<NUM_GLYPH_HIGHLIGHTS;iHighlight++)
      {
         index = iConfig + NUM_GLYPH_CONFIGS * iHighlight;
         // Copy the basic spec...
         memcpy( XmpBmp, GlyphXpmRegionSpec, sizeof( GlyphXpmRegionSpec ));
         // The higlighted region (if any) is white...
         if( iHighlight==1 ) XmpBmp[5]="5 c #FFFFFF";
         if( iHighlight==2 ) XmpBmp[6]="6 c #FFFFFF";
         if( iHighlight==3 ) XmpBmp[7]="7 c #FFFFFF";
         // For left or right arrow the other side of the glyph
         // is the transparent color.
         if( iConfig==0) { XmpBmp[3]="3 c #C0C0C0"; XmpBmp[5]="5 c #C0C0C0"; }
         if( iConfig==1) { XmpBmp[4]="4 c #C0C0C0"; XmpBmp[7]="7 c #C0C0C0"; }
         // Create the icon from the tweaked spec.
         mBoundaryGlyphs[index] = wxIcon(XmpBmp);
      }
   }

   mIconWidth  = mBoundaryGlyphs[0].GetWidth();
   mIconHeight = mBoundaryGlyphs[0].GetHeight();
   mTextHeight = mIconHeight; // until proved otherwise...
   // The icon should have an odd width so that the
   // line goes exactly down the middle.
   wxASSERT( (mIconWidth %2)==1);

   mbGlyphsReady=true;
}

/// The 'typing at selection creates label' feature
/// will only accept these keyCodes as a first label 
/// character.
bool LabelTrack::IsGoodLabelFirstCharacter(long keyCode)
{
   if(( 'a' <= keyCode ) && (keyCode <='z' ))
      return true;
   if(( 'A' <= keyCode ) && (keyCode <='Z' ))
      return true;
   if(( '0' <= keyCode ) && (keyCode <='9' ))
      return true;
   return false;
}

/// We'll only accept these characters within a label
bool LabelTrack::IsGoodLabelCharacter(long keyCode)
{
// if( IsGoodLabelFirstCharacter( keyCode ))
//    return true;
   if( keyCode >= WXK_START )
      return false;
   return true;
}

/// Sorts the labels in order of their starting times.
/// This function is called often (whilst dragging a label)
/// We expect them to be very nearly in order, so insertion 
/// sort (with a linear search) is a reasonable choice.  
void LabelTrack::SortLabels()
{
   int i,j;
   LabelStruct * pTemp;
   for (i = 1; i < (int)mLabels.Count(); i++) 
   {
      j=i-1;
      while( (j>=0) && (mLabels[j]->t > mLabels[i]->t) )
      {  
         j--;
      }
      j++;
      if( j<i)
      {
         // Remove at i and insert at j.
         pTemp = mLabels[i];
         mLabels.RemoveAt( i );
         mLabels.Insert(pTemp, j);

         // Various indecese need to be updated with the moved items...
         if( mMouseOverLabelLeft <=i )
         {
            if( mMouseOverLabelLeft == i )
               mMouseOverLabelLeft=j;
            else if( mMouseOverLabelLeft >= j)
               mMouseOverLabelLeft++;
         }
         if( mMouseOverLabelRight <=i )
         {
            if( mMouseOverLabelRight == i )
               mMouseOverLabelRight=j;
            else if( mMouseOverLabelRight >= j)
               mMouseOverLabelRight++;
         }
         if( mSelIndex <=i )
         {
            if( mSelIndex == i )
               mSelIndex=j;
            else if( mSelIndex >= j)
               mSelIndex++;
         }
      }
   }
}


// Indentation settings for Vim and Emacs and unique identifier for Arch, a
// version control system. Please do not modify past this point.
//
// Local Variables:
// c-basic-offset: 3
// indent-tabs-mode: nil
// End:
//
// vim: et sts=3 sw=3
// arch-tag: f321cf69-6f22-4a1b-a44b-b70d533227e3

