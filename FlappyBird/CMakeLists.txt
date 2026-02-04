add_executable(FlappyBird
	src/bird.cpp
	src/game.cpp
	src/main.cpp
	src/pipe.cpp
	src/times.cpp
	src/titlescreen.cpp
)

target_include_directories(FlappyBird
	PRIVATE $(CMAKE_CURRECT_SOURCE_DIR)/src
)


target_link_libraries(FlappyBird
	PRIVATE
		sfml-graphics
		sfml-window
		sfml-system
		sfml-audio
)
