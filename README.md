# DataStructure_XJTU_2020

This repository contains implementations for four experiments as part of the "Data structure and program design" subject experiment course. The experiments and their specific requirements are detailed below:

## Experiment 1: Expression Evaluation
* **Requirements:**
  * Basic requirement: Implement basic stack operations and expression evaluation.
* **Implementation requirements:**
  * Implement basic stack operations like push and pop.
  * Check if the input expression is a valid mathematical expression.
  * Evaluate the value of the correct mathematical expression.
* **Notes:**
  * The evaluation of mathematical expressions should support addition, subtraction, multiplication, division, parentheses, brackets, braces, and exponentiation.
  * Incorrect expressions may include letters, non-operator symbols, mismatched parentheses, incorrectly arranged operators, and division by zero among others.
  * Expressions are input and output through command line parameters.
  * Output requirements:
    * Output the result if the expression is correct.
    * Output ERROR_01 if command line parameters are incorrect.
    * Output ERROR_02 for format errors in expressions.
    * Output ERROR_03 for logical errors during computation.

## Experiment 2: Pattern Matching Based on Strings
* **Requirements:**
  * Use strings and pattern matching algorithms.
  * Implement pattern matching using the KMP algorithm.
* **Notes:**
  * Chinese characters occupy 2 positions in a string.
  * Output requirements:
    * Output the position of the keyword in the characters. If it does not exist, output -1.
    * Output ERROR_01 for incorrect command line parameters.

## Experiment 3: Encoding/Decoding Based on Huffman Tree
* **Requirements:**
  * Input a string (length >= 20) from the keyboard to construct a Huffman tree.
  * Obtain the encoding of each character based on the tree, and encode the string.
  * Decode the obtained encoding.
  * Implement a non-recursive preorder traversal algorithm based on the Huffman tree to output all nodes of the tree, node weights, node degrees, and node levels.
* **Notes:**
  * The sizes of left and right children of nodes in the Huffman tree should satisfy the condition that the weight of the left child is less than the weight of the right child.
  * Output requirements:
    * Output ERROR_01 for incorrect command line parameters.
    * Output ERROR_02 for encoding failures.
    * Output ERROR_03 for decoding failures.

## Experiment 4: Shortest Path Search in an Undirected Graph
* **Requirements:**
  * Proficient in graph operations.
* **Notes:**
  * Output requirements:
    * Output ERROR_01 for incorrect command line parameters.
    * Output ERROR_02 for failure to obtain the shortest path.
    * Output the shortest path and its length on successful retrieval.

---
Code explanations can be found in report.pdf

Testing tool: AutoScore.exe

---
<!-- 
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
 -->
 
This article was originally published on GitHub by HuXinying0420 in the repository DS_XJTU_2020 at the following address: https://github.com/HuXinying0420/DS_XJTU_2020

Please note the following when reprinting this content:

1. Source: This article was originally published on GitHub by HuXinying0420.
2. Original URL: https://github.com/HuXinying0420/DS_XJTU_2020
