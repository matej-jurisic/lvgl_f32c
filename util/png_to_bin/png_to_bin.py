from PIL import Image
import struct
import os
import sys

def rgb_to_rgb565(r, g, b):
    r5 = (r >> 3) & 0x1F  # Convert 8-bit R to 5-bit R
    g6 = (g >> 2) & 0x3F  # Convert 8-bit G to 6-bit G
    b5 = (b >> 3) & 0x1F  # Convert 8-bit B to 5-bit B
    return (r5 << 11) | (g6 << 5) | b5

def convert_png_to_rgb565_bin(input_png_path, output_bin_path):
    try:
        img = Image.open(input_png_path).convert('RGB')
    except FileNotFoundError:
        print(f"Error: Input PNG file not found at '{input_png_path}'")
        return
    except Exception as e:
        print(f"Error opening or converting PNG: {e}")
        return

    width, height = img.size
    pixel_data = bytearray()

    for y in range(height):
        for x in range(width):
            r, g, b = img.getpixel((x, y))
            rgb565_pixel = rgb_to_rgb565(r, g, b)
            packer_format = '<H'
            pixel_data.extend(struct.pack(packer_format, rgb565_pixel))

    try:
        with open(output_bin_path, 'wb') as f:
            f.write(pixel_data)
        print(f"Successfully converted '{input_png_path}' to '{output_bin_path}'.")
        print(f"Output dimensions: {width}x{height} pixels, color format: RGB565.")
        print(f"File size: {os.path.getsize(output_bin_path)} bytes.")
    except IOError as e:
        print(f"Error writing output file '{output_bin_path}': {e}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <input_png_path> <output_bin_path>")
        sys.exit(1)

    input_png = sys.argv[1]
    output_bin = sys.argv[2]

    print(f"Converting '{input_png}' to raw RGB565 binary...")
    convert_png_to_rgb565_bin(input_png, output_bin)

    print("\n--- Next Steps ---")
    print(f"1. Ensure you have '{input_png}' available.")
    print(f"2. A raw RGB565 binary file '{output_bin}' has been created.")
    print("3. Copy this .bin file to your SD card.")
    print("4. In your C code, ensure image width and image height match the dimensions of your input PNG.")
