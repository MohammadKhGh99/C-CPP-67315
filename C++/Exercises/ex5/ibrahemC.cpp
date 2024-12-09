//
//#include <chrono>
//#include "ibrahem.h"
//#define NA -10
//#define EXIT_FAIL -1
//#define FILE_ERROR "Unable to open file "
//#define ILLEGAL_ERROR "illegal input"
//
///**
// * read the two files of info. about movies and user ratings
// * @param moviesAttributesFilePath the file path of the movies and its charactristic
// * @param userRanksFilePath the file path of user ranking movies
// * @return 0 on success, -1 on failure //todo not done yet
// */
//int RecommenderSystem::loadData(const std::string& moviesAttributesFilePath, const std::string& userRanksFilePath)
//{
//
//	std::ifstream moviesFile(moviesAttributesFilePath); // declaring an ifstream first file
//
//	if(!moviesFile.is_open())
//	{
//		std::cout << FILE_ERROR << moviesAttributesFilePath << std::endl;
//		return EXIT_FAIL;
//	}
//
//	std::ifstream ratingsFile(userRanksFilePath); // declaring an ifstream second file
//	if(!ratingsFile.is_open())
//	{
//		std::cout << FILE_ERROR << userRanksFilePath << std::endl;
//		return EXIT_FAIL;
//	}
//
//
//	if(moviesFile.is_open() && ratingsFile.is_open())
//	{
//		//handeling first file
//
//		_putFileInMap(moviesFile, moviesRankings);
//
////        std::cout << std::endl << "movies rating size: " << moviesRankings.size() << std::endl ;
//
//
//		//handeling second file
//		//handling first line alone (from second file)
//		std::string line;
//		std::getline(ratingsFile, line);
//		_movieNamesIntoVector(line);
////        std::cout << std::endl << "movies name size: " << moviesNames.size() << std::endl ;
//
//		//handeling second file (second line to the end)
//		_putFileInMap(ratingsFile, userRatings);
//
//		moviesFile.close();
//		ratingsFile.close();
//
//		return EXIT_SUCCESS;
//	}
//
//	return EXIT_FAIL;
//}
//
///**
// * add file data in a map
// * @param fileStream the datastream we want to add to the map
// * @param mapToFill the map we want to fill with data from file
// * @return //todo check what return.. when false/true
// */
//int RecommenderSystem::_putFileInMap(std::ifstream& fileStream, std::map<std::string, std::vector<int>> &mapToFill)
//{
//	std::string line;
//	int index2 = 0;
//	while (std::getline(fileStream, line))
//	{
//		std::istringstream iss(line);
//		std::string mapKey;
//		std::vector<int> mapValue;
//		std::string temp;
//
//		//get movie name (mapKey)
//		iss >> mapKey;
//
//		//add ratings to vector (if NA put 0 else the number)
//		int index = 0;
//		while(!iss.eof())
//		{
//			index++;
//			iss >> temp;
//			if(temp == "NA")
//			{
//				mapValue.push_back(NA);
//			}
//			else
//			{
//				mapValue.push_back(stoi(temp));
//			}
//		}
////        std::cout << mapValue.size() << ":before " << std::endl ;
//		mapValue.pop_back();
////        std::cout << mapValue.size() << ":after " << std::endl ;
//
////        std::cout << index2 << ":" << (index) << std::endl ;
//		mapToFill[mapKey] = mapValue;
//		index2++;
//	}
//	return 0;
//}
//
///**
// * split a string by space and add each elemenet in list
// * @param firstLine the string we want to split
// * @return 0 in success, -1 otherwise
// */
//void RecommenderSystem::_movieNamesIntoVector(std::string const& firstLine)
//{
//	std::istringstream iss(firstLine);
//	std::string s;
//	while (std::getline( iss, s, ' ' ))
//	{
//		if(s.back() == '\r')
//		{
//			s.erase(s.size()-1);
//		}
//		moviesNames.push_back(s);
//	}
//}
//
///**
// * get suggested movie for user by his ratings on other movies
// * @param userName the user we want to suggest to him a movie
// * @return the name of the movie we suggest it to him to watch
// */
//std::string RecommenderSystem::recommendByContent(const std::string& userName)
//{
//	auto search = userRatings.find(userName);
//	if(search != userRatings.end())
//	{
//		//check if userRating is the same size as movies ratings
//		if(moviesRankings.size() != userRatings[userName].size())
//		{
////            std::cout << moviesRankings.size() << " " <<  userRatings[userName].at(750) << std::endl;
//			return ILLEGAL_ERROR;
//		}
//
//		//creating RatingVec and movieList for rated movies by user
//		std::vector<double> newVec;
//		std::vector<std::string> moviesList;
//		_getRatedVector(userName, newVec, moviesList);
//
//
//		//decrease average from ratings of movies
//		_decAverageFromRatings(newVec);
//
//		// get prefer vector of movies based on prev ratings
//		std::vector<double> preferVec = _getTotalRating(newVec, moviesList);
//
//		//get best movie:
//		return _findBestMovie(moviesList, preferVec);
//	}
//	else
//	{
////        std::cout << "1 did you enter?" << std::endl;
//		return USER_NOT_FOUND;
//	}
//}
//
///**
// * fill a list and a vector with rated movies and its rating by user.
// * @param userName the user we want to get his ratings
// * @param newVec the vector we want to fill the ratings into
// * @param movies the list we want to fill the rated movies into
// */
//void RecommenderSystem::_getRatedVector(const std::string& userName, std::vector<double>& newVec, std::vector<std::string> &movies)
//{
//	std::vector ratings = userRatings[userName];
//	int indexOfMovie = 0;
//	for (auto& num : ratings)
//	{
//		if (num != NA)
//		{
//			newVec.push_back(num);
//			movies.push_back(moviesNames[indexOfMovie]);
//		}
//		indexOfMovie++;
//	}
//}
//
///**
// * decrease the ratings in vector by average
// * @param ratings - the vector of ratings we want to change
// */
//void RecommenderSystem::_decAverageFromRatings(std::vector<double>& ratings)
//{
//	double sum, count;
//	for (auto& num : ratings)
//	{
//		sum += num;
//		count ++;
//	}
//	double average = ((sum*1.0) / count);
//
//	for (double& rating : ratings)
//	{
//		rating -= average;
//	}
//}
//
///**
// * get prefer ratings of genres of movies based on before ratings
// * @param ratings the vector of ratings for watch movies
// * @param moviesList a vector of movies that the user rated
// * @return prefer ratings of genres of movies
// */
//std::vector<double> RecommenderSystem::_getTotalRating(const std::vector<double>& ratings, const std::vector<std::string>& moviesList)
//{
//	//create answer vector
//	std::vector<double> answer ;
//	answer = std::vector<double>(moviesRankings[moviesList.at(0)].size()) ;
//
//	//loop over the ratings the user rated
//	for(size_t i = 0; i < ratings.size(); i++)
//	{
//		std::vector movieRating = moviesRankings[moviesList.at(i)];
//		for(size_t element = 0; element < movieRating.size(); element++)
//		{
//			movieRating.at(element) *= ratings.at(i);
//			answer.at(element) += movieRating.at(element);
//		}
//	}
//	return answer;
//}
//
///**
// * check how much similar the two vectors are
// * @param firstVec the first vector we want to check similiraty with
// * @param secondVec the second vector we want to check similiraty with
// * @return similraty ration
// */
//double RecommenderSystem::_getSimilarity(const std::vector<double>& firstVec, const std::vector<double>& secondVec)
//{
//	double vecMul = 0;
//	double firstNormal = 0;
//	double secondNormal = 0;
//	for(size_t i = 0; i < firstVec.size(); i++)
//	{
//		vecMul += firstVec.at(i)*secondVec.at(i);
//		firstNormal += firstVec.at(i)*firstVec.at(i);
//		secondNormal += secondVec.at(i)*secondVec.at(i);
//	}
//
//	firstNormal = sqrt(firstNormal);
//	secondNormal = sqrt(secondNormal);
//
//	return (vecMul / (firstNormal*secondNormal));
//}
//
//std::string RecommenderSystem::_findBestMovie(const std::vector<std::string>& moviesList, const std::vector<double>& preferVec)
//{
//	std::string bestMovie;
//	double bestRating = INTMAX_MIN;
//	int i = 0;
//	for(auto& movie: moviesNames)
//	{
//		//if the movie not rated
////        std::cout << "movie name: " << movie << "num: " << i << std::endl;
//		if(!std::count(moviesList.begin(), moviesList.end(), movie))
//		{
//			std::vector<double> doubleVec;
//			doubleVec = std::vector<double>(moviesRankings[movie].begin(), moviesRankings[movie].end());
//			double temp = _getSimilarity(preferVec, doubleVec);
//			//todo check above if you can cast less letters
//			if(temp > bestRating)
//			{
//				bestRating = temp;
//				bestMovie = movie;
//			}
//		}
//		i++;
//	}
//	return bestMovie;
//}
//
///**
// * predict a ratings for a movie of user depends on similarity of ratings
// * @param movieName the movie we want to rate for user
// * @param userName the username
// * @param k how many movies to get in count
// * @return the rating for the unwatched movie
// */
//double RecommenderSystem::predictMovieScoreForUser(const std::string &movieName, const std::string &userName, int k)
//{
//	auto searchUN = userRatings.find(userName);
//	auto searchMovie = std::find(moviesNames.begin(), moviesNames.end(), movieName);
//
////    auto searchUN = std::find(userRatings.begin(), userRatings.end(), userName);
////    std::cout << moviesNames.at(999) << std::endl ;
//
//	if(searchUN != userRatings.end() && searchMovie != moviesNames.end())
//	{
////        std::cout << moviesNames.at(999) << std::endl ;
//
//		std::vector<std::pair<std::string, double>> ratedMovies;
//		//check if userRating is the same size as movies
//		if(moviesRankings.size() != userRatings[userName].size())
//		{
//			return EXIT_FAIL;
//		}
//		//get ratedMovies
//		_getRatedVector(userName, ratedMovies);
//
//
//		//check movies similarity with a given movie, and add similarity to ratedMovies vector pair
//		_fillSimilarMovies(movieName, ratedMovies);
//
//
//		//sort the rated vector by its similarity rating
//		_sortByAscending(ratedMovies);
//
//
//
//		//predict the rating of the movies
//
//		double predict = _predictRating(ratedMovies, k, userName);
//
//
//
////        ratedMovies.clear();
//		return predict;
//	}
//	else
//	{
//		//userName or movieName not found
////        std::cout << "3 did you enter?" << std::endl;
//		return EXIT_FAIL;
//	}
//
//}
//
///**
// * fill a list and a vector with rated movies .
// * @param userName the user we want to get his rated movies
// * @param ratedMovies vector we want to fill the rated movies into
// */
//void RecommenderSystem::_getRatedVector(const std::string &userName, std::vector<std::pair<std::string, double>> &ratedMovies)
//{
//	std::vector ratings = userRatings[userName];
//	int indexOfMovie = 0;
//	for (auto& num : ratings)
//	{
//		if (num != NA)
//		{
//			ratedMovies.emplace_back(moviesNames[indexOfMovie], 0);
//		}
//		indexOfMovie++;
//	}
//}
//
///**
// * check a given movie similraties to given vector of movies and fill it in a map, and put similarity in vector pair
// * @param movieName the movie we want to check other movies similarities
// * @param ratedMovies vector of movies we want to check how similar to a given movie, and put the similarity in his pair
// */
//void RecommenderSystem::_fillSimilarMovies(const std::string &movieName, std::vector<std::pair<std::string, double>> &ratedMovies)
//{
//	int index = 0;
//	for(auto& ratedMovie: ratedMovies)
//	{
//		double ratio = similarityMoviesTable[ratedMovie.first][movieName];
//		if (ratio  == 0)
//		{
//			std::vector<double> firstVec(moviesRankings[movieName].begin(), moviesRankings[movieName].end());
//			std::vector<double> secondVec(moviesRankings[ratedMovie.first].begin(), moviesRankings[ratedMovie.first].end());
//			ratio = _getSimilarity(firstVec, secondVec);
//			similarityMoviesTable[movieName][ratedMovie.first] = ratio;
//			similarityMoviesTable[ratedMovie.first][movieName] = ratio;
//			ratedMovie.second = ratio;
//		}
//		ratedMovie.second = ratio;
//		index++;
//
//	}
//
//}
//
///**
// * sort a giving pair of vector by its second element in ascending order
// * @param ratedMovies the vector we want to sort
// */
//void RecommenderSystem::_sortByAscending(std::vector<std::pair<std::string, double>>& ratedMovies)
//{
//	//sort the rated Movies by its similarity
////    std::sort(unratedMovies.begin(), unratedMovies.end(), sortSimilarity);
//
//	//if that works no need for the under function
//	std::sort(ratedMovies.begin(), ratedMovies.end(), [](const std::pair<std::string, double> &a,
//														 const std::pair<std::string, double> &b){return (a.second > b.second); });
//
//}
//
////bool RecommenderSystem::sortSimilarity(const std::pair<std::string,double> &a, const std::pair<std::string,double> &b)
////{
////    return (a.second < b.second);
////}
//
//
///**
// * get predict rating by the function provided in page 6
// * @param ratedMovies a vector of pairs of sorted movies and its similarity to a given movie
// * @param k the first k movies we want to check
// * @param username  the person we want to suggest a movie to
// * @return predicted rating of username about a movie
// */
//double RecommenderSystem::_predictRating(const std::vector<std::pair<std::string, double>>& ratedMovies, int k, const std::string& username)
//{
//	double numerator;
//	double denominator;
//	// get first k movies
//	for(int i = 0; i < k; i++)
//	{
//		//get movie name
//		std::string movieName = ratedMovies.at(i).first;
//		//search movie in movie list
//		auto searchMovie = std::find(moviesNames.begin(), moviesNames.end(), movieName);
//		//get index of the movie in list
//		int index = std::distance(moviesNames.begin(), searchMovie);
//		//get rating of movie for user, multiply with similarity
//		numerator += userRatings[username].at(index)*(ratedMovies.at(i).second);
//		denominator += ratedMovies.at(i).second;
//	}
//
//	return numerator / denominator;
//}
//
///**
// * recommend a movie to user depends on predicted scores for his movies
// * @param username the user we want to predict movies to
// * @param k number of movies to take in count
// * @return a movie name
// */
//std::string RecommenderSystem::recommendByCF(const std::string& username, int k)
//{
//	auto search = userRatings.find(username);
//	if(search != userRatings.end())
//	{
//		std::vector<std::string> unratedMovies;
//		_getUnratedVector(username, unratedMovies);
//
//		std::vector<std::pair<std::string, double>> moviesExpected;
//		double maxRatio = INTMAX_MIN;
//
////		auto start = std::chrono::high_resolution_clock::now();
//		for (auto &unratedMovie: unratedMovies)
//		{
//			auto start1 = std::chrono::high_resolution_clock::now();
//			double ratio = predictMovieScoreForUser(unratedMovie, username, k);
//			auto finish1 = std::chrono::high_resolution_clock::now();
//			std::chrono::duration<double> elapsed = finish1 - start1;
//			std::cout << "Prediction Elapsed time: " << elapsed.count() << " s\n";
//
//			if (ratio > maxRatio)
//			{
//				maxRatio = ratio;
//				moviesExpected.clear(); //todo make sure we make new vec
//				moviesExpected.emplace_back(unratedMovie, ratio);
//			}
//			else if (ratio == maxRatio)
//			{
//				moviesExpected.emplace_back(unratedMovie, ratio);
//			}
//		}
////		auto finish = std::chrono::high_resolution_clock::now();
////		std::chrono::duration<double> elapsed = finish - start;
////		std::cout << "Elapsed time: " << elapsed.count() << " s\n";
//
//		for (auto &movieName: moviesNames)
//		{
////        auto searchMovie = std::find(moviesExpected.begin(), moviesExpected.end(), movieName);
//
//			auto searchMovie = std::find_if(moviesExpected.begin(), moviesExpected.end(),
//											[&movieName](const std::pair<std::string, double> &element)
//											{
//												return element.first == movieName;
//											});
//
//
//			if (searchMovie != moviesExpected.end())
//			{
//				return movieName;
//			}
//		}
//		std::cout << moviesNames.at(999) << std::endl ; //todo delete
//
//	}
//	else
//	{
////        std::cout << "2 did you enter?" << std::endl;
//		return USER_NOT_FOUND;
//	}
//	return "none";
//}
//
///**
// * fill a list and a vector with rated movies .
// * @param userName the user we want to get his rated movies
// * @param unratedMovies vector we want to fill the rated movies into
// */
//void RecommenderSystem::_getUnratedVector(const std::string &userName, std::vector<std::string> &unratedMovies)
//{
//	std::vector ratings = userRatings[userName];
//	int indexOfMovie = 0;
//	for (auto& num : ratings)
//	{
//		if (num == NA)
//		{
//			unratedMovies.push_back(moviesNames[indexOfMovie]);
//		}
//		indexOfMovie++;
//	}
//
//
//}