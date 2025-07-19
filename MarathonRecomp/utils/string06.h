#ifndef STRING06
#define STRING06
#include <utils/xbe.h>
//Fake std::string BXT
union string06BXT {
    string06BXT() {
        memset(&_buffer_str, 0, 0x10);
    }
    char _buffer_str[0x10]; // SSO buffer (16 bytes)
    xbe<const char*, big_endian_tag, uint32_t> _ptr_str; // Pointer for long strings

};
//Fake std::string
struct string06 {
    xbe<uint32_t> proxy; // Some control field, purpose unclear 0
    string06BXT _buffer; //4-0x14
    xbe<uint32_t> _size; //0x14
    xbe<uint32_t> _capacity; // = 0x18

    string06(){
        proxy = (uint32_t)0;
        _capacity = (uint32_t)0xF;
        _size = (uint32_t)0;
        _buffer._buffer_str[0] = '\0'; // Initialize empty string
    }
    string06(const char* str) {
        proxy = (uint32_t)0;
        _capacity = (uint32_t)0xF;
        _size = (uint32_t)0;
        _buffer._buffer_str[0] = '\0'; // Initialize empty string
        size_t len = strlen(str);
        if (len <= 0x10) {
			_capacity = 0xF;
            memcpy(_buffer._buffer_str, str, len + 1);
            _size = static_cast<uint32_t>(len);
        }
        else {
            // Use heap allocation
            if (is_short() || capacity() < len + 1) {
                // Allocate new memory


                char* new_buf = (char*)g_userHeap.Alloc(len + 1);
                memcpy(new_buf, str, len + 1);
                _buffer._ptr_str = new_buf;
                _capacity = static_cast<uint32_t>(len + 1);
            }
            else {
                // Reuse existing allocation
                memcpy(const_cast<char*>((const char*)_buffer._ptr_str), str, len + 1);
            }
            _size = static_cast<uint32_t>(len);
        }
   
    }

    // Get whether we're using SSO
    bool is_short() const {
        return (uint32_t)_size <= 0x10;
    }

    // Get the size
    size_t size() const {
        return (uint32_t)_size;
    }

    // Get the capacity
    size_t capacity() const {
        return (uint32_t)_capacity;
    }

  


  

    // Get the string data
    const char* data() const {
        return is_short() ? _buffer._buffer_str
            : (const char*)_buffer._ptr_str;
    }

    const char* c_str() const {
        return is_short() ? _buffer._buffer_str
            : (const char*)_buffer._ptr_str;
    }

    // Copy constructor
    string06(const string06& other):string06(other.c_str()) {
    }
    // Destructor
    ~string06() {
        if (!is_short()) {
            g_userHeap.Free((void*)(const char*)_buffer._ptr_str);
        }
    }

    explicit operator std::string() const {
        return std::string(data(), size());
    }
    // Assignment from std::string
    string06& operator=(const std::string& str) {
        string06(str.c_str());
        return *this;
    }
  

};
#endif
