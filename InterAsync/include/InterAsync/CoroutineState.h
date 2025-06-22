#pragma once
#include <InterAsync/Core.h>
#include <coroutine>
#include <memory>
#include <optional>

BEGIN_DETAILS_INTER_ASYNC_NAMESPACE
template <typename ValueType>
class Promise;

template <typename ValueType>
class CoroutineValueHolder
{
public:
	void set_value(ValueType&& value)
	{
		value_ = std::forward<ValueType>(value);
	}

	void set_value(const ValueType& value)
	{
		value_ = value;
	}

	bool is_ready() const
	{
		return value_ != std::nullopt;
	}

private:
	std::optional<ValueType> value_;
};

template <>
class CoroutineValueHolder<void>
{
public:
	void set_value()
	{
		is_ready_ = true;
	}

	bool is_ready() const
	{
		return is_ready_;
	}

private:
	bool is_ready_ = false;
};

template <typename ValueType>
class CoroutineState : public CoroutineValueHolder<ValueType>
{
	friend class Promise<ValueType>;

public:
	using CoroHandle = std::coroutine_handle<Promise<ValueType>>;

	CoroutineState(const CoroutineState&) = delete;
	CoroutineState(CoroutineState&&) = delete;
	CoroutineState& operator=(const CoroutineState&) = delete;
	CoroutineState& operator=(CoroutineState&&) = delete;

	~CoroutineState()
	{
		if (handle_)
		{
			handle_.promise().state_ = nullptr;
			handle_.destroy();
		}
	}

	static auto create_shared_ptr(CoroHandle handle)
	{
		return std::shared_ptr<CoroutineState>(new CoroutineState(handle));
	}

private:
	CoroutineState(CoroHandle handle)
		: handle_(handle)
	{
		handle_.promise().state_ = this;
	}

	CoroHandle handle_ = nullptr;
};

END_DETAILS_INTER_ASYNC_NAMESPACE