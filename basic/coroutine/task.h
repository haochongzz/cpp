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
  // Constructors.
  Task() : _handle() {}
  Task(promise_type *p);

  // Copy and move constructors.
  Task(const Task &task);
  Task(Task &&task);

  // Resume execution of the suspended coroutine.
  void resume() const {
    _handle->resume();
  }

  // Check if the suspended coroutine is at final suspend point. 
  bool done() const {
    _handle->done();
  }

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

struct YieldAwaiter {
  bool await_ready() noexcept { return false; }
  void await_suspend(std::coroutine_handle<> h) noexcept {
    _awaiting.promise().set_awaiting(h);
  }
  void await_resume() noexcept {}

  std::coroutine_handle<> _awaiting;
};

struct BasePromise {
  std::suspend_always initial_suspend() noexcept { return {}; }
  FinalAwaiter final_suspend() noexcept { return FinalAwaiter{_awaiting}; }

  // handle exception.
  void unhandled_exception() { std::current_exception(); }

  void set_awaiting(std::coroutine_handle<> h) { _awaiting = h; }

  // operand of co_await.
  template <typename T>
  TaskAwaiter<T> await_transform(Task<T> &&awaited) {
    return TaskAwaiter<T>{std::move(awaited)};
  }

  // operand of co_yield.
  struct yield_type {};
  YieldAwaiter yield_value(yield_type) {
    return YieldAwaiter{_awaiting};
  }

 private:
  std::coroutine_handle<> _awaiting;
};

// specialization.
template <>
struct Promise<void> : public BasePromise {
  Task<void> get_return_object() { return Task<void>{this}; }

  void return_void() noexcept {}
};

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

/******************************************************************************/
/* Implementations.                                                           */
/******************************************************************************/
// implementation of Task. 
template <typename T>
Task<T>::Task(promise_type *p)
    : _handle(new std::coroutine_handle<>(
          std::coroutine_handle<promise_type>::from_promise(*p))) {}

template <typename T>
Task<T>::Task(const Task &task) : _handle(task._handle) {}

template <typename T>
Task<T>::Task(Task &&task) : _handle(task._handle) {
  task._handle = nullptr;
}

// implementation of TaskAwatier.
template <typename T>
std::coroutine_handle<> TaskAwaiter<T>::await_suspend(
    std::coroutine_handle<> h) noexcept {
  _awaited.promise().set_awaiting(h);
  return _awaited.handle();
}

template <typename T>
T TaskAwaiter<T>::await_resume() noexcept {
  return _awaited.promise().get_value();
}


}  // namespace task

#endif
