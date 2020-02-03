#include<stdio.h>
#include<stdlib.h>

/*
��������
@params array �����ص�����
@params flag ���صı�־
@return �ҵ��Ľڵ����
*/
//ö�ٷ�
int enumSearchEle(int* array,int flag);
//���ַ�
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

	/*�ж��Ƿ��ѳ�ʼ��*/

	bool flaginit(LinkedNodes* flag){
		if(flag->pMine) return true;
		else return false;
	}



	/* 1
		��������Ԫ�ز����
	*/
	void visitedLinkedNodes();

	/* 2
		��������Ԫ��
		@params d��������
		@return �ҵ��Ľڵ�ָ��
	*/
	LinkedNodes* searchLinkedNodes(Data d);

	/* 3
		�����������ظ��Ƶ�ͷ�ڵ�
		@return pt ���ƺ��������ͷ�ڵ�
	*/

	LinkedNodes* ReplicationLinkedList();
	/* 4
		ɾ������Ԫ�ز����ض�Ӧ�ڵ�ֵ
		@params d ��ɾ����Ԫ��
		@return ��Ӧ�ڵ�ֵ
	*/
	LinkedNodes* DeleteLinkedListElement(Data d);
	
	/* 5
		�������Ԫ�ز������Ƿ�ɹ�
		@params d  ��ӵ�Ԫ��
		@return ���Ԫ�غ������ͷ�ڵ�
	*/
	LinkedNodes* AddLinkedListElement(Data d);

	/*6
		��������Ԫ�ز������Ƿ�ɹ�
	*/
	bool SortListElements();


	/* 7
		�ϲ��������������Ƿ�ɹ�
		@params LC ���Ӷ��������ͷ�ڵ�
	*/
	bool MergetwoLinkedLists(LinkedNodes* LC);

	/* 8
		��������Ԫ�ز������Ƿ�ɹ�
		@params d number �����Ԫ�� ����Ԫ������λ��
	*/
	bool InsertLinkedListElement(Data d,int number);

	/* ==����ѡ����==
        �����������Ϊ1-n
        ÿ�ִ�1����m��
        ������m�ĺ��Ӽ��˳�Ȧ�ӣ�
        ��˲���ѭ����
        ���ʣ�µ�һֻ���Ӿ�ѡΪ����
		@params m ��1����m��ÿ�ֵı�������
    */
	void findMonkeyKing(int m);
	
	/* ---����---
	    �����������Ϊ1-n(nΪż��)
        ÿ�ִ�1����3��
	    ÿ��������ȥ��λ
        ����ȥ����������
        ��һ���Ǵ������ڶ����Ƕ�����
		@params n ��������
		@return answer һ�������Ŵ����Ͷ������������Ϣ��ֵ
						answer%n+1Ϊ�������
						answer/n+1Ϊ���������
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
	printf("���������:%d,�����������:%d\n",answer%(i-1)+1,answer/(i-1)+1);

	return 0;
}
//����ֵ���Ͷ�Ӧ�ṹ����::������(��������){��������}

//��������(��������Ԫ�ز����)
void LinkedNodes::visitedLinkedNodes(){
	if(this==NULL){
		printf("����Ϊ��\n"); return;
	}
	LinkedNodes *pt=this;
	while(pt->next){
		printf("%d->",pt->D.data);
		pt=pt->next;
	}
	printf("%d\n",pt->D.data);
}

//��������(��������Ԫ�ز����ض�Ӧ�ڵ�ָ��)
LinkedNodes* LinkedNodes::searchLinkedNodes(Data d){
	LinkedNodes *pt=this;
	while(pt&&pt->D.data!=d.data){
		pt=pt->next;
	}
    return pt;
}

//��������(�����������ظ��Ƶ�ͷ�ڵ�)
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

//��������(ɾ������Ԫ�ز����ض�Ӧ�ڵ�ֵ)
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

//��������(�������Ԫ�ز������Ƿ�ɹ�)
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

//��������(��������Ԫ�ز������Ƿ�ɹ�)
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

//��������(�ϲ��������������Ƿ�ɹ�)
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

//��������(��������Ԫ�ز������Ƿ�ɹ�)
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


//ö�ٷ�
int enumSearchEle(int* array,int flag){
    int node=1;
    while(*array!=flag){
        array++;
        node++;
    }
    return node;
}

//���ַ�
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

//��������(����ѡ����)
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
	printf("���������:%d\n",pt->D.data);
	free(pt);
    return;
}

//��������(����)
int LinkedNodes::findMonkeyKingNo2(int n){
    if(this==NULL) return -1;
    LinkedNodes *pt=this->ReplicationLinkedList(),*pre=pt;
	int answer,No2;
    while(pt->next){
        pt=pt->next;
    }
	pt->next=pre;pt=pre;
	//������ֻ���������ڵ�
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
