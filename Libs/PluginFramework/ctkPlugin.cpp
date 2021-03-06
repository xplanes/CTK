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

#include "ctkPlugin.h"

#include "ctkPluginPrivate_p.h"
#include "ctkPluginArchive_p.h"
#include "ctkPluginFrameworkContext_p.h"

#include <QStringList>


  ctkPlugin::ctkPlugin(ctkPluginFrameworkContext* fw,
                 ctkPluginArchive* pa)
    : d_ptr(new ctkPluginPrivate(*this, fw, pa))
  {

  }

  ctkPlugin::ctkPlugin(ctkPluginPrivate& dd)
    : d_ptr(&dd)
  {

  }

  ctkPlugin::~ctkPlugin()
  {
    delete d_ptr;
  }

  ctkPlugin::State ctkPlugin::getState() const
  {
    Q_D(const ctkPlugin);
    return d->state;
  }

  void ctkPlugin::start(const StartOptions& options)
  {
    Q_D(ctkPlugin);

    if (d->state == UNINSTALLED)
    {
      throw std::logic_error("ctkPlugin is uninstalled");
    }

    // Initialize the activation; checks initialization of lazy
    // activation.

    //TODO 1: If activating or deactivating, wait a litle
    // we don't use mutliple threads to start plugins for now
    //waitOnActivation(lock, "ctkPlugin::start", false);

    //2: start() is idempotent, i.e., nothing to do when already started
    if (d->state == ACTIVE)
    {
      return;
    }

    //3: Record non-transient start requests.
    if ((options & START_TRANSIENT) == 0)
    {
      d->setAutostartSetting(options);
    }

    //4: Resolve plugin (if needed)
    d->getUpdatedState();

    //5: Register Qt Mobility service xml files
    //only register if we are not already in the STARTING state
    if (d->state != STARTING)
    {
      QByteArray serviceDescriptor = getResource("servicedescriptor.xml");
      if (!serviceDescriptor.isEmpty())
      {
        d->fwCtx->services.registerService(d, serviceDescriptor);
      }
    }

    //6: Eager?
    if ((options & START_ACTIVATION_POLICY) && !d->eagerActivation )
    {
      if (STARTING == d->state) return;
      d->state = STARTING;
      d->pluginContext = new ctkPluginContext(this->d_func());
      ctkPluginEvent pluginEvent(ctkPluginEvent::LAZY_ACTIVATION, this);
      d->fwCtx->listeners.emitPluginChanged(pluginEvent);
    }
    else
    {
      d->finalizeActivation();
    }
  }

  void ctkPlugin::stop(const StopOptions& options)
  {
    Q_UNUSED(options)
  }

  ctkPluginContext* ctkPlugin::getPluginContext() const
  {
    //TODO security checks
    Q_D(const ctkPlugin);
    return d->pluginContext;
  }

  long ctkPlugin::getPluginId() const
  {
    Q_D(const ctkPlugin);
    return d->id;
  }

  QString ctkPlugin::getLocation() const
  {
    //TODO security
    Q_D(const ctkPlugin);
    return d->location;
  }

  QHash<QString, QString> ctkPlugin::getHeaders()
  {
    //TODO security
    Q_D(ctkPlugin);
    if (d->cachedRawHeaders.empty())
    {
      d->cachedRawHeaders = d->archive->getUnlocalizedAttributes();
    }

    if (d->state == UNINSTALLED)
    {
      return d->cachedHeaders;
    }

    //TODO use the embedded .qm files to localize header values
    return d->cachedRawHeaders;
  }

  QString ctkPlugin::getSymbolicName() const
  {
    Q_D(const ctkPlugin);
    return d->symbolicName;
  }

  QStringList ctkPlugin::getResourceList(const QString& path) const
  {
    Q_D(const ctkPlugin);
    return d->archive->findResourcesPath(path);
  }

  QByteArray ctkPlugin::getResource(const QString& path) const
  {
    Q_D(const ctkPlugin);
    return d->archive->getPluginResource(path);
  }

  ctkVersion ctkPlugin::getVersion() const
  {
    Q_D(const ctkPlugin);
    return d->version;

}
