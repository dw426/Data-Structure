#include <stdio.h>
#include <stdlib.h>

typedef struct node * NodeP;
struct node {  // 트리의 노드 구조
    char data;
    struct node *left, *right;
};

NodeP mkNode(char c) {
    NodeP node = (NodeP)malloc(sizeof(struct node));
    node->data = c;
    node->left = node->right = NULL;
    return node;
}

// 비순환적 방법으로 총 노드 수 계산
int iterNodeCount(NodeP root) {
    if (!root) return 0;

    int count = 0;
    NodeP current = root;
    NodeP pre;

    while (current != NULL) {
        if (current->left == NULL) {
            count++;  // 노드를 방문할 때마다 카운트 증가
            current = current->right;
        } else {
            pre = current->left;
            while (pre->right != NULL && pre->right != current) {
                pre = pre->right;
            }

            if (pre->right == NULL) {
                pre->right = current;
                current = current->left;
            } else {
                pre->right = NULL;
                count++;  // 노드를 방문할 때마다 카운트 증가
                current = current->right;
            }
        }
    }

    return count;
}

// 비순환적 방법으로 리프 노드 수 계산
int iterLeafCount(NodeP root) {
    if (!root) return 0;

    int count = 0;
    NodeP current = root;
    NodeP pre;

    while (current != NULL) {
        if (current->left == NULL) {
            // 리프 노드는 왼쪽 자식과 오른쪽 자식이 모두 NULL인 경우
            if (current->right == NULL) {
                count++;
            }
            current = current->right;
        } else {
            pre = current->left;
            while (pre->right != NULL && pre->right != current) {
                pre = pre->right;
            }

            if (pre->right == NULL) {
                pre->right = current;
                current = current->left;
            } else {
                pre->right = NULL;
                // 리프 노드는 왼쪽, 오른쪽 자식이 모두 NULL인 경우
                if (current->left == NULL && current->right == NULL) {
                    count++;
                }
                current = current->right;
            }
        }
    }

    return count;
}

// 비순환적 방법으로 트리 높이 계산
int iterHeight(NodeP root) {
    if (!root) return 0;

    int height = 0;
    NodeP current = root;
    NodeP pre;

    while (current != NULL) {
        if (current->left == NULL) {
            current = current->right;
        } else {
            pre = current->left;
            while (pre->right != NULL && pre->right != current) {
                pre = pre->right;
            }

            if (pre->right == NULL) {
                pre->right = current;
                current = current->left;
            } else {
                pre->right = NULL;
                // 왼쪽과 오른쪽 서브트리의 높이를 비교하여 최대 높이를 선택
                int leftHeight = 0, rightHeight = 0;
                if (current->left) leftHeight = iterHeight(current->left);
                if (current->right) rightHeight = iterHeight(current->right);
                
                height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
                current = current->right;
            }
        }
    }

    return height;
}

int main() {
    // 트리 구조 설정
    NodeP root = mkNode('A');
    root->left = mkNode('B');
    root->right = mkNode('C');
    root->left->left = mkNode('D');
    root->right->left = mkNode('E');
    root->right->right = mkNode('F');
    root->right->left->left = mkNode('G');
    root->right->left->right = mkNode('H');
    root->right->left->right->left = mkNode('K');

    // 총 노드 수 출력
    printf("Total number of nodes: %d\n", iterNodeCount(root));
    
    // 리프 노드 수 출력
    printf("Number of leaf nodes: %d\n", iterLeafCount(root));
    
    // 트리 높이 출력
    printf("Height of the tree: %d\n", iterHeight(root));
    
    return 0;
}
