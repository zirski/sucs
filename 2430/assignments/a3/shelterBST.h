#include <string>

using namespace std;

#ifndef SHELTERBST_H
#define SHELTERBST_H

class ShelterBST {
public:
  ShelterBST();
  ~ShelterBST();
  void insertPet(string name, int age);
  void searchPet(string name);
  void inorderDisplay();
  void preorderDisplay();
  void postorderDisplay();
  void displayParent(string name);
  void displayPredecessor(string name);
  void displayNumNodes();
  void displayNumInternalNodes();
  void displayNumNodesAtLevel(int level);
  void displayTreeHeight();
  void displayBalance();
  void deletePet(string name);
  void destroyTree();
  void test();

private:
  class duplicatePetException {};
  struct Pet {
    string name;
    int age;
    Pet(string name, int age) : name(name), age(age){};
  };
  struct TreeNode {
    Pet* pet;  // you must use a Pet pointer
    TreeNode* left;
    TreeNode* right;
    TreeNode(Pet* pet) : pet(pet), left(nullptr), right(nullptr){};
  };
  TreeNode* root;
  // Throws duplicatePetException if the same-named pet is added more than once.
  // Pre: Pet must not be nullptr
  TreeNode* insert(TreeNode* root, Pet* pet);
  // Returns pointer to TreeNode that matches the given age
  // Nullptr if no match is found
  TreeNode* search(TreeNode* root, string name);
  // The three traversals below will neatly print to screen
  // the Pets’ names and ages in the respective order
  void inorder(TreeNode* root);
  void preorder(TreeNode* root);
  void postorder(TreeNode* root);
  TreeNode* parent(TreeNode* root, TreeNode* parent, string name);
  TreeNode* predecessor(TreeNode* root, string name);
  int numNodes(TreeNode* root);
  int numInternalNodes(TreeNode* root);
  int numNodesAtLevel(TreeNode* root, int target, int current);
  int treeHeight(TreeNode* root);
  bool isBalanced(TreeNode* root);
  TreeNode* deleteNode(TreeNode*& root, string name);
  TreeNode* destroy(TreeNode*& root);
};

#endif
