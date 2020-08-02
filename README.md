# Intel
conan remote add conan "https://api.bintray.com/conan/conan/public-conan"
conan remote add conan "https://api.bintray.com/conan/conan-community/conan"
conan search parallelstl --remote=conan-center

not work:
 [requires]
 TBB/2019_U9@conan/stable
 parallelstl/20181004@conan/stable


# HPX
conan search hpx --remote=conan-center