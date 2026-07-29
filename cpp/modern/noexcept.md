The short answer is: **No, it is not automatic for most functions.** While C++ makes a few things `noexcept` behind the scenes, regular functions default to assuming they *can* throw an exception. If you want the performance benefits and safety guarantees of `noexcept`, you usually have to mark it yourself.

Here is the breakdown of what the compiler does automatically, why manually adding `noexcept` matters, and exactly when you should use it.

---

## What C++ Does Automatically (The Defaults)

C++ only assumes a function is `noexcept` in a few specific, safety-critical scenarios:

1. **Destructors:** Since C++11, all destructors are implicitly `noexcept` by default. Throwing an exception during stack unwinding causes an immediate crash (`std::terminate`), so the language protects you here.
2. **Deallocation Functions:** Functions like `operator delete` or `operator delete[]` are automatically `noexcept`.
3. **Implicitly Generated Special Members:** If the compiler auto-generates your default constructor, copy/move constructor, or assignment operators, they will be `noexcept` **only if** every member variable and base class they call is also `noexcept`.

For any standard function you write (like `void calculate_score()`), the compiler defaults to assuming it *might* throw an exception, even if there isn't a single `throw` statement inside it. Why? Because the compiler can't easily look inside other compiled libraries or translation units to prove a function won't throw.

---

## Why Use `noexcept`? (The "Vector Move" Trick)

The primary reason to use `noexcept` isn't just to document your code—it's for **massive performance optimizations**.

The most famous example is **`std::vector` reallocation**. When a vector runs out of space, it must allocate a larger block of memory and move the existing elements over.

* **Without `noexcept`:** If your class's move constructor is *not* marked `noexcept`, `std::vector` plays it safe. To guarantee it won't lose your data if an exception throws halfway through, it will **copy** all elements to the new memory instead of moving them. For large objects, this ruins performance.
* **With `noexcept`:** The vector knows it is safe to use fast move semantics.

---

## When You *Should* Explicitly Use `noexcept`

You should sprinkle `noexcept` on functions that are guaranteed to never throw, or functions where throwing an exception means the program is toast anyway.

### 1. Move Constructors and Move Assignment Operators

This is the most critical place. Always mark them `noexcept` so standard library containers can optimize their internals.

```cpp
MyClass(MyClass&& other) noexcept : data_(std::move(other.data_)) {}

```

### 2. Swap Functions

Custom swap functions are heavily utilized by standard algorithms. They should never throw.

```cpp
friend void swap(MyClass& first, MyClass& second) noexcept {
    using std::swap;
    swap(first.data_, second.data_);
}

```

### 3. Simple Getters and Setters

If a function just returns a primitive type, reads a pointer, or performs basic math, mark it.

```cpp
int get_id() const noexcept { return id_; }

```

### 4. Leaf Functions That Bridge to C

If you are writing functions meant to be called by C code (like an API or a callback), exceptions cannot cross the language boundary. Mark them `noexcept`.

---

## When You Should *NOT* Use It

> ⚠️ **The Golden Rule:** Never lie to the compiler.

If you mark a function `noexcept` and an exception *does* escape from it at runtime, the program calls `std::terminate()` and **crashes instantly**. No stack unwinding, no catching it later.

Avoid `noexcept` if:

* The function calls other code that might throw (like `std::string` operations that might throw `std::bad_alloc`).
* The function uses `dynamic_cast` on references (which throws `std::bad_cast`).
* You are writing a wide-contract function where you validate parameters and throw an error if they are invalid.
