#ifndef RATIONAL_H_SENTRY
#define RATIONAL_H_SENTRY

/*
 * This class is for manipulating rational numbers of the form n/m,
 * where n is nominator and m is denominator, n includes 0
 * (how only {N} if i need 0 and division on 0 = Inf? :D).
 * If you need the double result as < 0. then set m < 0.
 * Provides:
 * 		default oparators +=, -=, *=, /= (r1 +*-/= r2 => r1 = r1 operator r2),
 * 		public methods:
 * 			GetN, GetM, GetFloat, GetFloatWhole, GetFloatWholeRounded, GetFloatFraction.
 * 			GetN and GetM also allow to change values respectively.
 * 	Also, this module provides operators +*-/ as friends for the Rational class
 * 	that do respectively calculate between the Rational class operands (arguments)
 * 	and return results as the same class with fields that respectively calculated.
 */

class Rational {
	long long n, m; // n = {0, N} = n > 0, m = {Z} = -inf < m < +inf, float = n / m

	friend Rational operator+(Rational& r1, Rational& r2);
	friend Rational operator-(Rational& r1, Rational& r2);
	friend Rational operator*(Rational& r1, Rational& r2);
	friend Rational operator/(Rational& r1, Rational& r2);

	public:
		/*
		 * Two constructors.
		 * First: 
		 * 		Ratioanl(): n = m = 1;
		 * 		Rational(nn): n = nn, m = 1;
		 * 		Rational(nn, mm): n = nn, m = mm;
		 * 		if nn < 0 then n = |nn|
		 * 	Second:
		 * 		For the exclude of copy per bytes.
		 * 	This class without explict destructor.
		 */
		Rational(long long nn = 1, long long mm = 1) : n(nn < 0 ? -nn : nn), m(mm) { euclid_gcd_n_m(n, m); }
		Rational(const Rational& r) : n(r.n), m(r.m) {}

		Rational &operator += (const Rational& op); // Rational1 += Rational2
		Rational &operator -= (const Rational& op); // Rational1 -= Rational2
		Rational &operator *= (const Rational& op); // Rational1 *= Rational2
		Rational &operator /= (const Rational& op); // Rational1 /= Rational2

		long long &GetN() { return n; } // return link at n (changable)
		long long &GetM() { return m; } // return link at m (changable)
		double GetFloat() const { return rational_float(); } // n / m
		double GetFloatWhole() const { return rational_float_whole(); } // whole of n / m
		double GetFloatWholeRounded() const { return rational_float_whole_rounded(); } // rounded whole of n / m
		double GetFloatFraction() const { return rational_fraction(); } // fracation part of n / m

	private:
		/* Description of these functions inside the rational.cpp file. */
		double rational_float() const;
		double rational_float_whole() const;
		double rational_fraction() const;
		double rational_float_whole_rounded() const;
		void filling_arr(long long *arr, unsigned long arr_length, double r) const;

		static void euclid_gcd_n_m(long long& n, long long& m);
};

Rational operator+(Rational &r1, Rational &r2);
Rational operator-(Rational &r1, Rational &r2);
Rational operator*(Rational &r1, Rational &r2);
Rational operator/(Rational &r1, Rational &r2);

#endif
