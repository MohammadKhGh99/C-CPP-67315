////#include "RecommenderSystem.h"
////#include <iostream>
////#include <fstream>
////#include <string>
////
////#define ILLEGAL_OUT "your_res_1.txt"
////
////using std::cout;
////using std::endl;
////using std::ofstream;
////
////
////string UNAMES[2] = {"Miles", "Michaela"};
////string MOVIES[2] = {"TopHat", "TropicalMalady"};
////string UNAMES_SEEN[2] = {"Reina", "Celine"};
////
////void printIllegals(RecommenderSystem& rc)
////{
////    // look for non existing user/ movie
////
////    string uname = "a523sgf";
////    cout << rc.recommendByContent(uname) << endl;
////    cout << rc.recommendByCF(uname, 1) << endl;
////    cout << rc.predictMovieScoreForUser("TheKid", uname, 1) << endl;
////    cout << rc.predictMovieScoreForUser(uname, "Reina", 1) << endl;
////
////    cout << "\nlegal vals:" << endl;
////    for (const string& n : UNAMES)
////    {
////        cout << "recommend by content: " << rc.recommendByContent(n) << endl;
////        for (int k = 1; k < 4; k++)
////        {
////            cout << "recommend by cf, k = " << k << ": " << rc.recommendByCF(n, k) << endl;
////            for (const string& m: MOVIES)
////            {
////                cout << "predict, k = " << k << ": " << rc.predictMovieScoreForUser(m, n, k) << endl;
////            }
////        }
////    }
////
////    cout << "\nillegal vals:" << endl;
////    for (const string& n : UNAMES_SEEN)
////    {
////        cout << "recommend by content: " << rc.recommendByContent(n) << endl;
////        for (int k = 1; k < 2; k++)
////        {
////            cout << "recommend by cf, k = " << k << ": " << rc.recommendByCF(n, k) << endl;
////            for (const string& m: MOVIES)
////            {
////                cout << "predict, k = " << k << ": " << rc.predictMovieScoreForUser(m, n, k) << endl;
////            }
////        }
////    }
////}
////
////
////int main()
////{
////    // init rc obj
////    cout << "started" << endl;
////    RecommenderSystem rc = RecommenderSystem();
////    // illegal path try
////    rc.loadData("iasvf", "ranks_big.txt");
////    cout << "next" << endl;
////    cout<< "loaded: " << rc.loadData(R"(D:\C&C++LionProjects\C++\Exercises\ex5\movies_big.txt)", R"(D:\C&C++LionProjects\C++\Exercises\ex5\ranks_big.txt)") << endl;
////    printIllegals(rc);
////}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
////
//// Created by Rina Karnauch on 20/06/2020.
//// HELLO FRIENDS AND WELCOME TO THE FIRST TRY OUT OF THE SEASON 1 OF: RINA IS TRYING TO WRITE TESTS
//// YOU CAN ENJOY OR NOT ENJOY THE FOLLOWING NONSENSE THAT WAS TRIED HERE
//// HAVE A NICE DAY AND REMEMBER THAT ׳׳ ׳™ ׳׳׳—׳׳× ׳׳›׳ ׳™׳•׳ ׳§׳¡׳•׳
//// love u guys xoxo
////
//
//#define RANKS_BIG R"(D:\C&C++LionProjects\C++\Exercises\ex5\ranks_big.txt)"
//#define RANKS_MEDIUM R"(D:\C&C++LionProjects\C++\Exercises\ex5\ranks_matrix.txt)"
//#define RANKS_SMALL R"(D:\C&C++LionProjects\C++\Exercises\ex5\ranks_small.txt)"
//#define MOVIES_BIG R"(D:\C&C++LionProjects\C++\Exercises\ex5\movies_big.txt)"
//#define MOVIES_MEDIUM R"(D:\C&C++LionProjects\C++\Exercises\ex5\movies_features.txt)"
//#define MOVIES_SMALL  R"(D:\C&C++LionProjects\C++\Exercises\ex5\movies_small.txt)"
//
//#define BIG_RESULTS R"(D:\C&C++LionProjects\C++\Exercises\ex5\schooloutputBig.txt)"
//#define MEDIUM_RESULTS R"(D:\C&C++LionProjects\C++\Exercises\ex5\schooloutputMedium.txt)"
//#define SMALL_RESULTS R"(D:\C&C++LionProjects\C++\Exercises\ex5\schooloutputSmall.txt)"
//
//// LIBS
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <algorithm>
//#include <iterator>
//#include <cmath>
//#include <vector>
////#include "ibrahem.h"
//#include "RecommenderSystem.h"
//#include <chrono>  // for high_resolution_clock
//
//// MACROS
//#define NOTFOUND -1
//#define ZERO 0
//#define ONE 1
//#define SUCCESS_READING 0
//#define FAILURE_READING -1
//#define k 2
//
//// MSGS:
//#define USER_ERROR "USER NOT FOUND"
//#define FILE_PATH_ERROR "Unable to open file "
//
////USINGS
//using std::endl;
//using std::cout;
//using std::string;
//using std::cerr;
//using std::cin;
//using std::istream_iterator;
//using std::string;
//using std::istringstream;
//using std::sort;
//using std::map;
//using std::end;
//using std::pair;
//using std::begin;
//using std::vector;
//
//
//vector<string> getNames(string filePath, vector<string> names)
//{
//	std::ifstream in;
//	in.open(filePath);
//	if (!in)
//	{
//		cerr << "unable to open file: " << filePath << endl;
//		in.close();
//	}
//
//	string lineN;
//	int i = ZERO;
//	while (getline(in, lineN, '\n'))
//	{
//		if (i == ZERO)
//		{
//			i++;
//		}
//		else
//		{
//			string word = lineN.substr(0, lineN.find(' '));
//			names.insert(names.end(), word);
//		}
//	}
//	return names;
//}
//
//vector<string> schoolResults(string filePath)
//{
//	std::ifstream in;
//	in.open(filePath);
//	if (!in)
//	{
//		cerr << "problem opening file, make sure it's in the right place" << endl;
//		exit(1);
//	}
//
//	string line;
//
//	vector<string> schoolVector;
//
//	while (getline(in, line, '\n'))
//	{
//		schoolVector.push_back(line);
//	}
//
//	return schoolVector;
//}
//
//int main()
//{
//	vector<string> names;
//
//	vector<string> bigResults = schoolResults(BIG_RESULTS);
//	vector<string> mediumResults = schoolResults(MEDIUM_RESULTS);
//	vector<string> smallResults = schoolResults(SMALL_RESULTS);
//
//	RecommenderSystem r1;
//	string result;
//	int check;
//	int size;
//	names = getNames(RANKS_SMALL, names);
//
//	auto start = std::chrono::high_resolution_clock::now();
//
//	check = r1.loadData(MOVIES_SMALL, RANKS_SMALL);
//	if(check == -1)
//	{
//		cerr << "problem with one of the files in loadData function" << endl;
//		exit(1);
//	}
//
//	size = smallResults.size();
//	for (int i = 0; i < size; i++)
//	{
//		result = r1.recommendByCF(names[i], k);
//		if (result != smallResults[i])
//		{
//			cerr << " problem with name: " << names[i] << endl;
//			cout << " wanted result: " << smallResults[i] << " current result: " << result << endl;
//			exit(1);
//		}
//	}
//
//	cout << "small file has passed peacefully comrade." << endl;
//
//	names.clear();
//	names = getNames(RANKS_MEDIUM, names);
//
//	RecommenderSystem r2;
//	check = r2.loadData(MOVIES_MEDIUM, RANKS_MEDIUM);
//	if(check == -1)
//	{
//		cerr << "problem with one of the files in loadData function" << endl;
//		exit(1);
//	}
//
//	size = mediumResults.size();
//	for (int i = 0; i < size; i++)
//	{
//		result = r2.recommendByCF(names[i], k);
//		if (result != mediumResults[i])
//		{
//			cerr << "problem with name: " << names[i] << endl;
//			cout << "wanted result: " << mediumResults[i] << "current result: " << result << endl;
//			exit(1);
//		}
//	}
//
//	cout << "medium file has passed peacefully comrade." << endl;
//
//	cout << " * * * its gonna take some time for the next file, be aware! * * * " << endl;
//
//	RecommenderSystem r3;
//	names.clear();
//	names = getNames(RANKS_BIG, names);
//	check = r3.loadData(MOVIES_BIG, RANKS_BIG);
//
//	if(check == -1)
//	{
//		cerr << "problem with one of the files in loadData function" << endl;
//		exit(1);
//	}
//
//	size = bigResults.size();
//	for (int i = 0; i < size; i++)
//	{
//		cout<<"#"<<i<<endl;
////		auto start1 = std::chrono::high_resolution_clock::now();
//		result = r3.recommendByCF(names[i], k);
////		auto finish1 = std::chrono::high_resolution_clock::now();
////		std::chrono::duration<double> elapsed = finish1 - start1;
////		std::cout << "Elapsed time: " << elapsed.count() << " s\n";
//
//		if (result != bigResults[i])
//		{
//			cerr << "problem with name: " << names[i] << endl;
//			cout << "wanted result: " << bigResults[i] << "current result" << result << endl;
//			exit(1);
//		}
//	}
//	cout << "----------- all files passed if nothing has appeared on screen, well done!! "
//			"-----------" ;
//
//	auto finish = std::chrono::high_resolution_clock::now();
//	std::chrono::duration<double> elapsed = finish - start;
//	std::cout << "Elapsed time: " << elapsed.count() << " s\n";
//
//	exit(0);
//}
//
//
//