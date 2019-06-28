# Copyright (c) 2014-present, Facebook, Inc.
# All rights reserved.
#
# This source code is licensed in accordance with the terms specified in
# the LICENSE file found in the root directory of this source tree.

function(deepstateMain)
  set(version "1.0")
  set(archive_name "master")
  set(archive_type "zip")
  set(extract_folder "${CMAKE_CURRENT_BINARY_DIR}/deepstate-master")
  set(hash "9611b0999b31afb95af2dec3d861ba5aa88664cf55693584d7347c852c45e15a")
  set(anchor_file "${extract_folder}/src/include/DeepState.h")

  set(base_url "https://codeload.github.com/trailofbits/deepstate/zip/master")

  downloadRemoteFile2(thirdparty_deepstate "${base_url}" "${archive_name}.${archive_type}" "${hash}")

  set(deepstate_source_code
    "${extract_folder}/src/lib/DeepState.c"
    "${extract_folder}/src/lib/Log.c"
    "${extract_folder}/src/lib/Option.c"  
    "${extract_folder}/src/lib/Stream.c"
  )
  
  list(APPEND additional_anchors ${deepstate_source_code})

  extractLocalArchive(thirdparty_deepstate "${anchor_file}" "${downloadRemoteFile_destination}" "${CMAKE_CURRENT_BINARY_DIR}" ${additional_anchors})

  # So that's possible to download and extract dependencies before building, to have the IDE working correctly
  add_dependencies("prepare_for_ide" "thirdparty_deepstate_extractor")

  add_osquery_library(thirdparty_deepstate EXCLUDE_FROM_ALL
    "${deepstate_source_code}"
  )

  add_dependencies(thirdparty_deepstate thirdparty_deepstate_extractor)

  add_osquery_library(thirdparty_deepstate_headers INTERFACE)
  target_include_directories(thirdparty_deepstate_headers INTERFACE "${extract_folder}/src/include/")

  add_dependencies(thirdparty_deepstate_headers thirdparty_deepstate_extractor)
  target_link_libraries(thirdparty_deepstate PUBLIC
    global_cxx_settings
    thirdparty_deepstate_headers
    thirdparty_glibc_pthread
  )

  #target_link_libraries(thirdparty_deepstate -static "-Wl,--allow-multiple-definition,--no-export-dynamic") 
  #target_compile_options(thirdparty_deepstate PRIVATE -DLIBFUZZER -mno-avx -fsanitize=fuzzer-no-link,undefined)
endfunction()

deepstateMain()
