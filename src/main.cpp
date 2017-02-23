#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>
#include <string>

#include "GlCore.hpp"
#include "GlContext.hpp"
#include "Events.hpp"
#include "Loop.hpp"
#include "Pipeline.hpp"
#include "vec.hpp"
#include "mat.hpp"


bool draw(void)
{
    Pipeline::clear(true, true);
    if (EventManager::keyPressed(KEY(A)))
    {
        return true;
    }
    
    return false;
}

int main(int argc, char** argv)
{
    GlContext::initGL(640, 480);
    GlContext::windowCaption("mtlkit in action !");
    Pipeline::fromXML("assets/xml/PipelineConfig.xml");
    
    renderLoop(30, draw);
    GlContext::endGL();
    return EXIT_SUCCESS;
}
