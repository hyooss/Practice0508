#include <stdio.h>
#include <malloc.h>

typedef struct node {
	int data; // ������
	struct node* link; // �ڽŰ� �Ȱ��� ��带 ����Ŵ
} node;

// ��� ���
typedef struct listType {
	int length;  // ����� ����
	struct node* head;  // ù ��° ��带 ����Ű�� ������
} listType;

int circular_list_delte(listType* list, int pos) {

	node* nptr = NULL; //���� ���
	node* pptr = NULL; //���� ���� ���
	int index;
	int delitem;

	//����Ʈ ����ִ� ���
	if (list->length == 0) { //list->head == NULL
		printf("List is Empty!!\n");
		return -1;
	}

	//�߸��� ��ġ�� ������ ���
	if (pos<1 || pos>list->length) {
		printf("Position out of range\n");
		return -1;
	}

	// ù��° ��带 �����ϴ� ���
	if (pos == 1) {
		nptr = list->head;

		//��尡 1������ ���
		if (nptr==nptr->link) { //list->length == 1
			list->head = NULL;
		}
		//��尡 2�� �̻��� ���
		else {
			// pptr�� ������ ���� �̵�
			pptr = list->head;
			for (index = 1; index < list->length; index++) {
				pptr = pptr->link;
			}
			pptr->link = list->head->link;
			list->head = nptr->link; //list->head->link �� ���� ǥ��
			
		}

	}

	// �߰��� ��带 �����ϴ� ���
	// pos�� 2 �̻��� ���
	else {
		// ���� ���� nptr �̵�
		nptr = list->head;
		for (int index = 1; index < pos; index++) {
			pptr = nptr; //�̵��ϱ� ���� ���� �����͸� ����
			nptr = nptr->link;
		}
		pptr->link = nptr->link;
	}
	delitem = nptr->data;
	free(nptr);
	list->length--;
	return delitem;
}

void circular_list_insert(listType* list, int pos, int item)
{
	node* newNode = NULL;
	node* nptr = NULL;
	int index;

	// position�� ��� ���
	if (pos < 1 || pos > list->length + 1) {
		printf("position out of range\n");
		return;
	}

	newNode = (node*)malloc(sizeof(node));
	newNode->data = item;

	// ù ��° ���� ������ ��� ���� �����ʹ� �̵��� �ʿ䰡 ����
	if (pos == 1) {
		// ù��° ��ġ�� ���
		// ����Ʈ�� ����ִ� ���� ��尡 �����ϴ� ���� ������ ����
		if (list->head == NULL) { //����ִ� ���
			newNode->link = newNode; // �ڱ� �ڽ��� ����Ŵ
			list->head = newNode;
		}
		// ������� ���� ���(1�� �̻��� ��尡 ����)
		else {
			//nptr�� ������ ���� �̵�
			//������ ��尡 ù��° ��带 ����Ű�� �ϱ� ���ؼ�
			nptr = list->head;
			for (index = 1; index < list->length; index++) {
				nptr = nptr->link;
			}
			newNode->link = list->head;
			list->head = newNode;
			//������ ��尡 ���� ���ԵǴ� ù��° ��带 ����Ŵ
			nptr->link = newNode;
		}
		}

	//pos�� 2 �̻��� ���	
	else {
		nptr = list->head;
		// ���� ��ġ�� �ٷ� �� ���� �̵�
		// ex) pos=3 �̶�� 2��° ���� �̵�
		for (index = 1; index < pos - 1; index++) {
			nptr = nptr->link;
		}
		newNode->link = nptr->link;
		nptr->link = newNode;
	}

	list->length++;
}

void circular_list_free(listType* list)
{
	// 1.������ ��� ���� ������ ����
	// 2.ù��° ������ �ڷ� ����
	// 3.�ι�° ������ �ڷ� ����

	node* nptr = list->head;
	while (nptr != NULL) {
		// ��尡 1���� ���
		if (nptr == nptr->link)  // �ڱ� �ڽ��� link�� �ڱ� �ڽ��� ����Ŵ
			list->head = NULL;
		// 2�� �̻��� ���
		else {
			// 2��° ��� ���� ����
			nptr = list->head->link;
			list->head->link = nptr->link;
		}
		free(nptr);
		nptr = list->head;  // �ٽ� ù ��° ��带 ����Ŵ
	}
	list->length = 0;
}

void circular_list_display(listType* list)
{
	int index;
	node* nptr = list->head;

	/*
	// ���̸� �̿��� for�� �ݺ�
	printf("Circular List = [");
	for (index = 1; index < list->length; index++) {
		printf("%d", nptr->data);  // ���
		nptr = nptr->link;  // �̵�
		if (nptr != list->head) // �˻� (ù��° ��尡 �ƴϸ�)
			printf("->");
	}
	printf("]\n");
	*/

	// length�� ���� ��� while�� �ݺ�
	printf("Circular List = [");
	// ������ nptr != list->head �� �Ѵٸ� �������ڸ��� ����
	while (nptr != NULL) {
		printf("%d", nptr->data);  // ���
		nptr = nptr->link;  // �̵�
		if (nptr != list->head) // �˻� (ù��° ��尡 �ƴϸ�)
			printf("->");
		else
			nptr = NULL;
	}
	printf("]\n");

	/*
	do {
		if (nptr == NULL)  // ��尡 ���� ���
			break;
		printf("%d", nptr->data);  // ���
		nptr = nptr->link;  // �̵�
		if (nptr != list->head) // �˻� (ù��° ��尡 �ƴϸ�)
			printf("->");

	} while (nptr != list->head);  // �˻縦 ���߿�
	*/
}

void circular_list_menu(listType* list)
{
	int menu, pos, item, delitem = -1;

	while (1) {
		printf("Circular List 1.Insert, 2.Delete, 3.Display, 4.Exit\n");
		printf("Input Menu ? ");
		scanf_s("%d", &menu);

		if (menu == 1) {
			printf("Insert Position ? ");
			scanf_s("%d", &pos);
			printf("Insert Item ? ");
			scanf_s("%d", &item);
			circular_list_insert(list, pos, item);
		}
		else if (menu == 2) {
			// ����ִ��� �˻�
			printf("Delete Position ? ");
			scanf_s("%d", &pos);
			delitem = circular_list_delete(list, pos);
			if (delitem > 0) {
				printf("Delete Item : %d\n", delitem);
			}
		}
		else if (menu == 3) {
			circular_list_display(list);
		}
		else if (menu == 4) {
			circular_list_free(list);
			circular_list_display(list);
			break;
		}
		else {
			printf("menu error\n");
		}
	}
}

listType* circular_list_init(void)
{
	// ������ �ʱ�ȭ
	listType* list = (listType*)malloc(sizeof(listType));
	list->length = 0;
	list->head = NULL;
	return list;
}

int main(void)
{
	listType* list = circular_list_init();
	circular_list_menu(list);
	free(list);
	return 0;
}

