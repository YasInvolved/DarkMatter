#ifndef _DM_ENGINE_THREAD_POOL_H_INCLUDED_
#define _DM_ENGINE_THREAD_POOL_H_INCLUDED_

namespace DarkMatter
{
   class ThreadPool
   {
   public:
      ThreadPool(size_t workerCount);
      ~ThreadPool();

      template<typename F, typename... Args>
      auto enqueue(F&& func, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>
      {
         using return_type = std::invoke_result_t<F, Args...>;

         auto task = std::make_shared<std::packaged_task<void()>>(
            std::bind(std::forward<F>(func), std::forward<Args>(args)...)
         );

         std::future<return_type> res = task->get_future();

         {
            std::lock_guard<std::mutex> lock(m_queueMutex);
            m_tasks.emplace([task]() { (*task)(); });
         }

         m_condition.notify_one();
         return res;
      }

   private:
      using Task = std::function<void()>;

      gtl::vector<std::thread> m_workers;
      std::queue<Task> m_tasks;
      std::mutex m_queueMutex;
      std::condition_variable m_condition;
      std::atomic<bool> m_stop = false;
   };
}

#endif