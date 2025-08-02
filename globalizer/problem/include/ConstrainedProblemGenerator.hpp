/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2016 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      ConstrainedProblemGenerator.h                               //
//                                                                         //
//  Purpose:   Header file for Globalizer problem interface                //
//                                                                         //
//                                                                         //
//  Author(s): Lebedev I. Sovrasov V.                                      //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

/**
\file ConstrainedProblemGenerator.h

\authors ������� �. �������� �.
\date 2016
\copyright ���� ��. �.�. ������������

\brief ����� ��� �������� ����� � �������������

\details
*/

#ifndef CONSTRAINED_PROBLEM_GENERATOR_H
#define CONSTRAINED_PROBLEM_GENERATOR_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <omp.h>
#include <iostream>

#include "ProblemPar.hpp"
#include "ConstrainedProblem.hpp"

enum GenerateMode { RHS = 0, DELTA = 1 };

enum GeneratorOptions
{
  IMPROVE_OBJECTIVE = 1,
  TOTAL_DELTA = 1 << 1,
  ZOOM = 1 << 2,
  SHIFT = 1 << 3,
  BOUNDARY_SHIFT = 1 << 4
};

template <class FType>
class ConstrainedProblemGenerator : virtual public ProblemPar
{
protected:

  /// ������� �������
  FType* mPObjective;
  /// �����������
  std::vector<FType*> mPConstraints;
  /// ��������� �����������: ���� ����� ���� ���� �������
  std::vector<double> mConstraintsParams;
  /// ����������� ������ ����������� ��� ���������� ������� �������
  std::vector<double> mImprovementOfTheObjective;
  /// ����� �� ��������� �����
  std::vector<bool> mNeedTuneParam;
  /// ����������� ��������������� ��� ������� �����������
  double** mvZoomRatios;
  /// �������������� ����� �����������
  double*** mvShift;
  /// �������������� ����� ����������� �������� �� �������
  double* mvBoundaryShift;
  /// ����� �� �������������� ������
  bool mIsZoom;
  /// ����� �� �������� ������� �����������
  bool mIsShift;
  /// ����� �� �������� ������� ������� ������� �� �������
  bool mIsBoundaryShift;
  /// �������� ������ ��������� ����� �� ������� ������� (������� 0.5)
  int mBoundarySearchPrecision;
  /// ���� ����� ������(���� �������) ��� ���� ������� ��� ��� ������ ������� ����
  bool mIsTotalDelta;

  /// ������� ����������� �������
  FType* currentFunction;
  /// ����� ����������� �������
  int currentFunctionNumber;


  /// ��������� ���� ������� currentFunction
  double OneFunctionCalculate(double* y);
  /// �������� �������� ���� ����������� � �����
  double MaxFunctionCalculate(double* y);

  double FunctionCalculate(double* x);

  double CalculateRHS(double delta, int m = 100, double Epsilon = 0.01, int maxM = 10000000);

  /// ������ ����������� ��������������� ��� ������� �����������
  virtual void SetZoom();
  /// ������ ����� � ����������� �������� ��� ������� �����������
  virtual void SetShift();
  /// ������ ����� ����������� �������� ������� ������� �� ������� �������
  virtual void SetBoundaryShift();

  /** �������������� ������� � ������� index,
  �������������� ���� ��������� �������� ��������� ������� � ����������� �� ���������� ������
  */
  virtual void InitFunc(FType* func, int index)
  {  }

  double CalculateFunctionConstrained(const double* y, int fNumber);

public:
  double** mmQ;
  double** improvementCoefficients;
  bool mmIsImprovementOfTheObjective;
  ConstrainedProblemGenerator();

  /** ����� ���������� ���������� ����� ����������� �������� ������� �������
  \param[out] y �����, � ������� ����������� ����������� ��������
  \return ��� ������ (#OK ��� #UNDEFINED)
  */
  virtual int GetOptimumPoint(double* y) const;

  /// ���������� ����� ����������� �������� ��� ������� fNumber
  virtual int GetConstraintOptimumPoint(double* point, int fNumber);

  /// �������� ����������� � ������
  void AddConstraint(FType* function, double parameter, int mode = DELTA, double imp = 0);

  /// ������ ������� �������
  void SetObjective(FType* function);

  /** ������� ������
  \param[in] isImprovementOfTheObjective - ������������ �� ����� ������� �������
  \param[in] isTotalDelta - �������� ��� ����������� ������ ��� �� ����������� (���� true �� �������� mode � AddConstraint �� ������������)
  \param[in] isZoom - �������������� �� ����������� ��� ��������� ������������� ������
  \param[in] isShift - �������� �� ����������� ��� �� ���������� ������� ��� ������ ���������� �������
  \param[in] isBoundaryShift - �������� �� ���������� ������� �� �������
  \param[in] boundarySearchPrecision - �������� ������ ����� �� ������� ���������� ������� (������� 0.5)
  \return ����� ������
  */
  ConstrainedProblem<FType> GenerateProblem(bool isImprovementOfTheObjective = false,
    bool isTotalDelta = true, bool isZoom = false, bool isShift = false,
    bool isBoundaryShift = false, int boundarySearchPrecision = 20);

  /** ������� ������
  \param[in] generateOptions - ����, ���������� ����� ���������� �����. ��������
  ����������� ��������� ��������:
   GeneratorOptions::IMPROVE_OBJECTIVE - ������������ �� ����� ������� �������
   GeneratorOptions::TOTAL_DELTA - �������� ��� ����������� ������ ��� �� ����������� (���� true �� �������� mode � AddConstraint �� ������������)
   GeneratorOptions::ZOOM - �������������� �� ����������� ��� ��������� ������������� ������
   GeneratorOptions::SHIFT - �������� �� ����������� ��� �� ���������� ������� ��� ������ ���������� �������
   GeneratorOptions::BOUNDARY_SHIFT - �������� �� ���������� ������� �� �������
  \param[in] boundarySearchPrecision - �������� ������ ����� �� ������� ���������� ������� (������� 0.5)
  \return ����� ������
  */
  ConstrainedProblem<FType> GenerateProblem(int generateOptions, int boundarySearchPrecision = 20);

};

/** ����� ���������� ���������� ����� ����������� �������� ������� �������
\param[out] y �����, � ������� ����������� ����������� ��������
\return ��� ������ (#OK ��� #UNDEFINED)
*/
template <class FType>
int ConstrainedProblemGenerator<FType>::GetOptimumPoint(double* y) const
{
  mPObjective->GetOptimumPoint(y);

  for (int i = 0; i < mDim; i++)
  {
    y[i] = y[i] * (*mvZoomRatios)[mNumberOfConstraints] + (*mvShift)[mNumberOfConstraints][i] + mvBoundaryShift[i];
  }

  return ProblemPar::ProblemOK;
}

/// ���������� ����� ����������� �������� ��� ������� fNumber
template <class FType>
int ConstrainedProblemGenerator<FType>::GetConstraintOptimumPoint(double* point, int fNumber)
{
  mPConstraints[fNumber]->GetOptimumPoint(point);
  for (int i = 0; i < mDim; i++)
  {
    point[i] = point[i] * (*mvZoomRatios)[fNumber] + (*mvShift)[fNumber][i];
  }
  return ProblemPar::ProblemOK;
}

template <class FType>
ConstrainedProblemGenerator<FType>::ConstrainedProblemGenerator()
{
  mIsTotalDelta = true;
  mIsZoom = false;
  mIsShift = false;
  mIsBoundaryShift = false;
  mBoundarySearchPrecision = 20;

  mvZoomRatios = 0;
  mvShift = 0;
  mvBoundaryShift = 0;

  currentFunction = 0;
  currentFunctionNumber = 0;

  mPObjective = 0;
}

template <class FType>
void ConstrainedProblemGenerator<FType>::SetObjective(FType* function)
{
  mPObjective = function;
  mNumberOfCriterions = 1;
  mDim = function->GetDimension();
}

template <class FType>
double ConstrainedProblemGenerator<FType>::OneFunctionCalculate(double* y)
{
  double x[MAX_TRIAL_DIMENSION];
  for (int i = 0; i < mDim; i++)
  {
    x[i] = (y[i] - (*mvShift)[currentFunctionNumber][i]) / (*mvZoomRatios)[currentFunctionNumber];
  }
  return currentFunction->Calculate(x);
}


/// �������� �������� ���� ����������� � �����
template <class FType>
double ConstrainedProblemGenerator<FType>::MaxFunctionCalculate(double* y)
{
  double x[MAX_TRIAL_DIMENSION];
  if (GetRealNumberOfConstraints() > 0)
  {
    for (int j = 0; j < mDim; j++)
    {
      x[j] = (y[j] - (*mvShift)[0][j]) / (*mvZoomRatios)[0];
    }
    double res = mPConstraints[0]->Calculate(x);
    for (int i = 1; i < GetRealNumberOfConstraints(); i++)
    {
      for (int j = 0; j < mDim; j++)
      {
        x[j] = (y[j] - (*mvShift)[i][j]) / (*mvZoomRatios)[i];
      }

      double f = mPConstraints[i]->Calculate(x);
      if (res < f)
        res = f;
    }
    return res;
  }
  return 0;
}


template <class FType>
double ConstrainedProblemGenerator<FType>::FunctionCalculate(double* x)
{
  if (mIsTotalDelta)
    return MaxFunctionCalculate(x);
  else
    return OneFunctionCalculate(x);
}

template <class FType>
double ConstrainedProblemGenerator<FType>::CalculateFunctionConstrained(const double* y, int fNumber)
{
  double x[MAX_TRIAL_DIMENSION];
  if (fNumber < GetRealNumberOfConstraints())
  {
    for (int i = 0; i < mDim; i++)
    {
      x[i] = (y[i] - (*mvShift)[fNumber][i]) / (*mvZoomRatios)[fNumber];
    }
    return mPConstraints[fNumber]->Calculate(x) - (*mmQ)[fNumber];
  }
  else
  {
    if (mmIsImprovementOfTheObjective)
    {
      double resultCoefficient = 0;

      for (int j = 0; j < GetRealNumberOfConstraints(); j++)
      {
        for (int i = 0; i < mDim; i++)
        {
          x[i] = (y[i] - (*mvShift)[j][i]) / (*mvZoomRatios)[j];
        }
        double f = mPConstraints[j]->Calculate(x) - (*mmQ)[j];
        double fVal = std::max(f, 0.0);
        resultCoefficient += (*improvementCoefficients)[j] * (fVal * fVal * fVal);
      }
      double result = 0;
      result = mPConstraints[fNumber]->Calculate(y) - resultCoefficient;
      return result;
    }
    else
    {
      double boundaryShift = 0; // �������� ������
      double* objectiveMin = new double[mDim];
      for (int j = 0; j < mDim; j++)
      {
        objectiveMin[j] = 0;
        x[j] = y[j];
      }
      GetOptimumPoint(objectiveMin);

      int coordinateNum = 0; // ����������, �� ������� ���������� �����
      for (int i = 0; i < mDim; i++)
      {
        if (mvBoundaryShift[i] != 0)
        {
          coordinateNum = i;
          boundaryShift = mvBoundaryShift[i];
        }
      }
      // �������������� ��������� ����� �������, ����� ����� �������� ��������� �� ������� ���������� �������
      if (boundaryShift > 0)
      {
        if ((y[coordinateNum] >= objectiveMin[coordinateNum]) &&
          (y[coordinateNum] < objectiveMin[coordinateNum] + boundaryShift))
        {
          x[coordinateNum] = objectiveMin[coordinateNum] + boundaryShift -
            (objectiveMin[coordinateNum] + boundaryShift - y[coordinateNum]) * 2;
        }
        else if ((y[coordinateNum] > objectiveMin[coordinateNum] - 2 * boundaryShift) &&
          (y[coordinateNum] < objectiveMin[coordinateNum]))
        {
          x[coordinateNum] = objectiveMin[coordinateNum] - 2 * boundaryShift +
            (y[coordinateNum] - (objectiveMin[coordinateNum] - 2 * boundaryShift)) / 2;
        }
      }
      else if (boundaryShift < 0)
      {
        if ((y[coordinateNum] > objectiveMin[coordinateNum]) &&
          (y[coordinateNum] < objectiveMin[coordinateNum] - 2 * boundaryShift))
        {
          x[coordinateNum] = objectiveMin[coordinateNum] - 2 * boundaryShift -
            (objectiveMin[coordinateNum] - 2 * boundaryShift - y[coordinateNum]) / 2;
        }
        else if ((y[coordinateNum] > objectiveMin[coordinateNum] + boundaryShift) &&
          (y[coordinateNum] < objectiveMin[coordinateNum]))
        {
          x[coordinateNum] = objectiveMin[coordinateNum] + boundaryShift +
            (y[coordinateNum] - (objectiveMin[coordinateNum] + boundaryShift)) * 2;
        }
      }
      delete[] objectiveMin;

      return mPConstraints[fNumber]->Calculate(x);
    }
  }
}

template <class FType>
double ConstrainedProblemGenerator<FType>::CalculateRHS(double delta, int m, double Epsilon, int maxM)
{
  double rhs = 0;
  double* objectiveMin = new double[mDim];
  unsigned dimension = mDim;
  double hmin = 0;

  for (int j = 0; j < mDim; j++)
    objectiveMin[j] = 0;
  GetOptimumPoint(objectiveMin);

  hmin = mPObjective->GetOptimumValue();
  //mPObjective->GetOptimumValue(hmin);

  double hmax = hmin;
  double d = 0;
  //����������� �������, � ����� - ���������
  int* size = new int[dimension];//���-�� ����� ����� �� �����������
  double* step = new double[dimension];//��� �� ������ �����������
  int sumn = 1;//����� ���������

  double* a = new double[dimension];
  double* b = new double[dimension];
  mPObjective->GetBounds(a, b);
  double multiplyingLength = 1;
  for (unsigned i = 0; i < dimension; i++)
  {
    d = (b[i] - a[i]);
    size[i] = (int)ceil(d / Epsilon) + 1;
    step[i] = d / (size[i] - 1);
    multiplyingLength = multiplyingLength * d;
    sumn *= (size[i]);
  }

  if ((sumn > maxM) || (sumn <= 0))
  {
    multiplyingLength = multiplyingLength / maxM;
    Epsilon = pow(multiplyingLength, 1.0 / (double)dimension);
    sumn = 1;
    multiplyingLength = 1;

    for (unsigned i = 0; i < dimension; i++)
    {
      d = (b[i] - a[i]);
      size[i] = (int)ceil(d / Epsilon) + 1;
      step[i] = d / (size[i] - 1);
      sumn *= (size[i]);
    }

  }

  double* f = new double[sumn];//�������� �������
  double* yArray = new double[dimension*omp_get_max_threads()];

#pragma omp parallel for num_threads(omp_get_max_threads())
  for (int i = 0; i < sumn; i++)
  {
    double w;
    int z = i;
    double* y = yArray + omp_get_thread_num()*dimension;
    //��������� ���������� ����� ���������
    for (unsigned j = 0; j < dimension; j++)
    {
      w = z % size[j];//���������� ����� ���� �� i-�� �����������
      y[j] = a[j] + w * step[j];//����� ������� + ����� ���� �� i-�� ����������� * ��� �� i-�� �����������
      z = z / size[j];//��� ���������� ������ ���� �� ��������� �����������
    }
    //�������� ���������
    f[i] = FunctionCalculate(y);
    hmax = std::max(f[i], hmax);
    hmin = std::min(f[i], hmin);
  }

  double* h1 = new double[m];
  double* h2 = new double[m];
  int* p = new int[m];
  int* s = new int[m];

  double deltah = (hmax - hmin) / m;

  for (int i = 0; i < m; i++)
  {
    h1[i] = hmin + i * deltah;
    h2[i] = hmin + (i + 1) * deltah;
    p[i] = 0;
    s[i] = 0;
  }

  for (int i = 0; i < sumn; i++)
    for (int j = 0; j < m; j++)
      if ((f[i] >= h1[j]) && (f[i] <= h2[j]))
      {
        p[j] ++;
        break;
      }

  s[0] = p[0];
  for (int i = 1; i < m; i++)
  {
    s[i] = s[i - 1] + p[i];
  }

  double smax = s[m - 1];
  double g = delta * smax;
  for (int i = 0; i < m; i++)
  {
    if (s[i] >= g)
    {
      rhs = h2[i];
      break;
    }
  }

  double dm = delta;
  if (dm == 0)
    dm += 0.1;
  dm = dm * (hmax - hmin);

  double criticalValue = FunctionCalculate(objectiveMin);

  if (rhs < criticalValue)
  {
    std::cout << "Q was changed from " << rhs << " to " << criticalValue + dm << "\n";
    rhs = criticalValue + dm;
  }

  delete[] size;
  delete[] step;
  delete[] a;
  delete[] b;
  delete[] f;
  delete[] yArray;

  delete[] h1;
  delete[] h2;
  delete[] p;
  delete[] s;

  return rhs;
}

template <class FType>
void ConstrainedProblemGenerator<FType>::AddConstraint(FType* function, double parameter, int mode, double imp)
{
  mPConstraints.push_back(function);
  mConstraintsParams.push_back(parameter);
  if (mode == DELTA)
    mNeedTuneParam.push_back(true);
  else
    mNeedTuneParam.push_back(false);
  mImprovementOfTheObjective.push_back(imp);
  mNumberOfConstraints++;
}

template <class FType>
ConstrainedProblem<FType> ConstrainedProblemGenerator<FType>::
GenerateProblem(int generateOptions, int boundarySearchPrecision)
{
  mIsShift = bool(generateOptions & SHIFT);
  mIsZoom = bool(generateOptions & ZOOM);

  mIsBoundaryShift = bool(generateOptions & BOUNDARY_SHIFT);
  mBoundarySearchPrecision = boundarySearchPrecision;

  /// �������, � ������ �����������, ����� �������
  FType** mPFunction = new FType*[mNumberOfConstraints + 1];
  for (int i = 0; i < mNumberOfConstraints; i++)
  {
    mPFunction[i] = mPConstraints[i];
  }
  mPFunction[mNumberOfConstraints] = mPObjective;

  double* objectiveMin = new double[mDim];

  /// ����� �����������, ��� �� RHS
  mmQ = new double*[1];
  (*mmQ) = new double[mNumberOfConstraints + 1];

  /// ����������� ��������������� ��� ������� �����������
  double* mZoomRatios = new double[mNumberOfConstraints + 1];
  /// �������������� ����� �����������
  double** mShift = new double*[mNumberOfConstraints + 1];

  for (int i = 0; i < GetRealNumberOfFunctions(); i++)
  {
    mZoomRatios[i] = 1.0;

    mShift[i] = new double[mDim];
    for (int j = 0; j < mDim; j++)
    {
      mShift[i][j] = 0.0;
    }
  }

  /// �������������� ����� ����������� �������� �� �������
  double* mBoundaryShift = new double[mDim];
  for (int i = 0; i < mDim; i++)
  {
    mBoundaryShift[i] = 0.0;
  }
  mvBoundaryShift = mBoundaryShift;
  mvZoomRatios = &mZoomRatios;
  mvShift = &mShift;

  mmIsImprovementOfTheObjective = bool(generateOptions & IMPROVE_OBJECTIVE);
  mIsTotalDelta = bool(generateOptions & TOTAL_DELTA);
  /// ����������� ���������
  improvementCoefficients = new double*[1];
  *improvementCoefficients = new double[mNumberOfConstraints + 1];
  for (int i = 0; i < mNumberOfConstraints; i++)
    (*improvementCoefficients)[i] = mImprovementOfTheObjective[i];
  (*improvementCoefficients)[mNumberOfConstraints] = 0;

  for (int i = 0; i < GetRealNumberOfFunctions(); i++)
  {
    InitFunc(mPFunction[i], i);
  }

  if (mIsZoom)
  {
    SetZoom();
  }

  if (mIsShift)
  {
    SetShift();
  }

  currentFunctionNumber = 0;

  if (mIsTotalDelta)
  {
    double q = CalculateRHS(mConstraintsParams[0]);
    for (int i = 0; i < GetRealNumberOfConstraints(); i++)
    {
      (*mmQ)[i] = q;
    }
  }
  else
  {
    for (int i = 0; i < GetRealNumberOfConstraints(); i++)
    {
      if (mNeedTuneParam[i])
      {
        currentFunctionNumber = i;
        currentFunction = mPFunction[i];
        (*mmQ)[i] = CalculateRHS(mConstraintsParams[i]);
      }
      else
      {
        (*mmQ)[i] = mConstraintsParams[i];
      }
    }
  }

  if (mIsBoundaryShift)
  {
    SetBoundaryShift();
  }

  return ConstrainedProblem<FType>(mPFunction, mmQ, mZoomRatios, mShift,
    mmIsImprovementOfTheObjective, improvementCoefficients, mNumberOfConstraints,
    mNumberOfCriterions, mDim);
}

template <class FType>
ConstrainedProblem<FType> ConstrainedProblemGenerator<FType>::GenerateProblem(
  bool isImprovementOfTheObjective, bool isTotalDelta, bool isZoom, bool isShift,
  bool isBoundaryShift, int boundarySearchPrecision)
{
  mIsShift = isShift;
  mIsZoom = isZoom;
  mIsBoundaryShift = isBoundaryShift;
  mBoundarySearchPrecision = boundarySearchPrecision;
  /// �������, � ������ �����������, ����� �������
  FType** mPFunction = new FType*[mNumberOfConstraints + 1];
  for (int i = 0; i < mNumberOfConstraints; i++)
  {
    mPFunction[i] = mPConstraints[i];
  }
  mPFunction[mNumberOfConstraints] = mPObjective;

  double* objectiveMin = new double[mDim];

  /// ����� �����������, ��� �� RHS
  mmQ = new double*[1];
  (*mmQ) = new double[mNumberOfConstraints + 1];

  /// ����������� ��������������� ��� ������� �����������
  double* mZoomRatios = new double[mNumberOfConstraints + 1];
  /// �������������� ����� �����������
  double** mShift = new double*[mNumberOfConstraints + 1];

  for (int i = 0; i < GetRealNumberOfFunctions(); i++)
  {
    mZoomRatios[i] = 1.0;

    mShift[i] = new double[mDim];
    for (int j = 0; j < mDim; j++)
    {
      mShift[i][j] = 0.0;
    }
  }

  /// �������������� ����� ����������� �������� �� �������
  double* mBoundaryShift = new double[mDim];
  for (int i = 0; i < mDim; i++)
  {
    mBoundaryShift[i] = 0.0;
  }
  mvBoundaryShift = mBoundaryShift;
  mvZoomRatios = &mZoomRatios;
  mvShift = &mShift;

  /// �������� �� ������� ������� ����� ���������� ����������� �� �����������
  mmIsImprovementOfTheObjective = isImprovementOfTheObjective;
  mIsTotalDelta = isTotalDelta;
  /// ����������� ���������
  improvementCoefficients = new double*[1];
  *improvementCoefficients = new double[mNumberOfConstraints + 1];
  for (int i = 0; i < mNumberOfConstraints; i++)
    (*improvementCoefficients)[i] = mImprovementOfTheObjective[i];
  (*improvementCoefficients)[mNumberOfConstraints] = 0;

  for (int i = 0; i < GetRealNumberOfFunctions(); i++)
  {
    InitFunc(mPFunction[i], i);
  }

  if (mIsZoom)
  {
    SetZoom();
  }

  if (mIsShift)
  {
    SetShift();
  }

  currentFunctionNumber = 0;

  if (mIsTotalDelta)
  {
    double q = CalculateRHS(mConstraintsParams[0]);
    for (int i = 0; i < GetRealNumberOfConstraints(); i++)
    {
      (*mmQ)[i] = q;
    }
  }
  else
  {
    for (int i = 0; i < GetRealNumberOfConstraints(); i++)
    {
      if (mNeedTuneParam[i])
      {
        currentFunctionNumber = i;
        currentFunction = mPFunction[i];
        (*mmQ)[i] = CalculateRHS(mConstraintsParams[i]);
      }
      else
      {
        (*mmQ)[i] = mConstraintsParams[i];
      }
    }
  }

  if (mIsBoundaryShift)
  {
    SetBoundaryShift();
  }

  return ConstrainedProblem<FType>(mPFunction, mmQ, mZoomRatios, mShift,
    mmIsImprovementOfTheObjective, improvementCoefficients, mNumberOfConstraints,
    mNumberOfCriterions, mDim);
}

/// ������ ����������� ��������������� ��� ������� �����������
template <class FType>
void ConstrainedProblemGenerator<FType>::SetZoom()
{

  double* objectiveMin = new double[mDim];
  double* lower = new double[mDim];
  double* upper = new double[mDim];
  double* constraintMin = new double[mDim];

  for (int j = 0; j < mDim; j++)
  {
    objectiveMin[j] = 0;
    lower[j] = 0;
    upper[j] = 0;
  }
  /// ���������� ���������� ����������� �������� ������� �������
  GetOptimumPoint(objectiveMin);
  /// ���������� ������� �������
  mPObjective->GetBounds(lower, upper);

  double maxDistanceToBoundary = 0;

  for (int k = 0; k < mDim; k++)
  {
    if (maxDistanceToBoundary < (objectiveMin[k] - lower[k]))
      maxDistanceToBoundary = (objectiveMin[k] - lower[k]);
    if (maxDistanceToBoundary < (upper[k] - objectiveMin[k]))
      maxDistanceToBoundary = (upper[k] - objectiveMin[k]);
  }

  if (fabs(maxDistanceToBoundary) < AccuracyDouble)
  {
    mIsZoom = false;
    for (int j = 0; j < GetRealNumberOfFunctions(); j++)
    {
      (*mvZoomRatios)[j] = 1;
    }

    delete[] objectiveMin;
    delete[] lower;
    delete[] upper;
    delete[] constraintMin;
    return;
  }

  for (int i = 0; i < GetRealNumberOfConstraints(); i++)
  {
    double minDistanceToBoundary = upper[0] - lower[0];

    for (int j = 0; j < mDim; j++)
    {
      constraintMin[j] = 0;
    }

    GetConstraintOptimumPoint(constraintMin, i);
    for (int k = 0; k < mDim; k++)
    {
      if (minDistanceToBoundary > (constraintMin[k] - lower[k]))
        minDistanceToBoundary = (constraintMin[k] - lower[k]);
      if (minDistanceToBoundary > (upper[k] - constraintMin[k]))
        minDistanceToBoundary = (upper[k] - constraintMin[k]);
    }

    if (fabs(minDistanceToBoundary) < AccuracyDouble)
    {
      mIsZoom = false;
      for (int j = 0; j < GetRealNumberOfFunctions(); j++)
      {
        (*mvZoomRatios)[j] = 1;
      }
      delete[] objectiveMin;
      delete[] lower;
      delete[] upper;
      delete[] constraintMin;
      return;
    }
    else
    {
      (*mvZoomRatios)[i] = maxDistanceToBoundary / minDistanceToBoundary;
    }
  }

  delete[] objectiveMin;
  delete[] lower;
  delete[] upper;
  delete[] constraintMin;
}

/// ������ ����� � ����������� �������� ��� ������� �����������
template <class FType>
void ConstrainedProblemGenerator<FType>::SetShift()
{
  double* objectiveMin = new double[mDim];
  double* lower = new double[mDim];
  double* upper = new double[mDim];
  double* constraintMin = new double[mDim];

  for (int j = 0; j < mDim; j++)
  {
    objectiveMin[j] = 0;
    lower[j] = 0;
    upper[j] = 0;
  }
  /// ���������� ���������� ����������� �������� ������� �������
  GetOptimumPoint(objectiveMin);
  /// ���������� ������� �������
  mPObjective->GetBounds(lower, upper);

  for (int i = 0; i < GetRealNumberOfConstraints(); i++)
  {

    for (int j = 0; j < mDim; j++)
    {
      constraintMin[j] = 0;
    }

    GetConstraintOptimumPoint(constraintMin, i);

    for (int k = 0; k < mDim; k++)
    {
      (*mvShift)[i][k] = objectiveMin[k] - constraintMin[k];
    }

    GetConstraintOptimumPoint(constraintMin, i);
  }

  delete[] objectiveMin;
  delete[] lower;
  delete[] upper;
  delete[] constraintMin;
}

/// ������ ����� ����������� �������� �� ������� �������
template <class FType>
void ConstrainedProblemGenerator<FType>::SetBoundaryShift()
{
  double* objectiveMin = new double[mDim];
  double* tempPoint = new double[mDim];
  double* lower = new double[mDim];
  double* upper = new double[mDim];
  double* outPoint = new double[mDim], *inPoint = new double[mDim];
  double delta = pow(0.5, 5);

  for (int j = 0; j < mDim; j++)
  {
    objectiveMin[j] = 0;
    tempPoint[j] = 0;
    lower[j] = 0;
    upper[j] = 0;
    outPoint[j] = 0;
    inPoint[j] = 0;
  }

  // ���������� ������� ���������� ������� ������ (��� ����� �����������)
  mPObjective->GetBounds(lower, upper);
  /// ���������� ���������� ����������� �������� ������� �������
  GetOptimumPoint(objectiveMin);

  bool isBoundReached = false; // ������� �� ����� �� �������
  int closestDir = 0; // �����������, � ������� ���� ������� ��������� ����� �� �������
  int i = 1;

  while (!isBoundReached)
  {
    for (int k = 0; k < 2 * mDim; k++)
    {
      isBoundReached = false;
      // ������ ����� �����
      GetOptimumPoint(tempPoint);
      tempPoint[k%mDim] = objectiveMin[k%mDim] + ((k >= mDim) ? (-1) : (1)) * delta * i;

      // ��������, �� ����� �� �� ������� ������� ������ (��� ����� �����������)
      if ((tempPoint[k % mDim] - upper[k % mDim] >= 0) ||
        (tempPoint[k % mDim] - lower[k % mDim] <= 0))
      {
        if (tempPoint[k % mDim] - upper[k % mDim] >= 0)
        {
          tempPoint[k % mDim] = upper[k % mDim];
        }
        else
        {
          tempPoint[k % mDim] = lower[k % mDim];
        }
        isBoundReached = true;
        closestDir = k % mDim;
        break;
      }

      for (int j = 0; j < GetRealNumberOfConstraints(); j++)
      {
        if (CalculateFunctionConstrained(tempPoint, j) >= 0)
        {
          isBoundReached = true;
          closestDir = k%mDim;
          if (CalculateFunctionConstrained(tempPoint, j) == 0) // ����� ����� ������ �� ������� ���������� �������
          {
            break;
          }

          // ����� - ����� �� ������� -> ������� ����� ������ ���������� ������� �������� �������
          for (int l = 0; l < mDim; l++)
          {
            outPoint[l] = tempPoint[l];
            inPoint[l] = tempPoint[l];
          }
          inPoint[closestDir] = objectiveMin[closestDir] + ((k >= mDim) ? (-1) : (1)) * delta * (i - 1);

          // �������� ������  - 2^(-mBoundarySearchPrecision)
          while ((abs(inPoint[closestDir] - outPoint[closestDir]) > pow(0.5, mBoundarySearchPrecision)) &&
            (CalculateFunctionConstrained(tempPoint, j) != 0))
          {
            delta = delta / 2;
            tempPoint[closestDir] = inPoint[closestDir] + ((k >= mDim) ? (-1) : (1)) * delta;
            if (CalculateFunctionConstrained(tempPoint, j) > 0)
            {
              outPoint[closestDir] = tempPoint[closestDir];
              tempPoint[closestDir] = inPoint[closestDir];
            }
            else if (CalculateFunctionConstrained(tempPoint, j) < 0)
            {
              inPoint[closestDir] = tempPoint[closestDir];
            }
          }
          break;
        }
      }
      if (isBoundReached) break;
    }
    i++;
  }

  mvBoundaryShift[closestDir] = tempPoint[closestDir] - objectiveMin[closestDir];

  delete[] objectiveMin;
  delete[] tempPoint;
  delete[] lower;
  delete[] upper;
  delete[] outPoint;
  delete[] inPoint;
}

#endif // CONSTRAINED_PROBLEM_GENERATOR_H