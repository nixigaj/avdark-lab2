#include "atomic_counters.hpp"

atomic_counter_atomic_incdec::atomic_counter_atomic_incdec()
    : atomic_counter()
    , m_value(0) {
}

int atomic_counter_atomic_incdec::increment() {
    // TODO: Modify this code using atomic fetch_add operations
    int prev_value = m_value.fetch_add(1, std::memory_order_relaxed);
    return prev_value;
}

int atomic_counter_atomic_incdec::decrement() {
    // TODO: Modify this code using atomic fetch_sub operations
    int prev_value = m_value.fetch_sub(1, std::memory_order_relaxed);
    return prev_value;
}

void atomic_counter_atomic_incdec::set(int value) {
    // TODO: Modify this code using atomic store operations
    m_value.store(value, std::memory_order_relaxed);
}

int atomic_counter_atomic_incdec::get() {
    // TODO: Modify this code using atomic load operations
    return m_value.load(std::memory_order_relaxed);
}
