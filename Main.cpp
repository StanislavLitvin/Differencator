#include "Differencator.h"
#include "Differencator.cpp"

/*int main()
{
  Node_Of_Diff_Tree* Node1 = Creat_Node(OP, DIV, NULL, NULL, NULL);
  Node_Of_Diff_Tree* Node2 = Creat_Node(OP, ADD, NULL, NULL, NULL);
  Node_Of_Diff_Tree* Node3 = Creat_Node(OP, SUB, NULL, NULL, NULL);
  Node_Of_Diff_Tree* Node4 = Creat_Node(NUM, 2, NULL, NULL, NULL);
  Node_Of_Diff_Tree* Node5 = Creat_Node(VAR, X, NULL, NULL, NULL);
  Node_Of_Diff_Tree* Node6 = Creat_Node(NUM, 5, NULL, NULL, NULL);
  Node_Of_Diff_Tree* Node7 = Creat_Node(VAR, Y, NULL, NULL, NULL);

  Link_Node(Node1, Node2, Node3);
  Link_Node(Node2, Node4, Node5);
  Link_Node(Node3, Node6, Node7);

  Node_Of_Diff_Tree* Diff_Node = Diff(Node1);

  FILE* Tex_File = fopen("Tex_File.tex", "w");
  assert(Tex_File);

  Tex_View_Tree(Node1, Tex_File);

  fclose(Tex_File);

  FILE* Viz_File = fopen("Viz_File.txt", "w");
  assert(Viz_File);

  //Dump_Tree(Node1, Viz_File);
  Dump_Tree(Diff_Node, Viz_File);

  fclose(Viz_File);

  Delete_Tree(Node1);
  Delete_Tree(Diff_Node);

  return 0;
}*/

int main()
{
  Node_Of_Diff_Tree* Node1 = Creat_Node(OP, ADD, NULL, NULL, NULL);
  Node_Of_Diff_Tree* Node2 = Creat_Node(NUM, 2, NULL, NULL, NULL);
  Node_Of_Diff_Tree* Node3 = Creat_Node(VAR, X, NULL, NULL, NULL);

  Link_Node(Node1, Node2, Node3);

  Node_Of_Diff_Tree* Diff_Node = Diff(Node1);

  FILE* Tex_File = fopen("Tex_File.tex", "w");
  assert(Tex_File);

  Tex_View_Tree(Node1, Tex_File);

  fclose(Tex_File);

  FILE* Viz_File = fopen("Viz_File.txt", "w");
  assert(Viz_File);

  //Dump_Tree(Node1, Viz_File);
  Dump_Tree(Diff_Node, Viz_File);

  fclose(Viz_File);

  Delete_Tree(Node1);
  Delete_Tree(Diff_Node);

  return 0;
}