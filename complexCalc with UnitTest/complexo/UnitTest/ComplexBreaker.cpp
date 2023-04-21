#include "pch.h"
#include <iostream>
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ComplexBreaker
{
	TEST_CLASS(ComplexBreaker)
	{
	public:
		TEST_METHOD(TestAdd){
			complex<double> x(12, 12);
			complex<double> y(55, 1);
			complex<double> z = x + y;
			Assert::AreEqual(67.0, z.get_re());
			Assert::AreEqual(13.0, z.get_im());

			z = z + 2.0;
			Assert::AreEqual(69.0, z.get_re());

			z = 2.0 + z;
			Assert::AreEqual(71.0, z.get_re());

			z += y;
			Assert::AreEqual(126.0, z.get_re());
			Assert::AreEqual(14.0, z.get_im());

			Assert::AreEqual(12.0, x.get_re());
			Assert::AreEqual(12.0, x.get_im());
			Assert::AreEqual(55.0, y.get_re());
			Assert::AreEqual(1.0, y.get_im());
		}
		TEST_METHOD(TestSubstract){
			complex<double> x(12, 12);
			complex<double> y(55, 1);
			complex<double> z = x - y;

			Assert::AreEqual(-43.0, z.get_re());
			Assert::AreEqual(11.0, z.get_im());

			z = z - 2.0;
			Assert::AreEqual(-45.0, z.get_re());

			z = 2.0 - z;
			Assert::AreEqual(-47.0, z.get_re());

			z -= y;
			Assert::AreEqual(-102.0, z.get_re());
			Assert::AreEqual(10.0, z.get_im());

			Assert::AreEqual(12.0, x.get_re());
			Assert::AreEqual(12.0, x.get_im());
			Assert::AreEqual(55.0, y.get_re());
			Assert::AreEqual(1.0, y.get_im());
		}
		TEST_METHOD(TestMultiply){
			complex<double> x(12, 12);
			complex<double> y(55, 1);
			complex<double> z = x * y;

			Assert::AreEqual(648.0, z.get_re());
			Assert::AreEqual(672.0, z.get_im());

			z = z * 2.0;
			Assert::AreEqual(1296.0, z.get_re());
			Assert::AreEqual(1344.0, z.get_im());

			z = 2.0 * z;
			Assert::AreEqual(2592.0, z.get_re());
			Assert::AreEqual(2688.0, z.get_im());

			z *= y;
			Assert::AreEqual(139872.0, z.get_re());
			Assert::AreEqual(150432.0, z.get_im());

			Assert::AreEqual(12.0, x.get_re());
			Assert::AreEqual(12.0, x.get_im());
			Assert::AreEqual(55.0, y.get_re());
			Assert::AreEqual(1.0, y.get_im());

		}
		TEST_METHOD(TestDivide){
			complex<double> x(600, 720);
			complex<double> y(55, 5);
			complex<double> z = x / y;

			Assert::AreEqual(12.0, z.get_re());
			Assert::AreEqual(12.0, z.get_im());

			x /= y;
			Assert::AreEqual(12.0, x.get_re());
			Assert::AreEqual(12.0, x.get_im());

			Assert::AreEqual(55.0, y.get_re());
			Assert::AreEqual(5.0, y.get_im());
		}
		TEST_METHOD(TestString1){
			string s = "i+3i-1+25-24i-0+16+0i";
			complex<int> z(s);
			Assert::AreEqual(40,z.get_re());
			Assert::AreEqual(-20,z.get_im());
		}
		TEST_METHOD(TestString2){
			string s = "-0+0-4.5i-1.0+25.9-0+0i+0i";
			complex<double> z(s);
			Assert::AreEqual(24.9, z.get_re());
			Assert::AreEqual(-4.5, z.get_im());
		}
		TEST_METHOD(bulbul){
			complex<double> z(1.3, 2.3);
			complex<double> z2(1.3, 2.5);
			int c = 0;
			if (z == z2)
				c = 1;
			Assert::AreEqual(0, c);
			int c1 = 0;
			if (z != z2)
				c1 = 1;
			Assert::AreEqual(1, c1);
		}
	};
}
