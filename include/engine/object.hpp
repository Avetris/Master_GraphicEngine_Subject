#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <cstdint>

class Object {
    public:
        Object(uint16_t UID): _UID(UID){}
        uint16_t _UID = 0;
};
#endif
