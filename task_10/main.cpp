#define _CRT_SECURE_NO_WARNINGS
#include "../libwinbgi/src/graphics.h"
#include "stdio.h"


class point
{
public:
	int x;
	int y;
	int count; // times met in others

	point()
	{
		x = 0;
		y = 0;
		count = 0;
	}

	void set_point(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	void print()
	{
		printf("(%d; %d) ^ %d\n", x, y, count);
	}

	void draw(int _c)
	{
		setcolor(_c);
		setfillstyle(SOLID_FILL, _c);

		circle(x, y, 3);
		floodfill( x,  y, _c);
	}

	// End class
};


class mnozh
{
public:
	int size; // M
	point* arr;
	int max_count_idx;
	int max_count;

	mnozh()
	{

	}

	mnozh(int _size)
	{
		if (_size > 0)
		{
			size = _size;
			arr = new point[size];
		}
		max_count_idx = 0;
		max_count = 0;
	}

	point* operator[](int idx)
	{
		return &arr[idx];
	}

	void print()
	{
		for (int i = 0; i < size; i++)
		{
			printf("%d) ", i); 
			arr[i].print();
		}
	}


	void compare(mnozh* ptr) //&?
	{
		for (int i = 0; i < size; i++)
		
		
		{
			for (int j = 0; j < size; j++)
			{
				printf("i = %d j = %d\n", i, j);
				//printf("ix %d iy %d  jx %d jy %d\n", arr[i].x ,  arr[i].y , (*ptr)[j]->x, (*ptr)[j]->y);
				
				if (arr[i].x == (*ptr)[j]->x && arr[i].y == (*ptr)[j]->y)
				{
					(*ptr)[j]->count++;
					arr[i].count++;
					arr[j].print();
				}
				
			}
		}
		// End func
	}

	void find_max_count_idx()
	{
		for (int i = 0; i < size; i++)
		{
			if(arr[i].count > max_count)
			{
				max_count = arr[i].count;
				max_count_idx = i;
			}
		}
		//End func
	}

	void draw(int _c)
	{

		for (int i = 0; i < size; i++)
		{

			arr[i].draw(_c);

			getch();
		}
	}


	// End class
};




int main()
{

	// Scan mnozh's
	FILE* fin = fopen("config.txt", "r");
	if (fin == NULL)
		return -1;

	int num_of_el = 0;
	int num_of_mnozh = 0;

	fscanf(fin, "%d", &num_of_mnozh);
	fscanf(fin, "%d", &num_of_el);
	printf("scanned: nom: %d noe: %d\n", num_of_mnozh, num_of_el);

	mnozh* set = new mnozh[num_of_mnozh]; // ?
	for (int i = 0; i < num_of_mnozh; i++)
	{
		(set[i]) = *(new mnozh(num_of_el));
	}

	int x;
	int y;
	for (int i = 0; i < num_of_mnozh; i++)
	{
		for (int j = 0; j < num_of_el; j++)
		{
			fscanf(fin, "%d %d", &x, &y);
			mnozh tmp = set[i];
			tmp[j]->set_point(x, y);
			
		}
	}

	fclose(fin);

	for (int i = 0; i < num_of_mnozh; i++)
	{
		for (int j = 0; j < num_of_el; j++)
		{
			mnozh tmp = set[i];
			tmp[j]->print();

		}
	}



	// Compare set[zero] to others
	for (int i = 1; i < num_of_mnozh; i++)
	{
		set[i].compare(&set[0]);
		printf("set i %d\n", i); set[i].print();
		printf("set 0:\n");
		set[0].print();

	}


	// Find max count of points covered

	set[0].find_max_count_idx();
	int target_idx = set[0].max_count_idx;
	int max_count = set[0].max_count;
	int target_x = set[0][target_idx]->x;
	int target_y = set[0][target_idx]->y;


	printf("x:%d y:%d idx:%d, times met:%d\n", target_x, target_y, target_idx, max_count);
	// output result

	initwindow(1000, 1000);

	clearviewport();

	for (int i = 0; i < num_of_mnozh; i++)
	{
		set[i].draw(i + 5);
		printf("set new\n");
	}

	set[0].arr[target_idx].draw(4);

	getch();

	closegraph();


	return 0;
}