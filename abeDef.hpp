
/*********************************************************************************************

    This is public domain software that was developed by or for the U.S. Naval Oceanographic
    Office and/or the U.S. Army Corps of Engineers.

    This is a work of the U.S. Government. In accordance with 17 USC 105, copyright protection
    is not available for any work of the U.S. Government.

    Neither the United States Government, nor any employees of the United States Government,
    nor the author, makes any warranty, express or implied, without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, or assumes any liability or
    responsibility for the accuracy, completeness, or usefulness of any information,
    apparatus, product, or process disclosed, or represents that its use would not infringe
    privately-owned rights. Reference herein to any specific commercial products, process,
    or service by trade name, trademark, manufacturer, or otherwise, does not necessarily
    constitute or imply its endorsement, recommendation, or favoring by the United States
    Government. The views and opinions of authors expressed herein do not necessarily state
    or reflect those of the United States Government, and shall not be used for advertising
    or product endorsement purposes.
*********************************************************************************************/


/****************************************  IMPORTANT NOTE  **********************************

    Comments in this file that start with / * ! or / / ! are being used by Doxygen to
    document the software.  Dashes in these comment blocks are used to create bullet lists.
    The lack of blank lines after a block of dash preceeded comments means that the next
    block of dash preceeded comments is a new, indented bullet list.  I've tried to keep the
    Doxygen formatting to a minimum but there are some other items (like <br> and <pre>)
    that need to be left alone.  If you see a comment that starts with / * ! or / / ! and
    there is something that looks a bit weird it is probably due to some arcane Doxygen
    syntax.  Be very careful modifying blocks of Doxygen comments.

*****************************************  IMPORTANT NOTE  **********************************/



#ifndef _ABE_TOOLBAR_DEF_H_
#define _ABE_TOOLBAR_DEF_H_


#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#include "nvutility.h"
#include "nvutility.hpp"


#include <QtCore>
#include <QtGui>

#ifdef ET_PHONE_HOME
#include <QtNetwork>
#endif

#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif


using namespace std;  // Windoze bullshit - God forbid they should follow a standard


#define         FILEEDIT3D                  0
#define         TRACKLINE                   1
#define         AREACHECK                   2
#define         PFMLOAD                     3
#define         PFMVIEW                     4
#define         PFMFEATURE                  5
#define         PFMEXTRACT                  6
#define         PFMGEOTIFF                  7

#define         NUM_PROGS                   8      //  Number of program toolbuttons defined


//  The OPTIONS structure contains all those variables that can be saved to the users abe QSettings.


typedef struct
{
  QString     buttonAccel[NUM_PROGS];     //  Accelerator key sequences for the buttons
  int32_t     main_button_icon_size;      //  Main button icon size (16, 24, 32)
  int32_t     orientation;                //  Qt::Horizontal or Qt::Vertical
  int32_t     window_x;                   //  Main window x position
  int32_t     window_y;                   //  Main window y position
  QFont       font;                       //  Font used for all ABE GUI applications
} OPTIONS;


//  General stuff.

typedef struct
{
  QString     buttonWhat[NUM_PROGS];      //  WhatsThis text for the buttons
  QIcon       buttonIcon[NUM_PROGS];      //  Button icons
  uint8_t     buttonFile[NUM_PROGS];      //  NVTrue if program can accept command line file name
  QString     progName[NUM_PROGS];        //  Actual program names
  QString     qsettings_app;              //  Application name for QSettings
} MISC;


#endif
