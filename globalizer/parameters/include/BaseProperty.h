/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2016 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      BaseProperty.h                                              //
//                                                                         //
//  Purpose:   Header file for random generator class                      //
//                                                                         //
//  Author(s): Lebedev I.                                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#ifndef __BASE_PROPERTY_H__
#define __BASE_PROPERTY_H__

/**
\file BaseProperty.h

\authors ������� �.
\date 2015-2016
\copyright ���� ��. �.�. ������������

\brief ���������� ������ ������� ��� �������

*/

#include "Property.h"

//

/* ======================================================================== *\
**  ���������� �������                                                      **
\* ======================================================================== */


/**
������� ����� ������� ���������
*/
template <class Owner>
class BaseProperty : public IBaseValueClass
{
protected:

  /// ��� ������ ������� �������� ������, ��������� ����� �������� ���������� ��� ������
  typedef int (Owner::*tCheckValue)(int);

  /// �������� �������
  Owner* mOwner;
  /// ����������� �� �������� ��������� �� ���������� ������� ��� ������ �����
  bool mIsReadValue;
  /// �������� �������� �� �������������
  bool mIsPreChange;
public:
  /// ���������� ��������� ����������� ���� ��������
  virtual void operator = (BaseProperty<Owner>& data);
  /// ���������� ��������� ����������� ��� ���������
  virtual void operator = (BaseProperty<Owner>* data);

  /// ������� ������ data
  virtual void Clone(BaseProperty<Owner>** data) = 0;

  BaseProperty(Owner* owner) : mOwner(owner), mIsReadValue(false), mIsPreChange(false) {}
  virtual ~BaseProperty() {}

  /** ������������� ��������
  \param[in] owner - ����� �������� ��������
  \param[in] checkMethod - ����� �������� ������������ ��������� ������
  \param[in] index - ����� ��������
  \param[in] separator - ����������� ��������� �������
  \param[in] size - ������ ������� ��������, ��� ����� ������ �� ����������� �������� - ������ ����� 1
  \param[in] name - ��� ��������
  \param[in] help - ��������� �� ������� �������
  \param[in] link - �������� ������ ��� �������
  \param[in] defValue - �������� �� ���������
  */
  virtual void InitializationParameterProperty(Owner * owner,
    tCheckValue checkMethod, int index, std::string separator, int size, std::string name,
    std::string help, std::string link, std::string defValue) = 0;

  /// ���������� ����������� �� �������� ��������� �� ���������� ������� ��� ������ �����
  virtual bool GetIsReadValue()
  {
    return mIsReadValue;
  }
  /// ������ ����������� �� �������� ��������� �� ���������� ������� ��� ������ �����
  virtual void SetIsReadValue(bool isReadValue)
  {
    mIsReadValue = isReadValue;
  }

  /// ������ ��� �������� ���� �������� �� �������������
  virtual void SetIsPreChange(bool val)
  {
    mIsPreChange = val;
  }

  /// ���� �� �������� �������� �� �������������
  virtual bool IsPreChange()
  {
    return mIsPreChange;
  }


};



/* ======================================================================== *\
**  ���������� ������� ������     BaseProperty                                 **
\* ======================================================================== */

// ------------------------------------------------------------------------------------------------
///���������� ��������� ���������� ���� ��������
template <class Owner>
void BaseProperty<Owner>::operator = (BaseProperty<Owner>& data)
{
  mOwner = data.mOwner;
}

// ------------------------------------------------------------------------------------------------
/// ���������� ��������� ���������� ��� ���������
template <class Owner>
void BaseProperty<Owner>::operator = (BaseProperty<Owner>* data)
{
  mOwner = data->mOwner;
}

#endif //__BASE_PROPERTY_H__
// - end of file ----------------------------------------------------------------------------------
