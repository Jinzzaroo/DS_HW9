/*binary-search-tree*/

#include <stdio.h>
#include <stdlib.h>

//이진트리의 노드 구조 선언 - left child와 right child
typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);
int freeBST(Node* head); /* free all memories allocated to the tree */

void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */

int insert(Node* head, int key);  		  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */

Node* searchRecursive(Node* ptr, int key);   /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

    printf("[----- [JinYeongKim] [2019038030] -----]");

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
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;

		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;

		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
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

    //이진트리가 null 상태가 아니면 초기화
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

//중위순회 방식(LVR)
void inorderTraversal(Node* ptr)
{
	if(ptr) {
		inorderTraversal(ptr->left);	//함수를 stack에 쌓아가며 ptr을 left child가 null일 때까지 이동
		printf(" [%d] ", ptr->key);		//left child가 null일 때 현재 ptr 노드 출력
		inorderTraversal(ptr->right);	//함수를 stack에 쌓아가며 ptr을 right child가 null일 때까지 이동
	}	//스택에 쌓였던 함수들을 LIFO 방식으로 차례대로 실행
}

//전위순회 방식(VLR)
void preorderTraversal(Node* ptr)
{
	if(ptr) {
		printf(" [%d] ", ptr->key);		//recursive 방식으로 이동하기 전 먼저 ptr 출력
		preorderTraversal(ptr->left);	//함수를 stack에 쌓아가며 ptr을 left child가 null일 때까지 출력하며 이동
		preorderTraversal(ptr->right);	//left child가 끝나면 right child 출력하며 이동 until null
	}
}

//후위순회 방식(LRV)
void postorderTraversal(Node* ptr)
{
	if(ptr) {
		postorderTraversal(ptr->left);	//함수를 stack에 쌓아가며 ptr을 left child가 null일 때까지 이동
		postorderTraversal(ptr->right);	//함수를 stack에 쌓아가며 ptr을 right child가 null일 때까지 이동
		printf(" [%d] ", ptr->key);		//그리고 ptr 출력
	}
}


int insert(Node* head, int key)
{

}

int deleteLeafNode(Node* head, int key)
{

}

Node* searchRecursive(Node* ptr, int key)
{

}
Node* searchIterative(Node* head, int key)
{

}

void freeNode(Node* ptr)
{

}

int freeBST(Node* head)
{

}