/*  userbase.cpp file by RTR for Spring 2014 CSE250.
    Implementation for UserNode and UserBase classes 
    and associated functions.                     */

#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "userbaseRTR.h"		//?
//#include "moviebaseCJS.h"		//unnecessary? 

using namespace std;

mr::mr()						//sets default state for mr struct to be NULL
{  movie=rating=0;
   for(int i=0; i<6; i++)
	   genre[i]=false;
}

///UserNode CLASS
UserNode::UserNode()
{  prev=NULL;
   rc=NULL;
   lc=NULL;
   myDem.userNum=0;
   myDem.age=0;
   myDem.male=false;			//boolean value if user is male
   myDem.occ=" ";
   myDem.zip=0;
}

UserNode::UserNode(userDem d, UserNode* p, UserNode* left, UserNode* right)
{  myDem.userNum=d.userNum;
   myDem.age=d.age;
   myDem.male=d.male;
   myDem.occ=d.occ;
   myDem.zip=d.zip;
   prev=p;
   lc=left;
   rc=right;
   userGenrerate = vector<vector<int> >(6);
}

void UserNode::calculateGenreAvePref(MovieBase& m,UserBase* u)
{  userGenreAves.clear();
   userGenrePref.clear();
   vector<vector<float> > overallForRatedMovies;
   
   //cout << "setting movie average ratings" << endl;

   //cout << "calling setAvgRating..." << endl;
   m.setAvgRating(u);
   //cout << "ratings set" << endl;
   
   //cin.ignore();

   for (int z=0; z<6; z++)			//populates vector with 6 vectors of ints
   {  vector<float> ins;
      overallForRatedMovies.push_back(ins);
   }
   //cout << movieratings.size() << " = movieratings.size()" << endl;
   //cout << userGenrerate.size() << " = userGenrerate.size()" << endl;
   for (int i=0; i<movieratings.size();i++)														//loops through all of user's reviews
   {  if(((movieratings.at(i))->genre[0]) == true)												//tests for which genre to put scores into
      {  userGenrerate.at(0).push_back((movieratings.at(i))->rating);					//score added to appropriate genre table
         overallForRatedMovies.at(0).push_back(((m.movies)->at(i).avgRating));
      }
      if(((movieratings.at(i))->genre[1]) == true)
      {  userGenrerate.at(1).push_back((movieratings.at(i))->rating);  
         overallForRatedMovies.at(1).push_back(((m.movies)->at(i).avgRating));
      }
      if(((movieratings.at(i))->genre[2]) == true)    
      {  userGenrerate.at(2).push_back((movieratings.at(i))->rating);
         overallForRatedMovies[2].push_back(((m.movies)->at(i).avgRating));   
      }
      if(((movieratings.at(i))->genre[3]) == true)
      {  userGenrerate.at(3).push_back((movieratings.at(i))->rating); 
         overallForRatedMovies.at(3).push_back(((m.movies)->at(i).avgRating));
      }
      if(((movieratings.at(i))->genre[4]) == true)
      {  userGenrerate.at(4).push_back((movieratings.at(i))->rating);
         overallForRatedMovies.at(4).push_back((((m.movies)->at(i).avgRating)));  
      }
      if(((movieratings.at(i))->genre[5]) == true)
      {  userGenrerate.at(5).push_back((movieratings.at(i))->rating);
         overallForRatedMovies.at(5).push_back((((m.movies)->at(i).avgRating)));  
      }
   }
   //cout << "genre loop done" << endl;
   float ua=0;
   /*ua=ua/userGenrerate.at(0).size();				//takes the averages of them
   userGenreAves.push_back(ua);

   //float ua=0;  moved above because otherwise it's undeclared for above 2 lines
   for (int i=0; i < userGenrerate.at(0).size(); i++)
      ua+=userGenrerate.at(0).at(i);				//loop adds up all values of individual user ratings
   float ga=0;
   ga=ga/userGenrerate.at(0).size();								//calculates average for genre by allusers
   userGenrePref.push_back((ua/ga));								//and pushes the ratio into the vector of preference factors
   */
   float ga=0;
   for (int i = 0; i < userGenrerate.at(0).size(); i++) {
      ua+=userGenrerate.at(0).at(i);
      ga+=overallForRatedMovies.at(0).at(i);
   }
   ua=ua/userGenrerate.at(0).size();
   userGenreAves.push_back(ua);
   ga=ga/userGenrerate.at(0).size();
   userGenrePref.push_back((ua/ga));


   ua=ga=0;
   for (int i=0; i < userGenrerate.at(1).size(); i++)
   {  ua+=userGenrerate.at(1).at(i);
      ga+=overallForRatedMovies.at(1).at(i);
   }
   ua=ua/userGenrerate.at(1).size();
   userGenreAves.push_back(ua);
   ga=ga/userGenrerate.at(1).size();
   userGenrePref.push_back((ua/ga));
   
   ua=ga=0;
   for (int i=0; i < userGenrerate.at(2).size(); i++)
   {  ua+=userGenrerate.at(2).at(i);
      ga+=overallForRatedMovies.at(2).at(i);
   }
   ua=ua/userGenrerate.at(2).size();
   userGenreAves.push_back(ua);
   ga=ga/userGenrerate.at(2).size();
   userGenrePref.push_back((ua/ga));
   
   ua=ga=0;
   for (int i=0; i < userGenrerate.at(3).size(); i++)
   {  ua+=userGenrerate.at(3).at(i);
      ga+=overallForRatedMovies.at(3).at(i);
   }
   ua=ua/userGenrerate.at(3).size();
   userGenreAves.push_back(ua);
   ga=ga/userGenrerate.at(3).size();
   userGenrePref.push_back((ua/ga));
   
   ua=ga=0;
   for (int i=0; i < userGenrerate.at(4).size(); i++)
   {  ua+=userGenrerate.at(4).at(i);
      ga+=overallForRatedMovies.at(4).at(i);
   }
   ua=ua/userGenrerate.at(4).size();
   userGenreAves.push_back(ua);
   ga=ga/userGenrerate.at(4).size();
   userGenrePref.push_back((ua/ga));
   
   ua=ga=0;
   for (int i=0; i < userGenrerate.at(5).size(); i++)
   {  ua+=userGenrerate.at(5).at(i);
      ga+=overallForRatedMovies.at(5).at(i);
   }
   ua=ua/userGenrerate.at(5).size();
   userGenreAves.push_back(ua);
   ga=ga/userGenrerate.at(5).size();
   userGenrePref.push_back((ua/ga));
}

vector<mr*> UserNode::getMovieRatings()
{  return movieratings;   }

vector<float> UserNode::getUserGenreAves()
{  return userGenreAves;   }

vector<float> UserNode::getUserGenrePref()
{  return userGenrePref;   }
vector<vector<int> > UserNode::getUserGenrerate()
{  return userGenrerate;}

bool UserNode::operator==(const UserNode& rhs)	
{  return (prev==rhs.prev&&lc==rhs.lc&&rc==rhs.rc);  }

bool UserNode::operator!=(const UserNode& rhs)
{  return (!(*this==rhs));  }

///////////////////////////////////////////////////////////////////////////////////////////
///UserBase CLASS
UserBase::UserBase()
{  nill = new UserNode();
   nill->rc=nill;
   nill->lc=nill;
   head = nill;
   numNodes=0;
}

UserBase::iterator::iterator(const UserBase* in, UserNode* ent)
{  myUser=in;
   UserNode* h = in->head;
   if (ent==in->nill)			//null iterator
   {  curr=in->nill;
      return;
   }
   while (h!=in->nill)			//return iterator to first element in tree
   {  itstack.push(h);
      h=h->lc;
   }
   if (itstack.size()>0)
   {  curr = itstack.top();
      itstack.pop();
   }
   else
	   curr = in->nill;
}

UserNode* UserBase::iterator::operator*()
{  return curr;  }

UserBase::iterator& UserBase::iterator::operator++()
{  if (curr->rc!=myUser->nill)
   {  itstack.push(curr->rc);
      UserNode* temp = curr->rc;
	  while (temp->lc!=myUser->nill)
	  {  itstack.push(temp->lc);
		 temp=temp->lc;
      }
   }
   if (itstack.size() == 0 )
   {  curr=myUser->nill;
      return *this;
   }
   curr = itstack.top();
   itstack.pop();
   return *this;
}//thanks to the prev* field in the node structure, the ++ operator runs at O(1) 

UserBase::iterator& UserBase::iterator::operator++(int ignored)
{  iterator* copy = this;
   copy->operator++();
   return *copy;
}

bool UserBase::iterator::operator==(const iterator& rhs)
{  return (curr==rhs.curr&&myUser==rhs.myUser);   }

bool UserBase::iterator::operator!=(const iterator& rhs)
{  return (!(*this==rhs));   }

UserBase::iterator UserBase::begin()			//beginning node iterator
{  return iterator(this,head);
}

UserBase::iterator UserBase::end()			//end iterator
{  return iterator(this,nill);   }

UserNode* UserBase::insertUser(userDem d,UserNode* n)	
//inserts new node to the furthest right-most point from input node n
{  if (head==nill)
   {  head=NULL;
      head=new UserNode(d,nill,nill,nill);
      numNodes++;
	  return head;
   }
   else
   {  if (n->rc!=nill)			//if not nill
         while(n->rc!=nill)		//traverse to furthest right from n
            n=n->rc;
      n->rc=NULL;
      n->rc=new UserNode(d,n,nill,nill);		//new node inserted as right child
      numNodes++;
	  return n->rc;
   }
   return head;					//returns head by default.
}

void UserBase::addReview(mr* x, int un)
{  UserNode* trace=NodeByUsr(un);				//gets node for user number
   trace->movieratings.push_back(x);			//adds review to user's review vector
}

UserNode* UserBase::NodeByUsr(int usrId)
{  for (UserBase::iterator i=UserBase::begin(); i!=UserBase::end();i++)
      if ((*i)->myDem.userNum == usrId)
         return *i;
   cerr << "Could not find UserNumber " << usrId << endl;
   return *(end());				
}			//////////function avg case log(n), worst n

void UserBase::balance()
//Adapted from Day, Stout, Warren Algorithm for converting a degenerate binary tree
//into a balanced binary tree
{  int size=numNodes;
   float ln = ( (log(float(size))) / (log(float(2)))) ;
   int m(ln);
   rot(size-m);
   while (m>1)
	   rot(m/=2);
}

void UserBase::rot(int s)
{  UserNode* gp = nill;
   UserNode* p = head;
   UserNode* c = head->rc;

   for ( ;s>0;s--)		//while in bounds
   {  if(nill != c)		//if there's a right child, rotate it left
      {   rotleft(gp,p,c);
          gp=c;
          p=gp->rc;
          c=p->rc;
      } 
      else						//if cannot test, then break loop
         break;
   }
}

void UserBase::rotleft(UserNode* gparent, UserNode* parent, UserNode* child)
{  if(nill!=gparent)			//if not pointing to head of tree
   {  gparent->rc = child;		//gparent rotates 
      child->prev = gparent;
   }
   else
      head = child;				//otherwise the right node takes on the head position

   parent->rc = child->lc;		//the parent is moved left
   parent->rc->prev = parent;

   child->lc = parent;			//and the right node is moved up.
   parent->prev = child;
}

bool UserBase::buildUserList()	
//fnc returns bool if was successful in reading file
{  ifstream inFile;
   string in;
   UserNode* unp=head;
   
   inFile.open("u.user",ios_base::in);	//opens hard coded filename
   if (!inFile.is_open())				//test if open
   {  cerr << "Failed to open u.user file." << endl;
      return false;
   }

   while (inFile>>in)					//reads items from files
   {  userDem d;						//userDem & incoming string declared in while loop to avoid having to void it out
      string::iterator it=in.begin();
      string unum,age,sex,zip;

      while((*(it))!='|')				//reads usernumber
         unum+=*it++;
      it++;								//it++'s in this section skip '|'s
      while((*(it))!='|')				//reads age
         age+=*it++;
      it++;
      while((*(it))!='|')				//reads gender
         sex+=*it++;
      it++;
      while((*(it))!='|')				//reads occupation
         d.occ+=*it++;
      it++;
      while(it!=in.end())				//reads zipcode
         zip+=*it++;

      if(sex=="M"||sex=="m")			//sets gender.  false by default, so no additional considerations needed.
         d.male=true;         

      stringstream uconvert(unum);		
      stringstream aconvert(age);
      stringstream zconvert(zip);		//stringstreams used to convert 
      uconvert>>d.userNum;				//strings to ints
      aconvert>>d.age;
      zconvert>>d.zip;

	  unp=insertUser (d,unp);			//inserts user into the array
	  in ="";
   }

   UserNode* temp=head;
   while (temp->rc!=nill)		//resets terminal value of tree to right most node from head.
	   temp=temp->rc;
   term=temp;

   balance();					//sorts tree into balanced BST
   inFile.close();				//closes inFile
   return true;   
}			

bool UserBase::readRatings(MovieBase& m)
{  ifstream inFile;
   mr* mov;
   string in;
   int unum=0;

   inFile.open("u.data",ios_base::in);
   if (!inFile.is_open())				//test if open
   {  cerr << "Failed to open u.data file." << endl;
      return false;
   }

   while (inFile>>in)					//while goes thorugh whole file, copies user number
   {  mov = new mr;
      stringstream uconvert(in);		//stringstream for converting strings to ints
      inFile>>in;						//reads movie number
      stringstream mconvert(in);
      inFile>>in;						//reads user rating
      stringstream rconvert(in);
      inFile>>in;		
      uconvert >> unum;					//sets values of variables
      mconvert >> mov->movie;
      rconvert >> mov->rating;

	  Movie* temp = &(m.movies->at((mov->movie)-1));
	  if(temp->index == (mov->movie))
      {  if(temp->genres->at(1)==1||temp->genres->at(2)==1||temp->genres->at(16)==1||temp->genres->at(18)==1)
            mov->genre[0]=true;
         if(temp->genres->at(6)==1||temp->genres->at(10)==1||temp->genres->at(11)==1||temp->genres->at(13)==1)
            mov->genre[1]=true;
         if(temp->genres->at(3)==1||temp->genres->at(4)==1||temp->genres->at(5)==1||temp->genres->at(12)==1)
            mov->genre[2]=true;
		 if(temp->genres->at(8)==1||temp->genres->at(14)==1)
            mov->genre[3]=true;
         if(temp->genres->at(9)==1||temp->genres->at(15)==1)
            mov->genre[4]=true;
         if(temp->genres->at(7)==1||temp->genres->at(17)==1)
            mov->genre[5]=true;
      }
      addReview(mov,unum);			//adds review to node
   }


   for(iterator i=begin();i!=end();i++)		//calculates the final genre preference factors
      (*i)->calculateGenreAvePref(m,this);

   inFile.close();
   return true;
}

string UserBase::genreName(int n)
{  vector<string> v;
   v.push_back("Action"); v.push_back("Noir"); v.push_back("Light");
   v.push_back("Serious"); v.push_back("Fantasy"); v.push_back("History");
   return v.at(n);
}

void UserBase::print()
{   int j=0;
    cout << "Head = " << head->myDem.userNum << ", lc = " << head->lc->myDem.userNum << ", and rc = " << head->rc->myDem.userNum << endl;
	for (UserBase::iterator i=begin();i!=UserBase::end();i++)
    {   cout << (*i)->myDem.userNum << endl;
	    if (!((j++)%10))
			cin.ignore();
	}
cin.ignore();
}
