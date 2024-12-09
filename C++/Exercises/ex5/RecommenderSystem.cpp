#include "RecommenderSystem.h"

/**
 * this function loads the information from the two files to our Recommender System.
 * @param moviesAttributesFilePath the movies attributes file path as string.
 * @param userRanksFilePath the user ranks file path as string.
 * @return 0 if success, 1 if failed.
 */
int RecommenderSystem::loadData(const string &moviesAttributesFilePath, const string &userRanksFilePath)
{
	std::ifstream moviesAttributesFile(moviesAttributesFilePath);
	std::ifstream userRanksFile(userRanksFilePath);
	if (!moviesAttributesFile.is_open())
	{
		std::cerr << FILE_ERROR << moviesAttributesFilePath << std::endl;
		return FAIL;
	}
	if (!userRanksFile.is_open())
	{
		std::cerr << FILE_ERROR << userRanksFilePath << std::endl;
		return FAIL;
	}

	string line;
	while (getline(moviesAttributesFile, line))
	{
		_readMovieLine(line);
	}

	int lineNum = 1;
	while (getline(userRanksFile, line))
	{
		_readUserRankingLine(line, lineNum);
		lineNum++;
	}
	userRanksFile.close();
	moviesAttributesFile.close();
	return SUCCESS;
}

/**
 * this function returns the most recommended movie for the given customer by content Algorithm.
 * @param userName the customer's username.
 * @return string with the name of the recommended movie for the given customer username.
 */
string RecommenderSystem::recommendByContent(const string &userName)
{
	if (this->_usersMap.find(userName) == this->_usersMap.end())
	{
		return NO_USER;
	}

	map<string, double> tmp(this->_usersMap[userName]);
	double avg = _getAverage(tmp);
	vector<double> result(this->_usersMap[userName][*this->_moviesInUsersOrder.begin().]);
	vector<string> notRankedNames;

	auto movie = this->_moviesInUsersOrder.begin();
	while (movie != this->_moviesInUsersOrder.end())
	{
		if (tmp[*movie] != NA)
		{
			tmp[*movie] -= avg;
			vector<double> temp = _vectorMultiply(this->_moviesMap[*movie], tmp[*movie]);
			result = _vectorsSum(result, temp);

		}
		else
		{
			notRankedNames.push_back(*movie);
		}
		movie++;
	}

	string recommendedMovie = _getRecommendedMovie(notRankedNames, result);
	return recommendedMovie;

}

/**
 * this function returns the predicted rank for the given movie name by the filtering way.
 * @param movieName the movie name to predict its rank by the given customer's user name.
 * @param userName the customer's user name.
 * @param k the number of the k most similar movies by customer's movies.
 * @return -1 if the userName or movieName are not in the system, positive double number that represents the
 * predicted rank for the given movieName.
 */
double RecommenderSystem::predictMovieScoreForUser(const string &movieName, const string &userName, myInt k)
{
	if (this->_usersMap.find(userName) == this->_usersMap.end() || _moviesMap.find(movieName) == _moviesMap.end())
	{
		return FAIL;
	}

	vector<pair<string, double>> ranked = _rankedMovies(userName);
	auto rankIt = ranked.begin();
	while (rankIt != ranked.end())
	{
		double similarity = this->_similarities[rankIt->first][movieName];
		if (similarity != 0)
		{
			rankIt->second = similarity;
		}
		else
		{
			vector<double> firstCaseVec(this->_moviesMap[movieName]);
			vector<double> secondCaseVec(this->_moviesMap[rankIt->first]);
			similarity = _similarity(firstCaseVec, secondCaseVec);
			this->_similarities[movieName][rankIt->first] = similarity;
			this->_similarities[rankIt->first][movieName] = similarity;
			rankIt->second = similarity;
		}
		rankIt++;
	}

	std::sort(ranked.begin(), ranked.end(), [](pair<string, double> &a, pair<string, double> &b)
	{
		return (a.second < b.second);
	});

	double sum1 = 0, sum2 = 0;
	auto it = ranked.rbegin();
	unsigned int i = 0;
	while (it != ranked.rend() && i < k)
	{
		sum1 += (it->second * this->_usersMap[userName][it->first]);
		sum2 += it->second;
		it++;
		i++;
	}

	return (sum1 / sum2);
}

/**
 * this function returns the recommended movie by the filtering way.
 * @param userName the customer's user name.
 * @param k the number of the k most similar movies by customer's movies.
 * @return the movie that we have recommended for the customer.
 */
string RecommenderSystem::recommendByCF(const string &userName, myInt k)
{
	if (this->_usersMap.find(userName) == this->_usersMap.end())
	{
		return NO_USER;
	}

	vector<string> notRankedMovies = _notRankedMovies(userName);
	string maxName;
	double max = LOWER_BOUND;
	for (auto &notRanked : notRankedMovies)
	{
		double currentPredict = predictMovieScoreForUser(notRanked, userName, k);
		if (currentPredict > max)
		{
			max = currentPredict;
			maxName = notRanked;
		}
	}

	return maxName;
}
