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

#ifndef __ctkWorkflowStackedWidget_h
#define __ctkWorkflowStackedWidget_h

// Qt includes
class QWidget;
class QString;

// CTK includes
#include "ctkWorkflowAbstractPagedWidget.h"
#include "ctkPimpl.h"
#include "CTKWidgetsExport.h"

class ctkWorkflowStackedWidgetPrivate;

///
/// \brief ctkWorkflowStackedWidget is the basis for a workflow with a user
/// interface containing a QStackedWidget.
class CTK_WIDGETS_EXPORT ctkWorkflowStackedWidget : public ctkWorkflowAbstractPagedWidget
{
  Q_OBJECT

public:

  typedef ctkWorkflowAbstractPagedWidget Superclass;
  explicit ctkWorkflowStackedWidget(QWidget* newParent = 0);
  virtual ~ctkWorkflowStackedWidget();

  virtual void createNewPage(QWidget* widget);

  virtual void showPage(QWidget* widget, const QString& label);

  virtual void initClientArea();

  virtual QWidget* clientArea();

protected:
  QScopedPointer<ctkWorkflowStackedWidgetPrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(ctkWorkflowStackedWidget);
  Q_DISABLE_COPY(ctkWorkflowStackedWidget);

};

#endif
