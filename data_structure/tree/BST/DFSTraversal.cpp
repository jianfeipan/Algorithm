class InOderTraversal
{
private:
  void inOrderTraversalHelper(std::vector<int> & result, TreeNode * root)
  {
      if(root == nullptr)
      {
        return;
      }
      inOrderTraversalHelper(result, root->left);
      result.push_back(root->val);
      inOrderTraversalHelper(result, root->right);//same idea for other orders
  }
public:
  std::vector<int> getInOrderTraversal(TreeNode * root)
  {
    std::vector<int> result;
    inOrderTraversalHelper(result, root);
    return result;
  }
  
  //print code simpler than pushing into a vector
  void printIneorder(TreeNode * root)
  {
    if(root)
    {
      //print(root->val);//preOrder print here 
      printIneorder(root->left);
      print(root->val);
      printIneorder(root->right);
      //print(root->val);//postOrder print here 
    }
  }
  
  //Norecusive means you need your onw stack to replace the call stack, in the stack, you need all the root of  sub tree
  void printInorderNoRecusive(TreeNode * root)
  {
    if(root)
    {
      std::Stack<TreeNode*> stack;
      TreeNode * current = root;
      
      while(current!=nullptr || !stack.empty())
      {
        //first step is to push all sub tree root on left to go down
        while(current!=nullptr)
        {
          stack.push(current); 
          currenct = current->left;
        }
        
        //here means the current node doesn't have a left child, and here current == nullptr, we can start to go up now
        if(!stack.empty())
        {
          current = stack.pop();
          
          print(current->val);//inorder means LNR: print this most left node
          
          current = current->right; //try to loop current's right child
          
        }
      }
    }
  }
  
  //PreorderNorecusive is very similar to the printInorderNoRecusive, just change the place to print the root
  void printPreorderNoRecusive(TreeNode * root)
  {
    if(root)
    {
      std::Stack<TreeNode*> stack;
      TreeNode * current = root;
      
      while(current!=nullptr || !stack.empty())
      {
        //first step is to push all sub tree root on left to go down
        while(current!=nullptr)
        {
          print(current->val);//preOrder means NLR: print this root first
          stack.push(current); 
          currenct = current->left;
        }
        
        //here means the current node doesn't have a left child, and here current == nullptr, we can start to go up now
        if(!stack.empty())
        {
          current = stack.pop();          
          current = current->right; //try to loop current's right child
        }
      }
    }
  }
  
  
  //PostorderNorecusive (LRN) is different from the two others: because your root if printed after the right one.
  //so when you pop a root, how do you make sure : 
  //  now you need to print root because the right branch is looped  
  //  or you just printed the left one and now you need to loop on right branch --> solution is to have a flag to note looped right node
  void printPostOrderNoRecusive(TreeNode * root)
  {
    if(root)
    {
      std::Stack<TreeNode*> stack;
      TreeNode * current = root;
      
      while(current!=nullptr || !stack.empty())
      {
        //first step is to push all sub tree root on left to go down
        while(current!=nullptr)
        {
          stack.push(current); 
          currenct = current->left;
        }
        
        //here means the current node doesn't have a left child, and here current == nullptr, we can start to go up now
        
        current = stack.top();

        // right side is not looped, here we need to loop right branch
        if(current->right!=nullptr && current->right!=loopedRoot)
        {
            current = current->right;
            stack.push(current);
            current = current->left;
        }
        else//doesn't have right branch of right branch is looped, now we should print root
        {
            result.push_back(current->val);
            stack.pop();
            loopedRoot = current;
            current = nullptr;//avoid to go back to push left while loop
        }
      }
    }
  }
  
}
