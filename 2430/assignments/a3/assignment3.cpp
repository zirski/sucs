// TODO!!!!!!!
// Destroy not working
// Treeheight not tested
// balance not tested
// Delete node not tested
// Parent not working

#include <iostream>

#include "shelterBST.h"

using namespace std;

int main()
{
  ShelterBST tree;
  int choice;

  do {
    cout << "Welcome to my implementation of ShelterBST" << endl;
    cout << "Please choose the operation you want" << endl;
    cout << "1. Insert a node" << endl;
    cout << "2. Search a value" << endl;
    cout << "3. Inorder" << endl;
    cout << "4. Preorder" << endl;
    cout << "5. Postorder" << endl;
    cout << "6. The parent of a node" << endl;
    cout << "7. The predecessor of a node" << endl;
    cout << "8. Number of nodes in the tree" << endl;
    cout << "9. Number of internal nodes in the tree" << endl;
    cout << "10. Number of Nodes at a level" << endl;
    cout << "11. Tree height" << endl;
    cout << "12. Is it balanced?" << endl;
    cout << "13. Delete a node" << endl;
    cout << "14. Destroy the tree" << endl;
    cout << "15. Run tests (Erases all changes!)" << endl;
    cout << "16. Exit" << endl;
    cout << ":";

    cin >> choice;

    switch (choice) {
      case 1: {
        string name;
        int age;
        cout << "Enter the name of the pet you would like to add: ";
        cin >> name;
        cout << "Enter its age: ";
        cin >> age;
        tree.insertPet(name, age);
        cout << "Pet " << name << ", age " << age << " added." << endl;
        break;
      }
      case 2: {
        string name;
        cout << "Enter the name of the pet you would like to search for: ";
        cin >> name;
        tree.searchPet(name);
        break;
      }
      case 3:
        tree.inorderDisplay();
        break;
      case 4:
        tree.preorderDisplay();
        break;
      case 5:
        tree.postorderDisplay();
        break;
      case 6: {
        string name;
        cout << "Enter the name of the node whose parent you wish to find: ";
        cin >> name;
        tree.displayParent(name);
        break;
      }
      case 7: {
        string name;
        cout << "Enter the name of the node whose predecessor you wish to "
                "find: ";
        cin >> name;
        tree.displayPredecessor(name);
        break;
      }
      case 8:
        tree.displayNumNodes();
        break;
      case 9:
        tree.displayNumInternalNodes();
        break;
      case 10: {
        int level;
        cout << "Enter the level whose amount of nodes you wish to know: ";
        cin >> level;
        tree.displayNumNodesAtLevel(level);
        break;
      }
      case 11:
        tree.displayTreeHeight();
        break;
      case 12:
        tree.displayBalance();
        break;
      case 13: {
        string name;
        cout << "Please enter the name of the node you want to delete: ";
        cin >> name;
        tree.deletePet(name);
        break;
      }
      case 14:
        tree.destroyTree();
        break;
      case 15:
        tree.test();
        break;
    }
  } while (choice != 16);
  return 0;
}
