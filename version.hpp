
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



/*  PFM_ABE standalone toolbar.  */


#ifndef VERSION

#define     VERSION     "PFM Software - abe V1.29 - 09/23/17"

#endif

/*!< <pre>

    Version 1.00
    Jan C. Depner
    01/15/10

    First working version.


    Version 1.01
    Jan C. Depner
    01/28/10

    Swapped bathyQuery and areaCheck because it seemed to make more sense that way.


    Version 1.02
    Jan C. Depner
    01/03/11

    Make sure that unavailable programs are insensitive when you switch the orientation of the box.


    Version 1.03
    Jan C. Depner
    01/06/11

    Correct problem with the way I was instantiating the main widget.  This caused an intermittent error on Windows7/XP.


    Version 1.10
    Jan C. Depner
    09/26/11

    Removed CUBE, CHRTR, and PFM gridding programs and added charts2LAS.  Now this only supports actual ABE programs.


    Version 1.11
    Jan C. Depner
    10/20/11

    Removed chartsLAS program and added trackLine.


    Version 1.12
    Jan C. Depner
    11/30/11

    Converted .xpm icons to .png icons.


    Version 1.13
    Jan C. Depner
    01/30/12

    Added Quit entry to View menu (shortcut Ctrl-q).


    Version 1.14
    Jan C. Depner (PFM Software)
    12/09/13

    Switched to using .ini file in $HOME (Linux) or $USERPROFILE (Windows) in the ABE.config directory.  Now
    the applications qsettings will not end up in unknown places like ~/.config/navo.navy.mil/blah_blah_blah on
    Linux or, in the registry (shudder) on Windows.


    Version 1.15
    Jan C. Depner (PFM Software)
    03/17/14

    Removed WLF from help contents.


    Version 1.16
    Jan C. Depner (PFM Software)
    03/19/14

    - Straightened up the Open Source acknowledgments.


    Version 1.17
    Jan C. Depner (PFM Software)
    05/27/14

    - Added the new LGPL licensed GSF library to the acknowledgments.


    Version 1.18
    Jan C. Depner (PFM Software)
    07/01/14

    - Replaced all of the old, borrowed icons with new, public domain icons.  Mostly from the Tango set
      but a few from flavour-extended and 32pxmania.


    Version 1.19
    Jan C. Depner (PFM Software)
    07/23/14

    - Switched from using the old NV_INT64 and NV_U_INT32 type definitions to the C99 standard stdint.h and
      inttypes.h sized data types (e.g. int64_t and uint32_t).


    Version 1.20
    Jan C. Depner (PFM Software)
    02/11/15

    - Added QDialog for error messages.


    Version 1.21
    Jan C. Depner (PFM Software)
    02/15/15

    - Removed examGSF (it can be run from inside pfmEdit3D), pfmChartsImage (OBE), charts2LAS, and
      bagGeotiff.
    - Switched to just one row or column (depending on orientation).


    Version 1.22
    Jan C. Depner (PFM Software)
    02/17/15

    - Removed bagViewer and pfmBag.  These are mostly NAVO things and they have their own toolbar.


    Version 1.23
    Jan C. Depner (PFM Software)
    02/22/15

    - Added "Save" button for the error messages dialog.


    Version 1.24
    Jan C. Depner (PFM Software)
    03/30/15

    - Modified to reflect name change of geoSwath3D to fileEdit3D.


    Version 1.25
    Jan C. Depner (PFM Software)
    04/04/15

    - Added a PFMABE release check for public domain versions.  It will attempt to check the latest version
      on http://pfmabe.software.


    Version 1.26
    Jan C. Depner (PFM Software)
    05/11/16

    - Moved include of release.hpp from abe.hpp to abe.cpp so that the program doesn't get rebuilt completely every
      time we build it.


    Version 1.27
    Jan C. Depner (PFM Software)
    07/06/16

    - Turned off the ET_PHONE_HOME stuff in the mk.linux and mk.mingw files.  I left the code in case I need to do
      something similar in the future.


    Version 1.28
    Jan C. Depner (PFM Software)
    08/26/16

    - Now uses the same font as all other ABE GUI apps.  Font can only be changed in pfmView Preferences.


    Version 1.29
    Jan C. Depner (PFM Software)
    09/23/17

    - A bunch of changes to support doing translations in the future.  There is a generic abe_xx.ts file that
      can be run through Qt's "linguist" to translate to another language.

*/
