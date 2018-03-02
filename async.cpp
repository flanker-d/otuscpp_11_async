#include <async.h>

namespace async
{
  handle_t connect(std::size_t bulk)
  {
    return async_lib::handles_storage::instance().create_handle(bulk);
  }

  void receive(handle_t handle, const char *data, std::size_t size)
  {
    handle->process_data(data, size);
  }

  void disconnect(handle_t handle)
  {
    async_lib::handles_storage::instance().destroy_handle(handle->id());
  }
}
