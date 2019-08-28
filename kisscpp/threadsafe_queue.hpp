// File  : threadsafe_queue.hpp
// Author: Dirk J. Botha <bothadj@gmail.com>
//
// This file is part of kisscpp library.
//
// The kisscpp library is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// The kisscpp library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with the kisscpp library. If not, see <http://www.gnu.org/licenses/>.

#ifndef _THREADSAFE_QUEUE_HPP_
#define _THREADSAFE_QUEUE_HPP_

#include <memory>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include "statable_queue.hpp"

//--------------------------------------------------------------------------------
namespace kisscpp
{

  template <class _qoT, >
  class ThreadsafeQueue : public StatAbleQueue, public boost::noncopyable
  {
    public:
      ThreadsafeQueue() {}

      ~ThreadsafeQueue() {}

      void push(std::shared_ptr<_qoT> p)
      {
        boost::lock_guard<boost::mutex> guard(queueMutex);
        queue->push_back(p);
      }

      std::shared_ptr<_qoT> pop()
      {
        boost::lock_guard<boost::mutex> guard(queueMutex);
        return queue->pop_front();
      }

      std::shared_ptr<_qoT> front()
      {
        boost::lock_guard<boost::mutex> guard(queueMutex);
        return queue->front();
      }

      std::shared_ptr<_qoT> back()
      {
        boost::lock_guard<boost::mutex> guard(queueMutex);
        return queue->back();
      }

      bool empty()
      {
        boost::lock_guard<boost::mutex> guard(queueMutex);
        return queue->empty();
      }

      size_t size()
      {
        boost::lock_guard<boost::mutex> guard(queueMutex);
        return queue->size();
      }

    protected:
    private:
      std::deque<std::shared_ptr<_qoT> > queue;
      boost::mutex                       queueMutex;
  };

}
#endif

