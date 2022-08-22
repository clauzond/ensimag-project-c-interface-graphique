## Utilisation du fichier CMakeLists.txt
#### Ajout des sources
    set(LIB_EI_SOURCES
	${SRC}/ei_draw.c
    ...)
#### Ajout des tests
    # target test_segment

    add_executable(test_segment ${TESTS_SRC}/test_segment.c)
    target_link_libraries(test_segment ei ${PLATFORM_LIB_FLAGS})
#### Modification emplacement SDL (Windows)
    else()

	    set(SDL "C:/[...]/SDL2_windows")

