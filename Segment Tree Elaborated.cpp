#include<bits/stdc++.h>
using namespace std;
int max_size;
int *s;
int *f;

int getMid(int s, int e) {  return s + (e -s)/2;  }

int getSumUtil(int *st, int ss, int se, int qs, int qe, int index)
{
    if (qs <= ss && qe >= se)
        return st[index];

    if (se < qs || ss > qe)
        return 0;

    int mid = getMid(ss, se);
    return getSumUtil(st, ss, mid, qs, qe, 2*index+1) +
           getSumUtil(st, mid+1, se, qs, qe, 2*index+2);
}

void updateValueUtil(int *st, int ss, int se, int i, int diff, int index)
{

    if (i < ss || i > se)
        return;

    st[index] = st[index] + diff;
    if (se != ss)
    {
        int mid = getMid(ss, se);
        updateValueUtil(st, ss, mid, i, diff, 2*index + 1);
        updateValueUtil(st, mid+1, se, i, diff, 2*index + 2);
    }
}
void updateValue(int arr[], int *st, int n, int i, int new_val)
{
    if (i < 0 || i > n-1)
    {
        printf("Invalid Input");
        return;
    }

    int diff = new_val - arr[i];
    arr[i] = new_val;
    updateValueUtil(st, 0, n-1, i, diff, 0);
}

int getSum(int *st, int n, int qs, int qe)
{
    if (qs < 0 || qe > n-1 || qs > qe)
    {
        printf("Invalid Input");
        return -1;
    }
    return getSumUtil(st, 0, n-1, qs, qe, 0);
}

int constructSTUtil(int arr[], int ss, int se, int *st, int si)     /***************    constructSTUtil(arr, 0, n-1, st, 0);    ****************/
{
    if (ss == se)
    {
        st[si] = arr[ss];
        s[si]=ss;
        f[si]=se;
        return arr[ss];
    }
    int mid = getMid(ss, se);

    int xx=constructSTUtil(arr, ss, mid, st, si*2+1);
    int  yy= constructSTUtil(arr, mid+1, se, st, si*2+2);

    if(xx >=0 && yy>=0 )
    {
        st[si] =  xx+yy;
        s[si]=ss;
        f[si]= se;
    }



    return st[si];
}

int *constructST(int arr[], int n)
{
    int x = (int)(ceil(log2(n)));
    max_size = 2*(int)pow(2, x) - 1;
    int *st = new int[max_size];


    s = new int[max_size];
    f = new int[max_size];

    constructSTUtil(arr, 0, n-1, st, 0);
    return st;
}

int main()
{
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }

    int *st = constructST(arr, n);
    int q;
    cin>>q;
    while(q--)
    {
        int aa,bb;
        cin>>aa>>bb;
        cout<<getSum(st, n, aa-1, bb-1)<<"\n";
    }

    for(int i=0;i<max_size;i++)
    {
        cout<<st[i]<<" -> "<<i<<" -> ("<<s[i]<<" , "<<f[i]<<")\n";
    }
}
