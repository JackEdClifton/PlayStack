add_executable(FlagNinja
	src/bullet.cpp
	src/button.cpp
	src/coin.cpp
	src/collectables.cpp
	src/colour.cpp
	src/connection.cpp
	src/enemy.cpp
	src/entity.cpp
	src/flag.cpp
	src/game.cpp
	src/gameDraw.cpp
	src/gameLoops.cpp
	src/gameUserData.cpp
	src/gun.cpp
	src/main.cpp
	src/pch.cpp
	src/player.cpp
	src/sfmlExtension.cpp
	src/staticEntity.cpp
	src/textures.cpp
	src/timer.cpp
)

target_link_libraries(FlagNinja PRIVATE
	sfml-graphics
	sfml-window
	sfml-system
	sfml-audio
	sfml-network
)

target_include_directories(FlagNinja PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/hdr
)

target_precompile_headers(FlagNinja PRIVATE
	hdr/pch.h
)


