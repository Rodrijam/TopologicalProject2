// File: LList2.hpp

#ifndef LLIST2_HPP
#define LLIST2_HPP
using namespace std;

enum dtype { FORWARD, BACKWARD };

template <class LT> class LList2;
template <class LT> ostream & operator << (ostream & outs, const LList2<LT> & L);

template <class LT>
class LList2
{
   private:
      struct LNode
      {
         LNode ();
		 void PrintNode (ostream & output);
         LT data;
         LNode * next;
		 LNode * prev;
      };
   public:
	  class Iterator
	  {
		public:
			Iterator ();
			Iterator (LNode * NP);
			LT & operator * () const;
			Iterator operator ++ ();
			Iterator operator ++ (int);
			Iterator operator -- ();
			Iterator operator -- (int);
			bool operator == (const Iterator & other) const;
			bool operator != (const Iterator & other) const;
		private:
			LNode * current;
	  };
      LList2 ();
      LList2 (const LList2 & other);
      ~LList2 ();
      LList2 & operator = (const LList2 & other);
      bool operator == (const LList2 & other);
      int Size () const;
	  void SetDirection (dtype dir);
	  dtype GetDirection () const;
      friend ostream & operator << <> (ostream & outs, const LList2<LT> & L);
      bool InsertFirst (const LT & value);
      bool InsertLast (const LT & value);
      bool DeleteFirst ();
      bool DeleteLast ();
	  void Forward (void function (const LT & param));
	  void Backward (void function (const LT & param));
	  Iterator begin () const;
	  Iterator rbegin () const;
	  Iterator end () const;
	  Iterator rend () const;
	  LT & operator [] (const int & index) const;
	  
   private:
      LNode * first;
	  LNode * last;
      int size;
	  dtype direction;
};

template <class LT>
LList2<LT>::LNode::LNode ()
{ 
	next = NULL;
	prev = NULL;
}

template <class LT>
void LList2<LT>::LNode::PrintNode (ostream & output)
{
	if (next != NULL)
		next->PrintNode (output);
	if (next != NULL)
		output << ' ';
	
	output << data;
}

template <class LT>
LList2<LT>::LList2 ()
{ 
	first = NULL;
	last = NULL;
	size = 0;
	direction = FORWARD;
}

template <class LT>
LList2<LT>::LList2 (const LList2 & other)
{
	first = NULL;
	size = 0;
	for (LNode * n = other.first; n!= NULL; n = n->next)
		InsertLast (n->data);
	direction = other.direction;
}

template <class LT>
LList2<LT>::~LList2 ()
{
	while (first)
		DeleteFirst();
}

template <class LT>
LList2<LT> & LList2<LT>::operator = (const LList2 & other)
{
	if (this == &other)
		return * this;
	while (first)
		DeleteFirst();
	for (LNode * n = other.first; n!= NULL; n = n->next)
		InsertLast( n->data );
	direction = other.direction;
	return * this;
}

template <class LT>
bool LList2<LT>::operator == (const LList2 & other)
{ 
	if (size != other.size)
		return false;
	LNode * n = first;
	LNode * m = other.first;
	while( n != NULL )
	{
		if (n->data != m->data)
			return false;
		n = n->next;
		m = m->next;
	}		
	return true;
}

template <class LT>
int LList2<LT>::Size () const
{ 
	return size;
}

template <class LT>
void LList2<LT>::SetDirection (dtype dir)
{
	direction = dir;
}

template <class LT>
dtype LList2<LT>::GetDirection () const
{
	return direction;
}

template <class LT>
ostream & operator << (ostream & outs, const LList2<LT> & L)
{
	if (L.first == NULL)
		return outs;
	if (L.direction == FORWARD)
	{
		outs << L.first->data;
		typename LList2<LT>::LNode * n;
		for (n = L.first->next; n != NULL; n = n->next)
			outs << ' ' << n->data;
	}
	else if (L.direction == BACKWARD)
	{
		outs << L.last->data;
		typename LList2<LT>::LNode * n;
		for (n = L.last->prev; n != NULL; n = n->prev)
			outs << ' ' << n->data;
	}
	return outs;
}

template <class LT>
bool LList2<LT>::InsertFirst (const LT & value)
{
	LNode * np = NULL;
	np = new LNode;
	if (np==NULL)
		return false;
	np->data = value;
	if (size ==0)
	{
		np -> next = NULL;
		np -> prev = NULL;
		first = np;
		last = np;
		size++;
		return true;
	}

	np->next = first;
	np->prev = NULL;
	first->prev = np;
	first = np;
	size++;
	return true;
}

template <class LT>
bool LList2<LT>::InsertLast (const LT & value)
{
	if (size == 0)
		return InsertFirst(value);
	LNode * np = new LNode;
	if (np==NULL)
		return false;
	np->data = value;
	np->prev = last;
	np->next = NULL;
	last ->next = np;
	last = np;
	
	size++;
	return true;
}


template <class LT>
bool LList2<LT>::DeleteFirst ()
{ 
	if (first == NULL)
		return false;
	if (size == 1)
	{
		delete first;
		first = NULL;
		last = NULL;
		size--;
		return true;
	}
	LNode * np = first;
	np->prev = NULL;
	first = first ->next;
	
	delete np;
	size--;
	return true;
}

template <class LT>
bool LList2<LT>::DeleteLast ()
{ 
	if (first == NULL)
		return false;
	if (size == 1)
		return DeleteFirst();
	LNode * np = last->prev;
	np -> next = NULL;
	delete last;
	last = np;
	size--;
	return true;
}

template <class LT>
void LList2<LT>::Forward (void function ( const LT & param))
{
	for (LNode * n = first; n != NULL; n = n->next)
		function (n->data);
}

template <class LT>
void LList2<LT>::Backward (void function ( const LT & param))
{
	for (LNode * n = last; n; n = n->prev)
		function (n->data);
}

template <class LT>
LList2<LT>::Iterator::Iterator()
{
	current = NULL;
}

template <class LT>
LList2<LT>::Iterator::Iterator(LNode * NP)
{
	current = NP;
}

template <class LT>
LT & LList2<LT>::Iterator::operator * () const
{
	try
	{
		if (current == NULL)
			throw ("Cannot dereference a NULL pointer");
		return current->data;
	}
	catch (const  char * message)
	{
		cerr << message << endl;
		exit(1);
	}

}

template <class LT>
typename LList2<LT>::Iterator LList2<LT>::Iterator::operator ++ ()
{
	try
	{
		if (current == NULL)
			throw ("Cannot increment a NULL pointer");
		current = current->next;
		return *this;
	}
	catch (const char * message)
	{
		cerr << message << endl;
		exit (2);
	}
}

template <class LT>
typename LList2<LT>::Iterator LList2<LT>::Iterator::operator ++ (int)
{
	try
	{
		if (current == NULL)
			throw ("Cannot post-increment a NULL pointer");
		Iterator temp = *this;
		current = current->next;
		return temp;
	}
	catch (const char * message)
	{
		cerr << message << endl;
		exit (6);
	}
}

template <class LT>
typename LList2<LT>::Iterator LList2<LT>::Iterator::operator -- ()
{
	try
	{
		if (current == NULL)
			throw ("Cannot decrement a NULL pointer");
		current = current->prev;
		return *this;
	}
	catch (const char * message)
	{
		cerr << message << endl;
		exit (5);
	}
}

template <class LT>
typename LList2<LT>::Iterator LList2<LT>::Iterator::operator -- (int)
{
{
	try
	{
		if (current == NULL)
			throw ("Cannot post-increment a NULL pointer");
		Iterator temp = *this;
		current = current->prev;
		return temp;
	}
	catch (const char * message)
	{
		cerr << message << endl;
		exit (4);
	}
}
}

template <class LT>
bool LList2<LT>::Iterator::operator == (const Iterator & other) const
{
	return current == other.current;
}

template <class LT>
bool LList2<LT>::Iterator::operator != (const Iterator & other) const
{
	return current != other.current;
}

template <class LT>
typename LList2<LT>::Iterator LList2<LT>::begin () const
{
	Iterator temp (first);
	return temp;
}

template <class LT>
typename LList2<LT>::Iterator LList2<LT>::rbegin () const
{
	Iterator temp (last);
	return temp;
}

template <class LT>
typename LList2<LT>::Iterator LList2<LT>::end () const
{
	Iterator temp;
	return temp;
}

template <class LT>
typename LList2<LT>::Iterator LList2<LT>::rend () const
{
	Iterator temp;
	return temp;
}

template <class LT>
LT & LList2<LT>::operator [] (const int & index) const
{
	try
	{
		if (size == 0)
			throw "You are indexing an empty list";
		if (index >= size)
			throw "Subscript out of bounds : index is too large";
		if (index < 0)
			throw index;
		LList2<LT>::LNode * n = first;
		for (int i = 0; i < index; i++)
			n = n-> next;
		return n->data;
	}
	catch (const char * message)
	{
		cerr << message << endl;
		exit(3);
	}
	catch (const int idx)
	{
		cerr << idx << "is not a valid index";
		exit (8);
	}
}

#endif