KERNEL_MODULE_AUTOLOAD += "xfs"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED = "rtc"

PREFERRED_VERSION_linux-axas = "4.10.12"

#Provider
PREFERRED_PROVIDER_virtual/kernel ?= "linux-axas"
PREFERRED_PROVIDER_virtual/egl ?= "axas-libgles-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles1 ?= "axas-libgles-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles2 ?= "axas-libgles-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgl ?= "mesa"
PREFERRED_PROVIDER_virtual/mesa ?= "mesa"

require conf/machine/include/tune-cortexa15.inc
require conf/machine/include/axas-essential.inc

PACKAGECONFIG_GL_pn-qtbase = " "
PACKAGECONFIG_append_pn-qtbase += " gles2 linuxfb"

MACHINE_EXTRA_RRECOMMENDS = " \
	gst-plugin-dvbmediasink \
	ntfs-3g \
	"

DVBMEDIASINK_CONFIG += " --with-h265 --with-vb8 --with-vb9 --with-opus --with-wma --with-wmv --with-pcm --with-dts --with-eac3"

MACHINE_FEATURES += " alsa usbhost wlan 3dtv switchoff osdposition hdmicec"

IMAGEVERSION := "${DISTRO_NAME}-${DISTRO_VERSION}-${DATE}"
IMAGEVERSION[vardepsexclude] = "DATE"
IMAGEDIR ?= "${MACHINE}"
IMGDEPLOYDIR ?= "${DEPLOY_DIR_IMAGE}"

IMAGE_CMD_axasemmc_append = "\
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}.emmc.img ${IMGDEPLOYDIR}/${IMAGEDIR}/disk.img; \
	echo "${IMAGEVERSION}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/imageversion; \
	cp ${DEPLOY_DIR_IMAGE}/zImage ${IMGDEPLOYDIR}/${IMAGEDIR}/kernel.bin; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.tar ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.tar; \
	bzip2 ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.tar; \
	cd ${IMGDEPLOYDIR}; \
	zip ${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_usb.zip ${IMAGEDIR}/disk.img ${IMAGEDIR}/imageversion; \
	zip ${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_multiboot_ofgwrite.zip ${IMAGEDIR}/imageversion ${IMAGEDIR}/kernel.bin ${IMAGEDIR}/rootfs.tar.bz2; \
	rm -Rf ${IMAGEDIR}; \
	"

IMAGE_CMD_prepend = " \
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	"
