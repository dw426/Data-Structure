#include <stdio.h>
#include <stdlib.h>

typedef struct node * NodeP;
struct node {
    char data;
    struct node *left, *right;
};

NodeP mkNode(char c) {
    NodeP node = (NodeP)malloc(sizeof(struct node));
    node->data = c;
    node->left = node->right = NULL;
    return node;
}

int iterNodeCount(NodeP root) {
    if (!root) return 0;

    int count = 0;
    NodeP stack[100];
    int top = -1;

    stack[++top] = root;
    
    while (top >= 0) {
        NodeP current = stack[top--];
        count++;

        if (current->right) stack[++top] = current->right;
        if (current->left) stack[++top] = current->left;
    }

    return count;
}

int iterLeafCount(NodeP root) {
    if (!root) return 0;

    int count = 0;
    NodeP stack[100];
    int top = -1;

    stack[++top] = root;
    
    while (top >= 0) {
        NodeP current = stack[top--];

        if (!current->left && !current->right) {
            count++;
        }
        
        if (current->right) stack[++top] = current->right;
        if (current->left) stack[++top] = current->left;
    }

    return count;
}

int iterHeight(NodeP root) {
    if (!root) return 0;

    int height = 0;
    NodeP queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;
    
    while (front < rear) {
        int levelSize = rear - front;
        height++;

        for (int i = 0; i < levelSize; i++) {
            NodeP current = queue[front++];
            if (current->left) queue[rear++] = current->left;
            if (current->right) queue[rear++] = current->right;
        }
    }

    return height;
}

int main() {
    NodeP root = mkNode('A');
    root->left = mkNode('B');
    root->right = mkNode('C');
    root->left->left = mkNode('D');
    root->right->left = mkNode('E');
    root->right->right = mkNode('F');
    root->right->left->left = mkNode('G');
    root->right->left->right = mkNode('H');
    root->right->left->right->left = mkNode('K');

    printf("총 노드수 : %d\n", iterNodeCount(root));
    printf("리프 노드수 : %d\n", iterLeafCount(root));
    printf("트리 높이 : %d\n", iterHeight(root));
    
    return 0;
}
