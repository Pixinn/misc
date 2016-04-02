#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <list>
#include <mutex>
#include <condition_variable>

//! \brief A templated *thread-safe* collecttion based on list
//!
//!        pop_front() waits for the notification of a filling method if the list is empty.
//!        The various "emplace" operations are factorized by using the generic "addData_protected".
//!        This generic asks for a concrete operation to use, which can be passed as a lambda.
template< typename T >
class TListConcurrent {

    using const_iterator = typename std::list<T>::const_iterator;

public:
    //! \brief Emplaces a new instance of T in front of the list
    template<typename... Args>
    void emplace_front( Args&&... args )
    {
        addData_protected( [&] {
            _list.emplace_front(std::forward<Args>(args)...);
        } );
    }

    //! \brief Emplaces a new instance of T at the back of the list
    template<typename... Args>
    void emplace_back( Args&&... args )
    {
        addData_protected( [&] {
            _list.emplace_back(std::forward<Args>(args)...);
        } );
    }

    //! \brief Returns the front element and removes it from the collection
    //!
    //!        No exception is ever returned as we garanty that the list is not empty
    //!        before trying to return data.
    T pop_front( void ) noexcept
    {
        std::unique_lock<std::mutex> lock{_mutex};
        while (_list.empty()) {
            _condNewData.wait(lock);
        }
        auto elem = std::move(_list.front());
        _list.pop_front();
        return elem;
    }



private:

    //! \brief Protects the list, calls the provided function and notifies the presence of new data
    //! \param The concrete operation to be used. It MUST be an operation which will add data to the list,
    //!        as it will notify that new data are available!
    template<class F>
    void addData_protected(F&& fct)
    {
        std::unique_lock<std::mutex> lock{ _mutex };
        fct();
        lock.unlock();
        _condNewData.notify_one();
    }

    std::list<T> _list;                     ///< Concrete, not thread safe, storage.
    std::mutex   _mutex;                    ///< Mutex protecting the concrete storage
    std::condition_variable _condNewData;   ///< Condition used to notify that new data are available.
};


#endif // CONCURRENT_QUEUE_H
