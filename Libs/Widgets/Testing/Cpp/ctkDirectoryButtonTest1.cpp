/*=========================================================================

  Library:   CTK
 
  Copyright (c) 2010  Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.commontk.org/LICENSE

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 
=========================================================================*/

// Qt includes
#include <QApplication>
#include <QTimer>

// CTK includes
#include "ctkDirectoryButton.h"

// STD includes
#include <cstdlib>
#include <iostream>

//-----------------------------------------------------------------------------
int ctkDirectoryButtonTest1(int argc, char * argv [] )
{
  QApplication app(argc, argv);

  ctkDirectoryButton ctkObject;
#if QT_VERSION >= 0x040700
  ctkObject.setOptions(QFileDialog::ShowDirsOnly | QFileDialog::ReadOnly);
#else
  ctkObject.setOptions(ctkDirectoryButton::ShowDirsOnly |
                       ctkDirectoryButton::ReadOnly);
#endif
  ctkObject.show();

  QTimer autoExit;
  if (argc < 2 || QString(argv[1]) != "-I")
    {
    QObject::connect(&autoExit, SIGNAL(timeout()), &app, SLOT(quit()));
    autoExit.start(100);
    }
  return app.exec();
}

