#pragma once
#include <InterAsync/Core.h>
#include <InterAsync/CoroutineState.h>
#include <coroutine>
#include <memory>

BEGIN_DETAILS_INTER_ASYNC_NAMESPACE

template <typename ValueType>
class PromiseValue
{
public:
	void return_value(this auto& self, ValueType&& value)
	{
		self.get_state().set_value(std::forward<ValueType>(value));
	}

	void return_value(this auto& self, const ValueType& value)
	{
		self.get_state().set_value(value);
	}
};

template <>
class PromiseValue<void>
{
public:
	void return_void(this auto& self)
	{
		self.get_state().set_value();
	}
};

template <typename ValueType>
class Promise : public PromiseValue<ValueType>
{
	friend class CoroutineState<ValueType>;

	using CoroHandle = std::coroutine_handle<Promise>;
	using CoroState = CoroutineState<ValueType>;

public:
	Promise() = default;
	Promise(const Promise&) = delete;
	Promise& operator=(const Promise&) = delete;
	Promise(Promise&&) = delete;
	Promise& operator=(Promise&&) = delete;

	~Promise()
	{
		if (state_)
		{
			state_->handle_ = nullptr;
		}
	}

	auto initial_suspend()
	{
		return std::suspend_never{};
	}

	auto final_suspend() noexcept
	{
		return std::suspend_never{};
	}

	void unhandled_exception()
	{
		std::terminate();
	}

	CoroState& get_state() const
	{
		if (!state_)
		{
			std::abort();
		}
		return *state_;
	}

	CoroHandle get_handle()
	{
		return CoroHandle::from_promise(*this);
	}

	std::shared_ptr<CoroState> get_return_object()
	{
		return CoroState::create_shared_ptr(get_handle());
	}

private:
	CoroState* state_ = nullptr;
};

END_DETAILS_INTER_ASYNC_NAMESPACE