#include "user_locks.hpp"

user_lock_dekker::user_lock_dekker()
    : user_lock() {
    m_flag[0].store(false); 
    m_flag[1].store(false);
    m_turn.store(0);
}

void user_lock_dekker::lock(int thread_id) {
    // TODO: Implement the lock acquire part of the Dekker algorithm here
    int other = 0;
    if (thread_id == 0) other = 1;

    // Hardware fence: StoreLoad barrier (x86 mfence/sfence+lfence, or std::atomic_thread_fence(memory_order_seq_cst)).
    m_flag[thread_id].store(true);
    // fence here in concept: ensure flag[thread_id]=true is globally visible before reading m_flag[other]/m_turn

    while (m_flag[other].load()){
        if (m_turn.load() != thread_id){
            m_flag[thread_id].store(false);
            // fence here: ensure flag[thread_id]=false is globally visible before reading m_turn

            while (m_turn.load() != thread_id);
            // fence here: ensure m_turn observation is committed with respect to later flag set

            m_flag[thread_id].store(true);
            // fence here: ensure flag[thread_id]=true is globally visible before re-checking other flag
        }
    }
}

void user_lock_dekker::unlock(int thread_id) {
    // TODO: Implement the lock release part of the Dekker algorithm here
    int other = 0;
    if (thread_id == 0) other = 1;
    m_turn.store(other);
    m_flag[thread_id].store(false);
}
