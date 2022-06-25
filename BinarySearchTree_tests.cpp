// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"


TEST(test_stub) {
    // Add your tests here
    ASSERT_TRUE(true);
}

TEST_MAIN()

TEST(empty_size_height_testing)
{
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty() == true);
    ASSERT_TRUE(tree.height() == 0);
    ASSERT_TRUE(tree.size() == 0);
    
    tree.insert(5);
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    tree.insert(10);
    tree.insert(9);
    tree.insert(11);
    ASSERT_TRUE(tree.empty() == false);
    ASSERT_TRUE(tree.height() == 3);
    ASSERT_TRUE(tree.size() == 7);
    ASSERT_TRUE(tree.check_sorting_invariant());
    std::ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    std::cout << "preorder" << std::endl;
    std::cout << oss_preorder.str() << std::endl << std::endl;
    ASSERT_TRUE(oss_preorder.str() == "5 3 2 4 10 9 11 ");
    
    std::ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    std::cout << "inorder" << std::endl;
    std::cout << oss_inorder.str() << std::endl << std::endl;
    ASSERT_TRUE(oss_inorder.str() == "2 3 4 5 9 10 11 ");
    ASSERT_TRUE(*tree.max_element() == 11);
    ASSERT_TRUE(*tree.min_element() == 2);
    ASSERT_TRUE(*tree.min_greater_than(5) == 9);
    
    ASSERT_TRUE(tree.find(5) != tree.end());
    ASSERT_TRUE(tree.find(100) == tree.end());
}

TEST(height_edge_case)
{
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty() == true);
    ASSERT_TRUE(tree.height() == 0);
    ASSERT_TRUE(tree.size() == 0);
    
    BinarySearchTree<int> tree1;
    tree = tree1;
    
    
    tree.insert(10);
    tree.insert(7);
    tree.insert(6);
    tree.insert(3);
    tree.insert(4);
    tree.insert(9);
    tree.insert(8);
    tree.insert(15);
    tree.insert(14);
    tree.insert(18);
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_TRUE(tree.find(3) == tree.begin());
    ASSERT_TRUE(tree.find(4) == ++tree.begin());
    ASSERT_TRUE(tree.find(6) == ++++tree.begin());
    ASSERT_TRUE(tree.find(7) == ++++++tree.begin());
    ASSERT_TRUE(tree.find(8) == ++++++++tree.begin());
    ASSERT_TRUE(tree.find(9) == ++++++++++tree.begin());
    ASSERT_TRUE(tree.find(10) == ++++++++++++tree.begin());
    ASSERT_TRUE(tree.find(14) == ++++++++++++++tree.begin());
    ASSERT_TRUE(tree.find(15) == ++++++++++++++++tree.begin());
    ASSERT_TRUE(tree.find(18) == ++++++++++++++++++tree.begin());
    ASSERT_TRUE(tree.empty() == false);
    ASSERT_TRUE(tree.height() == 5);
    ASSERT_TRUE(tree.size() == 10);
    
    std::ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    std::cout << "preorder" << std::endl;
    std::cout << oss_preorder.str() << std::endl << std::endl;
    ASSERT_TRUE(oss_preorder.str() == "10 7 6 3 4 9 8 15 14 18 ");
    ASSERT_TRUE(*tree.max_element() == 18);
    ASSERT_TRUE(*tree.min_element() == 3);
    ASSERT_TRUE(*tree.min_greater_than(5) == 6);
    
    std::ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    std::cout << "inorder" << std::endl;
    std::cout << oss_inorder.str() << std::endl << std::endl;
    ASSERT_TRUE(oss_inorder.str() == "3 4 6 7 8 9 10 14 15 18 ");
    
    BinarySearchTree<int> tree_copy;
    
    tree_copy = tree;
    ASSERT_TRUE(tree_copy.empty() == false);
    ASSERT_TRUE(tree_copy.height() == 5);
    ASSERT_TRUE(tree_copy.size() == 10);
    ASSERT_TRUE(*tree_copy.max_element() == 18);
    ASSERT_TRUE(*tree_copy.min_element() == 3);
    ASSERT_TRUE(*tree_copy.min_greater_than(5) == 6);
    ASSERT_TRUE(*tree_copy.min_greater_than(10) == 14);
    ASSERT_TRUE(*tree_copy.min_greater_than(15) == 18);
    ASSERT_TRUE(tree_copy.min_greater_than(18) == tree.end());
    
    std::ostringstream oss_preorder_copy;
    tree_copy.traverse_preorder(oss_preorder_copy);
    std::cout << "preorder" << std::endl;
    std::cout << oss_preorder_copy.str() << std::endl << std::endl;
    ASSERT_TRUE(oss_preorder_copy.str() == "10 7 6 3 4 9 8 15 14 18 ");
    
    std::ostringstream oss_inorder_copy;
    tree.traverse_inorder(oss_inorder_copy);
    std::cout << "inorder" << std::endl;
    std::cout << oss_inorder_copy.str() << std::endl << std::endl;
    ASSERT_TRUE(oss_inorder.str() == "3 4 6 7 8 9 10 14 15 18 ");
}

TEST(checking_insorting_variant1)
{
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty() == true);
    ASSERT_TRUE(tree.height() == 0);
    ASSERT_TRUE(tree.size() == 0);
    
    tree.insert(10);
    tree.insert(7);
    tree.insert(6);
    tree.insert(3);
    tree.insert(4);
    tree.insert(9);
    tree.insert(8);
    tree.insert(15);
    tree.insert(14);
    tree.insert(18);
    
    *tree.begin() = 11;
    ASSERT_FALSE(tree.check_sorting_invariant());
    *tree.begin() = 3;
    ASSERT_TRUE(tree.check_sorting_invariant());
    *(++++++++++++tree.begin()) = 4;
    ASSERT_FALSE(tree.check_sorting_invariant());

}

TEST(checking_insorting_variant2)
{
    BinarySearchTree<int> tree1;
    
    tree1.insert(10);
    tree1.insert(7);
    tree1.insert(9);
    tree1.insert(3);
    tree1.insert(8);
    tree1.insert(15);
    tree1.insert(78);
    tree1.insert(90);
    *(++++++++++++tree1.begin()) = 2;
    ASSERT_FALSE(tree1.check_sorting_invariant());
}

TEST(test_stub1) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_TRUE(tree.size() == 0);
    ASSERT_TRUE(tree.height() == 0);
    tree.insert(5);
    ASSERT_TRUE(tree.size() == 1);
    ASSERT_TRUE(tree.height() == 1);
    tree.insert(7);
    ASSERT_TRUE(tree.height() == 2);
    tree.insert(1);
    ASSERT_TRUE(tree.height() == 2);
    tree.insert(2);
    ASSERT_TRUE(tree.height() == 3);
    tree.insert(3);
    ASSERT_TRUE(tree.height() == 4);
    ASSERT_TRUE(tree.size() == 5);
    tree.insert(6);
    ASSERT_TRUE(tree.height() == 4);
    ASSERT_TRUE(*tree.min_greater_than(-4) == 1);
    ASSERT_TRUE(*tree.min_greater_than(1) == 2);
    ASSERT_TRUE(*tree.min_greater_than(2) == 3);
    ASSERT_TRUE(*tree.min_greater_than(3) == 5);
    ASSERT_TRUE(*tree.min_greater_than(4) == 5);
    ASSERT_TRUE(*tree.min_greater_than(5) == 6);
    ASSERT_TRUE(*tree.min_greater_than(6) == 7);
    ASSERT_TRUE(tree.min_greater_than(7) == tree.end());
    ASSERT_TRUE(tree.check_sorting_invariant());
    tree.insert(9);
    tree.insert(-1);
    std::cout << tree.to_string() << std::endl << std::endl;
    std::ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    std::cout << "preorder" << std::endl;
    std::cout << oss_preorder.str() << std::endl << std::endl;
    ASSERT_TRUE(oss_preorder.str() == "5 1 -1 2 3 7 6 9 ");

    std::ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    std::cout << "inorder" << std::endl;
    std::cout << oss_inorder.str() << std::endl << std::endl;
    ASSERT_TRUE(oss_inorder.str() == "-1 1 2 3 5 6 7 9 ");
    
    
// test copy constructor
    BinarySearchTree<int> tree1(tree);
    ASSERT_TRUE(tree1.height() == 4);
    ASSERT_TRUE(tree1.size() == 8);
    ASSERT_TRUE(tree1.check_sorting_invariant());
    
    
    ASSERT_TRUE(tree.find(-1) == tree.begin());
    ASSERT_TRUE(tree.find(2) == ++++tree.begin());
    ASSERT_TRUE(tree.find(3) == ++++++tree.begin());
    
    ASSERT_TRUE(*tree.min_element() == -1);
    ASSERT_TRUE(*tree.max_element() == 9);
    
    
    
    
    BinarySearchTree<int> tree2;
    ASSERT_TRUE(tree2.size() == 0);
    ASSERT_TRUE(tree2.min_greater_than(-100) == tree2.end());
    //std::cout << *tree.min_element();
    ASSERT_TRUE(tree2.min_element() == tree2.end());
    tree2.insert(-8);
    ASSERT_TRUE(*tree2.min_element() == -8);
    ASSERT_TRUE(*tree2.max_element() == -8);
    ASSERT_TRUE(*tree2.min_greater_than(-10) == -8);
    ASSERT_TRUE(tree2.min_greater_than(5) == tree2.end());
    ASSERT_TRUE(tree2.check_sorting_invariant());
    std::ostringstream oss_preorder2;
    tree2.traverse_preorder(oss_preorder2);
    std::cout << "preorder" << std::endl;
    std::cout << oss_preorder2.str() << std::endl << std::endl;
    ASSERT_TRUE(oss_preorder2.str() == "-8 ");

    std::ostringstream oss_inorder2;
    tree2.traverse_inorder(oss_inorder2);
    std::cout << "inorder" << std::endl;
    std::cout << oss_inorder2.str() << std::endl << std::endl;
    ASSERT_TRUE(oss_inorder2.str() == "-8 ");
    
}

TEST(test_check_invariant){
    BinarySearchTree<int> tree;
    tree.insert(100);
    tree.insert(1000);
    tree.insert(0);
    tree.insert(2000);
    tree.insert(-1);
    tree.insert(5);
    *tree.begin() = 2;
    ASSERT_TRUE(!tree.check_sorting_invariant());
    
}
TEST(test_check_invariant1){
    BinarySearchTree<int> tree;
    tree.insert(100);
    tree.insert(1000);
    tree.insert(0);
    tree.insert(2000);
    tree.insert(-1);
    tree.insert(5);
    *++++++++++tree.begin() = 999;
    std::cout << tree.to_string() << std::endl << std::endl;
    std::cout << tree.check_sorting_invariant();
    ASSERT_TRUE(!tree.check_sorting_invariant());
    
}

TEST(test_check_invariant2){
    BinarySearchTree<int> tree;
    tree.insert(100);
    tree.insert(1000);
    tree.insert(0);
    tree.insert(2000);
    tree.insert(-1);
    tree.insert(5);
    *++++tree.begin() = 500;
    //std::cout << tree.to_string() << std::endl << std::endl;
    //std::cout << tree.check_sorting_invariant();
    ASSERT_TRUE(!tree.check_sorting_invariant());
    
}
