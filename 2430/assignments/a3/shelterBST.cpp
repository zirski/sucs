#include "shelterBST.h"

#include <cmath>
#include <iostream>
#include <string>

ShelterBST::ShelterBST()
{
  root = nullptr;
}

ShelterBST::~ShelterBST()
{
  destroyTree();
}

ShelterBST::TreeNode* ShelterBST::insert(TreeNode* root, Pet* pet)
{
  if (root == nullptr)
    root = new TreeNode(pet);
  else if (pet->name == root->pet->name)
    throw new duplicatePetException;
  else if (pet->name < root->pet->name)
    root->left = insert(root->left, pet);
  else
    root->right = insert(root->right, pet);
  return root;
}
ShelterBST::TreeNode* ShelterBST::search(TreeNode* root, string name)
{
  if (root == nullptr)
    return nullptr;
  else if (root->pet->name == name)
    return root;
  else {
    if (name < root->pet->name)
      return search(root->left, name);
    else
      return search(root->right, name);
  }
}

void ShelterBST::inorder(TreeNode* root)
{
  if (root != nullptr) {
    inorder(root->left);
    cout << root->pet->name << ", Age " << root->pet->age << endl;
    inorder(root->right);
  }
}
void ShelterBST::preorder(TreeNode* root)
{
  if (root != nullptr) {
    cout << root->pet->name << ", Age " << root->pet->age << endl;
    preorder(root->left);
    preorder(root->right);
  }
}
void ShelterBST::postorder(TreeNode* root)
{
  if (root != nullptr) {
    postorder(root->left);
    postorder(root->right);
    cout << root->pet->name << ", Age " << root->pet->age << endl;
  }
}

ShelterBST::TreeNode* ShelterBST::parent(TreeNode* root, TreeNode* p,
                                         string name)
{
  if (root == nullptr)
    return root;
  else if (root->pet->name == name)
    return p;
  else if (name < root->pet->name)
    return parent(root->left, root, name);
  else
    return parent(root->right, root, name);
}

ShelterBST::TreeNode* ShelterBST::predecessor(TreeNode* root, string name)
{
  if (root->pet->name == name && root->left != nullptr)
    return root->left;
  else if (name < root->pet->name)
    return predecessor(root->left, name);
  else
    return predecessor(root->right, name);
}

int ShelterBST::numNodes(TreeNode* root)
{
  if (root == nullptr)
    return 0;
  else if (root->left == nullptr && root->right == nullptr)
    return 1;
  else if (root->left != nullptr && root->right == nullptr)
    return 1 + numNodes(root->left);
  else if (root->right != nullptr && root->left == nullptr)
    return 1 + numNodes(root->right);
  else
    return 1 + numNodes(root->left) + 1 + numNodes(root->right);
}

int ShelterBST::numInternalNodes(TreeNode* root)
{
  if (root->left == nullptr || root->right == nullptr)
    return 1;
  else
    return numInternalNodes(root->left) + numInternalNodes(root->right);
}

int ShelterBST::numNodesAtLevel(TreeNode* root, int target, int current)
{
  if (root == nullptr)
    return 0;
  else if (target == current)
    return 1;
  else
    return numNodesAtLevel(root->left, target, current + 1) +
           numNodesAtLevel(root->right, target, current + 1);
}

int ShelterBST::treeHeight(TreeNode* root)
{
  if (root == nullptr)
    return 0;
  else if (treeHeight(root->left) > treeHeight(root->right))
    return 1 + treeHeight(root->left);
  else
    return 1 + treeHeight(root->right);
}

bool ShelterBST::isBalanced(TreeNode* root)
{
  return abs(treeHeight(root->left) - treeHeight(root->right)) <= 1;
}

ShelterBST::TreeNode* ShelterBST::deleteNode(TreeNode*& root, string name)
{
  if (root == nullptr)
    return nullptr;
  else {
    TreeNode* target = root;
    TreeNode* parent;
    bool left;
    // Iteratively searches for target node and stores it and its parent
    while (target->left != nullptr || target->right != nullptr) {
      if (target->left != nullptr && name < target->pet->name) {
        parent = target;
        target = target->left;
        left = true;
      } else if (target->right != nullptr) {
        parent = target;
        target = target->right;
        left = false;
      }
    }
    if (target->left == nullptr && target->right == nullptr) {
      delete target;
      if (left)
        parent->left = nullptr;
      else
        parent->right = nullptr;
    } else if (!(target->left != nullptr && target->right != nullptr)) {
      if (target->left != nullptr) {
        if (left)
          parent->left = target->left;
        else
          parent->right = target->left;
      } else {
        if (left)
          parent->left = target->right;
        else
          parent->right = target->right;
      }
      delete target;
    } else {
      TreeNode* pred = predecessor(root, name);
      pred->left = target->left;
      pred->right = target->right;
      delete target;
    }
    return root;
  }
}

ShelterBST::TreeNode* ShelterBST::destroy(TreeNode*& root)
{
  if (root != nullptr) {
    destroy(root->left);
    destroy(root->right);
    delete root;
    root = nullptr;
  }
  return nullptr;
}

void ShelterBST::insertPet(string name, int age)
{
  root = insert(root, new Pet(name, age));
}

void ShelterBST::searchPet(string name)
{
  TreeNode* result = search(root, name);
  if (result == nullptr)
    cout << "Error: pet not found." << endl;
  else
    cout << result->pet->name << ", age" << result->pet->age << endl;
}

void ShelterBST::inorderDisplay()
{
  inorder(root);
}

void ShelterBST::preorderDisplay()
{
  preorder(root);
}

void ShelterBST::postorderDisplay()
{
  postorder(root);
}

void ShelterBST::displayParent(string name)
{
  TreeNode* parent = ShelterBST::parent(root, nullptr, name);
  cout << "Parent node of " << name << ":" << endl;
  cout << parent->pet->name << ", " << parent->pet->age << endl;
}

void ShelterBST::displayPredecessor(string name)
{
  TreeNode* pred = ShelterBST::predecessor(root, name);
  cout << "Predecessor node of " << name << ":" << endl;
  cout << pred->pet->name << ", " << pred->pet->age << endl;
}

void ShelterBST::displayNumNodes()
{
  cout << "Number of nodes in tree: " << numNodes(root) << endl;
}

void ShelterBST::displayNumInternalNodes()
{
  cout << "Number of internal nodes in tree: " << numInternalNodes(root)
       << endl;
}

void ShelterBST::displayNumNodesAtLevel(int level)
{
  cout << "Number of internal nodes at level " << level << ": "
       << numNodesAtLevel(root, level, 0) << endl;
}

void ShelterBST::displayTreeHeight()
{
  cout << "Tree Height: " << ShelterBST::treeHeight(root) << endl;
}

void ShelterBST::displayBalance()
{
  if (isBalanced(root))
    cout << "The tree is balanced" << endl;
  else
    cout << "The tree is not balanced" << endl;
}

void ShelterBST::deletePet(string name)
{
  ShelterBST::deleteNode(root, name);
}

void ShelterBST::destroyTree()
{
  ShelterBST::destroy(root);
}

void ShelterBST::test()
{
  if (root != nullptr)
    destroyTree();
  // Insertions
  cout << "Inserting pet Smudge, age 12" << endl;
  insertPet("Smudge", 12);
  cout << "Inserting pet Angus, age 7" << endl;
  insertPet("Angus", 7);
  cout << "Inserting pet Rio, age 8" << endl;
  insertPet("Rio", 8);
  cout << "Inserting pet Zuzu, age 3" << endl;
  insertPet("Zuzu", 3);
  cout << "Inserting pet Ferris Wheel, age 5" << endl;
  insertPet("Ferris Wheel", 5);
  cout << "Inserting pet Beeb, age 7" << endl;
  insertPet("Beeb", 7);
  cout << "Inserting pet Katy, age 13" << endl;
  insertPet("Katy", 13);
  cout << "Inserting pet Indy, age 4" << endl;
  insertPet("Indy", 4);
  cout << "Inserting pet Violet, age 2" << endl;
  insertPet("Violet", 2);
  cout << "Inserting pet Coco, age 11" << endl;
  insertPet("Coco", 11);

  // Search tests
  cout << "Searching for Beeb..." << endl;
  searchPet("Beeb");
  cout << "Searching for Caius Pompeius..." << endl;
  searchPet("Caius Pompeius");

  // Display tests
  cout << "--------------------------------"
       << "Inorder Display:" << endl;
  inorderDisplay();
  cout << "--------------------------------"
       << "Preorder Display:" << endl;
  preorderDisplay();
  cout << "--------------------------------"
       << "Postorder Display:" << endl;
  postorderDisplay();

  // Tree data tests
  displayParent("Violet");
  displayPredecessor("Rio");
  displayNumNodes();
  displayNumInternalNodes();
  displayNumNodesAtLevel(2);
  displayTreeHeight();
  displayBalance();

  // Deletion
  cout << "Deleted node Coco" << endl;
  deletePet("Coco");
}
