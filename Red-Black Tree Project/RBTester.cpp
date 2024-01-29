#include "RBTree.cpp"
#include <string>
#include <random>
#include <iostream>
#include <ctime>
#include <iostream>
#include <unistd.h>
using namespace std;

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}

char ABCrandom() {
    static const char alphanum[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char tmp_s;

    tmp_s = alphanum[rand() % (sizeof(alphanum) - 1)];
    
    return tmp_s;
}


int randomInt(int low, int high)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(low,high); 
    // distribution in range [low, high] (I got frustrated with C++ rng so I looked up a better way. I understand none of this)
    return dist6(rng);
}

std::string randomString(int maxLength)
{
    int length = randomInt(1, maxLength);
    return gen_random(length);
}

void veryLargeTreeInt()
{
    const int BIG_SIZE = 2000000;
    RBTree<int, int> tree;
    int temp;
    for(int i = 0; i < BIG_SIZE; i++)
    {
        temp = randomInt(0, BIG_SIZE);
        tree.insert(temp, temp);
    }
    tree.inorder();
}

void veryLargeTreeString()
{
    const int BIG_SIZE = 2000000;
    RBTree<std::string, std::string> tree;
    std::string temp;
    for(int i = 0; i < BIG_SIZE; i++)
    {
        temp = gen_random(5);
        tree.insert(temp, temp);
    }
    tree.inorder();
}

void randomBullshitGo()
{
    const int STARTING_SIZE = 15;
    char arr[STARTING_SIZE];
    for (int i = 0; i < STARTING_SIZE; i++)
    {
        arr[i] = ABCrandom();
    }
    RBTree<char, char> tree(arr, arr, STARTING_SIZE);
    tree.inorder();
    const int RANDOM_CYCLES = 100;
    int dice;
    for (int i = 0; i < RANDOM_CYCLES; i++)
    {
        dice = randomInt(1, 10);
        char query = ABCrandom();
        switch (dice)
        {
            case 1:
            {
                std::cout << "Adding " << query << "..." << std::endl;
                tree.insert(query, query);
                break;
            }
            case 2:
            {
                std::cout << "Removing " << query << "..." << std::endl;
                (tree.remove(query))? std::cout << "Remove success!" << std::endl : std::cout << "Remove failed" << std::endl;
                break;
            }
            case 3:
            {
                std::cout << "Searching for " << query << "..." << std::endl;
                char* result = NULL;
                (result = tree.search(query))? std::cout << "Search yields pointer to " << *result << std::endl : std::cout << "Search failed" << std::endl;
                break;
            }
            case 4:
            {
                std::cout << "Getting rank of " << query << "..." << std::endl;
                int rank;
                (rank = tree.rank(query))? std::cout << "Rank is " << rank << std::endl : std::cout << "Value not found" << std::endl;
                break;
            }
            case 5:
            {
                std::cout << "Getting successor of " << query << "..." << std::endl;
                char* suc;
                (suc = tree.successor(query)) ? std::cout << "Successor is " << *suc << std::endl : std::cout << "Value not found" << std::endl;
                break;
            }
            case 6:
            {
                std::cout << "Getting predecessor of " << query << "..." << std::endl;
                char* pre;
                (pre = tree.predecessor(query))? std::cout << "Predecessor is " << *pre << std::endl : std::cout << "Value not found" << std::endl;
                break;
            }
            case 7:
            {
                int pos = randomInt(1, tree.size());
                std::cout << "Getting element at position " << pos << "..." << std::endl;
                char elem = tree.select(pos);
                std::cout << "Element is " << elem << std::endl;
                break;
            }
            case 8:
            {
                std::cout << "Getting size..." << std::endl;
                int size = tree.size();
                std::cout << "Size is " << size << std::endl;
                break;
            }
            case 9:
            {
                std::cout << "Copying tree..." << std::endl;
                RBTree<char, char> copyTree(tree);
                std::cout << "Inorder traversal of copied tree:" << std::endl;
                copyTree.inorder();
                break;
            }
            case 10:
            {
                std::cout << "Assigning tree..." << std::endl;
                RBTree<char, char> assignedTree;
                assignedTree = tree;
                std::cout << "Inorder traversal of assigned tree:" << std::endl;
                assignedTree.inorder();
                break;
            }
            default:
                break;
        }
        tree.inorder();
    }
}

void insertTester()
{
    std::cout << "Testing insert function..." << std::endl;
    const int STARTING_SIZE = 5;
    char arr[STARTING_SIZE] = {'a', 'c', 'e', 'g', 'i'};
    RBTree<char, char> tree(arr, arr, STARTING_SIZE);

    // Insert some values
    tree.insert('b', 'b');
    tree.insert('d', 'd');
    tree.insert('f', 'f');
    tree.insert('h', 'h');
    tree.insert('j', 'j');

    // Expected size of tree after inserts
    const int EXPECTED_SIZE = STARTING_SIZE + 5;

    // Expected inorder traversal after inserts
    char expectedInorder[EXPECTED_SIZE] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

    // Verify size after inserts
    int actualSize = tree.size();
    if (actualSize != EXPECTED_SIZE)
    {
        std::cout << "Error: Expected size of " << EXPECTED_SIZE << ", but got " << actualSize << std::endl;
    }

    std::cout << "Expected inorder:";
    for (int i = 0; i < EXPECTED_SIZE; i++)
    {
        std::cout << expectedInorder[i];
        if (i < EXPECTED_SIZE - 1) std::cout << " ";
    }
    std::cout << std::endl;
    std::cout << "Got:";
    tree.inorder();
}

void removeTester()
{
    std::cout << "Testing remove function..." << std::endl;
    const int STARTING_SIZE = 10;
    int arr[STARTING_SIZE] = { 10, 5, 15, 3, 7, 13, 17, 1, 4, 6 };
    RBTree<int, int> tree(arr, arr, STARTING_SIZE);

    std::cout << "Initial tree:\n";
    tree.inorder();

    // Test removing a leaf node
    int toRemove = 4;
    std::cout << "\nRemoving " << toRemove << "...\n";
    bool removed = tree.remove(toRemove);
    if (removed)
    {
        std::cout << "Remove success!\n";
    }
    else
    {
        std::cout << "Remove failed\n";
    }
    std::cout << "Expected tree:\n1 3 5 6 7 10 13 15 17\n10 5 3 1 7 6 15 13 17\n";
    std::cout << "Actual tree:\n";
    tree.inorder();
    tree.preorder();

    // Test removing a node with one child
    toRemove = 7;
    std::cout << "\nRemoving " << toRemove << "...\n";
    removed = tree.remove(toRemove);
    if (removed)
    {
        std::cout << "Remove success!\n";
    }
    else
    {
        std::cout << "Remove failed\n";
    }
    std::cout << "Expected tree:\n1 3 5 6 10 13 15 17\n10 5 3 1 6 15 13 17\n";
    std::cout << "Actual tree:\n";
    tree.inorder();
    tree.preorder();

    // Test removing a node with two children
    toRemove = 15;
    std::cout << "\nRemoving " << toRemove << "...\n";
    removed = tree.remove(toRemove);
    if (removed)
    {
        std::cout << "Remove success!\n";
    }
    else
    {
        std::cout << "Remove failed\n";
    }
    std::cout << "Expected tree:\n1 3 5 6 10 13 17\n10 5 3 1 6 13 17\n";
    std::cout << "Actual tree:\n";
    tree.inorder();
    tree.preorder();

    // Test removing the root node
    toRemove = 10;
    std::cout << "\nRemoving " << toRemove << "...\n";
    removed = tree.remove(toRemove);
    if (removed)
    {
        std::cout << "Remove success!\n";
    }
    else
    {
        std::cout << "Remove failed\n";
    }
    std::cout << "Expected tree:\n1 3 5 6 13 17\n6 3 1 5 13 17\n";
    std::cout << "Actual tree:\n";
    tree.inorder();
    tree.preorder();

    // Test removing a non-existent node
    toRemove = 11;
    std::cout << "\nRemoving " << toRemove << "...\n";
    removed = tree.remove(toRemove);
    if (removed)
    {
        std::cout << "Remove success!\n";
    }
    else
    {
        std::cout << "Remove failed\n";
    }
    std::cout << "Expected tree:\n1 3 5 6 13 17\n6 3 1 5 13 17\n";
    std::cout << "Actual tree:\n";
    tree.inorder();
    tree.preorder();
}

void printMenu()
{
    std::cout << "-2: Stop\n-1: Menu\n0: All\n1: Basic Inserts\n2: Basic Removal\n3: Lots of Numbers\n4: Lots of Strings\n5: Random Bullshit" << std::endl;
}

int main()
{
    const int METHOD_COUNT = 5;
    bool done = false;
    while (!done)
    {
        std::cout << "Enter a number to select a tester, -1 for the Menu" << std::endl;
        int methodNum;
        std::string input;
        std::cin >> input;
        try{
            methodNum = std::stoi(input);
            if (!(-2 <= methodNum && methodNum <= METHOD_COUNT)) throw std::out_of_range("no");
        }
        catch(std::invalid_argument)
        {
            cout << "\nPlease enter an integer value.\n";
            std::cin.clear();
            continue;
        }
        catch(std::out_of_range)
        {
            cout << "\nPlease enter an value from -2 - " << METHOD_COUNT << "\n";
            methodNum = -3;
            std::cin.clear();
            continue;
        }
        switch (methodNum)
        {
        case -2:
            done = true;
            break;
        case -1:
            printMenu();
            break;
        case 0:
            insertTester();
            removeTester();
            veryLargeTreeInt();
            veryLargeTreeString();
            randomBullshitGo();
            break;
        case 1:
            insertTester();
            break;
        case 2:
            removeTester();
            break;
        case 3:
            veryLargeTreeInt();
            break;
        case 4:
            veryLargeTreeString();
            break;
        case 5:
            randomBullshitGo();
            break;
        default:
            break;
        }
    }
}