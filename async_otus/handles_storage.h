#pragma  once

#include <async_otus/handle.h>
#include <mutex>
#include <map>

namespace async_lib
{
  class handles_storage
  {
    public:
      static handles_storage& instance();
      void* create_handle(std::size_t bulk);
      void destroy_handle(int id);

    private:
      handles_storage() = default;
      handles_storage(const handles_storage& root) = delete;
      handles_storage& operator=(const handles_storage&) = delete;

    private:
      std::map<int, std::shared_ptr<handle>> m_handles;
      int m_id = 0;
      std::mutex m_mutex;
  };
}

