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

#ifndef __ctkVTKMatrixWidget_h
#define __ctkVTKMatrixWidget_h

// CTK includes
#include <ctkPimpl.h>
#include "ctkVTKAbstractMatrixWidget.h"

#include "CTKVisualizationVTKWidgetsExport.h"
 
class vtkMatrix4x4;

class CTK_VISUALIZATION_VTK_WIDGETS_EXPORT ctkVTKMatrixWidget : public ctkVTKAbstractMatrixWidget
{
  Q_OBJECT
public:
  /// Self/Superclass typedef
  typedef ctkVTKMatrixWidget  Self;
  typedef ctkVTKAbstractMatrixWidget   Superclass;
  
  /// Constructors
  ctkVTKMatrixWidget(QWidget* parent);

public slots:
  void setMatrix(vtkMatrix4x4* matrix);
}; 

#endif
