#include "Differencator.h"

Node_Of_Diff_Tree* Creat_Node(Type_Of_Node Type, double Val, Node_Of_Diff_Tree* Left,
                              Node_Of_Diff_Tree* Right, Node_Of_Diff_Tree* Parent)
{
  Node_Of_Diff_Tree* New_Node = (Node_Of_Diff_Tree*)calloc(1, sizeof(Node_Of_Diff_Tree));
  assert(New_Node);

  New_Node->Type = Type;
  New_Node->Val = Val;
  New_Node->Left = Left;
  New_Node->Right = Right;
  New_Node->Parent = Parent;

  return New_Node;
}

void Delete_Node(Node_Of_Diff_Tree* Node)
{
  assert(Node);

  free(Node);

  return;
}

void Delete_Tree(Node_Of_Diff_Tree* Node)
{
  assert(Node);

  if (Have_Node_Left(Node))
    Delete_Tree(Node->Left);
  if (Have_Node_Right(Node))
    Delete_Tree(Node->Right);

  Delete_Node(Node);

  return;
}

bool Have_Node_Left(Node_Of_Diff_Tree* Node)
{
  if (Node->Left != NULL)
    return true;
  else
    return false;
}

bool Have_Node_Right(Node_Of_Diff_Tree* Node)
{
  if (Node->Right != NULL)
    return true;
  else
    return false;
}

bool Have_Node_Parent(Node_Of_Diff_Tree* Node)
{
  if (Node->Parent != NULL)
    return true;
  else
    return false;
}

void Link_Node(Node_Of_Diff_Tree* Parent, Node_Of_Diff_Tree* Left, Node_Of_Diff_Tree* Right)
{
  assert(Parent);

  if (Left != NULL)
    Set_Left_Link(Parent, Left);
  if (Right != NULL)
    Set_Right_Link(Parent, Right);

  return;
}

void Set_Left_Link(Node_Of_Diff_Tree* Parent, Node_Of_Diff_Tree* Left)
{
  assert(Parent);
  assert(Left);

  Parent->Left = Left;
  Left->Parent = Parent;

  return;
}

void Set_Right_Link(Node_Of_Diff_Tree* Parent, Node_Of_Diff_Tree* Right)
{
  assert(Parent);
  assert(Right);

  Parent->Right = Right;
  Right->Parent = Parent;

  return;
}

//----------------------------------------------------------------------------------------------

void Tex_View_Tree(Node_Of_Diff_Tree* Node, FILE* Tex_File)
{
  assert(Node);
  assert(Tex_File);

  fprintf(Tex_File, "\\documentclass{article}\n"
                    "\\begin{document}\n\n");
  fprintf(Tex_File, "$");
  Tex_View_Nodes(Node, Tex_File);
  fprintf(Tex_File, "$\n\n");
  fprintf(Tex_File, "\\end{document}");

  return;
}

void Tex_View_Nodes(Node_Of_Diff_Tree* Node, FILE* Tex_File)
{
  assert(Node);
  assert(Tex_File);

  if (Node->Type == NUM)
  {
    fprintf(Tex_File, "%lg", Node->Val);
    return;
  }
  if (Node->Type == VAR)
    switch((Variables)Node->Val)
    {
      case X:
          fprintf(Tex_File, "x");
          return;
      case Y:
          fprintf(Tex_File, "y");
          return;
      case Z:
          fprintf(Tex_File, "z");
          return;
      default:
          fprintf(Tex_File, "Invalid variable\n");
          return;
    }
  if (Node->Type == OP)
    switch((Type_Of_Operation)Node->Val)
    {
      case ADD:
          fprintf(Tex_File, "(");
          Tex_View_Nodes(Node->Left, Tex_File);
          fprintf(Tex_File, "+");
          Tex_View_Nodes(Node->Right, Tex_File);
          fprintf(Tex_File, ")");
          return;

      case SUB:
          fprintf(Tex_File, "(");
          Tex_View_Nodes(Node->Left, Tex_File);
          fprintf(Tex_File, "-");
          Tex_View_Nodes(Node->Right, Tex_File);
          fprintf(Tex_File, ")");
          return;

      case MUL:
          Tex_View_Nodes(Node->Left, Tex_File);
          fprintf(Tex_File, "\\cdot");
          Tex_View_Nodes(Node->Right, Tex_File);
          return;

      case DIV:
          fprintf(Tex_File, "\\frac{");
          Tex_View_Nodes(Node->Left, Tex_File);
          fprintf(Tex_File, "}{");
          Tex_View_Nodes(Node->Right, Tex_File);
          fprintf(Tex_File, "}");
          return;

      default:
          fprintf(Tex_File, "Invalid operation\n");
          return;
    }
  
  fprintf(Tex_File, "Invalid type of node\n");
  return;
}

//----------------------------------------------------------------------------------------------

void Dump_Tree(Node_Of_Diff_Tree* Root, FILE* Viz_File)
{
  assert(Root);
  assert(Viz_File);

  fprintf(Viz_File, "digraph Tree_Dump_Graphviz\n"
                    "{\n"
                    "\trankdir=TB;\n"
                    "\tnode [fontcolor=\"#220808\"];\n"
                    "\tbgcolor=\"#EADF9D\";\n"
                    "\tmargin=0.2;\n"
                    "\tpad=0.2;\n\n");

  Dump_Tree_Nodes(Root, Viz_File);
  Dump_Tree_Arrows(Root, Viz_File);

  fprintf(Viz_File, "}");

  return;
}

void Dump_Tree_Nodes(Node_Of_Diff_Tree* Node, FILE* Viz_File)
{
  assert(Node);
  assert(Viz_File);

  switch(Node->Type)
  {
    case OP:
        Dump_Op_Node(Node, Viz_File);
        break;
    case VAR:
        Dump_Var_Node(Node, Viz_File);
        break;
    case NUM:
        Dump_Num_Node(Node, Viz_File);
        break;
    default:
        printf("ERROR: Invalid type of node\n");
        break;
  }

  if (Have_Node_Left(Node))
    Dump_Tree_Nodes(Node->Left, Viz_File);
  if (Have_Node_Right(Node))
    Dump_Tree_Nodes(Node->Right, Viz_File);

  if (Have_Node_Left(Node) && Have_Node_Right(Node))
    fprintf(Viz_File, "\t{rank=same; node%p; node%p};\n", (void*)Node->Left, (void*)Node->Right);

  return;
}

void Dump_Op_Node(Node_Of_Diff_Tree* Node, FILE* Viz_File)
{
  assert(Node);
  assert(Viz_File);
  assert(Node->Type == OP);

  const int Max_Op_Name = 10;
  char Op_Name[Max_Op_Name] = "";

  switch((Type_Of_Operation)Node->Val)
  {
    case ADD:
        strcpy(Op_Name, "+");
        break;
    case SUB:
        strcpy(Op_Name, "-");
        break;
    case MUL:
        strcpy(Op_Name, "*");
        break;
    case DIV:
        strcpy(Op_Name, "/");
        break;
    default:
        printf("ERROR: Invalid type of operation\n");
        break;
  }

  fprintf(Viz_File, "\tnode%p[shape=Mrecord, label=\"%s\", style = \"filled\", "
                    "fillcolor = \"#3EB8D7\"];\n", (void*)Node, Op_Name);

  return;
}

void Dump_Var_Node(Node_Of_Diff_Tree* Node, FILE* Viz_File)
{
  assert(Node);
  assert(Viz_File);
  assert(Node->Type == VAR);

  const int Max_Var_Name = 5;
  char Var_Name[Max_Var_Name] = "";

  switch((Variables)Node->Val)
  {
    case X:
        strcpy(Var_Name, "x");
        break;
    case Y:
        strcpy(Var_Name, "y");
        break;
    case Z:
        strcpy(Var_Name, "z");
        break;
    default:
        printf("ERROR: Invalid type of variable\n");
        break;
  }

  fprintf(Viz_File, "\tnode%p[shape=square, label=\"%s\", style = \"filled\", "
                    "fillcolor = \"#CE86F8\"];\n", (void*)Node, Var_Name);

  return;
}

void Dump_Num_Node(Node_Of_Diff_Tree* Node, FILE* Viz_File)
{
  assert(Node);
  assert(Viz_File);
  assert(Node->Type == NUM);

  fprintf(Viz_File, "\tnode%p[shape=circle, label=\"%lg\", style = \"filled\", "
                    "fillcolor = \"#93C996\"];\n", (void*)Node, Node->Val);

  return;
}

void Dump_Tree_Arrows(Node_Of_Diff_Tree* Node, FILE* Viz_File)
{
  assert(Node);
  assert(Viz_File);

  if (Have_Node_Left(Node))
  {
    fprintf(Viz_File, "\tnode%p->node%p;\n", (void*)Node, (void*)Node->Left);
    Dump_Tree_Arrows(Node->Left, Viz_File);
  }
  if (Have_Node_Right(Node))
  {
    fprintf(Viz_File, "\tnode%p->node%p;\n", (void*)Node, (void*)Node->Right);
    Dump_Tree_Arrows(Node->Right, Viz_File);
  }

  return;
}

//----------------------------------------------------------------------------------------------

double Calculate_Node(Node_Of_Diff_Tree* Node, double Var_Value)
{
  assert(Node);

  if (Node->Type == NUM)
    return Node->Val;
  if (Node->Type == VAR)
    return Var_Value;
  if (Node->Type == OP)
  {
    double Left_Part = NAN;
    double Right_Part = NAN;
    if (Have_Node_Left(Node))
      Left_Part = Calculate_Node(Node->Left, Var_Value);
    if (Have_Node_Right(Node))
      Right_Part = Calculate_Node(Node->Right, Var_Value);

    return Calculate(Node, Left_Part, Right_Part);
  }

  return NAN;
}

double Calculate(Node_Of_Diff_Tree* Node, double Value1, double Value2)
{
  assert(Node);
  assert(Node->Type == OP);

  if (isnan(Value1) || isnan(Value2))
  {
    printf("ERROR: operand has too few arguments\n");
    assert(0);
  }

  switch((Type_Of_Operation)Node->Val)
  {
    case ADD:
        return Value1 + Value2;
    case SUB:
        return Value1 - Value2;
    case MUL:
        return Value1 * Value2;
    case DIV:
        if (Value2 < ACCURACY_CONSTANT)
        {
          printf("ERROR: attempt to divide by zero\n");
          assert(0);
        }
        return Value1 / Value2;
    default:
        printf("ERROR: Invalid type of operation\n");
        return NAN;
  }
}

Node_Of_Diff_Tree* Copy_Subtree(Node_Of_Diff_Tree* Node)
{
  assert(Node);

  Node_Of_Diff_Tree* Node_Left = NULL;
  Node_Of_Diff_Tree* Node_Right = NULL;

  if (Have_Node_Left(Node))
    Node_Left = Copy_Subtree(Node->Left);
  if (Have_Node_Right(Node))
    Node_Right = Copy_Subtree(Node->Right);

  Node_Of_Diff_Tree* New_Node = Copy_Node(Node);
  if (Node_Left != NULL || Node_Right != NULL)
    Link_Node(New_Node, Node_Left, Node_Right);

  return New_Node;
}

Node_Of_Diff_Tree* Copy_Node(Node_Of_Diff_Tree* Node)
{
  assert(Node);

  Node_Of_Diff_Tree* Copy_Node = Creat_Node(Node->Type, Node->Val, Node->Left,
                                                        Node->Right, Node->Parent);

  return Copy_Node;
}

//----------------------------------------------------------------------------------------------

Node_Of_Diff_Tree* Diff(Node_Of_Diff_Tree* Node)
{
  assert(Node);

  switch(Node->Type)
  {
    case NUM:
        return _NUM(0);
    case VAR:
        return _NUM(1);
    case OP:
        switch((Type_Of_Operation)Node->Val)
        {
          case ADD:
              return _ADD(_DL, _DR);
          case SUB:
              return _SUB(_DL, _DR);
          case MUL:
              return _ADD(_MUL(_DL, _CR), _MUL(_CL, _DR));
          case DIV:
              return _DIV(_SUB(_MUL(_DL, _CR), _MUL(_CL, _DR)), _MUL(_CR, _CR));
          default:
              printf("ERROR: Invalid operation\n");
              return NULL;
        }
    default:
        printf("ERROR: Invalid type of node\n");
        return NULL;
  }
}