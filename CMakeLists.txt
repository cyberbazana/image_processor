add_executable(
    image_processor
    image_processor.cpp
        filters/base.cpp
        filters/base.h
        filters/crop.cpp
        filters/crop.h
        filters/sharpening.cpp
        filters/sharpening.h
        bmp.cpp
        producers.cpp
        processor.cpp
        parser.cpp
        image.cpp
        filters/crystal.cpp
        filters/edge_detection.cpp
        filters/gauss.cpp
        filters/grayscale.cpp
        filters/negative.cpp
        exceptions/file_read_exceptions.cpp
        exceptions/filter_exceptions.cpp
        io.cpp
)
