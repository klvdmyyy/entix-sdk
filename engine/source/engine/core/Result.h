#pragma once

#include "engine/core/Error.h"

template<typename T, typename E = Error>
class Result
{
};

template<typename E>
class Result<void, E>
{
};