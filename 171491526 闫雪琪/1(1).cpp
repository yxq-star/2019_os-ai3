#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
float v[101]; //��Ʒ��ֵ
float w[101]; //��Ʒ����
float x[101]; //����Ľ�
float a[101]; //���vi/wi
int in[101]; //���vi/wi�Ӵ�С���±�
float v1[101];	//����vi/wi����ŵ���Ʒ����
float w1[101]; //����vi/wi����õ���Ʒ����
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
	float total = 0; //�����ļ�ֵ
	while(w[i]<M) //�жϵ�ǰ��Ʒ�������Ƿ���װ�뱳��
	{
		x[i]= 1;
		total += v[i];
		M = M-w[i];
		i++;
	}
	x[i] = M/w[i]; //�������װ�뱳������Ʒ
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
	for(int i = 0;i<n;i++)	//������a��vi/wi����ð�ݽ������򣬲��Ҽ�¼�±굽in[]����
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
	for(int i = 0;i<n;i++) //��ԭ�������w[i]��v[i]����������У�����v[i]/w[i]��˳��
	{
	v1[i] = v[in[i]];
	w1[i] = w[in[i]];
	}
	
	cout<<Knapsack(n,W,v1,w1,x)<<endl;
	return 0;
}
