#include <iostream>
#include <queue>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
};

class BinaryTree {
private:
    Node* root;

    Node* createNode(int value) {
        Node* newNode = new Node();
        if (newNode) {
            newNode->value = value;
            newNode->left = newNode->right = nullptr;
        }
        return newNode;
    }

    Node* insertNode(Node* currentNode, int value) {
        if (currentNode == nullptr) {
            return createNode(value);
        }

        if (value < currentNode->value) {
            currentNode->left = insertNode(currentNode->left, value);
        }
        else if (value > currentNode->value) {
            currentNode->right = insertNode(currentNode->right, value);
        }

        return currentNode;
    }

    Node* minValueNode(Node* currentNode) {
        Node* current = currentNode;

        while (current && current->left != nullptr) {
            current = current->left;
        }

        return current;
    }

    Node* deleteNode(Node* currentNode, int value) {
        if (currentNode == nullptr) {
            return currentNode;
        }

        if (value < currentNode->value) {
            currentNode->left = deleteNode(currentNode->left, value);
        }
        else if (value > currentNode->value) {
            currentNode->right = deleteNode(currentNode->right, value);
        }
        else {
            if (currentNode->left == nullptr) {
                Node* temp = currentNode->right;
                delete currentNode;
                return temp;
            }
            else if (currentNode->right == nullptr) {
                Node* temp = currentNode->left;
                delete currentNode;
                return temp;
            }

            Node* temp = minValueNode(currentNode->right);
            currentNode->value = temp->value;
            currentNode->right = deleteNode(currentNode->right, temp->value);
        }

        return currentNode;
    }

    void inorderTraversal(Node* currentNode) {
        if (currentNode != nullptr) {
            inorderTraversal(currentNode->left);
            cout << currentNode->value << " ";
            inorderTraversal(currentNode->right);
        }
    }

    void preorderTraversal(Node* currentNode) {
        if (currentNode != nullptr) {
            cout << currentNode->value << " ";
            preorderTraversal(currentNode->left);
            preorderTraversal(currentNode->right);
        }
    }

    void postorderTraversal(Node* currentNode) {
        if (currentNode != nullptr) {
            postorderTraversal(currentNode->left);
            postorderTraversal(currentNode->right);
            cout << currentNode->value << " ";
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        root = insertNode(root, value);
    }

    void remove(int value) {
        root = deleteNode(root, value);
    }

    void inorder() {
        inorderTraversal(root);
    }

    void preorder() {
        preorderTraversal(root);
    }

    void postorder() {
        postorderTraversal(root);
    }

    void breadthFirst() {
        if (root == nullptr)
            return;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* currentNode = q.front();
            cout << currentNode->value << " ";
            q.pop();

            if (currentNode->left != nullptr)
                q.push(currentNode->left);

            if (currentNode->right != nullptr)
                q.push(currentNode->right);
        }
    }
};

int main() {
    BinaryTree bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);

    cout << "Inorder Traversal: ";
    bst.inorder();
    cout << endl;

    cout << "Preorder Traversal: ";
    bst.preorder();
    cout << endl;

    cout << "Postorder Traversal: ";
    bst.postorder();
    cout << endl;

    cout << "Breadth First Traversal: ";
    bst.breadthFirst();
    cout << endl;

    bst.remove(20);
    bst.remove(30);

    cout << "Inorder Traversal after removing nodes: ";
    bst.inorder();
    cout << endl;

    return 0;
}