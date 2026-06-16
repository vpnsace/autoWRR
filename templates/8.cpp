/*AIM- To implement Huffman Encoding using a Greedy Algorithm with Binary Tree and Min-Heap (Priority Queue) to
generate optimal variable-length prefix codes.*/
//{NAME}

#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct Node
{
 char data; int freq;
 Node *left, *right;
 Node(char data, int freq)
 { this->data=data; this->freq=freq; left=right=NULL; }
};
struct compare
{
 bool operator()(Node* l, Node* r){ return l->freq > r->freq; }
};
void printCodes(Node* root, string code)
{
 if(root==NULL) return;
 if(root->left==NULL && root->right==NULL)
 cout << root->data << " : " << code << endl;
 printCodes(root->left, code+"0");
 printCodes(root->right, code+"1");
}
void huffmanCoding(char data[], int freq[], int n)
{
 priority_queue<Node*,vector<Node*>,compare> pq;
 for(int i=0;i<n;i++) pq.push(new Node(data[i],freq[i]));
 while(pq.size()>1)
 {
 Node *left=pq.top(); pq.pop();
 Node *right=pq.top(); pq.pop();
 Node *newNode=new Node('$',left->freq+right->freq);
 newNode->left=left; newNode->right=right;
 pq.push(newNode);
 }
 Node *root=pq.top();
 cout << "Huffman Codes:\n";
 printCodes(root,"");
}
int main()
{
 int n; cout << "Enter number of characters: "; cin >> n;
 char data[n]; int freq[n];
 cout << "Enter characters:\n";
 for(int i=0;i<n;i++) cin >> data[i];
 cout << "Enter frequencies:\n";
 for(int i=0;i<n;i++) cin >> freq[i];
 huffmanCoding(data,freq,n); return 0;
}