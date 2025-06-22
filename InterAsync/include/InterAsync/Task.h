#pragma once
#include <InterAsync/Core.h>
#include <InterAsync/Promise.h>
#include <utility>

BEGIN_PUBLIC_INTER_ASYNC_NAMESPACE

template <typename ReturnType>
class Task
{
	using CoroState = details::CoroutineState<ReturnType>;

public:
	using promise_type = details::Promise<ReturnType>;

	Task(std::shared_ptr<CoroState> frame)
		: state_(std::move(frame))
	{
	}

	~Task()
	{
	}

	Task(const Task&) = delete;

	Task& operator=(const Task&) = delete;

	Task(Task&& other) noexcept
		: state_(std::exchange(other.state_, nullptr))
	{
	}

	Task& operator=(Task&& other) noexcept
	{
		if (this != &other)
		{
			state_ = std::exchange(other.state_, nullptr);
		}
		return *this;
	}

	bool is_ready() const
	{
		return state_ && state_->is_ready();
	}

private:
	std::shared_ptr<CoroState> state_;
};

END_PUBLIC_INTER_ASYNC_NAMESPACE