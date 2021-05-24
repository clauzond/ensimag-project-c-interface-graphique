## Mercredi jusqu'à 18h30 :
  - Faire du debug
  - Être capable de montrer visuellement toute notre avancée
  - Cleanup le code (formatting, enlever import inutile, enlever TODO...)
  - Pendant cleanup / debug / autre, notez ce qui est important pour la présentation orale (Quelles fonctionnalitées manque-t-il ? Quelles améliorations à faire ?)

## Mercredi 19h00 : upload TEIDE

## Jeudi matin : préparer la présentation
## Jeudi aprèm ou Vendredi : présentation

## Étapes de progression
- [x] A.1 (Damien)
- [x] A.2 (Baptiste)  
- [x] A.3 (Esteban)  
- [ ] A.4  (Esteban)  
    - Manque la création d'une structure de type `ei_widgetclass_t`
    - Manque l'enregistrement des classes
- [ ] A.5  (Damien)
    - Manque la "bonne" implémentation de `ei_placer_run`
- [ ] A.7
    - Manque (?) l'apparence enfoncée du bouton selon emplacement souris


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

