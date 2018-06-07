//IMPLEMENTING AND MANIPULATING EXPRESSION TREES

#include<iostream>
#include<fstream>
using namespace std;

class ExpTree //class declaration
{
  public:
    //CONSTRUCTOR
    ExpTree() { root = NULL; } //initializing root to null
  
    //DESTRUCTOR
    ~ExpTree();
    
    int value();
    //precondition - an object should be selected
    //postcondition - an integer is returned
  
    void build_tree(istream& in_s);
    //precondition - istream object should be passed
    //postcondition - the tree is built from the contents of the file
  
    void prefix();
    //precondition - a tree object should be selected
    //postcondition - the contents are printed in prefix form to the out stream  
  
    void infix();
    //precondition - a tree object should be selected
    //postcondition - the contents are printed in infix form to the out stream
  
    void postfix();
    //precondition - a tree object should be selected
    //postcondition - the contents are printed in postfix form to the out stream
  
  private:
    struct Node
    {
      char optr; //stores the item name
      int operand; //stores the number
      Node *left; //points to left subtree
      Node *right; //points to right subtree
    };
    Node *root; //the top of the tree
  
    void destroy(Node *p);
    //precondition - a node should be passed
    //postcondition - the tree is emptied recursively
    
    int value(Node *r);
    //precondition - a node should be passed
    //postcondition - an integer is returned
  
    Node* r_build(istream& in_s);
    //precondition - istream object is passed
    //postcondition - a node pointer is returned
  
    void prefix(Node *r, ostream& out_s);
    //precondition - a node pointer and an ostream object are passed
    //postcondition - the expression is printed to the out stream
  
    void infix(Node *r, ostream& out_s);
    //precondition - a node pointer and an ostream object are passed  
    //postcondition - the expression is printed to the out stream
  
    void postfix(Node *r, ostream& out_s);
    //precondition - a node pointer and an ostream object are passed
    //postcondition - the expression is printed to the out stream
};

ExpTree :: ~ExpTree()
{
  destroy(root);
}

void ExpTree :: destroy(Node *p)
{
  if(p!=NULL)
  {
    destroy(p->left);
    destroy(p->right);
    delete p;
  }
}

int ExpTree :: value()
{
  return value(root);
}

int ExpTree :: value(Node *r)
{
  int l_val, r_val;
  if(r->left == NULL)
    return r->operand;
  else
  {
    l_val = value(r->left);
    r_val = value(r->right);
    if(r->optr == '+')
      return l_val + r_val;
    else if(r->optr == '-')
      return l_val - r_val;
    else if(r->optr == '*')
      return l_val * r_val;
    else //r->optr == '/'
      return l_val / r_val;
  }
}

void ExpTree :: build_tree(istream& in_s)
{
  destroy(root);
  root = r_build(in_s);
}

ExpTree :: Node* ExpTree :: r_build(istream& in_s)
{
  char ch;
  Node *temp;
  in_s >> ch;
  if(isdigit(ch))
  {
    temp = new Node;
    temp->operand = ch - '0';
    temp->left = NULL;
    temp->right = NULL;
    return temp;
  }
  else if(ch == '(')
  {
    temp = new Node;
    temp->left = r_build(in_s);
    in_s >> temp->optr;
    temp->right = r_build(in_s);
    in_s >> ch; // ')'
    return temp;
  }
  else
  {
    in_s >> ch;
    temp = r_build(in_s);
  }
  in_s >> ch; //a check for end of the line
}


void ExpTree :: prefix()
{
  prefix(root, cout);
}

void ExpTree :: infix()
{
  infix(root, cout);
}

void ExpTree :: postfix()
{
  postfix(root, cout);
}

void ExpTree :: prefix(Node *r, ostream& out_s)
{
  if(r->left == NULL)
    out_s << r->operand << ' ';
  else
  {
    out_s << r->optr << ' ';
    prefix(r->left, out_s);
    prefix(r->right, out_s);
  }
}

void ExpTree :: infix(Node *r, ostream& out_s)
{
  if(r->left == NULL)
    cout << r->operand << ' ';
  else
  {
    cout << "( ";
    infix(r->left, out_s);
    cout << r->optr << ' ';
    infix(r->right, out_s);
    cout << ") ";
  }
}
void ExpTree :: postfix(Node *r, ostream& out_s)
{
  if(r->left == NULL)
    cout << r->operand << ' ';
  else
  {
    postfix(r->left, out_s);
    postfix(r->right, out_s);
    cout << r->optr << ' ';
  }
}

int main()
{
  ExpTree exp;
  string fname;
  cout << "Enter file name: ";
  cin >> fname;
  ifstream in_s;
  in_s.open(fname.c_str());
  while(!in_s.eof())
  {
    exp.build_tree(in_s);
    cout << "\nPreorder:  ";
    exp.prefix();
    cout << "\nInorder:   ";
    exp.infix();
    cout << "\nPostorder: ";
    exp.postfix();
    cout << "\nValue: " << exp.value() << endl;
  }
  in_s.close();
}
