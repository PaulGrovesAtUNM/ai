.PHONY: clean All

All:
	@echo "----------Building project:[ ai - Debug ]----------"
	@$(MAKE) -f  "ai.mk"
clean:
	@echo "----------Cleaning project:[ ai - Debug ]----------"
	@$(MAKE) -f  "ai.mk" clean
