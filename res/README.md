# PixelGames Resource File Format Specification

## General information

PixelGames uses Resource files **(\*.res)** to pack multiple, often used assets 
(like images or fonts) into one file with little memory overhead. It is 
compressed using the [zlib](http://zlib.net/) library.

## File structure

The file starts with 5 Bytes: ```0x50 0x47 0x52 0x45 0x53 (PGRES)```, which marks the magic value. The next 8 bytes contain the uncompressed size of the 
data. After that, the compressed part begins with the resource 
entries listed one after another.

### Resource entry

Each entry starts with the name as a null-terminated UTF-8 string. The next byte
marks the type (Text, Number, Binary). Depending on the type, the value changes:

- Text uses a null-terminated UTF-8 string
- Number uses a 64 Bit number (```long```)
- Binary uses a 64 Bit number containing the size of the data, followed immediately by said data