#include<iostream>
#include<map>
#include<set>

using namespace std;

struct point{
	long long int x,y;
	point(long long int a, long long int b){
		x=a;
		y=b;
	}

    bool operator<(const point& rhs) const
    {
        if (x < rhs.x)
        {
           return true;
        }
        else if (x == rhs.x)
        {
            if (y < rhs.y)
            {
                return true;
            }
            else{
            	return false;
            }
        }
        else{
        	return false;
        }
    }
};
int main(){
	multiset<point> red,blue;
	long long int n;
	long long int counter=0;
	cin>>n;
	for(long long int i=0;i<n;i++){
		long long int temp1,temp2;
		cin>>temp1;
		cin>>temp2;
		red.insert(point(temp1,temp2));
	}
	for(long long int i=0;i<n;i++){
		long long int temp1,temp2;
		cin>>temp1;
		cin>>temp2;
		blue.insert(point(temp1,temp2));
	}
	multiset<point> :: reverse_iterator rit;
	multiset<point> :: reverse_iterator rit1=blue.rbegin();
	multiset<long long int> y;
	for(rit=red.rbegin();rit!=red.rend();rit++){
		while(rit1->x>=rit->x&&rit1!=blue.rend()){
			y.insert(rit1->y);
			rit1++;
		}
		multiset<long long int> :: iterator lb=y.lower_bound(rit->y);
		if(lb!=y.end()){
			counter++;
			y.erase(lb);
		}
		else{}

	}
	/*for(multiset<point> :: iterator it=red.begin();it!=red.end();it++){
		cout<<it->x<<" "<<it->y<<endl;
	}*/
	cout<<counter;
}