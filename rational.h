#ifndef RATIONAL_H_SENTRY
#define RATIONAL_H_SENTRY

/*
 * This class is for manipulating rational numbers of the form n/m,
 * where n is nominator and m is denominator, n includes 0
 * (how only {N} if i need 0 and division on 0 = Inf? :D).
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

	public:
		/*
		 * Two constructors.
		 * First: 
		 * 		Ratioanl(): n = m = 1;
		 * 		Rational(nn): n = nn, m = 1;
		 * 		Rational(nn, mm): n = nn, m = mm;
		 * 		if nn < 0 then n = |nn|
		 * 		if mm == 0 then m = 1
		 * 	Second:
		 * 		For the exclude of copy per bytes.
		 * 	This class without explict destructor.
		 */
		Rational(long long nn = 1, long long mm = 1) : n(nn < 0 ? -nn : nn), m(!mm ? 1 : mm) {}
		Rational(const Rational &r) : n(r.n), m(r.m) {}
		void operator += (Rational& op) { n += op.n; m += op.m; } // rational1 += rational2 => rational1 = rational1 + rational2
		void operator -= (Rational& op) { n -= op.n; m -= op.m; } // rational -= rational => rational1 = rational1 - rational2
		void operator *= (Rational& op) { n *= op.n; m *= op.m; } // rational *= rational => rational1 = rational1 * rational2
		void operator /= (Rational& op) { n *= op.m; m *= op.n; } // rational /= rational => rational1 = rational1 / rational2
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
};

Rational operator+(Rational &r1, Rational &r2);
Rational operator-(Rational &r1, Rational &r2);
Rational operator*(Rational &r1, Rational &r2);
Rational operator/(Rational &r1, Rational &r2);

#endif
