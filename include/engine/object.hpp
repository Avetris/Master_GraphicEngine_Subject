#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <cstdint>
#include <engine\handle\handle.hpp>

class Object {
    public:
        Object(uint16_t UID);
        virtual ~Object();
        Handle* getHandle() const;
        uint16_t _UID = 0;

    protected:
        Handle* _handle;
};
#endif
