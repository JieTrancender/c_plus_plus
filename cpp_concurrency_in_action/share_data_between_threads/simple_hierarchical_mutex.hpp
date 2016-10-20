#pragma once

#include <mutex>

namespace mtp
{
	class HierarchicalMutex
	{
	public:
		HierarchicalMutex(unsigned long value)
			:m_hierarchy_value(value), m_previous_hierarchy_value(0) {}

		void lock()
		{
			checkForHierarchyViolation();
			m_internal_mutex.lock();
			updateHierarchyValue();
		}

		void unlock()
		{
			m_this_thread_hierarchy_value = m_previous_hierarchy_value;
			m_internal_mutex.unlock();
		}

		bool try_lock()
		{
			checkForHierarchyViolation();
			if (!m_internal_mutex.try_lock())
				return false;
			updateHierarchyValue();
			return true;
		}

	private:
		void checkForHierarchyViolation()
		{
			if (m_this_thread_hierarchy_value <= m_hierarchy_value)
			{
				throw std::logic_error("Mutex hierarchy violated.");
			}
		}

		void updateHierarchyValue()
		{
			m_previous_hierarchy_value = m_this_thread_hierarchy_value;
			m_this_thread_hierarchy_value = m_hierarchy_value;
		}

		std::mutex m_internal_mutex;
		unsigned long const m_hierarchy_value;
		unsigned long m_previous_hierarchy_value;
		static thread_local unsigned long m_this_thread_hierarchy_value;
	};
	thread_local unsigned long HierarchicalMutex::m_this_thread_hierarchy_value(10000000000);
}
