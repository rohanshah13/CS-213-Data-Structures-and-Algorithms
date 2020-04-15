#include<iostream>
#include<vector>

using namespace std;

struct FenwickTreeOneBasedIndexing {
    vector<long long int> bit;  // binary indexed tree
    long long int n;
    /*void init(int size){
    	for(int i=0;i<n;i++){
    		bit.push_back(0);
    	}
    }*/
    FenwickTreeOneBasedIndexing(long long int n) {
        this->n = n + 1;
        bit.assign(n + 1, 0);
    }

    FenwickTreeOneBasedIndexing(vector<long long int> a)
        : FenwickTreeOneBasedIndexing(a.size()) {
        //init(a.size());
        this->n = n + 1;
        bit.assign(n + 1, 0);
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    long long int sum(long long int idx) {
        long long int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }

    long long int sum(long long int l, long long int r) {
        return sum(r) - sum(l - 1);
    }

    void add(long long int idx, long long int delta) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[idx] += delta;
    }
};


int main(){
	long long int n;
	cin>>n;
	vector<long long int> perm(n);
	vector<long long int> zero(n);
	vector<long long int> rev(n);
	for(long long int i=0;i<n;i++){
		long long int temp;
		cin>>temp;
		zero[i]=0;
		perm[i]=temp;
		rev[n-1-i]=temp;
	}
	FenwickTreeOneBasedIndexing fw= FenwickTreeOneBasedIndexing(zero);
	vector<long long int> order(n);
	long long int total_inc=0;
	for(long long int i=0;i<n;i++){
		
		fw.add(perm[i],1);
		long long int temp=fw.sum(n)-fw.sum(perm[i]);
		//cout<<temp<<endl;
		order[perm[i]-1]=n-perm[i]-temp;
		if(perm[i]!=1&&perm[i]!=n){
			//cout<<fw.sum(perm[i]-1)<<" "<<order[perm[i]-1]<<" "<<perm[i]<<endl;
			total_inc+=(fw.sum(perm[i]-1)*order[perm[i]-1]);
		}

	}
	//cout<<total_inc;
	long long int sum1=0;
	for(int i=0;i<n;i++){
		sum1+=(order[i]*(order[i]-1))/2;
	}
	cout<<sum1-total_inc<<" ";
	for(int i=0;i<n;i++){
		perm[i]=n+1-perm[i];
	}	
	FenwickTreeOneBasedIndexing fw1= FenwickTreeOneBasedIndexing(zero);
	vector<long long int> order1(n);
	long long int total_inc1=0;
	for(long long int i=0;i<n;i++){
		
		fw1.add(perm[i],1);
		long long int temp1=fw1.sum(n)-fw1.sum(perm[i]);
		//cout<<temp<<endl;
		order1[perm[i]-1]=n-perm[i]-temp1;
		if(perm[i]!=1&&perm[i]!=n){
			//cout<<fw.sum(perm[i]-1)<<" "<<order[perm[i]-1]<<" "<<perm[i]<<endl;
			total_inc1+=(fw1.sum(perm[i]-1)*order1[perm[i]-1]);
		}

	}
	//cout<<total_inc;
	long long int sum2=0;
	for(int i=0;i<n;i++){
		sum2+=(order1[i]*(order1[i]-1))/2;
	}
	cout<<sum2-total_inc1;

	//<<total_dec<<endl;
	//cout<<sum2-total_dec;
	
}