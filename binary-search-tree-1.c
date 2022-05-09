#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  //tree에 노드 삽입
int deleteLeafNode(Node* head, int key); //key의 리프노드 삭제
Node* searchRecursive(Node* ptr, int key);  //key에 대한 노드검색
Node* searchIterative(Node* head, int key);  //key에 대한 노드검색
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	printf("[----- [조정동] [2017015041] -----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head); //트리를 초기화하는 함수 
			break;
		case 'q': case 'Q':
			freeBST(head); //quit
			break;
		case 'n': case 'N':
			printf("Your Key = "); //트리에 key값 삽입
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = "); //트리에 key값 삭제
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key); //iterative방식으로 트리에서 key값 find
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //find -> key의 주소 출력
			else
				printf("\n Cannot find the node [%d]\n", key); //key not find -> not find 문구 출력
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key); //recursive방식으로 트리에서 key값 find
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	//tree가 NULL이 아니면, freeBST를 호출하여 할당된 메모리 모두 해제
	if(*h != NULL)
		freeBST(*h);

	//headnode 생성
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if(ptr) {
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

    //list에 key에 대한 노드하나를 추가
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		// 키에 대한 노드가 있으면 반환
		if(ptr->key == key) return 1;

		// *parentNode를 사용하여 부모노드를 계속 추적
		parentNode = ptr;

		/*키 비교해서 현재 노드의 키가 입력 키보다 큰 경우 새 노드가 오른쪽 하위 트리에 삽입되어야 함
        그렇지 않으면 왼쪽 하위 트리*/
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	//새 노드를 부모 노드에 연결
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left;


	//*parentNode를 사용하여 부모를 계속 추적
	Node* parentNode = head;

	while(ptr != NULL) {

		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {

				/* root node case */
				if(parentNode == head)
					head->left = NULL;

				/* left node case or right case*/
				if(parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;

				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr;

		/*키 비교, 현재 노드의 키가 입력 키보다 큰 경우 새 노드가 오른쪽 하위 트리에 삽입
        그렇지 않으면 왼쪽 하위 트리에 삽입*/
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;


	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL)
		return NULL;

	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	/* if ptr->key == key */
	return ptr;

}
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;

	while(ptr != NULL)
	{
		if(ptr->key == key)
			return ptr;

		if(ptr->key < key) ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	return NULL;
}

void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}




