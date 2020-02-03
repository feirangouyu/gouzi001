#include<stdio.h>
#include<stdlib.h>

/*
搜素数据
@params array 被搜素的数组
@params flag 搜素的标志
@return 找到的节点序号
*/
//枚举法
int enumSearchEle(int* array,int flag);
//二分法
int equiSearchEle(int* array,unsigned int start,unsigned int end,int flag);

#define ElementType int 
typedef struct DATA Data;

struct DATA{
	ElementType data;
};

typedef struct LINKEDNODES LinkedNodes;
struct LINKEDNODES{
	Data D;
	LinkedNodes* next;
	LinkedNodes** pMine;

	void init(LinkedNodes** pMine){
		if(this==NULL) return;
		this->pMine=pMine;
		this->D.data=-1;
		this->next=NULL;
	}

	/*判断是否已初始化*/

	bool flaginit(LinkedNodes* flag){
		if(flag->pMine) return true;
		else return false;
	}



	/* 1
		遍历链表元素并输出
	*/
	void visitedLinkedNodes();

	/* 2
		搜索链表元素
		@params d搜索数据
		@return 找到的节点指针
	*/
	LinkedNodes* searchLinkedNodes(Data d);

	/* 3
		复制链表并返回复制的头节点
		@return pt 复制后新链表的头节点
	*/

	LinkedNodes* ReplicationLinkedList();
	/* 4
		删除链表元素并返回对应节点值
		@params d 需删除的元素
		@return 对应节点值
	*/
	LinkedNodes* DeleteLinkedListElement(Data d);
	
	/* 5
		添加链表元素并返回是否成功
		@params d  添加的元素
		@return 添加元素后的链表头节点
	*/
	LinkedNodes* AddLinkedListElement(Data d);

	/*6
		排序链表元素并返回是否成功
	*/
	bool SortListElements();


	/* 7
		合并俩个链表并返回是否成功
		@params LC 连接对象的链表头节点
	*/
	bool MergetwoLinkedLists(LinkedNodes* LC);

	/* 8
		插入链表元素并返回是否成功
		@params d number 插入的元素 插入元素所在位置
	*/
	bool InsertLinkedListElement(Data d,int number);

	/* ==猴子选大王==
        给定猴子序号为1-n
        每轮从1报到m，
        凡报到m的猴子即退出圈子，
        如此不断循环，
        最后剩下的一只猴子就选为猴王
		@params m 从1报到m，每轮的报到次数
    */
	void findMonkeyKing(int m);
	
	/* ---变种---
	    给定猴子序号为1-n(n为偶数)
        每轮从1报到3，
	    每次连续出去俩位
        最后出去的俩个猴子
        第一个是大王，第二个是二大王
		@params n 猴子总数
		@return answer 一个包含着大王和二大王的序号信息的值
						answer%n+1为大王序号
						answer/n+1为二大王序号
    */
	int findMonkeyKingNo2(int n);
};


int main(){
	LinkedNodes *head=NULL;
	Data d;
	int answer;
	head=(LinkedNodes*)malloc(sizeof(LinkedNodes));
	head->next=NULL;
	head->D.data=1;
	for(int i=2;i<=5;i++){
		d.data=i;
	    head->AddLinkedListElement(d);
	}
	head->visitedLinkedNodes();
	head->findMonkeyKing(3);
	answer=head->findMonkeyKingNo2(i-1);
	printf("大王的序号:%d,二大王的序号:%d\n",answer%(i-1)+1,answer/(i-1)+1);

	return 0;
}
//返回值类型对应结构体名::函数名(函数参数){函数内容}

//函数定义(遍历链表元素并输出)
void LinkedNodes::visitedLinkedNodes(){
	if(this==NULL){
		printf("链表为空\n"); return;
	}
	LinkedNodes *pt=this;
	while(pt->next){
		printf("%d->",pt->D.data);
		pt=pt->next;
	}
	printf("%d\n",pt->D.data);
}

//函数定义(搜素链表元素并返回对应节点指针)
LinkedNodes* LinkedNodes::searchLinkedNodes(Data d){
	LinkedNodes *pt=this;
	while(pt&&pt->D.data!=d.data){
		pt=pt->next;
	}
    return pt;
}

//函数定义(复制链表并返回复制的头节点)
LinkedNodes* LinkedNodes::ReplicationLinkedList(){
	if(this==NULL) return NULL;
	LinkedNodes *pt=NULL,*pt2=this,*pt3=NULL,*pt4=NULL;
	pt=pt3=(LinkedNodes*)malloc(sizeof(LinkedNodes));
	if(pt==NULL) return NULL;
	while(pt2->next){
		pt3->D.data=pt2->D.data;
		pt2=pt2->next;
		pt4=(LinkedNodes*)malloc(sizeof(LinkedNodes));
		if(pt4==NULL) return NULL;
		pt3->next=pt4;
		pt3=pt4;
	}
	pt3->D.data=pt2->D.data;
	pt3->next=NULL;
	return pt;
}

//函数定义(删除链表元素并返回对应节点值)
LinkedNodes* LinkedNodes::DeleteLinkedListElement(Data d){
    if(this||this->searchLinkedNodes(d)==NULL) return NULL;
	LinkedNodes *pt=this,*pt2=NULL;
	if(pt->D.data==d.data){
	   *(this->pMine)=pt->next;
	   return pt;
	}
	while(pt->next->D.data!=d.data){
		pt=pt->next;
	}
	pt2=pt->next;
	pt->next=pt->next->next;
	return pt2;
}

//函数定义(添加链表元素并返回是否成功)
LinkedNodes* LinkedNodes::AddLinkedListElement(Data d){
    LinkedNodes *pt=this,*pt2=NULL;
	if(pt->searchLinkedNodes(d)!=NULL) return NULL;
	pt2=(LinkedNodes*)malloc(sizeof(LinkedNodes));
	if(pt2==NULL) return NULL;
	pt2->D.data=d.data;
	pt2->next=NULL;
	if(this==NULL) return pt2;
	while(pt->next){
		pt=pt->next;
	}
	pt->next=pt2;

	return this;
}

//函数定义(排序链表元素并返回是否成功)
bool LinkedNodes::SortListElements(){
    if(this==NULL) return true;
	if(this->flaginit(this)!=true) return false;
	LinkedNodes *newhead=NULL,*insert=NULL,*next=NULL,*prev=NULL;
    insert=this->next;
	this->next=NULL;
	while(insert!=NULL){
	    newhead=*(this->pMine);
	    next=insert->next;
	    while(newhead && newhead->D.data <= insert->D.data){
	        prev=newhead;
	        newhead=newhead->next;
	    }
        if(newhead==*(this->pMine)){
            insert->next=*(this->pMine);
            *(this->pMine)=insert;
        }
        else{
            insert->next=newhead;
            prev->next=insert;
        }
	    insert=next;
	}
	return true;
}

//函数定义(合并俩个链表并返回是否成功)
bool LinkedNodes::MergetwoLinkedLists(LinkedNodes* LC){
    if(this==NULL && LC==NULL) return true;
    LinkedNodes *pt1,*pt2;
    pt1=this->ReplicationLinkedList();
    pt2=LC->ReplicationLinkedList();
    if(this==NULL) return true;
    while(pt1->next){
        pt1=pt1->next;
    }
    pt1->next=pt2;
    return true;
}

//函数定义(插入链表元素并返回是否成功)
bool LinkedNodes::InsertLinkedListElement(Data d,int number){
    if(this==NULL) return false;
    LinkedNodes *pt=this,*addpt=NULL;
    addpt=(LinkedNodes*)malloc(sizeof(LinkedNodes));
    if(addpt==NULL) return false;
    addpt->D.data=d.data;
    addpt->next=NULL;
    if(number==1){
        *(this->pMine)=addpt;
        addpt->next=pt;
    }
    else{
        while(number--!=2){
            pt=pt->next;
        }
        addpt->next=pt->next;
        pt->next=addpt;
    }
	return true;
}


//枚举法
int enumSearchEle(int* array,int flag){
    int node=1;
    while(*array!=flag){
        array++;
        node++;
    }
    return node;
}

//二分法
int equiSearchEle(int* array,unsigned int start,unsigned int end,int flag){
    int middle;
    while(start<=end){
        middle=(start+end)/2;
        if(*(array+middle)==flag){
            return middle;
        }
        else if(*(array+middle)>flag){
            end=middle-1;
        }
        else{
            start=middle+1;
        }
    }
    return -1;
}

//函数定义(猴子选大王)
void LinkedNodes::findMonkeyKing(int m){
    if(this==NULL) return ;
    LinkedNodes *pt=this->ReplicationLinkedList(),*pre=pt;
    while(pt->next){
		pt=pt->next;
	}
	pt->next=pre;pt=pre;
    while(pt->next!=pt){
        int count=1;
        while(count!=m){
            pre=pt;
            pt=pt->next;
            count++;
        }
        pre->next=pt->next;
        pt->next=NULL;
        free(pt);
        pt=pre->next;
    }
	printf("猴王的序号:%d\n",pt->D.data);
	free(pt);
    return;
}

//函数定义(变种)
int LinkedNodes::findMonkeyKingNo2(int n){
    if(this==NULL) return -1;
    LinkedNodes *pt=this->ReplicationLinkedList(),*pre=pt;
	int answer,No2;
    while(pt->next){
        pt=pt->next;
    }
	pt->next=pre;pt=pre;
	//若链表只含有两个节点
    if(pt==pt->next->next) {
		answer=pt->D.data-1+(pt->next->D.data-1)*n;
		free(pt->next);pt->next=NULL;
		free(pt);pt=NULL;
		return answer;
	}
    while(1){
        int count=1;
        while(count!=3){
            pre=pt;
            pt=pt->next;
            count++;
        }
		No2=pt->next->D.data;
        pre->next=pt->next->next;
        pt->next->next=NULL;free(pt->next);
        pt->next=NULL;free(pt);
        pt=pre->next;
		if(pt==pt->next){
			answer=No2-1+(pt->D.data-1)*n;
			pt->next=NULL;free(pt);
			return answer;
		}
        if(pt->next==pre){
            answer=pt->D.data-1+(pt->next->D.data-1)*n;
			pt->next=NULL;free(pt);
			pre->next=NULL;free(pre);
            return answer;
        }
    }
}
