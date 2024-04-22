#pragma once

class AccessTypes {
public:
    static constexpr int PRIVATE = 0;
    static constexpr int PRIVATE2 = 1;
    static constexpr int PUBLIC = 2;
};

class WsJoinTypes {
public:
    static constexpr int AS_PARTICIPANT = 1;
    static constexpr int AS_VIEWER = 2;
};