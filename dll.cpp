#include <iostream>
#include <cstdlib>
using namespace std;

// An Atom is just the thing that the list element points to... it could be anything
class Atom
{
public:
  char * getValue();
  void setValue( char * );
  Atom( char * );
  Atom(void);
  Atom(const Atom& obj);
  ~Atom();
private:
  char * value;
};

char * Atom::getValue()
{
#ifdef DEBUG
  cerr << "[char * Atom::getValue()]\t\t[" << value << "]" << endl;
#endif  
  return value;
}
void Atom::setValue( char * v )
{
#ifdef DEBUG
  cerr << "[void Atom::setValue( " << v << " )]" << endl;
#endif  
  value=v;
}
Atom::Atom( void )
{
#ifdef DEBUG
  cerr << "[Atom::Atom( void )]" << endl;
#endif  
  value=(char*)"[empty]";
}
Atom::Atom( char * v )
{
#ifdef DEBUG
  cerr << "[Atom::Atom( char * v )]\t\t[" << v << "]" << endl;
#endif  
  setValue(v);
}
Atom::~Atom()
{
#ifdef DEBUG
  cerr << "[Atom::~Atom()]" << endl;
#endif  
  value=NULL;
}
Atom::Atom(const Atom& obj)
{
#ifdef DEBUG
  cerr << "[Atom::Atom(const Atom& obj)]" << endl;
#endif  
  *value = *obj.value;
}

// This is an element of the list
// it should point to the previous element (if there is one)
// and the next element (if there is one);
class element
{
public:
  void setNext( element * e );
  void setPrevious( element * e );
  element * getNext();
  element * getPrevious();
  Atom * getAtom();
  ~element();
  element( Atom * i );

  // copy onstructor
  element(const element& obj);

private:  
  element();

  element * pNextElement;
  element * pPreviousElement;
  Atom * pMyAtom;
};

element::element()
{
#ifdef DEBUG
  cerr << "[element::element()]" << endl;
#endif  
}

element::element(const element& obj)
{
#ifdef DEBUG
  cerr << "[element::element(const element& obj)]" << endl;
#endif  
  // Copy Constructor
  pNextElement = new element();
  *pNextElement = *obj.pNextElement;
  pPreviousElement = new element();
  *pPreviousElement = *obj.pPreviousElement;
  pMyAtom = new Atom();
  *pMyAtom = *obj.pMyAtom;
}

Atom * element::getAtom()
{
#ifdef DEBUG
  cerr << "[Atom * element::getAtom()]" << endl;
#endif  
  return pMyAtom;
}
element::element( Atom * i )
{
#ifdef DEBUG
  cerr << "[element::element( Atom * i )]" << endl;
#endif  
  pMyAtom=i;
}
element::~element()
{
#ifdef DEBUG
  cerr << "[element::~element()]" << endl;
#endif  
  delete pMyAtom;
}
void element::setNext( element * e )
{
#ifdef DEBUG
  cerr << "[void element::setNext( element * e )]" << endl;
#endif  
  pNextElement = e;
}
void element::setPrevious( element * e )
{
#ifdef DEBUG
  cerr << "[void element::setPrevious( element * e )]" << endl;
#endif  
  pPreviousElement = e;
}
element * element::getNext()
{
#ifdef DEBUG
  cerr << "[element * element::getNext()]" << endl;
#endif  
  return pNextElement;
}
element * element::getPrevious()
{
#ifdef DEBUG
  cerr << "[element * element::getPrevious()]" << endl;
#endif  
  return pPreviousElement;
}

class dll
{
public:
  void add( element * e );
  void del( int i );
  element * getElement( int i );
  ~dll();
  void dump();
  int getSize();
  void insert( int i, element * e );
private:
  element * first;
  element * last;

};

// Insert as the ith element
void dll::insert( int i, element * e )
{
#ifdef DEBUG
  cerr << "[void dll::insert( int i, element * e )]" << endl;
#endif  

  if( i == getSize() + 1 )
    {
      add( e );
      return;
    }
  
  if( i > getSize() ) return;
  
  element * oldi = getElement(i);
  oldi->getPrevious()->setNext( e );
  if( i==1 )
    {
      e->setPrevious(NULL);
    }
  else
    {
      e->setPrevious( oldi->getPrevious() );
    }
  e->setNext( oldi );
  oldi->setPrevious( e );
}

int dll::getSize()
{
#ifdef DEBUG
  cerr << "[int dll::getSize()]" << endl;
#endif  

  int size=0;
  element * f = first;
  while( f )
    {
      size++;
      f=f->getNext();
    }
  return( size );
}

element * dll::getElement( int i )
{
#ifdef DEBUG
  cerr << "[element * dll::getElement( int i )]" << endl;
#endif  

  // if the user asks for an element beyond the size of the list, return NULL
  if( i > getSize() ) return(NULL);

  i--;
  int count=0;
  element * f=first;
  while(f!=NULL)
    {
      if( count == i )
	{
	  return f;
	}
      else
	{
	  f=f->getNext();
	  count++;
	}
    }
}

void dll::dump()
{
#ifdef DEBUG
  cerr << "[void dll::dump()]" << endl;
#endif  

  // This prints out the value of each Atom that is in the linked list.
  element * f=first;
  while( f!=NULL)
    {
      cerr << "[" << f->getAtom()->getValue() << "]" << endl;
      f=f->getNext();
    }
}

dll::~dll()
{
#ifdef DEBUG
  cerr << "[dll::~dll()]" << endl;
#endif  

  element * d=NULL;
  element * f=first;
  while( f!=NULL )
    {
      d=f->getNext();
      delete f;
      f=d;
    }
}

void dll::add( element * e )
{
#ifdef DEBUG
  cerr << "[void dll::add( element * e )]" << endl;
#endif  

  if( getSize()<=0 )
    {
      // then it's the first element
      first=e;
      last=e;
      e->setNext(NULL);
      e->setPrevious(NULL);
    }
  else
    {
      last->setNext( e );
      e->setNext( NULL );
      e->setPrevious( last );
      last=e;
    }
}

void dll::del( int i )
{
#ifdef DEBUG
  cerr << "[void dll::del( int i )]" << endl;
#endif  

  if( getSize()<i )
    {
      return;
    }
  else
    {
      int count=0;
      i--;
      element * to_be_deleted=first;
      while( to_be_deleted!=NULL)
	{
	  if( count++ == i )
	    {
	      if( to_be_deleted->getNext() == NULL )
		{
		  to_be_deleted->getPrevious()->setNext( NULL );
		}
	      else
		{
		  to_be_deleted->getNext()->setPrevious( to_be_deleted->getPrevious() );
		  to_be_deleted->getPrevious()->setNext( to_be_deleted->getNext() );
		}
	      delete to_be_deleted;
	    }
	  to_be_deleted=to_be_deleted->getNext();
	}
    }
}

// -------------------------------------------------------
int main()
{
#ifdef DEBUG
  cerr << "[PROGRAM IS IN DEBUG MODE]" << endl;
#endif  

  dll * myList = new dll();
  myList->add( new element( new Atom( (char*)"I" )));
  myList->add( new element( new Atom( (char*)"II" )));
  myList->add( new element( new Atom( (char*)"III" )));
  myList->add( new element( new Atom( (char*)"IV" )));
  myList->add( new element( new Atom( (char*)"V" )));
  myList->add( new element( new Atom( (char*)"VI" )));
  myList->add( new element( new Atom( (char*)"VII" )));
  myList->add( new element( new Atom( (char*)"VIII" )));
  myList->add( new element( new Atom( (char*)"IX" )));
  myList->add( new element( new Atom( (char*)"X" )));
  myList->dump();

  cout << "======" << endl;

  myList->del(4);
  myList->del(7);
  myList->dump();

  cout << "======" << endl;
  myList->insert( 3, new element( new Atom( (char*)"***" )));
  myList->insert( 3, new element( new Atom( (char*)"222222" )));
  myList->insert( 10, new element( new Atom( (char*)"ten ten ten" )));
  myList->insert( 12, new element( new Atom( (char*)">>END<<" )));
  myList->insert( 12, new element( new Atom( (char*)"-- not quite the end --" )));

  myList->dump();
  delete myList;
#ifdef DEBUG
  cerr << "[END OF PROGRAM]" << endl;
#endif  

  return( 0 );
}
