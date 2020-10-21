.PHONY: clean
SHELL = /usr/bin/env bash

print: whereami
	cat whereami | xargs echo "I am in"

whereami:
	pwd > whereami

duplicate: whereami
	cp whereami duplicate

clean:
	rm -f whereami duplicate
