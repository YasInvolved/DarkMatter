#ifndef _DM_ENGINE_THREAD_POOL_H_INCLUDED_
#define _DM_ENGINE_THREAD_POOL_H_INCLUDED_

namespace DarkMatter
{
   class ThreadPool
   {
   public:
      ThreadPool(size_t workerCount);
      ~ThreadPool();

      template <typename F, typename... Args>
      using FutureType = std::future<std::invoke_result_t<F, Args...>>;

      template<typename F, typename... Args>
      auto enqueue(F&& func, Args&&... args) -> FutureType<F, Args...>
      {
         using result_t = std::invoke_result_t<F, Args...>;

         auto task = std::make_shared<std::packaged_task<result_t()>>(
            [func = std::forward<F>(func), ... args = std::forward<Args>(args)]() mutable {
               return std::invoke(std::move(func), std::move(args)...);
            }
         );

         FutureType<F, Args...> res = task->get_future();

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