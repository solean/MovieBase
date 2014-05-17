/*  userbase.h file by RTR for Spring 2014 CSE250.
    Class headers for UserBase and UserNode classes,
    as well as declarations of useful structs.
*/
#ifndef USERBASE_H__
#define USERBASE_H__
class UserBase;
class UserNode;
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include "MovieBaseCJS.h"

using namespace std;

//helper structs:
struct userDem									//struct holds individual user's demographics
{  int userNum;
   int age;
   bool male;									//boolean value if user is male
   string occ;
   int zip;	
};
struct mr										//struct stores the two data elements 
{  int movie;									//in each vector index for movieratings 
   int rating;
   bool genre[6];
   mr();
};
//class UserNode:
class UserNode
{  UserNode* prev;								//prev UserNode used for iterator
   UserNode* lc;								//left child UserNode
   UserNode* rc;								//right child UserNode
   userDem myDem;								//user's demographics

   vector<mr*> movieratings;					//vector of movie ratings, rated 1-5
   vector<vector<int> > userGenrerate;			//vector of ratings by user sorted into genres 0-5
   vector<float> userGenreAves;					//vector holds floats of averages of ratings by user in genres
   vector<float> userGenrePref;					//user's genre preference factor
   //genre indexes: [0]=Action, [1]=Noir, [2]=Light, [3]=Serious, [4]=Fantasy, [5]=History   

   friend class UserBase;
   friend class MovieBase;

public:
   UserNode();									//default constructor
   UserNode(userDem d, UserNode* p, UserNode* left, UserNode* right);//overloaded argument constructor
   void calculateGenreAvePref(MovieBase& m,UserBase* u);	//calculates values of user average genre ranks and preferences
   vector<mr*> getMovieRatings();				//returns vector of user's movie ratings
   vector<float> getUserGenreAves();			//returns vector of user's average genre ratings
   vector<float> getUserGenrePref();			//returns vector of user's preference factor
   vector<vector<int> > getUserGenrerate();
   bool operator==(const UserNode& rhs);		//overloaded bool operations
   bool operator!=(const UserNode& rhs);
};
//class UserBase:
class UserBase
{  UserNode* nill;								//null UserNode
   UserNode* head;								//head UserNode
   UserNode* term;								//terminal UserNode, not necessary per se, but it helps. 
												//points to "bottom right" most UserNode in tree
   size_t numNodes;
   vector<vector<int> > genreRate();			//vector of all user submitted ratings sorted into genres 0-5
   vector<float> genreAves;						//vector holds floats of averages ratings by users in genres
   //genre indexes: [0]=Action, [1]=Noir, [2]=Light, [3]=Serious, [4]=Fantasy, [5]=History   

   friend class UserNode;
   friend class MovieBase;								//may be unnecessary?   

public:
   UserBase();											//default constructor

   class iterator	//iterator subclass 
   {  const UserBase* myUser;			
      UserNode* curr;				
      stack<UserNode*> itstack;
      friend class UserBase;
      friend class UserNode;
      iterator(const UserBase* in, UserNode* ent);		//constructor
   public:
      UserNode* operator*();							//returns curr
      iterator& operator++();							//increment operators
      iterator& operator++(int ignored);
      bool operator==(const iterator& rhs);				//overloaded bool operations
      bool operator!=(const iterator& rhs);
   };

   iterator begin();									//iterator to first element
   iterator end();										//returns iterator to "nill" UserNode
   UserNode* insertUser(userDem U,UserNode* n);			//inserts user into structure to the right of node n
   void addReview(mr* x, int un);						//inserts new user rating into existing user
   UserNode* NodeByUsr(int usrId);
   void balance();
   void rot(int s);
   void rotleft(UserNode* gparent, UserNode* parent, UserNode* child);
   
//the rest of the functions are used to read the files:
   bool buildUserList();								//builds the user list from the user file
   bool readRatings(MovieBase& m);						//reads ratings from ratings file
   void print();
   string genreName(int n);         //utilized for info purposes in driver
};
#endif
