
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2016 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      CombinableBaseParameter.h                                                  //
//                                                                         //
//  Purpose:   Header file for random generator class                      //
//                                                                         //
//  Author(s): Lebedev I.                                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#ifndef __COMBINABLE_BASE_PARAMETERS_H__
#define __COMBINABLE_BASE_PARAMETERS_H__

/**
\file CombinableBaseParameter.h

\authors ������� �.
\date 2015-2016
\copyright ���� ��. �.�. ������������

\brief ���������� ������ ������� ��� �������

*/

#include "Types.h"

/**
������� ����� ����������
��� �������� ���������� ���������� �������������� �������� OWNER_NAME
� � ������������ ������ mOwner
(mOwner = this;)
*/
class CombinableBaseParameters
{
protected:
  /// ���������� ��������� ��������� ������
  int mArgumentCount;
  /// ���� ��������� ��������� ������
  char** mAargumentValue;
  /// ��� �� ��������������� MPI
  bool mIsMPIInit;
public:

  /// ������ ��������� ���������
  virtual void SetInitParam(int argc = 0, char* argv[] = 0, bool isMPIInit = false)
  {
    mArgumentCount = argc;
    mAargumentValue = argv;
    mIsMPIInit = isMPIInit;
  }

  /// ���������� ��� ��������� ���� ������� � �����
  virtual void CombineOptions(IBaseValueClass** otherOptions, int count) = 0;
  /// ���������� ��������� ��������
  virtual IBaseValueClass** GetOptions() = 0;
  /// ���������� ���������� �����
  virtual int GetOptionsCount() = 0;

  virtual void SetVal(std::string name, std::string val) = 0;
  /// ������� ��������� � ������ name �������� val
  virtual void SetVal(std::string name, void* val) = 0;
  /// ���������� ������ � ��������� ��������� � ������ name
  virtual std::string GetStringVal(std::string name) = 0;
  /// ���������� �������� ��������� � ������ name
  virtual void* GetVal(std::string name) = 0;

  CombinableBaseParameters()
  {
    mArgumentCount = 0;
    mAargumentValue = 0;
    mIsMPIInit = false;
  }

  /// ���������������� ������ ������ �� ���������� �������
  virtual void InitDataByParameters()
  {};
};

#endif //__COMBINABLE_BASE_PARAMETERS_H__