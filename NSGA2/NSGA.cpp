/* ˵����Ŀ�꺯��ͳһΪ���ֵ*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include <math.h> 
using namespace std;
#define N 5      //������Ⱥ��С
#define SIZE 21    //���򳤶�
#define left -1000	
#define right 1000
#define GET_ARRAY_LEN(array,len){len = (sizeof(array) / sizeof(array[0]));}   //��ȡ����ĳ���

int XX=pow(2,SIZE-1);
typedef struct Node
{
  char gene[SIZE]; //����
  int number;     //��ÿ��������
  struct Node * next;
  double fitness,fitsum;
}Node,*LNode;

typedef struct  VNode
{
	int level;   //ÿ���Ӽ��Ĵ�С
	struct Node * firstarc;
}VNode,*LVNode;

//typedef ; 
VNode AdjList[N];   //���֧�����i�ĸ���������¼������i֧��ĸ��弯��
VNode pop[N];       //��ŷ�֧�伯
string getGene(){
	char  gene1[SIZE];
	for(int i=0;i<SIZE;i++){
		int rd=rand() % 10;
		if(rd>4){
			gene1[i]='1';
		}else{
			gene1[i]='0';
		}
	}
	gene1[SIZE-1]='\0';
	return gene1;
}

void init(LNode &L){   //������ʼ����Ⱥ
		Node * p; Node * r;
		p=L;
		for(int i=0;i<N;i++){
			r= (Node*)malloc(2*sizeof(Node));  
			string s=getGene();
			for(int j=0;j<SIZE;j++)
				r->gene[j]=s[j];	
			r->next=NULL;   //��ĩָ�������
			r->number=i;     //��ÿ��������
			p->next = r;
			p=p->next;
		}
}
double changeNumber(char * c,int length){  //2������ת����10������
	int a=0;
	if(c[0]=='1') a=1;
	for(int i=1;i<length;i++){
		a=a*2;
		if(c[i]=='1') a=a+1;
	}   
	double x=(double)(right-left)/XX;//��ת���ɶ�Ӧ��ʵ��ֵ
	x=x*a-left;
	return x;
}
double f1(double x){//SCH f1
	return x*x;
}
double f2(double x){   //SCH
	return (x-1)*(x-1);
}

bool dominated(double p,double q){//�ж�p�Ƿ�֧��q
	if(f1(p)>f1(q) && f2(p)>f2(q)){
		return true;
	}else{
		return false;
	}
}
void fastNonDominateSort(LNode n){ //�����֧�伯
	Node *p1=n->next;
	for(int i=0;i<N;i++){
		Node * np=AdjList[i].firstarc;  //
		AdjList[i].level=0;
		Node * p2=n->next; //�ڶ���ѭ��
		while (p2!=NULL)
		{
			if(p1->number!=p2->number){
				double x1=changeNumber(p1->gene,N);
				double x2 =changeNumber(p2->gene,N);
				if(dominated(x1,x2)){
					Node * r=(Node*)malloc(2*sizeof(Node));//����һ���½ڵ�
					memcpy(r->gene,p2->gene,SIZE); 
					np=r;    
					np=np->next;				
				}
				else if(dominated(x2,x1)){		
					AdjList[i].level=AdjList[i].level+1;	
				}
			}
			p2=p2->next;
		}
		if(p1->number==0){
			Node * p=pop[0].firstarc;  //��һ����һ���Ӽ�
			Node * r=(Node*)malloc(2*sizeof(Node));//����һ���½ڵ�
			memcpy(r->gene,p1->gene,SIZE); 
			r->number=p1->number;     //��ÿ��������
			p=r;
			p=p->next;
		}
		p1=p1->next;
	}
	int j=0;
	while (pop[j].firstarc!=NULL){
		Node * pp=pop[j].firstarc;
		Node * h1;//����һ������
		Node * qq=AdjList[pp->number].firstarc;
		VNode  r=pop[j];               //����ͷ�ڵ�
		while (qq!=NULL){
			qq->number=qq->number-1;
			if(qq->number==0){
				h1=(Node*)malloc(2*sizeof(Node));//����һ���ڵ�
				h1->number=qq->number;
				memcpy(h1->gene,qq->gene,SIZE); 
				pp=h1;
				pp=pp->next;
			}
			qq=qq->next;
		}
		j=j+1;
		pop[j].firstarc=r.firstarc->next;   //r����Ϊhead
	}
}
/**
��ȡ�Ľṹ������,��ȡð������
**/
void sort(LNode & L){ //����Ⱥp��������  ð������
	
}
void distanceAssignment(LNode & L){//�����֮��ľۼ�����

}
/**
Deb��NSGA-||�㷨�ľ���ʵ��
**/
void nsga(LNode L){
	L=L->next;
	Node * q0=(Node*)malloc(2*sizeof(Node));
	memcpy(q0,L,SIZE);  //��q0���ж�Ԫ������ѡ�񣬽���ͱ������


}
void Printf(LNode node){
	int totle=0;
	node=node->next;
	while (node->next!=NULL)
	{
		totle++;
		printf("%d::%s\n",totle,node->gene);
		node= node->next;
	}
}
int main(){

	Node * node =(Node*)malloc(2*sizeof(Node));
	init(node); // ��ʼ������һ����Ⱥ
	nsga(node);  //Deb��NSGA-||�㷨

	Printf(node);
	fastNonDominateSort(node);

	printf("%d\n",XX);
	
	system("pause");
	return 0;
}
