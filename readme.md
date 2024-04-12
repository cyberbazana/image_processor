# Image Processor

This console application can edit your photos. Supported filters are: Gauss Blur, Crystallize, Crop, Sharpening,
Edge Detection, Grayscale, Negative.

## Supported file format -- BMP24 bit only.

## Command line format

`{name_of_programm} {input.bmp} {output.bmp}
[-{filter name 1} [params 1] [params 2] ...]
[-{filter name 2} [params 1] [params 2] ...] ...`

### Example
`./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5`

### Filters

#### Crop (-crop width height)

#### Grayscale (-gs)

#### Negative (-neg)

#### Sharpening (-sharp)

#### Edge Detection (-edge threshold)

#### Gaussian Blur (-blur sigma)

#### Crystallize (-cells)