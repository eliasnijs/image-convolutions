ARCHIVE_DIR="archives"
mkdir -p $ARCHIVE_DIR


STB_DIR="stb"
STB_CXX=g++
STB_CXXFLAGS="-Wall -I."
STB_SOURCES=("stb_image.cpp" "stb_write.cpp")


build() {
    local DIR=$1
    local CXX=$2
    local CXXFLAGS=$3
    shift 3
    local SOURCES=("$@")

    cd $DIR || exit 1

    OBJECTS=()
    LIBRARY="lib${DIR}.a"

    echo "building $LIBRARY... "

    for src in "${SOURCES[@]}"; do
	    OBJECTS+=("${src%.cpp}.o")
    done

    for src in "${SOURCES[@]}"; do
	    $CXX $CXXFLAGS -c $src -o "${src%.cpp}.o"
    done


    ar rcs "../$ARCHIVE_DIR/$LIBRARY" "${OBJECTS[@]}"

    rm -f "${OBJECTS[@]}"

    cd .. || exit 1
}

case "$1" in
    all)
        echo '#define STB_IMAGE_IMPLEMENTATION' > "$STB_DIR/stb_image.cpp"
        echo '#include "stb_image.h"' >> "$STB_DIR/stb_image.cpp"
        echo '#define STB_IMAGE_WRITE_IMPLEMENTATION' > "$STB_DIR/stb_write.cpp"
        echo '#include "stb_image_write.h"' >> "$STB_DIR/stb_write.cpp"
        build $STB_DIR $STB_CXX "$STB_CXXFLAGS" "${STB_SOURCES[@]}"
	rm -f "$STB_DIR/stb_image.cpp"
        ;;
    clean)
	echo "cleaning..."
	rm -rf $ARCHIVE_DIR
        ;;
    *)
        echo "Usage: $0 {all|clean}"
        exit 1
        ;;
esac

