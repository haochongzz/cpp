#include <memory>

// define a shared_pointer
std::shared_ptr<int> ip(new int());  // 值初始化为0
std::shared_ptr<int> ip(new int);    // 默认初始化，*ip的值是未定义的。

auto ip2 = std::make_shared<int>(42);

// 利用初始化器initializer来推断类型
auto p1 = new auto(obj);

// 交换p和q中的指针
std::swap(p, q);

// deleter 删除器
// 默认情况下，智能指针使用delete释放所关联的对象。我们可以将smart
// pointer绑定到一个指向其他类型资源的pointer上，但必须提供自己的删除器deleter。
void deleter(T *p);
std::shared_ptr<int> sp(p, deleter);

// unique_ptr 拥有他指向的对象，因此不能拷贝或赋值。
std::unique_ptr<int> up(new int(42));

// 释放对指向对象的控制权，返回指针。
up.release();
// 释放指向对象的控制权，
up.reset(other_up.release());