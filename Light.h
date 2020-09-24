/*  Purely abstract class for dealing with multiple versions of light casters
    - RAB
 */
#pragma once

#include "Shader.h"
#include "PrintDebug.h"

class Light
{
public:
    /// <summary>
    /// Sends light data to passed in shader program
    /// </summary>
    /// <param name="program"> Shader program being passed in </param>
    virtual void dataToShader(const Shader& program) = 0;

};

