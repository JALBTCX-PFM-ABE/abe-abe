
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



//  abe class.

/***************************************************************************\

    Module :        abe

    Prorammer :     Jan C. Depner

    Date :          01/15/10

    Purpose :       Silly little toolbar with buttons for all of the ABE
                    graphical programs.

\***************************************************************************/

#include "abe.hpp"
#include "abeHelp.hpp"
#include "acknowledgments.hpp"

#include "release.hpp"

abe::abe (int *argc __attribute__ ((unused)), char **argv __attribute__ ((unused)), QWidget *parent):
  QDialog (parent, 0)
{
  void envin (OPTIONS *options, MISC *misc);
  void set_defaults (MISC *misc, OPTIONS *options);


#ifdef ET_PHONE_HOME


  //  For public domain versions we want this program to check for new versions when it starts.

  QNetworkAccessManager *manager = new QNetworkAccessManager (this);
  connect(manager, SIGNAL (finished (QNetworkReply *)), this, SLOT (slotReplyFinished (QNetworkReply *)));

  QNetworkRequest request (QUrl ("http://pfmabe.software/downloads/CURRENT_VERSION.txt"));
  request.setRawHeader ("User-Agent", "Mozilla Firefox");
  manager->get (request);

#endif


  //  Switched to one row or column (depending on orientation).

  half_progs = NUM_PROGS;// / 2;
  messageD = NULL;
  messages = new QStringList ();
  msg_x = 0;
  msg_y = 0;
  msg_w = 600;
  msg_h = 400;


  QResource::registerResource ("/icons.rcc");


  //  Have to set the focus policy or keypress events don't work properly at first in Focus Follows Mouse mode

  setFocusPolicy (Qt::WheelFocus);


  setSizePolicy (QSizePolicy::Maximum, QSizePolicy::Maximum);


  //  Set the main title and icon

  setWindowIcon (QIcon (":/icons/abe.png"));
  setWindowTitle (VERSION);


  //  Set all of the defaults

  set_defaults (&misc, &options);


  //  Get the user's defaults if available

  envin (&options, &misc);


  // Set the application font

  QApplication::setFont (options.font);


  QSize mainButtonIconSize (options.main_button_icon_size, options.main_button_icon_size);


  vbox = new QVBoxLayout (this);
  vbox->setMargin (5);
  vbox->setSpacing (5);
  vbox->setSizeConstraint (QLayout::SetNoConstraint);


  QMenuBar *menuBar = new QMenuBar (this);


  QAction *verticalAction = new QAction (tr ("Vertical"), this);
  verticalAction->setShortcut (tr ("Ctrl+V", "Vertical orientation shortcut key"));
  connect (verticalAction, SIGNAL (triggered ()), this, SLOT (slotVertical ()));

  QAction *horizontalAction = new QAction (tr ("Horizontal"), this);
  horizontalAction->setShortcut (tr ("Ctrl+H", "Horizontal orientation shortcut key"));
  connect (horizontalAction, SIGNAL (triggered ()), this, SLOT (slotHorizontal ()));

  QAction *messageAction = new QAction (tr ("Messages"), this);
  messageAction->setShortcut (tr ("Ctrl+M", "Messages shortcut key"));
  messageAction->setToolTip (tr ("Messages from running programs"));
  messageAction->setWhatsThis (tr ("This menu entry will display a dialog containing any messages (error or information) from running programs."));
  connect (messageAction, SIGNAL (triggered ()), this, SLOT (slotMessage ()));

  QAction *quitAction = new QAction (tr ("&Quit"), this);
  quitAction->setShortcut (tr ("Ctrl+Q", "Quit shortcut key"));
  quitAction->setStatusTip (tr ("Exit from application"));
  connect (quitAction, SIGNAL (triggered ()), this, SLOT (slotQuit ()));

  QMenu *orientationMenu = menuBar->addMenu (tr ("&View"));
  orientationMenu->addAction (verticalAction);
  orientationMenu->addAction (horizontalAction);
  orientationMenu->addSeparator ();
  orientationMenu->addAction (messageAction);
  orientationMenu->addSeparator ();
  orientationMenu->addAction (quitAction);


  //  Setup the help menu.

  QAction *whatsThisAct = QWhatsThis::createAction (this);
  whatsThisAct->setIcon (QIcon (":/icons/contextHelp.png"));

  QAction *aboutAct = new QAction (tr ("&About"), this);
  aboutAct->setShortcut (tr ("Ctrl+A", "About shortcut key"));
  aboutAct->setStatusTip (tr ("Information about abe"));
  connect (aboutAct, SIGNAL (triggered ()), this, SLOT (about ()));

  QAction *acknowledgments = new QAction (tr ("A&cknowledgments"), this);
  acknowledgments->setShortcut (tr ("Ctrl+c", "Acknowledgments shortcut key"));
  acknowledgments->setStatusTip (tr ("Information about supporting libraries and contributors"));
  connect (acknowledgments, SIGNAL (triggered ()), this, SLOT (slotAcknowledgments ()));

  QAction *aboutQtAct = new QAction (tr ("A&bout Qt"), this);
  aboutQtAct->setShortcut (tr ("Ctrl+b", "About Qt shortcut key"));
  aboutQtAct->setStatusTip (tr ("Information about Qt"));
  connect (aboutQtAct, SIGNAL (triggered ()), this, SLOT (aboutQt ()));

  QMenu *helpMenu = menuBar->addMenu (tr ("&Help"));
  helpMenu->addAction (whatsThisAct);
  helpMenu->addSeparator ();
  helpMenu->addAction (aboutAct);
  helpMenu->addSeparator ();
  helpMenu->addAction (acknowledgments);
  helpMenu->addAction (aboutQtAct);


  vbox->addWidget (menuBar);


  grid = new QGridLayout ();
  grid->setSizeConstraint (QLayout::SetNoConstraint);


  QButtonGroup *toolGrp = new QButtonGroup (this);
  connect (toolGrp, SIGNAL (buttonClicked (int)), this, SLOT (slotToolGrp (int)));
  toolGrp->setExclusive (false);

  for (int32_t i = 0 ; i < NUM_PROGS ; i++)
    {
      toolButton[i] = new dndButton (this, i);
      toolButton[i]->setIcon (misc.buttonIcon[i]);
      toolButton[i]->setIconSize (mainButtonIconSize);
#ifdef NVWIN3X
      QString prog = misc.progName[i];
      QString tip = prog.remove (".exe") + " - (" + options.buttonAccel[i] + ")";
#else
      QString tip = misc.progName[i] + " - (" + options.buttonAccel[i] + ")";
#endif
      toolButton[i]->setToolTip (tip);
      toolButton[i]->setWhatsThis (misc.buttonWhat[i]);
      connect (toolButton[i], SIGNAL (dropSignal (char *, int32_t)), this, SLOT (slotDrop (char *, int32_t)));
      toolGrp->addButton (toolButton[i], i);

      int32_t row;
      int32_t col;

      if (options.orientation == Qt::Vertical)
        {
          row = i % half_progs;
          col = i / half_progs;
        }
      else
        {
          row = i / half_progs;
          col = i % half_progs;
        }
      grid->setColumnStretch (col, 0);
      grid->setRowStretch (row, 0);

      grid->addWidget (toolButton[i], row, col);


      char pn[128];
      strcpy (pn, misc.progName[i].toLatin1 ());

      if (find_startup_name (pn) == NULL) toolButton[i]->setEnabled (false);
    }


  vbox->addLayout (grid);


  //  Set the location from defaults.

  this->move (options.window_x, options.window_y);


  show ();
}



abe::~abe ()
{
}



//  Somebody pressed the little X in the window decoration.

void 
abe::closeEvent (QCloseEvent *event __attribute__ ((unused)))
{
  slotQuit ();
}



void 
abe::slotQuit ()
{
  void envout (OPTIONS *options, MISC *misc);

  envout (&options, &misc);

  exit (0);
}



void
abe::keyPressEvent (QKeyEvent *event)
{
  QString qkey = event->text ();


  for (int32_t i = 0 ; i < NUM_PROGS ; i++)
    {
      if (qkey == options.buttonAccel[i])
        {
          program = new QProcess (this);
          connect (program, SIGNAL (readyReadStandardError ()), this, SLOT (slotReadyReadStandardError ()));

          program->start (misc.progName[i]);

          break;
        }
    }
}



void
abe::slotToolGrp (int id)
{
  for (int32_t i = 0 ; i < NUM_PROGS ; i++)
    {
      if (i == id)
        {
          program = new QProcess (this);
          connect (program, SIGNAL (readyReadStandardError ()), this, SLOT (slotReadyReadStandardError ()));

          program->start (misc.progName[i]);

          break;
        }
    }
}



void
abe::slotDrop (char *text, int32_t id)
{
  for (int32_t i = 0 ; i < NUM_PROGS ; i++)
    {
      if (i == id)
        {
          if (misc.buttonFile[i])
            {
              program = new QProcess (this);
              connect (program, SIGNAL (readyReadStandardError ()), this, SLOT (slotReadyReadStandardError ()));

              QStringList arguments;
              QString arg;

              arg = QString (text);
              arguments += arg;

              program->start (misc.progName[i], arguments);
            }
          else
            {
              program = new QProcess (this);
              connect (program, SIGNAL (readyReadStandardError ()), this, SLOT (slotReadyReadStandardError ()));

              program->start (misc.progName[i]);
            }

          break;
        }
    }
}



void 
abe::slotVertical ()
{
  options.orientation = Qt::Vertical;


  //  We have to delete and recreate the grid layout so it will recalculate the number of rows and columns.

  for (int32_t i = 0 ; i < NUM_PROGS ; i++) grid->removeWidget (toolButton[i]);


  vbox->removeItem (grid);
  delete (grid);

  grid = new QGridLayout ();
  grid->setSizeConstraint (QLayout::SetNoConstraint);

  for (int32_t i = 0 ; i < NUM_PROGS ; i++)
    {
      int32_t row = i % half_progs;
      int32_t col = i / half_progs;

      grid->setColumnStretch (col, 0);
      grid->setRowStretch (row, 0);

      grid->addWidget (toolButton[i], row, col);


      char pn[128];
      strcpy (pn, misc.progName[i].toLatin1 ());

      if (find_startup_name (pn) == NULL) toolButton[i]->setEnabled (false);
    }

  vbox->addLayout (grid);


  resize (1, 1);
  adjustSize ();
}



void 
abe::slotHorizontal ()
{
  options.orientation = Qt::Horizontal;


  //  We have to delete and recreate the grid layout so it will recalculate the number of rows and columns.

  for (int32_t i = 0 ; i < NUM_PROGS ; i++) grid->removeWidget (toolButton[i]);


  vbox->removeItem (grid);
  delete (grid);

  grid = new QGridLayout ();
  grid->setSizeConstraint (QLayout::SetNoConstraint);

  for (int32_t i = 0 ; i < NUM_PROGS ; i++)
    {
      int32_t row = i / half_progs;
      int32_t col = i % half_progs;

      grid->setColumnStretch (col, 0);
      grid->setRowStretch (row, 0);

      grid->addWidget (toolButton[i], row, col);


      char pn[128];
      strcpy (pn, misc.progName[i].toLatin1 ());

      if (find_startup_name (pn) == NULL) toolButton[i]->setEnabled (false);
    }

  vbox->addLayout (grid);

  resize (1, 1);
  adjustSize ();
}



void 
abe::slotMessage ()
{
  if (!messageD)
    {
      messageD = new QDialog (this, (Qt::WindowFlags) Qt::WA_DeleteOnClose);
      messageD->setWhatsThis (tr ("Error and warning messages from programs are displayed here."));
      messageD->setWindowTitle (tr ("abe Error Messages"));

      QVBoxLayout *vbox = new QVBoxLayout (messageD);
      vbox->setMargin (5);
      vbox->setSpacing (5);

      displayBox = new QListWidget (this);

      vbox->addWidget (displayBox);


      QHBoxLayout *actions = new QHBoxLayout (0);
      vbox->addLayout (actions);

      QPushButton *bClear = new QPushButton (tr ("Clear"), this);
      bClear->setToolTip (tr ("Clear all messages"));
      connect (bClear, SIGNAL (clicked ()), this, SLOT (slotClearMessage ()));
      actions->addWidget (bClear);

      QPushButton *bSaveMessage = new QPushButton (tr ("Save"), this);
      bSaveMessage->setToolTip (tr ("Save messages to text file"));
      connect (bSaveMessage, SIGNAL (clicked ()), this, SLOT (slotSaveMessage ()));
      actions->addWidget (bSaveMessage);

      actions->addStretch (10);

      QPushButton *closeButton = new QPushButton (tr ("Close"), messageD);
      closeButton->setToolTip (tr ("Close the message dialog"));
      connect (closeButton, SIGNAL (clicked ()), this, SLOT (slotCloseMessage ()));
      actions->addWidget (closeButton);


      //  Put the dialog in the middle of the screen.

      messageD->move (x () + width () / 2 - messageD->width () / 2, y () + height () / 2 - messageD->height () / 2);


      messageD->resize (msg_w, msg_h);
      messageD->move (msg_x, msg_y);


      messageD->show ();
    }

  if (messages->size ())
    {
      for (int32_t i = 0 ; i < messages->size () ; i++)
        {
          cur = new QListWidgetItem (messages->at (i));

          displayBox->addItem (cur);
          displayBox->setCurrentItem (cur);
          displayBox->scrollToItem (cur);
        }
    }
}



void
abe::slotCloseMessage ()
{
  //  Use frame geometry to get the absolute x and y.

  QRect tmp = messageD->frameGeometry ();
  msg_x = tmp.x ();
  msg_y = tmp.y ();


  //  Use geometry to get the width and height.

  tmp = messageD->geometry ();
  msg_w = tmp.width ();
  msg_h = tmp.height ();


  messageD->close ();
  messageD = NULL;
}



void 
abe::slotReadyReadStandardError ()
{
  static QString resp_string = "";


  QByteArray response = program->readAllStandardError ();


  //  Parse the return response for line feeds

  for (int32_t i = 0 ; i < response.length () ; i++)
    {
      if (response.at (i) == '\n')
        {
          //  Let's not print out the "QProcess: Destroyed while process is still running" messages that come from
          //  killing ancillary programs in the editor.  Also, ignore the pfm io cache setting message from pfmLoad.

          if (!resp_string.contains ("Destroyed while") && !resp_string.contains ("Setting MAXIMUM Cache Size") &&
              !resp_string.contains ("failed to add paths") && !resp_string.contains ("DrvShareLists") &&
              !resp_string.contains ("OpenGL Warning"))
            {
              if (!messageD) slotMessage ();

              messages->append (resp_string);

              cur = new QListWidgetItem (resp_string);

              displayBox->addItem (cur);
              displayBox->setCurrentItem (cur);
              displayBox->scrollToItem (cur);
            }

          resp_string = "";
        }
      else
        {
          resp_string += response.at (i);
        }
    }
}



void
abe::slotClearMessage ()
{
  displayBox->clear ();
  messages->clear ();
}



void
abe::slotSaveMessage ()
{
  FILE *fp = NULL;
  QStringList files, filters;
  QString file;

  QFileDialog *fd = new QFileDialog (this, tr ("abe Save error messages"));
  fd->setViewMode (QFileDialog::List);


  //  Always add the current working directory and the last used directory to the sidebar URLs in case we're running from the command line.
  //  This function is in the nvutility library.

  setSidebarUrls (fd, QString ("."));

  filters << tr ("Text (*.txt)");

  fd->setNameFilters (filters);
  fd->setFileMode (QFileDialog::AnyFile);
  fd->selectNameFilter (tr ("Text (*.txt)"));

  if (fd->exec () == QDialog::Accepted)
    {
      files = fd->selectedFiles ();

      file = files.at (0);


      if (!file.isEmpty())
        {
          //  Add .txt to filename if not there.

          if (!file.endsWith (".txt")) file.append (".txt");
 
          char fname[1024];
          strcpy (fname, file.toLatin1 ());


          if ((fp = fopen (fname, "w")) != NULL)
            {
              for (int32_t i = 0 ; i < messages->size () ; i++)
                {
                  char string[2048];
                  strcpy (string, messages->at (i).toLatin1 ());

                  fprintf (fp, "%s\n", string);
                }

              fclose (fp);
            }

          slotClearMessage ();
          slotCloseMessage ();
        }
    }
}



#ifdef ET_PHONE_HOME

void 
abe::slotReplyFinished (QNetworkReply *reply)
{
  QString ver = "", changes = "", install = "", license = "", win_install = "", mingw_install = "", source = "", foss = "", resp_string = "";
  uint8_t new_version = NVFalse;


  QString current = QString (PFM_ABE_RELEASE);

  int32_t cur_major = current.section ('.', 0, 0).toInt ();
  int32_t cur_minor = current.section ('.', 1, 1).toInt ();
  int32_t cur_rel = current.section ('.', 2, 2).toInt ();
  int32_t cur_sub = current.section ('.', 3, 3).toInt ();
  int32_t cur_big_num = cur_sub + cur_rel * 1000 + cur_minor * 10000 + cur_major * 100000;


  QUrl url = reply->url ();

  if (reply->error ())
    {
      //  Just silently go away if the request failed.
      //  fprintf (stderr, "Download of %s failed: %s\n", url.toEncoded ().constData (), qPrintable (reply->errorString ()));
    }
  else
    {
      QByteArray vrsn = reply->readAll ();

      for (int32_t i = 0 ; i < vrsn.size () ; i++)
        {
          if (vrsn.at (i) == '\n')
            {
              if (resp_string.contains ("[VERSION]"))
                {
                  ver = resp_string.remove ("[VERSION]");
                  int32_t new_major = ver.section ('.', 0, 0).toInt ();
                  int32_t new_minor = ver.section ('.', 1, 1).toInt ();
                  int32_t new_rel = ver.section ('.', 2, 2).toInt ();
                  int32_t new_sub = ver.section ('.', 3, 3).toInt ();
                  int32_t new_big_num = new_sub + new_rel * 1000 + new_minor * 10000 + new_major * 100000;

                  if (cur_big_num >= new_big_num) break;

                  new_version = NVTrue;
                }
              else if (resp_string.contains ("[CHANGES]"))
                {
                  changes = resp_string.remove ("[CHANGES]");
                }
              else if (resp_string.contains ("[INSTALL]"))
                {
                  install = resp_string.remove ("[INSTALL]");
                }
              else if (resp_string.contains ("[LICENSE]"))
                {
                  license = resp_string.remove ("[LICENSE]");
                }
              else if (resp_string.contains ("[MINGW_INSTALL]"))
                {
                  mingw_install = resp_string.remove ("[MINGW_INSTALL]");
                }
              else if (resp_string.contains ("[WIN_INSTALL]"))
                {
                  win_install = resp_string.remove ("[WIN_INSTALL]");
                }
              else if (resp_string.contains ("[SOURCE]"))
                {
                  source = resp_string.remove ("[SOURCE]");
                }
              else if (resp_string.contains ("[FOSS]"))
                {
                  foss = resp_string.remove ("[FOSS]");
                }

              resp_string = "";
            }
          else
            {
              resp_string += vrsn.at (i);
            }
        }

      if (new_version)
        {
          QString msg = tr ("<center><br><h3>There is a new version of PFMABE available</h3><br></center>" 
                            "Your current version is %1<br>The new version is %2<br><br>"
                            "The new version is %2<br><br>"
                            "You may download updated files using the links below. "
                            "If a file is not listed below it has not been modified since the last release and does not need to be updated.<br><br><ul>"
                            "<li><a href=%3>List of Changes</a></li>").arg (current).arg (ver).arg (changes);

          if (!install.isEmpty ()) msg += tr ("<li><a href=%1>INSTALL file</a></li>").arg (install);
          if (!license.isEmpty ()) msg += tr ("<li><a href=%1>LICENSE file</a></li>").arg (license);

#ifdef NVWIN3X
          if (!mingw_install.isEmpty ())
            {
              msg += tr ("<li><a href=%1>MinGW Installer</a></li>").arg (mingw_install);
              msg += tr ("<li><a href=%1.md5sum>MinGW Installer md5sum</a></li>").arg (mingw_install);
            }
          if (!win_install.isEmpty ())
            {
              msg += tr ("<li><a href=%1>PFMABE Windows Installer</a></li>").arg (win_install);
              msg += tr ("<li><a href=%1.md5sum>PFMABE Windows Installer md5sum</a></li>").arg (win_install);
            }
#endif
          if (!source.isEmpty ())
            {
              msg += tr ("<li><a href=%1>PFMABE Source Code</a></li>").arg (source);
              msg += tr ("<li><a href=%1.md5sum>PFMABE Source Code md5sum</a></li>").arg (source);
            }
          if (!foss.isEmpty ())
            {
              msg += tr ("<li><a href=%1>FOSS Libraries</a></li>").arg (foss);
              msg += tr ("<li><a href=%1.md5sum>FOSS Libraries md5sum</a></li>").arg (foss);
            }
          msg += "</ul><br><br>";

          QMessageBox::information (this, "abe", msg);
        }
    }

  reply->deleteLater ();
}

#endif


void
abe::about ()
{
  QMessageBox::about (this, VERSION, abeAboutText);
}



void
abe::slotAcknowledgments ()
{
  QMessageBox::about (this, VERSION, acknowledgmentsText);
}



void
abe::aboutQt ()
{
  QMessageBox::aboutQt (this, VERSION);
}
