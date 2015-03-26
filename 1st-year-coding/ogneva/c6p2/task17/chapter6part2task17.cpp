#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void sort(vector<int*>& v, bool isAscending) {
	int temp;
	int lowindex, lowkey, i, j; 
	
	if (v.size()>=2) {
	for(i=0; i<v.size(); i++){
		lowindex=i; 
		lowkey=*v[i];		

		for (j=i+1; j<v.size();j++)
			if ((isAscending)?*v[j]<lowkey:*v[j]>lowkey){
				lowkey=*v[j]; 
				lowindex=j;
			} 
		swap (*v[i], *v[lowindex]);		
	}
	}
}

void print(vector<vector<int> >& v)
{
	for (int i=0;i<v.size();i++) {
		for (int j=0;j<v[i].size();j++)
			cout<<v[i][j]<<" ";
		cout<<endl;
	}
}

int main(void){
	freopen("input","r",stdin);
	freopen("output","w",stdout);

	int n;
	cin>>n;

	vector<vector<int> > matrix;
	for (int i=0;i<n;i++)
	{
		vector<int> t = vector<int>(n,0);
		matrix.push_back(t);
	}
	
	for (int i=0;i<n;i++) {			
		for (int j=0;j<n;j++) {			
			cin>>matrix[i][j];
		}				
	}

	print(matrix);
	cout<<"----\n";

	
		
	int k=1;
	int p=matrix.size()/2-1;	
	for (;k<matrix.size(), p>=0 ;k++, p--) {
		vector<int*> aboveDiagonal;
		vector<int*> underDiagonal;

	 for (int i = 0; i < matrix.size(); i++)
  		{
  		for (int j = 0; j < matrix.size(); j++)
   		{
      		if (i==j-k)
         		aboveDiagonal.push_back(&matrix[i][j]);
         	if (i==j+p)
         		underDiagonal.push_back(&matrix[i][j]);
   		}	

  		}
  			sort(aboveDiagonal, false);	
  			sort(underDiagonal, true);
  	}

  	print(matrix);
	

		//for (int j=i+1;j<matrix.size();j++)
		//	aboveDiagonal.push_back(&matrix[i][j]);				
		//sort(underDiagonal, true);
		//sort(aboveDiagonal, false); 
	
	//print(matrix);
		

}