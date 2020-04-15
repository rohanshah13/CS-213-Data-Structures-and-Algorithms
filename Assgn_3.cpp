#include<iostream>
#include<vector>

using namespace std;


void add(vector<int>::iterator ptr1,vector<int>::iterator ptr2,vector<int>::iterator ptr_a,long long int n) {
	for (long long int i=0;i<n;i++){
		*next(ptr_a,i)=*next(ptr1,i)+*next(ptr2,i);
	}
}
void subtract(vector<int>::iterator ptr1,vector<int>::iterator ptr2,vector<int>::iterator ptr_a,long long int n) {
	for (long long int i=0;i<n;i++){
		*next(ptr_a,i)=*next(ptr1,i)-*next(ptr2,i);
	}
}

void multiply(vector<int>::iterator ptr1,vector<int>::iterator ptr2,vector<int>::iterator ptr_a,long long int n) {
	if(n<=32){
		for(long long int i=0;i<n;i++){
			for(long long int j=0;j<n;j++){
				*next(ptr_a,(i+j))+=*next(ptr1,i)*(*next(ptr2,j));
			}
		}
	}
	else{
		multiply(ptr1,ptr2,ptr_a,n/2);
		multiply(next(ptr1,n/2),next(ptr2,n/2),next(ptr_a,n),n/2);
		vector<int> sum1(n/2);
		vector<int> sum2(n/2);
		vector<int> prod(n-1);
		add(ptr1,next(ptr1,n/2),sum1.begin(),n/2);
		add(ptr2,next(ptr2,n/2),sum2.begin(),n/2);
		multiply(sum1.begin(),sum2.begin(),prod.begin(),n/2);
		subtract(prod.begin(),ptr_a,prod.begin(),n-1);
		subtract(prod.begin(),next(ptr_a,n),prod.begin(),n-1);
		add(next(ptr_a,n/2),prod.begin(),next(ptr_a,n/2),n-1);
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	long long int n;
	cin>>n;
	vector<int> p1,p2;
	for(long long int i=0; i<n;i++){
		int coeff;
		cin>>coeff;
		p1.push_back(coeff);
	}
	for(long long int i=0; i<n;i++){
		int coeff;
		cin>>coeff;
		p2.push_back(coeff);
	}
	vector<int> r(2*n-1);
	
	multiply(p1.begin(),p2.begin(),r.begin(),n);
	for (vector<int>::iterator ptr = r.begin(); ptr < r.end(); ptr++){
		cout<<*ptr<<" ";
	}
}

