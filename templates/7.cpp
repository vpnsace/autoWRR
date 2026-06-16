/* AIM- To find the minimum cost of merging n sorted files using a Binary Tree structure and Linked List for maintaining
the sorted order of file sizes.*/
//{NAME}

#include<iostream>
using namespace std;
int n, sum = 0;
struct tnode { tnode *l, *r; int length; };
struct list { tnode *root; list *next; };
list *start=NULL, *End=NULL, *m, *tmp;
tnode* Least(tnode* temp)
{
 if(start==End){ tnode *t=temp; start=End=NULL; return t; }
 tnode *t=temp; start=start->next; return t;
}
void insertfirst(){ m->next=start; start=m; }
void insertlast(){ End->next=m; End=m; }
void insertpos()
{
 list *t2, *t1=start;
 while(t1->root->length < m->root->length){ t2=t1; t1=t1->next; }
 m->next=t1; t2->next=m;
}
void getnode()
{
 m=new list; m->root=new tnode;
 cout << "\nEnter length: "; cin >> m->root->length;
 m->root->l=m->root->r=m->next=NULL;
}
void insert()
{
 if(start==NULL){ start=End=m; }
 else if(m->root->length <= start->root->length) insertfirst();
 else if(m->root->length >= End->root->length) insertlast();
 else insertpos();
}
int main()
{
 cout << "No. of files: "; cin >> n;
 for(int i=0;i<n;i++){ getnode(); insert(); }
 for(int i=0;i<n-1;i++)
 {
 list *newm=new list; newm->next=NULL;
 newm->root=new tnode;
 newm->root->l=Least(start->root);
 newm->root->r=Least(start->root);
 newm->root->length=newm->root->l->length+newm->root->r->length;
 sum+=newm->root->length; m=newm; insert();
 }
 cout << "\nOptimal Merge Cost = " << sum;
}
