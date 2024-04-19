/*
** Binary Search Tree Basic Operations
** Lab 3, CPSC 2430
*/
class ShelterBST {
private:
  struct Pet {
    string name;
    int age;
    // add your constructor here
    // ...
  };
  struct TreeNode {
    Pet* pet;  // you must use a Pet pointer
    TreeNode* left;
    TreeNode* right;
  };
  TreeNode* root;
  // PRIVATE RECURSIVE FUNCTIONS
  // For this lab, TreeNodes will be ordered by Pet age.
  // No duplicate values (Pet ages) will be entered for this lab.
  TreeNode* insert(TreeNode* root, Pet* pet)
  {
    // add your code here
    // ...
  }
  // Returns pointer to TreeNode that matches the given age
  // Nullptr if no match is found
  TreeNode* search(TreeNode* root, int age)
  {
    // add your code here
    // ...
  }
  // The three traversals below will neatly print to screen
  // the Pets’ names and ages in the respective order
  void inorder(TreeNode* root)
  {
    // add your code here
    // ...
  }
  void preorder(TreeNode* root)
  {
    // add your code here
    // ...
  }
  void postorder(TreeNode* root)
  {
    // add your code here
    // ...
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
    // display name of pet found or
    // message if not found
    // ...
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
  tree.insertNode(“Zelda”, 5);
  tree.insertNode(“Link”, 7);
  // etc ...
  // inorder display
  tree.inorderDisplay();
  // preorder display
  tree.preorderDisplay();
  // postorder display
  tree.postorderDisplay();
  // successful search
  tree.searchPet(7);
  // unsuccessful search
  tree.searchPet(100);  // assuming no Pet in your tree is aged 100
  return 0;
}
