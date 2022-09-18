set(DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/2DEngine")
set(SOURCES
    src/Engine/EngineFactory.cpp
    src/Engine/Direct2D/Direct2dColour.cpp
    src/Engine/Direct2D/Direct2dEngine.cpp
    src/Utility/Direct2dUtility.cpp
)

set(HEADERS
    src/Macros.h
    src/Engine/Direct2D/Direct2dColour.h
    src/Utility/Direct2dUtility.h
)

set(PUBLIC_INCLUDES
    include/EngineLib/IEngine.h
    include/EngineLib/IDrawable.h
    include/EngineLib/IRender.h
    include/EngineLib/EngineFactory.h
    include/EngineLib/Coordinate2d.h
    include/EngineLib/Colour.h
    include/EngineLib/Size.h
    include/EngineLib/TextAlignment.h
)