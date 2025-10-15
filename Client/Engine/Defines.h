#pragma once

/*================
//    Macros    //
================*/

// Make singleton class
#define DECLARE_SINGLE(classname)                                                \
private:                                                                         \
    classname() = default;                                                       \
    friend class ISingleton<classname>;

// [TEMP] Empty vec2
#define EMPTY_VEC2 glm::vec2(0.0f)

// Dummy Transform
#define DUMMY_TRANSFORM                                                         \
"DummyTransform", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)