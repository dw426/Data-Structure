#include <stdio.h>
#include <stdlib.h>

struct node {
    char data;
    struct node *left, *right;
};

typedef struct node* NodeP;

NodeP mkNode(char c) {
    NodeP node = (NodeP)malloc(sizeof(struct node));
    node->data = c;
    node->left = node->right = NULL;
    return node;
}

// 총 노드 수 계산 (비순환적 방법)
int iterNodeCount(NodeP root) {
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

// 리프 노드 수 계산 (비순환적 방법)
int iterLeafCount(NodeP root) {
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

// 트리의 높이 계산 (비순환적 방법)
int iterHeight(NodeP root) {
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
                // 높이를 추적하면서 자식의 높이를 비교하여 갱신
                int leftHeight = (current->left) ? 1 : 0;
                int rightHeight = (current->right) ? 1 : 0;
                height = (height > (leftHeight > rightHeight ? leftHeight : rightHeight)) ? height : (leftHeight > rightHeight ? leftHeight : rightHeight);
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

    // 총 노드 수 출력
    printf("Total number of nodes: %d\n", iterNodeCount(root));
    
    // 리프 노드 수 출력
    printf("Number of leaf nodes: %d\n", iterLeafCount(root));
    
    // 트리 높이 출력
    printf("Height of the tree: %d\n", iterHeight(root));
    
    return 0;
}
