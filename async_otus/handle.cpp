#include <async_otus/handle.h>
#include <interpreter.h>
#include <algorithm>

namespace async_lib
{
  handle::handle(int id, std::size_t bulk)
    : m_id(id)
    , m_interpreter(std::make_shared<interpreter>(bulk))
  {
    m_interpreter->run_observers();
  }

  handle::~handle()
  {
    m_interpreter->stop_observers();
  }

  const int handle::id() const
  {
    return m_id;
  }

  void handle::process_data(const char *data, std::size_t size)
  {
    std::unique_lock<std::mutex> lk(m_mutex);
    m_buffer += {data, size};

    while(true)
    {
      auto term_pos = m_buffer.find('\n');
      if(term_pos != std::string::npos)
      {
        std::string cmd(m_buffer.begin(), m_buffer.begin() + term_pos);
        m_interpreter->process_cmd(cmd);
        m_buffer.erase(m_buffer.begin(), m_buffer.begin() + term_pos + 1);
      }
      else
        return;
    }
  }
}