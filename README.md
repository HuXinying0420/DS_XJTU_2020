# DataStructure_XJTU_2020
数据结构课程实验
## 实验一 表达式求值
* 实验要求
  * 基本要求：实现栈的基本操作，及表达式求值的实现。
* 实现要求
  * 实现栈的 push、pop 基本操作；
  * 检测表达式的输入是否是正确的数学表达式；
  * 对于正确的数学表达式求取其值。
* 注
  * 数学表达式的判读与求值需支持加减乘除、小括号、中括号、大括号、幂运算。
  * 不正确的表达式可能包括：字母、非运算符号、括号不匹配，运算符的排列不符合表达式形式、分母为0等多种情况。
  * 表达式通过在命令行参数输入输出获取。
  * 输出要求：
    * 表达式正确的情况下输出结果；
    * 命令行参数不正确输出ERROR_01；
    * 表达式存在格式错误输出ERROR_02；
    * 表达式在计算过程中出现逻辑错误输出ERROR_03。

## 实验二 基于串的模式匹配
* 实验要求
  * 使用串及其模式匹配算法。
  * 用KMP算法实现模式匹配。
* 注：
  * 中文字符在字符串中占2位。
  * 输出要求：
    * 关键字在字符中的位置，如果不存在则输出-1；
    * 命令行参数不正确输出ERROR_01。

## 实验三 基于赫夫曼树的编码/译码
* 实验要求
  * 通过键盘输入一段字符(长度>=20)，构建霍夫曼树；
  * 根据该树求每个字符的编码，并对该段字符串进行编码；
  * 将得到的编码进行译码；
  * 基于该霍夫曼树，实现非递归的先序遍历算法，输出该树所有的节点、节点的权值、节点的度和节点所在的层数；
* 注：
  * 在实现时要求霍夫曼树的左右孩子的大小关系满足，左孩子节点权值小于右孩子节点权值。
  * 输出要求：
    * 命令行参数不正确输出ERROR_01；
    * 编码失败输出ERROR_02；
    * 译码失败输出ERROR_03。
## 实验四 无向图最短路径搜索
* 实验要求
  * 熟练掌握图的操作。
* 注：
  * 命令行参数不正确输出ERROR_01；
  * 获取最短路径失败时输出ERROR_02；
  * 获取最短路径成功时输出最短路径以及路径长度。
---
代码详解见report.pdf

测试工具：AutoScore.exe

---
本文首发于 GitHub HuXinying0420的仓库，原地址：https://github.com/HuXinying0420/DS_XJTU_2020
 
转载请注明：
 
1. 出处：本文首发于 GitHub HuXinying0420 的仓库
2. 原文地址：https://github.com/HuXinying0420/DS_XJTU_2020
 
This article was originally published on GitHub by HuXinying0420 in the repository ME233_TBSI_2024 at the following address: https://github.com/HuXinying0420/DS_XJTU_2020

Please note the following when reprinting this content:

1. Source: This article was originally published on GitHub by HuXinying0420.
2. Original URL: https://github.com/HuXinying0420/DS_XJTU_2020
