#include <iostream>
#include <string>

using namespace std;

class ShelterBST {
private:
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
  // PRIVATE RECURSIVE FUNCTIONS
  // For this lab, TreeNodes will be ordered by Pet age.
  // No duplicate values (Pet ages) will be entered for this lab.
  TreeNode* insert(TreeNode* root, Pet* pet)
  {
    if (root == nullptr)
      root = new TreeNode(pet);
    else if (pet->age < root->pet->age)
      root->left = insert(root->left, pet);
    else
      root->right = insert(root->right, pet);
    return root;
  }
  // Returns pointer to TreeNode that matches the given age
  // Nullptr if no match is found
  TreeNode* search(TreeNode* root, int age)
  {
    if (root == nullptr)
      return nullptr;
    else if (root->pet->age == age)
      return root;
    else {
      if (age < root->pet->age)
        return search(root->left, age);
      else
        return search(root->right, age);
    }
  }
  // The three traversals below will neatly print to screen
  // the Pets’ names and ages in the respective order
  void inorder(TreeNode* root)
  {
    if (root != nullptr) {
      inorder(root->left);
      cout << root->pet->name << ", Age " << root->pet->age << endl;
      inorder(root->right);
    }
  }
  void preorder(TreeNode* root)
  {
    if (root != nullptr) {
      cout << root->pet->name << ", Age " << root->pet->age << endl;
      preorder(root->left);
      preorder(root->right);
    }
  }
  void postorder(TreeNode* root)
  {
    if (root != nullptr) {
      postorder(root->left);
      postorder(root->right);
      cout << root->pet->name << ", Age " << root->pet->age << endl;
    }
  }

public:
  ShelterBST()
  {
    root = nullptr;
  }
  void insertPet(string name, int age)
  {
    root = insert(root, new Pet(name, age));
  }
  void searchPet(int age)
  {
    TreeNode* result = search(root, age);
    if (result == nullptr)
      cout << "Error: pet not found." << endl;
    else
      cout << result->pet->name << endl;
  }
  void inorderDisplay()
  {
    inorder(root);
  }
  void preorderDisplay()
  {
    preorder(root);
  }
  void postorderDisplay()
  {
    postorder(root);
  }
};
// In your main function, test your implementation
// 1. Insert 10 pets into your BST (with different ages)
// 2. Display the three traversals of the resulting BST
// 3. Conduct one successful search and one unsuccessful search
int main()
{
  ShelterBST tree;
  // insert 10 pets, for example: (this syntax may be different
  // depending on how you design your constructors)
  tree.insertPet("Zelda", 5);
  tree.insertPet("Link", 7);
  tree.insertPet("Lillard", 3);
  tree.insertPet("Jordan", 7);
  tree.insertPet("Bird", 9);
  tree.insertPet("Tars", 20);
  tree.insertPet("Case", 7);
  tree.insertPet("Lamelo", 2);
  tree.insertPet("Kyle", 11);
  tree.insertPet("Kipp", 5);
  // inorder display
  cout << "-*- Inorder Display -*-" << endl;
  tree.inorderDisplay();
  // preorder display
  cout << "-*- Preorder Display -*-" << endl;
  tree.preorderDisplay();
  // postorder display
  cout << "-*- Postorder Display -*-" << endl;
  tree.postorderDisplay();
  // successful search
  cout << "searching for pet of age 7:" << endl;
  tree.searchPet(7);
  // unsuccessful search
  cout << "searching for pet of age 100:" << endl;
  tree.searchPet(100);  // assuming no Pet in your tree is aged 100
  return 0;
}
