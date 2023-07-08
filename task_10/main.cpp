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
	int marked;

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
		marked = 0;
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
				if (arr[i].x == (*ptr)[j]->x && arr[i].y == (*ptr)[j]->y)
				{
					(*ptr)[j]->count++;
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
		}
	}

	void mark()
	{
		marked = 1;
	}

	int has(int x, int y)
	{
		for (int i = 0; i < size; i++)
		{
			if (arr[i].x == x && arr[i].y == y)
			{
				return 1;
			}
		}

		return 0;
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
	//printf("scanned: nom: %d noe: %d\n", num_of_mnozh, num_of_el);

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




	// Compare set[zero] to others
	for (int i = 1; i < num_of_mnozh; i++)
	{
		set[i].compare(&set[0]);
		//set[0].print();
	}


	// Find max count of points covered

	set[0].find_max_count_idx();

	int target_idx = set[0].max_count_idx;
	int max_count = set[0].max_count;
	int target_x = set[0][target_idx]->x;
	int target_y = set[0][target_idx]->y;

	// mark that have this point
	for (int i = 0; i < num_of_mnozh; i++)
	{
		if (set[i].has(target_x, target_y))
			set[i].mark();
	}


	//printf("x:%d y:%d idx:%d, times met:%d\n", target_x, target_y, target_idx, max_count);
	// output result

	initwindow(900, 900);
	clearviewport();

	for (int i = 0; i < num_of_mnozh; i++)
	{
		int color = i + 5;	
		if (set[i].marked)
			set[i].draw(color % 15);
		else
			set[i].draw(15);
		getch();
	}



	char message[128] = {0};
	setcolor(15);
	sprintf_s(message, "(%d; %d) : %d", target_x, target_y, max_count+1);
	settextstyle(0, 0, 1);
	outtextxy(700, 860, message);
	set[0].arr[target_idx].draw(4);


	getch();
	closegraph();


	return 0;
}