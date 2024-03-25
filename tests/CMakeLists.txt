add_test(NAME single_register_mov
  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/compare.sh $<TARGET_FILE:dis>
          ${CMAKE_CURRENT_SOURCE_DIR}/single_register_mov
          ${CMAKE_CURRENT_SOURCE_DIR}/single_register_mov.asm)
add_test(NAME many_register_mov
  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/compare.sh $<TARGET_FILE:dis>
          ${CMAKE_CURRENT_SOURCE_DIR}/many_register_mov
          ${CMAKE_CURRENT_SOURCE_DIR}/many_register_mov.asm)
