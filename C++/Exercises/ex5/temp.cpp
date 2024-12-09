//#include "RecommenderSystem.h"
//#include <iostream>
////#include <fstream>
//#include <cstring>
////#include <sstream>
//
//#define FILE_ERROR "Unable to open file "
//#define FAIL -1
//#define SUCCESS 0
//#define NO_RANK "NA"
//#define NO_USER "USER NOT FOUND"
//
//using std::string, std::cerr, std::istringstream, std::vector, std::pair;
//
///**
// * this function loads the information from the two files to our Recommender System.
// * @param moviesAttributesFilePath the movies attributes file path as string.
// * @param userRanksFilePath the user ranks file path as string.
// * @return 0 if success, 1 if failed.
// */
//int RecommenderSystem::loadData(const string &moviesAttributesFilePath, const string &userRanksFilePath)
//{
//	std::ifstream moviesAttributesFile(moviesAttributesFilePath); //todo
//	std::ifstream userRanksFile(userRanksFilePath);
//	if (!moviesAttributesFile.is_open())
//	{
//		cerr << FILE_ERROR << moviesAttributesFilePath << std::endl;
//		return FAIL;
//	}
//	if (!userRanksFile.is_open())
//	{
//		cerr << FILE_ERROR << userRanksFilePath << std::endl;
//		return FAIL;
//	}
//
//	string line;
//	while (getline(moviesAttributesFile, line))
//	{
//		istringstream movieLine(line);
//		int i = 1;
//		string movieName;
//		vector<double> attributes;
//		while (movieLine >> line)
//		{
//			if (i == 1)
//			{
//				movieName = line;
//			}
//			else
//			{
//				char *end;
////				todo check if 1-10 ? return -1 ?
//				attributes.push_back(strtod(line.c_str(), &end)); //todo try & catch? or manual check?
//				attributes.shrink_to_fit();
//			}
//			i++;
//		}
//		if (!movieName.empty())
//		{
//			this->_moviesMap[movieName] = attributes;
//		}
//		// todo "else" ?
//	}
//
//	int num = 1;
//	while (getline(userRanksFile, line))
//	{
//		istringstream userLine(line);
//		int j = 0;
//		string userName;
//		vector<double> ranks;
//		while (userLine >> line) //todo
//		{
//			if (num == 1)
//			{
//				this->_moviesInUsersOrder.push_back(line);
//				this->_moviesInUsersOrder.shrink_to_fit();
//			}
//			else
//			{
//				if (j == 0) // the line of ranking, j = 0 the names.
//				{
//					userName = line;
//				}
//				else if (strcmp(line.c_str(), NO_RANK) != 0) //todo
//				{
//					char *end;
//					ranks.push_back(strtod(line.c_str(), &end)); //todo
//					ranks.shrink_to_fit();
//				}
//				else //if NA found
//				{
//					ranks.push_back(0.0); //0.0 represents the NA rank, yet !!!
//					ranks.shrink_to_fit();
//				}
//
//				j++;
//			}
//		}
//
//		///////////////////////////////////////////////////START////////////////////////////////////////////////////////
//		if (!userName.empty())
//		{
//			map<string, double> temp;
//			auto movieIt = this->_moviesInUsersOrder.begin();
//			auto rankIt = ranks.begin();
//			while (movieIt != this->_moviesInUsersOrder.end() && rankIt != ranks.end())
//			{
//				temp[*movieIt] = (*rankIt);
//				movieIt++;
//				rankIt++;
//			}
//			this->_usersMap[userName] = temp;
//		}
//		/////////////////////////////////////////////////////END////////////////////////////////////////////////////////
//
//		if (!userName.empty())
//		{
//			this->_users[userName] = ranks;
//		}
//		//todo "else" ?
//		num++;
//	}
//	userRanksFile.close();
//	moviesAttributesFile.close();
//	return SUCCESS;
//}
//
///**
// * this function returns the most recommended movie for the given customer by content Algorithm.
// * @param userName the customer's username.
// * @return string with the name of the recommended movie for the given customer username.
// */
//string RecommenderSystem::recommendByContent(const string &userName)
//{
//	if (this->_usersMap.find(userName) == this->_usersMap.end())
//	{
//		return NO_USER;
//	}
//
//	map<string, map<string, double>> temp(this->_usersMap);
//
//	vector<double> ranks(this->_users[userName]);
//	double sum = _getAverage(ranks);
//
//	auto it = ranks.begin();
//	auto strIt = this->_moviesInUsersOrder.begin();
//	vector<double> result(this->_moviesMap[*strIt].size());
//	auto movieIt = temp[userName].begin();
//	vector<string> notRankedNames;
//	while (movieIt != temp[userName].end())
//	{
//		if (movieIt->second != 0)
//		{
//			movieIt->second -= sum;
//			result = _vectorsSum(result, _vectorMultiply(this->_moviesMap[movieIt->first], movieIt->second));
//		}
//		else
//		{
//			notRankedNames.push_back(movieIt->first);
//			notRankedNames.shrink_to_fit();
//		}
//		movieIt++;
//	}
//
//	map<string, double> currentSimilarityMap;
//	double max = -20;
//	it = ranks.begin();
//	string recommendedMovie;
//	auto notRanked = notRankedNames.begin();
//	while (notRanked != notRankedNames.end())
//	{
//		currentSimilarityMap[*notRanked] = _similarity(result, this->_moviesMap[*notRanked]);
//		notRanked++;
//	}
//
//	notRanked = notRankedNames.begin();
////	movieIt = temp[userName].begin();
//	while (notRanked!=notRankedNames.end())
//	{
//		if (currentSimilarityMap[*notRanked]>max)
//		{
//			max=currentSimilarityMap[*notRanked];
//			recommendedMovie=(*notRanked);
//		}
//		notRanked++;
//	}
//
////	while (movieIt != temp[userName].end())
////	{
////		if (movieIt->second == 0)
////		{
////			if (currentSimilarityMap[movieIt->first] > max || notRanked == notRankedNames.begin())
////			{
////				max = currentSimilarityMap[movieIt->first];
////				recommendedMovie = movieIt->first;
////			}
////		}
////		notRanked++;
////		movieIt++;
////	}
//
//	return recommendedMovie;
//
//}
//
///**
// * this function returns the predicted rank for the given movie name by the filtering way.
// * @param movieName the movie name to predict its rank by the given customer's user name.
// * @param userName the customer's user name.
// * @param k the number of the k most similar movies by customer's movies.
// * @return -1 if the userName or movieName are not in the system, positive double number that represents the
// * predicted rank for the given movieName.
// */
//double RecommenderSystem::predictMovieScoreForUser(const string &movieName, const string &userName, myInt k)
//{
//	if (this->_users.find(userName) == this->_users.end() || this->_moviesMap.find(movieName) == this->_moviesMap.end())
//	{
//		return FAIL;
//	}
//
//	map<string, vector<double>> ranked = _rankedMovies(userName);
//	vector<pair<string, double>> asd;
//	for (auto &it : ranked)
//	{
//		double sim = _similarity(it.second, this->_moviesMap[movieName]);
//		pair<string, double> t(it.first, sim);
//		asd.push_back(t);
//		asd.shrink_to_fit();
//	}
//
//	return _predictValue(_kSimilarVal(asd, k), userName);
//}
//
///**
// * this function returns the recommended movie by the filtering way.
// * @param userName the customer's user name.
// * @param k the number of the k most similar movies by customer's movies.
// * @return the movie that we have recommended for the customer.
// */
//string RecommenderSystem::recommendByCF(const string &userName, myInt k)
//{
//	if (this->_users.find(userName) == this->_users.end())
//	{
//		return NO_USER;
//	}
//
//	vector<string> notRankedMovies = _notRankedMovies(userName);
//	string maxName;
//	double max = 0;
//	for (auto &notRanked : notRankedMovies)
//	{
//		double currentPredict = predictMovieScoreForUser(notRanked, userName, k);
//		if (currentPredict > max)
//		{
//			max = currentPredict;
//			maxName = notRanked;
//		}
//	}
//
//	return maxName;
//}
