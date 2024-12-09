#include "RecommenderSystem.h"
#include <iostream>


#define MOVIES "movies.txt"
#define RANKS "ranks.txt"
#define NOTHING "blablaBla"
#define IMAGINE_FRIEND "ancientFish"
#define IMAGINE_MOVIE "no_corona_in_huji"
#define RETURN_STRING_VALUE "USER NOT FOUND"

using std::cout;
using std::endl;
using std::string;

int main()
{
	RecommenderSystem arr[4];
	int exitCode = 0;
	exitCode = arr[0].loadData(NOTHING, NOTHING);
	if (exitCode != -1)
	{
		cout << "bad exit code while giving 2 bad paths" << endl;
	}
	exitCode = arr[1].loadData(MOVIES, NOTHING);
	if (exitCode != -1)
	{
		cout << "bad exit code while giving bad rank path" << endl;
	}
	exitCode = arr[2].loadData(NOTHING, RANKS);
	if (exitCode != -1)
	{
		cout << "bad exit code while giving bad movie path" << endl;
	}
	arr[3].loadData(MOVIES, RANKS);
	string sReturnVal;
	sReturnVal = arr[3].recommendByContent(IMAGINE_FRIEND);
	if (sReturnVal != RETURN_STRING_VALUE)
	{
		cout << "bad string returned from non exist username, recommend by content func" << endl;
	}
	sReturnVal = arr[3].recommendByCF(IMAGINE_FRIEND, 2);
	if (sReturnVal != RETURN_STRING_VALUE)
	{
		cout << "bad string returned from non exist username, recommend by CF func" << endl;
	}
	double dReturnVal;
	dReturnVal = arr[3].predictMovieScoreForUser("Batman", IMAGINE_FRIEND, 2);
	if (dReturnVal != -1)
	{
		cout << "bad value returned from non exist username, predict func" << endl;
	}
	dReturnVal = arr[3].predictMovieScoreForUser(IMAGINE_MOVIE, "Arik", 2);
	if (dReturnVal != -1)
	{
		cout << "bad value returned from non exist movie, predict func" << endl;
	}
	dReturnVal = arr[3].predictMovieScoreForUser(IMAGINE_MOVIE, IMAGINE_FRIEND, 2);
	if (dReturnVal != -1)
	{
		cout << "bad value returned from non exist movie and username, predict func" << endl;
	}
	return 0;
}
