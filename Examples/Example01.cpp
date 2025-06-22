#include <InterAsync/InterAsync.h>
#include <iostream>

struct A
{
	int a = 0;

	A()
	{
		std::cout << this << " A default constructed\n";
	}

	A(int a)
		: a(a)
	{
		std::cout << this << " A constructed: " << a << "\n";
	}

	A(const A&) = delete;
	A& operator=(const A&) = delete;

	A(A&& other) noexcept
		: a(other.a)
	{
		other.a = -1; // Reset the moved-from object
		std::cout << this << " A moved: " << a << "\n";
	}

	A& operator=(A&& other) noexcept
	{
		if (this != &other)
		{
			a = other.a;
			other.a = -1; // Reset the moved-from object
			std::cout << this << " A move assigned: " << a << "\n";
		}
		return *this;
	}

	~A()
	{
		std::cout << this << " A destructed: " << a << "\n";
	}
};

ia::Task<int> ExampleTask(A&& a)
{
	std::cout << "ExampleTask started\n";
	std::cout << "A value: " << a.a << "\n";

	co_return a.a + 42;
}

void test()
{
	auto task = ExampleTask(A(100));

	std::cout << "Result: " << task.get() << "\n";
}

int main()
{
	test();
	return 0;
}