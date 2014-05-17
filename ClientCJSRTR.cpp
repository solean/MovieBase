/* File "driver.cpp" written for Project 2 - CSE 250 Spring 2014
   Chris Schnabel and Robert Rymarczyk

   compile with command:
      g++ ClientCJSRTR.cpp MovieBaseCJS.h MovieBaseCJS.cpp userbaseRTR.h userbaseRTR.cpp
   then run: ./a.out to see output
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "MovieBaseCJS.h"
#include "userbaseRTR.h"
using namespace std;

int main() {
	UserBase u = UserBase();
	MovieBase m = MovieBase();
	cout << endl << "Reading user and movie databases:" << endl;
	m.readMovieFile("u.item");		//Task 1
	cout << "Movie file read." << endl;
	u.buildUserList();				//Task 2
	cout << "User file read." << endl;
	cout << "Reading ratings file, may take a while." << endl;
	u.readRatings(m);
	cout << "Done reading files." << endl;
	cout << endl;

	int user = 101; //arbitrary user index to use for demo, change to see diff outputs for diff users

	//Task 3 accomplished by MovieBase::setAvgRating, called during
	//process of readRatings() call. Can be accessed with Movie::getAvgRating

	//Task 4 (ug = average rating u(m) by user u of movies m that belong
	//to genre g) can be accessed by UserNode::getUserGenreAves. Demo:
	vector<float> userGenreAves = u.NodeByUsr(user)->getUserGenreAves();
	cout << "UserGenreAves for user # " << user << ": " << endl;
	for (int i = 0; i < userGenreAves.size(); i++) {
		cout << u.genreName(i) << ": " << userGenreAves.at(i) << endl;
	}

	//Task 5 and 6 accomplished by UserNode::calculateGenreAvePref, called
	//during process of readRatings() call. Access results with
	//UserNode::getUserGenrePref(). Demo:
	vector<float> userGenrePref = u.NodeByUsr(user)->getUserGenrePref();
	cout << endl << "UserGenrePref for user # " << user << ": " << endl;
	for (int j = 0; j < userGenrePref.size(); j++) {
		cout << u.genreName(j) << ": " << userGenrePref.at(j) << endl;
	}
	cout << endl;

	//Task 7: call MovieBase::topMovies, passing in the number of top
	//movies that you'd like to see, and the UserNode of the user for
	//the movies to be recommended to
	cout << "Top Movie Recommendations for user # " << user << ":" << endl;
	m.topMovies(10, u.NodeByUsr(user)); //this will print 10 movies to the console
	cout << endl;
}