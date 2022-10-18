file(REMOVE_RECURSE
  "libsockpp-static.a"
  "libsockpp-static.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/sockpp-static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
