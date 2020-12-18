
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



/*****************************************************************************\

    This program is public domain software that was developed by 
    the U.S. Naval Oceanographic Office.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

\*****************************************************************************/


QString abeText = 
  abe::tr ("The abe program is just a simple PFM Area-Based Editor program launcher.  Just press a button to start a program.  "
           "Help is available on each of the program buttons by selecting the <b>What's This</b> button in the Help menu "
           "and then clicking on the program of interest.");

QString abeAboutText = 
  abe::tr ("<center><br><h1><b>abe</b></h1><br><br>"
           "Author : Jan C. Depner (area.based.editor@gmail.com)<br>"
           VERSION"</center><br>"
           "The <b>abe</b> program is a simple PFM Area-Based Editor (ABE) program toolbar.  Just press a button to start one of "
           "the PFM ABE programs.  You can also drag and drop files on the buttons.  For example, you can drag and drop a "
           ".pfm file on the <b>pfmView</b> button to start the <b>pfmView</b> program using that .pfm file.<br><br>"
           "The following is an example of how you might use <b>abe</b>:"
           "<ol>"
           "<li><img source=\":/icons/fileEdit3D_small.png\"> Run <b>fileEdit3D</b> to check one or more of your data files "
           "(Generic Sensor Format, CHARTS HOF/TOF, CZMIL CPF, or LAS) to make sure they are OK.  You can also use "
           "it to get an estimate of needed bin size for building a PFM.</li>"
           "<li><img source=\":/icons/trackLine_small.png\"> Run <b>trackLine</b> using one or more of "
           "your data files to create a track (.trk) file.</li>"
           "<li><img source=\":/icons/areaCheck_small.png\"> Run <b>areaCheck</b> to open the track file and create  a "
           "generic rectangular or polygonal area file (.are).</li>"
           "<li><img source=\":/icons/pfmLoad_small.png\"> Run <b>pfmLoad</b> to use the area file and data files to create a PFM "
           "(.pfm, .pfm.data) structure.</li>"
           "<li><img source=\":/icons/pfmView_small.png\"> Run <b>pfmView</b> to open the .pfm file and edit the data.  The <b>pfmView</b> "
           "program will launch the editor (pfmEdit3D) which can then launch monitor type programs (lidarMonitor, CZMILwaveMonitor, LASwaveMonitor, "
           "etc).  After editing the data, the edits can be unloaded back to the data files from within <b>pfmView</b> (look for the unload "
           "button in the <b>pfmView</b> toolbar, <b>Unload edits for displayed area</b> is the recommended approach).</li>"
           "<li><img source=\":/icons/pfmFeature_small.png\"> Run pfmFeature to select IHO features and create a Binary Feature "
           "Data (BFD) file that can be edited from within <b>pfmView</b>.</li>"
           "<li><img source=\":/icons/pfmExtract_small.png\"> Run <b>pfmExtract</b> to extract surface and/or point data "
           "in ASCII, LLZ, RDP, or SHAPE format.</li>"
           "<li><img source=\":/icons/pfmGeotiff_small.png\"> Run <b>pfmGeotiff</b> to export a GeoTIFF of one or more of "
           "the PFM surfaces.</li>"
           "</ol><br><br>"
           "Help is available on each of the program buttons by selecting the <b>What's This</b> button in the Help menu "
           "and then clicking on the program of interest.");
