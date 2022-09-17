set(DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/2DEngine")
set(SOURCES
    src/Engine/EngineFactory.cpp
    src/Engine/Direct2D/Direct2dColour.cpp
    src/Engine/Direct2D/Direct2dEngine.cpp
    src/Utility/Direct2dUtility.cpp
)

set(PUBLIC_INCLUDES
    include/IEngine.h
    include/IDrawable.h
    include/IRender.h
    include/EngineFactory.h
    include/Coordinate2d.h
    include/Colour.h
    include/Size.h
    include/TextAlignment.h
)