#include <handles_storage.h>

namespace async_lib
{
  handles_storage &handles_storage::instance()
  {
    static handles_storage inst;
    return inst;
  }

  std::shared_ptr<handle> handles_storage::create_handle(std::size_t bulk)
  {
    std::unique_lock<std::mutex> lk(m_mutex);
    auto h = std::make_shared<handle>(m_id, bulk);
    m_handles.insert(std::make_pair(m_id, h));
    ++m_id;
    return h;
  }

  void handles_storage::destroy_handle(int id)
  {
    std::unique_lock<std::mutex> lk(m_mutex);
    auto it = m_handles.find(id);
    if(it != m_handles.end())
      m_handles.erase(it);
  }
}
