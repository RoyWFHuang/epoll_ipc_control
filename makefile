
SUBDIR = src
MAKE_DIR = $(SUBDIR:%=build-%)
MAKECLEAN_DIR = $(SUBDIR:%=clean-%)

.PHONY: $(MAKE_DIR) $(MAKECLEAN_DIR)

all: $(MAKE_DIR)

$(MAKE_DIR) : 
	@echo
	@echo Making all in subdirectory $@...
	@make -C $(@:build-%=%)
	
clean: $(MAKECLEAN_DIR)	

$(MAKECLEAN_DIR) :
	@echo
	@echo Making all in subdirectory $@...
	@make -C $(@:clean-%=%) clean

