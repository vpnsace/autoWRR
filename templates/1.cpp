/*AIM- To implement Fractional Knapsack problem using Greedy Strategy to maximize total profit by selecting items (or
fractions) based on profit-to-weight ratio.*/
//{NAME}

#include<bits/stdc++.h>
using namespace std;
struct item { double p, w, pDivw; };
bool cmp(item x, item y) { return x.pDivw > y.pDivw; }
double knapsack(item a[], int n, double m)
{
 double x[n] = {0.0}; double profit = 0; int i;
 for(i = 0; i <= n-1; i++)
 {
 if(a[i].w > m) break;
 x[i] = 1.0; m = m - a[i].w; profit = profit + a[i].p;
 }
 if(m != 0) { x[i] = m / a[i].w; profit = profit + a[i].p * x[i]; }
 return profit;
}
int main()
{
 int n; cout << "Enter no. of items"; cin >> n;
 item a[n]; double m;
 cout << "\nEnter knapsack capacity"; cin >> m;
 for(int i = 0; i <= n-1; i++)
 {
 cout << "Enter p and w of item " << i+1 << endl;
 cin >> a[i].p >> a[i].w; a[i].pDivw = a[i].p / a[i].w;
 }
 sort(a, a+n, cmp);
 double max_p = knapsack(a, n, m);
 cout << "Max Profit is " << max_p;
}
