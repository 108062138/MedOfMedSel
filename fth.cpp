#include <iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<fstream>

using namespace std;

int G;

int PARITION(vector<int>& A, int p, int r) {
    int x = A[r];
    int i = p - 1;
    for (int j = p; j <= r - 1; j++) {
        if (A[j] <= x) {
            i = i + 1;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

int RANDOMIZED_PARTITION(vector<int>& A, int p, int r) {
    int i = rand() % ((r - p + 1)) + p;
    swap(A[r], A[i]);
    return PARITION(A, p, r);
}

int RANDOMIZED_SELECT(vector<int>& A, int p, int r, int i) {
    if (p == r)return A[p];
    int q = RANDOMIZED_PARTITION(A, p, r);
    int k = q - p + 1;
    if (i == k)return A[q];
    else if (i < k)return RANDOMIZED_SELECT(A, p, q - 1, i);
    else return RANDOMIZED_SELECT(A, q + 1, r, i - k);
}

int KTH(vector<int> &arr,int lb, int rb,int k){
    //cout << "status: " << lb << " " << rb << " " << k << endl;
    int cursz = rb - lb + 1;
    if (cursz <= G) {
        sort(arr.begin()+lb, arr.begin()+rb+1);
        //cout << "edge:" << endl;
        //for (auto iter = arr.begin() + lb; iter != arr.begin() + rb+1; ++iter)cout << *iter << " ";
        //cout << endl;
        return *(arr.begin()+ lb + k-1);
    }

    int totalGroup = (cursz+G-1)/G;

    vector<int> mids;

    for(int i=0;i<totalGroup-1;i++){
        sort(arr.begin()+lb+i*G,arr.begin()+lb+i*G+G);
        int md = (lb+i*G + lb+i*G+G-1)/2;
        mids.push_back(arr[md]);
    }

    sort(arr.begin()+lb+(totalGroup-1)*G,arr.begin()+rb);
    mids.push_back(arr.back());

    int midValue = KTH(mids,0,mids.size()-1,ceil(mids.size()/2));
    
    int q=0;
    int meet = 0;
    int l = lb; int r = rb;
    int i = lb;
    //cout << "MIDVALUE==" << midValue << endl;
    //cout << "before partition:" << endl;
    //for (auto x : arr)cout << x << " ";
    //cout << endl;
    while(i<=r){
        if (arr[i] < midValue) {
            swap(arr[l], arr[i]);
            q++;
            l++;
        }
        else if (arr[i] > midValue) {
            swap(arr[i], arr[r]);
            r--;
            i--;
        }
        else meet++;
        i++;
    }

    //cout << "after partition:" << endl;
    //for (auto x : arr)cout << x << " ";
    //cout << endl;

    if(k==q+1) return midValue;

    if (k <= q)
        return KTH(arr,lb,lb+q-1, k);
    else 
        return KTH(arr,lb+q+meet,rb, k - (q + meet));
}

int main()
{
    fstream myfile("input_300_3.txt", std::ios_base::in);
    int N,K;
    N = 10000000; 
    K = 9000000; 
    G = 7;

    //cin>>N>>K>>G;
    myfile >> N >> K >> G;
    vector<int> vec;
    for(int i=0;i<N;i++){
        int val=rand()%35;
        myfile>>val;
        //cin >> val;
        vec.push_back(val);
    }

    
    cout<<"at k="<<K<<endl;
    cout<<"no~~"<<endl;
    int res =KTH(vec,0,N-1,K);
    cout<<"kth res: "<<res<<endl;
    
    nth_element(vec.begin(), vec.begin()+K, vec.end());
    cout<<"true res: "<<vec[K-1]<<endl;

    //sort(vec.begin(),vec.end());
    //for(auto x:vec){
    //    cout<<x<<" ";
    //}cout<<endl;


}

/*
13 5 7
6 1 5 2 3 9 6 4 7 1 0 8 7 
*/