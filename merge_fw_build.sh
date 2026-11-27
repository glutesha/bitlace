pio run
pio run -t buildfs
pio pkg exec -p "tool-esptoolpy" -- esptool.py --chip esp32c3 merge_bin -o merged_fw.bin \
  --flash_mode dio --flash_size 4MB \
  0x0 .pio/build/stable/bootloader.bin \
  0x8000 .pio/build/stable/partitions.bin \
  0xe000 ~/.platformio/packages/framework-arduinoespressif32/tools/partitions/boot_app0.bin \
  0x10000 .pio/build/stable/firmware.bin \
  0x290000 .pio/build/stable/littlefs.bin
