#include<stdio.h>
#include<CoalaMOD.h>
#pragma comment(lib, "CoalaMOD.lib")
#include<math.h>

#define pi 3.14159265358979323846

int px, py, pz, locblo[24][2];

void Getline(int a)
{
	double dir = getPlayerDirection();
	double rad = dir * pi / 180;
	int dx = -a * sin(rad) + 13 * cos(rad)+px, dz = a * cos(rad) + 13 * sin(rad)+pz;
	double lx = -cos(rad)*10, lz = -sin(rad)*10, s=0;
	int pmx = lx > 0 ? 1 : -1, pmz = lz > 0 ? 1 : -1;
	//printf("%f\n%f", lx, lz);
	for (int i = 0; i < 24; i++)
	{
		double nows = s;
		if (abs(lx) > abs(lz)) 
		{
			dx+= pmx;
			s += abs(lz); 
			if (lx <= nows) { dz+=pmz; s -= abs(lx); }
			locblo[i][0] = dx;
			locblo[i][1] = dz;
		}
		else 
		{ 
			dz+= pmz;
			s += abs(lx);
			if (lz <= nows) { dx+=pmx; s -= abs(lz); }
			locblo[i][1] = dz;
			locblo[i][0] = dx;
		}
	}
}

void BuildHome()
{
	int house[24][11] = { {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{
		10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {10, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, {10, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}, {10, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2}, {3, 0, 0, 0}, {0}, {1, 3}, {0}, {5, 3, 3, 4, 4, 3}, {5, 3, 4, 3, 4, 3}, {5, 3, 4, 4, 3, 3}, {0}, {5, 3, 3, 3, 3, 3}, {
		0}, {5, 3, 3, 3, 3, 3}, {5, 4, 4, 3, 4, 3}, {5, 4, 4, 3, 3, 3} };
	ConcreteID Ye = createConcrete(COLOR_YELLOW, true);
	ConcreteID Gr = createConcrete(COLOR_GRAY, true);
	ConcreteID Wh = createConcrete(COLOR_WHITE, true);
	ConcreteID Bl = createConcrete(COLOR_BLACK, true);

	for (int i = 0; i < 24; i++)
	{
		for (int j = 1; j <= house[i][0]; j++)
		{
			if (house[i][j] == 0) locateConcrete(Ye, locblo[i][0], j + py - 1, locblo[i][1]);
			if (house[i][j] == 1) locateConcrete(Gr, locblo[i][0], j + py - 1, locblo[i][1]);
			if (house[i][j] == 2) locateConcrete(Wh, locblo[i][0], j + py - 1, locblo[i][1]);
			if (house[i][j] == 3) locateConcrete(Bl, locblo[i][0], j + py - 1, locblo[i][1]);
		}
	}
}

int main()
{
	getPlayerLocation(&px, &py, &pz);

	for (int i = 20; i <= 20; i++)
	{
		Getline(i);
		BuildHome();
	}

	return 0;
}