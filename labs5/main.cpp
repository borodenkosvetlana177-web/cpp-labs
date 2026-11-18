#include <iostream>
#include <cmath>

struct IntegralResult {
	double value; 
	int count;   
};


double Function1(double x) {
	double f;
	f =std::asin(sqrt(x)) / sqrt(x * (1 - x));
	return f;
}

double Function2(double x) {
	double f;
	f = pow(x, 3) * std::exp(2 * x);
	return f;
}

double Function3(double x) {
	double f;
	const double PI = std::acos(-1.0);
	f = pow(std::tan(x/2.0 + PI/4.0), 3);
	return f;
}



double CalcRectanglesStep(double (*func)(double), double min_x, double max_x, int num_of_figur){
	double h = (max_x - min_x) / num_of_figur;
	double sum_f = 0;
	double x = max_x;
	for (int i = 0; i < num_of_figur; ++i) {
		sum_f += func(x);
		x -= h;
	}
	return  sum_f * h;;
}


double CalcTrapezoidStep(double (*func)(double), double min_x, double max_x, int num_of_figur) {
	double h = (max_x - min_x) / num_of_figur;
	double sum_f = 0;
	double x = min_x;
	sum_f += func(x);
	for (int i = 0; i < num_of_figur - 1; ++i) {
		x += h;
		sum_f += 2*func(x);
	}
	sum_f += func(max_x);
	return  sum_f/2 * h;
}


IntegralResult FoundIntegral(double (*func)(double), double (*method)(double (*)(double), double, double, int), double min_x, double max_x, double eps) {
	int num_of_figur = 4;
	double sqr1 = method(func, min_x, max_x, num_of_figur);

	num_of_figur *= 2;
	double sqr2 = method(func, min_x, max_x, num_of_figur);

	while (std::abs( sqr2- sqr1) > eps) {
		sqr1 = sqr2;
		num_of_figur *= 2;
		sqr2 =method(func, min_x, max_x, num_of_figur);
		
	}
	return { sqr2, num_of_figur };
}

int main() {
	const double eps = 0.000001;
	double max_x1 = 0.3;
	double min_x1 = 0.2;

	double max_x2 = 0.8;
	double min_x2 = 0.0;

	const double PI = std::acos(-1.0);
	double max_x3 = PI/8;
	double min_x3 = 0.0;

	std::cout << "The method of rectangle: \n";

	IntegralResult res1 = FoundIntegral(Function1, CalcRectanglesStep, min_x1, max_x1, eps);
	std::cout << "First integral: " << res1.value << ", n = " << res1.count << '\n';
	IntegralResult res2 = FoundIntegral(Function2, CalcRectanglesStep, min_x2, max_x2, eps);
	std::cout << "Second integral: " << res2.value << ", n = " << res2.count << '\n';
	IntegralResult res3 = FoundIntegral(Function3, CalcRectanglesStep, min_x3, max_x3, eps);
	std::cout << "Third integral: " << res3.value << ", n = " << res3.count << '\n';

	
std::cout << "The method of trapeziod: \n";

IntegralResult res4 = FoundIntegral(Function1, CalcTrapezoidStep, min_x1, max_x1, eps);
std::cout << "First integral: " << res4.value << ", n = " << res4.count << '\n';
IntegralResult res5 = FoundIntegral(Function2, CalcTrapezoidStep, min_x2, max_x2, eps);
std::cout << "Second integral: " << res5.value << ", n = " << res5.count << '\n';
IntegralResult res6 = FoundIntegral(Function3, CalcTrapezoidStep, min_x3, max_x3, eps);
std::cout << "Third integral: " << res6.value << ", n = " << res6.count << '\n';
	return 0;
}
