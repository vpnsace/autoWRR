/*AIM- To implement Job Sequencing with Deadline using Greedy Strategy to maximize total profit by scheduling jobs
within their respective deadlines.*/
//{NAME}

#include<bits/stdc++.h>
using namespace std;
struct Job {int d, p, id;};
bool cmp(Job x, Job y) {return x.p > y.p;}
int maxslot = 0;
void Jobseq(Job a[], int n){
    int x[maxslot], profit = 0;
    for(int i = 0; i <= maxslot - 1; i++) x[i] = -1;
    for(int i = 0; i <= n - 1; i++){
        for(int j = min(a[i].d, maxslot) - 1; j >= 0; j--){
            if(x[j] == -1){
                x[j] = a[i].id;
                profit = profit + a[i].p;
                break;
            }
        }
    }
   for(int i = 0; i <= maxslot - 1; i++){
        if(x[i] == -1) cout << "No Job in slot " << i << " - " << i + 1 << endl;
        else cout << "Job No." << x[i] << " in slot " << i << " - " << i + 1 << endl;
    }
    cout << "Maximum Profit = " << profit << endl;
}
int main(){
    int n;
    cout << "Enter No. of Jobs ";
    cin >> n;
    Job a[n];
    for(int i = 0; i < n; i++){
        cout << "Enter id, deadline, Profit of job " << i + 1 << endl;
        cin >> a[i].id >> a[i].d >> a[i].p;
        if(maxslot < a[i].d) maxslot = a[i].d;
    }
    sort(a, a + n, cmp);
    Jobseq(a, n);
}