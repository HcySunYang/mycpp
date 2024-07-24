// C++20 coroutines
// What is a coroutine?
// A coroutine is a function that can suspend its execution and return control to the caller,
// possibly many times, and then resume where it left off. The caller of a coroutine can
// then resume the execution at a later time. This is useful when a function has to perform
// a long-running task, but the caller of the function is not interested in the result until
// some time later.

// Any function that uses the co_yield, co_return, or co_await keywords is a coroutine.

// Not all functions can be coroutines. A function can be a coroutine if it meets the following
// requirements:
// 1. The return type of the function is a specialization of std::coroutine_handle.
// 2. The function contains at least one of the following keywords: co_await, co_yield, or co_return.
// 3. constexpr functions cannot be coroutines.
// 4. constructors, destructors, and operators cannot be coroutines.
// 5. The main function cannot be a coroutine.

// The following are the keywords used in coroutines:
// 1. co_await: This keyword is used to suspend the execution of a coroutine until the result
// of an asynchronous operation is available.
// 2. co_yield: This keyword is used to return a value to the caller of the coroutine and
// suspend the execution of the coroutine.
// 3. co_return: This keyword is used to optionaly return a value to the caller of the coroutine and
// stop the execution of the coroutine.

