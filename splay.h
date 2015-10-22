#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"


template <class KeyType, class ValueType>
class SplayTree : public BinarySearchTree<KeyType, ValueType>
{
  public:
  std::pair<const KeyType, ValueType> find (const KeyType & k)
  {
    if(this->root == NULL)
    {
      const KeyType n;
      ValueType s;
      std::pair<const KeyType, ValueType>nothere(n, s);
      return nothere;
    }
    bool find = false;
    Node<KeyType,ValueType>* temp = this->root;
    while(find == false)
    {
      if(temp->getKey() == k)
      {
        splayhelper(temp);
        return temp->getItem();
      }
      else
      {
        if(k < temp->getKey())
        {
          if(temp->getLeft() == NULL)
          {
            splayhelper(temp);
            const KeyType n;
            ValueType s;
            std::pair<const KeyType, ValueType>nothere(n, s);
            return nothere;
          }
          else
          {
            //std::cout<<"1"<<std::endl;
            temp = temp->getLeft();
          }

        }
        else if(k > temp->getKey())
        {
          if(temp->getRight() == NULL)
          {
            splayhelper(temp);
            const KeyType n;
            ValueType s;
            std::pair<const KeyType, ValueType>nothere(n, s);
            return nothere;
          }
          else
          {
            //std::cout<<"2"<<std::endl;
            temp = temp->getRight();
          }
        }
      }
    }
      const KeyType n;
      ValueType s;
      std::pair<const KeyType, ValueType>nothere(n, s);
      return nothere;
  }
  void insert (const std::pair<const KeyType, ValueType>& new_item)
  {
    Node<KeyType, ValueType>* check = this->internalFind(new_item.first);
    if(check != NULL)
    {
      check->setValue(new_item.second);
      return;
    }
    bool find = false;
    Node<KeyType, ValueType>* temp = this->root;
    if(this->root == NULL)
    {
      Node<KeyType, ValueType>* newnode = new Node<KeyType, ValueType>(new_item.first, new_item.second, NULL);
      this->root = newnode;
      splayhelper(newnode);
    }
    else
    {
      while(find == false)
      {
        if(new_item.first < temp->getKey())
        {
          if(temp->getLeft() == NULL)
          {
            Node<KeyType, ValueType>* newnode = new Node<KeyType, ValueType>(new_item.first, new_item.second, temp);
            temp->setLeft(newnode);
            splayhelper(newnode);
            find = true;
            break;
          }
          else
          {
            temp = temp->getLeft();
          }
        }
        else if(new_item.first > temp->getKey())
        {
          if(temp->getRight() == NULL)
          {
            Node<KeyType, ValueType>* newnode = new Node<KeyType, ValueType>(new_item.first, new_item.second, temp);
            temp->setRight(newnode);
            splayhelper(newnode);
            find = true;
            break;
          }
          else
          {
            temp = temp->getRight();
          }
        }
      }
    }
  }
  private:
  void splayhelper(Node<KeyType, ValueType>*& x)
  {
  	//root case
  	if(x->getParent() == NULL)
  	{
  		this->root = x;
  	}
  	//zig zig
  	else if(x->getParent()->getParent() != NULL && x->getParent()->getParent()->getLeft() != NULL && x->getParent()->getParent()->getLeft()->getLeft() == x)
  	{
  		Node<KeyType, ValueType>*daddy;
  		Node<KeyType, ValueType>*Gdaddy;
  		Node<KeyType, ValueType>*ancestor;
  		Node<KeyType, ValueType>*uncle;
  		daddy = x->getParent();
  		Gdaddy = x->getParent()->getParent(); 	
  		ancestor = x->getParent()->getParent()->getParent();
  		uncle = x->getParent()->getRight();
  		daddy->setLeft(x->getRight());
      if(x->getRight() != NULL)
      {
       x->getRight()->setParent(daddy);
      }
  		x->setRight(daddy);
  		daddy->setParent(x);
  		Gdaddy->setLeft(uncle);
      if(uncle != NULL)
      {
        uncle->setParent(Gdaddy);
      }
  		daddy->setRight(Gdaddy);
  		Gdaddy->setParent(daddy);
 	    if(ancestor != NULL)
	    {
	      if(ancestor->getRight() == Gdaddy)
	      {
	        ancestor->setRight(x);
	      }
	      else
	      {
	        ancestor->setLeft(x);
	      }
	    }
	    x->setParent(ancestor);
	    splayhelper(x);
  	}
  	//zig zig
  	else if(x->getParent()->getParent() != NULL && x->getParent()->getParent()->getRight() != NULL && x->getParent()->getParent()->getRight()->getRight() == x)
  	{  	
      Node<KeyType, ValueType>*daddy;
  		Node<KeyType, ValueType>*Gdaddy;
  		Node<KeyType, ValueType>*ancestor;
  		Node<KeyType, ValueType>*uncle;
  		daddy = x->getParent();
  		Gdaddy = x->getParent()->getParent(); 	
  		ancestor = x->getParent()->getParent()->getParent();
  		uncle = x->getParent()->getLeft();
  		daddy->setRight(x->getLeft());
      if(x->getLeft() != NULL)
      {
        x->getLeft()->setParent(daddy);
      }
  		x->setLeft(daddy);
  		daddy->setParent(x);
  		Gdaddy->setRight(uncle);
      if(uncle != NULL)
      {
        uncle->setParent(Gdaddy);
      }
  		daddy->setLeft(Gdaddy);
  		Gdaddy->setParent(daddy);
 	    if(ancestor != NULL)
	    {
	      if(ancestor->getRight() == Gdaddy)
	      {
	        ancestor->setRight(x);
	      }
	      else
	      {
	        ancestor->setLeft(x);
	      }
	    }
	    x->setParent(ancestor);
	    splayhelper(x);

  	}
  	//zig zag
  	else if(x->getParent()->getParent() != NULL && x->getParent()->getParent()->getLeft() != NULL && x->getParent()->getParent()->getLeft()->getRight() == x)
  	{  	
  		Node<KeyType, ValueType>*daddy;
  		Node<KeyType, ValueType>*Gdaddy;
  		Node<KeyType, ValueType>*ancestor;
  		Node<KeyType, ValueType>*b;
  		Node<KeyType, ValueType>*c;
  		daddy = x->getParent();
  		Gdaddy = x->getParent()->getParent(); 	
  		ancestor = x->getParent()->getParent()->getParent();
  		b = x->getLeft();
  		c = x->getRight();
  		x->setLeft(daddy);
  		x->setRight(Gdaddy);
  		daddy->setParent(x);
  		Gdaddy->setParent(x);
  		daddy->setRight(b);
      if(b != NULL)
      {
        b->setParent(daddy);
      }
  		Gdaddy->setLeft(c);
      if(c != NULL)
      {
        c->setParent(Gdaddy);
      }
 	    if(ancestor != NULL)
	    {
	      if(ancestor->getRight() == Gdaddy)
	      {
	        ancestor->setRight(x);
	      }
	      else
	      {
	        ancestor->setLeft(x);
	      }
	    }
	    x->setParent(ancestor);
	    splayhelper(x);
  	}
   	//zig zag
  	else if(x->getParent()->getParent() != NULL && x->getParent()->getParent()->getRight() != NULL && x->getParent()->getParent()->getRight()->getLeft() == x)
  	{
  		Node<KeyType, ValueType>*daddy;
  		Node<KeyType, ValueType>*Gdaddy;
  		Node<KeyType, ValueType>*ancestor;
  		Node<KeyType, ValueType>*b;
  		Node<KeyType, ValueType>*c;
  		daddy = x->getParent();
  		Gdaddy = x->getParent()->getParent(); 	
  		ancestor = x->getParent()->getParent()->getParent();
  		b = x->getLeft();
  		c = x->getRight();
  		x->setRight(daddy);
  		x->setLeft(Gdaddy);
  		daddy->setParent(x);
  		Gdaddy->setParent(x);
  		daddy->setLeft(c);
      if(c != NULL)
      {
        c->setParent(daddy);
      }
  		Gdaddy->setRight(b);
      if(b != NULL)
      {
        b->setParent(Gdaddy);
      }
 	    if(ancestor != NULL)
	    {
	      if(ancestor->getRight() == Gdaddy)
	      {
	        ancestor->setRight(x);
	      }
	      else
	      {
	        ancestor->setLeft(x);
	      }
	    }
	    x->setParent(ancestor);
	    splayhelper(x);
  	}
  	else if(x->getParent() == this->root && x->getParent()->getRight() == x)
  	{
	    x->getParent()->setRight(x->getLeft());
      if(x->getLeft() != NULL)
      {
        x->getLeft()->setParent(x->getParent());
      }
	    x->setLeft(x->getParent());
	    x->getParent()->setParent(x);
	    x->setParent(NULL);
	    splayhelper(x);
  	}
  	else if(x->getParent() == this->root && x->getParent()->getLeft() == x)
  	{
	    x->getParent()->setLeft(x->getRight());// take b's right to c's left
      if(x->getRight() != NULL)
      {
        x->getRight()->setParent(x->getParent());
      }
	    x->setRight(x->getParent());// set b's right to parent
	    x->getParent()->setParent(x);//set c's parent to b
	    x->setParent(NULL);
	    splayhelper(x);
  	}
  }


};