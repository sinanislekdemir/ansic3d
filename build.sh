#!/bin/bash
rm -f build/*
python bbee
python bbee --install
python bbee --i=test.json
