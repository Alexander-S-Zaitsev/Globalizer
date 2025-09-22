/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2015 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      data.h                                                      //
//                                                                         //
//  Purpose:   Header file for search data classes                         //
//                                                                         //
//  Author(s): Sysoyev A., Barkalov K., Sovrasov V.                        //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#ifndef __TREE_NODE_H__
#define __TREE_NODE_H__

#include "SearchInterval.h"
#include "SearchIntervalFactory.h"

class SearchInterval;
// ------------------------------------------------------------------------------------------------
class TreeNode
{
public:
    /// �������� ������
    SearchInterval* pInterval;

    /// ������ ������
    unsigned char Height;

    /// ����� ����� ������
    TreeNode* pLeft;
    /// ������ ����� ������
    TreeNode* pRight;
    /// ������������ ����
    TreeNode* pParent;

    TreeNode(SearchInterval& p);

    ~TreeNode();
};

#endif
// - end of file ----------------------------------------------------------------------------------
