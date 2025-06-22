#include <InterAsync/InterAsync.h>
#include <iostream>

struct A
{
	int a = 0;

	A(int a)
	{
		std::cout << "A constructed\n";
	}

	A(const A&) = default;

	A(A&& other) noexcept
		: a(other.a)
	{
		other.a = 0; // Reset the moved-from object
		std::cout << "A moved\n";
	}

	~A()
	{
		std::cout << "A destructed " << a << "\n";
	}
};

ia::Task<void> ExampleTask(A a)
{
	co_return;
}

void test()
{
	auto task = ExampleTask(A(100));
}

int main()
{
	test();
	return 0;
}