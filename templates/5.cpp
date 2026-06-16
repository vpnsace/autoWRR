/*AIM- To find the minimum cost of merging n sorted files into a single sorted file using Greedy Strategy with sorted
arrays.*/
//{NAME}

#include<bits/stdc++.h>
using namespace std;
void Shifting(int files[], int &n)
{
 for(int i=1; i<=n-2; i++) files[i] = files[i+1];
 n--;
}
void display(int files[], int n)
{
 for(int i=0; i<=n-1; i++) cout << files[i] << "\t";
}
int OMP(int files[], int n)
{
 sort(files, files+n);
 cout << "\nFile sequence after sorting: "; display(files,n); cout << endl;
 int Cost = 0;
 while(n > 1)
 {
 int mergefileSize = files[0] + files[1];
 Cost += mergefileSize;
 cout << "Cost of merging " << files[0] << " and " << files[1]
 << " is " << mergefileSize << endl;
 cout << "Total Cost at this point: " << Cost << endl;
 files[0] = mergefileSize; Shifting(files, n);
 sort(files, files+n);
 cout << "\nFile sequence after merging: "; display(files,n); cout << endl;
 }
 return Cost;
}
int main()
{
 int n; cout << "Number of files: "; cin >> n;
 int files[n];
 cout << "\nEnter file sizes: ";
 for(int i=0;i<=n-1;i++) cin >> files[i];
 cout << "Minimum cost of merge: " << OMP(files, n);
}