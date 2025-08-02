/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2016 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      ParameterProperty.h                                                  //
//                                                                         //
//  Purpose:   Header file for random generator class                      //
//                                                                         //
//  Author(s): Lebedev I.                                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#ifndef __PARAMETER_PROPERTY_H__
#define __PARAMETER_PROPERTY_H__

#include <cctype>

/**
\file ParameterProperty.h

\authors ������� �.
\date 2015-2016
\copyright ���� ��. �.�. ������������

\brief ���������� ������ ������� ��� �������

*/

#include "TypedProperty.h"

//

/* ======================================================================== *\
**  ���������� �������                                                      **
\* ======================================================================== */

/**
������� ����� ��� ������� ����������, ����� ������ ����������
*/
template <class Type, class Owner>
class ParameterProperty : public TypedProperty<Type, Owner>
{
protected:
  typedef typename BaseProperty<Owner>::tCheckValue tCheckValue;
  typedef typename TypedProperty<Type, Owner>::tGetter tGetter;
  typedef typename TypedProperty<Type, Owner>::tSetter tSetter;
  /// ����������� �������
  std::string mSeparator;
  /// ������ �������
  int mSize;
  /// ��� ��������
  std::string mName;
  /// ����� �������
  std::string mHelp;
  /// �������� ��� ��� ��������� ������
  std::string mLink;

  /// ������ ���������� ��� �� �����
  std::string GetFullLink();

public:

  /// ���������� ��������� ���������� ���� ��������
  virtual void operator = (ParameterProperty<Type, Owner>&  data);
  /// ���������� ��������� ���������� ��� ���������
  virtual void operator = (ParameterProperty<Type, Owner>* data);

  /// ������� ������ data
  virtual void Clone(BaseProperty<Owner>** data);

  /// ������ ����������� ��������� �������
  virtual void SetSeparator(std::string separator);
  /// ���������� ����������� ��������� �������
  virtual std::string GetSeparator();

  /// ������ ������ ������� ���������
  virtual void SetSize(int size);
  /// ���������� ������ ������� ���������
  virtual int GetSize();

  /// ��� ��������
  virtual std::string GetName();
  /// ����� �������
  virtual std::string GetHelp();
  /// �������� ��� ��� ��������� ������
  virtual std::string GetLink();

  /// ��� ��������
  virtual void SetName(std::string name);
  /// ����� �������
  virtual void SetHelp(std::string help);
  /// �������� ��� ��� ��������� ������
  virtual void SetLink(std::string link);
  /// ���������� ������� �� ��������
  virtual std::string GetHelpString();
  /// ���������� �������� ��������� ���������
  virtual std::string GetCurrentStringValue();

  /// �������� � ������
  virtual std::string ToString();
  /// ��������� �������� �� ������
  virtual void FromString(std::string val);

  /// ��������� �� ��� ��������� �� ��������� �������
  virtual bool IsNameEqual(std::string name);

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
    std::string help, std::string link, std::string defValue);

  /** ������������� ��������
  \param[in] owner - ����� �������� ��������
  \param[in] getMethod - ������
  \param[in] setMethod - ������
  \param[in] checkMethod - ����� �������� ������������ ��������� ������
  \param[in] index - ����� ��������
  \param[in] separator - ����������� ��������� �������
  \param[in] size - ������ ������� ��������, ��� ����� ������ �� ����������� �������� - ������ ����� 1
  \param[in] name - ��� ��������
  \param[in] help - ��������� �� ������� �������
  \param[in] link - �������� ������ ��� �������
  \param[in] defValue - �������� �� ���������
  */
  virtual void InitializationParameterProperty(Owner * owner, tGetter getMethod, tSetter setMethod,
    tCheckValue checkMethod, int index, std::string separator, int size, std::string name,
    std::string help, std::string link, std::string defValue);

  ParameterProperty();
  ParameterProperty(Type value);
  ParameterProperty(Owner * owner, tGetter getMethod, tSetter setMethod,
    tCheckValue checkMethod, Type value);




};


/* ======================================================================== *\
**  ���������� ������� ������     ParameterProperty                                 **
\* ======================================================================== */

// ------------------------------------------------------------------------------------------------
/// ���������� ��������� ���������� ���� ��������
template <class Type, class Owner>
void ParameterProperty<Type, Owner>::operator = (ParameterProperty<Type, Owner>&  data)
{
  mSeparator = data.mSeparator;
  mSize = data.mSize;
  mName = data.mName;
  mHelp = data.mHelp;
  mLink = data.mLink;
  this->mIsFlag = data.mIsFlag;
  TypedProperty<Type, Owner>::operator=(data);
}

// ------------------------------------------------------------------------------------------------
/// ���������� ��������� ���������� ��� ���������
template <class Type, class Owner>
void ParameterProperty<Type, Owner>::operator = (ParameterProperty<Type, Owner>* data)
{
  mSeparator = data->mSeparator;
  mSize = data->mSize;
  mName = data->mName;
  mHelp = data->mHelp;
  mLink = data->mLink;
  this->mIsFlag = data->mIsFlag;
  TypedProperty<Type, Owner>::operator=(data);
}

// ------------------------------------------------------------------------------------------------
/// ������� ������ data
template <class Type, class Owner>
void ParameterProperty<Type, Owner>::Clone(BaseProperty<Owner>** data)
{
  *data = new ParameterProperty<Type, Owner>();

  *((ParameterProperty<Type, Owner>*)*data) = *this;
}

// ------------------------------------------------------------------------------------------------
/// ������ ����������� ��������� �������
template <class Type, class Owner>
void ParameterProperty<Type, Owner>::SetSeparator(std::string separator)
{
  mSeparator = separator;
}

// ------------------------------------------------------------------------------------------------
/// ���������� ����������� ��������� �������
template <class Type, class Owner>
std::string ParameterProperty<Type, Owner>::GetSeparator()
{
  return mSeparator;
}

// ------------------------------------------------------------------------------------------------
/// ������ ������ ������� ���������
template <class Type, class Owner>
void ParameterProperty<Type, Owner>::SetSize(int size)
{
  //if (size > 0)
  //  mSize = size;
}

// ------------------------------------------------------------------------------------------------
/// ���������� ������ ������� ���������
template <class Type, class Owner>
int ParameterProperty<Type, Owner>::GetSize()
{
  return mSize;
}

// ------------------------------------------------------------------------------------------------
/// ��� ��������
template <class Type, class Owner>
std::string ParameterProperty<Type, Owner>::GetName()
{
  return mName;
}

// ------------------------------------------------------------------------------------------------
/// ����� �������
template <class Type, class Owner>
std::string ParameterProperty<Type, Owner>::GetHelp()
{
  return mHelp;
}

// ------------------------------------------------------------------------------------------------
/// �������� ��� ��� ��������� ������
template <class Type, class Owner>
std::string ParameterProperty<Type, Owner>::GetLink()
{
  return mLink;
}

// ------------------------------------------------------------------------------------------------
/// ��� ��������
template <class Type, class Owner>
void ParameterProperty<Type, Owner>::SetName(std::string name)
{
  mName = name;
}

// ------------------------------------------------------------------------------------------------
/// ����� �������
template <class Type, class Owner>
void ParameterProperty<Type, Owner>::SetHelp(std::string help)
{
  mHelp = help;
}

// ------------------------------------------------------------------------------------------------
/// �������� ��� ��� ��������� ������
template <class Type, class Owner>
void ParameterProperty<Type, Owner>::SetLink(std::string link)
{
  mLink = link;
}

// ------------------------------------------------------------------------------------------------
/// ���������� ������� �� ��������
template <class Type, class Owner>
std::string ParameterProperty<Type, Owner>::GetHelpString()
{
  std::string result = "";
  result = result + GetName() + " (" + GetLink() + ") - \'" + GetHelp() + "\' default:\t" + ToString();
  return result;
}

// ------------------------------------------------------------------------------------------------
/// ���������� �������� ��������� ���������
template <class Type, class Owner>
std::string ParameterProperty<Type, Owner>::GetCurrentStringValue()
{
  std::string result = "";
  result = result + GetName() + " = " + ToString();
  return result;
}

// ------------------------------------------------------------------------------------------------
/// �������� � ������
template <class Type, class Owner>
std::string ParameterProperty<Type, Owner>::ToString()
{
  return "";
}

// ------------------------------------------------------------------------------------------------
/// ��������� �������� �� ������
template <class Type, class Owner>
void ParameterProperty<Type, Owner>::FromString(std::string val)
{}

// ------------------------------------------------------------------------------------------------
/// ������ ���������� ��� �� �����
template <class Type, class Owner>
std::string ParameterProperty<Type, Owner>::GetFullLink()
{
  return "-" + GetName();
}

// ------------------------------------------------------------------------------------------------
/// ��������� �� ��� ��������� �� ��������� �������
template <class Type, class Owner>
bool ParameterProperty<Type, Owner>::IsNameEqual(std::string name)
{
  if ((name.length() == GetFullLink().length()) || (name.length() == GetLink().length()) || (name.length() == GetName().length()))
  {
    std::string lName = name;
    std::string LGetFullLink = GetFullLink();
    std::string LGetLink = GetLink();
    std::string LGetName = GetName();

    for (int i = 0; i < lName.length(); i++) 
      lName[i] = std::tolower(lName[i]);

    for (int i = 0; i < LGetFullLink.length(); i++)
      LGetFullLink[i] = std::tolower(LGetFullLink[i]);

    for (int i = 0; i < LGetLink.length(); i++)
      LGetLink[i] = std::tolower(LGetLink[i]);

    for (int i = 0; i < LGetName.length(); i++)
      LGetName[i] = std::tolower(LGetName[i]);


    if ((lName == LGetFullLink) || (lName == LGetLink) || (lName == LGetName))
      return true;  
    else
      return false;
  }
  else
    return false;
}

// ------------------------------------------------------------------------------------------------
template <class Type, class Owner>
void ParameterProperty<Type, Owner>::InitializationParameterProperty(Owner * owner,
  tCheckValue checkMethod, int index, std::string separator, int size, std::string name,
  std::string help, std::string link, std::string defValue)
{
  TypedProperty<Type, Owner>::Init(owner, 0, 0, checkMethod);

  this->SetIndex(index);
  SetSeparator(separator);
  SetSize(size);
  SetName(name);
  SetHelp(help);
  SetLink(link);

  FromString(defValue);
  this->mIsChange = false;
}

// ------------------------------------------------------------------------------------------------
template <class Type, class Owner>
void ParameterProperty<Type, Owner>::InitializationParameterProperty(Owner * owner, tGetter getMethod, tSetter setMethod,
  tCheckValue checkMethod, int index, std::string separator, int size, std::string name,
  std::string help, std::string link, std::string defValue)
{
  TypedProperty<Type, Owner>::Init(owner, getMethod, setMethod, checkMethod);

  this->SetIndex(index);
  SetSeparator(separator);
  SetSize(size);
  SetName(name);
  SetHelp(help);
  SetLink(link);

  FromString(defValue);
  this->mIsChange = false;
}

// ------------------------------------------------------------------------------------------------
template <class Type, class Owner>
ParameterProperty<Type, Owner>::ParameterProperty() : mSize(1), TypedProperty<Type, Owner>()
{
  this->mIsEdit = true;

  mSeparator = "_";
  mName = "";
  mHelp = "";
  mLink = "";
}

// ------------------------------------------------------------------------------------------------
template <class Type, class Owner>
ParameterProperty<Type, Owner>::ParameterProperty(Type value) : mSize(1), TypedProperty<Type, Owner>(value)
{
  this->mIsEdit = true;

  mSeparator = "_";
  mName = "";
  mHelp = "";
  mLink = "";
}

// ------------------------------------------------------------------------------------------------
template <class Type, class Owner>
ParameterProperty<Type, Owner>::ParameterProperty(Owner * owner, tGetter getMethod,
  tSetter setMethod, tCheckValue checkMethod, Type value) :
  mSize(1), TypedProperty<Type, Owner>(this->mOwner, this->mGetter, this->mSetter, this->mCheckValue, value)
{
  this->mIsEdit = true;

  mSeparator = "_";
  mName = "";
  mHelp = "";
  mLink = "";
}

#endif //__PARAMETER_PROPERTY_H__
// - end of file ----------------------------------------------------------------------------------
