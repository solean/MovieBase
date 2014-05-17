/** File "MovieBaseCJS.cpp", by Chris Schnabel, for CSE 250 Project #2, Spring 2014.

*/

#include "MovieBaseCJS.h"
//#include "userbase.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

/*using std::vector;
using std::string;
using std::stringstream;
using std::cout;
using std::endl;*/
using namespace std;

// MOVIE CLASS /////////////////////////////////////////////////

Movie::Movie(int i, string t, int y, vector<int>* g) 
	: index(i)
	, title(t)
	, year(y)
	, genres(g)
	, avgRating(1.0)
	, numOfRatings(0)
	, coeff(0)
{ }

float Movie::getAvgRating() { return Movie::avgRating; }
int Movie::getNumOfRatings() { return Movie::numOfRatings; }
void Movie::setAvgRating(float newAvg ) { Movie::avgRating = newAvg; }
void Movie::setNumOfRatings(int n) { Movie::numOfRatings = n; }
vector<int> Movie::broadGenres() {
	vector<int> v;
	vector<int>* g = this->genres;
	if (g->at(1)==1 || g->at(2)==1 || g->at(16)==1 || g->at(18)==1) {
		v.push_back(0); //0 represents that the Movie is genre "Action"
	} if (g->at(6)==1 || g->at(10)==1 || g->at(11)==1 || g->at(13)==1) {
		v.push_back(1); //1 represents the genre "Noir"
	} if (g->at(3)==1 || g->at(4)==1 || g->at(5)==1 || g->at(12)==1) {
		v.push_back(2); //2 represents the genre "Light"
	} if (g->at(8)==1 || g->at(14)==1) {
		v.push_back(3); //3 represents the genre "Serious"
	}if (g->at(15)==1 || g->at(9)==1) {
		v.push_back(4); //4 represents the genre "Fantasy"
	}if (g->at(17)==1 || g->at(7)==1) {
		v.push_back(5); //5 represents the genre "History"
	}
	return v;
}

// MOVIEBASE CLASS ////////////////////////////////////////////

MovieBase::MovieBase() : movies(new vector<Movie>()) { }

MovieBase::~MovieBase() { delete(movies); }

/**
This method takes the name of a file, reads each 
line (assuming it is formatted like "u.item"), and
creates a new Movie object for each entry and adds
them to the movies vector.
*/
void MovieBase::readMovieFile(string filename) {

	std::ifstream infile(filename.c_str());

	for (string line; getline(infile, line);) {
		string::iterator it = line.begin();
		string index = "";
		string title = "";
		string year = "";
		vector<int>* genres = new vector<int>();

		//parse line to get index in string
		while ((*(it)) != '|') {
			index += *it;
			it++;
		}
		//convert index to int from string
		int i;
		stringstream convert(index);
		if (!(convert >> i)) {i = 0;}
		it++;
		//parse line to get title of movie
		while ((*(it)) != '|') {
			title += *it;
			it++;
		}
		year = title.substr(title.size() - 5, 4); //parse year of release from the title
		title.erase(title.size() - 7); //remove the year from the title
		//convert year to int (date)
		int date;
		stringstream convert2(year);
		if (!(convert2 >> date)) {date = 0;}

		//advance iterator past release date of video (don't need)
		it++;
		while ((*(it)) != '|') {
			it++;
		}
		//advance iterator past imdb url (don't need)
		it++; it++;
		while ((*(it)) != '|') {
			it++;
		}

		it++;
		//add the genre "bits" to a vector
		for (int i = 0; i <= 36; i++) {
			if ((*(it)) != '|') {
				int n = ((*it) - '0') % 48; //convert from char to int
				genres->push_back(n);
			}
			it++;
		}

		//create a Movie object with the appropriate fields
		Movie thisMovie = Movie(i, title, date, genres);
		//add Movie object to vector of movies
		movies->push_back(thisMovie);
	}
}


/*
Use a UserBase to set the average rating for each Movie
in MovieBase.
*/
void MovieBase::setAvgRating(UserBase* ub) { //UserBase::UserBase?
	//UserBase::iterator it = ub->begin();
	//cout << "beginning..." << endl;
	for (UserBase::iterator it = ub->begin(); it != ub->end(); it++) { //iterate through users
		vector<mr*> movieRatings = (*it)->getMovieRatings(); //getMovieRatings to access vector<mr*> movieratings from UserNode
		for (int i = 0; i < movieRatings.size(); i++) { //loop through movies that this user has rated
			mr* currentRating = movieRatings.at(i);
			Movie* thisMovie = &movies->at(currentRating->movie - 1);
			if (thisMovie->numOfRatings == 0) {
				thisMovie->avgRating = currentRating->rating;
				thisMovie->numOfRatings++;
				//cout << "First rating updated." << endl;

			} else {
				float newAvgRating = ((thisMovie->avgRating * thisMovie->numOfRatings) + currentRating->rating) / (thisMovie->numOfRatings + 1);
				thisMovie->avgRating = newAvgRating;
				thisMovie->numOfRatings++;
				//cout << "Rating updated." << endl;
			}
		}
	}
}

vector<Movie> MovieBase::topMovies(int n, UserNode* un) {
	vector<Movie> top;
	vector<float> userGenrePref = un->getUserGenrePref();
	top.push_back(movies->at(0)); //now 1 movie in top
	for (int i = 1; i < movies->size(); i++) {
		vector<int> g = movies->at(i).broadGenres();
		float coeff = 0;
		for (int j = 0; j < g.size(); j++) {
			if ((userGenrePref.at(g.at(j)) * movies->at(i).getAvgRating()) > coeff) {
				coeff = userGenrePref.at(g.at(j)) * movies->at(i).getAvgRating();
			}
		}
		movies->at(i).coeff = coeff;
		if (movies->at(i).numOfRatings >= 10) { //filter out movies with low amt of ratings
			top.push_back(movies->at(i));		
		}
	}
	sort(top.begin(), top.end(), coeffCompare);
	top.erase(top.begin() + n, top.end());
	for (int k = 0; k < top.size(); k++) {
		cout << top.at(k).title << "   (coefficient: " << top.at(k).coeff << " )" << endl;
	}
	return top;
}

bool MovieBase::coeffCompare (const Movie& a, const Movie& b) {
	return a.coeff > b.coeff;
}

/**
Finds and returns a Movie object given the movie number.
*/
Movie MovieBase::getMovie (int movieNumber) {
	return movies->at(movieNumber - 1);
}


