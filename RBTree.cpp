#include <iostream>
#include <queue>
using namespace std;
template <typename keytype, typename valuetype>
class RBTree {
private:
    struct Node {
        keytype key;
        valuetype value;
        Node* left;
        Node* right;
        Node* parent;
        bool red;
        int size;
    };

    Node* root;
    Node* nil;
    int sizee;
public:

    RBTree()
    {
        nil = new Node;
        nil->left = nil;
        nil->right = nil;
        nil->parent = nil;
        nil->red = false;
        nil->size = 0;
        root = nil;
        sizee = 0;
    }
    RBTree(keytype k[], valuetype v[], int s)
    {
        nil = new Node;
        nil->left = nil;
        nil->right = nil;
        nil->parent = nil;
        nil->red = false;
        nil->size = 0;
        bool sorted = true;

        for (int i = 1; i < s; i++) {
            if (k[i] < k[i - 1]) {
                sorted = false;
                break;
            }
        }
        if (sorted)
        {
            sizee = s;
            root = buildSortedTree(k, v, 0, s - 1, nil);
        }
        else
        {
            root = nil;
            for (int i = 0; i < s; i++) {
                insert(k[i], v[i]);
            }
        }
    }
    RBTree(const RBTree<keytype, valuetype>& copy) {
        root = nodeCopier(copy.root);
        sizee = copy.sizee;
        equalsHelper(copy.root, root, copy);
    }
    ~RBTree()
    {
        while (sizee > 0 && root != nil) {
            remove(root->key);
        }
        delete nil;
    }


    RBTree<keytype, valuetype>& operator=(const RBTree<keytype, valuetype>& copy)
    {
        delete nil;

        nil = new Node;
        nil->left = nil;
        nil->right = nil;
        nil->parent = nil;
        nil->red = false;

        while (sizee > 0)
            remove(root->key);

        root = nodeCopier(copy.root);
        sizee = copy.sizee;
        equalsHelper(copy.root, root, copy);

        return *this;
    }

    Node* nodeCopier(const Node* copy) {
        Node* node = new Node;
        node->key = copy->key;
        node->value = copy->value;
        node->left = nil;
        node->right = nil;
        node->parent = nil;
        node->red = copy->red;
        node->size = copy->size;
        return node;
    }


    void equalsHelper(Node* from, Node* to, const RBTree<keytype, valuetype>& copy) {


        if (from->left != copy.nil) {
            to->left = nodeCopier(from->left);
            to->left->parent = to;
            equalsHelper(from->left, to->left, copy);
        }
        if (from->right != copy.nil) {
            to->right = nodeCopier(from->right);
            to->right->parent = to;
            equalsHelper(from->right, to->right, copy);
        }

    }

    valuetype* search(keytype k)
    {
        Node* current = root;
        while (current != nil)
        {
            if (current->key == k)
            {
                valuetype* val = &current->value;
                return val;
            }
            else if (current->key > k)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        return NULL;
    }


    void insert(keytype k, valuetype v) {
        Node* parent = nil;
        Node* current = root;
        while (current != nil) {
            parent = current;
            if (k < current->key) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        Node* node = new Node;
        node->key = k;
        node->value = v;
        node->left = nil;
        node->right = nil;
        node->parent = parent;
        node->red = true;
        node->size = 1;
        sizee++;


        if (parent == nil) {
            root = node;
        }
        else if (k < parent->key) {
            parent->left = node;
            // updateSubTree(parent);
        }
        else {
            parent->right = node;
            // updateSubTree(parent);
        }

        updateSubTree(node);
        insertfixup(node);
        updateSubTree(node);
        // if (nil->size != 0)
        // {
        //     cout << nil->size << " " << k << endl;
        // }
    }

    void insertfixup(Node* node) {

        while (node != nil && node->parent != nil && node->parent->parent != nil && node->parent->red == true)
        {
            if (node->parent == node->parent->parent->left)
            {
                Node* y = node->parent->parent->right;

                if (y != nil && y->red == true)
                {
                    node->parent->red = false;
                    y->red = false;
                    node->parent->parent->red = true;
                    node = node->parent->parent;
                }
                else if (node == node->parent->right)
                {
                    node = node->parent;
                    leftRotate(node);
                }
                else {
                    node->parent->red = false;
                    node->parent->parent->red = true;
                    rightRotate(node->parent->parent);
                }
            }
            else
            {
                Node* y = node->parent->parent->left;


                if (y != nil && y->red == true)
                {
                    node->parent->red = false;
                    y->red = false;
                    node->parent->parent->red = true;
                    node = node->parent->parent;
                }
                else if (node == node->parent->left)
                {
                    node = node->parent;
                    rightRotate(node);
                }
                else {
                    node->parent->red = false;
                    node->parent->parent->red = true;
                    leftRotate(node->parent->parent);
                }
            }
        }
        root->red = false;
    }

    void  transplant(Node* node, Node* node2)
    {
        // if (node == nullptr || node2 == nullptr || node == nil || node2 == nil)
        // {
        //     return;
        // }
        if (node->parent == nil)
        {
            root = node2;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = node2;
        }
        else
        {
            node->parent->right = node2;
        }

        // if (node->parent == nullptr)
        // {
        //     node->parent = nil;
        // }
        // if (node2->parent == nullptr)
        // {
        //     node2->parent = nil;
        // }
        node2->parent = node->parent;
    }

    void updateSubTree(Node* current)
    {
        if (current->left == nil && current->right == nil)
        {
            current->size = 1;
        }
        else
        {
            current->size = subSize(current->left) + subSize(current->right) + 1;
        }
        if (current->parent != nil)
        {
            updateSubTree(current->parent);
        }
    }

    Node* minimum(Node* x)
    {
        while (x->left != nil)
        {
            x = x->left;
        }
        return x;
    }

    Node* maximum(Node* x)
    {
        while (x->right != nil)
        {
            x = x->right;
        }
        return x;
    }

    int remove(keytype k)
    {
        Node* current = root;
        while (current != nil)
        {
            if (current->key == k)
            {
                Node* y = current;
                bool yOgColor = y->red;
                Node* x;
                if (current->left == nil)
                {
                    x = current->right;
                    transplant(current, current->right);
                }
                else if (current->right == nil)
                {
                    x = current->left;
                    transplant(current, current->left);
                }
                else
                {
                    y = maximum(current->left);
                    yOgColor = y->red;
                    x = y->left;
                    if (y->parent == current)
                    {
                        x->parent = y;
                    }
                    else
                    {
                        transplant(y, y->left);
                        y->left = current->left;
                        y->left->parent = y;
                    }
                    transplant(current, y);
                    y->right = current->right;
                    y->right->parent = y;
                    y->red = current->red;
                }
                updateSubTree(x);
                updateSubTree(y);
                if (yOgColor == false)
                {
                    deleteFixup(x);
                }
                sizee--;
                delete current;

                // updateSubTree(x);
                // updateSubTree(y);
                return 1;
            }
            else if (current->key > k)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        return 0;
    }

    void deleteFixup(Node* x)
    {
        while (x != root && x->red == false)
        {
            if (x == x->parent->left)
            {
                Node* w = x->parent->right;
                if (w->red == true)
                {
                    w->red = false;
                    x->parent->red = true;
                    // updateSubTree(x);
                    // updateSubTree(w);
                    leftRotate(x->parent);
                    w = x->parent->right;
                    updateSubTree(x);
                    updateSubTree(w);
                }
                if (w->left->red == false && w->right->red == false)
                {
                    w->red = true;
                    x = x->parent;
                    updateSubTree(x);
                    updateSubTree(w);
                }
                else if (w->right->red == false)
                {
                    w->left->red = false;
                    w->red = true;
                    // updateSubTree(x);
                    // updateSubTree(w);
                    rightRotate(w);
                    w = x->parent->right;
                    updateSubTree(x);
                    updateSubTree(w);
                }
                else
                {
                    w->red = x->parent->red;
                    x->parent->red = false;
                    w->right->red = false;
                    // updateSubTree(x->right);
                    // updateSubTree(w->right);
                    leftRotate(x->parent);
                    x = root;
                    updateSubTree(x->right);
                    updateSubTree(w->left);
                }
            }
            else
            {
                Node* w = x->parent->left;
                if (w->red == true)
                {
                    w->red = false;
                    x->parent->red = true;
                    updateSubTree(x);
                    updateSubTree(w);
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->red == false && w->left->red == false)
                {
                    w->red = true;
                    x = x->parent;
                    updateSubTree(x);
                    updateSubTree(w);
                }
                else if (w->left->red == false)
                {
                    w->right->red = false;
                    w->red = true;
                    updateSubTree(x);
                    updateSubTree(w);
                    leftRotate(w);
                    w = x->parent->left;
                }
                else
                {
                    w->red = x->parent->red;
                    x->parent->red = false;
                    w->left->red = false;
                    updateSubTree(x);
                    updateSubTree(w);
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->red = false;
    }

    int rank(keytype k)
    {
        Node* current = root;
        Node* x = rankHelper(current, k);
        int z;
        if (x == nil)
        {
            return 0;
        }
        if (x->left == nil)
        {
            z = 1;
        }
        else
        {
            z = x->left->size + 1;
        }
        Node* y = x;
        while (y != current)
        {
            if (y == y->parent->right)
            {
                z += y->parent->left->size + 1;
            }
            y = y->parent;
        }
        return z;
    }

    Node* rankHelper(Node* current, keytype k)
    {
        while (current != nil) {
            if (current->key == k)
            {
                return current;
            }
            else if (k > current->key)
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }
        return nil;
    }


    keytype select(int pos)
    {
        Node* current = root;
        int subTree;
        while (current != nil)
        {
            subTree = subSize(current->left) + 1;
            if (subTree == pos)
            {
                return current->key;
            }
            else if (subTree > pos)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
                pos = pos - subTree;
            }
        }
        return nil->key;
    }


    keytype* successor(keytype k)
    {
        Node* current = root;
        while (current->right != nil)
        {
            current = current->right;
        }
        if (current->key == k)
        {
            return NULL;
        }

        current = root;
        while (current != nil)
        {
            if (current->key == k)
            {
                if (current->right != nil) {
                    current = current->right;
                    while (current->left != nil) {
                        current = current->left;
                    }
                    return &current->key;
                }
                else {
                    Node* successor = nil;
                    Node* ancestor = root;
                    while (ancestor != current) {
                        if (current->key < ancestor->key) {
                            successor = ancestor;
                            ancestor = ancestor->left;
                        }
                        else {
                            ancestor = ancestor->right;
                        }
                    }
                    return &successor->key;
                }
            }
            else if (current->key > k)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        // return &nil->key;
        return NULL;
    }


    keytype* predecessor(keytype k)
    {
        Node* current = root;
        while (current->left != nil)
        {
            current = current->left;
        }
        if (current->key == k)
        {
            return NULL;
        }

        current = root;
        while (current != nil)
        {
            if (current->key == k)
            {
                if (current->left != nil) {
                    current = current->left;
                    while (current->right != nil)
                    {
                        current = current->right;
                    }
                    return &current->key;
                }
                else
                {
                    Node* predecessor = nil;
                    Node* ancestor = root;
                    while (ancestor != current) {
                        if (current->key > ancestor->key) {
                            predecessor = ancestor;
                            ancestor = ancestor->right;
                        }
                        else {
                            ancestor = ancestor->left;
                        }
                    }
                    return &predecessor->key;
                }
            }
            else if (current->key > k)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        // return &nil->key;
        return NULL;
    }

    int subSize(Node* curr) {
        if (curr == nil) {
            return 0;
        }
        else
        {
            return curr->size;
        }
    }

    int size()
    {
        return sizee;
    }
    void preorder()
    {
        Node* current = root;
        recursion(current);
        cout << endl;
    }

    void recursion(struct Node* current) {
        if (current != nil) {

            cout << current->key << " ";
            // current = current->left;
            recursion(current->left);
            // current = current->right;
            recursion(current->right);
        }
    }

    void inorder()
    {
        Node* current = root;
        recursion2(current);
        cout << endl;
    }

    void recursion2(struct Node* current) {
        if (current != nil) {
            recursion2(current->left);
            cout << current->key << " ";
            recursion2(current->right);
        }
    }

    void postorder()
    {
        Node* current = root;
        recursion3(current);
        cout << endl;
    }

    void recursion3(struct Node* current) {
        if (current != nil) {
            recursion3(current->left);
            recursion3(current->right);
            cout << current->key << " ";
        }
    }

    struct Node* buildSortedTree(keytype k[], valuetype v[], int start, int end, Node* parent) {
        if (start > end) {
            return nil;
        }
        int mid = (start + end) / 2;
        Node* node = new Node;
        node->key = k[mid];
        node->value = v[mid];
        node->left = nil;
        node->right = nil;
        node->parent = parent;
        node->red = true;

        updateSubTree(node);

        node->left = buildSortedTree(k, v, start, mid - 1, node);

        updateSubTree(node);

        node->right = buildSortedTree(k, v, mid + 1, end, node);

        updateSubTree(node);
        return node;
    }

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != nil) {
            y->left->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == nil) {
            root = y;

        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
        updateSubTree(x);
        updateSubTree(y);
    }
    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;


        if (y->right != nil) {
            y->right->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == nil) {
            root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }

        y->right = x;
        x->parent = y;
        updateSubTree(x);
        updateSubTree(y);

    }
};
