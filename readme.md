Async

[![Build Status](https://travis-ci.org/flanker-d/otuscpp_11_async.svg?branch=master)](https://travis-ci.org/flanker-d/otuscpp_11_async)

Async bulkmt application

Installation:

```bash
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 379CE192D401AB61
echo “deb http://dl.bintray.com/flankerd/otuscpp trusty main” | sudo tee -a /etc/apt/sources.list
sudo apt update
sudo apt install async
```
Usage:
```c++
#include <async_otus/async.h>

int main(int argc, char **argv)
{
  std::size_t bulk = 5;
  auto h = async::connect(bulk);
  auto h2 = async::connect(bulk);
  async::receive(h, "1", 1);
  async::receive(h2, "1\n", 2);
  async::receive(h, "\n2\n3\n444\n5\n6\n{\na\n", 15);
  async::receive(h, "b\nc\nd\n}\n89\n", 11);
  async::disconnect(h);
  async::disconnect(h2);

  return 0;
}
```

