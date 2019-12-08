#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
float v[101]; //物品价值
float w[101]; //物品重量
float x[101]; //问题的解
float a[101]; //存放vi/wi
int in[101]; //存放vi/wi从大到小的下标
float v1[101];	//按照vi/wi排序号的物品重量
float w1[101]; //按照vi/wi排序好的物品重量
int cmp(int a,int b)
{
	if(a>b)
	return 1;
	return 0;
}
float Knapsack(int n,float M,float v[],float w[],float x[])
{
	int i;
	memset(x,0,sizeof(x));
	i = 0;
	float total = 0; //背包的价值
	while(w[i]<M) //判断当前物品的重量是否能装入背包
	{
		x[i]= 1;
		total += v[i];
		M = M-w[i];
		i++;
	}
	x[i] = M/w[i]; //这是最后装入背包的物品
	total = total+x[i]*v[i];
	return total;
}
int main()
{
	int n,i;
	cout<<"input n:"<<endl;
	cin>>n;
	float W;
	cout<<"input W:"<<endl;
	cin>>W;
	cout<<endl;
	cout<<"input numbergroup:"<<endl;
	for(int i = 0;i<n;i++)
	{
		cin>>w[i]>>v[i];
		a[i] = v[i]/w[i];
	}
	int temp = 0;
	int index = 0;
	for(int i = 0;i<n;i++)	//对数组a即vi/wi进行冒泡降序排序，并且记录下标到in[]数组
	{
	for(int j = 0;j<n-i;j++)
	{
	if(a[j]>a[j+1])
	{
	temp = a[j];
	a[j] = a[j+1];
	a[j+1] = temp;
	index = j;
	}
	}
	in[i] = index;
	}
	for(int i = 0;i<n;i++) //将原来输入的w[i]、v[i]数组进行排列，按照v[i]/w[i]的顺序
	{
	v1[i] = v[in[i]];
	w1[i] = w[in[i]];
	}
	
	cout<<Knapsack(n,W,v1,w1,x)<<endl;
	return 0;
}
