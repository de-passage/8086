add_test(NAME basic
  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/compare.sh $<TARGET_FILE:dis>
          ${CMAKE_CURRENT_SOURCE_DIR}/single_register_mov
          ${CMAKE_CURRENT_SOURCE_DIR}/single_register_mov.asm)
