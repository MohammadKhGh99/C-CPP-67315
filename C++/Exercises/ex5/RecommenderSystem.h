#ifndef EX5_RECOMMENDERSYSTEM_H
#define EX5_RECOMMENDERSYSTEM_H

#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <algorithm>

#define FILE_ERROR "Unable to open file "
#define FAIL -1
#define SUCCESS 0
#define NO_USER "USER NOT FOUND"
#define NA 0.0
#define MOVIES_LINE 1
#define USER_COLUMN 0
#define LOWER_BOUND -20.0
#define NA_STR "NA"

using std::vector, std::map, std::string, std::pair;
typedef vector<pair<string, double>> myVec;
typedef const unsigned int myInt;

/**
 * this class represents the system which can recommend a movie to user.
 */
class RecommenderSystem
{
private:

	map<string, vector<double>> _moviesMap;
	vector<string> _moviesInUsersOrder;
	map<string, map<string, double>> _similarities;
	map<string, map<string, double>> _usersMap;

	/**
	 * this function reads the user userLine with the its rankings.
	 * @param userLine the userLine to read.
	 * @param num the userLine of the movies names in the rankings file.
	 * @return the read vector of rankings of the current user.
	 */
	vector<double> _readUserRankingLine(string &userLine, int num)
	{
		std::istringstream userLineStream(userLine);
		int j = 0;
		string userName;
		vector<double> ranks; //the ranks of the current user.
		auto it = this->_moviesInUsersOrder.begin();
		while (userLineStream >> userLine)
		{
			if (num == MOVIES_LINE)
			{
				this->_moviesInUsersOrder.push_back(userLine); //save the movies names as they are in users file.
			}
			else
			{
				if (j == USER_COLUMN) // the userLine of ranking, j = 0 the names.
				{
					userName = userLine;
				}
				else if (userLine != NA_STR)
				{
					char *end;
					double rank = strtod(userLine.c_str(), &end);
					ranks.push_back(rank);
					this->_usersMap[userName][*it] = rank;
					it++;
				}
				else //if NA found
				{
					this->_usersMap[userName][*it] = NA;
					ranks.push_back(NA);
					it++;
				}
				j++;
			}
		}
		return ranks;
	}

	/**
	 * this function reads the movie movieLine with its rankings.
	 * @param movieLine the movieLine to read.
	 */
	void _readMovieLine(string &movieLine)
	{
		std::istringstream movieLineStream(movieLine);
		movieLineStream >> movieLine; //to get the movies name in the current line.
		string movieName = movieLine;
		vector<double> attributes;
		while (movieLineStream >> movieLine)
		{
			char *end;
			attributes.push_back(strtod(movieLine.c_str(), &end));
		}
		if (!movieName.empty())
		{
			this->_moviesMap[movieName] = attributes;
		}
	}

	/**
	 * this function calculates the similarity rate between two vectors.
	 * @param v the first vector.
	 * @param u the second vector.
	 * @return the similarity rate of the two vectors.
	 */
	static double _similarity(const vector<double> &v, const vector<double> &u)
	{
		double mulRes = 0, norm1 = 0, norm2 = 0;
		auto firstIt = v.begin(), secondIt = u.begin();
		while (firstIt != v.end() && secondIt != u.end())
		{
			mulRes += (*firstIt) * (*secondIt);
			norm1 += (*firstIt) * (*firstIt);
			norm2 += (*secondIt) * (*secondIt);
			++firstIt;
			++secondIt;
		}
		return (mulRes / (sqrt(norm1) * sqrt(norm2)));
	}

	/**
	 * this function returns the movies that the given user has not ranked yet (didn't watch them).
	 * @param userName the user name.
	 * @return a vector of the not ranked movies.
	 */
	vector<string> _notRankedMovies(const string &userName)
	{
		vector<string> result;
		auto movieIt = _moviesInUsersOrder.begin();
		while (movieIt != _moviesInUsersOrder.end())
		{
			if (this->_usersMap[userName][*movieIt] == NA)
			{
				result.push_back(*movieIt);
			}
			movieIt++;
		}
		return result;
	}

	/**
	 * this function returns the movies that the gicen user has ranked.
	 * @param userName the user name.
	 * @return a vector with the ranked movies.
	 */
	myVec _rankedMovies(const string &userName)
	{
		myVec result;
		auto movieIt = this->_moviesInUsersOrder.begin();
		while (movieIt != this->_moviesInUsersOrder.end())
		{
			if (this->_usersMap[userName][*movieIt] != NA)
			{
				result.emplace_back(*movieIt, this->_usersMap[userName][*movieIt]);
			}
			movieIt++;
		}
		return result;
	}

	/**
	 * this function sums the given vectors.
	 * @param v the first vector.
	 * @param u the second vector.
	 * @return the sum of both vector as vector instance.
	 */
	static vector<double>& _vectorsSum(const vector<double> &v, const vector<double> &u)
	{
		vector<double> result;
			for (int i = 0; i < (int) v.size(); ++i)
			{
				result.push_back(v[i] + u[i]);
			}
		return result;
	}

	/**
	 * this function multiply the given vector with scalar.
	 * @param v the vector to multiply.
	 * @param c the scalar.
	 * @return the result of multiplication. as vector instance.
	 */
	static vector<double> _vectorMultiply(const vector<double> &v, const double &c)
	{
		vector<double> result;
		for (double n : v)
		{
			result.push_back(n * c);
		}
		return result;
	}

	/**
	 * this function returns the average of the values of the given map.
	 * @param m the map to get its average.
	 * @return the average as double.
	 */
	static double _getAverage(const map<string, double> &m)
	{
		double sum = 0;
		int count = 0;

		for (auto &it : m)
		{
			sum += it.second;
			if (it.second != NA)
			{
				count++;
			}
		}
		return (sum / count);
	}

	/**
	 * this function gets the recommended movie name.
	 * @param notRankedNames vector of the not ranked movies' names.
	 * @param result the vector to help in similarity.
	 * @return the name of the recommended movie as string.
	 */
	string _getRecommendedMovie(const vector<string> &notRankedNames, const vector<double> &result)
	{
		double max = LOWER_BOUND;
		string recommendedMovie;
		auto notRanked = notRankedNames.begin();
		while (notRanked != notRankedNames.end())
		{
			double current = _similarity(result, this->_moviesMap[*notRanked]);

			if (current > max)
			{
				max = current;
				recommendedMovie = (*notRanked);
			}
			notRanked++;
		}
		return recommendedMovie;
	}

public:
	/**
	 * this function loads the information from the two files to our Recommender System.
	 * @param moviesAttributesFilePath the movies attributes file path as string.
	 * @param userRanksFilePath the user ranks file path as string.
	 * @return 0 if success, 1 if failed.
	 */
	int loadData(const string &moviesAttributesFilePath, const string &userRanksFilePath);

	/**
	 * this function returns the most recommended movie for the given customer by content Algorithm.
	 * @param userName the customer username.
	 * @return string with the name of the recommended movie for the given customer username.
	 */
	string recommendByContent(const string &userName);

	/**
	 * this function returns the predicted rank for the given movie name by the filtering way.
	 * @param movieName the movie name to predict its rank by the given customer's user name.
	 * @param userName the customer's user name.
	 * @param k the number of the k most similar movies by customer's movies.
	 * @return -1 if the userName or movieName are not in the system, positive double number that represents the
	 * predicted rank for the given movieName.
	 */
	double predictMovieScoreForUser(const string &movieName, const string &userName, myInt k);

	/**
	 * this function returns the recommended movie by the filtering way.
	 * @param userName the customer's user name.
	 * @param k the number of the k most similar movies by customer's movies.
	 * @return the movie that we have recommended for the customer.
	 */
	string recommendByCF(const string &userName, myInt k);

};

#endif //EX5_RECOMMENDERSYSTEM_H
