#include <iostream>
#include <random>
#include <vector>
#include <set>
#include <sstream>
#include "BST.h"

// ANSI escape codes for coloring output
const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";

// Function to generate a string representation of the set
std::string setToString(const std::set<int>& s) {
    std::ostringstream oss;
    for (const int& num : s) {
        oss << num << "\n";
    }
    return oss.str();
}

// Random test function
void randomTests() {
    BinarySearchTree<int> bst;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 100);
    std::set<int> elements;

    std::cout << GREEN << "\n--- Random Tests ---\n" << RESET << std::endl;

    // Insert random elements
    std::cout << GREEN << "Inserting random elements into the BST:" << RESET << std::endl;
    for (int i = 0; i < 10; ++i) {
        int num = distribution(generator);
        bst.insert(num);
        elements.insert(num);
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Print the initial tree
    std::cout << BLUE << "Initial tree (in-order):" << RESET << std::endl;
    bst.printTree();

    // Compare the BST contents with the set
    std::cout << YELLOW << "Elements in set after insertion: " << RESET << std::endl;
    std::cout << setToString(elements) << std::endl;

    // Remove random elements that are actually present in the BST
    std::cout << GREEN << "Removing some random elements from the BST:" << RESET << std::endl;
    for (int i = 0; i < 5; ++i) {
        auto it = elements.begin();
        std::advance(it, distribution(generator) % elements.size());
        int num = *it;
        std::cout << "Trying to remove: " << RED << num << RESET << std::endl;

        // Remove the element from the BST and the set
        bst.remove(num);
        elements.erase(it);

        // Print the tree into a stringstream for comparison
        std::stringstream treeOutput;
        bst.printTree(treeOutput);

        // Display the tree structure
        std::cout << BLUE << "Tree after removing " << RED << num << BLUE << ":" << RESET << std::endl;
        std::cout << treeOutput.str();

        // Compare the BST contents with the set
        std::string setString = setToString(elements);
        std::cout << YELLOW << "Elements in set after removal: " << RESET << std::endl;
        std::cout << setString << std::endl;

        // Check if both outputs match
        std::vector<int> bstElements;
        std::istringstream bstStream(treeOutput.str());
        int bstNum;
        while (bstStream >> bstNum) {
            bstElements.push_back(bstNum);
        }

        // Compare each element in the set with the BST in-order traversal
        bool match = true;
        auto setIt = elements.begin();
        for (const int& bstElement : bstElements) {
            if (setIt == elements.end() || bstElement != *setIt) {
                match = false;
                break;
            }
            ++setIt;
        }

        if (match && setIt == elements.end()) {
            std::cout << GREEN << "The BST and the set match." << RESET << std::endl;
        } else {
            std::cout << RED << "Mismatch between the BST and the set!" << RESET << std::endl;
        }
    }

    bst.makeEmpty(); // Clean up
}

// Special case test function
void specialCaseTests() {
    BinarySearchTree<int> bst;
    std::set<int> elements;

    std::cout << GREEN << "\n--- Special Case Tests ---\n" << RESET << std::endl;

    // 1. Attempt to delete from an empty tree
    std::cout << YELLOW << "Test 1: Deleting from an empty tree" << RESET << std::endl;
    bst.remove(10); // Try to remove from an empty tree
    bst.printTree(); // Should remain empty

    // 2. Insert a single node and delete it
    std::cout << YELLOW << "\nTest 2: Insert a single node and delete it" << RESET << std::endl;
    bst.insert(50);
    elements.insert(50);
    std::cout << "Tree after inserting 50:" << std::endl;
    bst.printTree();

    bst.remove(50);
    elements.erase(50);
    std::cout << "Tree after deleting 50 (should be empty):" << std::endl;
    bst.printTree();

    // 3. Insert duplicate elements
    std::cout << YELLOW << "\nTest 3: Insert duplicate elements" << RESET << std::endl;
    bst.insert(30);
    bst.insert(30); // Attempt to insert duplicate
    elements.insert(30);
    std::cout << "Tree after attempting to insert duplicate 30:" << std::endl;
    bst.printTree();

    // 4. Remove a leaf node
    std::cout << YELLOW << "\nTest 4: Remove a leaf node" << RESET << std::endl;
    bst.insert(15);
    bst.insert(40);
    elements.insert(15);
    elements.insert(40);
    std::cout << "Tree before removing leaf node 15:" << std::endl;
    bst.printTree();

    bst.remove(15);
    elements.erase(15);
    std::cout << "Tree after removing leaf node 15:" << std::endl;
    bst.printTree();

    // 5. Remove a node with one child
    std::cout << YELLOW << "\nTest 5: Remove a node with one child" << RESET << std::endl;
    bst.insert(10);
    bst.insert(5);
    elements.insert(10);
    elements.insert(5);
    std::cout << "Tree before removing node 10 (which has one child 5):" << std::endl;
    bst.printTree();

    bst.remove(10);
    elements.erase(10);
    std::cout << "Tree after removing node 10 (should retain child 5):" << std::endl;
    bst.printTree();

    // 6. Remove a node with two children
    std::cout << YELLOW << "\nTest 6: Remove a node with two children" << RESET << std::endl;
    bst.insert(25);
    bst.insert(20);
    bst.insert(30);
    elements.insert(25);
    elements.insert(20);
    elements.insert(30);
    std::cout << "Tree before removing node 25 (which has two children 20 and 30):" << std::endl;
    bst.printTree();

    bst.remove(25);
    elements.erase(25);
    std::cout << "Tree after removing node 25 (should reorganize correctly):" << std::endl;
    bst.printTree();

    bst.makeEmpty(); // Clean up
}



class Checker : public BinarySearchTree<int>{
private:
    using BinarySearchTree<int>::root;
    using node = BinarySearchTree<int>::BinaryNode;

public:
    void createChain(int N){
        root = new node(1, nullptr, nullptr);
        root->height = N;
        auto p = root;
        for(int i = 2; i <= N; i++){
            p->right = new node(i, nullptr, nullptr);
            p = p->right;
            p->height = N - i + 1;
        }
    }
};

void testIncreasingData(){
    std::cout << "------------------------------" << std::endl;
    const int N = 7;
    Checker bst;
    bst.createChain(N);

    std::cout << "success created" << std::endl;
    // std::cout << "Before remove:" << std::endl;
    bst.remove(N);
    bst.printTree();

    for(int i = N; i >= 1; i--)
        bst.remove(i);

    std::cout << "After remove:" << std::endl;
    bst.printTree();
}


void linearTests() {
    BinarySearchTree<int> bst;
    std::set<int> elements;

    std::cout << GREEN << "\n--- Linear Tests ---\n" << RESET << std::endl;

    testIncreasingData();
    // 1. Insert elements in increasing order
    std::cout << YELLOW << "Test 1: Insert elements in increasing order" << RESET << std::endl;
    for (int i = 1; i <= 10; ++i) {
        bst.insert(i);
        elements.insert(i);
    }
    std::cout << "Tree after inserting elements 1 to 10:" << std::endl;
    bst.printTree();

    // 2. Remove elements in decreasing order
    std::cout << YELLOW << "\nTest 2: Remove elements in decreasing order" << RESET << std::endl;
    bst.remove(10);

    bst.printTree();

    for (int i = 9; i >= 1; --i) {
        bst.remove(i);
        elements.erase(i);
    }

    std::cout << "Tree after removing elements 10 to 1:" << std::endl;
    bst.printTree();

    // 3. Insert elements in decreasing order
    std::cout << YELLOW << "\nTest 3: Insert elements in decreasing order" << RESET << std::endl;
    for (int i = 10; i >= 1; --i) {
        bst.insert(i);
        elements.insert(i);
    }
    std::cout << "Tree after inserting elements 10 to 1:" << std::endl;
    bst.printTree();

    // 4. Remove elements in increasing order
    std::cout << YELLOW << "\nTest 4: Remove elements in increasing order" << RESET << std::endl;
    for (int i = 1; i <= 10; ++i) {
        bst.remove(i);
        elements.erase(i);
    }
    std::cout << "Tree after removing elements 1 to 10:" << std::endl;
    bst.printTree();

    bst.makeEmpty(); // Clean up
}

int main() {
    randomTests();
    specialCaseTests();
    linearTests();
    testIncreasingData();
    return 0;
}
