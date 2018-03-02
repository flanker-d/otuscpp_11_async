#pragma once

#include <cstddef>
#include <handles_storage.h>

namespace async
{
  using handle_t = std::shared_ptr<async_lib::handle>;

  handle_t connect(std::size_t bulk);
  void receive(handle_t handle, const char *data, std::size_t size);
  void disconnect(handle_t handle);
}