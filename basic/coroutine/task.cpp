#include "./task.h"

namespace task {

std::coroutine_handle<> FinalAwaiter::await_suspend(std::coroutine_handle<> h) noexcept {
  if (_awaiting) { 
    return _awaiting;
  }
  return std::noop_coroutine();
}

}  // namespace task
