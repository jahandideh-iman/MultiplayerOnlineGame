
#include "cocos2d.h"

#define AUTOID(className, IDFun)  virtual ID IDFun() const override { return #className; } 

#define  MOGLOG(format, ...) CCLOG(format,  ##__VA_ARGS__)