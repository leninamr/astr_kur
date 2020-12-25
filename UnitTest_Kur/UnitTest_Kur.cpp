#include "CppUnitTest.h"
#include "../astra_kur/List.h"
#include "../astra_kur/Stack.h"
#include "../astra_kur/Postfix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestKur
{
	TEST_CLASS(UnitTestKur)
	{
	public:
		
		Postfix* postfix;

		TEST_METHOD_INITIALIZE(setUp)
		{
			postfix = new Postfix();
		}

		TEST_METHOD_CLEANUP(cleanUp)
		{
			delete postfix;
		}

		TEST_METHOD(test_operator_1)
		{
			string input = {"1+2"};
			postfix->to_Postfix(input);
			Assert::AreEqual(postfix->calculation(), 3.0);
		}
		TEST_METHOD(test_operator_2)
		{
			string input = { "1-0.009" };
			postfix->to_Postfix(input);
			Assert::AreEqual(postfix->calculation(), 0,991);
		}
		TEST_METHOD(test_operator_3)
		{
			string input = { "10*3.3" };
			postfix->to_Postfix(input);
			Assert::AreEqual(postfix->calculation(), 33.0);
		}
		TEST_METHOD(test_operator_4)
		{
			string input = { "2+1/4" };
			postfix->to_Postfix(input);
			Assert::AreEqual(postfix->calculation(), 2.25);
		}
		TEST_METHOD(test_operator_5)
		{
			string input = { "2^4" };
			postfix->to_Postfix(input);
			Assert::AreEqual(postfix->calculation(), 16.0);
		}
		TEST_METHOD(test_operator_negative_exponent)
		{
			string input = { "2^(-2)" };
			postfix->to_Postfix(input);
			Assert::AreEqual(postfix->calculation(), 0.25);
		}
		TEST_METHOD(test_brecket_1)
		{
			string input = { "(2-1)*3" };
			postfix->to_Postfix(input);
			Assert::AreEqual(postfix->calculation(), 3.0);
		}
		TEST_METHOD(test_brecket_2)
		{
			string input = { "((3+1)/4 + 2)*5" };
			postfix->to_Postfix(input);
			Assert::AreEqual(postfix->calculation(), 15.0);
		}
		TEST_METHOD(test_function_1)
		{
			string input = { "cos(0)" };
			postfix->to_Postfix(input);
			Assert::AreEqual(postfix->calculation(), 1.0);
		}
		TEST_METHOD(test_function_with_expression_into)
		{
			string input = { "sin(1-2/2)" };
			postfix->to_Postfix(input);
			Assert::AreEqual(postfix->calculation(), 0.0);
		}
		TEST_METHOD(test_function_2)
		{
			string input = { "cos(pi)" };
			postfix->to_Postfix(input);
			Assert::AreEqual(postfix->calculation(), -1.0);
		}
		TEST_METHOD(test_function_3)
		{
			string input = { "ln(e)" };
			postfix->to_Postfix(input);
			Assert::AreEqual(postfix->calculation(), 1.0);
		}
		TEST_METHOD(test_function_4)
		{
			string input = { "log(10)" };
			postfix->to_Postfix(input);
			Assert::AreEqual(postfix->calculation(), 1.0);
		}
		TEST_METHOD(test_function_5)
		{
			string input = { "tg(0)" };
			postfix->to_Postfix(input);
			Assert::AreEqual(postfix->calculation(), 0.0);
		}
		TEST_METHOD(test_function_6)
		{
			string input = { "sqrt(25)" };
			postfix->to_Postfix(input);
			Assert::AreEqual(postfix->calculation(), 5.0);
		}
		TEST_METHOD(test_function_7)
		{
			string input = { "abs(-4)" };
			postfix->to_Postfix(input);
			Assert::AreEqual(postfix->calculation(), 4.0);
		}
		TEST_METHOD(test_error_1)
		{
			
			try {
				string input = { "abs(" };
				postfix->to_Postfix(input);
				postfix->calculation();
			}
			catch (const char* error) {
				Assert::AreEqual("Invalid input. Wrong number of breckets.", error);
			}
		}
		TEST_METHOD(test_error_2)
		{
			try {
				string input = { "12тест" };
				postfix->to_Postfix(input);
			}
			catch (const char* error) {
				Assert::AreEqual("Invalid input. Wrong symbols.", error);
			}
		}
		TEST_METHOD(test_error_3)
		{
			try {
				string input = { "1+2(9)" };
				postfix->to_Postfix(input);
			}
			catch (const char* error) {
				Assert::AreEqual("Invalid input. Number before brecket without operator.", error);
			}
		}
		TEST_METHOD(test_error_4)
		{
			try {
				string input = { "1+1.1.23" };
				postfix->to_Postfix(input);
			}
			catch (const char* error) {
				Assert::AreEqual("Invalid input. Too many dots in one number, don't you think?", error);
			}
		}
		TEST_METHOD(test_error_5)
		{
			try {
				string input = { "1+()" };
				postfix->to_Postfix(input);
			}
			catch (const char* error) {
				Assert::AreEqual("Invalid input. Expression like () was not expected.", error);
			}
		}
		TEST_METHOD(test_error_6)
		{
			try {
				string input = { "1+)" };
				postfix->to_Postfix(input);
			}
			catch (const char* error) {
				Assert::AreEqual("Invalid input. Left bracket required.", error);
			}
		}
		TEST_METHOD(test_error_7)
		{
			try {
				string input = { "1+1+" };
				postfix->to_Postfix(input);
			}
			catch (const char* error) {
				Assert::AreEqual("Invalid input. Too much operators.", error);
			}
		}
	};
}
