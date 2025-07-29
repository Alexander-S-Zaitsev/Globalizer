#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// ------------------------------------------------------------------------------------------------
/**
������� �����, ��������� ����� �� �������

*/
class OutputHelper { };

// ------------------------------------------------------------------------------------------------
/**
������� �����, ��������� ����� �� ������� ������� ������� ������

����� ���������� ������ ���� ���������� ��������� GLOBALIZER_OUTPUT_L1 ��� GLOBALIZER_OUTPUT_L2
*/
class OutputLevel1Helper { };

// ------------------------------------------------------------------------------------------------
/**
������� �����, ��������� ����� �� ������� ������� ������� ������

����� ���������� ������ ���� ���������� ��������� GLOBALIZER_OUTPUT_L2
*/
class OutputLevel2Helper { };

// ------------------------------------------------------------------------------------------------
/**
������� �����, ��������� ����� �� ������� ���������� ����������

����� ���������� ������ � debug ������ (�.�. ���� ���������� ��������� _DEBUG)
*/
class OutputDebugHelper { };

// ------------------------------------------------------------------------------------------------
class LogDebugHelper;

// ------------------------------------------------------------------------------------------------
/**
�������� �����, ��������� ����� � ����
������ ������ � debug ������������
*/
class Logger
{
protected:
  /// ����� ������ � ����
  std::fstream mLogOutputStream;
  /// ��� ��� �����
  static std::string mLogFileName;
  /// ���� �� ������������������� �������
  static bool mIsInitialized;

  ~Logger() {}
  Logger();
  Logger(const Logger&) {}
  Logger& operator=(const Logger&) {return *this;}

  template<typename T>
  friend inline LogDebugHelper& operator<<(LogDebugHelper& incomingHelper, const T& value);
public:
  /// ������� ������ ������ � ����
  void flush();
  /**
  ������������� ������, ���������� ������� ����� �������, ��������� ��� ��� �����
  \param[in] logFileName - ��� ����� � ������� ����� ������������� ������
  \param[in] isFlush - ������� �� ����
  */
  static void init(const std::string& logFileName);
  /// ���������� ��������� �������
  static Logger& instance();
};

// ------------------------------------------------------------------------------------------------
/**
������� �����, ��������� ����� � ���� ���������� ����������

����� ���������� ������ � debug ������ (�.�. ���� ���������� ��������� _DEBUG)
*/
class LogDebugHelper
{
  public:
    void flush()
    {
      Logger::instance().flush();
    }
};

// ------------------------------------------------------------------------------------------------
/// ���������� ���������� ��� ������ ���������� ���������� (������ cout)
extern OutputDebugHelper print_dbg;
/// ���������� ���������� ��� ������ �� ������� (������ cout)
extern OutputHelper print;
/// ���������� ���������� ��� ����� ���������� ���������� ������� � ������� ������
extern OutputLevel1Helper print_l1;
/// ���������� ���������� ��� ����� ���������� ���������� ������� ������
extern OutputLevel2Helper print_l2;
/// ���������� ���������� ��� ������ ���������� ���������� � ���
extern LogDebugHelper print_dbg_file;

// ------------------------------------------------------------------------------------------------
template<typename T> inline
OutputHelper& operator<<(OutputHelper& incomingHelper, const T& value)
{
  std::cout << value;
  return incomingHelper;
}

// ------------------------------------------------------------------------------------------------
template<typename T> inline
OutputLevel1Helper& operator<<(OutputLevel1Helper& incomingHelper, const T& value)
{
#if defined(GLOBALIZER_OUTPUT_L1) || defined(GLOBALIZER_OUTPUT_L2)
  std::cout << value;
#endif
  return incomingHelper;
}

// ------------------------------------------------------------------------------------------------
template<typename T> inline
OutputLevel2Helper& operator<<(OutputLevel2Helper& incomingHelper, const T& value)
{
#ifdef GLOBALIZER_OUTPUT_L2
  std::cout << value;
#endif
  return incomingHelper;
}

// ------------------------------------------------------------------------------------------------
template<typename T> inline
OutputDebugHelper& operator<<(OutputDebugHelper& incomingHelper, const T& value)
{
#ifdef _DEBUG
  std::cout << value;
#endif
  return incomingHelper;
}

// ------------------------------------------------------------------------------------------------
template<typename T> inline
LogDebugHelper& operator<<(LogDebugHelper& incomingHelper, const T& value)
{
#ifdef _DEBUG
  Logger::instance().mLogOutputStream << value;
#endif
  return incomingHelper;
}

// ------------------------------------------------------------------------------------------------
template<typename T>
std::string toString (T value)
{
  std::ostringstream oss;
  oss << value;
  return oss.str();
}
