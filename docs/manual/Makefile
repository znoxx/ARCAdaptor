PANDOC=pandoc
TOCDEPTH=4
TEMPLATE=html5template
PANDOC_OPTIONS=-s --toc --toc-depth=$(TOCDEPTH) --template=$(TEMPLATE)

index.html: ARCAdaptor-MANUAL.markdown metadata.yaml
	$(PANDOC) $(PANDOC_OPTIONS) $^  -o index.html 
   

.PHONY: clean

clean:
	rm -f index.html

