template <typename T>
struct SimpleUniquePointer {
    // default allows us to use both a default and non default constructor
    SimpleUniquePointer() = default;    // Initializes pointer to nullptr
    SimpleUniquePointer(T* pointer)
        : pointer{ pointer } {

        }
    ~SimpleUniquePointer() {
        // Because the pointer is possibly nullptr, the destructor checks before deleting
        if(pointer) delete pointer;
    }

    // you want to allow only a single owner of the pointed-to object,
    // this prevents double frees
    SimpleUniquePointer(const SimpleUniquePointer&) = delete;
    SimpleUniquePointer& operator=(const SimpleUniquePointer&) = delete;

    // Once the move constructor returns the moved-from object is destroyed
    SimpleUniquePointer(SimpleUniquePointer&& other) noexcept
        : pointer{ other.pointer } {
            other.pointer = nullptr;
        }

    SimpleUniquePointer& operator=(SimpleUniquePointer&& other) noexcept {
        if(pointer) delete pointer;     // check explicitly for prior ownership,
        pointer = other.pointer;
        other.pointer = nullptr;    // nsures that the moved-from object doesn’t delete the pointed-to object.
        return *this;
    }

    // obtain direct access to the underlying pointer
    T* get() {
        return pointer;
    }
    private:
    T* pointer;
};
