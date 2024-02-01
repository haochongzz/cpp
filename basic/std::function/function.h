#include <functional>

// 默认特化，不实现
template <typename T>
class Function;

// partial specialization.
template <typename Ret, typename... Args>
class Function<Ret(Args...)> {
   private:
    struct CallableBase {
        virtual Ret operator()(Args &&...args) = 0;
        virtual CallableBase *copy() = 0;
        virtual ~CallableBase() {}
    };

    template <typename T>
    struct Callable : public CallableBase {
        Callable(T func) : func_(func) {}
        Ret operator()(Args &&...args) override {
            return func_(std::forward(args)...);
        }
        Callable *copy() const override { return new Callable(func_); }

        T func_;
    };

   public:
    Function() = default;

    template <typename T>
    Function(T func) : callable_(new Callable<T>(func)) {}

    Function(std::nullptr_t) : Function() {}

    // copy constructor/assignment operator
    Function(const Function &other) {
        if (other.callable_)
            callable_ = other.callable_->copy();
        else
            callable_ = nullptr;
    }
    Function &operator=(const Function &other) {
        if (this != &other) {
            delete this;
            new (this) Function(other);
        }
        return *this;
    }

    // move constructor/assignment operator
    Function(Function &&other) {
        callable_ = other.callable_;
        other.callable_ = nullptr;
    }
    Function &operator=(Function &&other) {
        if (this != &other) {
            delete callable_;
            callable_ = other.callable_;
            other.callable_ = nullptr;
        }
        return *this;
    }

    Ret operator()(Args &&...args) {
        return callable_->operator()(std::forward(args)...);
    }

    // conversion operator
    operator bool() const { return callable_; }

    // destructor
    ~Function() { delete callable_; }

   private:
    CallableBase *callable_;
};