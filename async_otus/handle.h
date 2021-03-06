#include <memory>
#include <mutex>

class interpreter;

namespace async_lib
{
  class handle
  {
    public:
      handle(int id, std::size_t bulk);
      ~handle();
      const int id() const;
      void process_data(const char *data, std::size_t size);
      void *get_raw_ptr();

    private:
      int m_id;
      std::string m_buffer;
      std::shared_ptr<interpreter> m_interpreter;
      std::mutex m_mutex;
  };
}
