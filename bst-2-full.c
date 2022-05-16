/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {//node를 struct로 선언(지정)
	int key;//정수형 변수 key 선언
	struct node *left;//node에 대한 포인터 left 선언
	struct node *right;//node에 대한 포인터 rignt 선언
} Node;//구조체 별칭 Node

/* for stack */
#define MAX_STACK_SIZE		20 //스택사이즈고정20
Node* stack[MAX_STACK_SIZE]; //크기가 MAX_STACK_SIZE인 스택 생성
int top = -1; //스택초기화

Node* pop(); //스택에서 삭제
void push(Node* aNode); //스택에 삽입

/* for queue */
#define MAX_QUEUE_SIZE		20 //큐사이즈고정20
Node* queue[MAX_QUEUE_SIZE]; //크기가 MAX_QUEUE_SIZE인 큐 생성
int front = -1; 
int rear = -1; 
//큐초기화

Node* deQueue(); //큐에서 삭제
void enQueue(Node* aNode); //큐에 삽입


int initializeBST(Node** h); //트리 초기화

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack(); //스택 출력



int main()
{
	char command;
	int key;
	Node* head = NULL; 

	do{
		printf("[-----[Gahyun] [2020045070] -----\n");
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head); //트리초기화
			break;
		case 'q': case 'Q':
			freeBST(head); //할당된 메모리 해제
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key); //노드 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key); //노드 삭제
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);//재귀적 중위 순회
			break;
		case 't': case 'T':
			iterativeInorder(head->left); //반복적 중위 순회
			break;

		case 'l': case 'L':
			levelOrder(head->left); //레벨순서순회
			break;

		case 'p': case 'P':
			printStack(); //출력
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) { //초기화 하는 함수 

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //포인터 h에 Node의 크기만큼의 메모리 할당
	(*h)->left = NULL;	/* root */ //포인터 h의 left를 NULL로 초기화
	(*h)->right = *h; //포인터 h의 right에 포인터 h 저장
	(*h)->key = -9999; //포인터 h의 key에 -9999를 저장하여 초기화

	top = -1; //스택초기화

	front = rear = -1; //큐초기화

	return 1;
}



void recursiveInorder(Node* ptr) //재귀적중위순회
{
	if(ptr) {
		recursiveInorder(ptr->left); //재귀적중위순회 ptr의 left
		printf(" [%d] ", ptr->key); //key값 출력
		recursiveInorder(ptr->right); //재귀적중우순회 ptr의 right
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node) //반복적 중위 순회
{
	for(;;)
	{
		for(; node; node = node->left) //node의 왼쪽자식노드만큼
			push(node); //삽입
		node = pop(); //삭제

		if(!node) break;
		printf(" [%d] ", node->key);

		node = node->right; //node에 node의 right 저장
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) //레벨순서순회
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */

	enQueue(ptr); //큐에 삽입

	for(;;)
	{
		ptr = deQueue(); //큐에서삭제
		if(ptr) {
			printf(" [%d] ", ptr->key); //ptr 출력

			if(ptr->left) //ptr의 left 일 경우
				enQueue(ptr->left); //ptr의 right에 삽입
			if(ptr->right) //ptr의 right일 경우
				enQueue(ptr->right); //ptr의 left에 삽입
		}
		else
			break;

	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //newNode에 Node 크기만큼의 메모리 할당
	newNode->key = key; //newNode의 key에 입력받은 key 값 저장
	newNode->left = NULL; //newNode의 left NULL로 초기화
	newNode->right = NULL; //newNode의 right NULL로 초기화

	if (head->left == NULL) { //head의 left가 NULL일 경우
		head->left = newNode; //head의 left에 newNode 저장
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //Node의 포인터 ptr에 head의 left저장

	Node* parentNode = NULL; //Node의 parentNode NULL로 초기화
	while(ptr != NULL) { //ptr이 존재할동안

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr의 key가 key보다 작을 때
			ptr = ptr->right; //ptr에 ptr의 right을 저장
		else
			ptr = ptr->left; //ptr에 ptr의 left를 저장
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) //parentNode의 key가 입력받은 key보다 클때
		parentNode->left = newNode; //parentNode의 left에 newNode 저장
	else
		parentNode->right = newNode; //parentNode의 right에 newNode 저장
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL) { //head가 NULL일 경우
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { //head의 left가 NULL일 경우
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left; //포인터 root에 head의 left저장



	Node* parent = NULL; //포인터 parent NULL로 초기화
	Node* ptr = root; //포인터 ptr에 root 저장

	while((ptr != NULL)&&(ptr->key != key)) { //ptr이 존재하고 ptr의 key가 입력받은 key가 아닐 동안
		if(ptr->key != key) { //ptr의 key 가 key 가 아니면

			parent = ptr;	/* save the parent */

			if(ptr->key > key) //ptr의 key가 입력받은 key보다 크다면
				ptr = ptr->left; //ptr에 ptr의 left저장
			else
				ptr = ptr->right; //ptr에 ptr의 right저장
		}
	}

	/* there is no node for the key */
	if(ptr == NULL)
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL) //ptr의 left가 NULL이고 ptr의 right도 NULL일 때
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr) //parent의 left가 ptr일 때
				parent->left = NULL; //parent의 left를 NULL로 초기화
			else
				parent->right = NULL; //parent의 right을 NULL로 초기화
		} else {
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL; //head의 left를 NULL로 초기화

		}

		free(ptr); //ptr에 할당된 메모리 해제
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) //ptr의 left혹은 right가 NULL일 때
	{
		Node* child; //Node의 포인터 child 선언
		if (ptr->left != NULL) //ptr의 left가 NULL이 아니면
			child = ptr->left; //child 에 ptr의 left 저장
		else
			child = ptr->right; //child에 ptr의 right 저장

		if(parent != NULL) //parent가 NULL이 아니면
		{
			if(parent->left == ptr) //parent의 left가 ptr일 경우
				parent->left = child; //parent의 left에 child 저장
			else
				parent->right = child; //parent의 right에 child 저장
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child; //root에 child 저장
		}

		free(ptr); //ptr에 할당된 메모리 해제
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate; //Node에 대한 포인터 candidate 선언
	parent = ptr; //parent에 ptr 선언


	candidate = ptr->right; //candidate에 ptr의 right 저장

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL) //candidate의 left가 NULL이 아닐 때
	{
		parent = candidate; //parent에 candidate 저장
		candidate = candidate->left; //candidate에 candidate의 left저장
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate) //parent의 right가 candidate와 같을 때
		parent->right = candidate->right; //parent의 right에 candidate의 right 저장
	else
		parent->left = candidate->right; //parent의 left에 candidate의 right 저장 

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; //ptr의 key에 candidate의 key 값 저장

	free(candidate); //candidate에 할당된 메모리 해제
	return 1;
}


void freeNode(Node* ptr) //노드에 할당된 메모리 해제
{
	if(ptr) {
		freeNode(ptr->left); //ptr의 left에 할당된 메모리 해제
		freeNode(ptr->right);//ptr의 right에 할당된 메모리 해제
		free(ptr); //ptr에 할당된 메모리 해제
	}
}

int freeBST(Node* head) //트리에 할당된 메모리 해제
{

	if(head->left == head) //head의 left가 head와 같다면
	{
		free(head); //head에 할당된 메모리 해제
		return 1;
	}

	Node* p = head->left; //Node의 포인터 p에 head의 left 저장

	freeNode(p); //노드 p에 할당된 메모리 해제

	free(head); //head에 할당된 메모리 해제
	return 1;
}



Node* pop() //스택에서 삭제
{
	if (top < 0) return NULL; //top이 0보다 작다면 (초기화되어있다면)
	return stack[top--]; //stack[top--] 반환
}

void push(Node* aNode) //스택에 삽입
{
	stack[++top] = aNode; //stack[++top]에 aNode를 저장
}


void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top) //i가 top보다 작거나 같을 동안
	{
		printf("stack[%d] = %d\n", i, stack[i]->key); //stack에 저장된 값 출력
	}
}


Node* deQueue() //큐에서 삭제
{
	if (front == rear) {
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE; //front++
	return queue[front]; //queue의 front 반환

}

void enQueue(Node* aNode) //큐에삽입
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; //rear++
	if (front == rear) {
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode; //queue[rear]에 aNode 저장
}





