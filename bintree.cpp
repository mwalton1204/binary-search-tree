/*********************
Name: Michael Walton
COSC-2436-004
Purpose:
 - Design Binary Search Tree ADT
**********************/

#include "bintree.h"

BinTree::BinTree() {
    root = NULL;
    count = 0;
}

BinTree::~BinTree() {
    clear();
    delete root;
}

bool BinTree::isEmpty() {
    bool empty = false;

    if(!root) {
        empty = true;
    }

    return empty;
}

int BinTree::getCount() {
    return count;
}

bool BinTree::getRootData(Data* tmpData) {
    bool retrieved = false;

    if(root) {
        tmpData->id = root->data.id;
        tmpData->information = root->data.information;
        retrieved = true;
    } else {
        tmpData->id = -1;
        tmpData->information = "";
    }

    return retrieved;
}

void BinTree::displayTree() {
    cout << "DISPLAY TREE" << endl << "==============================================" << endl;
    if(root) {
        cout << "Tree is NOT empty" << endl;
    } else {
        cout << "Tree is empty" << endl;
    }
    cout << "Height " << getHeight() << endl;
    cout << "Node count: " << getCount() << endl << endl;

    cout << "Pre-Order Traversal" << endl;
    displayPreOrder();

    cout << endl << "In-Order Traversal" << endl;
    displayInOrder();

    cout << endl << "Post-Order Traversal" << endl;
    displayPostOrder();

    cout << "==============================================" << endl << endl;
}

void BinTree::clear() {
    clear(root);
    count = 0;
}

void BinTree::clear(DataNode* tmpRoot) {
    if(tmpRoot) {
        clear(tmpRoot->left);
        clear(tmpRoot->right);
        tmpRoot->left = NULL;
        tmpRoot->right = NULL;
        delete tmpRoot;
        root = NULL;
    }
}

bool BinTree::addNode(int newId, const string* newInfo) {
    bool added = false;
    if(newId > 0 && !newInfo->empty()) {
        DataNode *newNode = new DataNode{{newId, *newInfo}, NULL, NULL};
        if (addNode(newNode, &root)) {
            added = true;
            count += 1;
        }
    }
    return added;
}

bool BinTree::addNode(DataNode* newNode, DataNode** root) {
    bool added = false;

    if(!(*root)) {
        *root = newNode;
        added = true;
    } else {
        if (newNode->data.id < (*root)->data.id) {
            added = addNode(newNode, &(*root)->left);
        } else {
            added = addNode(newNode, &(*root)->right);
        }
    }

    return added;
}

bool BinTree::removeNode(int id) {
    int tempCount = count;
    bool removed = false;

    root = removeNode(id, root);

    if(count < tempCount) {
        removed = true;
    }

    return removed;
}

DataNode* BinTree::removeNode(int id, DataNode* tmpRoot) {
    if(tmpRoot) {
        if(id < tmpRoot->data.id) {
            tmpRoot->left = removeNode(id, tmpRoot->left);
        } else if(id > tmpRoot->data.id) {
            tmpRoot->right = removeNode(id, tmpRoot->right);
        } else {
            DataNode* temp;
            if(tmpRoot->left == NULL) {
                temp = tmpRoot->right;
                delete tmpRoot;
                tmpRoot = temp;
                count--;
            } else if (tmpRoot->right == NULL) {
                temp = tmpRoot->left;
                delete tmpRoot;
                tmpRoot = temp;
                count--;
            } else {
                temp = minValueNode(tmpRoot->right);
                tmpRoot->data.id = temp->data.id;
                tmpRoot->data.information = temp->data.information;
                tmpRoot->right = removeNode(temp->data.id, tmpRoot->right);
            }
        }
    }

    return tmpRoot;
}

bool BinTree::getNode(Data* tmpData, int id) {
    bool retrieved = false;
    if(id > 0 && getNode(tmpData, id, root)) {
        retrieved = true;
    }
    return retrieved;
}

bool BinTree::getNode(Data* tmpData, int id, DataNode* tmpRoot) {
    bool retrieved = false;
    if(tmpRoot) {
        if(tmpRoot->data.id == id) {
            tmpData->id = tmpRoot->data.id;
            tmpData->information = tmpRoot->data.information;
            retrieved = true;
        } else {
            if(id < tmpRoot->data.id) {
                retrieved = getNode(tmpData, id, tmpRoot->left);
            } else {
                retrieved = getNode(tmpData, id, tmpRoot->right);
            }
        }
    }
    return retrieved;
}

bool BinTree::contains(int id) {
    bool found = false;
    if(id > 0 && contains(id, root)) {
        found = true;
    }
    return found;
}

bool BinTree::contains(int id, DataNode* tmpRoot) {
    bool found = false;
    if(tmpRoot) {
        if(tmpRoot->data.id == id) {
            found = true;
        } else {
            if(id < tmpRoot->data.id) {
                found = contains(id, tmpRoot->left);
            } else {
                found = contains(id, tmpRoot->right);
            }
        }
    }

    return found;
}

int BinTree::getHeight() {
    return getHeight(root);
}

int BinTree::getHeight(DataNode* tmpRoot) {
    int height = 0;

    if(tmpRoot) {
        int lh = getHeight(tmpRoot->left);
        int rh = getHeight(tmpRoot->right);
        height = max(lh, rh) + 1;
    }

    return height;
}

void BinTree::displayPreOrder() {
    displayPreOrder(root);
}

void BinTree::displayPreOrder(DataNode* tmpRoot) {
    if(tmpRoot) {
        cout << tmpRoot->data.id << " " << tmpRoot->data.information << endl;
        if(tmpRoot->left) {
            displayPreOrder(tmpRoot->left);
        }
        if(tmpRoot->right) {
            displayPreOrder(tmpRoot->right);
        }
    }
}

void BinTree::displayPostOrder() {
    displayPostOrder(root);
}

void BinTree::displayPostOrder(DataNode* tmpRoot) {
    if(tmpRoot) {
        if(tmpRoot->left) {
            displayPostOrder(tmpRoot->left);
        }
        if(tmpRoot->right) {
            displayPostOrder(tmpRoot->right);
        }
        cout << tmpRoot->data.id << " " << tmpRoot->data.information << endl;
    }
}

void BinTree::displayInOrder() {
    displayInOrder(root);
}

void BinTree::displayInOrder(DataNode* tmpRoot) {
    if(tmpRoot) {
        if(tmpRoot->left) {
            displayInOrder(tmpRoot->left);
        }
        cout << tmpRoot->data.id << " " << tmpRoot->data.information << endl;
        if(tmpRoot->right) {
            displayInOrder(tmpRoot->right);
        }
    }
}

DataNode* BinTree::minValueNode(DataNode* node) {
    DataNode* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}