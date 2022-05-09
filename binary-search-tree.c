/*binary-search-tree*/

#include <stdio.h>
#include <stdlib.h>

//이진트리의 노드 구조 선언 - left child와 right child
typedef struct node
{
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node **h);
int freeBST(Node *head); /* free all memories allocated to the tree */
void freeNode(Node *ptr);

void inorderTraversal(Node *ptr);	/* recursive inorder traversal */
void preorderTraversal(Node *ptr);	/* recursive preorder traversal */
void postorderTraversal(Node *ptr); /* recursive postorder traversal */

int insert(Node *head, int key);		 /* insert a node to the tree */
int deleteLeafNode(Node *head, int key); /* delete the leaf node for the key */

Node *searchRecursive(Node *ptr, int key);	/* search the node for the key */
Node *searchIterative(Node *head, int key); /* search the node for the key */

int main()
{
	char command;
	int key;
	Node *head = NULL;
	Node *ptr = NULL; /* temp */

	printf("[----- [JinYeongKim] [2019038030] -----]");

	do
	{
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

		switch (command)
		{
		case 'z':
		case 'Z':
			initializeBST(&head);
			break;
		case 'q':
		case 'Q':
			freeBST(head);
			break;

		case 'n':
		case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd':
		case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;

		case 'f':
		case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's':
		case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i':
		case 'I':
			inorderTraversal(head->left);
			break;
		case 'p':
		case 'P':
			preorderTraversal(head->left);
			break;
		case 't':
		case 'T':
			postorderTraversal(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node **h)
{

	//이진트리가 null 상태가 아니면 초기화
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node *)malloc(sizeof(Node));
	(*h)->left = NULL; /* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

//중위순회 방식(LVR)
void inorderTraversal(Node *ptr)
{
	if (ptr)
	{
		inorderTraversal(ptr->left);  //함수를 stack에 쌓아가며 ptr을 left child가 null일 때까지 이동
		printf(" [%d] ", ptr->key);	  // left child가 null일 때 현재 ptr 노드 출력
		inorderTraversal(ptr->right); // ptr을 right로 이동
	}								  //스택에 쌓였던 함수들을 LIFO 방식으로 차례대로 실행
}

//전위순회 방식(VLR)
void preorderTraversal(Node *ptr)
{
	if (ptr)
	{
		printf(" [%d] ", ptr->key);	   // recursive 방식으로 이동하기 전 먼저 ptr 출력
		preorderTraversal(ptr->left);  //함수를 stack에 쌓아가며 ptr을 left child가 null일 때까지 출력하며 이동
		preorderTraversal(ptr->right); // left child가 끝나면 right child 출력하며 이동 until null
	}
}

//후위순회 방식(LRV)
void postorderTraversal(Node *ptr)
{
	if (ptr)
	{
		postorderTraversal(ptr->left);	//함수를 stack에 쌓아가며 ptr을 left child가 null일 때까지 이동
		postorderTraversal(ptr->right); //함수를 stack에 쌓아가며 ptr을 right child가 null일 때까지 이동
		printf(" [%d] ", ptr->key);		//그리고 ptr 출력
	}
}

int insert(Node *head, int key)
{
	// insert할 트리 노드 메모리 할당
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	// root가 NULL일 때 즉 아무 노드도 없을 때
	if (head->left == NULL)
	{
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node *ptr = head->left;

	Node *parentNode = NULL;
	while (ptr != NULL)
	{

		/* 이미 그 키값의 노드가 존재하면 종료 */
		if (ptr->key == key)
			return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/*키값을 비교하여 기존 노드보다 크면 오른쪽 작으면 왼쪽 노드로 이동*/
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* 새로운 노드와 기존 부모 노드 link */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

int deleteLeafNode(Node *head, int key)
{
	// head가 아예 초기화가 안 되었거나
	if (head == NULL)
	{
		printf("\n Nothing to delete!!\n");
		return -1;
	}
	// root가 NULL 즉 아무 노드도 없을 때
	if (head->left == NULL)
	{
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node *ptr = head->left;
	Node *parentNode = head;

	// ptr이 NULL이 아닐 때까지 반복
	while (ptr != NULL)
	{

		if (ptr->key == key)
		{
			if (ptr->left == NULL && ptr->right == NULL)
			{

				/* 삭제하고자 하는 노드가 root일 때 */
				if (parentNode == head)
					head->left = NULL;

				/* left node case or right case*/
				if (parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;

				free(ptr); //노드 삭제
			}
			//입력한 노드가 leaf가 아닐 경우 노드 즉 연결되어있을 경우
			else
			{
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr;

		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}
}

// recursive 방식으로 search
Node *searchRecursive(Node *ptr, int key)
{
	if (ptr == NULL)
		return NULL;

	if (ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	else if (ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	/* recursive가 끝나면 최종적으로 ptr->key == key */
	return ptr;
}

Node *searchIterative(Node *head, int key)
{
	/* root node */
	Node *ptr = head->left;

	// ptr이 NULL이 아닐 때까지 반복
	while (ptr != NULL)
	{
		if (ptr->key == key)
			return ptr;

		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	return NULL;
}

void freeNode(Node *ptr)
{
	if (ptr)
	{
		//마치 preorder 방식으로 free 해준다. 그래야 연속적으로 free를 해줄 수 있다.
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

//헤드노드까지 완전히 free
int freeBST(Node *head)
{
	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node *p = head->left;

	freeNode(p);

	free(head);
	return 1;
}
