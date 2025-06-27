#include <DarkMatter/Engine/ThreadPool.h>

using ThreadPool = DarkMatter::ThreadPool;

ThreadPool::ThreadPool(size_t workerCount)
{
   for (size_t i = 0; i < workerCount; i++)
   {
      m_workers.emplace_back([this]()
         {
            while (true)
            {
               Task task;

               {
                  std::unique_lock<std::mutex> lock(m_queueMutex);
                  m_condition.wait(lock, [this] { return m_stop.load(std::memory_order_acquire) || !m_tasks.empty(); });

                  if (m_stop.load(std::memory_order_acquire) && m_tasks.empty())
                     return;

                  task = std::move(m_tasks.front());
                  m_tasks.pop();
               }

               task();
            }
         }
      );
   }
}

ThreadPool::~ThreadPool()
{
   m_stop.store(true, std::memory_order_release);
   m_condition.notify_all();

   for (auto& worker : m_workers)
      worker.join();
}