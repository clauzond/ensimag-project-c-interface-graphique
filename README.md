## Étapes de progression
- [x] A.1 (Damien) ► *ei_draw.c* (sauf *ei_draw_text* et *ei_copy_surface*)
- [ ] A.2 (Baptiste)  
- [ ] A.3 (Esteban)  
- [ ] A.4  (Esteban)
- [ ] A.5  (Damien)
- [ ] A.6  
- [ ] A.7  
- [ ] A.8  


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

