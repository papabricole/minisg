#pragma once

namespace utils {

template<typename T>
class refptr {
public:
    refptr() : p(0)
    {

    }

    refptr(T *other) : p(other)
    {
        if (p)
            p->ref();
    }

    refptr(const refptr<T> &other) : p(other.p)
    {
        if (p)
            p->ref();
    }

    ~refptr()
    {
        if (p) {
            T* backup = p;
            p = 0;
            backup->unref();
        }
    }

    refptr<T> &operator=(const refptr<T> &other)
    {
        *this=other.p;
        return *this;
    }

    refptr<T> &operator=(T *other)
    {
        if(p!=other) {
            T* backup = p;
            p = other;
            if (p)
                p->ref();
            if (backup)
                backup->unref();
        }
        return *this;
    }

    operator bool() const { return p!=0; }
    T *operator->() const { return p; }
    T &operator*() const { return *p; }
    T* get() const { return p; }

private:
    T *p;
};

class refcounted
{
public:
    void ref() {
        refcount++;
    }

    void unref() {
        if (--refcount<=0) {
            destroy();
        }
    }

    /** should be called when it is desired to
        decrement the reference count, but not delete the instance if this
        brings the reference count to zero. This is most useful in returning
        an object to a zero-reference-count state, like it was when it was
        created.
    */
    void unrefNoDelete() {
        refcount--;
    }

    int getRefCount() const {
        return refcount;
    }
protected:
    virtual ~refcounted() { }

    virtual void destroy() {
        delete this;
    }

    refcounted() : refcount(0) { }
    refcounted(const refcounted &) : refcount(0) { }
    refcounted & operator=(const refcounted &) { return *this;}
private:
    int refcount;
};

} // namespace utils
