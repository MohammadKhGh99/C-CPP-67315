//
//#ifndef CPP2_RECOMMENDERSYSTEM_H
//#define CPP2_RECOMMENDERSYSTEM_H
//
//#include <fstream>
//#include <string>
//#include <iostream>
//#include <sstream>
//#include <iterator>
//#include <vector>
//#include <map>
//#include <cmath>
//#include <algorithm>
//
//
//#define USER_NOT_FOUND "USER NOT FOUND"
//
//
//
///**
// * a class to recommend movies to people depends on two different things
// * 1) by user old ratings
// * 2) by similar movies user watched
// */
//class RecommenderSystem
//{
//
//
//
//public:
//	/**
//	 * read the two files of info. about movies and user ratings
//	 * @param moviesAttributesFilePath the file path of the movies and its charactristic
//	 * @param userRanksFilePath the file path of user ranking movies
//	 * @return 0 on success, -1 on failure //todo not done yet
//	 */
//	int loadData(const std::string& moviesAttributesFilePath, const std::string& userRanksFilePath);
//
//	/**
//	 * recommend a movie to user depends on predicted scores for his movies
//	 * @param username the user we want to predict movies to
//	 * @param k number of movies to take in count
//	 * @return a movie name
//	 */
//	std::string recommendByCF(const std::string& username, int k);
//
//	/**
//	 * get suggested movie for user by his ratings on other movies
//	 * @param userName the user we want to suggest to him a movie
//	 * @return the name of the movie we suggest it to him to watch
//	 */
//	std::string recommendByContent(const std::string& userName);
//
//	/**
//	 * predict a ratings for a movie of user depends on similarity of ratings
//	 * @param movieName the movie we want to rate for user
//	 * @param userName the username
//	 * @param k how many movies to get in count
//	 * @return the rating for the unwatched movie
//	 */
//	double predictMovieScoreForUser(const std::string& movieName, const std::string& userName, int k);
//
//private:
//	//functions
//	int _putFileInMap(std::ifstream& fileStream, std::map<std::string, std::vector<int>>& mapToFill);
//	void _movieNamesIntoVector(std::string const& firstLine);
//	void _decAverageFromRatings(std::vector<double>& ratings);
//	void _getRatedVector(const std::string& userName, std::vector<double>& newVec , std::vector<std::string> &movies);
//	std::vector<double>_getTotalRating(const std::vector<double>& ratings, const std::vector<std::string>& moviesList);
//	double _getSimilarity(const std::vector<double>& firstVec, const std::vector<double>& secondVec);
//	std::string _findBestMovie(const std::vector<std::string>& moviesList, const std::vector<double>& preferVec);
//	void _getRatedVector(const std::string &userName, std::vector<std::pair<std::string, double>> &ratedMovies);
//	void _fillSimilarMovies(const std::string &movieName, std::vector<std::pair<std::string, double>> &ratedMovies);
//	void _sortByAscending(std::vector<std::pair<std::string, double>>& ratedMovies);
//	double _predictRating(const std::vector<std::pair<std::string, double>>& ratedMovies, int k, const std::string& username);
//	void _getUnratedVector(const std::string &userName, std::vector<std::string> &unratedMovies);
//
//	//fields
//	std::map<std::string, std::vector<int>> moviesRankings;
//	std::map<std::string, std::vector<int>> userRatings;
//	std::vector<std::string> moviesNames;
//	std::map<std::string, std::map<std::string, double>> similarityMoviesTable; //todo later
//};
//
//
//
//
//#endif //CPP2_RECOMMENDERSYSTEM_H
