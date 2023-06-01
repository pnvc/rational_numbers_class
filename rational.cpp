#include "rational.h"
#include <stdio.h>

#define ROUND_ARR_LENGTH 15

/*
 * All these functions are private within the Rational class,
 * excluded: Rational operator +*-/
 */

/* rational_float() just return a value as double type by division the numerator (n) on denominator (m). */
double Rational::rational_float() const
{
	if (!m || !n)
		return 0.;
	return (double)n / m;
}

/* rational_float_whole returns a whole from division (n) on (m). */
double Rational::rational_float_whole() const
{
	if (!m || !n)
		return 0.;
	long long res = n / m;
	return (double)res;
}

/* rational_fraction returns a fraction from division (n) on (m). */
double Rational::rational_fraction() const
{
	if (!m || !n)
		return 0;
	double res = (double)n / m;
	return res += (long long)-res;
}

/*
 * ufff...
 * rational_float_whole_rounded returns rounded up whole value.
 * To start, the array (arr) with ROUND_ARR_LENGTH length created,
 * then take rational_fraction() value and rational_float_whole() value.
 * Immediatly checking of rational_fraction() value: if >= 0.5 then return rational_float_whole() value +- 1 (positive/negative value respectively)
 * 										 else if < .4 return rational_float_whole() as it is.
 * Else filling of the arr with the help of filling_arr() by numbers of the fraction part
 * e.g. 0.12345 => arr = {1, 2, 3, 4, 5, ..., ROUND_ARR_LENGTH}
 * then pass through the arr from the end (ROUND_ARR_LENGTH - 1 index)
 * If index value > 4 then index-1 value++ etc.
 * Based on the first index value return rational_float_whole() +- 1 (positive/negative value respectively) or as it is if first index value < 5.
 * THE END! :D
 */
double Rational::rational_float_whole_rounded() const
{
	unsigned long i;
	double rf;
	long long result_whole, arr[ROUND_ARR_LENGTH]; // You can change the length of the arr by defining new value at the beginning of this file.
	rf = rational_fraction();
	result_whole = rational_float_whole();
	if (rf >= .5)
		return result_whole >= 0 ? ++result_whole : --result_whole;
	if (rf < .4)
		return result_whole;
	filling_arr(arr, ROUND_ARR_LENGTH, rf); // filled the arr by numbers from .(a) to .(...A)
													// for example: 0.12345 => {1, 2, 3, 4, 5, 0, ..., ROUND_ARR_LENGTH}
													// :D
	i = ROUND_ARR_LENGTH - 1;
	while (i > 0) {
		arr[i] > 4 ? arr[i-- - 1]++ : --i; // hehe
		if (!arr[i]) // It's mean that if initialy .495, so without if it will be as .405, but its wrong
					// we need up 0 to minimal 5 for up .4 to .5 and get right result.
			arr[i] = 5;
	}
	return arr[0] > 4 ? result_whole >= 0 ? ++result_whole : --result_whole : result_whole;
}

/* filling_arr are filling the arr with arr_length length by every single part of r (fracation) value. */
void Rational::filling_arr(long long *arr, unsigned long arr_length, double r) const
{
	if (r < 0) r *= -1;
	for (unsigned long i = 0; i < arr_length; i++) {
		arr[i] = (long long)r;
		r -= (long long)r;
		r *= 10;
	}
}

/* Below just four operators +*-/= */
Rational &Rational::operator += (const Rational& op)
{
	long long n, m;
	m = this->m * op.m;
	n = (this->n * (m / this->m)) + (op.n * (m / op.m));
	!n ? n = 0, m = 1 : n < 0 ? n *= -1, m *= -1 : n = n, m = m;
	this->n = n;
	this->m = m;
	return *this;
}
Rational &Rational::operator -= (const Rational& op)
{
	long long n, m;
	m = this->m * op.m;
	n = (this->n * (m / this->m)) - (op.n * (m / op.m));
	!n ? n = 0, m = 1 : n < 0 ? n *= -1, m *= -1 : n = n, m = m;
	this->n = n;
	this->m = m;
	return *this;
}
Rational &Rational::operator *= (const Rational& op) { n *= op.n; m *= op.m; return *this; }
Rational &Rational::operator /= (const Rational& op) { n *= op.m; m *= op.n; return *this; }


/*
 * Operators below for Rational = Rational1 +*-/ Rational2
 * I see that them dont need descriptions :)))))
 */
Rational operator+(Rational &r1, Rational &r2)
{
	long long n, m;
	m = r1.GetM() * r2.GetM();
	n = (r1.GetN() * (m / r1.GetM())) + (r2.GetN() * (m / r2.GetM()));
	!n ? n = 0, m = 1 : n < 0 ? n *= -1, m *= -1 : n=n, m=m;
	return Rational(n, m);
}

Rational operator-(Rational &r1, Rational &r2)
{
	long long n, m;
	m = r1.GetM() * r2.GetM();
	n = (r1.GetN() * (m / r1.GetM())) - (r2.GetN() * (m / r2.GetM()));
	!n ? n = 0, m = 1 : n < 0 ? n *= -1, m *= -1 : n=n, m=m;
	return Rational(n, m);
}

Rational operator*(Rational &r1, Rational &r2) { return Rational(r1.GetN() * r2.GetN(), r1.GetM() * r2.GetM()); }
Rational operator/(Rational &r1, Rational &r2) { return Rational(r1.GetN() * r2.GetM(), r1.GetM() * r2.GetN()); }
