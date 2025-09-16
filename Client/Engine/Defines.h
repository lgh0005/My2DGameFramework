#pragma once

/*================
//    Macros    //
================*/

// Make singleton class
#define DECLARE_SINGLE(classname)                                                \
private:                                                                         \
    classname() = default;                                                       \
    friend class ISingleton<classname>;

// Empty vec2
#define EMPTY_VEC2 glm::vec2(0.0f)
