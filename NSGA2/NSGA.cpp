/* 说明：目标函数统一为最大值*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include <math.h> 
using namespace std;
#define N 5      //定义种群大小
#define SIZE 21    //基因长度
#define left -1000	
#define right 1000
#define GET_ARRAY_LEN(array,len){len = (sizeof(array) / sizeof(array[0]));}   //获取数组的长度

int XX=pow(2,SIZE-1);
typedef struct Node
{
  char gene[SIZE]; //基因
  int number;     //给每个基因编号
  struct Node * next;
  double fitness,fitsum;
}Node,*LNode;

typedef struct  VNode
{
	int level;   //每个子集的大小
	struct Node * firstarc;
}VNode,*LVNode;

//typedef ; 
VNode AdjList[N];   //存放支配个体i的个体数，记录被个体i支配的个体集合
VNode pop[N];       //存放非支配集
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

void init(LNode &L){   //产生初始化种群
		Node * p; Node * r;
		p=L;
		for(int i=0;i<N;i++){
			r= (Node*)malloc(2*sizeof(Node));  
			string s=getGene();
			for(int j=0;j<SIZE;j++)
				r->gene[j]=s[j];	
			r->next=NULL;   //在末指针下添加
			r->number=i;     //给每个基因编号
			p->next = r;
			p=p->next;
		}
}
double changeNumber(char * c,int length){  //2进制数转换成10进制数
	int a=0;
	if(c[0]=='1') a=1;
	for(int i=1;i<length;i++){
		a=a*2;
		if(c[i]=='1') a=a+1;
	}   
	double x=(double)(right-left)/XX;//并转换成对应的实际值
	x=x*a-left;
	return x;
}
double f1(double x){//SCH f1
	return x*x;
}
double f2(double x){   //SCH
	return (x-1)*(x-1);
}

bool dominated(double p,double q){//判断p是否支配q
	if(f1(p)>f1(q) && f2(p)>f2(q)){
		return true;
	}else{
		return false;
	}
}
void fastNonDominateSort(LNode n){ //构造非支配集
	Node *p1=n->next;
	for(int i=0;i<N;i++){
		Node * np=AdjList[i].firstarc;  //
		AdjList[i].level=0;
		Node * p2=n->next; //第二层循环
		while (p2!=NULL)
		{
			if(p1->number!=p2->number){
				double x1=changeNumber(p1->gene,N);
				double x2 =changeNumber(p2->gene,N);
				if(dominated(x1,x2)){
					Node * r=(Node*)malloc(2*sizeof(Node));//生成一个新节点
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
			Node * p=pop[0].firstarc;  //第一个第一个子集
			Node * r=(Node*)malloc(2*sizeof(Node));//生成一个新节点
			memcpy(r->gene,p1->gene,SIZE); 
			r->number=p1->number;     //给每个个体编号
			p=r;
			p=p->next;
		}
		p1=p1->next;
	}
	int j=0;
	while (pop[j].firstarc!=NULL){
		Node * pp=pop[j].firstarc;
		Node * h1;//生成一个集合
		Node * qq=AdjList[pp->number].firstarc;
		VNode  r=pop[j];               //保存头节点
		while (qq!=NULL){
			qq->number=qq->number-1;
			if(qq->number==0){
				h1=(Node*)malloc(2*sizeof(Node));//生成一个节点
				h1->number=qq->number;
				memcpy(h1->gene,qq->gene,SIZE); 
				pp=h1;
				pp=pp->next;
			}
			qq=qq->next;
		}
		j=j+1;
		pop[j].firstarc=r.firstarc->next;   //r必须为head
	}
}
/**
采取的结构是链表,采取冒泡排序
**/
void sort(LNode & L){ //对种群p进行排序  冒泡排序
	
}
void distanceAssignment(LNode & L){//求个体之间的聚集距离

}
/**
Deb的NSGA-||算法的具体实现
**/
void nsga(LNode L){
	L=L->next;
	Node * q0=(Node*)malloc(2*sizeof(Node));
	memcpy(q0,L,SIZE);  //对q0进行二元锦标赛选择，交叉和变异操作


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
	init(node); // 初始化参数一个种群
	nsga(node);  //Deb的NSGA-||算法

	Printf(node);
	fastNonDominateSort(node);

	printf("%d\n",XX);
	
	system("pause");
	return 0;
}
