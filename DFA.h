#pragma once
#include "automat.h"

namespace automat {
    class DFA : public baseAutomat {
      public:
        virtual State* createState() override;
    };
}
