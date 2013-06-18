
#ifndef _UNITTEST_H_INCLUDED_
#define _UNITTEST_H_INCLUDED_

//////////////////////////////////////////////////////////////////////////
//
// UnitTest.h
//
// A smart unit test framework, which is adapted from the other two libs
//
// ShortCUT, a short cpp unit testing framework by Todd Lucas
// http://www.codeproject.com/KB/applications/shortcut.aspx
//
// MiniCppUnit, coded by Pau Arum and David Garcia
// http://www.iua.upf.es/~parumi/MiniCppUnit/
//
// Author, atyuwen
// Date, Nov.8, 2009
//
//////////////////////////////////////////////////////////////////////////

#include <Windows.h>
#include <string>
#include <iostream>
#include <sstream>
#include <list>
#include <cmath>
#include <cfloat>

namespace
{
	template <typename T> inline bool isnan(T x)
	{ 
		return _isnan(x) != 0; 
	}
	template <typename T> inline bool isinf(T x)
	{ 
		return _finite(x) == 0;
	}

	class ColorScheme
	{
	public:
		enum ConsoleColor
		{
			Black,
			DarkBlue,
			DarkGreen,
			DarkCyan,
			DarkRed,
			DarkPurple,
			DarkYellow,
			DarkWhite,
			Gray,
			Blue,
			Green,
			Cyan,
			Red,
			Purple,
			Yellow,
		};

	public:
		ColorScheme (ConsoleColor frontColor = DarkWhite, ConsoleColor backColor = Black)
		{
			m_frontColor = frontColor;
			m_backColor = backColor;
		}

		ColorScheme (const ColorScheme & colorScheme)
		{
			m_frontColor = colorScheme.m_frontColor;
			m_backColor = colorScheme.m_backColor;
		}

		friend ColorScheme operator | (ConsoleColor frontColor, ConsoleColor backColor)
		{
			return ColorScheme(frontColor, backColor);
		}

		friend std::ostream& operator << (std::ostream& os, ConsoleColor frontColor)
		{
			return operator << (os, ColorScheme(frontColor));
		}

		friend std::ostream& operator << (std::ostream& os, const ColorScheme& colorScheme)
		{
			WORD word = (static_cast<int>(colorScheme.m_backColor) << 4)
				| (static_cast<int>(colorScheme.m_frontColor));
			SetConsoleTextAttribute(HandleOut(), word);
			SetConsoleTextAttribute(HandleError(), word);
			return os;
		}

	private:
		static HANDLE HandleOut(){static HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); return hOut;}
			
		static HANDLE HandleError(){static HANDLE hError = GetStdHandle(STD_ERROR_HANDLE); return hError;}

	private:
		ConsoleColor m_frontColor;
		ConsoleColor m_backColor;
	};
}

namespace UnitTest
{
	class Test
	{
	public:
		virtual ~Test(){}

	public:
		virtual void Run() = 0;
		virtual std::string Name() const = 0;
	};

	class TestFailedException
	{
	public:
		void Pass(){}
	};

	class TestsListener
	{	
	private:
		TestsListener()
			: m_currentTest(0)
			, m_numExecuted(0)
			, m_numFailed(0)
			, m_numExceptions(0){}

	public:
		static TestsListener *Instance()
		{
			static TestsListener instance;
			return &instance;
		}

		std::stringstream &Log(){return LogCurrentTest(m_log);}

		std::string LogString(){std::string log = m_log.str(); m_log.str(""); return log;}

		void NotifyTestRun(Test *test){PrintRunPrompt(); m_currentTest = test; ++m_numExecuted;}

		void NotifyTestPassed(){PrintPassedPrompt();}
			
		void NotifyTestFailed(){PrintFailedPrompt(); ++m_numFailed; throw TestFailedException();}
			
		void NotifyTestThrown(){PrintThrownPrompt(); ++m_numExceptions;}
			
		bool AllTestsPassed(){return m_numFailed == 0 && m_numExceptions == 0;}

		void Summary()
		{
			std::cout << ColorScheme() << "Summary" << std::endl;
			std::cout << ColorScheme() << "  Executed Tests: " << m_numExecuted << std::endl;
			std::cout << ColorScheme::Green << "  Passed Tests: " << m_numExecuted - m_numFailed - m_numExceptions << std::endl;
				
			if (m_numFailed > 0)
				std::cout << ColorScheme::Red << "  Failed Tests: " << m_numFailed << std::endl;
				
			if (m_numExceptions > 0)
				std::cout << ColorScheme::Yellow << "  Unexpected Exceptions: " << m_numExceptions << std::endl;	
		}

	private:
		std::stringstream& LogCurrentTest(std::stringstream &log)
		{
			if (m_currentTest != 0)
			{
				log << std::endl;
				log << "Test Failed -- " << m_currentTest->Name() << std::endl;
			}
			return log;
		}

		static void PrintRunPrompt(){std::cout << ColorScheme() << ".";}

		static void PrintPassedPrompt(){std::cout << ColorScheme::Green << "O";}

		static void PrintFailedPrompt(){std::cout << ColorScheme::Red << "X";}

		static void PrintThrownPrompt(){std::cout << ColorScheme::Yellow << "E";}

	private:
		std::stringstream m_log;
		Test *m_currentTest;
		int m_numExecuted;
		int m_numFailed;
		int m_numExceptions;
	};

	
	template <typename ConcreteTestFixture> 
	class TestFixture : public Test
	{
	protected:
		typedef ConcreteTestFixture ConcreteFixture;
		typedef void (ConcreteFixture::*TestMethod)();

		class TestCase : public Test
		{
		public:
			TestCase(ConcreteFixture *fixture, TestMethod method, const std::string & name)
				: m_fixture(fixture)
				, m_method(method)
				, m_name(name){}

		public:
			virtual void Run()
			{
				TestsListener::Instance()->NotifyTestRun(this);
				try
				{
					(m_fixture->*m_method)();
				}
				catch (std::exception &e)
				{
					TestsListener::Instance()->NotifyTestThrown();
					TestsListener::Instance()->Log()
						<< "  std::exception: " << e.what() << std::endl;
					return;
				}
				catch (TestFailedException &e)
				{
					e.Pass();
					return;
				}
				catch (...)
				{
					TestsListener::Instance()->NotifyTestThrown();
					TestsListener::Instance()->Log()
						<< "  Non Standard Exception." << std::endl;
					return;
				}
				TestsListener::Instance()->NotifyTestPassed();
			}

			virtual std::string Name() const{return m_name;}
			
		private:
			ConcreteFixture *m_fixture;
			TestMethod m_method;
			std::string m_name;
		};

	public:
		TestFixture(const std::string &name = "A Test Fixture")
			: m_name(name){}

		~TestFixture()
		{
			for (TestIter it=m_testCases.begin(); it!=m_testCases.end(); ++it)
			{
				Test *test = *it;
				delete test;
			}
		}

	public:
		virtual void Setup(){}
		virtual void Teardown(){}
		virtual std::string Name() const{return m_name;}

		void AddTest(ConcreteFixture *fixture, TestMethod method, const std::string &name)
		{
			TestCase *p = new TestCase(fixture, method, name);
			m_testCases.push_back(p);
		}

		virtual void Run()
		{
			ListTests();
			for (TestIter it=m_testCases.begin(); it!=m_testCases.end(); ++it)
			{
				Setup();
				Test *test = *it;
				test->Run();
				Teardown();
			}
		}

	private:
		void ListTests() const
		{
			std::cout << ColorScheme() << std::endl;
			std::cout << "+ " << Name() << std::endl;
			for (ConstTestIter it=m_testCases.begin(); it!=m_testCases.end(); ++it)
			{
				std::cout << "  - "<< (*it)->Name() << std::endl;
			}
		}

	private:
		typedef std::list<Test*> TestCases;
		typedef TestCases::iterator TestIter;
		typedef TestCases::const_iterator ConstTestIter;

		TestCases m_testCases;
		std::string m_name;
	};

	class Assert
	{
	private:
		static std::string TagFile(){return "  File: ";}
		static std::string TagLine(){return "  line: ";}
		static std::string TagExpression(){return "  Failed Expression: ";} 
		static std::string TagResult(){return "  Result: ";} 
		static std::string TagExpected(){return "  Expected: ";}
		static std::string TagReason(){return "  Reason: ";}

	public:
		template<typename Type>
		static void AssertEquals(const Type &result, const Type &expected, const char *file="", int line=0)
		{
			if (result != expected)
			{
				TestsListener::Instance()->Log()
					<< TagFile() << file << std::endl
					<< TagLine() << line << std::endl
					<< TagResult() << result << std::endl
					<< TagExpected() << expected << std::endl;
				TestsListener::Instance()->NotifyTestFailed();
			}
		}

		static void AssertEquals(const char *result, const char *expected, const char *file="", int line=0)
		{
			AssertEquals(std::string(result), std::string(expected), file, line);
		}

		static void AssertEquals(const bool &result, const bool &expected, const char *file="", int line=0)
		{
			AssertEquals(result?"true":"false",expected?"true":"false", file, line);
		}

		static void AssertEquals(const float &result, const float &expected, const char *file="", int line=0)
		{
			AssertEqualsEpsilon(result, expected, 1E-6, file, line);
		}

		static void AssertEquals(const double &result, const double &expected, const char *file="", int line=0)
		{
			AssertEqualsEpsilon(result, expected, 1E-6, file, line);
		}

		static void AssertTrue(char* strExpression, bool expression, const char* file="", int line=0)
		{
			if (!expression)
			{
				TestsListener::Instance()->Log()
					<< TagFile() << file << std::endl
					<< TagLine() << line << std::endl
					<< TagExpression() << strExpression << std::endl;
				TestsListener::Instance()->NotifyTestFailed();
			}	
		}

		static void AssertEqualsEpsilon(const double& result, const double& expected, const double& epsilon,
			const char *file="", int line=0)
		{
			if (isnan(result) && isnan(expected))
				return;

			double base = std::abs(expected) + 1;
			double absError = (isinf(base))? epsilon : epsilon * base;
			if (!isnan(result) && !isnan(expected) && std::abs(result - expected) <= absError)
				return;

			TestsListener::Instance()->Log()
				<< TagFile() << file << std::endl
				<< TagLine() << line << std::endl
				<< TagResult() << result << std::endl
				<< TagExpected() << expected << std::endl;
			TestsListener::Instance()->NotifyTestFailed();
		}

		static void Fail(const std::string &why, const char *file, int line)
		{
			TestsListener::Instance()->Log()
				<< TagFile() << file << std::endl
				<< TagLine() << line << std::endl
				<< TagReason() << why << std::endl;
			TestsListener::Instance()->NotifyTestFailed();
		}
	};

	class TestFixtureFactory
	{
	private:
		typedef Test* (*FixtureCreator)();
		typedef std::list<FixtureCreator> Creators;
		typedef Creators::iterator CreatorIter;
		
	private:
		TestFixtureFactory(){}
		
	public:
		static TestFixtureFactory *Instance()
		{
			static TestFixtureFactory instance;
			return &instance;
		}
		
		bool RunTests()
		{
			for (CreatorIter it=m_creators.begin(); it!=m_creators.end(); ++it)
			{
				FixtureCreator creator = *it;
				Test *test = creator();
				test->Run();
				delete test;
			}

			std::string errorlog =  TestsListener::Instance()->LogString();
			std::cout << ColorScheme::Cyan << "\n\nError Details" << std::endl;
			std::cout << ColorScheme::Gray << errorlog << std::endl;
				
			TestsListener::Instance()->Summary();
			std::cout << ColorScheme();
			return TestsListener::Instance()->AllTestsPassed();
		}

		void AddFixtureCreator(FixtureCreator creator)
		{
			m_creators.push_back(creator);
		}

	private:
		Creators m_creators;
	};


	#define RUN_TESTS() \
		UnitTest::TestFixtureFactory::Instance()->RunTests()
		
	#define REGISTER_FIXTURE(ConcreteTestFixture) \
		\
		Test * ConcreteTestFixture##Creator() {return new ConcreteTestFixture;} \
		\
		class ConcreteTestFixture##Registrar \
		{ \
		public: \
			ConcreteTestFixture##Registrar() \
			{ \
				TestFixtureFactory::Instance()->AddFixtureCreator( \
				ConcreteTestFixture##Creator); \
			} \
		}; \
		static ConcreteTestFixture##Registrar static##ConcreteTestFixture;

	#define TEST_FIXTURE(ConcreteFixture) \
		ConcreteFixture() : TestFixture<ConcreteFixture>(#ConcreteFixture)

	#define TEST_CASE(TestMethod) \
		AddTest(this, &ConcreteFixture::TestMethod, #TestMethod);
		
	#define ASSERT_EQUALS(result, expected) \
		Assert::AssertEquals(result, expected, __FILE__, __LINE__);

	#define ASSERT_EQUALS_EPSILON(result, expected, epsilon) \
		Assert::AssertEqualsEpsilon(result, expected, epsilon, __FILE__, __LINE__);

	#define ASSERT(exp) \
		Assert::AssertTrue(#exp, exp, __FILE__, __LINE__);

	#define FAIL(why) \
		Assert::Fail(#why, __FILE__, __LINE__);
}


#endif // _UNITTEST_H_INCLUDED_