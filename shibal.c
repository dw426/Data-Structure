#include <stdio.h>
#include <stdlib.h>
#define SQ_SIZE 100

typedef struct node* NodeP;
struct node {
   char data;
   struct node* left, * right;
};

NodeP mkNode(char c)
{
   NodeP node = (NodeP)malloc(sizeof(struct node));
   node->data = c; node->left = node->right = NULL;
   return node;
}

int recNodeCount(NodeP node)
{
   if (!node) return 0;
   return 1 + recNodeCount(node->left) + recNodeCount(node->right);
}

int recLeafCount(NodeP node)
{
   if (!node) return 0;
   if (!node->left && !node->right) return 1;
   return recLeafCount(node->left) + recLeafCount(node->right);
}

int recHeight(NodeP node)
{
   int leftHeight, rightHeight;

   if (!node) return 0;
   leftHeight = recHeight(node->left);
   rightHeight = recHeight(node->right);
   return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int iterNodeCount(NodeP node)
{
   if (!node) return 0;

   int count = 0;
   NodeP stack[SQ_SIZE];
   int top = -1;
   stack[++top] = node;

   while (top >= 0) {
      NodeP current = stack[top--];
      count++;

      if (current->right) stack[++top] = current->right;
      if (current->left) stack[++top] = current->left;
   }
   return count;
}

int iterLeafCount(NodeP node)
{
   if (!node) return 0;

   int count = 0;
   NodeP stack[SQ_SIZE];
   int top = -1;
   stack[++top] = node;

   while (top >= 0) {
      NodeP current = stack[top--];

      if (!current->left && !current->right) {
         count++;
      }
      else {
         if (current->right) stack[++top] = current->right;
         if (current->left) stack[++top] = current->left;
      }
   }
   return count;
}

int iterHeight(NodeP node)
{
   if (!node) return 0;

   int maxHeight = 0;
   NodeP queue[SQ_SIZE];
   int front = 0, rear = 0;
   queue[rear++] = node;

   while (front < rear) {
      int levelSize = rear - front;
      maxHeight++;

      for (int i = 0; i < levelSize; i++) {
         NodeP current = queue[front++];
         if (current->left) queue[rear++] = current->left;
         if (current->right) queue[rear++] = current->right;
      }
   }
   return maxHeight;
}

int main()
{
   NodeP root, temp;

   root = mkNode('A');
   root->left = mkNode('B');
   root->right = mkNode('C');
   root->left->left = mkNode('D');
   root->right->left = mkNode('E');
   root->right->right = mkNode('F');
   root->right->left->left = mkNode('G');
   root->right->left->right = mkNode('H');
   root->right->left->right->left = mkNode('K');

   printf("총 노드수: %d\n", iterNodeCount(root));
   printf("리프노드수: %d\n", iterLeafCount(root));
   printf("트리의 높이: %d\n", iterHeight(root));

   return 0;
}
