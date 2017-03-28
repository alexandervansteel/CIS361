#!/bin/bash
while read f; do
	[[ -d "$f" ]] || echo "$f";
done
