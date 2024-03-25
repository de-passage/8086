macro(make_test name)
  add_test(NAME ${name}
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/compare.sh $<TARGET_FILE:dis>
            ${CMAKE_CURRENT_SOURCE_DIR}/${name}
            ${CMAKE_CURRENT_SOURCE_DIR}/${name}.asm)
endmacro()

make_test(single_register_mov)
make_test(many_register_mov)
make_test(more_movs)
make_test(challenge_movs)
