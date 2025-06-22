#pragma once
#include <InterAsync/Core.h>
#include <InterAsync/Promise.h>
#include <utility>

BEGIN_PUBLIC_INTER_ASYNC_NAMESPACE

template <typename ReturnType>
class Task
{
	using CoroutineState = details::CoroutineState<ReturnType>;

public:
	using promise_type = details::Promise<ReturnType>;

	Task(std::shared_ptr<CoroutineState> frame)
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

	auto& get()
		requires(not std::is_void_v<ReturnType>)
	{
		return state_->get_value();
	}

private:
	std::shared_ptr<CoroutineState> state_;
};

END_PUBLIC_INTER_ASYNC_NAMESPACE