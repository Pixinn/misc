
Read the following for a better understanding on how to generate a release of
EZWebGallery.



UBUNTU or DEBIAN:

    install the required packages:
        sudo apt-get install libqt5-dev libmagick++-dev yui-compressor
    build the sources then install ezwebgallery:
        sudo qmake && make install
    
    AFTERWARDS, you can build a functional DEBUG ezwebgallery.



WINDOWS:

    1 - Build a release target using the Visual Studio project located in src.
    2 - Run scripts/prepare_release.bat.
        A proper build of EZWebGallery will be generated in ../distribution/windows
    3 - Optionnaly you can build a full installer, based on NSIS,
        with deployment/windows/Setup_EZWebGallery.nsi 


    IMPORTANT NOTE (Windows only):
    ---------------
    In order to run EZWebGallery, the directories "data" and "skins"
    have to be placed alongside the binary. Thus, if you want to debug a binary,
    YOU HAVE TO manually copy them into the debug directory.



