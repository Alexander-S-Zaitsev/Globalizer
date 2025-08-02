#ifndef __SOLUTION_RESULT_H__
#define __SOLUTION_RESULT_H__

#include "Common.h"
#include "SearchData.h"
/**
���������� ������ �������
*/
struct SolutionResult
{
  /// ������ ��������, ���������� ��� ������ ������� ������
  Trial* BestTrial;
  /// ����� ����������� ��������
  int IterationCount;
  /// ���������� ���������
  int TrialCount;
};

#endif
