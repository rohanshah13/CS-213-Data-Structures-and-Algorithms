#include<iostream>
#include<vector>
#include<bits/stdc++.h> 

using namespace std;

//define COUNT1 10 

long long int countreg;


struct node{
	double a,b,c,countl,countr;
	node *left, *right;
	node(){
		left=NULL;
		right=NULL;
		countl=0;
		countr=0;
	}
	node(double a1, double b1, double c1){
		a=a1;
		b=b1;
		c=c1;
		left=NULL;
		right=NULL;
		countl=0;
		countr=0;
	}
};

void print2DUtil(node *root, int space)  
{  
    int COUNT1=20;
    // Base case  
    if (root == NULL)  
        return;  
  
    // Increase distance between levels  
    space += COUNT1;  
  
    // Process right child first  
    print2DUtil(root->right, space);  
  
    // Print current node after space  
    // countreg  
    cout<<endl;  
    for (int i = COUNT1; i < space; i++)  
        cout<<" ";  
    cout<<root->a<<" "<<root->b<<" "<<root->c<<"\n";  
  
    // Process left child  
    print2DUtil(root->left, space);  
}  
  
// Wrapper over print2DUtil()  
void print2D(node *root)  
{  
    // Pass initial space countreg as 0  
    print2DUtil(root, 0);  
}  

void count_point(node* root,vector<long long int>& freq){
	if(root->left==NULL){
		freq[root->countl]++;
	}
	else{
		count_point(root->left,freq);
	}
	if(root->right==NULL){
		freq[root->countr]++;
	}
	else{
		count_point(root->right,freq);
	}
}

void find_region(node* root, double x, double y){
	if(root->a*x+root->b*y-root->c>0){
		if(root->left==NULL){
			root->countl++;
			return;
		}
		else{
			find_region(root->left,x,y);
		}
	}
	else if(root->a*x+root->b*y-root->c){
		if(root->right==NULL){
			root->countr++;
			return;
		}
		else{
			find_region(root->right,x,y);
		}
	}
	else{
		return;
	}
}

double findx(double a1, double b1, double c1, double a2, double b2, double c2){
	double x=(b2*c1-b1*c2)/(b2*a1-b1*a2);
	return x;
}
double findy(double a1, double b1, double c1, double a2, double b2, double c2){
	double y=(a2*c1-a1*c2)/(a2*b1-a1*b2);
	return y;
}
void insert(node* root,double a, double b, double c, double x1, double x2,double y1, double y2){
	double side1=root->a*x1+root->b*y1-root->c;
	double side2=root->a*x2+root->b*y2-root->c;
	if(side1==0&&side2==0){
		return;
	}
	else if(side1>=0&&side2>=0){
		if(root->left!=NULL){
			insert(root->left,a,b,c,x1,x2,y1,y2);
			return;
		}
		else{
			root->left=new node(a,b,c);
			countreg++;
			return;
		}
	}
	else if(side1<=0&&side2<=0){
		if(root->right!=NULL){
			insert(root->right,a,b,c,x1,x2,y1,y2);
			return;
		}
		else{
			root->right=new node(a,b,c);
			countreg++;
			return;
		}
	}
	else if(side1>0&&side2<0){
		double x=findx(root->a,root->b,root->c,a,b,c);
		double y=findy(root->a,root->b,root->c,a,b,c);
		if(root->right!=NULL){
			insert(root->right,a,b,c,x,x2,y,y2);
			
		}
		else{
			root->right=new node(a,b,c);
			countreg++;
			
		}
		if(root->left!=NULL){
			insert(root->left,a,b,c,x,x1,y,y1);
			
		}
		else{
			root->left=new node(a,b,c);
			countreg++;
			
		}
	}
	else if(side1<0&&side2>0){
		double x=findx(root->a,root->b,root->c,a,b,c);
		double y=findy(root->a,root->b,root->c,a,b,c);
		if(root->right!=NULL){
			insert(root->right,a,b,c,x,x1,y,y1);
			
		}
		else{
			root->right=new node(a,b,c);
			countreg++;
			
		}
		if(root->left!=NULL){
			insert(root->left,a,b,c,x,x2,y,y2);
			
		}
		else{
			root->left=new node(a,b,c);
			countreg++;
			
		}
		
	}
}
long long int height(node* root){
	if(root==NULL){
		return 0;
	}
	else{
		long long int h1=height(root->left);
		long long int h2=height(root->right);
		if(h1<h2){
			long long int x=h2+1;
			return x;
		}
		else{
			long long int x=h1+1;
			return x;
		}
	}
}
int main(){
	countreg=0;
	long long int n;
	long long int m;
	cin>>n;
	cin>>m;
	double pos_inf=100000000000000;
	double neg_inf=-100000000000000;
	node* tree=new node();
	for(int i=0;i<n;i++){
		double a,b,c;
		cin>>a;
		cin>>b;
		cin>>c;
		if(i==0){
			tree->a=a;
			tree->b=b;
			tree->c=c;
			countreg=2;
		}
		else{
			if(b!=0){
				insert(tree,a,b,c,pos_inf,neg_inf,(c-a*pos_inf)/b,(c-a*neg_inf)/b);
				//print2D(tree);
			}
			else{
				insert(tree,a,b,c,c/a,c/a,pos_inf,neg_inf);
			}
		}
	}
	vector<long long int> freq(m,0);
	for(int i=0;i<m;i++){
		double x,y;
		cin>>x>>y;
		find_region(tree,x,y);
	}
	cout<<countreg<<" "<<height(tree)<<endl;
	count_point(tree,freq);
	for(int i=0;i<m;i++){
		if(freq[i]!=0){
			cout<<i<<" "<<freq[i]<<endl;
		}
	}
	//print2D(tree);
}