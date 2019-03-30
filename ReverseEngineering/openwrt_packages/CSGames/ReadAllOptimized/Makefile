include $(TOPDIR)/rules.mk

# Name, version and release number
# The name and version of your package are used to define the variable to point to the build directory of your package: $(PKG_BUILD_DIR)
PKG_NAME:=ReadAllOptimized
PKG_VERSION:=1.0
PKG_RELEASE:=1

# Source settings (i.e. where to find the source codes)
# This is a custom variable, used belo
SOURCE_DIR:=$(SOURCE_ROOT)/ReverseEngineering/ReadAllOptimized

include $(INCLUDE_DIR)/package.mk
RSTRIP:=:

# Package definition; instructs on how and where our package will appear in the overall configuration menu ('make menuconfig')
define Package/ReadAllOptimized
	SECTION:=CSGames
	CATEGORY:=CSGames
	TITLE:=ReadAllOptimized
endef

# Package description; a more verbose description on what our package does
define Package/ReadAllOptimized/description
  RE200 challenge from CSGames 2019.
endef

# Package preparation instructions; create the build directory and copy the source code. 
# The last command is necessary to ensure our preparation instructions remain compatible with the patching system.
define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	cp $(SOURCE_DIR)/third_lock.c $(PKG_BUILD_DIR)
	$(Build/Patch)
endef

# Package build instructions; invoke the target-specific compiler to first compile the source file, and then to link the file into the final executable
define Build/Compile
	$(TARGET_CC) $(TARGET_CFLAGS) -o $(PKG_BUILD_DIR)/third_lock.o -c $(PKG_BUILD_DIR)/third_lock.c -static -z execstack
	$(TARGET_CC) $(TARGET_LDFLAGS) -o $(PKG_BUILD_DIR)/$1 $(PKG_BUILD_DIR)/third_lock.o -static -z execstack
endef

# Package install instructions; create a directory inside the package to hold our executable, and then copy the executable we built previously into the folder
define Package/ReadAllOptimized/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ReadAllOptimized $(1)/usr/bin
endef

# This command is always the last, it uses the definitions and variables we give above in order to get the job done
$(eval $(call BuildPackage,ReadAllOptimized))
