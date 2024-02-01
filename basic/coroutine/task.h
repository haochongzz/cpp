#ifndef TASK_H_
#define TASK_H_

#include <coroutine>
#include <exception>
#include <optional>
#include <type_traits>

namespace task {

// forward declarations.
template <typename T>
struct Promise;
template <typename T>
struct TaskAwaiter;

template <typename T>
class [[nodiscard]] Task {
  using promise_type = Promise<T>;

  friend struct TaskAwaiter<T>;

 public:
  Task() : _handle() {}
  Task(promise_type *p);

 private:
  std::coroutine_handle<> handle() { return *_handle; }
  promise_type &promise() {
    return std::coroutine_handle<promise_type>::from_address(_handle->address())
        .promise();
  }

  std::coroutine_handle<> *_handle;
};

struct FinalAwaiter {
  bool await_ready() noexcept { return false; }
  std::coroutine_handle<> await_suspend(std::coroutine_handle<> h) noexcept;
  void await_resume() noexcept {}
  std::coroutine_handle<> _awaiting;
};

template <typename T>
struct TaskAwaiter {
  bool await_ready() noexcept { return false; }
  std::coroutine_handle<> await_suspend(std::coroutine_handle<> h) noexcept;
  T await_resume() noexcept;

  Task<T> &&_awaited;
};

struct BasePromise {
  std::suspend_always initial_suspend() noexcept { return {}; }
  FinalAwaiter final_suspend() noexcept { return FinalAwaiter{_awaiting}; }

  // handle exception.
  void unhandled_exception() { std::current_exception(); }

  void set_awaiting(std::coroutine_handle<> h) { _awaiting = h; }

 private:
  std::coroutine_handle<> _awaiting;
};

// specialization.
template <>
struct Promise<void> : public BasePromise {};

template <typename T>
struct Promise : public BasePromise {
  Task<T> get_return_object() { return Task<T>{this}; }

  void return_value(T value) {
    if constexpr (std::is_move_constructible_v<T>) {
      _value.emplace(std::move(value));
    } else {
      _value.emplace(value);
    }
  }

  T get_value() const {
    if constexpr (std::is_move_constructible_v<T>) {
      return *std::move(_value);
    } else {
      return *_value;
    }
  }

 private:
  std::optional<T> _value;
};

// implementations.
template <typename T>
std::coroutine_handle<> TaskAwaiter<T>::await_suspend(
    std::coroutine_handle<> h) noexcept {
  _awaited.promise().set_awaiting(h);
  return _awaited.handle();
}

template <typename T>
T TaskAwaiter<T>::await_resume() noexcept {
  return _awaited.promise.get_value();
}

template <typename T>
Task<T>::Task(promise_type *p)
    : _handle(new std::coroutine_handle<>(
          std::coroutine_handle<promise_type>::from_promise(*p))) {}

}  // namespace task

#endif
