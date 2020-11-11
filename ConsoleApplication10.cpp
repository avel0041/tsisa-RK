// lab04-tsisa.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

double myfun(double x, double y) {
	return -log(1 + x * x + y * y);
}

double Random(double a, double b)
{
	return a + (1. * rand() / RAND_MAX) * (b - a);
}

struct unit {
	double x;
	double y;
	double f;
	void print() {
		cout << endl << "x = " << x << endl <<
			"y = " << y << endl <<
			"f = " << f << endl;
	}
};

bool Compare(unit& lh, unit& rh) {
	return lh.f > rh.f;
};

int main()
{
	srand(time(0));
	double p_mut = 0.4;
	int pop_size = 4;
	double x_start = -2;
	double x_finish = 2;
	double y_start = -2;
	double y_finish = 2;
	int it_count = 10;

	vector<unit> population;
	for (int i = 0; i < pop_size; i++) {
		unit u;
		u.x = Random(x_start, x_finish);
		u.y = Random(y_start, y_finish);
		u.f = myfun(u.x, u.y);
		population.push_back(u);
	}
	sort(population.begin(), population.end(), Compare);
	cout << "0 Gen:";
	double zero_avg = 0;
	for (int i = 0; i < pop_size; i++) {
		zero_avg += population[i].f;
		population[i].print();
	}
	cout << "max_f = " << population[0].f << endl <<
		"avg = " << zero_avg / pop_size << endl;
	for (int i = 1; i <= it_count; i++) {
		sort(population.begin(), population.end(), Compare);
		population.pop_back();
		vector<unit> new_population;
		new_population.resize(pop_size);
		new_population[0].x = population[0].x;
		new_population[0].y = population[1].y;
		new_population[0].f = myfun(new_population[0].x, new_population[0].y);

		new_population[1].x = population[1].x;
		new_population[1].y = population[0].y;
		new_population[1].f = myfun(new_population[1].x, new_population[1].y);

		new_population[2].x = population[0].x;
		new_population[2].y = population[2].y;
		new_population[2].f = myfun(new_population[2].x, new_population[2].y);

		new_population[3].x = population[2].x;
		new_population[3].y = population[0].y;
		new_population[3].f = myfun(new_population[3].x, new_population[3].y);

		cout << i << " Gen:" << endl;
		double avg = 0;
		for (int i = 0; i < pop_size; i++) {
			double p = Random(0, 1);
			if (p < p_mut) {
				double temp = new_population[i].x;
				new_population[i].x = new_population[i].y;
				new_population[i].y = temp;
				new_population[i].f = myfun(new_population[i].x, new_population[i].y);
			}
			new_population[i].print();
			avg += new_population[i].f;
		}
		sort(new_population.begin(), new_population.end(), Compare);
		cout << "max_f = " << new_population[0].f << endl <<
			"avg = " << avg/pop_size << endl;
		population = new_population;
	}
	return 0;
}
