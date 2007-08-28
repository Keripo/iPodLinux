######################################################################
# Automatically generated by qmake (2.00a) Fri Jan 6 07:53:19 2006
######################################################################

TEMPLATE = app
TARGET += 
QT += network
DEPENDPATH += .
INCLUDEPATH += .
RESOURCES = installer.qrc
win32:LIBS += -lwsock32

# Installer
HEADERS += installer.h complexwizard.h actions.h panes.h \
           packages.h make_fw2.h scsi_inquiry.h
SOURCES += installer.cc main.cc complexwizard.cc actions.cc \
           packages.cc make_fw2.c firmware.cc scsi_inquiry.c
win32:SOURCES += getopt.c

# Rawpod
SOURCES += rawpod/device.cc rawpod/ext2.cc rawpod/fat32.cc \
           rawpod/partition.cc rawpod/vfs.cc rawpod/mkdosfs.cc \
           rawpod/rawpod.cc
HEADERS += rawpod/device.h rawpod/errors.h rawpod/ext2.h \
           rawpod/fat32.h rawpod/partition.h rawpod/vfs.h \
           rawpod/rawpod.h

# Rawpod mke2fs
INCLUDEPATH += rawpod rawpod/mke2fs rawpod/mke2fs/e2p rawpod/mke2fs/et \
               rawpod/mke2fs/ext2fs rawpod/mke2fs/uuid libtar zlib
HEADERS += rawpod/mke2fs/e2p/e2p.h
SOURCES += rawpod/mke2fs/e2p/feature.cc rawpod/mke2fs/e2p/hashstr.cc \
           rawpod/mke2fs/e2p/iod.cc rawpod/mke2fs/e2p/ls.cc \
           rawpod/mke2fs/e2p/mntopts.cc rawpod/mke2fs/e2p/pe.cc \
           rawpod/mke2fs/e2p/pf.cc rawpod/mke2fs/e2p/ps.cc rawpod/mke2fs/e2p/uuid.cc
HEADERS += rawpod/mke2fs/et/com_err.h rawpod/mke2fs/et/error_table.h rawpod/mke2fs/et/internal.h
SOURCES += rawpod/mke2fs/et/com_err.cc rawpod/mke2fs/et/com_right.cc \
           rawpod/mke2fs/et/error_message.cc rawpod/mke2fs/et/et_name.cc \
           rawpod/mke2fs/et/init_et.cc
HEADERS += rawpod/mke2fs/ext2fs/bitops.h rawpod/mke2fs/ext2fs/brel.h \
           rawpod/mke2fs/ext2fs/e2image.h rawpod/mke2fs/ext2fs/ext2_err.h \
           rawpod/mke2fs/ext2fs/ext2_ext_attr.h rawpod/mke2fs/ext2fs/ext2_io.h \
           rawpod/mke2fs/ext2fs/ext2fs.h rawpod/mke2fs/ext2fs/ext2fsP.h \
           rawpod/mke2fs/ext2fs/irel.h rawpod/mke2fs/ext2fs/jfs_compat.h \
           rawpod/mke2fs/ext2fs/jfs_dat.h rawpod/mke2fs/ext2fs/jfs_user.h \
           rawpod/mke2fs/ext2fs/kernel-jbd.h rawpod/mke2fs/ext2fs/kernel-list.h
SOURCES += rawpod/mke2fs/ext2fs/alloc.cc rawpod/mke2fs/ext2fs/alloc_sb.cc \
           rawpod/mke2fs/ext2fs/alloc_stats.cc rawpod/mke2fs/ext2fs/alloc_tables.cc \
           rawpod/mke2fs/ext2fs/badblocks.cc rawpod/mke2fs/ext2fs/bb_compat.cc \
           rawpod/mke2fs/ext2fs/bb_inode.cc rawpod/mke2fs/ext2fs/bitmaps.cc \
           rawpod/mke2fs/ext2fs/bitops.cc rawpod/mke2fs/ext2fs/block.cc \
           rawpod/mke2fs/ext2fs/bmap.cc rawpod/mke2fs/ext2fs/brel_ma.cc \ 
           rawpod/mke2fs/ext2fs/check_desc.cc rawpod/mke2fs/ext2fs/closefs.cc \
           rawpod/mke2fs/ext2fs/cmp_bitmaps.cc rawpod/mke2fs/ext2fs/dblist.cc \
           rawpod/mke2fs/ext2fs/dblist_dir.cc rawpod/mke2fs/ext2fs/dir_iterate.cc \
           rawpod/mke2fs/ext2fs/dirblock.cc rawpod/mke2fs/ext2fs/dirhash.cc \
           rawpod/mke2fs/ext2fs/dupfs.cc rawpod/mke2fs/ext2fs/expanddir.cc \
           rawpod/mke2fs/ext2fs/ext2_err.cc rawpod/mke2fs/ext2fs/fileio.cc \
           rawpod/mke2fs/ext2fs/freefs.cc rawpod/mke2fs/ext2fs/gen_bitmap.cc \
           rawpod/mke2fs/ext2fs/get_pathname.cc rawpod/mke2fs/ext2fs/getsectsize.cc \
           rawpod/mke2fs/ext2fs/icount.cc rawpod/mke2fs/ext2fs/initialize.cc \
           rawpod/mke2fs/ext2fs/inline.cc rawpod/mke2fs/ext2fs/inode.cc \
           rawpod/mke2fs/ext2fs/irel_ma.cc rawpod/mke2fs/ext2fs/ismounted.cc \
           rawpod/mke2fs/ext2fs/link.cc rawpod/mke2fs/ext2fs/lookup.cc \
           rawpod/mke2fs/ext2fs/mkdir.cc rawpod/mke2fs/ext2fs/mkjournal.cc \
           rawpod/mke2fs/ext2fs/namei.cc rawpod/mke2fs/ext2fs/native.cc \
           rawpod/mke2fs/ext2fs/newdir.cc rawpod/mke2fs/ext2fs/openfs.cc \
           rawpod/mke2fs/ext2fs/read_bb.cc rawpod/mke2fs/ext2fs/read_bb_file.cc \
           rawpod/mke2fs/ext2fs/rs_bitmap.cc rawpod/mke2fs/ext2fs/rw_bitmaps.cc \
           rawpod/mke2fs/ext2fs/swapfs.cc rawpod/mke2fs/ext2fs/unix_io.cc \
           rawpod/mke2fs/ext2fs/unlink.cc rawpod/mke2fs/ext2fs/valid_blk.cc \
           rawpod/mke2fs/ext2fs/version.cc rawpod/mke2fs/ext2fs/write_bb_file.cc 
HEADERS += rawpod/mke2fs/uuid/uuid.h rawpod/mke2fs/uuid/uuidP.h
SOURCES += rawpod/mke2fs/uuid/clear.cc rawpod/mke2fs/uuid/compare.cc \
           rawpod/mke2fs/uuid/gen_uuid.cc rawpod/mke2fs/uuid/isnull.cc \
           rawpod/mke2fs/uuid/pack.cc rawpod/mke2fs/uuid/parse.cc \
           rawpod/mke2fs/uuid/unpack.cc rawpod/mke2fs/uuid/unparse.cc
SOURCES += rawpod/mke2fs/mke2fs_app.cc

# Libtar
SOURCES += libtar/tblock.cc libtar/decode.cc libtar/extract.cc libtar/handle.cc \
           libtar/hash.cc libtar/list.cc libtar/output.cc libtar/util.cc
HEADERS += libtar/libtar.h libtar/listhash.h
win32:HEADERS += libtar/strsep.h

# Zlib
SOURCES += zlib/adler32.c zlib/compress.c zlib/crc32.c \
           zlib/deflate.c zlib/gzio.c zlib/infback.c \
           zlib/inffast.c zlib/inflate.c zlib/inftrees.c \
           zlib/trees.c zlib/uncompr.c zlib/zutil.c
HEADERS += zlib/crc32.h zlib/deflate.h zlib/inffast.h \
           zlib/inffixed.h zlib/inflate.h zlib/inftrees.h \
           zlib/trees.h zlib/zconf.h zlib/zlib.h zlib/zutil.h

DEFINES += EMBED_MAKEFW
nocrypto:DEFINES += DONT_HAVE_LIBCRYPTO
!nocrypto:LIBS += -lcrypto

#CONFIG += release
