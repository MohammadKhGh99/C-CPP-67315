#include <stdio.h>
#include <stdlib.h>

typedef struct Landmark
{
	int x, y;
	void *difficulty;
} Landmark;

typedef struct Route
{
	Landmark *landmarks;

	unsigned int (*is_difficult)(Landmark *);

	size_t size;
} Route;

void init_route(Route *route, unsigned int (*is_difficult)(Landmark *))
{
	route->is_difficult = is_difficult;
	route->size = 0;
	route->landmarks = NULL;
}

int add_to_route(Route *route, int x, int y, void *difficulty)
{
	route->size++;
	route->landmarks = (Landmark *) realloc(route->landmarks, route->size * sizeof(Landmark));
	if (route->landmarks == NULL)
	{
		route->size--;
		return 0;
	}
	route->landmarks[((int) route->size) - 1].x = x;
	route->landmarks[((int) route->size) - 1].y = y;
	route->landmarks[((int) route->size) - 1].difficulty = difficulty;
	return 1;
}

void free_route(Route *route)
{
	if (route != NULL && route->landmarks != NULL)
	{
		free(route->landmarks);
	}
}

//int is_hard_route(Route * route)
//{
//	int count = 0;
//	for(int i = 0; i < route->size; i++)
//	{
//		if(route->is_difficult(&route->landmarks[i]))
//		{
//			count++;
//		}
//	}
//	if (count > ( (route->size) / 2) )
//	{
//		return 1;
//	}
//	return 0;
//}

int is_hard_route(Route *route)
{
	if (route == NULL)
	{
		return -1;
	}
	int counter = 0;
	for (int i = 0; i < (int) route->size; ++i)
	{
		if (route->is_difficult(&route->landmarks[i]) == 1)
		{
			counter++;
		}
	}
	if (counter > (route->size / 2))
	{
		return 1;
	}
	return 0;
}

void print_route(Route *route)
{
	if (route == NULL || route->landmarks == NULL)
	{
		return;
	}
	for (size_t i = 0; i < route->size; ++i)
	{
		printf("%d, %d\n", route->landmarks[i].x, route->landmarks[i].y);
	}
	return;
}

unsigned int int_greater_than_3000(Landmark *landmark)
{
	if (*(int *) landmark->difficulty > 3000)
	{
		return 1;
	}
	return 0;
}

int main()
{
	Route hikeMountHimalaya;
	init_route(&hikeMountHimalaya, int_greater_than_3000);

	int firstLandmarkHigh = 2000;
	add_to_route(&hikeMountHimalaya, 0, 0, &firstLandmarkHigh);

	int secondLandmarkHigh = 3500;
	add_to_route(&hikeMountHimalaya, -70, 900, &secondLandmarkHigh);

	int thirdLandmarkHigh = 6000;
	add_to_route(&hikeMountHimalaya, 250, 3500, &thirdLandmarkHigh);

	if (is_hard_route(&hikeMountHimalaya))
	{
		printf("BEWARE! This is a hard route!\n");
	}
	else
	{
		printf("This route is not so hard.\n");
	}

	free_route(&hikeMountHimalaya);
	return 0;
}