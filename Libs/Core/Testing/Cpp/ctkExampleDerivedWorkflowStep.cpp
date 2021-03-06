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

// CTK includes
#include "ctkExampleDerivedWorkflowStep.h"

//-----------------------------------------------------------------------------
class ctkExampleDerivedWorkflowStepPrivate
{
public:
  ctkExampleDerivedWorkflowStepPrivate();

  // counters of the number of times we have run the onEntry()
  // and onExit() functions
  int numberOfTimesRanOnEntry;
  int numberOfTimesRanOnExit;
};

//-----------------------------------------------------------------------------
// ctkExampleDerivedWorkflowStepPrivate methods

//-----------------------------------------------------------------------------
ctkExampleDerivedWorkflowStepPrivate::ctkExampleDerivedWorkflowStepPrivate()
{
  this->numberOfTimesRanOnEntry = 0;
  this->numberOfTimesRanOnExit = 0;
}

//-----------------------------------------------------------------------------
// ctkExampleDerivedWorkflowStep methods

//-----------------------------------------------------------------------------
ctkExampleDerivedWorkflowStep::ctkExampleDerivedWorkflowStep(ctkWorkflow* newWorkflow, const QString& newId) :
  Superclass(newWorkflow, newId)
  , d_ptr(new ctkExampleDerivedWorkflowStepPrivate)
{
}

//-----------------------------------------------------------------------------
ctkExampleDerivedWorkflowStep::~ctkExampleDerivedWorkflowStep()
{
}

//-----------------------------------------------------------------------------
void ctkExampleDerivedWorkflowStep::validate(const QString& desiredBranchId)
{
  // Always returns true in this simple example
  this->validationComplete(true,desiredBranchId);
}

//-----------------------------------------------------------------------------
void ctkExampleDerivedWorkflowStep::onEntry(
    const ctkWorkflowStep* comingFrom,
    const ctkWorkflowInterstepTransition::InterstepTransitionType transitionType)
{
  Q_UNUSED(comingFrom);
  Q_UNUSED(transitionType);

  // Simply implements our counter of the number of times we have run this function
  Q_D(ctkExampleDerivedWorkflowStep);
  d->numberOfTimesRanOnEntry++;

  // signals that we are finished
  this->onEntryComplete();
}

//-----------------------------------------------------------------------------
void ctkExampleDerivedWorkflowStep::onExit(
    const ctkWorkflowStep* goingTo,
    const ctkWorkflowInterstepTransition::InterstepTransitionType transitionType)
{
  Q_UNUSED(goingTo);
  Q_UNUSED(transitionType);

  // simply implements our counter of the number of times we have run
  // this function
  Q_D(ctkExampleDerivedWorkflowStep);
  d->numberOfTimesRanOnExit++;

  // signals that we are finished
  this->onExitComplete();
}

//-----------------------------------------------------------------------------
CTK_GET_CXX(ctkExampleDerivedWorkflowStep, int, numberOfTimesRanOnEntry, numberOfTimesRanOnEntry);
CTK_GET_CXX(ctkExampleDerivedWorkflowStep, int, numberOfTimesRanOnExit, numberOfTimesRanOnExit);

