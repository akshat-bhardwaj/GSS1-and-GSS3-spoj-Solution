#include <algorithm>
#include <stdio.h>
#include <cstdio>
using namespace std;
struct node{
	int sum;
	int left;
	int right;
	int max;
};
node tree[131072];
int a [50000];
node query(int index,int l,int r,int e1,int e2){
	if (l == e1 && r == e2)return (tree[index]);
    int mid = (e1 + e2) / 2;
    if (r <= mid)return query(2 * index + 1, l, r, e1, mid);
    else if (l > mid)return query(2 * index + 2, l, r, mid + 1, e2);
    else {
        node currentResult;
        currentResult.max=0;
        currentResult.right=0;
        currentResult.left=0;
        currentResult.sum=0;
        node leftResult = query(2 * index + 1, l, mid, e1, mid);
        node rightResult = query(2 * index + 2, mid + 1, r, mid + 1, e2);

        currentResult.left= max(leftResult.left, leftResult.sum + rightResult.left);
        currentResult.right = max(leftResult.right + rightResult.sum, rightResult.right);
        currentResult.max = max(leftResult.max, max(leftResult.right + rightResult.left, rightResult.max));
        currentResult.sum = leftResult.sum + rightResult.sum;

        return currentResult;
    }
}
void merge(int index){
	int l=index*2+1;
	int r=index*2+2;
	tree[index].sum=tree[l].sum+tree[r].sum;
	tree[index].max=max(tree[l].right+tree[r].left,max(tree[l].sum+tree[r].left,max(tree[l].sum+tree[r].sum,max(tree[l].right+tree[r].sum,max(tree[l].max,tree[r].max)))));
	tree[index].left=max(tree[l].sum+tree[r].left,max(tree[l].sum,tree[l].left));
	tree[index].right=max(tree[l].right+tree[r].sum,max(tree[r].sum,tree[r].right));
}
int sizeoftree(int N) {
  int size = 1;
  for (; size < N; size <<= 1);
  return size << 1;
}
void maketree(int index,int left,int right){
	if(left==right){
		tree[index].left=tree[index].right=tree[index].sum=tree[index].max=a[left];
	}
	else{
		int mid=(left+right)/2;
		maketree(index*2+1,left,mid);
		maketree(index*2+2,mid+1,right);
		merge(index);
	}
}	
void update(int x,int y,int e1,int e2,int index){
	if(e1==x && e2==x){
		tree[index].max=tree[index].sum=tree[index].left=tree[index].right=y;
		return;
	}
	int mid=(e1+e2)/2;
	if(x<=mid)
		update(x,y,e1,mid,2*index+1);
	else
		update(x,y,mid+1,e2,2*index+2);
	merge(index);
	return;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	int size=sizeoftree(n);
	//cout<<size<<endl;
	maketree(0,0,n-1);
	int q;
	scanf("%d",&q);
	while(q--){
		int c,l,r;
		scanf("%d%d%d",&c,&l,&r);
		if(c==1){
			node newnode;
			newnode=query(0,l-1,r-1,0,n-1);
			printf("%d\n",newnode.max);
		//	printf("%d %d %d\n",newnode.sum,newnode.left,newnode.right);
		}
		else{
			update(l-1,r,0,n-1,0);
		}
	}
}