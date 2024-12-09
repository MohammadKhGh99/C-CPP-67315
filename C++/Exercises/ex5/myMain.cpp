#include <iostream>
#include "RecommenderSystem.h"


int main(int argc, char **argv)
{
	RecommenderSystem rec;
	rec.loadData(argv[1], argv[2]);
//	std::cout << rec.recommendByCF("Christopher", 2) << std::endl;
	std::cout<<rec.recommendByContent("London")<<std::endl;
	std::cout<<rec.recommendByContent("Brayson")<<std::endl;
	std::cout<<rec.recommendByContent("Christopher")<<std::endl;
//	std::cout<<rec.recommendByContent("Christopher")<<std::endl;
//	std::cout<<rec.predictMovieScoreForUser("ArabianNights","Brayson",2)<<std::endl;
//	std::cout<<rec.predictMovieScoreForUser("ArabianNights","Brayson",1)<<std::endl;
//	std::cout<<rec.predictMovieScoreForUser("ArabianNights","Brayson",2)<<std::endl;

//	std::cout<<rec.recommendByContent("Sofia")<<std::endl;
//	std::cout<<rec.predictMovieScoreForUser("Twilight","Nicole",2)<<std::endl;
//	std::cout<<rec.predictMovieScoreForUser("Titanic","Nicole",2)<<std::endl;

	return 0;
}

