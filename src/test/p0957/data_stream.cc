/**
 * Copyright (c) 2017-2018 Mingxin Wang. All rights reserved.
 */

#include <cstdio>
#include <queue>
#include <string>

#include "../../main/p0957/proxy.h"
#include "../../main/p0957/mock/proxy_data_stream_impl.h"

template <class Iterator>
class iterable_source {
 public:
  explicit iterable_source(Iterator fitst, Iterator last)
      : fitst_(std::forward<Iterator>(fitst)),
        last_(std::forward<Iterator>(last)) {}

  auto next() { return std::move(*(fitst_++)); }

  bool has_next() const { return fitst_ != last_; }

 private:
  Iterator fitst_, last_;
};

template <class T>
class fifo_source {
 public:
  T next() {
    T result = std::move(q_.front());
    q_.pop();
    return result;
  }

  bool has_next() const {
    return !q_.empty();
  }

  template <class... Args>
  void emplace(Args&&... args) {
    q_.emplace(std::forward<Args>(args)...);
  }

 private:
  std::queue<T> q_;
};

int main() {
  fifo_source<int> s1;
  for (int i = 0; i < 10; ++i) {
    s1.emplace(i);
  }
  std::reference_proxy<DataStream<double>> p(s1);
  while (p.has_next()) {
    printf("%f\n", p.next());
  }
}
