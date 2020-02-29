# QEmu
brew install qemu

# Home for out tests
mkdir ~/arm-emu
cd ~/arm-emu

# Download initrd and kernel
wget http://ftp.de.debian.org/debian/dists/jessie/main/installer-armel/current/images/versatile/netboot/initrd.gz

wget http://ftp.de.debian.org/debian/dists/jessie/main/installer-armel/current/images/versatile/netboot/vmlinuz-3.16.0-6-versatile

# Creating disk
qemu-img create -f qcow2 armdisk.img 1G

# Running 
qemu-system-arm -nographic -M versatilepb -kernel \
vmlinuz-3.16.0-6-versatile \
-initrd initrd.gz \
-hda armdisk.img \
-append "root=/dev/ram" \
-m 256
-vnc :0

qemu-system-arm -M versatilepb -kernel \
vmlinuz-3.16.0-6-versatile \
-initrd initrd.gz \
-hda armdisk.img \
-append "root=/dev/ram" \
-m 256
-vnc :0