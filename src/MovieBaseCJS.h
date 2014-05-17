/** File "MovieBaseCJS.h", by Chris Schnabel, for CSE 250 Project #2, Spring 2014.

*/

#ifndef MOVIEBASECJS_H_
#define MOVIEBASECJS_H_
class MovieBase;
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "userbaseRTR.h"


/*using std::vector;
using std::string;
using std::stringstream;
using std::cout;
using std::endl;*/
using namespace std;

class Movie {
	//friend class UserBase;
	//friend class UserNode;
  public: 
	int index;
	string title;
	int year;
	vector<int>* genres;
	float avgRating;
	int numOfRatings;
	float coeff;			//coefficient for Task 7 (movie recommendations)

	//constructor
	Movie(int i, string t, int y, vector<int>* g);

	//getters and setters for some fields of Movie
	float getAvgRating();
	int getNumOfRatings();
	void setAvgRating(float newAvg);
	void setNumOfRatings(int n);
	vector<int> broadGenres(); 		//get Movie's broad genres (0-5)
};


class MovieBase {
	vector<Movie>* movies;
	friend class UserBase;
	friend class UserNode;

  public:
  	//constructor
	MovieBase();

	//destructor
	virtual ~MovieBase();

	/**
	This method takes the name of a file, reads each 
	line (assuming it is formatted like "u.item"), and
	creates a new Movie object for each entry and adds
	them to the movies vector.
	*/
	void readMovieFile(string filename);

	/*
	Use a UserBase to set the average rating for each Movie
	in MovieBase.
	*/
	void setAvgRating(UserBase* ub);

	/*
	Finds n top movies for a user, described by Task 7 in handout
	*/
	vector<Movie> topMovies(int n, UserNode* un);

	/*
	Helper method for topMovies sort, compares coeff of two movies
	*/
	static bool coeffCompare(const Movie& a, const Movie& b) ;

	/**
	Finds and returns a Movie object given the movie number.
	*/
	Movie getMovie (int movieNumber);

};

#endif
