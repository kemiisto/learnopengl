#include <fmt/format.h>
#include <string>

#ifndef LEARNOPENGL_RESOURCE_H
#define LEARNOPENGL_RESOURCE_H

std::string resourcePath(const std::string& resource)
{
    return fmt::format("../../resources/{}", resource);
}

#endif // LEARNOPENGL_RESOURCE_H
