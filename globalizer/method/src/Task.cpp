/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2015 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      task.cpp                                                    //
//                                                                         //
//  Purpose:   Source file for optimization task class                     //
//                                                                         //
//  Author(s): Sysoyev A., Barkalov K.                                     //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#include "Exception.h"
#include "Task.h"
#include <cstring>

// ------------------------------------------------------------------------------------------------
Task::Task(int _N, int _FreeN, IProblem* _problem, int _ProcLevel)
{
  if ((_N <= 0) || (_N > MaxDim))
  {
    throw EXCEPTION("N is out of range");
  }
  N = _N;
  if ((_FreeN <= 0) || (_FreeN > N))
  {
    throw EXCEPTION("FreeN is out of range");
  }
  FreeN = _FreeN;
  NumOfFunc = _problem->GetNumberOfFunctions();
  _problem->GetBounds(A, B);
  IsOptimumPointDefined = _problem->GetOptimumPoint(OptimumPoint) == IProblem::OK ? true : false;
  IsOptimumValueDefined = _problem->GetOptimumValue(OptimumValue) == IProblem::OK ? true : false;
  pProblem = _problem;
  // По умолчанию фиксированные переменные отсутствуют
  FixedN = 0;
  ProcLevel = _ProcLevel;
  isInit = true;
}

Task::Task()
{
  N = 0;
  FreeN = 0;
  NumOfFunc = 0;
  IsOptimumPointDefined = false;
  IsOptimumValueDefined = false;
  pProblem = 0;
  // По умолчанию фиксированные переменные отсутствуют
  FixedN = 0;
  ProcLevel = 0;
  isInit = false;
}

// ------------------------------------------------------------------------------------------------
Task::~Task()
{
}

Task* Task::Clone()
{
  Task* res = 0;
  if (isInit)
    res = new Task(N, FreeN, pProblem, ProcLevel);
  else
    res = new Task();

  res->FixedN = FixedN;
  memcpy(res->FixedY, FixedY, FixedN * sizeof(double));
  res->isInit = isInit;
  return res;
}

void Task::Init(int _N, int _FreeN, IProblem * _problem, int _ProcLevel)
{
  if ((_N <= 0) || (_N > MaxDim))
  {
    throw EXCEPTION("N is out of range");
  }
  N = _N;
  if ((_FreeN <= 0) || (_FreeN > N))
  {
    throw EXCEPTION("FreeN is out of range");
  }
  FreeN = _FreeN;
  NumOfFunc = _problem->GetNumberOfFunctions();
  _problem->GetBounds(A, B);
  IsOptimumPointDefined = _problem->GetOptimumPoint(OptimumPoint) == IProblem::OK ? true : false;
  IsOptimumValueDefined = _problem->GetOptimumValue(OptimumValue) == IProblem::OK ? true : false;
  pProblem = _problem;
  // По умолчанию фиксированные переменные отсутствуют
  FixedN = 0;
  ProcLevel = _ProcLevel;
  isInit = true;
}

// ------------------------------------------------------------------------------------------------
void Task::SetFixed(int _FixedN, double *_FixedY)
{
  //if (_FixedN != N - FreeN)
  //{
  //  throw EXCEPTION("Not correct FixedN");
  //}
  FixedN = _FixedN;
  if (_FixedY == NULL)
  {
    throw EXCEPTION("Pointer FixedY is NULL");
  }
  memcpy(FixedY, _FixedY, FixedN * sizeof(double));
}
// - end of file ----------------------------------------------------------------------------------
