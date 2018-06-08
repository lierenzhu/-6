#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define WORDS 20

struct sort
{
	char  data[WORDS];
	int time;
};
/**********************�������ڵ�***********************/
typedef struct Bsnode
{
	char data[WORDS];
	int time = 0;
	struct Bsnode *Lchild, *Rchild;
}BSN, *BSP;
/*****************************************************/

/**********************��ջ����***********************/
typedef struct node
{
	BSP bsp;
	struct node *next;
}snode, *slink;
int Emptystack(slink S)
{
	if (S == NULL)
		return(1);
	else
		return(0);
}
BSP Pop(slink *top)
{
	BSP bsp2;
	slink p;
	if (Emptystack(*top))
		return(NULL);
	else
	{
		bsp2 = (*top)->bsp;
		p = *top;
		*top = (*top)->next;
		free(p);
		return(bsp2);
	}
}
void Push(slink *top, BSP bsp)
{
	slink p = NULL;
	p = (slink)malloc(sizeof(snode));
	p->bsp = bsp;
	p->next = *top;
	*top = p;
}
void Clearstack(slink *top)
{
	slink p;
	while (*top != NULL)
	{
		p = (*top)->next;
		Pop(top);
		*top = p;
	}
	*top = NULL;
}
BSP Getstop(slink S)
{
	if (S != NULL)
	{
		return(S->bsp);
	}
	return(NULL);
}
/**********************��ջ��������***********************/

/**********************������������***********************/
int isSame(char x[], char y[])
{
	int i = 0;
	while (x[i] != -51 && x[i] != -52 && y[i] != -51 && y[i] != -52)
	{
		if (x[i] != y[i])
		{
			return(0);
		}
		i++;
	}
	if (x[0] == -51 || x[0] == -52 || y[0] == -51 || y[0] == -52)
		return(0);
	return(1);
}

int isEnd(char x[], char y)
{
	int i = 0;
	while (x[i] != NULL)
	{
		if (x[i] == y)
		{
			return(0);
		}
		i++;
	}
	return(1);
}

/*********************************************************/

/**********************��������������**********************/
int m;
sort *readed, *sorted;
BSP createBst(BSP T,char words[WORDS],int time)
{
	BSP p, q;
	int i, j;
	if (T == NULL)
	{
		q = (BSP)malloc(sizeof(BSN));
		strcpy(q->data, words);
		q->time = time;
		q->Lchild = q->Rchild = NULL;
		T = q;
		m++;
		return(T);
	}
	p = T;
	for (;;)
	{
		if (strcmp(words, p->data) > 0)
		{
			if (p->Rchild == NULL)
			{
				q = (BSP)malloc(sizeof(BSN));
				strcpy(q->data, words);
				q->time = time;
				q->Lchild = q->Rchild = NULL;
				p->Rchild = q;
				m++;
				break;
			}
			else
			{
				p = p->Rchild;
			}
		}
		else if (strcmp(words, p->data) < 0)
		{
			if (p->Lchild == NULL)
			{
				q = (BSP)malloc(sizeof(BSN));
				strcpy(q->data, words);
				q->time = time;
				q->Lchild = q->Rchild = NULL;
				p->Lchild = q;
				m++;
				break;
			}
			else
			{
				p = p->Lchild;
			}
		}
		else
		{
			p->time += time;
			break;
		}
	}
	return(T);
}

int cmp1(const void *a, const void *b);

void inOrderLDR(BSP T)
{
	int i = 0;
	int j = 0;
	BSP p = T;
	slink S = NULL;
	Push(&S, T);
	readed = (sort*)malloc(sizeof(sort)*m);
	FILE *fpWrite;
	fpWrite = fopen("result.txt", "w");
	while (!Emptystack(S))
	{
		while ((p = Getstop(S)) && p)
			Push(&S, p->Lchild);
		p = Pop(&S);
		if (!Emptystack(S))
		{
			p = Pop(&S);
			while (p->data[i] != -51 && p->data[i] != -52)
			{
				printf("%c", p->data[i]);
				i++;
			}
			strcpy(readed[j].data, p->data);
			readed[j].time = p->time;
			j++;
			printf(" ");
			i = 0;
			Push(&S, p->Rchild);
		}
	}
	qsort(readed, m, sizeof(sort), cmp1);
	fprintf(fpWrite,"����%d������\n",m);
	for (int k = 0; k < m; k++)
	{
		fprintf(fpWrite, "%s : %d\n", readed[k].data, readed[k].time);
	}
	fclose(fpWrite);
	printf("\n�ļ���ȡ��ϡ���\n");
	printf("���س�����������\n");
	getchar();
	getchar();
	system("cls");

}


/*********************************************************/

BSP readFromFile()
{
	char file[100], words[WORDS];
	char c;
	int i = 0;
	int j = 0;
	BSP T;
	T = NULL;
	printf("��������Ҫ�ļ�������ȷ���ļ��ڸ�Ŀ¼�£���");
	scanf("%s", file);
	FILE *fpRead = fopen(file, "r");
	c = fgetc(fpRead);
	while (c != -1)
	{
		if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z') || (c >= '0'&&c <= '9') || c == '_')
		{
			words[i] = c;
			i++;
		}
		else if (i != 0)
		{
			words[i] = '\0';
			T = createBst(T,words,1);
			i = 0;
		}
		c = fgetc(fpRead);
	}
	return(T);

}

int cmp1 (const void *a, const void *b)
{
	return -((*(sort *)a).time - (*(sort *)b).time);
}


int chazhao(char a[WORDS])
{
	int i = 0;
	for (i = 0; i < m; i++)
	{
		if (strcmp(readed[i].data, a) == 0)
		{
			return(i);
		}
	}
	return(-1);
}

void find()
{
	int i;
	printf("������Ҫ��ѯ�ĵ��ʣ�");
	char a[WORDS];
	scanf("%s", &a);
	i = chazhao(a);
	if (i != -1)
		printf("%s���ֹ�%d��\n", a, readed[i].time);
	else
		printf("%s������û���ֹ�\n", a);
	printf("���س�����");
	getchar();
	getchar();
	system("cls");
}

void readResult()
{
	FILE *fpReadResult = fopen("result.txt", "r");
	fscanf(fpReadResult, "����%d������", &m);
	free(readed);
	readed = (sort*)malloc(sizeof(sort)*m);
	for (int i = 0; i < m; i++)
	{
		fscanf(fpReadResult, "%s : %d", &readed[i].data, &readed[i].time);
	}
}

void zhuijia()
{
	char c, file[100], words[WORDS];
	int i = 0, j = 0, k;
	FILE *fpRead;
	printf("��������Ҫ׷�ӵ��ļ���ȷ���ļ��ڸ�Ŀ¼�£���");
	scanf("%s", &file);
	fpRead = fopen(file, "r");
	c = fgetc(fpRead);
	BSP T;
	T = NULL;
	int n = m;
	for (k = 0; k < n; k++)
	{
		T = createBst(T, readed[k].data, readed[k].time);
	}
	m = n;
	while (c != -1)
	{
		if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z') || (c >= '0'&&c <= '9') || c == '_')
		{
			words[i] = c;
			i++;
		}
		else if (i != 0)
		{
			words[i] = '\0';
			T = createBst(T, words, 1);
			i = 0;
		}
		c = fgetc(fpRead);
	}
	inOrderLDR(T);
	free(readed);
	readResult();
	fclose(fpRead);
}

void main()
{
	BSP T;
	int i = 0;
	int choose;
	readResult();
	while (1)
	{
		printf("�����������\n1.��ȡ����\n2.���ǰʮ�����ִ������ĵ���\n3.�����ض�����\n4.׷������\n0.�˳�\n");
		scanf("%d", &choose);
		system("cls");
		switch (choose)
		{
		case 1: {
			free(readed);
			T = readFromFile();
			inOrderLDR(T);
			break;
		}
		case 2: {
			readResult();
			for (i = 0; i < 10; i++)
			{
				printf("%s:%d\n", readed[i].data, readed[i].time);
			}
			printf("���س�����������\n");
			getchar();
			getchar();
			system("cls");
			break;
		}
		case 3: {
			find();
			break;
		}
		case 4: {
			zhuijia();
			break;
		}
		case 0: {
			exit(0);
		}
		}
	}
	
}