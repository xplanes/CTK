/*=============================================================================

  Library: CTK

  Copyright (c) 2010 German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/

// Qt includes
#include <QCoreApplication>
#include <QDebug>

// CTK includes
#include <ctkPluginManager.h>

int main(int argc, char** argv)
{
  QCoreApplication app(argc, argv);

  ctkPluginManager pluginManager;
  pluginManager.addSearchPath("/home/sascha/git/CTK-bin/CTK-build/bin/Plugins");
  pluginManager.startAllPlugins();

  qDebug() << "List of services: " <<  pluginManager.serviceManager()->findServices();

  QObject* service = pluginManager.serviceManager()->loadInterface("org.commontk.cli.ICLIManager");

  return 0;
}
