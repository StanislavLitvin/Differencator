#ifndef DIFFERENCATOR_H
#define DIFFERENCATOR_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define _NUM(Value) Creat_Node(NUM, Value, NULL, NULL, NULL)
#define _VAR(Variable) Creat_Node(VAR, Variable, NULL, NULL, NULL)
#define _OP(Operation) Creat_Node(OP, Operation, NULL, NULL, NULL)
#define _DL(Node) Diff(Node->Left)
#define _DR(Node) Diff(Node->Right)
#define _CL(Node) Copy_Subtree(Node->Left)
#define _CR(Node) Copy_Subtree(Node->Right)
#define _ADD(Node1, Node2) Creat_Node(OP, ADD, NULL, NULL, NULL)
#define _SUB(Node1, Node2) Creat_Node(OP, SUB, NULL, NULL, NULL)
#define _MUL(Node1, Node2) Creat_Node(OP, MUL, NULL, NULL, NULL)
#define _DIV(Node1, Node2) Creat_Node(OP, DIV, NULL, NULL, NULL)

const double ACCURACY_CONSTANT = 1e-5;

enum Type_Of_Node
{
  OP  = 0,
  VAR = 1,
  NUM = 2
};

enum Type_Of_Operation
{
  ADD = 0,
  SUB = 1,
  MUL = 2,
  DIV = 3
};

enum Variables
{
  X = 0,
  Y = 1,
  Z = 2
};

struct Node_Of_Diff_Tree
{
  Type_Of_Node Type;
  double Val;
  Node_Of_Diff_Tree* Left;
  Node_Of_Diff_Tree* Right;
  Node_Of_Diff_Tree* Parent;
};
//----------------------------------------------------------------------------------------------
Node_Of_Diff_Tree* Creat_Node(Type_Of_Operation Type, double Val, Node_Of_Diff_Tree* Left,
                              Node_Of_Diff_Tree* Right, Node_Of_Diff_Tree* Parent);
void Delete_Node(Node_Of_Diff_Tree* Node);
void Delete_Tree(Node_Of_Diff_Tree* Node);
bool Have_Node_Left(Node_Of_Diff_Tree* Node);
bool Have_Node_Right(Node_Of_Diff_Tree* Node);
bool Have_Node_Parent(Node_Of_Diff_Tree* Node);
void Link_Node(Node_Of_Diff_Tree* Parent, Node_Of_Diff_Tree* Left, Node_Of_Diff_Tree* Right);
void Set_Left_Link(Node_Of_Diff_Tree* Parent, Node_Of_Diff_Tree* Left);
void Set_Right_Link(Node_Of_Diff_Tree* Parent, Node_Of_Diff_Tree* Right);
//----------------------------------------------------------------------------------------------
void Tex_View_Tree(Node_Of_Diff_Tree* Node, FILE* Tex_File);
void Tex_View_Nodes(Node_Of_Diff_Tree* Node, FILE* Tex_File);
//----------------------------------------------------------------------------------------------
void Dump_Tree(Node_Of_Diff_Tree* Root, FILE* Viz_File);
void Dump_Tree_Nodes(Node_Of_Diff_Tree* Node, FILE* Viz_File);
void Dump_Op_Node(Node_Of_Diff_Tree* Node, FILE* Viz_File);
void Dump_Var_Node(Node_Of_Diff_Tree* Node, FILE* Viz_File);
void Dump_Num_Node(Node_Of_Diff_Tree* Node, FILE* Viz_File);
void Dump_Tree_Arrows(Node_Of_Diff_Tree* Node, FILE* Viz_File);
//----------------------------------------------------------------------------------------------
double Calculate_Node(Node_Of_Diff_Tree* Node, double Var_Value);
double Calculate(Node_Of_Diff_Tree* Node, double Value1, double Value2);
Node_Of_Diff_Tree* Copy_Subtree(Node_Of_Diff_Tree* Node);
Node_Of_Diff_Tree* Copy_Node(Node_Of_Diff_Tree* Node);
//----------------------------------------------------------------------------------------------
Node_Of_Diff_Tree* Diff(Node_Of_Diff_Tree* Node);

#endif